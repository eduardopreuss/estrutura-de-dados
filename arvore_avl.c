
#include<stdlib.h>  
#include<stdio.h>  
#include<malloc.h>  
#define ALTURA 1  


struct nodo {
    int info;
    struct nodo* esq;
    struct nodo* dir;
    int alt;
};

struct nodo* get_node(int val) {
    struct nodo* novo_nodo = (struct nodo*) malloc(sizeof (struct nodo));
    novo_nodo->esq = NULL;
    novo_nodo->dir = NULL;
    novo_nodo->info = val;
    novo_nodo->alt = ALTURA;
    return novo_nodo;
}

int get_altura(struct nodo* raiz) {
    if (!raiz)
        return 0;
    else
        return raiz->alt;
}

int get_balance(struct nodo* raiz) {
    if (!raiz)
        return 0;
    return (get_altura(raiz->esq) - get_altura(raiz->dir));
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

struct nodo* rodar_esquerda(struct nodo* raiz) {
    struct nodo* direita = raiz->dir;
    struct nodo* esquerda = direita->esq;
    //faz a rotacao  
    direita->esq = raiz;
    raiz->dir = esquerda;
    //atualiza a altura do nodo rotacionado 
    raiz->alt = max(get_altura(raiz->esq), get_altura(raiz->dir)) + 1;
    direita->alt = max(get_altura(direita->esq), get_altura(direita->dir)) + 1;
    //return uma nova raiz  
    return direita;
}

struct nodo* rodar_direita(struct nodo* raiz) {
    struct nodo* esquerda = raiz->esq;
    struct nodo* direita = esquerda->dir;
    //faz a rotacao 
    esquerda->dir = raiz;
    raiz->esq = direita;
    //atualiza a altura do nodo rotacionado 
    raiz->alt = max(get_altura(raiz->esq), get_altura(raiz->dir)) + 1;
    esquerda->alt = max(get_altura(esquerda->esq), get_altura(esquerda->dir)) + 1;
    //return uma nova raiz 
    return esquerda;
}

struct nodo* inserir(struct nodo* raiz, int val) {
    //normal insertion  
    if (!raiz) {
        struct nodo* novo_nodo = get_node(val);
        return novo_nodo;
    }
    if (raiz->info > val)
        raiz->esq = inserir(raiz->esq, val);
    else
        raiz->dir = inserir(raiz->dir, val);
    //atualiza a altura da raiz  
    raiz->alt = max(get_altura(raiz->esq), get_altura(raiz->dir)) + 1;
    //checar balanceamento  
    int balance = get_balance(raiz);
    //rotacao simples a direita  
    if (balance > 1 && raiz->esq->info > val) {
        raiz = rodar_direita(raiz);
    }
        //rotacao simples a esquerda  
    else if (balance < -1 && raiz->dir->info < val) {
        raiz = rodar_esquerda(raiz);
    }
        //rotacao dupla a direita (rotacao simples a esquerda E rotacao simples a direita)   
    else if (balance > 1 && raiz->esq->info < val) {
        raiz->esq = rodar_esquerda(raiz->esq);
        raiz = rodar_direita(raiz);
    }
        //rotacao dupla a esquerda (rotacao simples a direita E rotacao simples a esquerda)  
    else if (balance < -1 && raiz->dir->info > val) {
        raiz->dir = rodar_direita(raiz->dir);
        raiz = rodar_esquerda(raiz);
    }
    return raiz;
}
//balanceia o nodo na operacao de deletar 

struct nodo* balancear_tree(struct nodo* raiz) {
    struct nodo* x, *y;
    int esqAlt, dirAlt;
    esqAlt = get_altura(raiz->esq);
    dirAlt = get_altura(raiz->dir);
    if (esqAlt >= dirAlt)
        x = raiz->esq;
    else
        x = raiz->dir;
    esqAlt = get_altura(x->esq);
    dirAlt = get_altura(x->dir);
    if (x == raiz->esq) {
        if (esqAlt >= dirAlt) {
            y = x->esq;
        }
        else
            y = x->dir;
    }
    if (x == raiz->dir) {
        if (esqAlt > dirAlt) {
            y = x->esq;
        }
        else
            y = x->dir;
    }
    //rotacao simples a direita  
    if (raiz->esq == x && x->esq == y) {
        raiz = rodar_direita(raiz);
    }
        //rotacao simples a esquerda  
    else if (x == raiz->dir && x->dir == y) {
        raiz = rodar_esquerda(raiz);
    }
        //rotacao dupla a direita (rotacao simples a esquerda E rotacao simples a direita)  
    else if (x == raiz->esq && y == x->dir) {
        raiz->esq = rodar_esquerda(raiz->esq);
        raiz = rodar_direita(raiz);
    }
        //rotacao dupla a esquerda (rotacao simples a direita E rotacao simples a esquerda)  
    else if (x == raiz->dir && y == x->esq) {
        raiz->dir = rodar_direita(raiz->dir);
        raiz = rodar_esquerda(raiz);
    }
    return raiz;
}
//achar o o sucessor do nodo que tem filho a direita

struct nodo* inorder_suc_direita_arvore(struct nodo* raiz) {
    struct nodo* temp = raiz->dir;
    while (temp->esq) {
        temp = temp->esq;
    }
    return temp;
}

struct nodo* deletar(struct nodo* raiz, int val) {

    if (!raiz)
        return NULL;
    if (raiz->info > val) {
        raiz->esq = deletar(raiz->esq, val);
    }
    else if (raiz->info < val) {
        raiz->dir = deletar(raiz->dir, val);
    }
    else {
        struct nodo* temp;
        if (raiz->esq == NULL || raiz->dir == NULL) {
            if (raiz->esq)
                temp = raiz->esq;
            else if (raiz->dir)
                temp = raiz->dir;
            else
                temp = NULL;
            raiz = NULL;
            free(raiz);
            return temp;
        }
        else {
            temp = inorder_suc_direita_arvore(raiz);
            raiz->info = temp->info;
            raiz->dir = deletar(raiz->dir, temp->info);
        }
    }
    if (raiz) {
        //atualiza altura  
        raiz->alt = max(get_altura(raiz->esq), get_altura(raiz->dir)) + 1;
        int balance = get_balance(raiz);
        if (balance > 1 || balance < -1)
            raiz = balancear_tree(raiz);
    }
    return raiz;
}

void preordem(struct nodo* raiz) {
    if (raiz != NULL) {
        printf("%d\t", raiz->info);
        preordem(raiz->esq);
        preordem(raiz->dir);
    }
}

void posordem(struct nodo* raiz) {
    if (raiz != NULL) {
        posordem(raiz->esq);
        posordem(raiz->dir);
        printf("%d\t", raiz->info);
    }
}

main() {

    struct nodo* raiz = NULL;

    int val, ch;

    while (1) {
        printf("Escolha uma opcao: \n");
        printf("1 - Inserir\n");
        printf("2 - Deletar\n");
        printf("3 - pre ordem\n");
        printf("4 - pos ordem\n");
        printf("5 - sair\n");
        scanf("%d", &ch);
        switch (ch) {
            case 1:
                printf("Digite um numero para ser inserido:");
                fflush(stdin);
                scanf("%d", &val);                
                fflush(stdin);
                raiz = inserir(raiz, val);
                break;
            case 2:
                printf("Digite o numero a ser deletado:");
                fflush(stdin);
                scanf("%d", &val);
                fflush(stdin);
                raiz = deletar(raiz, val);
                break;
            case 3:
                preordem(raiz);
                break;
            case 4:
                posordem(raiz);
                break;

            case 5:
                exit(0);
            default:
                printf("Opcao invalida\n");
                break;
        }
        printf("\n");
    }
}



