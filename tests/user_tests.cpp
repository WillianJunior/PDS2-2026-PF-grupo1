#include <doctest/doctest.h>

#include "domain/user.hpp"

using edu_social::domain::User;

TEST_SUITE("User") {

TEST_CASE("User tracks followed users and joined communities") {
    User user(1, "user", "User Example", "user@example.com", "Initial bio", "2026-05-14T18:00:00Z");

    user.follow_user(2);
    user.follow_user(2);
    user.join_community(30);
    user.join_community(30);

    CHECK(user.follows(2));
    CHECK(user.belongs_to(30));
    CHECK_EQ(user.followed_user_ids().size(), 1);
    CHECK_EQ(user.joined_community_ids().size(), 1);
}

TEST_CASE("User updates mutable profile data") {
    User user(1, "user", "User Example", "user@example.com", "Initial bio", "2026-05-14T18:00:00Z");

    user.update_bio("Updated bio");

    CHECK_EQ(user.bio(), "Updated bio");
    CHECK_EQ(user.unfollow_user(999), false);
    CHECK(user.leave_community(999) == false);
}

}
