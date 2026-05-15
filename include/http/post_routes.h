#pragma once

#include <crow.h>

namespace edu_social::http {

/**
 * @brief Registers post, comment and like routes.
 *
 * Current routes:
 * - POST /posts
 * - GET /posts/{id}
 * - POST /posts/{id}/comments
 * - GET /posts/{id}/comments
 * - POST /posts/{id}/likes
 * - DELETE /posts/{id}/likes/{userId}
 *
 * At this checkpoint these routes expose the planned API surface and return a
 * standard HTTP 501 payload.
 *
 * @param app Crow application that receives the routes.
 */
void register_post_routes(crow::SimpleApp& app);

}
