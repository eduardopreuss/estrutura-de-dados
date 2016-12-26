/* 
 * File:   main.c
 * Author: Tanisi1
 *
 * Created on 10 de MarÃ§o de 2012, 23:24
 */

/*Lista Circular*/

#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>

struct nodo
{
   int valor;
   struct nodo *prox;
 };
 
typedef struct nodo lista;


lista *insere_lista (lista *p, int v)
  {
    lista *novo;
 
    novo = (lista *)malloc(sizeof(lista)); //Aloca nodo
 
    if (novo != NULL) 
    {
     novo->valor=v;
     if (p==NULL) //Se a lista estiver vazia
     {
      	p = novo;
      	p->prox = p;
     }
     else //Se a lista tiver um elemento ou mais
     {
       	 novo->prox = p->prox;
       	 p->prox = novo;
         p = novo;
     }
    }
    return p;
}
    
 
lista *remove_lista (lista *p)
  {
   lista *aux;
   int v;

    if (p != NULL)
    {
       aux = p->prox;
       v=aux->valor;
       if (p->prox==p) 
         p=NULL;
        else
           p->prox=aux->prox;
       free(aux);
       printf("Valor retirado da lista=%d \n",v);
    }
   return p;
}

 void imprime_lista(lista *p)
 {
   lista *aux;
    
  if (p != NULL) 
  {
        aux = p->prox;
        do
        {
            printf("%d \n",aux->valor);
            aux = aux->prox;
        }while (aux != p->prox);
  }
 }
 
          
int main(int argc, char** argv) {

   int valor;
   lista *ptri=NULL;
  
   do
   {
    printf("Digite um valor \n");
    scanf("%i",&valor);
    if (valor != 0) 
        ptri=insere_lista(ptri,valor);
   }while (valor !=0);
 
   imprime_lista(ptri); 
   ptri=remove_lista(ptri);
   ptri=remove_lista(ptri);
   imprime_lista(ptri);
   
   return 0;
 }
