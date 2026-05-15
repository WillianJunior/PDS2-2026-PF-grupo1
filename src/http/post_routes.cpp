#include "http/post_routes.h"

#include "http/not_implemented_response.h"

namespace edu_social::http {

void register_post_routes(crow::SimpleApp& app) {
    CROW_ROUTE(app, "/posts").methods(crow::HTTPMethod::Post)([]() {
        return make_not_implemented_response("POST", "/posts");
    });

    CROW_ROUTE(app, "/posts/<int>").methods(crow::HTTPMethod::Get)([](int) {
        return make_not_implemented_response("GET", "/posts/{id}");
    });

    CROW_ROUTE(app, "/posts/<int>/comments").methods(crow::HTTPMethod::Post)([](int) {
        return make_not_implemented_response("POST", "/posts/{id}/comments");
    });

    CROW_ROUTE(app, "/posts/<int>/comments").methods(crow::HTTPMethod::Get)([](int) {
        return make_not_implemented_response("GET", "/posts/{id}/comments");
    });

    CROW_ROUTE(app, "/posts/<int>/likes").methods(crow::HTTPMethod::Post)([](int) {
        return make_not_implemented_response("POST", "/posts/{id}/likes");
    });

    CROW_ROUTE(app, "/posts/<int>/likes/<int>").methods(crow::HTTPMethod::Delete)([](int, int) {
        return make_not_implemented_response("DELETE", "/posts/{id}/likes/{userId}");
    });
}

}
