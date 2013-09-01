#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

enum TIPO_PESQUISA_LIVRO{
    titulo,
    assunto,
    autor,
    numeroRegistro
};

struct livros {
    char titulo[30];
    char assunto[50];
    char autor[30];
    int numRegistro;
    struct livros *proximo;
};

void escreverFinalDaOperacaoApertarEnterSair();
void enviarMensagemRegistroNaoEncontrado();

void insereRegistroNaListaPrincipalDeLivros(struct livros *novo);
void insereRegistroNaListaDeLivrosExcluidos(struct livros *excluido);
void inserirNovoLivro();
void inserirNovoLivroOrdenando();
void exibirInformacoesDoLivro(struct livros * livro);

void escreverRegistroEncontrado();
void listarLivrosCadastrados();
void escreverOpcaoInvalida();
void menuBuscar();
int escreverMenuComOpcoesParaBuscaDeLivros();
void deveInserirMaisRegistros();
void mudarConfiguracoesDeCor();
void verificaSeListaDeLivrosEstaVazia();

void removerLivroDaListaDeCadastro ();
void exibirDadosDosLivrosExcluidos();


void buscarLivrosPor(enum TIPO_PESQUISA_LIVRO tipoPesquisa, char busca[30]);
void procurarLivrosPorTitulo();
void procurarLivroPorAutor();
void procurarLivroPorAssunto();
void alterarDadosDoLivroPassandoTitulo();
struct livros * buscarUltimoLivroDaListaPrincipal();
struct livros * buscarUltimoLivroDaListaDeExcluidos();
struct livros * buscarLivroPorTitulo(char titulo[30]);



struct livros *principal=NULL;
struct livros *livros_excluidos=NULL;

void escreverFinalDaOperacaoApertarEnterSair(){
    printf("=====================================\n\n");
    system("pause");
    printf("Aperte enter para sair.......\n\n");
}

void enviarMensagemRegistroNaoEncontrado(){
    printf("\nRegistro não foi encontrado.\n");
    escreverFinalDaOperacaoApertarEnterSair();
}

struct livros * buscarUltimoLivroDaListaPrincipal(){
    struct livros *percorre;
    percorre=principal;
    while(percorre->proximo!=NULL){
        percorre=percorre->proximo;
    }
    return percorre;
}

struct livros * buscarUltimoLivroDaListaDeExcluidos(){
    struct livros *percorre;
    percorre=livros_excluidos;
    while(percorre->proximo!=NULL){
        percorre=percorre->proximo;
    }
    return percorre;
}

void inserirNovoLivroOrdenando(struct livros *novo){
    struct livros *percorre;
    percorre=principal;
    struct livros *anterior = NULL;

    if(principal==NULL) {
        principal=novo;
    } else {
        while(percorre != NULL && (percorre->numRegistro < novo->numRegistro)) {
            anterior = percorre;
            percorre = percorre->proximo;
        }
        anterior->proximo = novo;
        novo->proximo = percorre;
    }
    return;
}

void insereRegistroNaListaPrincipalDeLivros(struct livros *novo){
    struct livros *percorre;
    if(principal==NULL) {
        principal=novo;
    } else {
        percorre= buscarUltimoLivroDaListaPrincipal();
        percorre->proximo=novo;
    }
    return;
}

void insereRegistroNaListaDeLivrosExcluidos(struct livros *excluido){
    struct livros *percorre;
    if(livros_excluidos==NULL) {
        livros_excluidos=excluido;
    } else {
        percorre= buscarUltimoLivroDaListaDeExcluidos();
        percorre->proximo=excluido;
    }
    return;
}

void exibirInformacoesDoLivro(struct livros * livro){
    printf("* \tNumero do Registro: %d\n",livro->numRegistro);
    printf("* \tTitulo: %s\n",livro->titulo);
    printf("* \tAutor: %s\n",livro->autor);
    printf("* \tAssunto: %s\n",livro->assunto);
}

