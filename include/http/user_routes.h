#pragma once

#include <crow.h>

#include "database/sqlite_connection.h"

namespace edu_social::http {

/**
 * @brief Registers user profile routes.
 *
 * Current routes:
 * - GET  /users/{id}
 * - POST /users
 *
 * @param app Crow application that receives the routes.
 * @param db SQLite connection used by the route handlers.
 */
void register_user_routes(crow::SimpleApp& app, edu_social::SQLiteConnection& db);

}
