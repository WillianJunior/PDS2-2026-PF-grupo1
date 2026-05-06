#ifndef COMMENT_HPP
#define COMMENT_HPP
#include <string>
/// Representa um comentário em um post
class Comment {
public:
Comment(const std::string& content, int authorId, int postId);
void like();
void remove();
};
#endif