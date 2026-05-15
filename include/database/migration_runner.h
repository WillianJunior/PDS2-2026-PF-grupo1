#pragma once

#include <string>

#include "database/sqlite_connection.h"

namespace edu_social {

/**
 * @brief Applies the SQL schema that initializes the project database.
 *
 * MigrationRunner keeps schema application isolated from the rest of the
 * bootstrap flow so the application setup remains small and explicit.
 */
class MigrationRunner {
public:
    /**
     * @brief Binds the runner to an already opened connection.
     *
     * @param connection Database connection used to execute the schema.
     */
    explicit MigrationRunner(SQLiteConnection& connection);

    /**
     * @brief Reads and executes the schema file.
     *
     * The file is expected to contain the complete schema required by the
     * current checkpoint.
     *
     * @param schema_path Path to the SQL schema file.
     */
    void apply_schema(const std::string& schema_path) const;

private:
    SQLiteConnection& connection_;
};

}
