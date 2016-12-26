#include <stdio.h>
#include <stdlib.h>

#define MAX 4
#define MIN 2

struct nodo_arvore {
    int val[MAX + 1], count;
    struct nodo_arvore *filho[MAX + 1];
};

struct nodo_arvore *raiz;

// criando novo nodo

struct nodo_arvore * criarNodo(int val, struct nodo_arvore *filho) {
    struct nodo_arvore *novoNodo;
    novoNodo = (struct nodo_arvore *) malloc(sizeof (struct nodo_arvore));
    novoNodo->val[1] = val;
    novoNodo->count = 1;
    novoNodo->filho[0] = raiz;
    novoNodo->filho[1] = filho;
    return novoNodo;
}

// colocando os valores nas posicoes 

void adcValorNodo(int val, int pos, struct nodo_arvore *nodo, struct nodo_arvore *filho) {
    int j = nodo->count;
    while (j > pos) {
        nodo->val[j + 1] = nodo->val[j];
        nodo->filho[j + 1] = nodo->filho[j];
        j--;
    }
    nodo->val[j + 1] = val;
    nodo->filho[j + 1] = filho;
    nodo->count++;
}

// quebrando o nodo

void quebraNodo(int val, int *pval, int pos, struct nodo_arvore *nodo, struct nodo_arvore *filho, struct nodo_arvore **novoNodo) {
    int media, j;

    if (pos > MIN)
        media = MIN + 1;
    else
        media = MIN;

    *novoNodo = (struct nodo_arvore *) malloc(sizeof (struct nodo_arvore));
    j = media + 1;
    while (j <= MAX) {
        (*novoNodo)->val[j - media] = nodo->val[j];
        (*novoNodo)->filho[j - media] = nodo->filho[j];
        j++;
    }
    nodo->count = media;
    (*novoNodo)->count = MAX - media;

    if (pos <= MIN) {
        adcValorNodo(val, pos, nodo, filho);
    } else {
        adcValorNodo(val, pos - media, *novoNodo, filho);
    }
    *pval = nodo->val[nodo->count];
    (*novoNodo)->filho[0] = nodo->filho[nodo->count];
    nodo->count--;
}

//coloca o valor de val no nodo

int setValorNoNodo(int val, int *pval, struct nodo_arvore *nodo, struct nodo_arvore **filho) {

    int pos;
    if (!nodo) {
        *pval = val;
        *filho = NULL;
        return 1;
    }

    if (val < nodo->val[1]) {
        pos = 0;
    } else {
        for (pos = nodo->count;
                (val < nodo->val[pos] && pos > 1); pos--);
        if (val == nodo->val[pos]) {
            printf("Valores duplicados nao sao permitidos\n");
            return 0;
        }
    }
    if (setValorNoNodo(val, pval, nodo->filho[pos], filho)) {
        if (nodo->count < MAX) {
            adcValorNodo(*pval, pos, nodo, *filho);
        } else {
            quebraNodo(*pval, pval, pos, nodo, *filho, filho);
            return 1;
        }
    }
    return 0;
}

// coloca o val na arvore

void inserir(int val) {
    int flag, i;
    struct nodo_arvore *child;

    flag = setValorNoNodo(val, &i, raiz, &child);
    if (flag)
        raiz = criarNodo(i, child);
}

//copia o sucessor para o valor ser excluido

void copiarSucessor(struct nodo_arvore *meuNodo, int pos) {
    struct nodo_arvore *modelo;
    modelo = meuNodo->filho[pos];

    for (; modelo->filho[0] != NULL;)
        modelo = modelo->filho[0];
    meuNodo->val[pos] = modelo->val[1];

}

//remove o valor do nodo e ajeita os valores

void removerValor(struct nodo_arvore *meuNodo, int pos) {
    int i = pos + 1;
    while (i <= meuNodo->count) {
        meuNodo->val[i - 1] = meuNodo->val[i];
        meuNodo->filho[i - 1] = meuNodo->filho[i];
        i++;
    }
    meuNodo->count--;
}

// desloca o valor do pai para o filho a direita

void mudaDireitaFilho(struct nodo_arvore *meuNodo, int pos) {
    struct nodo_arvore *x = meuNodo->filho[pos];
    int j = x->count;

    while (j > 0) {
        x->val[j + 1] = x->val[j];
        x->filho[j + 1] = x->filho[j];
    }
    x->val[1] = meuNodo->val[pos];
    x->filho[1] = x->filho[0];
    x->count++;

    x = meuNodo->filho[pos - 1];
    meuNodo->val[pos] = x->val[x->count];
    meuNodo->filho[pos] = x->filho[x->count];
    x->count--;
    return;
}

// desloca o valor do pai para o filho a esquerda

void mudaEsquerdaFilho(struct nodo_arvore *meuNodo, int pos) {
    int j = 1;
    struct nodo_arvore *x = meuNodo->filho[pos - 1];

    x->count++;
    x->val[x->count] = meuNodo->val[pos];
    x->filho[x->count] = meuNodo->filho[pos]->filho[0];

    x = meuNodo->filho[pos];
    meuNodo->val[pos] = x->val[1];
    x->filho[0] = x->filho[1];
    x->count--;

    while (j <= x->count) {
        x->val[j] = x->val[j + 1];
        x->filho[j] = x->filho[j + 1];
        j++;
    }
    return;
}

