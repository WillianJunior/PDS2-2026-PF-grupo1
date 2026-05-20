# Rede Social Educacional (Grupo 1) - User Stories Corrigidas


## Cadastro de usuário

### Descrição
Como usuário, quero me cadastrar na plataforma para interagir com outros usuários acadêmicos.

### Critérios de aceitação
- Permitir cadastro com nome, e-mail e senha;
- Garantir unicidade do e-mail;
- Validar segurança da senha;
- Exibir mensagem de sucesso ou erro.



## Personalizar perfil

### Descrição
Como usuário, quero personalizar meu perfil com informações acadêmicas para me apresentar melhor.

### Critérios de aceitação
- Permitir informar curso, instituição e período;
- Exigir senha para alterar dados sensíveis;
- Permitir exclusão da própria conta;
- Remover posts e comentários ao deletar conta.



## Publicar conteúdo

### Descrição
Como aluno, quero publicar conteúdos educacionais para compartilhar conhecimento com outros usuários.

### Critérios de aceitação
- Permitir inserir texto na publicação;
- O objeto `Post` deve manter uma referência à `Comunidade` em que foi publicado;
- Permitir o autor deletar o próprio post;
- Não permitir edição do post após publicação.



## Interagir com posts

### Descrição
Como usuário, quero curtir e comentar posts para interagir com outros alunos.

### Critérios de aceitação
- Permitir curtir um post e remover a curtida;
- Permitir adicionar comentários;
- Permitir curtir comentários;
- O post deve possuir internamente uma coleção (como uma lista ou vetor) de objetos do tipo `Comentario` e de objetos do tipo `Curtida`;
- A destruição do post deve resultar na destruição de seus comentários.



## Seguir pessoas

### Descrição
Como usuário, quero seguir outros estudantes para formar uma rede acadêmica.

### Critérios de aceitação
- Permitir seguir usuários;
- Permitir deixar de seguir usuários;
- Listar seguidores e perfis seguidos.



## Buscar conteúdos e perfis

### Descrição
Como usuário, quero buscar conteúdos e perfis para encontrar informações e pessoas relevantes na rede acadêmica.

### Critérios de aceitação
- Permitir busca por palavras-chave;
- Exibir resultados em formato de lista;
- Permitir filtrar resultados por tipo (post ou perfil);
- Ordenar perfis em ordem alfabética;
- Exibir posts de comunidades das quais o usuário não participa.



## Criar comunidade

### Descrição
Como usuário, quero criar uma comunidade com um tema específico, para organizar conteúdos acadêmicos.

### Critérios de aceitação
- Permitir criar comunidades garantindo a validação de um nome único no sistema;
- O usuário criador deve ser automaticamente adicionado à lista de membros e receber a flag/permissão de `Administrador`;
- A comunidade deve inicializar uma lista vazia de membros e uma lista vazia de posts.



## Visualizar Feed da Comunidade

### Descrição
Como usuário, quero ingressar em comunidades e visualizar os conteúdos restritos àquele tema.

### Critérios de aceitação
- Permitir ingresso em comunidades existentes;
- Permitir apenas membros publicarem na comunidade;
- Exibir posts por ordem de publicação.



## Visualizar Feed Principal

### Descrição
Como usuário, quero visualizar um feed na minha página inicial com as novidades da minha rede.

### Critérios de aceitação
- Esta visualização deve mostrar os últimos posts feitos nas comunidades que o usuário participa.