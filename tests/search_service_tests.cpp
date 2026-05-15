#include <doctest/doctest.h>

#include "domain/community.hpp"
#include "domain/post.hpp"
#include "domain/search_service.hpp"

using edu_social::domain::Community;
using edu_social::domain::Post;
using edu_social::domain::SearchService;

TEST_SUITE("SearchService") {

TEST_CASE("Search service filters communities and posts") {
    SearchService service;
    std::vector<Community> communities = {
        Community(7, 40, "Mathematics", "Formal reasoning"),
        Community(8, 41, "Programming", "Implementation and refactoring")
    };
    std::vector<Post> posts = {
        Post(20, 40, 7, "Linear algebra", "Matrices and vectors", "2026-05-14T22:30:00Z", "2026-05-14T22:30:00Z"),
        Post(21, 41, 8, "Refactoring", "Domain reorganization plan", "2026-05-14T22:40:00Z", "2026-05-14T22:40:00Z")
    };

    CHECK(service.search_communities_by_name(communities, "prog").size() == 1);
    CHECK(service.search_posts_by_keyword(posts, "domain").size() == 1);
    CHECK(service.filter_posts_by_author(posts, 40).size() == 1);
}

}
