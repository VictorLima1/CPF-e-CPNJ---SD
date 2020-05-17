#include <stdio.h>
#include <stdlib.h>

using namespace std;

void calculaCNPJ(char *cnpj){
    int soma = 0, mult = 5;

    for(int i = 0; i < 12; i++){
        //int num = cpf[i] - '0';
        soma = soma + ((cnpj[i] - '0') * mult);
        mult--;
        if(mult < 2)
            mult = 9;
    }

    int num = 11 - (soma % 11);

    if(num >= 10)
        num = 0;

    cnpj[12] = num + '0';

    mult = 6, soma = 0;

    for(int i = 0; i < 13; i++){
        //int num = cpf[i] - '0';
        soma = soma + ((cnpj[i] - '0') * mult);
        mult--;
        if(mult < 2)
            mult = 9;
    }

    num = 11 - (soma % 11);

    if(num >= 10)
        num = 0;

    cnpj[13] = num + '0';

    //printf("O segundo digito é: %d", num);
}

void calculaCPF(char* cpf){
    int soma = 0, mult = 11;

    for(int i = 0; i < 9; i++){
        //int num = cpf[i] - '0';
        soma = soma + ((cpf[i] - '0') * (mult - 1));
        mult--;
    }
    
    int num = 11 - (soma % 11);

    if(num >= 10)
        num = 0;

    mult = 11, soma = 0;
    
    cpf[9] = num + '0';

    for(int i = 0; i < 10; i++){
        //int num = cpf[i] - '0';
        soma = soma + ((cpf[i] - '0') * (mult));
        mult--;
    }

    num = 11 - (soma % 11);
    if(num >= 10)
        num = 0;

    cpf[10] = num + '0';
}

int main(){
    FILE *fp;
    fp = fopen ("BASEPROJETO.txt", "r");
    static char temp[1200000][13], cpf[600000][13], cnpj[600000][14];

    int linhacnpj = 0, linhacpf = 0;

    for(int l = 0; l < 1200000; l++){
        for(int c = 0; c < 13; c++)
            fscanf(fp, "%c", temp[l]+c);
    }

    for(int l = 0; l < 1200000; l++){
        if(temp[l][0] >= '0' && temp[l][0] <= '9'){
            for(int c = 0; c < 13; c++){
                cnpj[linhacnpj][c] = temp[l][c];
            }

            linhacnpj++;
        }
        else{
            for(int c = 3; c < 13; c++){
                cpf[linhacpf][c - 3] = temp[l][c];
            }

            linhacpf++;
        }
    }
    
    for(int i = 0; i < 600000; i++){
        calculaCPF(cpf[i]);
        calculaCNPJ(cnpj[i]);
    }

    for(int i = 0; i < 600000; i++){
        for(int j = 0; j < 14; j++)
            printf("%c", cnpj[i][j]);

        printf("\n");
    }

    return 0;
}