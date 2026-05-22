#include <doctest/doctest.h>

#include "domain/community.hpp"
#include "domain/post.hpp"

using edu_social::domain::Community;
using edu_social::domain::Post;
using edu_social::domain::PostSource;

static Post make_post(int id) {
    return Post(id, 21, 4, "Title", "Body", "2026-05-14T22:00:00Z", "2026-05-14T22:00:00Z");
}

TEST_SUITE("Community") {

TEST_CASE("Constructor adds owner as first member") {
    Community community(4, 21, "PDS II", "desc");

    CHECK(community.member_count() == 1);
    CHECK(community.has_member(21));
}

TEST_CASE("Getters return construction values") {
    Community community(4, 21, "PDS II", "Community for project coordination");

    CHECK(community.id() == 4);
    CHECK(community.owner_id() == 21);
    CHECK(community.name() == "PDS II");
    CHECK(community.description() == "Community for project coordination");
}

TEST_CASE("add_member increases count") {
    Community community(4, 21, "PDS II", "desc");

    community.add_member(22);

    CHECK(community.member_count() == 2);
    CHECK(community.has_member(22));
}

TEST_CASE("add_member ignores duplicate") {
    Community community(4, 21, "PDS II", "desc");

    community.add_member(22);
    community.add_member(22);

    CHECK(community.member_count() == 2);
}

TEST_CASE("remove_member returns false when member does not exist") {
    Community community(4, 21, "PDS II", "desc");

    CHECK(community.remove_member(99) == false);
}

TEST_CASE("remove_member removes existing member and returns true") {
    Community community(4, 21, "PDS II", "desc");
    community.add_member(22);

    CHECK(community.remove_member(22) == true);
    CHECK(community.has_member(22) == false);
    CHECK(community.member_count() == 1);
}

TEST_CASE("has_member returns false for unknown user") {
    Community community(4, 21, "PDS II", "desc");

    CHECK(community.has_member(99) == false);
}

TEST_CASE("publish_post increases post count") {
    Community community(4, 21, "PDS II", "desc");

    community.publish_post(make_post(10));

    CHECK(community.post_count() == 1);
}

TEST_CASE("remove_post returns false when post does not exist") {
    Community community(4, 21, "PDS II", "desc");

    CHECK(community.remove_post(99) == false);
}

TEST_CASE("remove_post removes existing post and returns true") {
    Community community(4, 21, "PDS II", "desc");
    community.publish_post(make_post(10));

    CHECK(community.remove_post(10) == true);
    CHECK(community.post_count() == 0);
}

TEST_CASE("member_ids returns all members including owner") {
    Community community(4, 21, "PDS II", "desc");
    community.add_member(22);

    const auto& ids = community.member_ids();
    CHECK(ids.size() == 2);
    CHECK(ids[0] == 21);
    CHECK(ids[1] == 22);
}

TEST_CASE("posts returns composed post collection") {
    Community community(4, 21, "PDS II", "desc");
    community.publish_post(make_post(10));

    CHECK(community.posts().size() == 1);
    CHECK(community.posts()[0].id() == 10);
}

TEST_CASE("Community acts as PostSource") {
    Community community(4, 21, "PDS II", "desc");
    community.publish_post(make_post(10));

    const PostSource& source = community;
    CHECK(source.source_name() == "PDS II");
    CHECK(source.list_posts().size() == 1);
}

}