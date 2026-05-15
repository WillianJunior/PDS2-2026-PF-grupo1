#pragma once

#include <crow.h>

namespace edu_social::http {

/**
 * @brief Registers community and membership routes.
 *
 * Current routes:
 * - GET /communities
 * - POST /communities
 * - GET /communities/{id}
 * - POST /communities/{id}/members
 * - DELETE /communities/{id}/members/{userId}
 * - GET /communities/{id}/posts
 *
 * At this checkpoint these routes expose the planned API surface and return a
 * standard HTTP 501 payload.
 *
 * @param app Crow application that receives the routes.
 */
void register_community_routes(crow::SimpleApp& app);

}
