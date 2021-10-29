#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>
#include <typeinfo>

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

// função que transforma a string entre aspas em numeros float
float trataNumero(string buf, stringstream &ss){
    string auxBuf;
    getline(ss, auxBuf, ',');
    buf[0] = ' ';
    auxBuf[auxBuf.size()-1] = ' ';

    float n1 = stof(buf); // transforma a primeira string em float
    float n2 = stof(auxBuf); // transforma a segunda string em float
    int aux = n2; // armazena o valor do segundo número para usar na transformação em decimal

    // armazena em s o número de casas decimais do número
    int s = 0;
    do{
        aux /= 10;
        s++;
    } while(aux != 0);
    n2 = n2 / pow(10, s); // transforma n2 em decimal

    return n1 + n2; // retorna o valor completo do campo em float
    
}

// função que coloca os dados nos seus respectivos campos da estrutura
void armazenaEstrutura(vector<struct medicamento> &m, string linha){
    struct medicamento novo; // cria a estrutura que receberá todos os dados da linha
    string buf; // variavel que irá receber as palavras da linha
    stringstream ss(linha); // transforma a string em stream para acessar palavra por palavra separadamente

    // pega a informação de cada campo e armazena na estrutura

    // necessário criar condição para o caso de as existir substância com seus componentes divididos por vírgula
    getline(ss, buf, ',');
    if(buf.find("\"") != -1){ 
        string auxBuf;
        getline(ss, auxBuf, '\"'); // pega o resto do contéudo
        buf[0] = ' ';
        novo.substancia = buf + ',' + auxBuf; // junta o conteúdo existente antes da primeira e após a primeira vírgula
        getline(ss, buf, ','); // elimina a vírgula que divide esse do próximo
    }else{
        novo.substancia = buf;
    }
    
    // atribuição sem condições especiais
    getline(ss, buf, ',');
    novo.CNPJ = buf;

    // necessário verificar se existe nome de laboratório separado por vírgula
    getline(ss, buf, ',');
    if(buf.find("\"") != -1){ 
        string auxBuf;
        getline(ss, auxBuf, '\"'); // pega o resto do contéudo
        buf[0] = ' ';
        novo.laboratorio = buf + ',' + auxBuf; // junta o conteúdo existente antes da primeira e após a primeira vírgula
        getline(ss, buf, ','); // elimina a vírgula que divide esse do próximo
    }else{
        novo.laboratorio = buf;
    }

    // atribuições sem condições especiais

    getline(ss, buf, ',');
    novo.GGREM = buf;
    getline(ss, buf, ',');
    novo.registro = buf;
    getline(ss, buf, ',');
    novo.EAN1 = buf;
    getline(ss, buf, ',');
    novo.EAN2 = buf;
    getline(ss, buf, ',');
    novo.EAN3 = buf;

    // necessário criar uma condição caso o produto, apresentação ou classe terapêutica contenham valores decimais(com vírgula)
    getline(ss, buf, ',');
    if(buf.find("\"") != -1){ 
        string auxBuf;
        getline(ss, auxBuf, '\"'); // pega o resto do contéudo
        buf[0] = ' ';
        novo.produto = buf + ',' + auxBuf; // junta o conteúdo existente antes da primeira e após a primeira vírgula
        getline(ss, buf, ','); // elimina a vírgula que divide esse do próximo
    }else{
        novo.produto = buf;
    }

    getline(ss, buf, ',');
    if(buf.find("\"") != -1){ 
        string auxBuf;
        getline(ss, auxBuf, '\"'); // pega o resto do contéudo
        buf[0] = ' ';
        novo.apresentacao = buf + ',' + auxBuf; // junta o conteúdo existente antes da primeira e após a primeira vírgula
        getline(ss, buf, ','); // elimina a vírgula que divide esse do próximo
    }else{
        novo.apresentacao = buf;
    }

    getline(ss, buf, ',');
    if(buf.find("\"") != -1){ 
        string auxBuf;
        getline(ss, auxBuf, '\"'); // pega o resto do contéudo
        buf[0] = ' ';
        novo.classeTerapeutica = buf + ',' + auxBuf; // junta o conteúdo existente antes da primeira e após a primeira vírgula
        getline(ss, buf, ','); // elimina a vírgula que divide esse do próximo
    }else{
        novo.classeTerapeutica = buf;
    }

    // atribuições sem condições especiais
    getline(ss, buf, ',');
    novo.statusProduto = buf;
    getline(ss, buf, ',');
    novo.regimePreco = buf;
    getline(ss, buf, ',');
    novo.PFSemImposto = trataNumero(buf, ss);
    
    // necessário criar condições para verificar se os valores de PF e PMC não são vazios
    getline(ss, buf, ',');
    if(buf.length() == 0){
        novo.PF0 = 0;
    }else{
        novo.PF0 = trataNumero(buf, ss);
    }

    getline(ss, buf, ',');
    if(buf.length() == 0){
        novo.PF12 = 0;
    }else{
        novo.PF12 = trataNumero(buf, ss);
    }

    getline(ss, buf, ',');
    if(buf.length() == 0){
        novo.PF17 = 0;
    }else{
        novo.PF17 = trataNumero(buf, ss);
    }

    getline(ss, buf, ',');
    if(buf.length() == 0){
        novo.PF17ALC = 0;
    }else{
        novo.PF17ALC = trataNumero(buf, ss);
    }

    getline(ss, buf, ',');
    if(buf.length() == 0){
        novo.PF175 = 0;
    }else{
        novo.PF175 = trataNumero(buf, ss);
    }

    getline(ss, buf, ',');
    if(buf.length() == 0){
        novo.PF175ALC = 0;
    }else{
        novo.PF175ALC = trataNumero(buf, ss);
    }

    getline(ss, buf, ',');
    if(buf.length() == 0){
        novo.PF18 = 0;
    }else{
        novo.PF18 = trataNumero(buf, ss);
    }

    getline(ss, buf, ',');
    if(buf.length() == 0){
        novo.PF18ALC = 0;
    }else{
        novo.PF18ALC = trataNumero(buf, ss);
    }

    getline(ss, buf, ',');
    if(buf.length() == 0){
        novo.PF20 = 0;
    }else{
        novo.PF20 = trataNumero(buf, ss);
    }

    getline(ss, buf, ',');
    if(buf.length() == 0){
        novo.PMC0 = 0;
    }else{
        novo.PMC0 = trataNumero(buf, ss);
    }

    getline(ss, buf, ',');
    if(buf.length() == 0){
        novo.PMC12 = 0;
    }else{
        novo.PMC12 = trataNumero(buf, ss);
    }

    getline(ss, buf, ',');
    if(buf.length() == 0){
        novo.PMC17 = 0;
    }else{
        novo.PMC17 = trataNumero(buf, ss);
    }

    getline(ss, buf, ',');
    if(buf.length() == 0){
        novo.PMC17ALC = 0;
    }else{
        novo.PMC17ALC = trataNumero(buf, ss);
    }

    getline(ss, buf, ',');
    if(buf.length() == 0){
        novo.PMC175 = 0;
    }else{
        novo.PMC175 = trataNumero(buf, ss);
    }

    getline(ss, buf, ',');
    if(buf.length() == 0){
        novo.PMC175ALC = 0;
    }else{
        novo.PMC175ALC = trataNumero(buf, ss);
    }

    getline(ss, buf, ',');
    if(buf.length() == 0){
        novo.PMC18 = 0;
    }else{
        novo.PMC18 = trataNumero(buf, ss);
    }

    getline(ss, buf, ',');
    if(buf.length() == 0){
        novo.PMC18ALC = 0;
    }else{
        novo.PMC18ALC = trataNumero(buf, ss);
    }

    getline(ss, buf, ',');
    if(buf.length() == 0){
        novo.PMC20 = 0;
    }else{
        novo.PMC20 = trataNumero(buf, ss);
    }
    
    // atribuições sem condições especiais
    getline(ss, buf, ',');
    novo.restricaoHospitalar = buf;
    getline(ss, buf, ',');
    novo.CAP = buf;
    getline(ss, buf, ',');
    novo.CONFAZ87 = buf;
    getline(ss, buf, ',');
    novo.ICMS0 = buf;
    getline(ss, buf, ',');
    novo.analiseRecursal = buf;
    getline(ss, buf, ',');
    novo.listaCCT = buf;
    getline(ss, buf, ',');
    novo.comercializacao2020 = buf;
    getline(ss, buf, ',');
    novo.tarja = buf;

    // adiciona a linha no conjunto
    m.push_back(novo);
}

// função para ler o arquivo .csv e armazenar na estrutura medicamento
void lerArquivo(vector<struct medicamento> &m){
    ifstream arq; // declaração de variavel para entrada do arquivo
    arq.open("TA_PRECO_MEDICAMENTO.csv"); // abertura do arquivo
    if(!arq.is_open()) // teste para certificar que o arquivo abriu corretamente
        cout << "Erro ao tentar abrir arquivo!" << endl;
    else{
        string linha; // irá receber as linhas que forem lidas do arquivo
        getline(arq, linha); // le a primeira linha que corresponde ao nome dos campos do arquivo
        printaCampos(linha); // mostra no console o nome dos campos
        while(getline(arq, linha)){ // enquanto houver linhas no arquivo executa o loop
            armazenaEstrutura(m, linha); // coloca os valores nos respectivos campos da estrutura
        }
    }
}

int main(){
    SetConsoleOutputCP(65001); // funcionalidade da biblioteca Windows.h que permite que o console trate os dados com utf-8 que é o formato dos caracteres do arquivo .csv

    vector<struct medicamento> m = {};

    lerArquivo(m);

    return 0;
}