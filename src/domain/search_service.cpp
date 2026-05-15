#include "domain/search_service.hpp"

#include <algorithm>
#include <cctype>

namespace edu_social::domain {

namespace {

std::string normalize(std::string value) {
    std::transform(value.begin(), value.end(), value.begin(), [](unsigned char character) {
        return static_cast<char>(std::tolower(character));
    });
    return value;
}

bool contains_ignore_case(const std::string& text, const std::string& query) {
    return normalize(text).find(normalize(query)) != std::string::npos;
}

}

std::vector<Community> SearchService::search_communities_by_name(
    const std::vector<Community>& communities,
    const std::string& query) const {
    std::vector<Community> matches;
    for (const Community& community : communities) {
        if (contains_ignore_case(community.name(), query)) {
            matches.push_back(community);
        }
    }
    return matches;
}

std::vector<Post> SearchService::search_posts_by_keyword(const std::vector<Post>& posts, const std::string& query)
    const {
    std::vector<Post> matches;
    for (const Post& post : posts) {
        if (contains_ignore_case(post.title(), query) || contains_ignore_case(post.body(), query)) {
            matches.push_back(post);
        }
    }
    return matches;
}

std::vector<Post> SearchService::filter_posts_by_author(const std::vector<Post>& posts, int author_id) const {
    std::vector<Post> matches;
    for (const Post& post : posts) {
        if (post.author_id() == author_id) {
            matches.push_back(post);
        }
    }
    return matches;
}

}
