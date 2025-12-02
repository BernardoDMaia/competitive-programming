#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0
typedef int bool;
typedef int TIPOCHAVE;

typedef struct {
    TIPOCHAVE chave;
} REGISTRO;

typedef struct aux {
    REGISTRO reg;
    struct aux* prox;
} ELEMENTO;

typedef ELEMENTO* PONT;

typedef struct {
    PONT topo;
} PILHA;

void inicializarPilha(PILHA* p) {
    p->topo = NULL;
}

bool inserirElemPilha(PILHA* p, REGISTRO reg){
    PONT novo = (PONT) malloc(sizeof(ELEMENTO));
    if (novo==NULL) return false;
    novo->reg = reg;
    novo->prox = p->topo;
    p->topo = novo;
    return true;
}

void exibirPilha(PILHA* p) {
    PONT end = p->topo;
    while (end != NULL) {
        printf("%d", end->reg.chave);
        end = end->prox;
    }
    printf("\n");
}

void converte(int n, PILHA* stack){
    while(n > 1){
        REGISTRO r;
        r.chave = n % 2;
        inserirElemPilha(stack, r);
        n /= 2;
    }
    REGISTRO r;
    r.chave = 1;
    inserirElemPilha(stack, r);
}

int main(){
    PILHA stack;          // <- CORRETO
    inicializarPilha(&stack);

    int n;
    scanf("%d", &n);

    converte(n, &stack);  // <- CORRETO
    exibirPilha(&stack);

    return 0;
}