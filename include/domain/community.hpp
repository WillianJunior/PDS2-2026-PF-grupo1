#pragma once

#include <string>
#include <vector>

#include "domain/post.hpp"
#include "domain/post_source.hpp"

namespace edu_social::domain {

/**
 * @brief Represents the main academic space where people interact.
 *
 * Community is the center of the product model. It composes members and posts,
 * and it also acts as a PostSource to feed other parts of the system.
 *
 * Invariant: member identifiers are unique inside the community collection.
 */
class Community final : public PostSource {
public:
    /**
     * @brief Builds a community with ownership and presentation metadata.
     *
     * @param id Community identifier.
     * @param owner_id Identifier of the creator or moderator.
     * @param name Public community name.
     * @param description Short description of the community theme.
     */
    Community(int id, int owner_id, std::string name, std::string description);

    /**
     * @brief Returns the unique identifier of the community.
     *
     * @return Community identifier.
     */
    int id() const;

    /**
     * @brief Returns the identifier of the community owner.
     *
     * @return Owner identifier.
     */
    int owner_id() const;

    /**
     * @brief Returns the public name shown to users.
     *
     * @return Immutable reference to the community name.
     */
    const std::string& name() const;

    /**
     * @brief Returns the description that explains the community purpose.
     *
     * @return Immutable reference to the description.
     */
    const std::string& description() const;

    /**
     * @brief Adds a member to the community when the user is not already joined.
     *
     * @param user_id Identifier of the joining user.
     */
    void add_member(int user_id);

    /**
     * @brief Removes a member from the community when the user exists.
     *
     * @param user_id Identifier of the leaving user.
     * @return True when the member existed and was removed.
     */
    bool remove_member(int user_id);

    /**
     * @brief Verifies whether a user belongs to the community.
     *
     * @param user_id Identifier to be checked.
     * @return True when the user belongs to the community.
     */
    bool has_member(int user_id) const;

    /**
     * @brief Publishes a post inside the community-owned collection.
     *
     * The post value is stored by composition inside the community aggregate.
     *
     * @param post Post value to be copied into the composition.
     */
    void publish_post(const Post& post);

    /**
     * @brief Removes a post by identifier when it exists.
     *
     * @param post_id Identifier of the post that should be removed.
     * @return True when a post was removed.
     */
    bool remove_post(int post_id);

    /**
     * @brief Returns the member identifiers owned by the community.
     *
     * @return Immutable reference to the composed member list.
     */
    const std::vector<int>& member_ids() const;

    /**
     * @brief Returns the posts owned by the community.
     *
     * @return Immutable reference to the composed post collection.
     */
    const std::vector<Post>& posts() const;

    /**
     * @brief Returns how many members the community currently has.
     *
     * @return Number of members.
     */
    std::size_t member_count() const;

    /**
     * @brief Returns how many posts the community currently has.
     *
     * @return Number of posts.
     */
    std::size_t post_count() const;

    /**
     * @brief Returns the public source label used by polymorphic consumers.
     *
     * @return Community name.
     */
    std::string source_name() const override;

    /**
     * @brief Returns a snapshot of the posts exposed by the community.
     *
     * The return type is a copy because PostSource exposes snapshots rather
     * than mutable internal storage.
     *
     * @return Copy of the post list.
     */
    std::vector<Post> list_posts() const override;

private:
    int id_;
    int owner_id_;
    std::string name_;
    std::string description_;
    std::vector<int> member_ids_;
    std::vector<Post> posts_;
};

}
