/*
 Pilha
 * Uma Pilha Ã© uma LIFO - Last-int-First-Out
 * Uma pilha pode ser implementada usando um vetor ou uma lista encadeada
 */
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>

struct nodo
{
   int valor;
   struct nodo *prox;
 };
 
typedef struct nodo pilha;


pilha *push (pilha *topo, int v)//insere
  {
    pilha *novo;
    
    novo = (pilha *)malloc(sizeof(pilha)); //Aloca nodo
    if (novo!=NULL) //Se conseguiu alocar memÃ³ria
    {
     novo->valor=v; //Atribui valor ao nodo
     novo->prox=topo; //O campo prox do nodo criado aponta para topo
     topo = novo;     //O nodo criado agora Ã© o primeiro nodo da pilha
    }
    return topo;    
 }

pilha *pop (pilha *topo)//remove
  {
   pilha *aux;
   int v;

   if (topo != NULL)    //A lista estÃ¡ vazia
   {  
    aux=topo;
    v=topo->valor;
    topo=topo->prox;
    free(aux); //Libera a Ã¡rea de memÃ³ria apontada por aux 
    printf("Valor excluÃ­do=%d \n",v);
   }  
   return topo;
}

 void imprime_pilha(pilha *topo)
 {
   pilha *aux;
   aux=topo; //aux recebe o endereÃ§o do primeiro nodo da lista
   
  while (aux!=NULL)
  {
    printf("%i\n",(*aux).valor); //printf("%i",aux->valor);
    aux= aux->prox; //aux aponta para o prÃ³ximo nodo da lista
  }
   printf("\n");
 }
 
          
int main(int argc, char** argv) {

   int valor;
   pilha *ptrt=NULL;
  
   do
   {
    printf("Digite um valor \n");
    scanf("%i",&valor);
    if (valor != 0) 
        ptrt=push(ptrt,valor);
   }while (valor !=0);
 
   imprime_pilha(ptrt); 
   ptrt=pop(ptrt);
   ptrt=pop(ptrt);
   imprime_pilha(ptrt);
   
   return 0;
 }