/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: eduardo-pc
 *
 * Created on November 20, 2015, 1:46 AM
 */

/* FAZER EXERCICIO 37 E 13
 * File:   main.c
 * Author: 0573159
 *
 * Created on 30 de Março de 2016, 10:04
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */
typedef struct modo {
    int V;
    struct modo *prox, *ant;
} lista;

int registra_valor(void) {
    int valor;
    printf("Digite um valor: ");
    scanf("%d", &valor);
    return valor;

}

lista *insere_inicio(lista *inicio) {
    int op = registra_valor();
    lista *novo;
    novo = (lista*) malloc(sizeof (lista));
    novo->V = op;
    novo->ant = NULL;
    novo->prox = inicio;

    if (inicio != NULL) {
        inicio->ant = novo;
    }
    inicio = novo;

    return inicio;
}

lista *insere_fim(lista *inicio) {
    int op = registra_valor();
    lista *novo, *aux;
    novo = (lista*) malloc(sizeof (lista));
    novo->V = op;
    novo->prox = NULL;
    if (inicio == NULL) {
        novo->ant = NULL;
        inicio = novo;
    } else {
        aux = inicio;
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = novo;
        novo->ant = aux;

    }
    return inicio;
}

void imprime_inicio(lista *inicio) {
    lista *aux;
    aux = inicio;
    printf("Os valores da lista sao:\n");
    while (aux != NULL) {
        printf("%d\n", aux->V);
        aux = aux->prox;
    }
}

void imprime_fim(lista *inicio) {
    lista *aux;
    printf("Os valores da lista de tras pra frente sao:\n");
    if (inicio != NULL) {
        aux = inicio;
        while (aux->prox != NULL) {
            aux = aux->prox;
        }

        while (aux != NULL) {
            printf("%d\n", aux->V);
            aux = aux->ant;
        }
    }
}

lista *insere_antes(lista *inicio) {
    lista *novo, *aux, *p;
    if (inicio != NULL) {
        novo = (lista*) malloc(sizeof (lista));
        novo->V = registra_valor();
        if (inicio->prox != NULL) {
            aux = inicio;
            while (aux->prox != NULL) {
                p = aux;
                aux = aux->prox;
            }
            novo->prox = aux;
            novo->ant = p;
            p->prox = novo;
            aux->ant = novo;
        } else {
            novo->prox = inicio;
            novo->ant = NULL;
            inicio->ant = novo;
            inicio = novo;
        }
    }
    return inicio;
}

lista *remove_fim(lista *inicio) {
    lista *aux, *p;
    if (inicio != NULL) {
        if (inicio->prox == NULL) {
            free(inicio);
            inicio = NULL;
        } else {
            aux = inicio;
            while (aux->prox != NULL) {
                p = aux;
                aux = aux->prox;
            }
            p->prox = NULL;
            free(aux);
        }
    }
    return inicio;
}

lista *remove_penultimo(lista *inicio) {
    lista *aux, *p, *aux2;
    if (inicio != NULL && inicio->prox != NULL) {
        aux = inicio;
        aux = aux->prox;
        if (aux->prox != NULL) {
            aux = inicio;
            while (aux->prox != NULL) {
                p = aux;
                aux = aux->prox;
            }
            aux2 = p;
            aux2 = aux2->ant;
            free(p);
            aux2->prox = aux;
            aux->ant = aux2;
        } else {
            free(inicio);
            inicio = aux;
            aux->ant = NULL;
        }
    }

    return inicio;
}

lista *remove_inicio(lista *inicio) {
    lista *aux;
    if (inicio != NULL) {
        if (inicio->prox != NULL) {
            aux = inicio;
            aux = aux->prox;
            aux->ant = NULL;
            free(inicio);
            inicio = aux;
        } else {
            free(inicio);
            inicio = NULL;
        }
    }
    return inicio;
}

int main(int argc, char** argv) {
    lista *ptri = NULL;
    lista *ptri2 = NULL;
    int op = 0;


    do {
        printf("1 - Insere na Lista - inicio\n");
        printf("2 - Insere na Lista - fim\n");
        printf("3 - Imprime do inicio\n");
        printf("4 - Imprime do fim\n");
        printf("5 - Insere um valor antes do ultimo valor da lista.\n");
        printf("6 - Remove - fim\n");
        printf("7 - Remove - penultimo\n");
        printf("8 - Remove - inicio\n");
        printf("0 - Encerrar Programa\n");
        printf("Digite uma opçao: ");
        scanf("%d", &op);
        switch (op) {

            case 1:
                ptri = insere_inicio(ptri);
                break;

            case 2:
                ptri = insere_fim(ptri);
                break;

            case 3:
                imprime_inicio(ptri);
                break;

            case 4:
                imprime_fim(ptri);
                break;
            case 5:
                ptri = insere_antes(ptri);
                break;
            case 6:
                ptri = remove_fim(ptri);
                break;
            case 7:
                ptri = remove_penultimo(ptri);
                break;
            case 8:
                ptri = remove_inicio(ptri);
                break;       
            case 0:

                return 0;
                break;

        }
    } while (op != 0);
    return (EXIT_SUCCESS);
}





