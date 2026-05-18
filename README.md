# Edu Social Backend

Backend de uma rede social educacional desenvolvido em C++17 com Crow, SQLite, CMake e Makefile.

## Integrantes

Os integrantes do grupo sao identificados pelos arquivos de matricula presentes na raiz do repositorio:

- `2025019518`
- `2025019704`
- `2025019712`
- `2025075086`
- `2025116670`

## Descricao do problema

O sistema resolve o problema de comunicacao e colaboracao academica em um espaco social organizado por comunidades. A ideia central e permitir que usuarios entrem em comunidades, publiquem posts, respondam com comentarios, curtam conteudos e consumam um feed consolidado dos assuntos que acompanham.

O projeto foi estruturado para que a modelagem orientada a objetos fique visivel e defensavel. A arquitetura, o dominio, o schema do banco e a API contam a mesma historia do sistema.

## Objetivo principal

Entregar uma base de backend que apresente:

- modelagem OO clara
- hierarquia real de classes
- composicao explicita
- polimorfismo justificavel
- contratos `.hpp` completos
- documentacao Doxygen inicial
- schema coerente com o dominio
- API documentada e chamavel
- estrutura pronta para TDD

## Motivacao

A rede social educacional foi escolhida porque permite representar agregados e colaboracoes reais sem forcar abstracoes artificiais. Comunidades, posts, comentarios, feed e busca fornecem pontos naturais para mostrar heranca, composicao, polimorfismo e separacao de responsabilidades.

## Estrutura oficial do repositorio

```txt
.
|-- README.md
|-- CMakeLists.txt
|-- Doxyfile
|-- Makefile
|-- build/
|-- database/
|   `-- schema.sql
|-- design/
|   |-- README.md
|   |-- user_stories.md
|   |-- crc_cards.md
|   |-- CRC_Cartoes_Rede_Social_Educacional.pdf
|   `-- User_Stories_Rede_Social_Educacional.pdf
|-- include/
|   |-- app/
|   |   `-- app.h
|   |-- database/
|   |   |-- migration_runner.h
|   |   `-- sqlite_connection.h
|   |-- domain/
|   |   |-- comment.hpp
|   |   |-- community.hpp
|   |   |-- content.hpp
|   |   |-- feed.hpp
|   |   |-- post.hpp
|   |   |-- post_source.hpp
|   |   |-- search_service.hpp
|   |   `-- user.hpp
|   `-- http/
|       |-- api_routes.h
|       |-- auth_routes.h
|       |-- community_routes.h
|       |-- feed_routes.h
|       |-- health_routes.h
|       |-- not_implemented_response.h
|       |-- post_routes.h
|       |-- search_routes.h
|       `-- user_routes.h
|-- scripts/
|   |-- setup.ps1
|   |-- setup.sh
|   |-- run.ps1
|   |-- run.sh
|   |-- reset_db.ps1
|   |-- reset_db.sh
|   |-- test.ps1
|   |-- test.sh
|   |-- docs.ps1
|   `-- docs.sh
|-- src/
|   |-- app/
|   |   `-- app.cpp
|   |-- database/
|   |   |-- migration_runner.cpp
|   |   `-- sqlite_connection.cpp
|   |-- domain/
|   |   |-- comment.cpp
|   |   |-- community.cpp
|   |   |-- content.cpp
|   |   |-- feed.cpp
|   |   |-- post.cpp
|   |   |-- search_service.cpp
|   |   `-- user.cpp
|   |-- http/
|   |   |-- api_routes.cpp
|   |   |-- auth_routes.cpp
|   |   |-- community_routes.cpp
|   |   |-- feed_routes.cpp
|   |   |-- health_routes.cpp
|   |   |-- not_implemented_response.cpp
|   |   |-- post_routes.cpp
|   |   |-- search_routes.cpp
|   |   `-- user_routes.cpp
|   `-- main.cpp
`-- tests/
    |-- test_main.cpp
    |-- comment_tests.cpp
    |-- community_tests.cpp
    |-- content_tests.cpp
    |-- feed_tests.cpp
    |-- post_tests.cpp
    |-- search_service_tests.cpp
    `-- user_tests.cpp
```

## Arquitetura final do sistema

O sistema e organizado em quatro camadas:

- `app`: bootstrap e inicializacao do processo
- `http`: rotas e adaptadores HTTP
- `domain`: entidades, agregados, abstrações e servicos do dominio
- `database`: conexao SQLite e aplicacao do schema

Fluxo arquitetural:

```txt
HTTP route
  -> controller/route adapter
    -> domain service
      -> entity / aggregate
        -> repository / persistence adapter
          -> SQLite
```

Fluxo atual de bootstrap:

```txt
main.cpp
  -> App::run()
    -> cria database/app.db
    -> aplica database/schema.sql
    -> registra /health
    -> registra a superficie completa da API
    -> sobe o servidor
