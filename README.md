# Edu Social

Rede social educacional desenvolvida em **C++17**, com interface em **terminal**, persistência em **arquivos CSV**, build com **CMake** e automação via **Makefile**.

## Integrantes

Os integrantes do grupo são identificados pelos arquivos de matrícula na raiz do repositório:

- `2025019518`
- `2025019704`
- `2025019712`
- `2025075086`
- `2025116670`

## Descrição do problema

O sistema permite comunicação e colaboração acadêmica em um espaço social organizado por **comunidades**. Usuários podem:

- criar conta e fazer login;
- personalizar o perfil acadêmico;
- ingressar em comunidades e publicar posts nelas;
- publicar no feed global;
- curtir e comentar publicações;
- buscar perfis, posts e comunidades;
- manter os dados entre execuções via arquivos CSV.

A modelagem orientada a objetos está concentrada no domínio (`include/domain/`, `src/domain/`), com separação entre entidades, persistência, busca, feed e menus interativos.

## Estrutura do repositório

```txt
.
|-- README.md
|-- CMakeLists.txt
|-- Makefile
|-- 2025019518.txt ...          # arquivos de matrícula dos integrantes
|-- build/                        # artefatos de compilação (gerado)
|-- data/                         # persistência em CSV
|   |-- usuarios.csv
|   |-- perfis.csv
|   |-- comunidades.csv
|   |-- posts.csv
|   `-- comentarios.csv
|-- design/
|   |-- README.md                 # visão de design do sistema
|   |-- user_stories.md
|   |-- crc_cards.md
|   |-- Doxyfile
|   `-- notas-C7.md
|-- include/domain/               # contratos das classes (.hpp)
|-- report/                       # relatório de cobertura (gerado)
|-- scripts/
|   |-- demo.in                   # roteiro de demonstração automática
|   |-- criar_usuario.in          # cria usuários de teste
|   |-- meu_teste.in
|   |-- alunos.json
|   |-- coverage.sh
|   `-- count_commits_alunos.cpp
|-- src/
|   |-- main.cpp
|   `-- domain/                   # implementação do domínio e da aplicação
`-- tests/
    |-- doctest/
    |-- test_main.cpp
    |-- test_usuario.cpp
    |-- test_perfil.cpp
    |-- test_post.cpp
    |-- test_comentario.cpp
    |-- test_comunidade.cpp
    |-- test_armazenamento.cpp
    |-- test_gerenciador_csv.cpp
    |-- test_busca.cpp
    |-- test_feed.cpp
    `-- test_menus.cpp
```

## Arquitetura e fluxo de execução

O programa é uma aplicação de console. Não há servidor HTTP nem banco relacional.

```txt
main.cpp
  -> (opcional) redireciona stdin a partir de um arquivo .in
  -> Aplicacao::executar()
       -> Armazenamento::carregarDados()   # lê data/*.csv
       -> loop de menus (tela inicial ou menu principal)
       -> Armazenamento::salvarDados()     # grava data/*.csv a cada ciclo
```

### Camadas principais

| Componente | Responsabilidade |
|------------|------------------|
| `Aplicacao` | Orquestra login, cadastro e menu principal |
| `Menus` | Telas interativas (perfil, comunidade, post, listas) |
| `Armazenamento` | Banco em memória, sessão do usuário logado, regras de criação |
| `GerenciadorCSV` | Leitura e escrita dos arquivos em `data/` |
| `Feed` | Exibição e navegação do feed |
| `Busca` | Pesquisa por palavra-chave em perfis, posts e comunidades |
| `ConsoleUtils` | Utilitários de interface (limpar tela) |

## Classes do domínio

| Classe | Papel |
|--------|-------|
| `Usuario` | Conta (email, senha, nome de usuário) |
| `Perfil` | Dados públicos e acadêmicos; comunidades do usuário |
| `Administrador` | Especialização de `Perfil` com permissão de gestão |
| `Comunidade` | Grupo temático com administrador e membros |
| `Post` | Publicação textual (feed global ou comunidade) |
| `Comentario` | Resposta vinculada a um post |
| `Armazenamento` | Repositório central em memória |
| `GerenciadorCSV` | Persistência em CSV |
| `Busca` | Serviço de pesquisa |
| `Feed` | Visualização do feed |
| `Menus` | Interface textual |
| `Aplicacao` | Controlador principal |

## Modelagem orientada a objetos

### Herança

- `Administrador : public Perfil`
- `Perfil` expõe `virtual bool podeGerenciarComunidade() const` (padrão `false`; `Administrador` retorna `true`)

### Composição e associação

As relações entre entidades são modeladas principalmente por **IDs** e coleções:

- `Usuario` e `Perfil` compartilham o mesmo `id` (relação 1:1 lógica);
- `Comunidade` mantém lista de membros (`idsMembros`);
- `Perfil` mantém lista de comunidades (`idsComunidadesQueFazParte`);
- `Post` referencia autor e comunidade por ID;
- `Comentario` referencia post e autor por ID.

