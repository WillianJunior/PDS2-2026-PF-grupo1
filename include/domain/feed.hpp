#pragma once

#include <string>
#include <vector>

#include "domain/post.hpp"
#include "domain/post_source.hpp"

namespace edu_social::domain {

/**
 * @brief Represents the personalized aggregation of posts shown to a user.
 *
 * Feed is another PostSource implementation. It demonstrates polymorphism by
 * consuming other sources and republishing their posts as a single timeline.
 *
 * Feed does not own communities. It only aggregates snapshots provided by
 * PostSource implementations.
 */
class Feed final : public PostSource {
public:
    /**
     * @brief Builds an empty feed for a user.
     *
     * @param owner_id Identifier of the feed owner.
     * @param title Display title of the feed.
     */
    Feed(int owner_id, std::string title);

    /**
     * @brief Returns the user that owns the feed.
     *
     * @return Feed owner identifier.
     */
    int owner_id() const;

    /**
     * @brief Returns the list of sources already aggregated by the feed.
     *
     * @return Immutable reference to the source labels.
     */
    const std::vector<std::string>& source_labels() const;

    /**
     * @brief Imports the current snapshot of a source into the feed.
     *
     * The operation records the source label and appends the posts exposed by
     * that source at the time of ingestion.
     *
     * @param source Source that provides posts.
     */
    void ingest(const PostSource& source);

    /**
     * @brief Removes every aggregated post and source label.
     */
    void clear();

    /**
     * @brief Returns the total number of posts currently aggregated.
     *
     * @return Number of posts available in the feed.
     */
    std::size_t post_count() const;

    /**
     * @brief Returns the title used to identify the feed as a source.
     *
     * @return Feed title.
     */
    std::string source_name() const override;

    /**
     * @brief Returns a snapshot of the posts aggregated by the feed.
     *
     * The returned copy allows polymorphic consumers to inspect the feed
     * without mutating its internal timeline.
     *
     * @return Copy of the timeline.
     */
    std::vector<Post> list_posts() const override;

private:
    int owner_id_;
    std::string title_;
    std::vector<std::string> source_labels_;
    std::vector<Post> timeline_;
};

}
