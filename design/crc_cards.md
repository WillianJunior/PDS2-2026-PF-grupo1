# CRC - Classes e Responsabilidades

## Usuário

### Responsabilidades
- Realizar cadastro
- Editar informações do perfil
- Excluir a própria conta
- Seguir outros usuários
- Deixar de seguir outros usuários
- Visualizar seguidores e seguidos
- Publicar posts
- Curtir posts e comentários
- Comentar em posts
- Buscar perfis e conteúdos

### Colaboradores
- Sistema
- Perfil
- Post
- Comentário
- Comunidade
- Curtida



## Perfil

### Responsabilidades
- Armazenar informações acadêmicas
- Mostrar curso, instituição e período
- Atualizar dados sensíveis mediante senha

### Colaboradores
- Usuário



## Post

### Responsabilidades
- Armazenar conteúdo textual
- Associar publicação a uma comunidade
- Registrar autor do post
- Gerenciar comentários e curtidas
- Permitir exclusão pelo autor
- Impedir edição após publicação
- Exibir data/hora da publicação

### Colaboradores
- Usuário
- Comunidade
- Comentário
- Curtida
- Sistema



## Comentário

### Responsabilidades
- Armazenar texto do comentário
- Registrar autor do comentário
- Associar comentário a um post
- Gerenciar curtidas em comentários

### Colaboradores
- Usuário
- Post
- Curtida



## Curtida

### Responsabilidades
- Registrar curtida em posts
- Registrar curtida em comentários
- Remover curtida

### Colaboradores
- Usuário
- Post
- Comentário



## Comunidade

### Responsabilidades
- Criar comunidade com nome único
- Manter lista de membros
- Manter lista de posts
- Definir administrador
- Permitir entrada de membros
- Validar permissão para publicar
- Exibir feed da comunidade

### Colaboradores
- Usuário
- Post



## Sistema

### Responsabilidades
- Validar unicidade de e-mails
- Validar unicidade de comunidades
- Validar segurança de senhas
- Realizar buscas por perfis e posts
- Filtrar resultados de busca
- Gerar feed principal
- Ordenar posts por ordem de publicação

### Colaboradores
- Usuário
- Comunidade
- Post



## Feed

### Responsabilidades
- Exibir posts das comunidades do usuário
- Ordenar publicações cronologicamente
- Agregar conteúdos relevantes

### Colaboradores
- Comunidade
- Post
- Usuário



## Busca

### Responsabilidades
- Buscar posts por palavras-chave
- Buscar perfis de usuários
- Filtrar resultados por tipo (comunidade/perfil)
- Exibir lista de resultados

### Colaboradores
- Post
- Sistema
- Usuário