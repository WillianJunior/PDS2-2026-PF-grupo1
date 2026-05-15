#pragma once

#include <crow.h>

namespace edu_social::http {

/**
 * @brief Registers user profile routes.
 *
 * Current routes:
 * - GET /users/{id}
 *
 * At this checkpoint this route exposes the planned API surface and returns a
 * standard HTTP 501 payload.
 *
 * @param app Crow application that receives the routes.
 */
void register_user_routes(crow::SimpleApp& app);

}
