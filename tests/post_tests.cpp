#include <doctest/doctest.h>

#include "domain/comment.hpp"
#include "domain/post.hpp"

using edu_social::domain::Comment;
using edu_social::domain::ContentKind;
using edu_social::domain::Post;

TEST_SUITE("Post") {

TEST_CASE("Post composes comments") {
    Post post(2, 14, 9, "Algorithms", "Graph discussion", "2026-05-14T19:30:00Z", "2026-05-14T19:30:00Z");
    Comment comment(8, 15, 2, "Great topic", "2026-05-14T19:40:00Z", "2026-05-14T19:40:00Z");

    post.add_comment(comment);

    CHECK(post.community_id() == 9);
    CHECK(post.kind() == ContentKind::post);
    CHECK(post.comment_count() == 1);
    CHECK(post.comments().front().post_id() == 2);
    CHECK(post.remove_comment(8));
    CHECK(post.comment_count() == 0);
}

}