```

## Modelagem OO

### Hierarquia

Existe uma hierarquia principal de conteudo:

- `Content`
- `Post : Content`
- `Comment : Content`

`Content` concentra:

- identificador
- autor
- corpo textual
- timestamps
- contador de curtidas
- comportamento comum de edicao
- contrato polimorfico de resumo

### Composicao

As relacoes de composicao do sistema sao:

- `Community` compoe membros e posts
- `Post` compoe comentarios

Essas relacoes foram escolhidas porque representam posse real no dominio.

### Polimorfismo

O sistema demonstra polimorfismo em dois pontos:

1. `Content` permite tratar `Post` e `Comment` por uma interface comum
2. `PostSource` permite tratar `Community` e `Feed` como fontes de listagem de posts

### Classes principais

- `User`: conta principal do sistema
- `Community`: agregado central da plataforma
- `Content`: abstracao base do conteudo publicavel
- `Post`: publicacao principal de uma comunidade
- `Comment`: resposta vinculada a um post
- `Feed`: agregador de posts
- `SearchService`: servico de busca do dominio
- `PostSource`: interface de fonte de posts

## Banco de dados

O schema atual reflete a arquitetura final do sistema. As tabelas definidas sao:

- `users`
- `communities`
- `community_members`
- `auth_tokens`
- `posts`
- `comments`
- `likes`
- `follows`
- `password_reset_tokens`

### Relacoes principais

- uma comunidade pertence a um owner
- uma comunidade possui membros
- um post pertence a uma comunidade
- um comentario pertence a um post
- uma curtida referencia um item de conteudo
- um usuario pode seguir outro usuario

## Como executar

### Pre-requisitos

Windows:

- PowerShell
- CMake no PATH
- compilador C/C++ com suporte a C++17
- opcionalmente Ninja
- `gcovr` para coverage
- `doxygen` para gerar a documentacao HTML

Linux ou Git Bash:

- bash
- CMake
- GCC ou Clang com suporte a C++17
- `gcovr` para coverage
- `doxygen` para gerar a documentacao HTML

### Comandos no Windows PowerShell

Configurar e compilar:

```powershell
.\scripts\setup.ps1
```

Executar o backend:

```powershell
.\scripts\run.ps1
```

Resetar o banco:

```powershell
.\scripts\reset_db.ps1
```

Executar testes e coverage:

```powershell
.\scripts\test.ps1
```

Gerar documentacao Doxygen:

```powershell
.\scripts\docs.ps1
```

### Comandos com Make

Para ambientes que possuem `make` disponivel, o projeto tambem oferece os
seguintes atalhos:

```bash
make setup
make serve
make run
make reset-db
make test
make docs
```

> **Nota:** `make run` executa `setup` + `serve`. O `setup` pula a compilacao automaticamente se o binario ja existir em `build/bin/`. Para forcar um rebuild, delete o binario antes de rodar `make run`.

### Aviso: Smart App Control (Windows 11)

O Windows 11 pode bloquear a execucao de binarios compilados localmente via **Smart App Control**. Se isso ocorrer, desative-o em:

**Settings > Privacy & Security > Windows Security > App & Browser Control > Smart App Control > Off**

Essa configuracao e por conta do usuario e nao requer permissao de administrador.

Artefato gerado:

```txt
build/docs/html/index.html
```

## Testes

O projeto esta preparado para TDD com `doctest`. Existe uma suite base para:

- `Content`
- `Post`
- `Comment`
- `Community`
- `Feed`
- `User`
- `SearchService`

## Doxygen

O projeto possui uma configuracao real do Doxygen na raiz, em `Doxyfile`.

A documentacao e gerada a partir de:

- `README.md`
- `design/README.md`
- `design/user_stories.md`
- `design/crc_cards.md`
- todos os headers em `include/`

Escopo atual da documentacao:

- classes de dominio
- contratos da camada HTTP
- classes de infraestrutura de banco
- bootstrap da aplicacao

Comando de geracao:

```bash
make docs
```

Saida esperada:

```txt
build/docs/html/index.html
```

## API do sistema

### Base URL

```txt
http://localhost:18080
```

### Header JSON padrao

```txt
Content-Type: application/json
```

### Resposta padrao de endpoint ainda nao implementado

Todos os endpoints ja registrados que ainda nao possuem regra de negocio respondem com:

```json
{
  "message": "Feature not implemented yet.",
  "status": "not_implemented",
  "method": "POST",
  "route": "/posts"
}
```

### Status de implementacao usados neste README

- `implemented`
- `available, returns 501`

---

## Endpoint: Create User

- **Metodo:** `POST`
- **Rota:** `/users`
- **Objetivo:** cadastrar um novo usuario no sistema
- **Autenticacao:** nao
- **Parametros de rota:** nenhum
- **Parametros de query:** nenhum
- **Body esperado:** sim
- **Status de implementacao:** `implemented`

### Request schema

```json
{
  "username": "user-example",
  "full_name": "User Example",
  "email": "user@example.com",
  "password": "super-secret",
  "bio": "Student profile"
}
```

> Os campos `username`, `full_name`, `email` e `password` sao obrigatorios. `bio` e opcional.

### Success response schema

```json
{
  "id": 1,
  "username": "user-example",
  "full_name": "User Example",
  "email": "user@example.com",
  "bio": "Student profile",
  "created_at": "2026-05-18T18:40:22Z"
}
```

### Error response schemas

**Campos ausentes (422):**
```json
{ "error": "Fields username, full_name, email and password are required." }
```

**Username ou email ja em uso (409):**
```json
{ "error": "Username or email already in use." }
```

**Body invalido (400):**
```json
{ "error": "Invalid JSON body." }
```

### Status codes

- `201 Created`
- `400 Bad Request`
- `409 Conflict`
- `422 Unprocessable Entity`
- `500 Internal Server Error`

### curl minimo

```bash
curl -X POST http://localhost:18080/users
```

### curl com body JSON

```bash
curl -X POST http://localhost:18080/users \
  -H "Content-Type: application/json" \
  -d "{\"username\":\"user-example\",\"full_name\":\"User Example\",\"email\":\"user@example.com\",\"password\":\"super-secret\",\"bio\":\"Student profile\"}"
