#include "domain/community.hpp"

#include <algorithm>
#include <utility>

namespace edu_social::domain {

Community::Community(int id, int owner_id, std::string name, std::string description)
    : id_(id), owner_id_(owner_id), name_(std::move(name)), description_(std::move(description)) {
    member_ids_.push_back(owner_id_);
}

int Community::id() const {
    return id_;
}

int Community::owner_id() const {
    return owner_id_;
}

const std::string& Community::name() const {
    return name_;
}

const std::string& Community::description() const {
    return description_;
}

void Community::add_member(int user_id) {
    if (!has_member(user_id)) {
        member_ids_.push_back(user_id);
    }
}

bool Community::remove_member(int user_id) {
    const auto iterator = std::find(member_ids_.begin(), member_ids_.end(), user_id);
    if (iterator == member_ids_.end()) {
        return false;
    }

    member_ids_.erase(iterator);
    return true;
}

bool Community::has_member(int user_id) const {
    return std::find(member_ids_.begin(), member_ids_.end(), user_id) != member_ids_.end();
}

void Community::publish_post(const Post& post) {
    posts_.push_back(post);
}

bool Community::remove_post(int post_id) {
    const auto iterator =
        std::find_if(posts_.begin(), posts_.end(), [post_id](const Post& post) { return post.id() == post_id; });

    if (iterator == posts_.end()) {
        return false;
    }

    posts_.erase(iterator);
    return true;
}

const std::vector<int>& Community::member_ids() const {
    return member_ids_;
}

const std::vector<Post>& Community::posts() const {
    return posts_;
}

std::size_t Community::member_count() const {
    return member_ids_.size();
}

std::size_t Community::post_count() const {
    return posts_.size();
}

std::string Community::source_name() const {
    return name_;
}

std::vector<Post> Community::list_posts() const {
    return posts_;
}

}
