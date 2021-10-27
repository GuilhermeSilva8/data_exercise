#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

// estrutura criada para armazenar os dados dos campos do arquivo
struct medicamento{
    string substancia;
    string CNPJ;
    string laboratorio;
    string GGREM;
    string registro;
    string EAN1;
    string EAN2;
    string EAN3;
    string produto;
    string apresentacao;
    string classeTerapeutica;
    string statusProduto;
    string regimePreco;
    float  PFSemImposto;
    float  PF0;
    float  PF12;
    float  PF17;
    float  PF17ALC;
    float  PF175;
    float  PF175ALC;
    float  PF18;
    float  PF18ALC;
    float  PF20;
    float  PMC0;
    float  PMC12;
    float  PMC17;
    float  PMC17ALC;
    float  PMC175;
    float  PMC175ALC;
    float  PMC18;
    float  PMC18ALC;
    float  PMC20;
    string restricaoHospitalar;
    string CAP;
    string CONFAZ87;
    string ICMS0;
    string analiseRecursal;
    string listaCCT;
    string comercializacao2020;
    string tarja;
};

// função que printa no console o nome dos campos do arquivo
void printaCampos(string linha){
    string buf; // variavel que irá receber as palavras da linha
    stringstream ss(linha); // transforma a string em stream para acessar palavra por palavra separadamente
    cout << "Campos do arquivo:" << endl;
    cout << "| ";
    while (getline(ss, buf, ',')){ // enquanto houver palavras na linha separadas por vírgula, executa o loop
        if(buf.find("\"") != -1){ // condicional para tratar o caso dos números que também são separados por vírgula e iriam dar origem a um novo campo de forma errada se não houvesse esse tratamento
            string auxBuf;
            getline(ss, auxBuf, ',');
            buf[0] = ' ';
            auxBuf[auxBuf.size()-1] = ' ';
            cout << buf << "," << auxBuf << " | ";
        }else{
            cout << buf << " | ";
        }
    }
    cout << endl;
}

// função para ler o arquivo .csv e armazenar na estrutura medicamento
void lerArquivo(){
    ifstream arq; // declaração de variavel para entrada do arquivo
    arq.open("TA_PRECO_MEDICAMENTO.csv"); // abertura do arquivo
    if(!arq.is_open()) // teste para certificar que o arquivo abriu corretamente
        cout << "Erro ao tentar abrir arquivo!" << endl;
    else{
        string linha; // irá receber as linhas que forem lidas do arquivo
        getline(arq, linha); // le a primeira linha que corresponde ao nome dos campos do arquivo
        printaCampos(linha); // mostra no console o nome dos campos

    }

}

int main(){
    SetConsoleOutputCP(65001); // funcionalidade da biblioteca Windows.h que permite que o console trate os dados com utf-8 que é o formato dos caracteres do arquivo .csv

    lerArquivo();

    return 0;
}