```

---

## Endpoint: Health Check

- **Metodo:** `GET`
- **Rota:** `/health`
- **Objetivo:** verificar se o servidor subiu e se o banco foi inicializado
- **Autenticacao:** nao
- **Parametros de rota:** nenhum
- **Parametros de query:** nenhum
- **Body esperado:** nenhum
- **Status de implementacao:** `implemented`

### Request example

```bash
curl -X GET http://localhost:18080/health
```

### Request example with header

```bash
curl -X GET http://localhost:18080/health -H "Accept: application/json"
```

### Response schema

```json
{
  "status": "ok",
  "database": "connected",
  "service": "edu-social-backend"
}
```

### Status codes

- `200 OK`

---

## Endpoint: Register User

- **Metodo:** `POST`
- **Rota:** `/auth/register`
- **Objetivo:** cadastrar um novo usuario
- **Autenticacao:** nao
- **Parametros de rota:** nenhum
- **Parametros de query:** nenhum
- **Body esperado:** sim
- **Status de implementacao:** `available, returns 501`

### Request schema

```json
{
  "username": "user-example",
  "fullName": "User Example",
  "email": "user@example.com",
  "password": "super-secret",
  "bio": "Student profile"
}
```

### Success response schema

```json
{
  "message": "User registered successfully.",
  "user": {
    "id": 1,
    "username": "user-example",
    "fullName": "User Example",
    "email": "user@example.com",
    "bio": "Student profile",
    "joinedAt": "2026-05-14T23:00:00Z"
  }
}
```

### Error response schema

```json
{
  "message": "Validation failed.",
  "details": [
    "Email is already in use."
  ]
}
```

### Current runtime response

```json
{
  "message": "Feature not implemented yet.",
  "status": "not_implemented",
  "method": "POST",
  "route": "/auth/register"
}
```

### Status codes

- `201 Created`
- `400 Bad Request`
- `409 Conflict`
- `501 Not Implemented`

### curl minimo

```bash
curl -X POST http://localhost:18080/auth/register
```

### curl com headers

```bash
curl -X POST http://localhost:18080/auth/register \
  -H "Accept: application/json" \
  -H "Content-Type: application/json"
```

### curl com body JSON

```bash
curl -X POST http://localhost:18080/auth/register \
  -H "Accept: application/json" \
  -H "Content-Type: application/json" \
  -d "{\"username\":\"user-example\",\"fullName\":\"User Example\",\"email\":\"user@example.com\",\"password\":\"super-secret\",\"bio\":\"Student profile\"}"
```

---

## Endpoint: Login

- **Metodo:** `POST`
- **Rota:** `/auth/login`
- **Objetivo:** autenticar um usuario e devolver token
- **Autenticacao:** nao
- **Parametros de rota:** nenhum
- **Parametros de query:** nenhum
- **Body esperado:** sim
- **Status de implementacao:** `available, returns 501`

### Request schema

```json
{
  "email": "user@example.com",
  "password": "super-secret"
}
```

### Success response schema

```json
{
  "message": "Authentication succeeded.",
  "accessToken": "token-example",
  "expiresAt": "2026-05-15T23:00:00Z",
  "user": {
    "id": 1,
    "username": "user-example",
    "fullName": "User Example"
  }
}
```

### Error response schema

```json
{
  "message": "Authentication failed.",
  "details": [
    "Invalid credentials."
  ]
}
```

### Current runtime response

```json
{
  "message": "Feature not implemented yet.",
  "status": "not_implemented",
  "method": "POST",
  "route": "/auth/login"
}
```

### Status codes

- `200 OK`
- `400 Bad Request`
- `401 Unauthorized`
- `501 Not Implemented`

### curl minimo

```bash
curl -X POST http://localhost:18080/auth/login
```

### curl com headers

```bash
curl -X POST http://localhost:18080/auth/login \
  -H "Accept: application/json" \
  -H "Content-Type: application/json"
