Pseudocodigo:
Na tela inicial:
fazer login, criar conta e sair
No fazer login, pede email e senha. Se os dois batem com o "banco de dados" pode acessar. Caso contrário, email ou senha ivalidos, opção tente novamente ou voltar.
No criar conta pede email e senha (min 8 digitos), se senha for válida, vai para usuário. Se usuário repetido, avisar que existe alguém com esse nome, tentar novamente. Se email ou senha inválidos (email repetido ou senha sem minimo de 8 digitos) avisar que email repetido ou senha inválida, tentar novamente.
No sair, encerra o programa.
No backend:
ver feed, buscar, ver comunidades, ver perfil, alterar credenciais, deslogar
No ver feed:
Cataloga os posts, de forma "cronológica" (O mais recente aparece primeiro). Opções: entrar num post e voltar. 
Post padrão: usuario que escreveu, a comunidade que o post pertence se tiver e o conteúdo.
Dentro dele além de todo o restante tem o número de curtidas e os comentários (O comentario em sua lógica é muito igual ao post).
Opções: curtir/descurtir post, curtir/descurtir comentário. Fazer comentário. Abrir perfil do usuário do post. Abrir comunidade (se tiver). Voltar
No buscar: Tela de selecione o que voce quer buscar (perfil, post, comunidade). Depois digitar o termo chave e vai aparecer as opções tipo luana (1 - @luana.silva, 2 - @luaninha). opções de entrar no Perfil ou post ou comunidade. opção de voltar.
No ver comunidades:
Comunidades que pertence (tanto como seguidor, quanto administrador)
Opções: Criar comunidade (como admin). Explorar comunidade:
Comunidade padrão: nome, descrição, admin e posts feitos dentro dela - Opções: Virar membro (entra na sua lista de comunidades), postar (apenas se for membro), Entrar no post e voltar. Sair de uma comunidade. Voltar
No alterar credenciais:
1 - alterar email
2 - alterar senha
No ver perfil:
Mostra seu usuario, biografia, curso, instituição, período, número de seguidores, número de seguidos e comunidades que pertence. Tem a opção de ver posts feito pelo usuário, opção de editar perfil: 1 - curso 2 - instituição 3 - Biografia e 4 - período (no início estão vazios). Opção ver seguidores: ex 1 - @luana 2 - @joao (opção ver perfil selecionado e opção voltar). Opção ver seguidos: ex 1 - @luana 2 - @melissa (opção ver perfil selecionado, opção deixar de seguir e opção voltar) e opção de voltar.
Quando está vendo o perfil dos outros pode ver usuario, curso, instituição, número de seguidores, número de seguidos e comunidades que pertence. As opções são ver posts deste usuário, seguir usuário (se já seguir, mandar mensagem que já segue) e voltar.

Gosto de um padrão tipo:
////////////////////////////////////////
          EDU SOCIAL TELA INICIAL
////////////////////////////////////////
1 - Login
2 - Criar Usuário
3 - Sair

Digite sua opção desejada:

O mesmo padrão segue para todas as outras telas, inclusive feed
///////////////////////////////////////
	    EDU SOCIAL FEED
///////////////////////////////////////

1 - @luana.silva (Clube c++)
Adoro ler livros sobre c++

2 - @joao.sirge
Gente, essa faculdade ta me matando

A) Selecionar Post / B) Voltar

Digite sua opção desejada: A
Qual Post deseja selecionar: 1


////////////////Post//////////////////

@luana.silva (Clube c++)
Adoro ler livros sobre c++
Curtidas: 23

/////////////Comentarios//////////////

1 - @luquinhas
Ninguém perguntou
Curtidas: 3

2 - @joao.sirge
Esse luquinhas é muito grosso
Curtidas: 15

A) Curtir/Descurtir Post / B) Curtir/Descurtir Comentário / C) Comentar
D) Abrir Perfil / E) Abrir Comunidade / F) Voltar

Digite sua opção desejada: B
Qual comentário deseja Curtir/Descurtir: 2
...
Digite sua opção desejada: F