### Polimorfismo

O polimorfismo aparece no contrato virtual de `Perfil::podeGerenciarComunidade()`, permitindo tratar perfis comuns e administradores pela mesma interface base.

## Funcionalidades implementadas

### Tela inicial (deslogado)

1. Login
2. Criar usuário
3. Sair

### Menu principal (logado)

1. Ver feed (listar posts, criar post global, abrir post)
2. Buscar (perfil, post ou comunidade)
3. Ver comunidades (listar, entrar, criar, publicar)
4. Ver perfil (visualizar e editar dados acadêmicos)
5. Alterar credenciais (senha ou email)
6. Deslogar

### Interações em posts

- Curtir/descurtir post e comentários
- Comentar
- Abrir perfil do autor ou comunidade associada

### Validações

- Email e nome de usuário únicos no cadastro
- Senha com mínimo de 8 caracteres e pelo menos 1 dígito (na interface de cadastro)
- Email deve conter `@`
- Posts e comentários não podem ser vazios
- Apenas usuário logado cria posts e comunidades

### Modo automático (demo)

O executável aceita um arquivo de entrada como argumento:

```bash
build/bin/edu_social_backend scripts/demo.in
```

Útil para demonstrações e testes manuais sem digitar cada opção.

## Persistência (CSV)

Os dados ficam em `data/`. O diretório é criado automaticamente ao salvar.

| Arquivo | Cabeçalho |
|---------|-----------|
| `usuarios.csv` | `id,email,senha,nome` |
| `perfis.csv` | `id,nome,descricao,curso,instituicao,periodo,comunidades` |
| `comunidades.csv` | `id,nome,descricao,idAdmin,membros` |
| `posts.csv` | `id,idAutor,idComunidade,texto,curtidas` |
| `comentarios.csv` | `id,idPost,idAutor,texto,curtidas` |

Listas de inteiros (membros, comunidades, curtidas) usam `|` como separador. Vírgulas em textos são escapadas como `[VIRGULA]`.

**Importante:** execute o programa a partir da raiz do repositório para que o caminho `data/` seja resolvido corretamente.

## Como executar

### Pré-requisitos

**Windows**

- PowerShell ou terminal compatível com `make`
- CMake no `PATH`
- Compilador C++ com suporte a C++17 (Visual Studio Build Tools ou equivalente)

**Linux / Git Bash / WSL**

- `make`, `cmake`, compilador GCC ou Clang (C++17)
- `gcovr` (opcional, para cobertura)

### Comandos principais

```bash
make build          # compila o projeto
make run            # compila e executa (modo interativo)
make test           # executa a suíte de testes (doctest + ctest)
make run-demo       # roda demonstração com scripts/demo.in
make run-demo-clean # apaga CSVs, recria usuários demo e roda a demo
make clean          # remove build/
make help           # lista todos os alvos
```

### Exemplos

```bash
make build BUILD_TYPE=Release
make run-demo DEMO_INPUT=scripts/meu_teste.in
make commits alunos   # contagem de commits por integrante
```

### Binários gerados

Após o build, os executáveis ficam em `build/bin/`:

- `edu_social_backend` — aplicação principal
- `edu_social_tests` — testes unitários
- `count_commits_alunos` — utilitário de commits do grupo

## Testes

A suíte usa [doctest](tests/doctest/doctest.h) e é registrada no CTest pelo CMake.

```bash
make test
```

Cobertura de código (Linux/WSL com GCC):

```bash
make coverage
```

O relatório HTML é gerado em `report/coverage.html`. No Windows nativo, use WSL para `make coverage`.

## Documentação

- User Stories: [design/user_stories.md](design/user_stories.md)
- Cartões CRC: [design/crc_cards.md](design/crc_cards.md)
- Visão de design: [design/README.md](design/README.md)
- Contratos Doxygen: `include/domain/*.hpp`

Gerar documentação HTML:

```bash
make docs
```

(Requer `doxygen` instalado; configuração em `design/Doxyfile`.)

## Relação entre design e código

| Artefato | Local |
|----------|-------|
| Requisitos funcionais | `design/user_stories.md` |
| Responsabilidades das classes | `design/crc_cards.md` |
| Headers do domínio | `include/domain/` |
| Implementação | `src/domain/` |
| Dados persistidos | `data/*.csv` |
| Testes automatizados | `tests/test_*.cpp` |

## Status do projeto

### Implementado

- [x] Cadastro, login e logout
- [x] Edição de perfil acadêmico
- [x] Feed global e posts em comunidades
- [x] Comentários e curtidas
- [x] Criação e participação em comunidades
- [x] Busca por perfil, post e comunidade
- [x] Persistência em CSV
- [x] Testes unitários com doctest
- [x] Scripts de demonstração automática
- [x] Makefile com build, run, test e coverage

### Pendente / parcial

- [ ] Diagrama UML versionado no repositório
