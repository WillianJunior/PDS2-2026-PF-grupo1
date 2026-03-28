#include "database/sqlite_connection.h"

#include <stdexcept>
#include <string>

namespace edu_social {

SQLiteConnection::~SQLiteConnection() {
    close();
}

void SQLiteConnection::open(const std::string& database_path) {
    close();

    const int open_result = sqlite3_open(database_path.c_str(), &handle_);
    if (open_result != SQLITE_OK) {
        const std::string error_message = handle_ != nullptr ? sqlite3_errmsg(handle_) : "unknown sqlite error";
        close();
        throw std::runtime_error("failed to open sqlite database: " + error_message);
    }

    execute("PRAGMA foreign_keys = ON;");
}

void SQLiteConnection::close() {
    if (handle_ == nullptr) {
        return;
    }

    sqlite3_close(handle_);
    handle_ = nullptr;
}

void SQLiteConnection::execute(const std::string& sql) const {
    if (handle_ == nullptr) {
        throw std::runtime_error("sqlite connection is not open");
    }

    char* error_message = nullptr;
    const int execute_result = sqlite3_exec(handle_, sql.c_str(), nullptr, nullptr, &error_message);

    if (execute_result != SQLITE_OK) {
        const std::string sqlite_message = error_message != nullptr ? error_message : "unknown sqlite error";
        sqlite3_free(error_message);
        throw std::runtime_error("sqlite execution failed: " + sqlite_message);
    }
}

bool SQLiteConnection::is_open() const {
    return handle_ != nullptr;
}

sqlite3* SQLiteConnection::raw_handle() const {
    return handle_;
}

}