#pragma once

#include <crow.h>

namespace edu_social::http {

/**
 * @brief Registers authentication routes.
 *
 * Current routes:
 * - POST /auth/register
 * - POST /auth/login
 *
 * At this checkpoint these routes expose the planned API surface and return a
 * standard HTTP 501 payload.
 *
 * @param app Crow application that receives the routes.
 */
void register_auth_routes(crow::SimpleApp& app);

}
