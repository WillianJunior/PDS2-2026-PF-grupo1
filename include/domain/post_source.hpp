#pragma once

#include <string>
#include <vector>

namespace edu_social::domain {

class Post;

/**
 * @brief Defines a polymorphic source capable of listing posts.
 *
 * Community and Feed implement this interface so the project can demonstrate
 * polymorphism beyond the content hierarchy.
 *
 * The contract is intentionally small: consumers only need a label and a post
 * snapshot to aggregate or present content.
 */
class PostSource {
public:
    virtual ~PostSource() = default;

    /**
     * @brief Returns the label used to identify the source in the interface.
     *
     * @return Human-readable source label.
     */
    virtual std::string source_name() const = 0;

    /**
     * @brief Returns the current post snapshot exposed by the source.
     *
     * @return Copy of the posts made available by the source.
     */
    virtual std::vector<Post> list_posts() const = 0;
};

}
