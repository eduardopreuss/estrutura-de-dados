/* 
 * Fila
 * Uma Fila Ã© uma FIFO - First-In-First-Out
 * Uma Fila pode ser implementada utilizando-se um vetor ou 
 * uma lista simplesmente encadeada
 */

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

struct nodo 
 {
     int valor;
     struct nodo *prox;
 };


struct descritor_fila 
 {
     struct nodo *inicio;				
     struct nodo *fim;	
 } ;
 
typedef struct nodo lista;
typedef struct descritor_fila fila;

fila *cria_fila(fila *f)
{
   
    if (f == NULL)
   {
     f = (fila *)malloc(sizeof(fila));    
     if (f!= NULL)
     {
      f->inicio = NULL; 
      f->fim = NULL; 
     }
   }  
   return f;
}
 
void insere_fila (fila *f,int v)
{
    lista *novo;
    
    if (f != NULL)
    {
     novo = (lista *)malloc(sizeof(lista)); 
     if (novo!=NULL) 
     {
       novo->valor=v; 
       novo->prox=NULL;
       if (f->inicio==NULL)
       {
         f->inicio = novo;
         f->fim = novo;
       }
       else
       {
         (f->fim)->prox = novo;    //o penultimo da fila aponta para o ultimo
          f->fim = novo; 
       }
     }
    }
 }

void remove_fila (fila *f)
  {
   lista *aux;
   int v;

    if ((f!=NULL) && (f->inicio !=NULL))
    {
       aux=f->inicio;
       v=(f->inicio)->valor; 
       f->inicio=(f->inicio)->prox;     //libera o nodo da lista
       if (f->inicio==NULL)
         f->fim=NULL; 
       free(aux);
       printf("Valor excluido=%d \n",v);
    }   
}


 void imprime_fila(fila *f)
 {
   lista *aux;
  
  if (f!= NULL)
  {
    aux=f->inicio;
    while (aux!=NULL)
    {
     printf("%d \n",aux->valor);
     aux= aux->prox;
    }
   }
 }

 int main(int argc, char** argv) {

   fila *ptrf=NULL;
   int valor,s;
  
   ptrf=cria_fila(ptrf); 

   do
   {
    printf("Digite um valor ");
    scanf("%i",&valor);
    if (valor!=0)
    insere_fila(ptrf,valor);
   }while (valor != 0);
  
   printf("Lista antes da exclusao \n");
   imprime_fila(ptrf);
   remove_fila(ptrf);
   remove_fila(ptrf);
   printf("Lista depois da exclusao \n ");
   imprime_fila(ptrf);
 
 return (EXIT_SUCCESS);
}
