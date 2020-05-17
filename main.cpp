#include <stdio.h>
#include <stdlib.h>

using namespace std;

void calculaCPF(char cpf[12]){
    int soma = 0, mult = 11;
    char digito[2];
    
    for(int i = 0; i < 9; i++){
        soma = soma + ((cpf[i] - '0') * (mult - 1));
        mult--;
    }    
   
    if((11 - (soma%11)) <= 10)
        digito[0] = '0' + (11 - (soma%11));
    else
        digito[0] = 32;

    soma = 0;
    mult = 11;

    for(int i = 0; i < 9; i++){
        soma = soma + ((cpf[i] - '0') * (mult));
        mult--;
    }

    soma = soma + ((digito[0] - '0') * 2);

    for(int i = 0; i < 12; i++)
        printf("%c", cpf[i]);

    printf(" ");

    if((11 - (soma%11)) <= 10)
        digito[1] = '0' + (11 - (soma%11));
    else
        digito[1] = 32;

    printf("%c%c", digito[0], digito[1]);
}

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
            for(int c = 0; c < 10; c++)
                cpf[linhacpf][c] = temp[l][c+3];

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
            for(int c = 0; c < 10; c++)
                cpf[linhacpf][c] = temp[l][c+3];

            linhacpf++;
        }
    }

    for(int i = 0; i < 600000; i++){
        calculaCPF(cpf[i]);
        printf("\n");
    }

    
    return 0;
}