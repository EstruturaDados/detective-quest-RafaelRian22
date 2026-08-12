#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//define struct nó.
struct No {
    char valor[50];
    struct No* esquerda;
    struct No* direita;
};

//define uma função que adiciona valor e retorna uma struct a qual definimos anteriormente.
struct No* criarNo(char* valor) {
    struct No* novo = (struct No*) malloc(sizeof(struct No));
    strcpy(novo->valor, valor);
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

//essa função simula uma exploração com base na entrada de dados do usuário.
struct No* explorarsalas(struct No* atual, char entrada) {
    if (entrada == 'E' || entrada == 'e') {
        if (atual->esquerda != NULL) {
            return atual->esquerda; 
        } else {
            printf("\n--> Não há nada à esquerda!\n");
            return atual; 
        }
    } else if (entrada == 'D' || entrada == 'd') {
        if (atual->direita != NULL) {
            return atual->direita; 
        } else {
            printf("\n--> Não há nada à direita!\n");
            return atual; 
        }
    } else if (entrada == 'S' || entrada == 's') {
        return NULL; 
    } else {
        printf("\n--> Opção inválida!\n");
        return atual; 
    }
}

void liberar(struct No* raiz) {
    if (raiz != NULL) {
        liberar(raiz->esquerda);
        liberar(raiz->direita);
        free(raiz);
    }
}

int main() { 
    //aqui introduzimos os dados que queremos.
    struct No* raiz = criarNo("Hall de Entrada");
    raiz->esquerda = criarNo("Sala de Estar");
    raiz->direita = criarNo("Biblioteca");
    raiz->esquerda->esquerda = criarNo("Quarto");

    struct No* salaAtual = raiz;
    char entrada = 'P';

    //aqui está o loop, que vai terminar dado as seguintes condições:
    //se o usuário digitar s ou S.
    //se a raiz estiver vazia.
    do {
        printf("\n------------------------------------------------\n");
        //aqui exibe o local atual.
        printf("Você está na sala: [%s]\n", salaAtual->valor);

        if (salaAtual->esquerda == NULL && salaAtual->direita == NULL) {
            printf("Você chegou ao fim do caminho (uma sala folha)!\n");
            break; 
        }

        printf("Digite E (Esquerda), D (Direita) ou S (Sair): ");
        scanf(" %c", &entrada);

        //aqui usamos a função, com base no que o usuário digitou ele pode retornar o local que ele quer acessar.
        //ou ele pode retornar a raiz vazia.
        salaAtual = explorarsalas(salaAtual, entrada);

        if (salaAtual == NULL) {
            printf("Você saiu da exploração.\n");
            break;
        }
    } while (entrada != 'S' && entrada != 's');

    //aqui libera espaço da raiz.
    liberar(raiz);

    return 0;
}