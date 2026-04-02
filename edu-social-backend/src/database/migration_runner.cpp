#include "database/migration_runner.h"

#include <fstream>
#include <sstream>
#include <stdexcept>

namespace edu_social {

namespace {

std::string read_text_file(const std::string& file_path) {
    std::ifstream input(file_path);
    if (!input.is_open()) {
        throw std::runtime_error("failed to open file: " + file_path);
    }

    std::ostringstream buffer;
    buffer << input.rdbuf();
    return buffer.str();
}

}  // namespace

MigrationRunner::MigrationRunner(SQLiteConnection& connection) : connection_(connection) {}

void MigrationRunner::apply_schema(const std::string& schema_path) const {
    const std::string schema_sql = read_text_file(schema_path);
    if (schema_sql.empty()) {
        return;
    }

    connection_.execute(schema_sql);
}

} 