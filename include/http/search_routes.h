#pragma once

#include <crow.h>

namespace edu_social::http {

/**
 * @brief Registers search routes.
 *
 * Current routes:
 * - GET /search
 *
 * At this checkpoint this route exposes the planned API surface and returns a
 * standard HTTP 501 payload.
 *
 * @param app Crow application that receives the routes.
 */
void register_search_routes(crow::SimpleApp& app);

}
