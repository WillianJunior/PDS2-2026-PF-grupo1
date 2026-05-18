#include "http/api_routes.h"

#include "http/auth_routes.h"
#include "http/community_routes.h"
#include "http/feed_routes.h"
#include "http/post_routes.h"
#include "http/search_routes.h"
#include "http/user_routes.h"

namespace edu_social::http {

void register_api_routes(crow::SimpleApp& app, edu_social::SQLiteConnection& db) {
    register_auth_routes(app);
    register_user_routes(app, db);
    register_community_routes(app);
    register_post_routes(app);
    register_feed_routes(app);
    register_search_routes(app);
}

}
