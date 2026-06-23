# Edu Social Backend

Backend de uma rede social educacional desenvolvido em C++ com CSV, CMake e Makefile.

## Integrantes

Os integrantes do grupo são identificados pelos arquivos de matricula presentes na raiz do repositório:

- `2025019518`
- `2025019704`
- `2025019712`
- `2025075086`
- `2025116670`

## Descrição do problema

O sistema resolve o problema de falta de comunicação e colaboração acadêmica, por meio da criação de um espaço social organizado em comunidades. A ideia central é permitir que usuários entrem em comunidades cujos temas os interessem, publiquem posts, respondam com comentários, curtam conteúdos e consumam um feed consolidado dos assuntos que acompanham.

O projeto foi estruturado para que a modelagem orientada a objetos fique visível e defensável. Foram utilizadas ferramentas estratégicas como arquivos CSV de modo a tornar a experiência do usuário mais dinâmica.

## Objetivo principal

Entregar uma base de backend que apresente:

- modelagem OO clara;
- hierarquia de classes;
- composição explícita;
- polimorfismo justificável;
- contratos `.hpp` completos;
- documentacao Doxygen;
- estrutura pronta para TDD.

## Motivação

A rede social educacional foi escolhida porque permite representar agregados e colaborações reais sem forçar abstrações artificiais. Comunidades, posts, comentários, feed e busca fornecem pontos naturais para mostrar herança, composição, polimorfismo e separação de responsabilidades.

## Estrutura oficial do repositorio

```txt
.
├── 2025019518.txt
├── 2025019704.txt
├── 2025019712.txt
├── 2025075086.txt
├── 2025116670.txt
├── bin
│   ├── edusocial
│   └── run_tests
├── cmake-3.29.3-linux-x86_64.sh
├── CMakeLists.txt
├── data
├── design
│   ├── crc_cards.md
│   ├── diagramaUML.png
│   ├── Doxyfile
│   ├── notas-C7.md
│   └── user_stories.md
├── include
│   └── domain
│       ├── admin.hpp
│       ├── aplicacao.hpp
│       ├── armazenamento.hpp
│       ├── busca.hpp
│       ├── comentario.hpp
│       ├── comunidade.hpp
│       ├── console_utils.hpp
│       ├── feed.hpp
│       ├── gerenciador_csv.hpp
│       ├── menus.hpp
│       ├── perfil.hpp
│       ├── post.hpp
│       ├── restaurar_entrada_cin.hpp
│       └── usuario.hpp
├── Makefile
├── README.md
├── report
│   ├── coverage.armazenamento.cpp.36aad38bf57c3da4a46048ae6f766745.html
│   ├── coverage.armazenamento.hpp.6bfeb6631536af00d3d24676670172f8.html
│   ├── coverage.busca.cpp.ca8a20712bf1e0e2512a6994467708e8.html
│   ├── coverage.comentario.cpp.61bff116fbf623c0fe77b85baf74d8de.html
│   ├── coverage.comunidade.cpp.db54dc74d00a9467a4d38b33b9d1a6f3.html
│   ├── coverage.console_utils.cpp.049e4431eaa4a2d5f3f08616b7f94f0d.html
│   ├── coverage.css
│   ├── coverage.feed.cpp.0969b8d157a5ba498ae24327da1deaab.html
│   ├── coverage.functions.html
│   ├── coverage.gerenciador_csv.cpp.54c810f6d5bc2bc75188f6c15a35e75a.html
│   ├── coverage.html
│   ├── coverage.menus.cpp.a0baf141fe4db60fbf3cf774d75eaf0f.html
│   ├── coverage.perfil.cpp.10b5b1f7e9f1b62416e0595b06a2ce93.html
│   ├── coverage.post.cpp.c5c7acc94d8339fc4c07f3477e0d7930.html
│   └── coverage.usuario.cpp.b2326018c79f0753995ba0a75b03c7a5.html
├── scripts
│   ├── alunos.json
│   ├── count_commits_alunos.cpp
│   ├── coverage.sh
│   ├── criar_usuario.in
│   ├── demo.in
│   └── meu_teste.in
├── src
│   ├── domain
│   │   ├── admin.cpp
│   │   ├── aplicacao.cpp
│   │   ├── armazenamento.cpp
│   │   ├── busca.cpp
│   │   ├── comentario.cpp
│   │   ├── comunidade.cpp
│   │   ├── console_utils.cpp
│   │   ├── feed.cpp
│   │   ├── gerenciador_csv.cpp
│   │   ├── menus.cpp
│   │   ├── perfil.cpp
│   │   ├── post.cpp
│   │   ├── restaurar_entrada_cin.cpp
│   │   └── usuario.cpp
│   └── main.cpp
└── tests
    ├── doctest
    │   └── doctest.h
    ├── test_admin.cpp
    ├── test_aplicacao.cpp
    ├── test_armazenamento.cpp
    ├── test_busca.cpp
    ├── test_comentario.cpp
    ├── test_comunidade.cpp
    ├── test_console_utils.cpp
    ├── test_feed.cpp
    ├── test_gerenciador_csv.cpp
    ├── test_main.cpp
    ├── test_menus.cpp
    ├── test_perfil.cpp
    ├── test_post.cpp
    ├── test_restaurar_entrada_cin.cpp
    └── test_usuario.cpp
```

