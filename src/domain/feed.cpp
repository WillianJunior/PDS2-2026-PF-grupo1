#include "domain/feed.hpp"

#include <utility>

namespace edu_social::domain {

Feed::Feed(int owner_id, std::string title) : owner_id_(owner_id), title_(std::move(title)) {}

int Feed::owner_id() const {
    return owner_id_;
}

const std::vector<std::string>& Feed::source_labels() const {
    return source_labels_;
}

void Feed::ingest(const PostSource& source) {
    source_labels_.push_back(source.source_name());
    const std::vector<Post> source_posts = source.list_posts();
    timeline_.insert(timeline_.end(), source_posts.begin(), source_posts.end());
}

void Feed::clear() {
    source_labels_.clear();
    timeline_.clear();
}

std::size_t Feed::post_count() const {
    return timeline_.size();
}

std::string Feed::source_name() const {
    return title_;
}

std::vector<Post> Feed::list_posts() const {
    return timeline_;
}

}
