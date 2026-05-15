#pragma once

#include <crow.h>

namespace edu_social::http {

/**
 * @brief Registers the health endpoint of the application.
 *
 * Current route:
 * - GET /health
 *
 * This is the only endpoint with implemented runtime behavior in the current
 * checkpoint.
 *
 * @param app Crow application that receives the route.
 * @param database_connected Indicates whether the database is available.
 */
void register_health_routes(crow::SimpleApp& app, bool database_connected);

}
