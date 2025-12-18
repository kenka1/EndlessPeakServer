#include "db_pool.hpp"

#include <memory>

#include <spdlog/spdlog.h>

#include "connection/sql_connection.hpp"
#include "database/login_database.hpp"

namespace ep::db
{
  DBPoll::DBPoll(const std::string& host, const std::string& user, 
                      const std::string& password, const std::string& db_name, 
                      std::size_t workers_num)
  {
    int workers_start = 0;
    for (std::size_t i = 0; i < workers_num; i++) {
      auto con = SQLConnection::Load(host, user, password, db_name);
      if (!con) {
        spdlog::error("SQLConnection::Load()\nfile: {} line: {}", __FILE__, __LINE__);
        continue;
      }
      auto login_db = std::make_shared<LoginDataBase>(std::move(con.value()));
      workers_.Push(std::move(login_db));
      workers_start++;
    }

    spdlog::info("Load {} of {} database workers", workers_start, workers_num);
  }

  void DBPoll::Run()
  {
    for (;;) {
      auto packet = db_sybsystem_->in_queue_.WaitAndPop(); 
      auto worker = workers_.WaitAndPop();

      worker->HandlePacket(std::move(packet));
    }
  }
}
