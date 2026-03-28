# PDS2-2026-PF-grupo1
# edu-social-backend

Backend de uma rede social educacional estilo Twitter/X, desenvolvido em C++17 com Crow, SQLite e CMake.

## O que e este projeto

O edu-social-backend e a API de uma plataforma social focada em ambiente educacional. A proposta e permitir interacao entre usuarios por meio de publicacoes curtas, comentarios, curtidas e relacoes de seguir, com autenticacao por token e persistencia em banco local SQLite.

O projeto foi pensado para ser simples de executar em laboratorio e facil de evoluir em etapas. Por isso, ele usa stack enxuta, arquitetura em camadas e scripts de bootstrap para reduzir friccao no setup.

## Como o sistema e organizado

O backend segue separacao de responsabilidades para manter o codigo limpo e escalavel:

- routes: registra endpoints e metodo HTTP
- controllers: recebe request e monta response
- services: concentra regra de negocio
- repositories: executa operacoes de banco
- database: camada de conexao SQLite e aplicacao de schema

Fluxo esperado de uma requisicao:

1. rota recebe a chamada
2. controller valida entrada e delega
3. service aplica regra de negocio
4. repository consulta/altera dados no SQLite
5. controller retorna resposta HTTP padronizada

## Stack tecnica

- C++17 como base da aplicacao
- Crow para API HTTP
- SQLite como banco em arquivo local
- CMake para configuracao e compilacao
- FetchContent para obter dependencias no configure

Dependencias externas principais:

- Crow
- Asio (standalone)
- SQLite amalgamation

## Estrutura de pastas

```txt
edu-social-backend/
|-- CMakeLists.txt
|-- Makefile
|-- README.md
|-- scripts/
|   |-- setup.ps1
|   |-- setup.sh
|   |-- run.ps1
|   |-- run.sh
|   |-- reset_db.ps1
|   `-- reset_db.sh
|-- database/
|   |-- schema.sql
|   `-- app.db
|-- src/
|   |-- main.cpp
|   |-- app/
|   |-- config/
|   |-- controllers/
|   |-- database/
|   |-- dto/
|   |-- middleware/
|   |-- models/
|   |-- repositories/
|   |-- routes/
|   |-- services/
|   `-- utils/
|-- tests/
`-- third_party/
```

## Modelo de dados do MVP

O schema ja foi desenhado para suportar as funcionalidades principais da rede social. Tabelas previstas:

- users
- auth_tokens
- posts
- comments
- likes
- follows
- password_reset_tokens

Relacionamentos e constraints no schema garantem integridade entre usuario, post, comentario, like e follow.

## Como executar o projeto

### Pre-requisitos

Windows:

- CMake no PATH
- compilador C/C++ com suporte a C++17
- PowerShell
- opcional: Ninja
- opcional: GNU Make (para usar make run)

Linux ou Git Bash:

- CMake
- g++ ou clang++ com suporte a C++17
- bash

### Comandos de bootstrap e execucao

Opcao 1 (atalho padrao):

```bash
make run
```

Opcao 2 (Windows PowerShell):

```powershell
./scripts/setup.ps1
```

Opcao 3 (Linux/Git Bash):

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

## Endpoint de validacao

Endpoint de health check:

- GET /health

Resposta esperada:

```json
{
  "status": "ok",
  "database": "connected"
}
```

## Roadmap de implementacao

### Fase 1 - Auth e Users

- cadastro de usuario
- login com token persistido
- logout com revogacao de token
- endpoint de perfil autenticado

### Fase 2 - Posts

- criar post
- listar posts
- deletar post com regra de ownership

### Fase 3 - Comments

- comentar em post
- remover comentario

### Fase 4 - Likes

- curtir post
- descurtir post

### Fase 5 - Follows

- seguir usuario
- deixar de seguir usuario

### Fase 6 - Feed

- feed personalizado por follows
- paginacao basica

### Fase 7 - Reset de senha

- solicitar token de reset
- redefinir senha com token temporario

### Fase 8 - Qualidade e fechamento

- smoke tests dos endpoints principais
- padronizacao de erros HTTP/JSON
- revisao final da documentacao da API

## Checklist de progresso

- [x] Estrutura inicial de pastas criada
- [x] CMake configurado com C++17
- [x] Crow integrado via FetchContent
- [x] Asio integrado via FetchContent
- [x] SQLite integrado via FetchContent
- [x] Binario minimo compilando
- [x] Conexao SQLite implementada
- [x] Aplicacao automatica de schema.sql
- [x] Endpoint GET /health implementado
- [x] Scripts setup/run/reset-db (Windows e Linux)
- [ ] Fase 1 - Auth e Users concluida
- [ ] Fase 2 - Posts concluida
- [ ] Fase 3 - Comments concluida
- [ ] Fase 4 - Likes concluida
- [ ] Fase 5 - Follows concluida
- [ ] Fase 6 - Feed concluida
- [ ] Fase 7 - Reset de senha concluida
- [ ] Fase 8 - Qualidade e fechamento concluida
- [ ] Documentacao final de endpoints publicada
