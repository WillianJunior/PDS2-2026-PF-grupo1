# Cartões CRC – Rede Social Educacional

## Armazenamento

### Responsabilidades

- Gerenciar os dados da aplicação em memória.
- Carregar dados dos arquivos CSV.
- Salvar dados da aplicação.
- Validar cadastro de usuários.
- Realizar autenticação de usuários.
- Controlar a sessão do usuário logado.
- Criar usuários, perfis, posts, comunidades e comentários.
- Fornecer acesso aos objetos armazenados.

### Colaboradores

- Comunidade
- Perfil
- Usuário
- Post
- Comentário
- GerenciadorCSV


## Busca

### Responsabilidades

- Buscar perfis por palavra-chave.
- Buscar comunidades por palavra-chave.
- Buscar posts por palavra-chave.
- Consolidar resultados de diferentes tipos.
- Filtrar resultados por categoria.
- Organizar resultados encontrados.
- Exibir resultados de pesquisa.

### Colaboradores

- Perfil
- Comunidade
- Armazenamento
- Post


## Comentário

### Responsabilidades

- Armazenar informações do comentário.
- Associar comentário a um post.
- Associar comentário a um autor.
- Gerenciar curtidas do comentário.
- Registrar usuários que curtiram o comentário.
- Disponibilizar dados do comentário para consulta.

### Colaboradores

- Perfil
- Post


## Comunidade

### Responsabilidades

- Armazenar informações da comunidade.
- Gerenciar membros da comunidade.
- Permitir entrada de novos membros.
- Permitir saída de membros.
- Verificar permissões de publicação.
- Manter referência ao administrador.
- Buscar posts da comunidade.
- Disponibilizar informações da comunidade.

### Colaboradores

- Perfil
- Post
- Armazenamento


## Feed

### Responsabilidades

- Exibir publicações da rede social.
- Organizar posts para visualização.
- Permitir seleção de publicações.
- Encaminhar ações sobre posts.
- Exibir informações dos autores.
- Exibir informações das comunidades associadas.
- Navegar entre conteúdos da plataforma.

### Colaboradores

- Post
- Perfil
- Comunidade
- Menus
- Armazenamento


## GerenciadorCSV

### Responsabilidades

- Ler arquivos CSV.
- Escrever arquivos CSV.
- Converter registros CSV em objetos do sistema.
- Converter objetos em registros CSV.
- Manipular listas de inteiros serializadas.
- Persistir usuários.
- Persistir perfis.
- Persistir comunidades, posts e comentários.

### Colaboradores

- Armazenamento
- Usuário
- Perfil
- Comunidade
- Post
- Comentário


## Menus

### Responsabilidades

- Exibir menus da aplicação.
- Receber entradas do usuário.
- Validar opções informadas.
- Controlar a navegação entre telas.
- Exibir perfis.
- Exibir comunidades.
- Exibir posts e comentários.
- Permitir interações sociais (curtir e comentar).
- Permitir edição de perfil.

### Colaboradores

- Armazenamento
- Perfil
- Comunidade
- Post
- Comentário
- Feed
- Busca


## Perfil

### Responsabilidades

- Armazenar dados públicos do usuário.
- Gerenciar informações acadêmicas.
- Gerenciar biografia do usuário.
- Gerenciar comunidades das quais participa.
- Permitir atualização das informações do perfil.
- Disponibilizar dados do perfil.

### Colaboradores

- Usuário
- Comunidade
- Post
- Menus


## Post

### Responsabilidades

- Armazenar o conteúdo da publicação.
- Associar publicação ao autor.
- Associar publicação a uma comunidade.
- Gerenciar curtidas da publicação.
- Registrar usuários que curtiram o post.
- Disponibilizar informações da publicação.
- Permitir interação por comentários.

### Colaboradores

- Perfil
- Comunidade
- Comentário
- Feed


## Usuário

### Responsabilidades

- Armazenar credenciais de acesso.
- Armazenar informações básicas do usuário.
- Validar login.
- Disponibilizar dados de autenticação.
- Representar a conta associada a um perfil.

### Colaboradores

- Armazenamento
- Perfil