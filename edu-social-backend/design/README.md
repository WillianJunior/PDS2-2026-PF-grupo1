# Design do Sistema

Este documento registra a organização técnica planejada para o backend da rede social educacional.

## Visão geral

O sistema é uma API HTTP em C++17 para uma rede social educacional. A aplicação usa Crow para expor endpoints, SQLite para persistência local e CMake para configurar a compilação.

Funcionalidades previstas para o MVP:

- cadastro e autenticação de usuários
- criação e listagem de posts
- comentários em posts
- curtidas
- relações de seguir
- feed baseado nas relações entre usuários
- redefinição de senha

## Arquitetura atual

No estado atual, o projeto possui a infraestrutura mínima do backend:

- `main.cpp` cria a aplicação principal.
- `App` inicializa o banco, aplica o schema e registra endpoints.
- `SQLiteConnection` encapsula abertura, fechamento e execução SQL no SQLite.
- `MigrationRunner` lê o `database/schema.sql` e aplica o schema no banco local.
- `GET /health` valida se a aplicação subiu e se a conexão com banco foi inicializada.

Fluxo atual de inicialização:

```txt
main.cpp
  -> App::run()
    -> cria database/
    -> abre database/app.db
    -> aplica database/schema.sql
    -> registra GET /health
    -> inicia servidor na porta 18080
```

## Arquitetura planejada

Conforme as funcionalidades forem implementadas, o backend deve seguir uma organização em camadas:

```txt
routes
  -> controllers
    -> services
      -> repositories
        -> database
```

Responsabilidades:

- `routes`: registrar endpoints e métodos HTTP.
- `controllers`: interpretar requests, validar entrada e montar responses.
- `services`: concentrar regras de negócio.
- `repositories`: acessar e modificar dados no SQLite.
- `database`: manter conexão, schema e operações compartilhadas de banco.
- `models`: representar entidades do domínio.
- `dto`: representar dados de entrada e saída da API.
- `middleware`: tratar autenticação, autorização e etapas comuns da requisição.
- `utils`: guardar utilitários reutilizáveis e sem dependência de domínio.

## Modelo de dados

O schema atual foi desenhado para suportar estas entidades:

- `users`: usuários cadastrados.
- `auth_tokens`: tokens ativos ou revogados.
- `posts`: publicações dos usuários.
- `comments`: comentários vinculados a posts.
- `likes`: curtidas únicas por usuário e post.
- `follows`: relações entre seguidor e seguido.
- `password_reset_tokens`: tokens temporários para redefinição de senha.

Principais regras no banco:

- emails e usernames devem ser únicos.
- um usuário não pode seguir a si mesmo.
- um usuário só pode curtir o mesmo post uma vez.
- remoções em cascata mantêm integridade entre usuários, posts, comentários e curtidas.

## Organização de código

O projeto separa headers e implementações:

```txt
include/edu_social/
  -> headers públicos do projeto

src/
  -> implementações em C++
```

Essa separação facilita modularização, testes e crescimento do projeto sem misturar contratos públicos com detalhes de implementação.

## Build e execução

A pasta `build/` é reservada para arquivos gerados pelo CMake. Ela não deve receber código escrito manualmente.

Fluxo de build esperado:

```txt
src/ + include/ + CMakeLists.txt
  -> cmake -S . -B build
  -> cmake --build build
  -> build/bin/edu_social_backend
```

O comando principal do projeto é:

```bash
make run
```

No Windows, esse comando chama `scripts/setup.ps1`. Em Linux ou Git Bash, chama `scripts/setup.sh`.
