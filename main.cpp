#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main(){
    FILE *fp;
    fp = fopen ("BASEPROJETO.txt", "r");
    static char temp[600000][13], cpf[600000][12], cnpj[600000][14];
    char numero;

    int linhacnpj = 0, linhacpf = 0;

    for(int l = 0; l < 600000; l++){
        for(int c = 0; c < 13; c++)
            fscanf(fp, "%c", temp[l]+c);

    }

    for(int l = 0; l < 600000; l++){
        if(temp[l][0] >= '0' && temp[l][0] <= '9'){
            for(int c = 0; c < 13; c++)
                cnpj[linhacnpj][c] = temp[l][c];

            linhacnpj++;
        }
        else{
            for(int c = 0; c < 13; c++)
                cpf[linhacpf][c] = temp[l][c];

            linhacpf++;
        }
    }

    for(int l = 0; l < 600000; l++){
        for(int c = 0; c < 13; c++)
            fscanf(fp, "%c", temp[l]+c);

    }

    for(int l = 0; l < 600000; l++){
        if(temp[l][0] >= '0' && temp[l][0] <= '9'){
            for(int c = 0; c < 13; c++)
                cnpj[linhacnpj][c] = temp[l][c];

            linhacnpj++;
        }
        else{
            for(int c = 0; c < 13; c++)
                cpf[linhacpf][c] = temp[l][c];

            linhacpf++;
        }
    }

    for(int i = 0; i < 600000; i++){
        for(int c = 0; c < 13; c++)
            printf("%c", cnpj[i][c]);
        
        printf("\n");
    }

    
    return 0;
}