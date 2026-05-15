#include <doctest/doctest.h>

#include "domain/community.hpp"
#include "domain/feed.hpp"
#include "domain/post.hpp"

using edu_social::domain::Community;
using edu_social::domain::Feed;
using edu_social::domain::Post;
using edu_social::domain::PostSource;

TEST_SUITE("Feed") {

TEST_CASE("Feed aggregates posts from multiple sources") {
    Community databases(5, 30, "Databases", "SQL and modeling");
    Community oop(6, 31, "OOP", "Inheritance and composition");

    databases.publish_post(Post(11, 30, 5, "Normalization", "Third normal form discussion", "2026-05-14T22:10:00Z", "2026-05-14T22:10:00Z"));
    oop.publish_post(Post(12, 31, 6, "Polymorphism", "Examples for the presentation", "2026-05-14T22:20:00Z", "2026-05-14T22:20:00Z"));

    Feed feed(30, "Main feed");
    feed.ingest(databases);
    feed.ingest(oop);

    CHECK(feed.post_count() == 2);
    CHECK(feed.source_labels().size() == 2);

    const PostSource& source = feed;
    CHECK(source.source_name() == "Main feed");
    CHECK(source.list_posts().size() == 2);
}

}
