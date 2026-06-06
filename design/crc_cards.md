## Usuário

| Responsabilidades                                            | Colaboradores                                                |
| :----------------------------------------------------------- | :----------------------------------------------------------- |
| - Armazenar credenciais de acesso (e-mail, senha)<br>- Adicionar ou remover seguidores da lista interna<br>- Seguir outros usuários<br>- Adicionar ou remover usuários da lista de seguidos<br>\- Vincular-ao perfil | - Sistema<br>- Perfil<br>- Post<br>- Comentário<br>- Comunidade<br>- Curtida |

## Perfil

| Responsabilidades                                            | Colaboradores |
| :----------------------------------------------------------- | :------------ |
| - Armazenar informações de exibição pública (nome, bio)<br>- Armazenar informações acadêmicas (curso, instituição e período)<br>- Atualizar os próprios dados de exibição | - Usuário     |

## Post

| Responsabilidades                                            | Colaboradores                                          |
| :----------------------------------------------------------- | :----------------------------------------------------- |
| - Armazenar conteúdo textual<br>- Associar publicação a uma comunidade<br>- Registrar autor do post<br>- Gerenciar comentários<br>- Registrar curtidas<br>- Permitir exclusão pelo autor<br>- Impedir edição após publicação<br>- Exibir data/hora da publicação | - Usuário<br>- Comunidade<br>- Comentário<br>- Sistema |

## Comentário

| Responsabilidades                                            | Colaboradores                    |
| :----------------------------------------------------------- | :------------------------------- |
| - Armazenar texto do comentário<br>- Registrar autor do comentário<br>- Associar comentário a um post<br>- Manter lista de curtidas | - Usuário<br>- Post<br>- Curtida |

## Comunidade

| Responsabilidades                                            | Colaboradores       |
| :----------------------------------------------------------- | :------------------ |
| - Armazenar o nome único e o tema da comunidade<br>- Manter lista de membros<br>- Manter lista de posts<br>- Definir administrador<br>- Permitir entrada de membros<br>- Validar permissão para publicar<br> | - Usuário<br>- Post |

## ServicoAutenticacao

| Responsabilidades                                            | Colaboradores         |
| :----------------------------------------------------------- | :-------------------- |
| - Validar o formato e a unicidade de e-mails durante o cadastro<br>- Validar as regras de segurança e força da senha<br>- Gerenciar o processo de login (autenticação) e logout do usuário<br> | - Usuário<br>- Perfil |

## Feed

| Responsabilidades                                            | Colaboradores                       |
| :----------------------------------------------------------- | :---------------------------------- |
| - Exibir posts das comunidades do usuário<br>- Ordenar publicações cronologicamente<br>- Agregar conteúdos relevantes | - Comunidade<br>- Post<br>- Usuário |

## Busca

| Responsabilidades                                            | Colaboradores                    |
| :----------------------------------------------------------- | :------------------------------- |
| - Buscar posts por palavras-chave<br>- Buscar perfis de usuários<br>- Filtrar resultados por tipo (comunidade/perfil)<br>- Exibir lista de resultados | - Post<br>- Sistema<br>- Usuário |