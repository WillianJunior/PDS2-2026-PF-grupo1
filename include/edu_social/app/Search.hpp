#ifndef SEARCH_HPP
#define SEARCH_HPP
#include <string>
/// Serviço responsável pela busca no sistema
class Search {
public:
void searchByKeyword(const std::string& keyword);
void filterByType(const std::string& type);
};
#endif