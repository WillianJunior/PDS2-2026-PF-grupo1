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
- Instâncias principais do sistema (Armazenamento, Sistema, Busca)
### Responsabilidades de Realização
- Inicializar e controlar o loop principal do sistema
- Controlar menus
- Gerenciar fluxo de login e cadastro delegando ao Sistema
- Gerenciar fluxo de pesquisa
- Gerenciar visualização de perfis
- Controlar encerramento da aplicação
### Colaboradores
- Armazenamento
- Sistema
- Busca
- Feed
- RestaurarEntradaCin


## Armazenamento 
### Responsabilidades de Conhecimento
- Usuários cadastrados
- Perfis cadastrados
- Comunidades cadastradas
- Posts cadastrados
- Comentários cadastrados
- Próximos IDs disponíveis
### Responsabilidades de Realização
- Carregar dados
- Salvar dados
- Adicionar e recuperar Usuários
- Adicionar e recuperar Perfis
- Adicionar e recuperar Comunidades
- Adicionar e recuperar Posts
- Adicionar e recuperar Comentários
### Colaboradores
- Comunidade
- Perfil
- Usuário
- Post
- Comentário
- GerenciadorCSV


## Sistema 
### Responsabilidades de Conhecimento
- Sessão do usuário logado (E-mail e ID do Perfil)
- Regras de negócio da plataforma
### Responsabilidades de Realização
- Realizar login e logout
- Validar segurança de senhas
- Validar unicidade de e-mails e nomes de usuário
- Criar novos Usuários e Perfis
- Criar novas Comunidades
- Criar novos Posts e Comentários
- Disparar exceções em caso de regras violadas
### Colaboradores
- Armazenamento
- Perfil
- Usuário
- Comunidade
- Post
- Comentário


## Busca
### Responsabilidades de Conhecimento
- Resultados da pesquisa
### Responsabilidades de Realização
- Buscar perfis
- Buscar comunidades
- Buscar posts
- Validar se usuário é membro de comunidade
- Contabilizar número de membros
- Filtrar posts por autor respeitando regras de privacidade
- Agrupar comentários pertencentes a um post
- Resolver nome de exibição de um perfil por ID
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
- Nome e Descrição
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


## Console Utils
### Responsabilidades de Conhecimento
- Regras de interação com o terminal
- Recursos de limpeza e pausa da interface
### Responsabilidades de Realização
- Limpar a tela do terminal
- Pausar a execução aguardando interação do usuário
- Auxiliar na leitura segura de números inteiros
### Colaborações
- Aplicação
- Feed
- Menus


## Feed
### Responsabilidade de Conhecimento
- Dados temporários de exibição do feed
### Responsabilidades de Realização
- Exibir posts, perfis e comunidades
- Renderizar feed principal
- Intermediar criação de posts e curtidas delegando ao Sistema
### Colaboradores
- Post
- Perfil
- Comunidade
- Menus
- Armazenamento
- Sistema


## GerenciadorCSV
### Responsabilidades de Conhecimento
- Estrutura dos arquivos CSV
- Regras de serialização e desserialização
### Responsabilidades de Realização
- Salvar e carregar usuários, perfis, comunidades, posts e comentários
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
- Entidades exibidas na interface
### Responsabilidades de Realização
- Exibir detalhes de posts, perfis e comunidades
- Processar interações de navegação
- Encaminhar ações de edição e criação para o Sistema
### Colaboradores
- Armazenamento
- Sistema
- Perfil
- Comunidade
- Post
- Comentário
- Busca


## Perfil
### Responsabilidades de Conhecimento
- ID do perfil, Nome, Descrição/Biografia
- Curso, Instituição, Período acadêmico
- Comunidades das quais participa
### Responsabilidades de Realização
- Entrar/Sair de comunidade
- Editar informações acadêmicas
### Colaboradores
- Usuário
- Comunidade


## Post
### Responsabilidades de Conhecimento
- ID do post, Autor, Comunidade associada
- Conteúdo textual, Usuários que curtiram
### Responsabilidades de Realização
- Receber/Remover/Contabilizar curtidas
### Colaboradores
- Perfil
- Comunidade


## Usuário
### Responsabilidades de Conhecimento
- ID, E-mail, Senha, Nome de usuário
### Responsabilidades de Realização
- Validar tentativa de login
- Alterar senha e e-mail
### Colaboradores
- Armazenamento
- Perfil


## RestaurarEntradaCin
### Responsabilidades de Conhecimento
- Buffer original de entrada de dados (std::streambuf)
### Responsabilidades de Realização
- Reter o fluxo original do std::cin no construtor (RAII)
- Restaurar automaticamente o buffer original no destrutor
### Colaboradores
- Nenhum (Classe utilitária autocontida)