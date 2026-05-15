#include <doctest/doctest.h>

#include "domain/comment.hpp"

using edu_social::domain::Comment;
using edu_social::domain::ContentKind;

TEST_SUITE("Comment") {

TEST_CASE("Comment keeps the parent post identifier") {
    Comment comment(7, 12, 4, "Useful reply", "2026-05-14T21:00:00Z", "2026-05-14T21:00:00Z");

    CHECK(comment.post_id() == 4);
    CHECK(comment.kind() == ContentKind::comment);
    CHECK(comment.summary().find("post #4") != std::string::npos);
}

}
