#pragma once

#include <string>

#include <sqlite3.h>

namespace edu_social {

class SQLiteConnection {
public:
    SQLiteConnection() = default;
    ~SQLiteConnection();

    SQLiteConnection(const SQLiteConnection&) = delete;
    SQLiteConnection& operator=(const SQLiteConnection&) = delete;

    void open(const std::string& database_path);
    void close();
    void execute(const std::string& sql) const;

    bool is_open() const;
    sqlite3* raw_handle() const;

private:
    sqlite3* handle_ = nullptr;
};

}
