#pragma once

#include <string>
#include <vector>

namespace edu_social::domain {

/**
 * @brief Represents an account that interacts with communities and content.
 *
 * User remains a single entity in this iteration. The project exposes
 * contextual behavior through composition instead of artificial subclasses.
 *
 * Invariant: followed user identifiers and joined community identifiers are
 * unique inside their respective collections.
 */
class User final {
public:
    /**
     * @brief Builds a user profile with the core social metadata.
     *
     * @param id User identifier.
     * @param username Public username.
     * @param full_name Display name.
     * @param email Unique email address.
     * @param bio Short profile biography.
     * @param joined_at Account creation timestamp.
     */
    User(
        int id,
        std::string username,
        std::string full_name,
        std::string email,
        std::string bio,
        std::string joined_at);

    /**
     * @brief Returns the unique identifier of the user.
     *
     * @return User identifier.
     */
    int id() const;

    /**
     * @brief Returns the public username.
     *
     * @return Immutable reference to the username.
     */
    const std::string& username() const;

    /**
     * @brief Returns the display name.
     *
     * @return Immutable reference to the full name.
     */
    const std::string& full_name() const;

    /**
     * @brief Returns the profile email.
     *
     * @return Immutable reference to the email address.
     */
    const std::string& email() const;

    /**
     * @brief Returns the biography text.
     *
     * @return Immutable reference to the profile biography.
     */
    const std::string& bio() const;

    /**
     * @brief Returns the account creation timestamp.
     *
     * @return Immutable reference to the creation timestamp.
     */
    const std::string& joined_at() const;

    /**
     * @brief Replaces the biography text.
     *
     * @param new_bio New biography text.
     */
    void update_bio(const std::string& new_bio);

    /**
     * @brief Stores the identifier of a followed user when absent.
     *
     * Duplicate relations are ignored so the internal collection remains
     * stable.
     *
     * @param followed_user_id Identifier of the followed user.
     */
    void follow_user(int followed_user_id);

    /**
     * @brief Removes the identifier of a followed user when present.
     *
     * @param followed_user_id Identifier of the followed user.
     * @return True when the relation existed and was removed.
     */
    bool unfollow_user(int followed_user_id);

    /**
     * @brief Stores the identifier of a joined community when absent.
     *
     * Duplicate memberships are ignored so the internal collection remains
     * stable.
     *
     * @param community_id Identifier of the community.
     */
    void join_community(int community_id);

    /**
     * @brief Removes the identifier of a joined community when present.
     *
     * @param community_id Identifier of the community.
     * @return True when the relation existed and was removed.
     */
    bool leave_community(int community_id);

    /**
     * @brief Checks whether the user follows another user.
     *
     * @param followed_user_id Identifier to be checked.
     * @return True when the relation exists.
     */
    bool follows(int followed_user_id) const;

    /**
     * @brief Checks whether the user belongs to a community.
     *
     * @param community_id Identifier to be checked.
     * @return True when the membership exists.
     */
    bool belongs_to(int community_id) const;

    /**
     * @brief Returns followed user identifiers.
     *
     * @return Immutable reference to followed users.
     */
    const std::vector<int>& followed_user_ids() const;

    /**
     * @brief Returns joined community identifiers.
     *
     * @return Immutable reference to joined communities.
     */
    const std::vector<int>& joined_community_ids() const;

private:
    int id_;
    std::string username_;
    std::string full_name_;
    std::string email_;
    std::string bio_;
    std::string joined_at_;
    std::vector<int> followed_user_ids_;
    std::vector<int> joined_community_ids_;
};

}
