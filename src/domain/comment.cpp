#include "domain/comment.hpp"

#include <sstream>
#include <utility>

namespace edu_social::domain {

Comment::Comment(
    int id,
    int author_id,
    int post_id,
    std::string body,
    std::string created_at,
    std::string updated_at)
    : Content(id, author_id, std::move(body), std::move(created_at), std::move(updated_at)), post_id_(post_id) {}

int Comment::post_id() const {
    return post_id_;
}

ContentKind Comment::kind() const {
    return ContentKind::comment;
}

std::string Comment::summary() const {
    std::ostringstream stream;
    stream << "Comment #" << id() << " on post #" << post_id_ << " by user #" << author_id();
    return stream.str();
}

}