```

### curl com body JSON

```bash
curl -X POST http://localhost:18080/auth/login \
  -H "Accept: application/json" \
  -H "Content-Type: application/json" \
  -d "{\"email\":\"user@example.com\",\"password\":\"super-secret\"}"
```

---

## Endpoint: Get User Profile

- **Metodo:** `GET`
- **Rota:** `/users/{id}`
- **Objetivo:** consultar perfil resumido de um usuario
- **Autenticacao:** sim
- **Parametros de rota:** `id`
- **Parametros de query:** nenhum
- **Body esperado:** nenhum
- **Status de implementacao:** `available, returns 501`

### Success response schema

```json
{
  "id": 1,
  "username": "user-example",
  "fullName": "User Example",
  "email": "user@example.com",
  "bio": "Student profile",
  "joinedAt": "2026-05-14T23:00:00Z",
  "followedUserIds": [2, 3],
  "joinedCommunityIds": [10, 12]
}
```

### Current runtime response

```json
{
  "message": "Feature not implemented yet.",
  "status": "not_implemented",
  "method": "GET",
  "route": "/users/{id}"
}
```

### Status codes

- `200 OK`
- `401 Unauthorized`
- `404 Not Found`
- `501 Not Implemented`

### curl minimo

```bash
curl -X GET http://localhost:18080/users/1
```

### curl com headers

```bash
curl -X GET http://localhost:18080/users/1 \
  -H "Accept: application/json" \
  -H "Authorization: Bearer token-example"
```

---

## Endpoint: List Communities

- **Metodo:** `GET`
- **Rota:** `/communities`
- **Objetivo:** listar comunidades cadastradas
- **Autenticacao:** nao
- **Parametros de rota:** nenhum
- **Parametros de query:** `q`, `ownerId`
- **Body esperado:** nenhum
- **Status de implementacao:** `available, returns 501`

### Success response schema

```json
{
  "items": [
    {
      "id": 10,
      "name": "PDS II",
      "description": "Community for software design discussions",
      "ownerId": 1,
      "memberCount": 12,
      "postCount": 5
    }
  ]
}
```

### Current runtime response

```json
{
  "message": "Feature not implemented yet.",
  "status": "not_implemented",
  "method": "GET",
  "route": "/communities"
}
```

### Status codes

- `200 OK`
- `501 Not Implemented`

### curl minimo

```bash
curl -X GET http://localhost:18080/communities
```

### curl com query

```bash
curl -X GET "http://localhost:18080/communities?q=pds&ownerId=1"
```

---

## Endpoint: Create Community

- **Metodo:** `POST`
- **Rota:** `/communities`
- **Objetivo:** criar uma comunidade academica
- **Autenticacao:** sim
- **Parametros de rota:** nenhum
- **Parametros de query:** nenhum
- **Body esperado:** sim
- **Status de implementacao:** `available, returns 501`

### Request schema

```json
{
  "ownerId": 1,
  "name": "PDS II",
  "description": "Community for software design discussions"
}
```

### Success response schema

```json
{
  "message": "Community created successfully.",
  "community": {
    "id": 10,
    "ownerId": 1,
    "name": "PDS II",
    "description": "Community for software design discussions",
    "memberCount": 1,
    "postCount": 0
  }
}
```

### Current runtime response

```json
{
  "message": "Feature not implemented yet.",
  "status": "not_implemented",
  "method": "POST",
  "route": "/communities"
}
```

### Status codes

- `201 Created`
- `400 Bad Request`
- `401 Unauthorized`
- `409 Conflict`
- `501 Not Implemented`

### curl minimo

```bash
curl -X POST http://localhost:18080/communities
```

### curl com body JSON

```bash
curl -X POST http://localhost:18080/communities \
  -H "Accept: application/json" \
  -H "Authorization: Bearer token-example" \
  -H "Content-Type: application/json" \
  -d "{\"ownerId\":1,\"name\":\"PDS II\",\"description\":\"Community for software design discussions\"}"
