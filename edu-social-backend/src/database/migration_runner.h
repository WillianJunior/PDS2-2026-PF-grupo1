#pragma once

#include <string>

#include "database/sqlite_connection.h"

namespace edu_social {

class MigrationRunner {
public:
    explicit MigrationRunner(SQLiteConnection& connection);

    void apply_schema(const std::string& schema_path) const;

private:
    SQLiteConnection& connection_;
};

} 