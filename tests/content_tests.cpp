#include <type_traits>

#include <doctest/doctest.h>

#include "domain/comment.hpp"
#include "domain/post.hpp"

using edu_social::domain::Comment;
using edu_social::domain::Content;
using edu_social::domain::ContentKind;
using edu_social::domain::Post;

TEST_SUITE("Content") {

TEST_CASE("Content defines the abstract contract reused by posts and comments") {
    CHECK(std::is_abstract_v<Content>);

    Post post(1, 10, 20, "First post", "Domain body", "2026-05-14T19:00:00Z", "2026-05-14T19:00:00Z");
    Content& as_content = post;

    CHECK(as_content.id() == 1);
    CHECK(as_content.author_id() == 10);
    CHECK(as_content.kind() == ContentKind::post);
    CHECK(as_content.like_count() == 0);

    as_content.register_like();
    CHECK(as_content.like_count() == 1);

    as_content.edit_body("Edited body", "2026-05-14T20:00:00Z");
    CHECK(as_content.body() == "Edited body");
    CHECK(as_content.updated_at() == "2026-05-14T20:00:00Z");
}

TEST_CASE("Comments also satisfy the content contract polymorphically") {
    Comment comment(3, 11, 1, "Reply body", "2026-05-14T20:10:00Z", "2026-05-14T20:10:00Z");
    Content& as_content = comment;

    CHECK(as_content.kind() == ContentKind::comment);
    CHECK(as_content.summary().find("Comment #3") != std::string::npos);
}

}