void escreverRegistroEncontrado(){
    printf("=====================================\n");
    printf("*Registro encontrado! \n");
    printf("=====================================\n");
}

void buscarLivrosPor(enum TIPO_PESQUISA_LIVRO tipoPesquisa, char busca[30]){
    struct livros *percorre;
    struct livros *achado;
    percorre=principal;
    bool achou = false, escreverValor = false;
    system("cls");
    while (percorre!=NULL) {
        escreverValor = false;
        if(tipoPesquisa == titulo){
             if (strcmp(percorre->titulo, busca) == 0) {
                achado = percorre;
                escreverValor=true;
            }
        } else if (tipoPesquisa == autor) {
            if (strcmp(percorre->autor, busca) == 0) {
                achado = percorre;
                escreverValor=true;
            }
        } else if (tipoPesquisa == assunto) {
            if (strcmp(percorre->assunto, busca) == 0) {
                achado = percorre;
                escreverValor=true;
            }
        } else if(tipoPesquisa == numeroRegistro){
            char bla[30];
            sprintf(bla,"%d",percorre->numRegistro);
            if (strcmp(bla,busca) == 0){
                achado = percorre;
                escreverValor=true;
            }
        }

        if(escreverValor == true){
            escreverRegistroEncontrado();
            exibirInformacoesDoLivro(achado);
            achou = true;
        }
        percorre=percorre->proximo;
    }
    if(achou == false) {
        printf("\nO Livro %s não foi encontrado.\n", busca);
    }
    system("pause");
    return;
}

struct livros * buscarLivroPorTitulo(char titulo[30]){
    struct livros *percorre;
    percorre=principal;
    while (percorre!=NULL) {
        if (strcmp(percorre->titulo, titulo) ==0) {
            return percorre;
        } else {
            percorre=percorre->proximo;
        }
    }
    printf("\nO Livro %s não foi encontrado.\n", titulo);
    system("pause");
    return NULL;
}

void procurarLivrosPorTitulo(){
    char busca[30];
    printf("Digite o titulo do livro a ser procurado: ");
    scanf("%s",busca);
    enum TIPO_PESQUISA_LIVRO tipo = titulo;
    buscarLivrosPor(tipo,busca);
}

void procurarLivroPorAutor(){
    char busca[30];
    printf("Digite o autor do livro a ser procurado: ");
    scanf("%s",busca);
    enum TIPO_PESQUISA_LIVRO tipo = autor;
    buscarLivrosPor(tipo,busca);
}

void procurarLivroPorAssunto(){
    char busca[30];
    printf("Digite o assunto do livro a ser procurado: ");
    scanf("%s",busca);
    enum TIPO_PESQUISA_LIVRO tipo = assunto;
    buscarLivrosPor(tipo,busca);
}

void procurarLivroPorNumeroRegistro(){
    char busca[30];
    printf("Digite o numero de registro do livro a ser procurado: ");
    scanf("%s",busca);
    enum TIPO_PESQUISA_LIVRO tipo = numeroRegistro;
    buscarLivrosPor(tipo,busca);
}

void listarLivrosCadastrados() {
    system("cls");
    printf("*====================================\n");
    printf("*Relatorio de livros adicionados\n");
    printf("*====================================\n\n");
    struct livros *percorre;
    percorre=principal;
    while (percorre!=NULL)
    {
        printf("=====================================\n");
        exibirInformacoesDoLivro(percorre);
        printf("=====================================\n\n");
        percorre=percorre->proximo;
    }
    escreverFinalDaOperacaoApertarEnterSair();
    return;
}

void escreverOpcaoInvalida() {
    printf("Opcao invalida");
    system("pause");
}

