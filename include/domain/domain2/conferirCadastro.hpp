#ifndef CONFERIRCADASTRO_HPP
#define CONFERIRCADASTRO_HPP
#include <string>

class ConferirCadastro {

public:

    bool emailUnico(std::string email);
    bool senhaSegura(std::string senha);
    void mensagemSucessoErro();

};

#endif