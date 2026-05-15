#pragma once

#include <string>

#include "domain/content.hpp"

namespace edu_social::domain {

/**
 * @brief Represents a reply attached to a post.
 *
 * Comment specializes Content by binding a publishable item to a parent post.
 * It reuses the common behavior exposed by the base class and adds the
 * composition link required by Post.
 *
 * Invariant: a comment always references exactly one parent post.
 */
class Comment final : public Content {
public:
    /**
     * @brief Builds a comment associated with a post.
     *
     * @param id Comment identifier.
     * @param author_id Author identifier.
     * @param post_id Parent post identifier.
     * @param body Comment body.
     * @param created_at Creation timestamp.
     * @param updated_at Last update timestamp.
     */
    Comment(
        int id,
        int author_id,
        int post_id,
        std::string body,
        std::string created_at,
        std::string updated_at);

    /**
     * @brief Returns the identifier of the parent post.
     *
     * @return Parent post identifier.
     */
    int post_id() const;

    /**
     * @brief Reports the runtime subtype of the content hierarchy.
     *
     * @return ContentKind::comment.
     */
    ContentKind kind() const override;

    /**
     * @brief Produces a compact textual representation of the comment.
     *
     * The summary is intended for feed views, search results and debug output.
     *
     * @return Summary string containing its context.
     */
    std::string summary() const override;

private:
    int post_id_;
};

}
