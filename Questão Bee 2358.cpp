#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <bits/stdc++.h>

using namespace std;

char* remove_substring(char *str, int start_index, int end_index) {
    int len = strlen(str);

    // verifica se o índice inicial é válido
    if (start_index < 0 || start_index >= len) {
        return str;
    }

    // verifica se o índice final é válido
    if (end_index < start_index || end_index >= len) {
        return str;
    }

    // aloca memória para a nova string, com espaço para os caracteres antes do índice inicial
    // e depois do índice final, mais um caractere nulo
    char *new_str = (char *)malloc((len - (end_index - start_index) + 1) * sizeof(char));

    // copia os caracteres antes do índice inicial
    strncpy(new_str, str, start_index);

    // copia os caracteres depois do índice final
    strcpy(new_str + start_index, str + end_index + 1);

    // adiciona o caractere nulo ao final da nova string
    new_str[len - (end_index - start_index)] = '\0';

    return new_str;
}

char* remove_char(char* str, char c) {
    int len = strlen(str);
    char* result = (char*) malloc((len + 1) * sizeof(char));
    int j = 0;

    // Copia os caracteres da string original para a nova string, exceto os que são iguais a c
    for (int i = 0; i < len; i++) {
        if (str[i] != c) {
            result[j] = str[i];
            j++;
        }
    }
    result[j] = '\0';

    return result;
}

char* NSN(char *x, int m, char *y, int n) {
    int j, k, ell, ooo;

    /* Preprocessing */
    if (x[0] == x[1]) {
        k = 2;
        ell = 1;
    } else {
        k = 1;
        ell = 2;
    }

    /* Searching */
    j = 0;
    while (j <= n - m) {
        if (x[1] != y[j + 1]) {
            j += k;
        } else {
            if (memcmp(x + 2, y + j + 2, m - 2) == 0 && x[0] == y[j]) {
                ooo = j + m - 1;
                y = remove_substring(y, j, ooo);
                return y;
            }
            j += ell;
        }
    }
    
    return y;
}

char* find_common_substring(char **strings, int n) {
    int i, j, k, len, max_len = 0, max_start = 0;
    
    string aux1, aux2;
    
    char *common_substring;

    // seleciona a primeira string como base para a busca da substring comum
    len = strlen(strings[0]);
    common_substring = (char *)malloc((len + 1) * sizeof(char));
    strncpy(common_substring, strings[0], len);
    common_substring[len] = '\0';

    // percorre todas as substrings da primeira string, buscando uma que seja comum a todas as strings
    for (i = 0; i < len; i++) {
        for (j = i + 1; j <= len; j++) {
            // obtém a substring a partir da primeira string
            char *substring = (char *)malloc((j - i + 1) * sizeof(char));
            strncpy(substring, common_substring + i, j - i);
            substring[j - i] = '\0';

            // verifica se a substring está presente em todas as strings restantes
            for (k = 1; k < n; k++) {
            	
            	/*                      */
            	aux1 = strings[k];
            	aux2 = substring;
            	
                if (strstr(strings[k], substring) == NULL) {
                    break;
                }
                /*
                cout << aux1 << " " << aux2 << endl;
                if (aux1 == aux2){
                	
                	aux1 > aux2 ? cout << aux1 << endl : cout << aux2 << endl;
                
				}
				*/
				/*                                */
                
            }

            // se a substring é comum a todas as strings, e é maior do que a substring atualmente armazenada,
            // atualiza a substring comum
            if (k == n && j - i > max_len) {
                max_len = j - i;
                max_start = i;
            }

            // libera a memória alocada para a substring temporária
            free(substring);
        }
    }

    // cria uma nova string para armazenar a substring comum encontrada
    char *result = (char *)malloc((max_len + 1) * sizeof(char));
    strncpy(result, common_substring + max_start, max_len);
    result[max_len] = '\0';

    // libera a memória alocada para a string temporária
    free(common_substring);

    return result;
}

int main() {
    int numb, numb_virus, i, n, m, p;
    char str[1000], cpy[1000], sub_str_commum[1000];
    char *virus = str;
    char **strings, **new_strings;
    char *copy = cpy;
    char *str_commum = sub_str_commum;
    

    // lê o número de strings do teclado
    scanf("%d", &numb);

    // aloca memória para as strings
    strings = (char **)malloc(numb * sizeof(char *));
    for (i = 0; i < numb; i++) {
        strings[i] = (char *)malloc(1000 * sizeof(char));
        scanf("%s", strings[i]);
    }
    
    new_strings = (char **)malloc(numb * sizeof(char *));
    for (i = 0; i < numb; i++) {
        new_strings[i] = (char *)malloc(1000 * sizeof(char));
    }
    
    scanf("%s", virus);
    numb_virus = strlen(virus);
    
    if(numb_virus > 1)
    {
    	// Removendo as substrings presentes nas bactérias nas quais correspondem com o virus
    	for (p = 0; p < numb; p++) {
    		copy = (char *)malloc((strlen(strings[p]) + 1) * sizeof(char));
    		while(1)
    		{
    			m = strlen(strings[p]);
				copy = strings[p];
        		strings[p] = NSN(virus, numb_virus, strings[p], m);
        		if(copy == strings[p])
        		{
        			strcpy(new_strings[p],copy);
        			break;
				}
			}
			free(copy);
    	}	
	}else {
		for (p = 0; p < numb; p++) {
        	strings[p] = remove_char(strings[p], *virus);
        	strcpy(new_strings[p],strings[p]);
			
    	}
	}

	str_commum = find_common_substring(new_strings, numb);
	printf("%s\n", str_commum);

    return 0;
}
