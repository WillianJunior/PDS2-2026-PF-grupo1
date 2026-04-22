# edu-social-backend

Projeto final de PDS II do grupo 1.

Backend de uma rede social educacional estilo Twitter/X, desenvolvido em C++17 com Crow, SQLite e CMake.

## O que e este projeto

O edu-social-backend e a API de uma plataforma social focada em ambiente educacional. A proposta e permitir interacao entre usuarios por meio de publicacoes curtas, comentarios, curtidas e relacoes de seguir, com autenticacao por token e persistencia em banco local SQLite.

O projeto foi pensado para ser simples de executar e facil de evoluir em etapas. Por isso, ele usa uma stack enxuta, arquitetura em camadas e scripts de bootstrap para reduzir friccao no setup.

## Estrutura atual

```txt
.
|-- README.md
|-- Makefile
|-- edu-social-backend/
|   |-- CMakeLists.txt
|   |-- Makefile
|   |-- src/
|   |   |-- main.cpp
|   |   |-- app/
|   |   |   `-- app.cpp
|   |   `-- database/
|   |       |-- migration_runner.cpp
|   |       `-- sqlite_connection.cpp
|   |-- include/
|   |   `-- edu_social/
|   |       |-- app/
|   |       |   `-- app.h
|   |       `-- database/
|   |           |-- migration_runner.h
|   |           `-- sqlite_connection.h
|   |-- tests/
|   |   `-- .gitkeep
|   |-- design/
|   |   `-- README.md
|   |-- build/
|   |   `-- .gitkeep
|   |-- database/
|   |   `-- schema.sql
|   `-- scripts/
|       |-- setup.ps1
|       |-- setup.sh
|       |-- run.ps1
|       |-- run.sh
|       |-- reset_db.ps1
|       `-- reset_db.sh
`-- 2025*.txt
```

## Papel das pastas

- `edu-social-backend/src/`: arquivos de implementacao da aplicacao.
- `edu-social-backend/include/`: headers publicos do projeto.
- `edu-social-backend/build/`: arquivos gerados pelo CMake durante configuracao e compilacao.
- `edu-social-backend/tests/`: testes automatizados do projeto.
- `edu-social-backend/design/`: documentos de arquitetura, diagramas e decisoes tecnicas.
- `edu-social-backend/database/`: schema SQL e arquivos relacionados ao banco local.
- `edu-social-backend/scripts/`: scripts de setup, execucao e reset do banco.

## Estrutura planejada

Conforme novas funcionalidades forem implementadas, o projeto deve evoluir para a seguinte organizacao modular:

```txt
edu-social-backend/src/
|-- main.cpp
|-- app/
|-- config/
|-- controllers/
|-- database/
|-- dto/
|-- middleware/
|-- models/
|-- repositories/
|-- routes/
|-- services/
`-- utils/

edu-social-backend/include/edu_social/
|-- app/
|-- config/
|-- controllers/
|-- database/
|-- dto/
|-- middleware/
|-- models/
|-- repositories/
|-- routes/
|-- services/
`-- utils/
```

As pastas futuras devem ser criadas quando houver codigo real para elas. Isso evita estruturas vazias sem responsabilidade definida.

## Como o sistema e organizado

O backend segue separacao de responsabilidades para manter o codigo limpo e escalavel:

- `routes`: registra endpoints e metodos HTTP.
- `controllers`: recebe requests, valida entrada e monta responses.
- `services`: concentra regras de negocio.
- `repositories`: executa operacoes de banco.
- `database`: gerencia conexao SQLite e aplicacao do schema.

Fluxo esperado de uma requisicao:

1. A rota recebe a chamada HTTP.
2. O controller valida a entrada e delega a acao.
3. O service aplica a regra de negocio.
4. O repository consulta ou altera dados no SQLite.
5. O controller retorna uma resposta HTTP padronizada.

## Stack tecnica

- C++17 como base da aplicacao
- Crow para API HTTP
- SQLite como banco em arquivo local
- CMake para configuracao e compilacao
- FetchContent para obter dependencias no configure

Dependencias externas principais:

- Crow
- Asio standalone
- SQLite amalgamation

## Modelo de dados do MVP

O schema atual suporta as tabelas previstas para o MVP:

- `users`
- `auth_tokens`
- `posts`
- `comments`
- `likes`
- `follows`
- `password_reset_tokens`

Relacionamentos e constraints no schema garantem integridade entre usuario, post, comentario, like e follow.

## Como executar o projeto

### Pre-requisitos

Windows:

- GNU Make para usar `make run`
- CMake no PATH
- compilador C/C++ com suporte a C++17
- PowerShell
- opcional: Ninja

Linux ou Git Bash:

- GNU Make para usar `make run`
- CMake
- g++ ou clang++ com suporte a C++17
- bash

### Bootstrap e execucao

Atalho padrao a partir da raiz do repositorio:

```bash
make run
```

Windows PowerShell, a partir de `edu-social-backend/`:

```powershell
./scripts/setup.ps1
```

Linux ou Git Bash, a partir de `edu-social-backend/`:

```bash
./scripts/setup.sh
```

Para apenas subir o servidor ja compilado:

```bash
make serve
```

Para resetar o banco local:

```bash
make reset-db
```

## Build

A pasta `edu-social-backend/build/` e preenchida automaticamente pelo CMake:

```txt
edu-social-backend/build/
|-- CMakeCache.txt
|-- CMakeFiles/
|-- _deps/
|-- compile_commands.json
`-- bin/
    `-- edu_social_backend
```

Arquivos gerados dentro de `build/` nao devem ser versionados. Apenas `build/.gitkeep` existe para manter a pasta visivel no repositorio.

## Endpoint de validacao

Health check:

- `GET /health`

Resposta esperada:

```json
{
  "status": "ok",
  "database": "connected"
}
```

## Roadmap de implementacao

- [x] Estrutura inicial de pastas criada
- [x] CMake configurado com C++17
- [x] Crow integrado via FetchContent
- [x] Asio integrado via FetchContent
- [x] SQLite integrado via FetchContent
- [x] Binario minimo compilando
- [x] Conexao SQLite implementada
- [x] Aplicacao automatica de `schema.sql`
- [x] Endpoint `GET /health` implementado
- [x] Scripts setup/run/reset-db para Windows e Linux
- [ ] Auth e Users
- [ ] Posts
- [ ] Comments
- [ ] Likes
- [ ] Follows
- [ ] Feed
- [ ] Reset de senha
- [ ] Smoke tests dos endpoints principais
- [ ] Documentacao final de endpoints
