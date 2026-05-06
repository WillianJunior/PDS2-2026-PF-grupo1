#ifndef COMMUNITY_HPP
#define COMMUNITY_HPP
#include <string>
/// Representa uma comunidade acadêmica
class Community {
public:
Community(const std::string& name);
void addMember(int userId);
void removePost(int postId);
void listPosts();
};
#endif