int escreverMenuComOpcoesParaBuscaDeLivros(){
    int opcao = 0;
    printf("=====================================\n");
    printf("* Opcoes de busca.\n");
    printf("=====================================\n\n");
    printf("* \t1 - Titulo.\n");
    printf("* \t2 - Autor.\n");
    printf("* \t3 - Assunto.\n");
    printf("* \t4 - Numero Registro.\n");
    printf("* \t0 - Sair.\n");
    printf("=====================================\n\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);
    system("cls");
    return opcao;
}

void menuBuscar() {
    system("cls");
    int op=0;
    op = escreverMenuComOpcoesParaBuscaDeLivros();

    if (op==1) {
        procurarLivrosPorTitulo();
    } else if (op==2) {
        procurarLivroPorAutor();
    } else if (op==3) {
        procurarLivroPorAssunto();
    } else if (op==4) {
        procurarLivroPorNumeroRegistro();
    } else if (op==0) {
        return;
    }else {
        escreverOpcaoInvalida();
        return;
    }

    return;
}

void deveInserirMaisRegistros(){
    char op[2]="n";
    char op1[2]="s";

    printf("Adicionar novo registro? <s/n> : ");
    fflush(stdin);
    scanf("%s",op1);
    if(strcmp(op, op1) != 0){
        return inserirNovoLivro();
    } else {
        return;
    }
}

void inserirNovoLivro(){
    system("cls");
    struct livros *novo;
    novo=malloc(sizeof(struct livros));
    novo->numRegistro = rand() % 999;
    printf("Digite o titulo : ");
    scanf("%s",novo->titulo);
    printf("Digite o Autor : ");
    scanf("%s",novo->autor);
    printf("Digite o Assunto :");
    scanf("%s",novo->assunto);
    printf("\n\n");
    novo->proximo=NULL;
    inserirNovoLivroOrdenando(novo);

    return deveInserirMaisRegistros();

}

void alterarDadosDoLivroPassandoTitulo() {
    system("cls");
    struct livros *percorre;
    percorre=principal;
    int alterarDadosDoLivroPassandoTitulo=0;
    char tituloLivro[30];

    printf("Digite o titulo do livro a ser Alterado: ");
    scanf("%s",tituloLivro);
    percorre = buscarLivroPorTitulo(tituloLivro);

    if(percorre != NULL) {
        system("cls");
        escreverRegistroEncontrado();
        exibirInformacoesDoLivro(percorre);
        printf("=====================================\n\n");

        printf("* Voce Deseja Alterar?  1 - Titulo, 2 - Autor, 3 - Assunto : ");
        scanf("%d", &alterarDadosDoLivroPassandoTitulo);
        if (alterarDadosDoLivroPassandoTitulo==1) {
            printf("Novo titulo :");
            scanf("%s", percorre->titulo);
        } else if (alterarDadosDoLivroPassandoTitulo==2) {
            printf("Novo autor :");
            scanf("%s", percorre->autor);
        } else if (alterarDadosDoLivroPassandoTitulo==3) {
            printf("Novo assunto :");
            scanf("%s", percorre->assunto);
        } else {
            escreverOpcaoInvalida();
        }

        escreverFinalDaOperacaoApertarEnterSair();
    }
    return;
}

void removerLivroDaListaDeCadastro(){
    system("cls");
    struct livros *anterior = NULL;

    char nome_livro[30];
    struct livros *ponteiro_lista;
    ponteiro_lista = principal;

    printf("Insira o titulo do livro a ser removido :");
    scanf("%s",nome_livro);

    while (ponteiro_lista != NULL && (strcmp(ponteiro_lista->titulo, nome_livro) != 0) ) {
        anterior = ponteiro_lista;
        ponteiro_lista = ponteiro_lista->proximo;
    }

    if (ponteiro_lista == NULL) {
        enviarMensagemRegistroNaoEncontrado();
        return;
    }

    if (anterior == NULL) {  //primeiro elemento da lista
        insereRegistroNaListaDeLivrosExcluidos(ponteiro_lista);
        ponteiro_lista = ponteiro_lista->proximo;
        principal = ponteiro_lista;
        ponteiro_lista=NULL;
    } else {
        insereRegistroNaListaDeLivrosExcluidos(ponteiro_lista);
        anterior->proximo = ponteiro_lista->proximo;//faz o anterior apontar para o proximo elemento do que foi removido
        ponteiro_lista->proximo = NULL;
    }
    return;
}

void mudarConfiguracoesDeCor() {
    int op=0;
    system("cls");
    printf("*===================================*\n");
    printf("*Escolha a cor da letra/Fundo de tela\n");
    printf("*===================================*\n\n");
    printf("* \t1 - Cinza/Azul.\n");
    printf("* \t2 - Azul/Verde Agua.\n");
    printf("* \t3 - Marrom/Azul.\n");
    printf("* \t4 - Cinza/Vermelho.\n");
    printf("* \t5 - Azul/Lilas.\n");
    printf("* \t6 - Verde/Mostarda.\n");
    printf("* \t0 - Sair.\n\n");
    printf("*===================================*\n");
    printf("\n\nEscolha uma opcao: ");
    scanf("%d",&op);
    printf("\n\n");
    switch (op)
    {
    case 1:
        system("COLOR 17");
        break;
    case 2:
        system("COLOR 39");
        break;
    case 3:
        system("COLOR 34");
        break;
    case 4:
        system("COLOR 47");
        break;
    case 5:
        system("COLOR 53");
        break;
    case 6:
        system("COLOR 62");
        break;
    case 0:
        return;//volta menu principal
        break;
    default :
        escreverOpcaoInvalida();
        break;
    }
    return mudarConfiguracoesDeCor();
}

void verificaSeListaDeLivrosEstaVazia() {
    if (principal == NULL) {
        printf("Lista vazia, insira um registro.");
        return;
    }
}

void exibirDadosDosLivrosExcluidos() {
    system("cls");
    printf("*====================================\n");
    printf("*Lixeira items excluidos\n");
    printf("*====================================\n\n");
    struct livros *percorre;
    percorre=livros_excluidos;
    while (percorre!=NULL)
    {
        printf("=====================================\n");
        exibirInformacoesDoLivro(percorre);
        printf("=====================================\n\n");
        percorre=percorre->proximo;
    }
    escreverFinalDaOperacaoApertarEnterSair();
    return;
}

void menuPrincipal() {
    int opcao=0;
    system("cls");
    printf("*===================================*\n");
    printf("*Trabalho de CCI - Biblioteca 09/2013\n");
    printf("*===================================*\n\n");
    printf("* \t1 - Inserir Livro.\n");
    printf("* \t2 - Listar Livros.\n");
    printf("* \t3 - Buscar Livro.\n");
    printf("* \t4 - Alterar Livro.\n");
    printf("* \t5 - Remover Livro.\n");
    printf("* \t6 - Mudar cor.\n");
    printf("* \t7 - Lixeira.\n");
    printf("* \t0 - Sair.\n\n");
    printf("*===================================*\n");
    printf("\n\nEscolha uma opcao: ");
    scanf("%d",&opcao);
    printf("\n\n");
    switch (opcao) {
    case 1:
        inserirNovoLivro();
        break;
    case 2:
        verificaSeListaDeLivrosEstaVazia();
        listarLivrosCadastrados();
        break;
    case 3:
        verificaSeListaDeLivrosEstaVazia();
        menuBuscar();
        break;
    case 4:
        verificaSeListaDeLivrosEstaVazia();
        alterarDadosDoLivroPassandoTitulo();
        break;
    case 5:
        verificaSeListaDeLivrosEstaVazia();
        removerLivroDaListaDeCadastro();
        break;
    case 6:
        mudarConfiguracoesDeCor();
        break;
    case 7:
        exibirDadosDosLivrosExcluidos();
        break;
    case 0:
        return;
        break;
    default :
        escreverOpcaoInvalida();
        break;
    }
    return menuPrincipal();
}
int main(){
    int semente;
    printf("Digite um numero para gerar a sequencia randomica: ");
    if (scanf("%d",&semente) == 1) {
        srand(semente);
        menuPrincipal();
    } else {
        printf("Não eh um numero valido.\n");
    }

    return 0;
}
