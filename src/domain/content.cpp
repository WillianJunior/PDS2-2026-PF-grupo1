#include "domain/content.hpp"

#include <utility>

namespace edu_social::domain {

Content::Content(int id, int author_id, std::string body, std::string created_at, std::string updated_at)
    : id_(id),
      author_id_(author_id),
      body_(std::move(body)),
      created_at_(std::move(created_at)),
      updated_at_(std::move(updated_at)) {}

int Content::id() const {
    return id_;
}

int Content::author_id() const {
    return author_id_;
}

const std::string& Content::body() const {
    return body_;
}

const std::string& Content::created_at() const {
    return created_at_;
}

const std::string& Content::updated_at() const {
    return updated_at_;
}

int Content::like_count() const {
    return like_count_;
}

void Content::edit_body(const std::string& new_body, const std::string& updated_at) {
    body_ = new_body;
    updated_at_ = updated_at;
}

void Content::register_like() {
    ++like_count_;
}

void Content::remove_like() {
    if (like_count_ > 0) {
        --like_count_;
    }
}

}