```

---

## Endpoint: Get Community Details

- **Metodo:** `GET`
- **Rota:** `/communities/{id}`
- **Objetivo:** consultar detalhes de uma comunidade
- **Autenticacao:** nao
- **Parametros de rota:** `id`
- **Parametros de query:** nenhum
- **Body esperado:** nenhum
- **Status de implementacao:** `available, returns 501`

### Success response schema

```json
{
  "id": 10,
  "ownerId": 1,
  "name": "PDS II",
  "description": "Community for software design discussions",
  "memberCount": 12,
  "postCount": 5,
  "memberIds": [1, 2, 3]
}
```

### Current runtime response

```json
{
  "message": "Feature not implemented yet.",
  "status": "not_implemented",
  "method": "GET",
  "route": "/communities/{id}"
}
```

### Status codes

- `200 OK`
- `404 Not Found`
- `501 Not Implemented`

### curl minimo

```bash
curl -X GET http://localhost:18080/communities/10
```

---

## Endpoint: Join Community

- **Metodo:** `POST`
- **Rota:** `/communities/{id}/members`
- **Objetivo:** adicionar um usuario a uma comunidade
- **Autenticacao:** sim
- **Parametros de rota:** `id`
- **Parametros de query:** nenhum
- **Body esperado:** sim
- **Status de implementacao:** `available, returns 501`

### Request schema

```json
{
  "userId": 2,
  "roleInCommunity": "member"
}
```

### Success response schema

```json
{
  "message": "Member added successfully.",
  "membership": {
    "communityId": 10,
    "userId": 2,
    "roleInCommunity": "member"
  }
}
```

### Current runtime response

```json
{
  "message": "Feature not implemented yet.",
  "status": "not_implemented",
  "method": "POST",
  "route": "/communities/{id}/members"
}
```

### Status codes

- `201 Created`
- `400 Bad Request`
- `401 Unauthorized`
- `404 Not Found`
- `409 Conflict`
- `501 Not Implemented`

### curl minimo

```bash
curl -X POST http://localhost:18080/communities/10/members
```

### curl com body JSON

```bash
curl -X POST http://localhost:18080/communities/10/members \
  -H "Accept: application/json" \
  -H "Authorization: Bearer token-example" \
  -H "Content-Type: application/json" \
  -d "{\"userId\":2,\"roleInCommunity\":\"member\"}"
```

---

## Endpoint: Remove Community Member

- **Metodo:** `DELETE`
- **Rota:** `/communities/{id}/members/{userId}`
- **Objetivo:** remover um usuario de uma comunidade
- **Autenticacao:** sim
- **Parametros de rota:** `id`, `userId`
- **Parametros de query:** nenhum
- **Body esperado:** nenhum
- **Status de implementacao:** `available, returns 501`

### Success response schema

```json
{
  "message": "Member removed successfully."
}
```

### Current runtime response

```json
{
  "message": "Feature not implemented yet.",
  "status": "not_implemented",
  "method": "DELETE",
  "route": "/communities/{id}/members/{userId}"
}
```

### Status codes

- `200 OK`
- `401 Unauthorized`
- `404 Not Found`
- `501 Not Implemented`

### curl minimo

```bash
curl -X DELETE http://localhost:18080/communities/10/members/2
```

### curl com headers

```bash
curl -X DELETE http://localhost:18080/communities/10/members/2 \
  -H "Accept: application/json" \
  -H "Authorization: Bearer token-example"
```

---

## Endpoint: List Community Posts

- **Metodo:** `GET`
- **Rota:** `/communities/{id}/posts`
- **Objetivo:** listar posts de uma comunidade
- **Autenticacao:** nao
- **Parametros de rota:** `id`
- **Parametros de query:** `authorId`
- **Body esperado:** nenhum
- **Status de implementacao:** `available, returns 501`

### Success response schema

```json
{
  "items": [
    {
      "id": 100,
      "communityId": 10,
      "authorId": 1,
      "title": "Checkpoint review",
      "body": "We need to review the headers.",
      "likeCount": 4,
      "commentCount": 2
    }
  ]
}
```

### Current runtime response

```json
{
  "message": "Feature not implemented yet.",
  "status": "not_implemented",
  "method": "GET",
  "route": "/communities/{id}/posts"
}
```

### Status codes

- `200 OK`
- `404 Not Found`
- `501 Not Implemented`

### curl minimo

```bash
curl -X GET http://localhost:18080/communities/10/posts
```

### curl com query

```bash
curl -X GET "http://localhost:18080/communities/10/posts?authorId=1"
```

---

## Endpoint: Create Post

- **Metodo:** `POST`
- **Rota:** `/posts`
- **Objetivo:** criar um post em uma comunidade
- **Autenticacao:** sim
- **Parametros de rota:** nenhum
- **Parametros de query:** nenhum
- **Body esperado:** sim
- **Status de implementacao:** `available, returns 501`

### Request schema

```json
{
  "authorId": 1,
  "communityId": 10,
  "title": "Checkpoint review",
  "body": "We need to review the headers."
}
```

### Success response schema

```json
{
  "message": "Post created successfully.",
  "post": {
    "id": 100,
    "authorId": 1,
    "communityId": 10,
    "title": "Checkpoint review",
    "body": "We need to review the headers.",
    "likeCount": 0,
    "commentCount": 0
  }
}
```

### Current runtime response

```json
{
  "message": "Feature not implemented yet.",
  "status": "not_implemented",
  "method": "POST",
  "route": "/posts"
}
```

### Status codes

- `201 Created`
- `400 Bad Request`
- `401 Unauthorized`
- `404 Not Found`
- `501 Not Implemented`

### curl minimo

```bash
curl -X POST http://localhost:18080/posts
```

### curl com body JSON

```bash
curl -X POST http://localhost:18080/posts \
  -H "Accept: application/json" \
  -H "Authorization: Bearer token-example" \
  -H "Content-Type: application/json" \
  -d "{\"authorId\":1,\"communityId\":10,\"title\":\"Checkpoint review\",\"body\":\"We need to review the headers.\"}"
