#pragma once

#include <string>
#include <vector>

#include "domain/community.hpp"
#include "domain/post.hpp"

namespace edu_social::domain {

/**
 * @brief Encapsulates read-only search use cases over domain aggregates.
 *
 * SearchService is modeled as a service because it orchestrates queries over
 * multiple entities without owning persistent state.
 *
 * The service does not mutate the provided aggregates. It only produces
 * filtered projections for search-oriented use cases.
 */
class SearchService final {
public:
    /**
     * @brief Filters communities whose name contains the provided term.
     *
     * @param communities Candidate communities.
     * @param query Search term.
     * @return Communities whose names match the term.
     */
    std::vector<Community> search_communities_by_name(
        const std::vector<Community>& communities,
        const std::string& query) const;

    /**
     * @brief Filters posts whose title or body contains the provided term.
     *
     * @param posts Candidate posts.
     * @param query Search term.
     * @return Posts whose title or body match the term.
     */
    std::vector<Post> search_posts_by_keyword(const std::vector<Post>& posts, const std::string& query) const;

    /**
     * @brief Filters posts created by a specific author.
     *
     * @param posts Candidate posts.
     * @param author_id Identifier of the author.
     * @return Posts created by the selected author.
     */
    std::vector<Post> filter_posts_by_author(const std::vector<Post>& posts, int author_id) const;
};

}
