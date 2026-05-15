#include <doctest/doctest.h>

#include "domain/community.hpp"
#include "domain/post.hpp"

using edu_social::domain::Community;
using edu_social::domain::Post;
using edu_social::domain::PostSource;

TEST_SUITE("Community") {

TEST_CASE("Community composes members and posts and behaves as a post source") {
    Community community(4, 21, "PDS II", "Community for project coordination");
    Post post(10, 21, 4, "Checkpoint", "We need to review CRC cards", "2026-05-14T22:00:00Z", "2026-05-14T22:00:00Z");

    community.add_member(22);
    community.publish_post(post);

    CHECK(community.member_count() == 2);
    CHECK(community.post_count() == 1);
    CHECK(community.has_member(22));

    const PostSource& source = community;
    CHECK(source.source_name() == "PDS II");
    CHECK(source.list_posts().size() == 1);
}

}
