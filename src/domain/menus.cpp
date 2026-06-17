#include "menus.hpp"
#include <iostream>
#include <string>
#include <algorithm>

void menuVisualizarPost(Post& post, Armazenamento& db) {
    while (true) {
        std::cout << "\n////////////////Post//////////////////\n\n";
        Perfil* autor = db.getPerfil(post.getIdAutor());
        std::string nomeAutor = autor ? autor->getNome() : "Desconhecido";
        
        std::cout << "@" << nomeAutor;
        if (post.getIdComunidade() != 0) {
            Comunidade* com = db.getComunidade(post.getIdComunidade());
            if (com) std::cout << " (" << com->getNome() << ")";
        }
        std::cout << "\n" << post.getConteudo() << "\n";
        std::cout << "Curtidas: " << post.quantidadeDeCurtidas() << "\n\n";

        std::cout << "/////////////Comentarios//////////////\n\n";
        
        const auto& todosComentarios = db.getTodosComentariosMutavel();
        std::vector<Comentario> coms;

        for (const auto& c : todosComentarios) {
            if (c.getIdPost() == post.getId())
                coms.push_back(c);
        }

        if (coms.empty()) {
            std::cout << "Nenhum comentario nesta publicacao ainda.\n\n";
        } else {
            for (size_t i = 0; i < coms.size(); ++i) {
                Perfil* autorCom = db.getPerfil(coms[i].getIdAutor());
                std::string nomeCom = autorCom ? autorCom->getNome() : "Desconhecido";
                std::cout << (i + 1) << " - @" << nomeCom << "\n";
                std::cout << coms[i].getTexto() << "\n";
                std::cout << "Curtidas: " << coms[i].quantidadeDeCurtidas() << "\n\n";
            }
        }

        std::cout << "A) Curtir/Descurtir Post / B) Curtir/Descurtir Comentario / C) Comentar\n";
        std::cout << "D) Abrir Perfil / E) Abrir Comunidade / F) Voltar\n\n";
        std::cout << "Digite sua opcao desejada: ";
        std::string opcao;
        std::getline(std::cin, opcao);

        if (opcao == "F" || opcao == "f") break;
        else if (opcao == "A" || opcao == "a") {
            post.curtir(db.getIdPerfilLogado());