void unirNodos(struct nodo_arvore *meuNodo, int pos) {
    int j = 1;
    struct nodo_arvore *x1 = meuNodo->filho[pos], *x2 = meuNodo->filho[pos - 1];

    x2->count++;
    x2->val[x2->count] = meuNodo->val[pos];
    x2->filho[x2->count] = meuNodo->filho[0];

    while (j <= x1->count) {
        x2->count++;
        x2->val[x2->count] = x1->val[j];
        x2->filho[x2->count] = x1->filho[j];
        j++;
    }

    j = pos;
    while (j < meuNodo->count) {
        meuNodo->val[j] = meuNodo->val[j + 1];
        meuNodo->filho[j] = meuNodo->filho[j + 1];
        j++;
    }
    meuNodo->count--;
    free(x1);
}

void ajustarNodo(struct nodo_arvore *meuNodo, int pos) {
    if (!pos) {
        if (meuNodo->filho[1]->count > MIN) {
            mudaEsquerdaFilho(meuNodo, 1);
        } else {
            unirNodos(meuNodo, 1);
        }
    } else {
        if (meuNodo->count != pos) {
            if (meuNodo->filho[pos - 1]->count > MIN) {
                mudaDireitaFilho(meuNodo, pos);
            } else {
                if (meuNodo->filho[pos + 1]->count > MIN) {
                    mudaEsquerdaFilho(meuNodo, pos + 1);
                } else {
                    unirNodos(meuNodo, pos);
                }
            }
        } else {
            if (meuNodo->filho[pos - 1]->count > MIN)
                mudaDireitaFilho(meuNodo, pos);
            else
                unirNodos(meuNodo, pos);
        }
    }
}

int deletarValorDoNodo(int val, struct nodo_arvore *meuNodo) {
    int pos, flag = 0;
    if (meuNodo) {
        if (val < meuNodo->val[1]) {
            pos = 0;
            flag = 0;
        } else {
            for (pos = meuNodo->count;
                    (val < meuNodo->val[pos] && pos > 1); pos--);
            if (val == meuNodo->val[pos]) {
                flag = 1;
            } else {
                flag = 0;
            }
        }
        if (flag) {
            if (meuNodo->filho[pos - 1]) {
                copiarSucessor(meuNodo, pos);
                flag = deletarValorDoNodo(meuNodo->val[pos], meuNodo->filho[pos]);
                if (flag == 0) {
                    printf("O valor nao foi encontrado na arvore\n");
                }
            } else {
                removerValor(meuNodo, pos);
            }
        } else {
            flag = deletarValorDoNodo(val, meuNodo->filho[pos]);
        }
        if (meuNodo->filho[pos]) {
            if (meuNodo->filho[pos]->count < MIN)
                ajustarNodo(meuNodo, pos);
        }
    }
    return flag;
}

void remover(int val, struct nodo_arvore *meuNodo) {
    struct nodo_arvore *tmp;
    if (!deletarValorDoNodo(val, meuNodo)) {
        printf("O valor nao foi encontrado na arvore\n");
        return;
    } else {
        if (meuNodo->count == 0) {
            tmp = meuNodo;
            meuNodo = meuNodo->filho[0];
            free(tmp);
        }
    }
    raiz = meuNodo;
    return;
}

//procura val na arvore

void buscar(int val, int *pos, struct nodo_arvore *meuNodo) {
    if (!meuNodo) {
        return;
    }

    if (val < meuNodo->val[1]) {
        *pos = 0;
    } else {
        for (*pos = meuNodo->count;
                (val < meuNodo->val[*pos] && *pos > 1); (*pos)--);
        if (val == meuNodo->val[*pos]) {
            printf("O valor %d esta presente na arvore", val);
            return;
        }
    }
    buscar(val, pos, meuNodo->filho[*pos]);
    return;
}

void mostrar_arvore(struct nodo_arvore *raiz) {
    int i;

    if (raiz != NULL) {
        for (i = 0; i < raiz -> count; i++) {
            
            printf("\n \n");
            mostrar_arvore(raiz -> filho [i]);
            printf("%d \t", raiz -> val [i + 1]);
            
        }
        mostrar_arvore(raiz -> filho [i]); 
        printf("\t");
        
    }
}

int main() {
    int val, ch;
    while (1) {
        printf("Escolha uma opcao: \n");
        printf("1 - Inserir\n");
        printf("2 - Deletar\n");
        printf("3 - Procurar\n");
        printf("4 - Mostar arvore\n");
        printf("5 - Sair\n");
        scanf("%d", &ch);
        switch (ch) {
            case 1:
                printf("Digite um numero para ser inserido:");
                scanf("%d", &val);
                inserir(val);
                break;
                
            case 2:
                printf("Digite o numero a ser deletado:");//essa opcao nao ta funcionando direito
                scanf("%d", &val);
                remover(val, raiz);
                break;
                
            case 3:
                printf("Digite o numero a ser procurado:");
                scanf("%d", &val);
                buscar(val, &ch, raiz);
                break;
                
            case 4:
            	printf("\n");
                mostrar_arvore(raiz);
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
