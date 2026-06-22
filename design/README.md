# Design do Sistema - Edu Social

## Visão geral

O projeto modela uma rede social educacional centrada em comunidades. A comunidade é o espaço principal de interação: usuários entram em comunidades, publicam posts, respondem com comentários e consomem o feed consolidado das fontes que acompanham. A aplicação funciona por meio de uma interface em terminal, permitindo que os usuários realizem operações semelhantes às encontradas em redes sociais tradicionais, porém voltadas para o contexto educacional.

Além das funcionalidades sociais, o sistema implementa mecanismos de persistência de dados utilizando arquivos CSV, permitindo que informações sejam armazenadas e recuperadas entre diferentes execuções da aplicação. O objetivo desta modelagem é deixar a orientação a objetos visível no código e fácil de defender em apresentação, especialmente nos pontos de herança, composição e polimorfismo.

## Fluxo principal do produto

1. Um usuário cria ou entra em uma comunidade;
2. A comunidade passa a compor os membros cadastrados;
3. Um membro publica um post dentro da comunidade;
4. O post passa a compor seus comentários;
5. O feed agrega posts vindos de uma ou mais comunidades;
6. O serviço de busca percorre comunidades e posts sem se tornar dono deles;

## Mapa das classes principais

- `Armazenamento`: mantém coleção de objetos que serão utilizados. Central de dados;
- `Busca`: responsável pelas operações de pesquisa (de usuários, comunidades e posts);
- `Comentário`: resposta vinculada a um post;
- `Comunidade`: representa grupos temáticos dentro da plataforma;
- `Console Utils`: faz a limpeza da tela;
- `Feed`: responsável pela organização e exibição das publicações;
- `Gerenciador CSV`: responsável pela manutenção dos dados;
- `Menus`: responsável pela interação com o usuário;
- `Perfil`: representa as informações públicas de um usuário;
- `Post`: publicação principal da comunidade;
- `Usuário`: conta principal do participante da rede.

## Herança

O projeto usa uma hierarquia explicita de conteudo:

- Todas as classes herdam de `Armazenamento`;
- `Gerenciador CSV` herda de `Comunidade`, `Usuário`, `Perfil`, `Post` e `Comentário`;
- `Usuário`, `Perfil` e `Post` herdam de `Comunidade`;

## Composição

O projeto usa composição em dois pontos centrais:

- `Usuário` 1:1 `Perfil`.
- `Comentário` compõe de `Post` e `Perfil`;

## Polimorfismo

O projeto demonstra polimorfismo em dois eixos:

- 

## Relação entre modelagem e implementação

- As User Stories estao em [user_stories.md](./user_stories.md);
- Os CRCs estao em [crc_cards.md](./crc_cards.md);
- Os contratos das classes estao em `include/domain/`;
- O Diagrama UML do projeto está em `Diagrama_UML.png`;
- A API planejada está documentada no `README.md`.

