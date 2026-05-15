#include "http/user_routes.h"

#include "http/not_implemented_response.h"

namespace edu_social::http {

void register_user_routes(crow::SimpleApp& app) {
    CROW_ROUTE(app, "/users/<int>").methods(crow::HTTPMethod::Get)([](int) {
        return make_not_implemented_response("GET", "/users/{id}");
    });
}

}
