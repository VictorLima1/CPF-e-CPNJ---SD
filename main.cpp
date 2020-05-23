#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <chrono>
#include <ctime>

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

    /*FILE *fo;
    fo = fopen ("CNPJ.txt", "a");

	for(int j = 0; j < 14; j++)
	   fprintf(fo, "%c", cnpj[j]); 

    fprintf(fo,"\n");

    fclose(fo);*/

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

    pthread_t threads[4]; 
    static char temp[1200000][13], cpf[600000][13], cnpj[600000][14];

    int linhacnpj = 0, linhacpf = 0;

    for(int l = 0; l < 1200000; l++){
        for(int c = 0; c < 13; c++)
            fscanf(fp, "%c", temp[l]+c);
    }

    fclose(fp);

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

    /*thread t1(calculaCPF, cpf[0]);
    t1.join();*/

    std::clock_t c_start = std::clock();
    auto t_start = std::chrono::high_resolution_clock::now();

    for(int i = 0; i < 75000; i++){
        //thread th1(calculaCPF[i], 1);
        //printf("%d\n", i);
        thread t1(calculaCPF, cpf[i]);
        thread t3(calculaCPF, cpf[i + 75000]);
        thread t5(calculaCPF, cpf[i + 150000]);
        thread t7(calculaCPF, cpf[i + 225000]);
        thread t9(calculaCPF, cpf[i + 300000]);
        thread t11(calculaCPF, cpf[i + 375000]);
        thread t13(calculaCPF, cpf[i + 450000]);
        thread t15(calculaCPF, cpf[i + 525000]);

        //calculaCPF(cpf[i]);
        //thread th2(calculaCNPJ, 2); 
        thread t2(calculaCNPJ, cnpj[i]);
        thread t4(calculaCNPJ, cnpj[i + 75000]);
        thread t6(calculaCNPJ, cnpj[i + 150000]);
        thread t8(calculaCNPJ, cnpj[i + 225000]);
        thread t10(calculaCNPJ, cnpj[i + 300000]);
        thread t12(calculaCNPJ, cnpj[i + 375000]);
        thread t14(calculaCNPJ, cnpj[i + 450000]);
        thread t16(calculaCNPJ, cnpj[i + 525000]);

        t1.join();
        t2.join();
        t3.join();
        t4.join();
        t5.join();
        t6.join();
        t7.join();
        t8.join();
        t9.join();
        t10.join();
        t11.join();
        t12.join();
        t13.join();
        t14.join();
        t15.join();
        t16.join();
        //calculaCNPJ(cnpj[i]);
    }


    
    FILE *fo;
    fo = fopen ("CALCULADOS.txt", "w+");

    for(int i = 0; i < 600000; i++){
	    for(int j = 0; j < 11; j++){
	        fprintf(fo, "%c", cpf[i][j]);
            //printf("%c", cpf[i][j]);
	    }

        fprintf(fo,"\n", cpf[i][13]);
	}

    std::clock_t c_end = std::clock();
    auto t_end = std::chrono::high_resolution_clock::now();
    printf("%f", (std::chrono::duration<double, std::milli>(t_end-t_start).count())/1000);


    return 0;
}