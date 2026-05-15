#include "domain/post.hpp"

#include <algorithm>
#include <sstream>
#include <utility>

namespace edu_social::domain {

Post::Post(
    int id,
    int author_id,
    int community_id,
    std::string title,
    std::string body,
    std::string created_at,
    std::string updated_at)
    : Content(id, author_id, std::move(body), std::move(created_at), std::move(updated_at)),
      community_id_(community_id),
      title_(std::move(title)) {}

int Post::community_id() const {
    return community_id_;
}

const std::string& Post::title() const {
    return title_;
}

void Post::add_comment(const Comment& comment) {
    comments_.push_back(comment);
}

bool Post::remove_comment(int comment_id) {
    const auto iterator = std::find_if(
        comments_.begin(),
        comments_.end(),
        [comment_id](const Comment& comment) { return comment.id() == comment_id; });

    if (iterator == comments_.end()) {
        return false;
    }

    comments_.erase(iterator);
    return true;
}

const std::vector<Comment>& Post::comments() const {
    return comments_;
}

std::size_t Post::comment_count() const {
    return comments_.size();
}

ContentKind Post::kind() const {
    return ContentKind::post;
}

std::string Post::summary() const {
    std::ostringstream stream;
    stream << "Post #" << id() << " in community #" << community_id_ << ": " << title_;
    return stream.str();
}

}
