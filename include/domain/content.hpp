#pragma once

#include <string>

namespace edu_social::domain {

/**
 * @brief Identifies the concrete subtype of a publishable content item.
 */
enum class ContentKind {
    /**
     * @brief A publication that belongs to a community and can own comments.
     */
    post,
    /**
     * @brief A reply attached to an existing post.
     */
    comment
};

/**
 * @brief Defines the common contract shared by every publishable item.
 *
 * Content is the root of the domain hierarchy. It centralizes the attributes
 * and behaviors that both posts and comments share, making inheritance and
 * polymorphism explicit in the project.
 *
 * Invariant: every content item has an author, a textual body, audit
 * timestamps and a non-negative like counter.
 */
class Content {
public:
    virtual ~Content() = default;

    /**
     * @brief Returns the unique identifier of the content item.
     *
     * @return Numeric identifier assigned to the content.
     */
    int id() const;

    /**
     * @brief Returns the identifier of the author.
     *
     * @return Identifier of the user who created the content.
     */
    int author_id() const;

    /**
     * @brief Returns the textual body stored by the content item.
     *
     * @return Immutable reference to the content body.
     */
    const std::string& body() const;

    /**
     * @brief Returns the creation timestamp.
     *
     * @return Immutable reference to the creation timestamp.
     */
    const std::string& created_at() const;

    /**
     * @brief Returns the last update timestamp.
     *
     * @return Immutable reference to the last update timestamp.
     */
    const std::string& updated_at() const;

    /**
     * @brief Returns the number of likes attached to the content item.
     *
     * @return Current like counter.
     */
    int like_count() const;

    /**
     * @brief Replaces the body and updates the audit timestamp.
     *
     * The operation preserves the content identity and only changes mutable
     * textual state.
     *
     * @param new_body New textual body.
     * @param updated_at Timestamp that represents the latest edition.
     */
    void edit_body(const std::string& new_body, const std::string& updated_at);

    /**
     * @brief Increments the like counter by one.
     *
     * This method models the shared like behavior for every publishable item.
     */
    void register_like();

    /**
     * @brief Decrements the like counter when it is greater than zero.
     *
     * The counter never becomes negative.
     */
    void remove_like();

    /**
     * @brief Identifies the concrete subtype at runtime.
     *
     * @return Runtime kind of the content object.
     */
    virtual ContentKind kind() const = 0;

    /**
     * @brief Produces a human-readable summary for feeds and searches.
     *
     * @return Short summary string for presentation.
     */
    virtual std::string summary() const = 0;

protected:
    /**
     * @brief Creates the shared portion of a content item.
     *
     * This constructor is protected because Content is an abstract base class.
     *
     * @param id Content identifier.
     * @param author_id Author identifier.
     * @param body Text body.
     * @param created_at Creation timestamp.
     * @param updated_at Last update timestamp.
     */
    Content(int id, int author_id, std::string body, std::string created_at, std::string updated_at);

private:
    int id_;
    int author_id_;
    std::string body_;
    std::string created_at_;
    std::string updated_at_;
    int like_count_ = 0;
};

}
