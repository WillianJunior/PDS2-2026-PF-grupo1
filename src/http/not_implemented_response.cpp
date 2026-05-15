#include "http/not_implemented_response.h"

namespace edu_social::http {

crow::response make_not_implemented_response(const std::string& method, const std::string& route_pattern) {
    crow::json::wvalue response;
    response["message"] = "Feature not implemented yet.";
    response["status"] = "not_implemented";
    response["method"] = method;
    response["route"] = route_pattern;

    crow::response http_response(501);
    http_response.code = 501;
    http_response.set_header("Content-Type", "application/json");
    http_response.body = response.dump();
    return http_response;
}

}