```

---

## Endpoint: Get Post Details

- **Metodo:** `GET`
- **Rota:** `/posts/{id}`
- **Objetivo:** consultar um post com seus metadados
- **Autenticacao:** nao
- **Parametros de rota:** `id`
- **Parametros de query:** nenhum
- **Body esperado:** nenhum
- **Status de implementacao:** `available, returns 501`

### Success response schema

```json
{
  "id": 100,
  "authorId": 1,
  "communityId": 10,
  "title": "Checkpoint review",
  "body": "We need to review the headers.",
  "likeCount": 4,
  "commentCount": 2,
  "comments": [
    {
      "id": 201,
      "authorId": 2,
      "postId": 100,
      "body": "I agree with the plan."
    }
  ]
}
```

### Current runtime response

```json
{
  "message": "Feature not implemented yet.",
  "status": "not_implemented",
  "method": "GET",
  "route": "/posts/{id}"
}
```

### Status codes

- `200 OK`
- `404 Not Found`
- `501 Not Implemented`

### curl minimo

```bash
curl -X GET http://localhost:18080/posts/100
```

---

## Endpoint: Create Comment

- **Metodo:** `POST`
- **Rota:** `/posts/{id}/comments`
- **Objetivo:** criar comentario em um post
- **Autenticacao:** sim
- **Parametros de rota:** `id`
- **Parametros de query:** nenhum
- **Body esperado:** sim
- **Status de implementacao:** `available, returns 501`

### Request schema

```json
{
  "authorId": 2,
  "body": "I agree with the plan."
}
```

### Success response schema

```json
{
  "message": "Comment created successfully.",
  "comment": {
    "id": 201,
    "authorId": 2,
    "postId": 100,
    "body": "I agree with the plan.",
    "likeCount": 0
  }
}
```

### Current runtime response

```json
{
  "message": "Feature not implemented yet.",
  "status": "not_implemented",
  "method": "POST",
  "route": "/posts/{id}/comments"
}
```

### Status codes

- `201 Created`
- `400 Bad Request`
- `401 Unauthorized`
- `404 Not Found`
- `501 Not Implemented`

### curl minimo

```bash
curl -X POST http://localhost:18080/posts/100/comments
```

### curl com body JSON

```bash
curl -X POST http://localhost:18080/posts/100/comments \
  -H "Accept: application/json" \
  -H "Authorization: Bearer token-example" \
  -H "Content-Type: application/json" \
  -d "{\"authorId\":2,\"body\":\"I agree with the plan.\"}"
```

---

## Endpoint: List Post Comments

- **Metodo:** `GET`
- **Rota:** `/posts/{id}/comments`
- **Objetivo:** listar comentarios de um post
- **Autenticacao:** nao
- **Parametros de rota:** `id`
- **Parametros de query:** nenhum
- **Body esperado:** nenhum
- **Status de implementacao:** `available, returns 501`

### Success response schema

```json
{
  "items": [
    {
      "id": 201,
      "authorId": 2,
      "postId": 100,
      "body": "I agree with the plan.",
      "likeCount": 0
    }
  ]
}
```

### Current runtime response

```json
{
  "message": "Feature not implemented yet.",
  "status": "not_implemented",
  "method": "GET",
  "route": "/posts/{id}/comments"
}
```

### Status codes

- `200 OK`
- `404 Not Found`
- `501 Not Implemented`

### curl minimo

```bash
curl -X GET http://localhost:18080/posts/100/comments
```

---

## Endpoint: Like Post

- **Metodo:** `POST`
- **Rota:** `/posts/{id}/likes`
- **Objetivo:** registrar curtida em um post
- **Autenticacao:** sim
- **Parametros de rota:** `id`
- **Parametros de query:** nenhum
- **Body esperado:** sim
- **Status de implementacao:** `available, returns 501`

### Request schema

```json
{
  "userId": 2
}
```

### Success response schema

```json
{
  "message": "Like registered successfully.",
  "postId": 100,
  "userId": 2
}
```

### Current runtime response

```json
{
  "message": "Feature not implemented yet.",
  "status": "not_implemented",
  "method": "POST",
  "route": "/posts/{id}/likes"
}
```

### Status codes

- `201 Created`
- `400 Bad Request`
- `401 Unauthorized`
- `404 Not Found`
- `409 Conflict`
- `501 Not Implemented`

### curl minimo

```bash
curl -X POST http://localhost:18080/posts/100/likes
```

### curl com body JSON

```bash
curl -X POST http://localhost:18080/posts/100/likes \
  -H "Accept: application/json" \
  -H "Authorization: Bearer token-example" \
  -H "Content-Type: application/json" \
  -d "{\"userId\":2}"
