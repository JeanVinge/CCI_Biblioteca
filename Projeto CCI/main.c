#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct livros
{
    char titulo[30];
    char assunto[50];
    char autor[30];
    int numRegistro;
    struct livros *proximo;
};
struct livros *principal=NULL;

void listar()
{
    system("cls");
    struct livros *percorre;
    percorre=principal;
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
    return;
}

void buscar()
{
    system("cls");
    struct livros *percorre;
    percorre=principal;
    int check=0;
    char tituloLivro[30];
    printf("Digite o titulo do livro a ser procurado: ");
    scanf("%s",tituloLivro);

    while (percorre!=NULL) {
        if (strcmp(percorre->titulo, tituloLivro) ==0) {
            printf("=====================================\n");
            printf("Numero do Registro: %d\n",percorre->numRegistro);
            printf("Titulo: %s\n",percorre->titulo);
            printf("Autor: %s\n",percorre->autor);
            printf("Assunto: %s\n",percorre->assunto);
            printf("=====================================\n\n");
            check++;
            percorre=NULL;
        } else {
            percorre=percorre->proximo;
        }
    }
    if (check==0) {
        printf("\nO Livro %s n�o foi encontrado.\n", tituloLivro);
    }
    return;
}


void inserir()
{
    system("cls");
    struct livros *novo, *percorre;
    novo=malloc(sizeof(struct livros));
    /*printf("Digite o Numero do registro :");
    scanf("%d",&novo->numRegistro);*/
    novo->numRegistro = rand() % 999;
    printf("Digite o titulo :");
    scanf("%s",novo->titulo);
    printf("Digite o Autor :");
    scanf("%s",novo->autor);
    printf("Digite o Assunto :");
    scanf("%s",novo->assunto);
    printf("\n\n");
    novo->proximo=NULL;

    //Inser��o do primeiro n� na lista
    if(principal==NULL){
        principal=novo;
    } else {
        percorre=principal;
        while(percorre->proximo!=NULL)
            percorre=percorre->proximo;
        percorre->proximo=novo;
    }
    return;
}

void retira () {
    system("cls");

    struct livros *anterior = NULL;
    char nome_livro[30];
    struct livros *ponteiro_lista;
    ponteiro_lista = principal;

    if(ponteiro_lista == NULL) {
        printf("Lista vazia, insira um elemento para remover alguma coisa");
        return 0;
    }

    printf("Insira o titulo do livro a ser removido :");
    scanf("%s",nome_livro);

    while (ponteiro_lista != NULL && (strcmp(ponteiro_lista->titulo, nome_livro) != 0) ) {
        anterior = ponteiro_lista;
        ponteiro_lista = ponteiro_lista->proximo;
    }

    if (ponteiro_lista == NULL) {
        printf("n�o achou nada");
    }
    if (anterior == NULL) {//primeiro elemento da lista
        ponteiro_lista = ponteiro_lista->proximo;
        principal = ponteiro_lista;//gambiarra para funfar
    } else {
        anterior->proximo = ponteiro_lista->proximo;//faz o anterior apontar para o proximo elemento do que foi removido
        free(ponteiro_lista);
    }
    return 0;

}



int main()
{
    int opcao=0, semente;
    printf("Digite um numero para gerar a sequencia randomica: ");
    scanf("%d",&semente);
    srand(semente);
    system("cls");
    while (opcao != 5)
    {
        printf("*===================================*\n");
        printf("*Trabalho de CCI - Biblioteca 09/2013\n");
        printf("*===================================*\n\n");
        printf("* 1 - Inserir Livro.\n");
        printf("* 2 - Listar Livros.\n");
        printf("* 3 - Buscar Livro.\n");
        printf("* 4 - Remover Livro.\n");
        printf("* 5 - Sair.\n\n");
        printf("*===================================*\n");
        printf("\n\nEscolha uma opcao: ");
        scanf("%d",&opcao);
        switch (opcao)
        {
        case 1:
            inserir();
            break;
        case 2:
            listar();
            break;
        case 3:
            buscar();
            break;
        case 4:
            retira();
            break;
        case 5:
            break;
        default :
            system("cls");
            printf("\n[ERRO] - Opcao Invalida.\n\n");
            break;
        }
    }
    return 0;
}
