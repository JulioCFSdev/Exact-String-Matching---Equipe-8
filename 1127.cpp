//  Questão resolvida com uso do algoritmo KMP
#include <bits/stdc++.h>
#include <string>
#include <stdlib.h>

char txt[100000] , pat[10000];
char notes[] = "ABCDEFG";

// Distancia entre notas em semi-tons
// Entre B e C, E e F há 1 semi-ton
// Nas demais há 2 semi-tons
int distanceNotes(char x, char y){
    int result=0;
    if (x == y){
        return result;
    }else{
        int i=0;
        int j;
        while(notes[i] != x){i++;}

        j = i;

        while(notes[j] != y )
        {
            j = (j + 1 ) % 7;
            if(notes[j] == 'C' || notes[j] == 'F'){
                result++;
            }else{
                result = result + 2;
            }
        }
    }
    return result;
}

void computeLPSArray(char* pat, int M, int* lps);

int  KMPSearch(char* pat, char* txt)
{
    int M = strlen(pat);
    int N = strlen(txt);
    int lps[M];

    computeLPSArray(pat, M, lps);

    int i = 0;  
    int j = 0; 
    while ((N - i) >= (M - j)) {
        if (pat[j] == txt[i]) {
            j++;
            i++;
        }

        if (j == M) {
            return 1;
            j = lps[j - 1];
        }

        else if (i < N && pat[j] != txt[i]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }
    return 0;
}

// Vetor auxiliar de KMP
 void computeLPSArray(char* pat, int M, int* lps)
{
     int len = 0;

    lps[0] = 0;  

    int i = 1;
    while (i < M) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        }
        else 
        {

            if (len != 0) {
                len = lps[len - 1];
            }
            else 
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// Ler as notas e retorna uma string com os intervalos
// entre notas, podemos assim, identificar a melodia
char * strParser(char* strInput, int m){
    m = strlen(strInput);
    char * newStr = (char*) malloc(sizeof (char) * m);
    int  aux, i, j;
    j=0;
    for(i=0; i < (m - 3) ; i++){
        if( (strInput[i+1] == '\0')  || (strInput[i+2] == '\0')  ) {
            break;
        }
        if((strInput[i] != ' ') && (strInput[i+1] == ' ')) {
            if ((strInput[i]!= '#' && strInput[i]!='b')){
                aux = 0;
                aux = distanceNotes(strInput[i], strInput[i+2]);
                if(strInput[i+3] != ' '){
                    if (strInput[i+3] == 'b'){
                        aux--;
                    }else if (strInput[i+3] == '#') {
                        aux++;
                    }
                }
                newStr[j] = aux+'0';
                j++;
                }
        }else if((strInput[i]!= ' ') && (strInput[i+1] == 'b' || strInput[i+1] =='#' )){
            aux = 0;
            aux = distanceNotes(strInput[i], strInput[i + 3]);
            strInput[i+1] == '#' ? aux-- : aux++;
            if(strInput[i+4] != ' '){
                if (strInput[i+4] == 'b'){
                    aux--;

                }else if (strInput[i+4] == '#') {
                    aux++;
                }
            }
            newStr[j] = aux+'0';
            j++;
        }

    }
    newStr[j] = '\0';
    return newStr;

}


int main()
{

    int m, n;
    scanf("%d %d \n", &m, &n);

    while(m && n) {
        printf("m n = %d %d", m, n);
        fgets(txt, m*3,  stdin);
        fgets(pat, n*3,  stdin);
        char * paramTxt = strParser(txt, m*3);
        char * paramPat = strParser(pat, n*3);
        printf("\n%c", KMPSearch(paramPat, paramTxt) ? 'S': 'N');
        scanf("%d %d \n", &m, &n);
        if(m==0 && n==0){
            break;
        }else{
            continue;
        }

    }

    return 0;
}
