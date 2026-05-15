#include "http/feed_routes.h"

#include "http/not_implemented_response.h"

namespace edu_social::http {

void register_feed_routes(crow::SimpleApp& app) {
    CROW_ROUTE(app, "/feed").methods(crow::HTTPMethod::Get)([]() {
        return make_not_implemented_response("GET", "/feed");
    });
}

}