## Modelagem OO

### Hierarquia

Existe um caso de aplicação de herança no projeto, sendo este:

- `Admin` é um tipo de `Perfil`.

Como os administradores das comunidades são tipos específicos de pessoas que criaram perfis, possuímos um caso claro de herança.

### Composição

As relações de composição do sistema são:

- `Armazenamento` possui perfis, posts, comunidades, comentários e usuários;
- `Post` possui comentários;
- `Usuário` possui um único perfil contendo suas informações públicas, enquanto `Perfil` pertence a apenas um usuário (perfil 1:1 usuário);
- `Comunidade` possui posts;
- `Perfil` possui comunidades das quais participa;
- `Perfil` possui posts que o usuário criou durante o uso da plataforma;
- `Gerenciador CSV` possui dependência de perfis, posts, comunidades, usuários e comentários.

### Polimorfismo

O polimorfismo é utilizado por meio do método virtual:

- podeGerenciarComunidade()

A classe Perfil fornece uma implementação padrão retornando false, enquanto a classe Administrador sobrescreve esse método retornando true.

### Classes principais

- `Admin`: guarda informações sobre o administrador de determinada comunidade;
- `Aplicação`: controla o fluxo geral do programa;
- `Armazenamento`: mantém coleção de objetos que serão utilizados. Central de dados;
- `Busca`: responsável pelas operações de pesquisa (de usuários, comunidades e posts);
- `Comentário`: resposta vinculada a um post;
- `Comunidade`: representa grupos temáticos dentro da plataforma;
- `Console Utils`: faz a limpeza da tela;
- `Feed`: responsável pela organização e exibição das publicações;
- `Gerenciador CSV`: responsável pela manutenção dos dados;
- `Menus`: responsável pela interação com o usuário;
- `Perfil`: representa as informações públicas de um usuário;
- `Post`: publicação principal da comunidade;
- `Usuário`: conta principal do participante da rede.

### Relações principais

- uma comunidade pertence a um administrador;
- uma comunidade possui membros;
- um post pertence a uma comunidade;
- um comentário pertence a um post;
- uma curtida referencia um item de conteúdo;

## Como executar

### Pré-requisitos

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

Executar testes:

```powershell
.\scripts\test.ps1
```

Coverage (use WSL ou Linux):

```bash
make coverage
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
make run-demo
make run-demo-clean
make reset-db
make test
make coverage
make docs
make commits alunos
```

#### Coverage (`make coverage`)

No Linux ou WSL (GCC), gera o relatorio de cobertura com `gcovr`:

```bash
make coverage
```

O comando compila com instrumentacao, executa os testes e salva o HTML em
`report/coverage.html` (pasta `report/` na raiz do projeto). No WSL, o relatorio
abre automaticamente no navegador do Windows.

Pré-requisito:

```bash
sudo apt install gcovr
```

Opcional — copiar o relatório para outro diretório:

```bash
make coverage COPY_REPORT_TO=/caminho/desejado/report
```

> **Nota:** `make coverage` nao funciona no PowerShell com MSVC. Use WSL ou Linux.

> **Nota:** `make run` executa `setup` + `serve`. O `setup` pula a compilação automaticamente se o binário já existir em `build/bin/`. Para forçar um rebuild, delete o binário antes de rodar `make run`.

#### Conta usada na demo

| Campo | Valor |
|-------|-------|
| Email | `demo@test.com` |
| Senha | `senha12345` |
| Usuario | `demo_user` |

A senha precisa ter no mínimo 8 caracteres e pelo menos 1 dígito.

#### Arquivos em `scripts/`

| Arquivo | Descrição |
|---------|-----------|
| `scripts/demo.in` | Fluxo completo padrão da demo (comunidade `PDS II`, post, comentarios, feed, buscas, perfil, credenciais, logout) |
| `scripts/meu_teste.in` | Mesmo fluxo de `demo.in`; útil para testes locais sem alterar o script principal |
| `scripts/criar_usuario.in` | Apenas cria a conta demo (opcao 2 na tela inicial) |
| `scripts/alunos.json` | Emails dos integrantes para o contador de commits |
| `scripts/count_commits_alunos.cpp` | Programa que conta commits por aluno via `git` |

