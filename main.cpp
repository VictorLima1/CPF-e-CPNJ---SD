#include <future>
#include <mutex>
#include <iostream>
#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

void calculaCNPJ(string *cnpj){
    int soma = 0, mult = 5;

    for(int i = 0; i < 12; i++){
        soma = soma + ((cnpj -> at(i) - '0') * mult);
        mult--;
        if(mult < 2)
            mult = 9;
    }

    int num = 11 - (soma % 11);

    if(num >= 10)
        num = 0;

    string s(1, num + '0');

    cnpj -> append(s);

    mult = 6, soma = 0;

    for(int i = 0; i < 13; i++){
        soma = soma + ((cnpj -> at(i) - '0') * mult);
        mult--;
        if(mult < 2)
            mult = 9;
    }

    num = 11 - (soma % 11);

    if(num >= 10)
        num = 0;

    string t(1, num + '0');

    cnpj -> append(t);
}

void calculaCPF(string *cpf){
    int soma = 0, mult = 11;

    for(int i = 3; i < 12; i++){
        soma = soma + ((cpf -> at(i) - '0') * (mult - 1));
        mult--;
    }
    
    int num = 11 - (soma % 11);

    if(num >= 10)
        num = 0;

    string s(1, num + '0');

    cpf -> append(s);

    mult = 11, soma = 0;

    for(int i = 3; i < 13; i++){
        soma = soma + ((cpf -> at(i) - '0') * (mult));
        mult--;
    }

    num = 11 - (soma % 11);

    if(num >= 10)
        num = 0;

    string t(1, num + '0');

    cpf -> append(t);
}

int main()
{
    string numero;
    int cnpjcont = 0, cpfcont = 0;
    static string cpf[600000], cnpj[600000];
    ifstream myfile ("BASEPROJETO.txt");
    if (myfile.is_open())
    {
        while ( getline (myfile,numero) )
        {
            char primeiro = numero.at(0);
            if(primeiro >= '0' && primeiro <= '9'){
                cnpj[cnpjcont] = numero;
                cnpjcont++;
            }
            else{
                cpf[cpfcont] = numero;
                cpfcont++;
            }

        }
        myfile.close();
    }

    auto t_start = std::chrono::high_resolution_clock::now();
    
    for(int i = 0; i < 600000; i++){
        auto h1 = std::async(std::launch::async, calculaCNPJ, &cnpj[i]);
        auto h2 = std::async(std::launch::async, calculaCPF, &cpf[i]);
    
        h1.get(), h2.get();
    }

    auto t_end = std::chrono::high_resolution_clock::now();
    printf("Tempo de execução: %.2f segundos\n", (std::chrono::duration<double, std::milli>(t_end-t_start).count())/1000);

    ofstream saida ("CALCULADOS.txt");
    if (saida.is_open())
    {
        for(int i = 0; i < 600000; i++)
            saida << cpf[i] << endl;
            
        for(int i = 0; i < 600000; i++)
            saida << cnpj[i] << endl;

        saida.close();
    }

    return 0;
}