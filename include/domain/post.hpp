#pragma once

#include <string>
#include <vector>

#include "domain/comment.hpp"
#include "domain/content.hpp"

namespace edu_social::domain {

/**
 * @brief Represents a community publication that owns its comments.
 *
 * Post is a concrete Content specialization. It exposes the composition
 * relationship with Comment, making the ownership of replies visible in code.
 *
 * Invariant: comments stored by the post remain grouped under the same post
 * identifier in the aggregate.
 */
class Post final : public Content {
public:
    /**
     * @brief Builds a post published inside a community.
     *
     * @param id Post identifier.
     * @param author_id Author identifier.
     * @param community_id Target community identifier.
     * @param title Short headline of the post.
     * @param body Main textual body.
     * @param created_at Creation timestamp.
     * @param updated_at Last update timestamp.
     */
    Post(
        int id,
        int author_id,
        int community_id,
        std::string title,
        std::string body,
        std::string created_at,
        std::string updated_at);

    /**
     * @brief Returns the identifier of the community that contains the post.
     *
     * @return Community identifier.
     */
    int community_id() const;

    /**
     * @brief Returns the title of the publication.
     *
     * @return Immutable reference to the title.
     */
    const std::string& title() const;

    /**
     * @brief Adds a comment to the post-owned collection.
     *
     * The comment value is copied into the internal composition owned by the
     * post.
     *
     * @param comment Comment value to be copied into the composition.
     */
    void add_comment(const Comment& comment);

    /**
     * @brief Removes a comment by identifier when it exists.
     *
     * @param comment_id Identifier of the comment that should be removed.
     * @return True when a comment was removed, false otherwise.
     */
    bool remove_comment(int comment_id);

    /**
     * @brief Returns the comment collection owned by the post.
     *
     * @return Immutable reference to the composed comments.
     */
    const std::vector<Comment>& comments() const;

    /**
     * @brief Returns how many comments the post currently owns.
     *
     * @return Number of comments composed by the post.
     */
    std::size_t comment_count() const;

    /**
     * @brief Reports the runtime subtype of the content hierarchy.
     *
     * @return ContentKind::post.
     */
    ContentKind kind() const override;

    /**
     * @brief Produces a compact textual representation of the post.
     *
     * The summary is used by feed and search projections.
     *
     * @return Summary string containing community context.
     */
    std::string summary() const override;

private:
    int community_id_;
    std::string title_;
    std::vector<Comment> comments_;
};

}
