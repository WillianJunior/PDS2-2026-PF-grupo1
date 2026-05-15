#include "http/auth_routes.h"

#include "http/not_implemented_response.h"

namespace edu_social::http {

void register_auth_routes(crow::SimpleApp& app) {
    CROW_ROUTE(app, "/auth/register").methods(crow::HTTPMethod::Post)([]() {
        return make_not_implemented_response("POST", "/auth/register");
    });

    CROW_ROUTE(app, "/auth/login").methods(crow::HTTPMethod::Post)([]() {
        return make_not_implemented_response("POST", "/auth/login");
    });
}

}
