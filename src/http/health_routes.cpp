#include "http/health_routes.h"

namespace edu_social::http {

void register_health_routes(crow::SimpleApp& app, bool database_connected) {
    CROW_ROUTE(app, "/health")([database_connected]() {
        crow::json::wvalue response;
        response["status"] = "ok";
        response["database"] = database_connected ? "connected" : "disconnected";
        response["service"] = "edu-social-backend";
        return response;
    });
}

}
