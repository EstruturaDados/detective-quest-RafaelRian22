#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//define struct nó.
struct No {
    char valor[50];
    char valor2[100];
    struct No* esquerda;
    struct No* direita;
};

//função do tipo struct que criamos que vai alocar espaço para inserirmos informações da sala.
struct No* criarSala(const char* valor, const char* pista) {
    struct No* novo = (struct No*) malloc(sizeof(struct No));
    strcpy(novo->valor, valor);
    strcpy(novo->valor2, pista);
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}
//bem semelhante com a função anterior, a diferença é que iremos inserir informações das pistas.
struct No* arvorepista(const char* valor) {
    struct No* novo = (struct No*) malloc(sizeof(struct No));
    strcpy(novo->valor, valor);
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo; 
}
//função inserirmos dados nos espaços que alocamos para as salas.
struct No* inserirsalas(struct No* raiz, const char* valor, const char* valor2) {
    if (raiz == NULL) 
        return criarSala(valor, valor2);
    
    if (strcmp(valor, raiz->valor) < 0)
        raiz->esquerda = inserirsalas(raiz->esquerda, valor, valor2);
    else if (strcmp(valor, raiz->valor) > 0)
        raiz->direita = inserirsalas(raiz->direita, valor, valor2);
    
    return raiz;
}

//bem semelhante, porém é para pistas.
struct No* inserirPista(struct No* raiz, const char* valor) {
    if (raiz == NULL) 
        return arvorepista(valor);
    
    if (strcmp(valor, raiz->valor) < 0)
        raiz->esquerda = inserirPista(raiz->esquerda, valor);
    else if (strcmp(valor, raiz->valor) > 0)
        raiz->direita = inserirPista(raiz->direita, valor);
        
    return raiz;
}
//função que simula uma exploração de salas com base na entrada de dados do usuário.
struct No* explorarSalasComPistas(struct No* atual, char entrada) {
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

//procedimento que exibi as pistas.
void exibirPistas(struct No* raiz) {
    if (raiz != NULL) {
        exibirPistas(raiz->esquerda);
        printf("%s ", raiz->valor);
        exibirPistas(raiz->direita);
    }
}
//procedimento que libera espaço.
void liberar(struct No* raiz) {
    if (raiz != NULL) {
        liberar(raiz->esquerda);
        liberar(raiz->direita);
        free(raiz);
    }
}

int main() { 
    // aqui introduzimos os dados que queremos, definimos variáveis e definimos ponteiros.
    struct No* raiz = NULL;
    raiz = inserirsalas(raiz, "Hall de Entrada", "Porta da esquerda cheira a mofo. A da direita cheira a fumaça");
    raiz = inserirsalas(raiz, "Sala de Estar", "A TV está ligada em estática. A almofada do sofá está fora do lugar.");
    raiz = inserirsalas(raiz, "Biblioteca", "Diário diz: 'Busque no silêncio'.");
    raiz = inserirsalas(raiz, "Quarto", "A cama está desfeita e a porta do guarda-roupa está entreaberta.");
    
    struct No* salaAtual = raiz;
    struct No* pistas = NULL;
    char entrada = 'P';
    
    // aqui está o loop, que vai terminar dado as seguintes condições:
    // se o usuário digitar s ou S.
    // se a raiz estiver vazia.
    do {
        printf("\n------------------------------------------------\n");
        // aqui exibe o local atual.
        printf("Você está na sala: [%s]\n", salaAtual->valor);
        printf("você tem uma pista: %s\n", salaAtual->valor2);
        //inserimos as pistas de cada sala na árvore pistas.
        pistas = inserirPista(pistas, salaAtual->valor2);
        if (salaAtual->esquerda == NULL && salaAtual->direita == NULL) {
            printf("Você chegou ao fim do caminho (uma sala folha)!\n");
            break; 
        }
        printf("Digite E (Esquerda), D (Direita) ou S (Sair): ");
        scanf(" %c", &entrada);
        
        // aqui usamos a função, com base no que o usuário digitou ele pode retornar o local que ele quer acessar.
        // ou ele pode retornar a raiz vazia.
        salaAtual = explorarSalasComPistas(salaAtual, entrada);

        if (salaAtual == NULL) {
            printf("Você saiu da exploração.\n");
            break;
        }
    } while (entrada != 'S' && entrada != 's');
    
    printf("todas as pistas que você coletou:");
    exibirPistas(pistas);
    
    // aqui libera espaço da raiz e das pistas.
    liberar(raiz);
    liberar(pistas);

    return 0;
}