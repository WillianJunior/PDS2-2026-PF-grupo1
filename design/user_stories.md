# Rede Social Educacional (Grupo 1) - User Stories


## Cadastro de usuário

### Descrição
Como usuário, quero criar uma conta na plataforma para acessar os recursos da rede social educacional.

### Critérios de aceitação
- O sistema deve permitir informar nome de usuário, e-mail e senha;
- O sistema deve validar se o e-mail informado já está cadastrado;
- O sistema deve validar se o nome de usuário já está cadastrado;
- A senha deve possuir no mínimo 8 caracteres;
- A senha deve conter pelo menos um dígito numérico.


## Autenticação de usuário

### Descrição
Como estudante, quero realizar login na plataforma para acessar meu perfil e minhas interações.

### Critérios de aceitação
- O sistema deve permitir informar e-mail e senha;
- O login deve ser realizado apenas com credenciais válidas;
- O sistema deve exibir uma mensagem de erro para credenciais inválidas;
- Após autenticação bem-sucedida, o usuário deve acessar o menu principal;
- O usuário deve poder encerrar sua sessão por meio da opção de logout.


## Personalizar perfil

### Descrição
Como estudante, quero visualizar e atualizar minhas informações acadêmicas para manter meu perfil atualizado.

### Critérios de aceitação
- O sistema deve exibir os dados de perfil do usuário;
- O usuário deve poder alterar sua descrição pessoal;
- O usuário deve poder atualizar curso, instituição e período acadêmico;
- As alterações realizadas devem permanecer salvas após o encerramento do sistema;
- Outros usuários devem poder visualizar as informações públicas do perfil.


## Publicar conteúdo

### Descrição
Como aluno, quero publicar conteúdos textuais para compartilhar conhecimentos e experiências acadêmicas.

### Critérios de aceitação
- O usuário deve poder criar uma publicação textual;
- A publicação deve ser associada ao perfil do autor;
- A publicação deve aparecer no feed da plataforma;
- Outros usuários devem conseguir visualizar a publicação;
- As publicações devem permanecer armazenadas após a reinicialização do sistema.


## Interação com publicações

### Descrição
Como estudante, quero interagir com publicações para participar das discussões da comunidade acadêmica.

### Critérios de aceitação
- O usuário deve poder curtir uma publicação;
- O sistema deve registrar a quantidade de curtidas recebidas;
- O usuário deve poder comentar em uma publicação;
- Os comentários devem ficar vinculados à publicação correspondente;
- Outros usuários devem conseguir visualizar os comentários realizados;


## Participação em comunidades

### Descrição
Como aluno, quero ingressar em comunidades de interesse para interagir com pessoas que cse interessem pelos mesmos tópicos.

### Critérios de aceitação
- O sistema deve exibir as comunidades disponíveis;
- O usuário deve poder ingressar em uma comunidade;
- O sistema deve registrar a associação entre usuário e comunidade;
- O usuário deve poder sair de uma comunidade;
- A lista de membros da comunidade deve ser atualizada após alguma entrada ou saída;


## Busca de conteúdos

### Descrição
Como estudante, quero pesquisar informações na plataforma para encontrar perfis, publicações ou comunidades específicos.

### Critérios de aceitação
- O sistema deve permitir pesquisar perfis;
- O sistema deve permitir pesquisar publicações;
- O sistema deve permitir pesquisar comunidades;
- Os resultados devem conter apenas itens relacionados ao termo pesquisado;
- O usuário deve conseguir acessar os resultados encontrados.


## Criação de comunidades

### Descrição
Como estudante, quero criar comunidades com um tema específico, para reunir pessoas interessadas no mesmo assunto.

### Critérios de aceitação
- O usuário deve informar nome e descrição da comunidade.
- O sistema deve registrar o criador como administrador da comunidade;
- A nova comunidade deve aparecer na lista de comunidades disponíveis;
- O administrador deve ser considerado membro da comunidade;
- A comunidade criada deve permanecer salva após reinicialização do sistema.


## Publicação em comunidades

### Descrição
Como membro de uma comunidade, quero publicar conteúdos dentro dela para compartilhar informações específicas sobre o tema do grupo.

### Critérios de aceitação
- Apenas membros da comunidade podem publicar nela;
- A publicação deve ficar associada à comunidade correspondente;
- Os membros devem conseguir visualizar as publicações da comunidade;
- As publicações da comunidade devem exibir seu autor;
- As publicações devem permanecer armazenadas após o encerramento do sistema.
