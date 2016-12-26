#include <stdio.h>
#include <stdlib.h>


typedef struct modo
{
    int valor;
    struct modo *prox;
}lista;

lista *insere_inicio(lista *inicio, int V){
    lista *novo;
    novo=(lista*) malloc(sizeof(lista));
    if(novo!=NULL){
        novo->valor=V;
        novo->prox=inicio;
        inicio=novo;
    }
    return inicio;
}
lista *insere_fim(lista *inicio, int V){
    lista *novo, *aux;
    novo=(lista*) malloc(sizeof(lista));
    if(novo!=NULL){
        novo->valor=V;
        novo->prox=NULL;
        if(inicio==NULL){
            inicio=novo;
        }
        else{
            aux=inicio;
            while(aux->prox!=NULL){
                aux=aux->prox;
            }
            aux->prox=novo;
        }
    }
    return inicio;
}

lista *remove_inicio(lista *inicio){
    lista *aux;
    if(inicio!=NULL){
        aux=inicio;
        inicio=inicio->prox;
        free(aux);
    }
    return inicio;
}

lista *remove_fim(lista *inicio){
    lista *aux, *p;
    if(inicio!=NULL){
        aux=inicio;
        if (aux->prox==NULL){
           free(aux); 
           inicio=NULL;
        }
        else{
         while(aux->prox!=NULL){
              p=aux;
              aux=aux->prox; 
            }    
            p->prox=NULL;
            free(aux); 
        }
    }
    return inicio;
}

lista *insere_depois(lista *inicio, int V){
    lista *novo, *aux;
    novo=(lista*) malloc(sizeof(lista));
    if(novo!=NULL){
        if(inicio==NULL){
            novo->valor=V;
            novo->prox=inicio;
            inicio=novo; 
        }
        else{
            aux=inicio;
            aux=inicio->prox;
            inicio->prox=novo;
            novo->valor=V;
            novo->prox=aux;
        }  
    }
    return inicio;
}
lista *maior_valor(lista *inicio){
    lista *aux;
    int maior;
    aux=inicio;
     maior=aux->valor;
     while(aux!=NULL){
         if(maior<aux->valor){
             maior=aux->valor;
         }
        aux=aux->prox;
    }
    printf("O maior valor da lista eh: %d. \n", maior);
    
    return inicio;
}


void imprime_lista(lista *inicio){
    lista *aux;
    aux=inicio;
    printf("Os valores da lista sao:\n");
    while(aux!=NULL){
        printf("%d\n", aux->valor);
        aux=aux->prox;
    }
}


int main(int argc, char** argv) {
    int num, op;
    lista *ptri = NULL;
    
    printf("Escolha uma opcao:\n");
    printf("1 - Insere na Lista - Inicio\n");
    printf("2 - Insere na Lista - Fim\n");
    printf("3 - Remove da Lista - Inicio\n");
    printf("4 - Remove da Lista - Fim\n");
    printf("5 - Insere um valor depois do 1° da lista\n");
    printf("6 - Retorna o maior elemento da lista\n");
    printf("0 - Encerrar o programa\n");
    scanf("%d", &op); 
    while(op!=0){
    switch(op){
        case 1: 
            do
            {
                printf("informe um valor \n");
                scanf("%d", &num);
                if(num!=0){
                    ptri=insere_inicio(ptri, num);
                }
            }while(num!=0);
            imprime_lista(ptri);
        break;
        case 2:
           do
            {
                printf("informe um valor \n");
                scanf("%d", &num);
                if(num!=0){
                    ptri=insere_fim(ptri, num);
                }
            }while(num!=0);
            imprime_lista(ptri);
        break; 
        case 3:
            ptri=remove_inicio(ptri);
            imprime_lista(ptri);
            break;
        case 4:
            ptri=remove_fim(ptri);
            imprime_lista(ptri);
            break;
        case 5:
            printf("informe um valor \n");
            scanf("%d", &num);
            ptri=insere_depois(ptri, num);
            imprime_lista(ptri);
            break;
        case 6:
            ptri = maior_valor(ptri);
            break;
        case 0:
            printf("Programa Encerrado.\n");
            break;
    }
        printf("Escolha uma opcao:\n");
        printf("1 - Insere na Lista - Inicio\n");
        printf("2 - Insere na Lista - Fim\n");
        printf("3 - Remove da Lista - Inicio\n");
        printf("4 - Remove da Lista - Fim\n");
        printf("5 - Insere um valor depois do primeiro valor da lista\n");
        printf("6 - Retorna o maior elemento da lista\n");
        printf("0 - Encerrar o programa\n");
        scanf("%d", &op); 
    }
    
}
