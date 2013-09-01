#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

enum TIPO_PESQUISA_LIVRO            /* Defines an enumeration type    */
{
    titulo,
    assunto,
    autor
}tipoPesquisa;
struct livros
{
    char titulo[30];
    char assunto[50];
    char autor[30];
    int numRegistro;
    struct livros *proximo;
};

struct livros *principal=NULL;

struct auditoria
{
    char titulo[30];
    char assunto[50];
    char autor[30];
    int numRegistro;
    struct auditoria *proximo;
};
struct auditoria *log=NULL;

void escreverFinalDaOperacaoApertarEnterSair(){
    printf("=====================================\n\n");
    system("pause");
    printf("Aperte enter para sair.......\n\n");
}

void enviarMensagemRegistroNaoEncontrado(){
    printf("\nRegistro não foi encontrado.\n");
    escreverFinalDaOperacaoApertarEnterSair();
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

struct livros * buscarUltimoLivroDaListaPrincipal(){
    struct livros *percorre;
    percorre=principal;
    while(percorre->proximo!=NULL){
        percorre=percorre->proximo;
    }
    return percorre;
}

void insereRegistroNaLista(struct livros *novo){
    struct livros *percorre;
    if(principal==NULL) {
        principal=novo;
    } else {
        percorre= buscarUltimoLivroDaListaPrincipal();
        percorre->proximo=novo;
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

void buscarListaLivroPor(enum TIPO_PESQUISA_LIVRO tipoPesquisa, char busca[30]){
    struct livros *percorre;
    struct livros *achado;
    percorre=principal;
    bool achou = false, escreverValor = false;
    system("cls");
    while (percorre!=NULL) {
        escreverValor = false;
        if(tipoPesquisa == titulo){
             if (strcmp(percorre->titulo, busca) ==0) {
                achado= percorre;
                escreverValor=true;
            }
        } else if (tipoPesquisa == autor) {
            if (strcmp(percorre->autor, busca) ==0) {
                achado=percorre;
                escreverValor=true;
            }
        } else if (tipoPesquisa == assunto) {
            if (strcmp(percorre->assunto, busca) ==0) {
                achado= percorre;
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

void procurarLivroPorTituloMandandoMensagem(){
    char busca[30];
    printf("Digite o titulo do livro a ser procurado: ");
    scanf("%s",busca);
    enum TIPO_PESQUISA_LIVRO tipo = titulo;
    buscarListaLivroPor(tipo,busca);
}

void procurarLivroPorAutorMandandoMensagem(){
    char busca[30];
    printf("Digite o autor do livro a ser procurado: ");
    scanf("%s",busca);
    enum TIPO_PESQUISA_LIVRO tipo = autor;
    buscarListaLivroPor(tipo,busca);
}

void procurarLivroPorAssuntoMandandoMensagem(){
    char busca[30];
    printf("Digite o assunto do livro a ser procurado: ");
    scanf("%s",busca);
    enum TIPO_PESQUISA_LIVRO tipo = assunto;
    buscarListaLivroPor(tipo,busca);
}
void listar()
{
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
    system("pause");
    printf("Aperte enter para sair.......\n\n");
    return;
}

int escreverMenuParaBuscaDeLivros(){
    int opcao = 0;
    printf("=====================================\n");
    printf("* Opcoes de busca.\n");
    printf("=====================================\n\n");
    printf("* \t1 - Titulo.\n");
    printf("* \t2 - Autor.\n");
    printf("* \t3 - Assunto.\n");
    printf("* \t4 - Sair.\n");
    printf("=====================================\n\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);
    system("cls");
    return opcao;
}
void buscar()
{
    system("cls");
    int op=0;
    char busca[30];
    op = escreverMenuParaBuscaDeLivros();

    if (op==1) {
        procurarLivroPorTituloMandandoMensagem();
    } else if (op==2) {
        procurarLivroPorAutorMandandoMensagem();
    } else if (op==3) {
        procurarLivroPorAssuntoMandandoMensagem();
    } else {
        return 0;
    }

    return 0;
}

void inserir()
{
    system("cls");
    struct livros *novo;
    char op[2]="n";
    char op1[2]="s";
    novo=malloc(sizeof(struct livros));
    novo->numRegistro = rand() % 999;
    printf("Digite o titulo : ");
    scanf("%s",novo->titulo);
    printf("Digite o Autor : ");
    scanf("%s",novo->autor);
    printf("Digite o Assunto :");
    scanf("%s",novo->assunto);
    printf("\n\n");
    printf("Adicionar novo registro? <s/n> : ");
    fflush(stdin);
    scanf("%s",op1);
    novo->proximo=NULL;
    insereRegistroNaLista(novo);
    if(strcmp(op, op1) != 0){
        return inserir();
    } else {
        return;
    }
}

void altera()
{
    system("cls");
    struct livros *percorre;
    percorre=principal;
    int check=0, altera=0;
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
        scanf("%d", &altera);
        if (altera==1)
        {
            printf("Novo titulo :");
            scanf("%s", percorre->titulo);
        }
        if (altera==2)
        {
            printf("Novo autor :");
            scanf("%s", percorre->autor);
        }
        if (altera==3)
        {
            printf("Novo assunto :");
            scanf("%s", percorre->assunto);
        }

        system("pause");
        printf("Itens atualizados, aperte enter para sair....");
    }

    return 0;
}

void retira ()
{
    system("cls");
    struct livros *anterior = NULL;
    //struct auditoria *auditor;
    char nome_livro[30];
    struct livros *ponteiro_lista;
    ponteiro_lista = principal;

    if(ponteiro_lista == NULL)
    {
        printf("Lista vazia, insira um elemento para remover alguma coisa");
        return 0;
    }

    printf("Insira o titulo do livro a ser removido :");
    scanf("%s",nome_livro);

    while (ponteiro_lista != NULL && (strcmp(ponteiro_lista->titulo, nome_livro) != 0) )
    {
        anterior = ponteiro_lista;
        ponteiro_lista = ponteiro_lista->proximo;
    }

    if (ponteiro_lista == NULL)
    {
        printf("Registro não encontrado.");
    }
    if (anterior == NULL)  //primeiro elemento da lista
    {
        ponteiro_lista = ponteiro_lista->proximo;
        principal = ponteiro_lista;//gambiarra para funfar
    }
    else
    {
        //auditor=malloc(sizeof(struct auditoria));
        //auditor->assunto = ponteiro_lista->assunto;
        //auditor->autor = ponteiro_lista->autor;
        //auditor->titulo = ponteiro_lista->titulo;
        //auditor->numRegistro = ponteiro_lista->numRegistro;
        anterior->proximo = ponteiro_lista->proximo;//faz o anterior apontar para o proximo elemento do que foi removido
        free(ponteiro_lista);
    }
    return 0;

}

void mudarCor()
{
    int op=0;
    while (op != 7)
    {
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
        printf("* \t7 - Sair.\n\n");
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
        case 7:
            break;
        default :
            system("cls");
            printf("\n[ERRO] - Opcao Invalida.\n\n");
            break;
        }
    }
    return 0;
}

void verificaLista() {
    if (principal == NULL) {
        printf("Lista vazia, insira um registro.");
        return 0;
    }
}

void lixeira() {
    system("cls");
    printf("*====================================\n");
    printf("*Lixeira items excluidos\n");
    printf("*====================================\n\n");
    struct auditoria *percorre;
    percorre=log;
    while (percorre!=NULL)
    {
        printf("=====================================\n");
        printf("Numero do Registro: %d\n",percorre->numRegistro);
        printf("Titulo: %s\n",percorre->titulo);
        printf("Autor: %s\n",percorre->autor);
        printf("Assunto: %s\n",percorre->assunto);
        printf("=====================================\n\n");
        percorre=percorre->proximo;
    }
    system("pause");
    printf("Aperte enter para sair.......\n\n");
    return;
}

int main()
{
    int opcao=0, semente;
    printf("Digite um numero para gerar a sequencia randomica: ");
    scanf("%d",&semente);
    srand(semente);
    while (opcao != 8)
    {
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
        printf("* \t7 - Lixeira (Nao Funciona ainda.).\n");
        printf("* \t8 - Sair.\n\n");
        printf("*===================================*\n");
        printf("\n\nEscolha uma opcao: ");
        scanf("%d",&opcao);
        printf("\n\n");
        switch (opcao)
        {
        case 1:
            inserir();
            break;
        case 2:
            verificaLista();
            listar();
            break;
        case 3:
            verificaLista();
            buscar();
            break;
        case 4:
            verificaLista();
            altera();
            break;
        case 5:
            verificaLista();
            retira();
            break;
        case 6:
            mudarCor();
            break;
        case 7:
            //lixeira();
            break;
        case 8:
            break;
        default :
            system("cls");
            printf("\n[ERRO] - Opcao Invalida.\n\n");
            break;
        }
    }
    return 0;
}
