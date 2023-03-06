#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LEN 100 // Define o tamanho máximo da string de entrada
#define MAX_N 100000 // Define o valor máximo de n

bool NSN(char *x, int m, char *y, int n) {
    int j, k, ell;

    /* Preprocessing */
    if (x[0] == x[1]) {
        k = 2;
        ell = 1;
    }
    else {
        k = 1;
        ell = 2;
    }

    /* Searching */
    j = 0;
    while (j <= n - m) {
        if (x[1] != y[j + 1])
            j += k;
        else {
            if (memcmp(x + 2, y + j + 2, m - 2) == 0 && x[0] == y[j]) {
            	if(j == 0){
            		return true;
				}
			}
            j += ell;
        }
    }
    
    return false;
}

void add_string(char ***string_list, char *new_string, int *num_strings) {
    (*string_list) = (char **) realloc(*string_list, (*num_strings + 1) * sizeof(char *));
    if ((*string_list) == NULL) {
        printf("Conjunto Ruim");
        exit(1); // ou retorne "Conjunto Ruim" se preferir
    }

    (*string_list)[*num_strings] = (char *) malloc(strlen(new_string) + 1);
    if ((*string_list)[*num_strings] == NULL) {
        printf("Conjunto Ruim");
        exit(1); // ou retorne "Conjunto Ruim" se preferir
    }

    strcpy((*string_list)[*num_strings], new_string);
    (*num_strings)++;
}

void print_strings(char ***string_list, int num_strings) {
    for (int i = 0; i < num_strings; i++) {
        printf("%s\n", (*string_list)[i]);
    }
}

int main() {
    int n = 1, a, b, i, j;
    char** strs;
    char **feedback_list = NULL;
    int num_feedbacks = 0;
    bool has_bad_set;

    while (1) {
        scanf("%d", &n);
        has_bad_set = false;

        if (n == 0) {
            break;
        }

        // Aloca memória suficiente para armazenar n strings de tamanho MAX_LEN
        strs = (char**) malloc(n * sizeof(char*));

        for (int i = 0; i < n; i++) {
            strs[i] = (char*) malloc((MAX_LEN + 1) * sizeof(char));
            if (strs[i] == NULL) {
                exit(1);
            }
            scanf("%s", strs[i]);
        }
        
        for (i = 0; i < n; i++){
        	for (j = 0; j < n; j++){
			
        		a = strlen(strs[i]);
    			b = strlen(strs[j]);
        		if(i != j && a <= b){
        			if(a == 1){
        				if(strs[i][0] == strs[j][0]){
        					has_bad_set = true;	
						}
					} else {
						has_bad_set = NSN(strs[i], a, strs[j], b); /*  NSN   */
					}
        			if(has_bad_set)
        			{
        				/* Armazena que foi ruim na matriz Feedbacks */
        				add_string(&feedback_list, "Conjunto Ruim", &num_feedbacks);
        				break;
					}
				}
			}
			if(has_bad_set){
				break;
			}
		}
		
		if(!has_bad_set){
			add_string(&feedback_list, "Conjunto Bom", &num_feedbacks);
		}

        // Libera a memória alocada para cada string
        for (i = 0; i < n; i++) {
            free(strs[i]);
        }
        // Libera a memória alocada para o vetor de strings
        free(strs);
    }
    
    print_strings(&feedback_list, num_feedbacks);

    return 0;
}
