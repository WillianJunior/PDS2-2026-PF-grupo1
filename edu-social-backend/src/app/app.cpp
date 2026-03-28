#include "app/app.h"

#include <cstdint>
#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <string>

#include <crow.h>

#include "database/migration_runner.h"
#include "database/sqlite_connection.h"

namespace edu_social {

int App::run() {
    const auto project_root = std::filesystem::current_path();
    const auto database_dir = project_root / "database";
    const auto database_path = database_dir / "app.db";
    const auto schema_path = database_dir / "schema.sql";

    std::filesystem::create_directories(database_dir);

    SQLiteConnection connection;
    connection.open(database_path.string());

    MigrationRunner migration_runner(connection);
    migration_runner.apply_schema(schema_path.string());

    crow::SimpleApp app;
    const std::string database_status = connection.is_open() ? "connected" : "disconnected";

    CROW_ROUTE(app, "/health")([database_status]() {
        crow::json::wvalue response;
        response["status"] = "ok";
        response["database"] = database_status;
        return response;
    });

    constexpr std::uint16_t port = 18080;

    std::cout << "Server listening on http://localhost:" << port << std::endl;
    std::cout << "Health check available at /health" << std::endl;

    app.port(port).multithreaded().run();
    return 0;
}

}  