#ifndef POST_HPP
#define POST_HPP
#include <string>
/// Representa uma publicação educacional
class Post {
public:
Post(const std::string& content, int authorId, int communityId);
void like();
void unlike();
void remove();
};
#endif