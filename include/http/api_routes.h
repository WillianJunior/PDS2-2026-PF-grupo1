#pragma once

#include <crow.h>

#include "database/sqlite_connection.h"

namespace edu_social::http {

/**
 * @brief Registers the current API surface for the backend.
 *
 * This function is only a composition point for the resource-specific route
 * modules. It delegates registration to auth, user, community, post, feed and
 * search route files.
 *
 * Only the health endpoint is implemented with business behavior. The
 * remaining routes already exist and return a standard not implemented payload
 * so the external contract is visible and callable during the current
 * checkpoint.
 *
 * @param app Crow application that receives the routes.
 * @param db SQLite connection used by the route handlers.
 */
void register_api_routes(crow::SimpleApp& app, edu_social::SQLiteConnection& db);

}
