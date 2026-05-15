# CRC Cards

## Content

**Responsabilidades**
- Manter id, autor, corpo e timestamps.
- Manter contagem de curtidas.
- Permitir edicao do corpo.
- Expor um resumo textual.
- Informar o tipo concreto em tempo de execucao.

**Colaboracoes**
- Post
- Comment

## Post

**Responsabilidades**
- Representar uma publicacao dentro de uma comunidade.
- Herdar o comportamento comum de Content.
- Manter o titulo do post.
- Manter o identificador da comunidade.
- Compor a colecao de comentarios.
- Adicionar e remover comentarios.
- Expor resumo para feed e busca.

**Colaboracoes**
- Content
- Comment
- Community

## Comment

**Responsabilidades**
- Representar uma resposta vinculada a um post.
- Herdar o comportamento comum de Content.
- Manter o identificador do post pai.
- Expor resumo textual com contexto do post.
- Participar da composicao do Post.

**Colaboracoes**
- Content
- Post

## Community

**Responsabilidades**
- Representar o espaco academico central da plataforma.
- Manter owner, nome e descricao.
- Compor membros da comunidade.
- Compor posts da comunidade.
- Permitir entrada e saida de membros.
- Publicar e remover posts.
- Expor posts como PostSource.

**Colaboracoes**
- User
- Post
- PostSource

## Feed

**Responsabilidades**
- Agregar posts de multiplas fontes.
- Registrar as fontes ja importadas.
- Expor posts agregados como PostSource.
- Limpar e reconstruir a timeline.
- Servir como visao consolidada para o usuario.

**Colaboracoes**
- Post
- PostSource
- Community

## User

**Responsabilidades**
- Representar a conta principal do usuario.
- Manter username, nome, email e bio.
- Manter comunidades das quais participa.
- Manter usuarios seguidos.
- Atualizar bio.
- Entrar e sair de comunidades.
- Seguir e deixar de seguir usuarios.

**Colaboracoes**
- Community
- Feed
- Post

## SearchService

**Responsabilidades**
- Buscar comunidades por nome.
- Buscar posts por palavra-chave.
- Filtrar posts por autor.
- Operar sobre agregados sem possuir estado proprio.
- Reforcar a separacao entre entidade e servico.

**Colaboracoes**
- Community
- Post
