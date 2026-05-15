# Design do Sistema

## Visao geral

O projeto modela uma rede social educacional centrada em comunidades. A comunidade e o espaco principal de interacao: usuarios entram em comunidades, publicam posts, respondem com comentarios e consomem o feed consolidado das fontes que acompanham.

O objetivo desta modelagem e deixar a orientacao a objetos visivel no codigo e facil de defender em apresentacao, especialmente nos pontos de heranca, composicao e polimorfismo.

## Fluxo principal do produto

1. Um usuario cria ou entra em uma comunidade.
2. A comunidade passa a compor os membros cadastrados.
3. Um membro publica um post dentro da comunidade.
4. O post passa a compor seus comentarios.
5. O feed agrega posts vindos de uma ou mais comunidades.
6. O servico de busca percorre comunidades e posts sem se tornar dono deles.

## Mapa das classes principais

- `User`: conta principal do participante da rede.
- `Community`: agregado central do sistema.
- `Content`: abstracao base do conteudo publicavel.
- `Post`: publicacao principal da comunidade.
- `Comment`: resposta vinculada a um post.
- `Feed`: agregador personalizado de posts.
- `SearchService`: servico de busca do dominio.
- `PostSource`: interface polimorfica para qualquer classe que liste posts.

## Heranca

O projeto usa uma hierarquia explicita de conteudo:

- `Content` e a classe abstrata base.
- `Post` herda de `Content`.
- `Comment` herda de `Content`.

Essa decisao concentra comportamento comum em um unico lugar: id, autor, corpo, timestamps, curtidas e resumo textual.

## Composicao

O projeto usa composicao em dois pontos centrais:

- `Community` compoe membros e posts.
- `Post` compoe comentarios.

Essas relacoes aparecem de forma direta nos atributos das classes, o que deixa o modelo facil de enxergar e defender.

## Polimorfismo

O projeto demonstra polimorfismo em dois eixos:

- `Content` permite tratar `Post` e `Comment` por uma interface comum.
- `PostSource` permite tratar `Community` e `Feed` como fontes de listagem de posts.

Esses dois casos foram escolhidos porque representam diferencas reais de comportamento no dominio, evitando heranca artificial.

## Relacao entre modelagem e implementacao

- As User Stories estao em [user_stories.md](./user_stories.md).
- Os CRCs estao em [crc_cards.md](./crc_cards.md).
- Os contratos das classes estao em `include/domain/`.
- O schema esta em `database/schema.sql`.
- A API planejada esta documentada no `README.md`.

Os PDFs originais do checkpoint continuam no diretorio apenas como registro historico da entrega inicial.
