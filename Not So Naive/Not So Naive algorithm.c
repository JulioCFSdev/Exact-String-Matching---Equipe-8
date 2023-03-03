/*
O código em questão implementa o algoritmo Not So Naive (NSN) para o problema de correspondência exata de strings. 
O algoritmo recebe como entrada uma string x de comprimento m e uma string y de comprimento n, e busca por todas as ocorrências de x em y. 
A seguir, descrevo em mais detalhes o funcionamento do algoritmo.

O algoritmo é dividido em duas partes: uma fase de pré-processamento e uma fase de busca.
*/

#include <stdio.h>
#include <string.h>

void NSN(char *x, int m, char *y, int n) {
    int j, k, ell;

    /* Preprocessing */
    /*
    Na fase de pré-processamento, o algoritmo determina os valores de k e ell a serem usados na fase de busca. 
    Esses valores dependem dos dois primeiros caracteres de x: se eles forem iguais, k é definido como 2 e ell como 1, caso contrário, k é 1 e ell é 2.
    */
    if (x[0] == x[1]) {
        k = 2;
        ell = 1;
    }
    else {
        k = 1;
        ell = 2;
    }

    /* Searching */
    /*
    Na fase de busca, o algoritmo compara x[1] (o segundo caractere de x) com y[j + 1] (o segundo caractere da substring de y a partir da posição j). 
    Se esses caracteres forem diferentes, o algoritmo avança j por k posições. 
    Caso contrário, o algoritmo verifica se a substring de y a partir da posição j + 2 de comprimento m - 2 é igual à substring de x a partir da posição 2. 
    Se essas substrings forem iguais e se o primeiro caractere de x for igual ao caractere de y na posição j, então o algoritmo imprime a posição j como uma ocorrência de x em y. 
    Em seguida, o algoritmo avança j por ell posições.
    */
    j = 0;
    while (j <= n - m) {
        if (x[1] != y[j + 1])
            j += k;
        else {
            /*
            Uma função importante usada na fase de busca é a função memcmp(), que compara duas regiões de memória de comprimentos iguais. 
            No código em questão, memcmp(x + 2, y + j + 2, m - 2) compara a substring de x a partir da posição 2 com a substring de y a partir da posição j + 2 de comprimento m - 2.
            */
            if (memcmp(x + 2, y + j + 2, m - 2) == 0 &&
                x[0] == y[j])
                printf("Ocorrencia encontrada na posicao %d\n", j);
            j += ell;
        }
    }
}

int main() {
    char x[] = "abc";
    char y[] = "abcabcabcab";

    int m = strlen(x);
    int n = strlen(y);

    NSN(x, m, y, n);

    return 0;
}

/*
Em resumo, o algoritmo NSN é uma abordagem não tão ingênua para o problema de correspondência exata de strings, que oferece uma solução eficiente e escalável. 
O código em C implementa esse algoritmo e pode ser usado para encontrar todas as ocorrências de uma string em outra.
*/

