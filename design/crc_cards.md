# Cartões CRC – Rede Social Educacional

## Admin

### Responsabilidades de Conhecimento

- Todos os dados herdados de Perfil

### Responsabilidades de Realização

- Gerenciar comunidades
- Sobrescrever permissões de gerenciamento
- Validar privilégios administrativos

### Colaboradores

- Perfil
- Comunidade


## Aplicação

### Responsabilidades de Conhecimento

- Estado de execução do sistema
- Mensagens de alerta
- Instâncias principais do sistema

### Responsabilidades de Realização

- Exibir telas
- Controlar menus
- Gerenciar fluxo de login
- Gerenciar fluxo de cadastro
- Gerenciar fluxo de pesquisa
- Gerenciar visualização de perfis
- Controlar encerramento da aplicação

### Colaboradores

- Armazenamento
- Busca
- Feed


## Armazenamento

### Responsabilidades de Conhecimento

- Usuários cadastrados
- Perfis cadastrados
- Comunidades cadastradas
- Posts cadastrados
- Comentários cadastrados
- Sessão do usuário logado
- Próximos IDs disponíveis

### Responsabilidades de Realização

- Carregar dados
- Salvar dados
- Realizar login
- Realizar logout
- Criar usuários
- Criar perfis
- Criar comunidades
- Criar posts
- Criar comentários
- Recuperar entidades do sistema
- Validar unicidade de usuários

### Colaboradores

- Comunidade
- Perfil
- Usuário
- Post
- Comentário
- GerenciadorCSV
- Admin


## Busca

### Responsabilidades de Conhecimento

- Resultados da pesquisa

### Responsabilidades de Realização4

- Buscar perfis
- Buscar comunidades
- Buscar posts
- Filtrar resultados
- Exibir resultados encontrados

### Colaboradores

- Perfil
- Comunidade
- Armazenamento
- Post


## Comentário

### Responsabilidades de Conhecimento

- ID do comentário
- Autor
- Post relacionado
- Texto do comentário
- Curtidas recebidas

### Responsabilidades de Realização

- Registrar curtidas
- Remover curtidas
- Contabilizar curtidas
- Fornecer informações do comentário

### Colaboradores

- Perfil
- Post


## Comunidade

### Responsabilidades de Conhecimento

- ID da comunidade
- Nome
- Descrição
- Administrador responsável
- Lista de membros

### Responsabilidades de Realização

- Adicionar membro
- Remover membro
- Registrar entrada de usuários
- Verificar permissão de postagem
- Exibir membros

### Colaboradores

- Perfil
- Post
- Armazenamento
- Admin

## Console Utils

### Responsabilidades de Conhecimento

- Regras de interação com o terminal
- Recursos de limpeza e pausa da interface

### Responsabilidades de Realização

- Limpar a tela do terminal
- Pausar a execução aguardando interação do usuário
- Auxiliar a navegação da interface textual

### Colaborações
- Aplicação
- Feed
- Menus


## Feed

### Responsabilidade de Conhecimento

- Dados temporários de exibição do feed

### Responsabilidades de Realização

- Exibir posts
- Exibir perfis
- Exibir comunidades
- Renderizar feed principal
- Intermediar interação com publicações

### Colaboradores

- Post
- Perfil
- Comunidade
- Menus
- Armazenamento


## GerenciadorCSV

### Responsabilidades de Conhecimento

- Estrutura dos arquivos CSV
- Regras de serialização e desserialização

### Responsabilidades de Realização

- Salvar usuários
- Salvar perfis
- Salvar comunidades
- Salvar posts
- Salvar comentários
- Carregar usuários
- Carregar perfis
- Carregar comunidades
- Carregar posts
- Carregar comentários
- Converter strings e listas

### Colaboradores

- Armazenamento
- Usuário
- Perfil
- Comunidade
- Post
- Comentário


## Menus

### Responsabilidades de Conhecimento

- Estado atual de navegação do usuário
- Entidades exibidas na interface (posts, perfis e comunidades)

### Responsabilidades de Realização

- Exibir posts individuais
- Exibir listas de posts
- Exibir listas de perfis
- Exibir listas de comunidades
- Exibir perfis detalhados
- Exibir comunidades detalhadas
- Processar interações de navegação
- Encaminhar ações para o sistema de armazenamento

### Colaboradores

- Armazenamento
- Perfil
- Comunidade
- Post
- Comentário
- Feed
- Busca


## Perfil

### Responsabilidades de Conhecimento

- ID do perfil
- Nome do usuário
- Descrição/Biografia
- Curso
- Instituição
- Período acadêmico
- Comunidades das quais participa

### Responsabilidades de Realização

- Entrar em comunidade
- Sair de comunidade
- Editar informações acadêmicas
- Informar permissões básicas de comunidade

### Colaboradores

- Usuário
- Comunidade
- Post
- Menus
- Armazenamento
- Admin


## Post

### Responsabilidades de Conhecimento

- ID do post
- Autor
- Comunidade associada
- Conteúdo textual
- Usuários que curtiram

### Responsabilidades de Realização

- Receber curtidas
- Remover curtidas
- Contabilizar curtidas
- Disponibilizar comentários relacionados

### Colaboradores

- Perfil
- Comunidade
- Comentário
- Feed


## Usuário

### Responsabilidades de Conhecimento

- ID do usuário
- E-mail
- Senha
- Nome de usuário

### Responsabilidades de Realização

- Validar login
- Alterar senha
- Alterar e-mail
- Fornecer informações da conta

### Colaboradores

- Armazenamento
- Perfil