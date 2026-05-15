#include "domain/user.hpp"

#include <algorithm>
#include <utility>

namespace edu_social::domain {

User::User(
    int id,
    std::string username,
    std::string full_name,
    std::string email,
    std::string bio,
    std::string joined_at)
    : id_(id),
      username_(std::move(username)),
      full_name_(std::move(full_name)),
      email_(std::move(email)),
      bio_(std::move(bio)),
      joined_at_(std::move(joined_at)) {}

int User::id() const {
    return id_;
}

const std::string& User::username() const {
    return username_;
}

const std::string& User::full_name() const {
    return full_name_;
}

const std::string& User::email() const {
    return email_;
}

const std::string& User::bio() const {
    return bio_;
}

const std::string& User::joined_at() const {
    return joined_at_;
}

void User::update_bio(const std::string& new_bio) {
    bio_ = new_bio;
}

void User::follow_user(int followed_user_id) {
    if (!follows(followed_user_id)) {
        followed_user_ids_.push_back(followed_user_id);
    }
}

bool User::unfollow_user(int followed_user_id) {
    const auto iterator = std::find(followed_user_ids_.begin(), followed_user_ids_.end(), followed_user_id);
    if (iterator == followed_user_ids_.end()) {
        return false;
    }

    followed_user_ids_.erase(iterator);
    return true;
}

void User::join_community(int community_id) {
    if (!belongs_to(community_id)) {
        joined_community_ids_.push_back(community_id);
    }
}

bool User::leave_community(int community_id) {
    const auto iterator = std::find(joined_community_ids_.begin(), joined_community_ids_.end(), community_id);
    if (iterator == joined_community_ids_.end()) {
        return false;
    }

    joined_community_ids_.erase(iterator);
    return true;
}

bool User::follows(int followed_user_id) const {
    return std::find(followed_user_ids_.begin(), followed_user_ids_.end(), followed_user_id) !=
           followed_user_ids_.end();
}

bool User::belongs_to(int community_id) const {
    return std::find(joined_community_ids_.begin(), joined_community_ids_.end(), community_id) !=
           joined_community_ids_.end();
}

const std::vector<int>& User::followed_user_ids() const {
    return followed_user_ids_;
}

const std::vector<int>& User::joined_community_ids() const {
    return joined_community_ids_;
}

}
