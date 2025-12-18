#pragma once

#include "database/login_database.hpp"
#include "utils/ts_queue.hpp"
#include "subsystems/database_subsystem.hpp"

namespace ep::db
{
  class DBPoll {
  public:
    explicit DBPoll(const std::string& host, const std::string& user, 
                    const std::string& password, const std::string& db_name, 
                    std::size_t workers_num);
    ~DBPoll() = default;
    DBPoll(const DBPoll&) = delete;
    DBPoll& operator=(const DBPoll&) = delete;

    void Run();

  private:
    TSQueue<LoginDataBase> workers_;
    std::shared_ptr<DBSubsystem> db_sybsystem_;
  }; 
}
