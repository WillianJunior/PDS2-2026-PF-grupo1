#pragma once

#include <crow.h>
#include <string>

namespace edu_social::http {

/**
 * @brief Builds the standard response used by routes that are already
 * registered but still not implemented.
 *
 * The payload keeps the method and logical route pattern visible so API
 * consumers and reviewers can confirm which contract was reached at runtime.
 *
 * @param method HTTP method associated with the route.
 * @param route_pattern Logical route pattern used in the documentation.
 * @return HTTP 501 response with a standard JSON payload.
 */
crow::response make_not_implemented_response(const std::string& method, const std::string& route_pattern);

}
