#include "http/search_routes.h"

#include "http/not_implemented_response.h"

namespace edu_social::http {

void register_search_routes(crow::SimpleApp& app) {
    CROW_ROUTE(app, "/search").methods(crow::HTTPMethod::Get)([]() {
        return make_not_implemented_response("GET", "/search");
    });
}

}
