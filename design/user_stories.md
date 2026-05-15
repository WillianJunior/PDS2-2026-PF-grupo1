# User Stories

## US01 - Entrar em uma comunidade academica

**Descricao**  
Como estudante eu quero entrar em uma comunidade academica para acompanhar discussoes, materiais e avisos da disciplina.

**Criterios de aceitacao**
- O sistema deve permitir que um usuario entre em uma comunidade existente.
- O sistema deve impedir cadastro duplicado do mesmo usuario na mesma comunidade.
- O sistema deve registrar a data de entrada do usuario na comunidade.
- O sistema deve permitir consultar a lista de membros da comunidade.

## US02 - Criar uma comunidade

**Descricao**  
Como professor eu quero criar uma comunidade para centralizar postagens e interacoes de uma turma.

**Criterios de aceitacao**
- O sistema deve permitir informar nome e descricao da comunidade.
- O criador deve ser registrado como owner da comunidade.
- O nome da comunidade deve ser unico.
- A comunidade criada deve poder receber membros e posts depois.

## US03 - Publicar um post em comunidade

**Descricao**  
Como membro de comunidade eu quero publicar um post para compartilhar conteudo relevante com os demais participantes.

**Criterios de aceitacao**
- O sistema deve vincular o post a um autor e a uma comunidade.
- O sistema deve armazenar titulo, corpo e timestamps do post.
- O sistema deve permitir listar posts por comunidade.
- O sistema deve manter os comentarios do post como parte da sua composicao.

## US04 - Comentar um post

**Descricao**  
Como membro de comunidade eu quero comentar um post para responder, perguntar ou complementar a discussao.

**Criterios de aceitacao**
- O comentario deve ser associado a um post existente.
- O comentario deve armazenar autor, corpo e timestamps.
- Um post deve conseguir listar seus comentarios.
- A remocao de um post deve remover seus comentarios associados.

## US05 - Visualizar o feed consolidado

**Descricao**  
Como usuario eu quero visualizar um feed consolidado para acompanhar rapidamente o conteudo das comunidades que sigo.

**Criterios de aceitacao**
- O feed deve agregar posts vindos de uma ou mais comunidades.
- O feed deve registrar de quais fontes os posts vieram.
- O feed deve permitir listar posts agregados sem alterar as comunidades de origem.
- O feed deve ser modelado como fonte de posts para evidenciar polimorfismo.

## US06 - Buscar comunidades e posts

**Descricao**  
Como usuario eu quero buscar comunidades e posts por palavra-chave para encontrar rapidamente assuntos de interesse.

**Criterios de aceitacao**
- A busca deve localizar comunidades pelo nome.
- A busca deve localizar posts por titulo e corpo.
- A busca deve permitir filtrar posts por autor.
- A busca deve ser modelada em um servico independente do armazenamento.
