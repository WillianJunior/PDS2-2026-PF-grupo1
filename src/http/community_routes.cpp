#include "http/community_routes.h"

#include "http/not_implemented_response.h"

namespace edu_social::http {

void register_community_routes(crow::SimpleApp& app) {
    CROW_ROUTE(app, "/communities").methods(crow::HTTPMethod::Get)([]() {
        return make_not_implemented_response("GET", "/communities");
    });

    CROW_ROUTE(app, "/communities").methods(crow::HTTPMethod::Post)([]() {
        return make_not_implemented_response("POST", "/communities");
    });

    CROW_ROUTE(app, "/communities/<int>").methods(crow::HTTPMethod::Get)([](int) {
        return make_not_implemented_response("GET", "/communities/{id}");
    });

    CROW_ROUTE(app, "/communities/<int>/members").methods(crow::HTTPMethod::Post)([](int) {
        return make_not_implemented_response("POST", "/communities/{id}/members");
    });

    CROW_ROUTE(app, "/communities/<int>/members/<int>").methods(crow::HTTPMethod::Delete)([](int, int) {
        return make_not_implemented_response("DELETE", "/communities/{id}/members/{userId}");
    });

    CROW_ROUTE(app, "/communities/<int>/posts").methods(crow::HTTPMethod::Get)([](int) {
        return make_not_implemented_response("GET", "/communities/{id}/posts");
    });
}

}