```

---
## Funcionamento do Sistema

### Feed inical
Ao iniciar o programa e fazer o login com sucesso, o terminal limpa a tela (clear) e exibe o Feed Principal baseado no endpoint /feed.
O que o usuário vê: Um cabeçalho e uma lista vertical de posts enumerados para fácil seleção.

Layout sugerido no terminal:


```
======================================================================
                     EDU SOCIAL - FEED                     
======================================================================
Comunidades integradas: [PDS II] [Cálculo I]

[1] TÍTULO: Tipos Abstratos de Dados
    Usuário: @aluno_de_sistemas | COMUNIDADE: PDS II
    "Pessoal, vocês poderiam me explicar o que diferencia um TADs de uma classe ?"
    👍 14 curtidas | 💬 3 comentários

[2] TÍTULO: Derivada de log(x)
    AUTOR: @aluno_de_computação | COMUNIDADE: Cálculo I
    "Alguém sabe calcular o log(x)..."
    👍 4 curtidas | 💬 1 comentário

======================================================================
[V] Ver Post (Ex: V 1) | [C] Ver Comunidades | [P] Pesquisar | [S] Sair
Digite sua opção: _
```

### Navegação por Comunidades (Listagem e Telas Internas)

Quando o usuário digita C no menu principal, o sistema limpa a tela e chama o endpoint /communities.
#### Listar Comunidades (GET /communities)

O terminal exibe uma tabela limpa e organizada com as disciplinas disponíveis:
```
======================================================================
                    COMUNIDADES ACADÊMICAS
======================================================================
ID   | Nome do Grupo          | Membros | Posts | Criador
-----+------------------------+---------+-------+---------------------
10   | PDS II                 | 12      | 5     | @professor_alex
12   | Estruturas de Dados    | 45      | 18    | @prof_ana
20   | Álgebra Linear         | 8       | 0     | @monitor_lucas

======================================================================
[E] Entrar em Comunidade (Ex: E 10) | [V] Voltar
Digite sua opção: _
```
#### Visão de uma Comunidade Específica (GET /communities/{id})

Se o usuário digitar E 10, o terminal exibe o painel daquela disciplina específica e os posts dela:

```shell
======================================================================
                     EDU SOCIAL - COMUNIDADE                 
======================================================================
COMUNIDADE: PDS II (ID: 10)
Descrição: Discução sobre a matéria de PDS II
Membros: 12 | Status: [Você é Membro]

[100] TÍTULO: Dúvida sobre polimorfismo
    AUTOR: @aluno_de_controle
    "Pesoal estou em dúvida sobre o que é polimorfismo..."
    👍 4 curtidas | 💬 2 comentários

[105] TÍTULO: Dica de exercício
    AUTOR: @professor_de_pds
    "Pessoal uma ideais de exercício aqui..."
    👍 1 curtida | 💬 0 comentários

======================================================================
[V] Ver Post (Ex: V 100) | [N] Novo Post | [P] Sair da Comunidade | [Voltar]
Digite sua opção: _
```

### Visualização Detalhada do Post

Se o usuário estiver no feed ou na comunidade e digitar `V 100` (Ver Post 100), o terminal foca inteiramente na discussão daquela pergunta

```
======================================================================
 POST #100
 Autor: @professor_de_pds
 Título: Dica de exercício
----------------------------------------------------------------======
 "Pessoal uma ideais de exercício aqui: defina oq é o princípio de Liskov"
 
 [ 👍 4 Curtidas ]
======================================================================
 COMENTÁRIOS E RESPOSTAS:
----------------------------------------------------------------------
 #201 por @aluno_de_sistemas:
 "Obrigado por compartilhar"
 
 #202 por @monitor_lucas:
 "Acho que a galera ainda está com dúvidas nisso."
======================================================================
[L] Curtir Post | [R] Responder (Comentar) | [V] Voltar
Digite sua opção: _
```



## Endpoint: Remove Post Like

- **Metodo:** `DELETE`
- **Rota:** `/posts/{id}/likes/{userId}`
- **Objetivo:** remover curtida de um post
- **Autenticacao:** sim
- **Parametros de rota:** `id`, `userId`
- **Parametros de query:** nenhum
- **Body esperado:** nenhum
- **Status de implementacao:** `available, returns 501`

### Success response schema

```json
{
  "message": "Like removed successfully."
}
```

### Current runtime response

```json
{
  "message": "Feature not implemented yet.",
  "status": "not_implemented",
  "method": "DELETE",
  "route": "/posts/{id}/likes/{userId}"
}
```

### Status codes

- `200 OK`
- `401 Unauthorized`
- `404 Not Found`
- `501 Not Implemented`

### curl minimo

```bash
curl -X DELETE http://localhost:18080/posts/100/likes/2
```

### curl com headers

```bash
curl -X DELETE http://localhost:18080/posts/100/likes/2 \
  -H "Accept: application/json" \
  -H "Authorization: Bearer token-example"
