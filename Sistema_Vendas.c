#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <time.h>

/*Anotações
    Erro ao armazenar produtos, o ultimo produto adicionado sobrepoe os outros!

    Fazer o Total da Compra!
*/

typedef struct produtos
{
    char nomeProduto[60];
    int quantidade;
    float valorUnitario, valorTotal;
}produtos;

typedef struct venda
{
    char nomeCliente[60], data[10];
    int numeroVenda, totalItem;
    produtos *produto;
    struct venda *next, *back;
} venda;

venda *inicio, *fim, *auxiliar, *corrente;

void qtdItens()
{
    int i, a, totalItens;
    float  b, c;

    printf("\n Digite a quantidade total de itens [sem contar repetidos]: ");
    scanf("%d",&totalItens);

    corrente->totalItem = totalItens;
    corrente->produto = (produtos*)malloc(totalItens*sizeof(produtos));

    if(corrente->produto == NULL)
    {
        printf("\n Erro na alocação de memória!");
        system("pause");
    }else{
        for(i=0;i<totalItens;i++)  //cria uma pilha encadeada
        {
            //corrente->produto = NULL;
            printf("\n ---- Produto %d! ----",i+1);
            setbuf(stdin, 0);
            printf("\n Digite o nome do produto [sem acentuação]: ");
            fgets(corrente->produto->nomeProduto,60,stdin);
            corrente->produto->nomeProduto[strcspn(corrente->produto->nomeProduto, "\n")] = 0;

            printf("\n Digite a quantidade desse item comprado: ");
            scanf("%d",&corrente->produto->quantidade);

            printf("\n Digite o valor unitário: ");
            scanf("%f",&corrente->produto->valorUnitario);

            a = corrente->produto->quantidade;
            b = corrente->produto->valorUnitario;
            c = a*b;

            corrente->produto->valorTotal = c;
        }
    }
}

void inserir()
{
    system("cls");

    printf("\n ----- Sistema de Vendas -----");
    printf("\n\n");
    printf("\n Número de registro da venda: ");
    scanf("%d",&corrente->numeroVenda);
    setbuf(stdin, 0);
    printf("\n Nome do cliente [sem acentuação]: ");
    fgets(corrente->nomeCliente,60,stdin);
    corrente->nomeCliente[strcspn(corrente->nomeCliente, "\n")] = 0;
    printf("\n Data do cadastro [DD/MM/YYYY]: ");
    scanf("%s",&corrente->data);
    qtdItens();
}


void cadastrar()
{
    if(inicio==NULL)
    {
        corrente=(venda*)malloc(sizeof(venda));
        auxiliar=corrente;
        inicio=corrente;
        fim=corrente;
        corrente->next=NULL;
        corrente->back=NULL;
        inserir();
    }
    else
    {
        auxiliar = inicio;
        while(auxiliar->next != NULL)
        {
            auxiliar=auxiliar->next;
        }
        corrente=(venda*)malloc(sizeof(venda));
        auxiliar->next=corrente;
        corrente->back=auxiliar;
        auxiliar=corrente;
        corrente->next=NULL;
        fim=corrente;
        inserir();
    }
}

void exibir()
{
    if(inicio == NULL)
    {
        printf("\n Lista vazia...\n");
        system("pause");
    }
    else
    {
        system("cls");
        printf("\n ----- Sistema de Vendas -----");
        printf("\n\n");
        struct tm *p; //estrutura para data e hora local
        time_t seconds;
        time(&seconds);
        p = localtime(&seconds);

        int qt,i;
        auxiliar = fim;
        while(auxiliar != NULL)
        {
            printf("\n Número de registro: %d       Data: %s        Nome: %s \n",auxiliar->numeroVenda,auxiliar->data,auxiliar->nomeCliente);
            printf("\n\t Nome do Produto \t Quantidade \t Valor Unitario \t Valor Total");
            qt = corrente->totalItem;
            for(i=0;i<qt;i++)
            {
                printf("\n\t %s \t\t %d x \t\t R$ %.2f \t\t R$ %.2f ",corrente->produto->nomeProduto,corrente->produto->quantidade,corrente->produto->valorUnitario,corrente->produto->valorTotal);
            }

            printf("\n\n Total da Compra: R$ ..");
            printf("\n\n Obrigado e volte sempre!");
            printf("\n Gerado em %d/%d/%d às %d:%d:%d horas.\n\n", p->tm_mday, p->tm_mon + 1, p->tm_year + 1900, p->tm_hour, p->tm_min, p->tm_sec);
            printf("\n--------------------------------------------------------------------------------------------------------\n");
            auxiliar=auxiliar->back;
        }
        system("pause");
    }
}

int main()
{
    setlocale(LC_ALL,"Portuguese");

    inicio = NULL;
    fim = NULL;
    auxiliar = NULL;
    corrente = NULL;

    int op;

    do
    {
        system("cls");
        printf("\n ----- Sistema de Vendas -----");
        printf("\n\n [1] - Cadastrar Venda");
        printf("\n [2] - Exibir Venda");
        printf("\n [3] - Sair");

        printf("\n\n Escolha sua opção: ");
        scanf("%d",&op);

        switch(op)
        {
        case 1:
            cadastrar();
            break;
        case 2:
            exibir();
            break;
        case 3:
            exit(1);
            break;
        default:
            printf("\n Opção invalida... Tente novamente... \n");
            system("pause");
        }
    }
    while(op>0);
    return 0;
}