#### Comandos principais

Demo completa (reutiliza dados existentes nos CSVs):

```bash
make run-demo
```

Demo do zero (apaga CSVs na raiz e em `build/`, cria usuario e executa):

```bash
make run-demo-clean
```

Usar outro script de entrada:

```bash
make run-demo DEMO_INPUT=scripts/meu_teste.in
make run-demo-clean DEMO_INPUT=scripts/meu_teste.in
```

Rodar manualmente, sem Make:

```bash
# Windows (PowerShell), a partir da raiz do projeto
.\build\bin\edu_social_backend.exe scripts\demo.in

# Linux / Git Bash
./build/bin/edu_social_backend scripts/demo.in
```

Modo interativo (sem arquivo):

```bash
make run
```

Contagem de commits por integrante:

```bash
make commits alunos
```

#### O que a demo percorre

1. Login com a conta demo
2. Criar comunidade `PDS II`
3. Criar post, curtir e comentar na comunidade
4. Ver feed, curtir e comentar
5. Buscar perfil, post e comunidade
6. Ver perfil do usuário logado
7. Abrir menu de alterar credenciais (voltar sem alterar)
8. Deslogar e sair

#### Persistência dos dados

Os dados ficam em arquivos CSV na pasta de onde o programa é executado (geralmente a raiz do repositório):

- `usuarios.csv`
- `perfis.csv`
- `comunidades.csv`
- `posts.csv`
- `comentarios.csv`

Se a demo for executada varias vezes sem limpar, posts e comunidades se acumulam. Prefira
`make run-demo-clean` quando quiser uma saida limpa e previsivel.

#### Observações (Windows)

- Passe o arquivo como **argumento** (`edu_social_backend.exe scripts/demo.in`), nao use
  redirecionamento `< scripts/demo.in` — caminhos com espaco (ex.: `PDS II`) podem falhar com `<`.
- Se o binario estiver em uso, feche execucoes anteriores do programa antes de recompilar.

### Aviso: Smart App Control (Windows 11)

O Windows 11 pode bloquear a execucao de binarios compilados localmente via **Smart App Control**. Se isso ocorrer, desative-o em:

**Settings > Privacy & Security > Windows Security > App & Browser Control > Smart App Control > Off**

Essa configuração é por conta do usuário e não requer permissão de administrador.

Artefato gerado:

```txt
build/docs/html/index.html
```

## Doxygen

O projeto possui uma configuração real do Doxygen na raiz, em `Doxyfile`.

A documentação é gerada a partir de:

- `README.md`
- `design/user_stories.md`
- `design/crc_cards.md`
- todos os headers em `include/`

Comando de geração:

```bash
make docs
```

Saida esperada:

```txt
build/docs/html/index.html
```

## Funcionamento do Sistema

### Feed inical

Ao iniciar o programa e fazer o login com sucesso, o terminal limpa a tela (clear) e exibe o Feed Principal.
O que o usuário vê: Um cabeçalho e uma lista vertical de posts enumerados para fácil seleção.

```
////////////////////////////////////////
        EDU SOCIAL MENU PRINCIPAL    
////////////////////////////////////////
1 - Ver Feed
2 - Buscar
3 - Ver Comunidades
4 - Ver Perfil
5 - Alterar Credenciais
6 - Deslogar

Digite sua opcao desejada: 
```

#### Listar Comunidades

O terminal exibe uma tabela limpa e organizada com as comunidades disponíveis:
```
///////////////////////////////////////
            LISTA DE COMUNIDADES
///////////////////////////////////////

1 - PDS 2
Matéria de PDS 2
```
#### Visão de uma Comunidade Específica

  O terminal exibe o painel daquela disciplina específica e os posts dela:

```
///////////////////////////////////////
        COMUNIDADE: PDS 2
///////////////////////////////////////
Descricao: Matéria de PDS 2
Administrador: @maria
Membros: 1

=== POSTS RECENTES ===
-> Eu amo PDS 2

1 - Criar Post
2 - Ver Posts
3 - Voltar

Digite sua opcao desejada: 
```

### Visualização Detalhada do Post

O terminal foca inteiramente na discussão daquela postagem:

```
///////////////////////////////////////
              LISTA DE POSTS
///////////////////////////////////////

1 - @maria
Eu amo PDS 2

A) Selecionar Post / B) Voltar

Digite sua opcao desejada: 
```
