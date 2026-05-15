#pragma once

#include <string>

#include <sqlite3.h>

namespace edu_social {

/**
 * @brief Encapsulates the lifecycle of the SQLite connection used by the app.
 *
 * The object owns the raw SQLite handle and centralizes the low-level
 * operations needed by bootstrap and future persistence adapters.
 */
class SQLiteConnection {
public:
    SQLiteConnection() = default;
    ~SQLiteConnection();

    SQLiteConnection(const SQLiteConnection&) = delete;
    SQLiteConnection& operator=(const SQLiteConnection&) = delete;

    /**
     * @brief Opens a database file and enables foreign key support.
     *
     * After a successful call, the connection owns a valid SQLite handle until
     * close() or destruction.
     *
     * @param database_path Absolute or relative path to the database file.
     */
    void open(const std::string& database_path);

    /**
     * @brief Closes the underlying SQLite handle when it exists.
     */
    void close();

    /**
     * @brief Executes a raw SQL statement.
     *
     * @param sql SQL statement or batch to be executed.
     */
    void execute(const std::string& sql) const;

    /**
     * @brief Reports whether the connection currently owns an open handle.
     *
     * @return True when the SQLite handle is open.
     */
    bool is_open() const;

    /**
     * @brief Exposes the raw SQLite handle for integration code.
     *
     * @return Raw pointer managed by the connection object.
     */
    sqlite3* raw_handle() const;

private:
    sqlite3* handle_ = nullptr;
};

}