```

---

## Endpoint: Get Feed

- **Metodo:** `GET`
- **Rota:** `/feed`
- **Objetivo:** listar feed consolidado do usuario
- **Autenticacao:** sim
- **Parametros de rota:** nenhum
- **Parametros de query:** `userId`, `communityId`, `limit`
- **Body esperado:** nenhum
- **Status de implementacao:** `available, returns 501`

### Success response schema

```json
{
  "ownerId": 1,
  "title": "Main feed",
  "sourceLabels": ["PDS II", "Databases"],
  "items": [
    {
      "id": 100,
      "communityId": 10,
      "authorId": 1,
      "title": "Checkpoint review",
      "body": "We need to review the headers."
    }
  ]
}
```

### Current runtime response

```json
{
  "message": "Feature not implemented yet.",
  "status": "not_implemented",
  "method": "GET",
  "route": "/feed"
}
```

### Status codes

- `200 OK`
- `400 Bad Request`
- `401 Unauthorized`
- `501 Not Implemented`

### curl minimo

```bash
curl -X GET "http://localhost:18080/feed?userId=1"
```

### curl com query completa

```bash
curl -X GET "http://localhost:18080/feed?userId=1&communityId=10&limit=20" \
  -H "Accept: application/json" \
  -H "Authorization: Bearer token-example"
```

---

## Endpoint: Search

- **Metodo:** `GET`
- **Rota:** `/search`
- **Objetivo:** buscar comunidades e posts
- **Autenticacao:** nao
- **Parametros de rota:** nenhum
- **Parametros de query:** `q`, `type`, `authorId`
- **Body esperado:** nenhum
- **Status de implementacao:** `available, returns 501`

### Request query values for `type`

- `communities`
- `posts`
- `all`

### Success response schema

```json
{
  "query": "pds",
  "type": "all",
  "communities": [
    {
      "id": 10,
      "name": "PDS II"
    }
  ],
  "posts": [
    {
      "id": 100,
      "title": "Checkpoint review",
      "communityId": 10
    }
  ]
}
```

### Current runtime response

```json
{
  "message": "Feature not implemented yet.",
  "status": "not_implemented",
  "method": "GET",
  "route": "/search"
}
```

### Status codes

- `200 OK`
- `400 Bad Request`
- `501 Not Implemented`

### curl minimo

```bash
curl -X GET "http://localhost:18080/search?q=pds&type=all"
```

### curl com filtros

```bash
curl -X GET "http://localhost:18080/search?q=review&type=posts&authorId=1" \
  -H "Accept: application/json"
```

## Relacao entre design e codigo

- User Stories: [design/user_stories.md](./design/user_stories.md)
- CRCs: [design/crc_cards.md](./design/crc_cards.md)
- Arquitetura textual: [design/README.md](./design/README.md)
- Contratos do dominio: `include/domain/`
- Schema: `database/schema.sql`
- Rotas HTTP: `src/http/`
- Bootstrap: `src/app/app.cpp`

## Fases e status

### Estrutura e modelagem

- [x] raiz consolidada
- [x] legado removido
- [x] schema alinhado ao dominio
- [x] hierarquia `Content -> Post/Comment`
- [x] composicao `Community -> Post` e `Post -> Comment`
- [x] polimorfismo com `Content` e `PostSource`
- [x] User Stories em texto
- [x] CRCs em texto

### HTTP e documentacao

- [x] `GET /health` implementado
- [x] todos os endpoints principais registrados
- [x] endpoints nao implementados respondendo `501 Not Implemented`
- [x] README com contratos completos da API
- [x] README com `curl` para todos os endpoints
- [x] Doxygen configurado

### Build e testes

- [x] CMake reorganizado
- [x] Makefile com `setup`, `run`, `serve`, `reset-db`, `test`
- [x] suites base com `doctest`
- [x] `ctest` passando
- [ ] coverage executada com `gcovr`

### Comportamentos de negocio

- [ ] cadastro real de usuario
- [ ] login real
- [ ] criacao real de comunidade
- [ ] entrada real em comunidade
- [ ] criacao real de post
- [ ] criacao real de comentario
- [ ] curtidas reais
- [ ] feed real
- [ ] busca real

### Robustez final

- [ ] validacoes defensivas completas
- [ ] tratamento de excecoes em toda a camada HTTP
- [ ] cobertura minima exigida consolidada
- [ ] revisao final para apresentacao
