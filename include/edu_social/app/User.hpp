#ifndef USER_HPP
#define USER_HPP
#include <string>
/// Representa um usuário da rede
class User {
public:
User(const std::string& name,
const std::string& email,
const std::string& password);
void followUser(int userId);
void unfollowUser(int userId);
void createPost(const std::string& content, int communityId);
void deleteAccount();
};
#endif