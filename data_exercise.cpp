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
    cout << "\n\n";
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
    arq.close(); // fechamento do arquivo
}

// função que imprime na tela o produto com maior PF sem impostos
void maiorPF(vector<struct medicamento> m){
    vector<string> maior = {}; // vetor para armazenar o maior ou os maiores produtos
    float maiorPF = m[0].PFSemImposto; // variavel que armazenará o maior preço e inicialmente será o preço do primeiro produto
    maior.push_back(m[0].produto); // atribui como maior o primeiro produto

    // loop para percorrer todos os produtos
    for(int i = 1; i < m.size(); i++){
        
        //testa se o produto atual tem maior preço
        if(m[i].PFSemImposto > maiorPF){
            maior = {}; // atribui vazio pois pode ter mais de um elemento com valor maior que será substituído pelo novo maior
            maiorPF = m[i].PFSemImposto; // valor do maiorPF é atualizado
            maior[0] = m[i].produto; // nome do maior produto é atualizado
        }else if(m[i].PFSemImposto == maiorPF){ // testa se o produto tem valor igual ao maior para adicionar a lista de maiores caso não seja um produto que já foi guardado
                int flag = 0; // variável que irá servir para testar se o produto já pertence a lista
                for(int j = 0; j < maior.size(); j++){ // loop para percorrer o(s) maiores produtos e verificar se o atual já consta na lista
                    if(maior[j] == m[i].produto){
                        flag++;
                    }
                }
                if(flag == 0){ // se o produto não foi encontrado
                    maior.push_back(m[i].produto); // adiciona na lista de maiores produtos
                }
        }
    }
    
    // imprime o(s) maior(es) produto(s)
    cout << "Produto(s) com maior(es) PF sem impostos: " << endl;
    for(int i = 0; i < maior.size(); i++){
        cout << maior[i] << endl;
    }

    cout << "\n";
}

//função que imprime na tela os possíveis tipos de produtos
void tiposProdutos(vector<struct medicamento> m){
    
    vector<string> tipos = {}; // vetor que irá armazenar os tipos que já foram printados
    tipos.push_back(m[0].statusProduto); // coloca no vetor o tipo do primeiro produto
    cout << "Tipos de produtos:" << endl;
    cout << "| " << tipos[0] << " | "; // imprime o primeiro tipo de produto

    // loop para percorrer todos os medicamentos e imprimir na tela o tipo caso ainda não tenha sido printado
    for(int i = 1; i < m.size(); i++){
        string tipoAtual = m[i].statusProduto;
        int flag = 0;
        for(int j = 0; j < tipos.size(); j++){
            if(tipoAtual == tipos[j]){ // se já está na lista
                flag++;
                break;
            }
        }
        // caso não tenha sido encontrado na lista
        if(flag == 0){
            tipos.push_back(tipoAtual); // adiciona no vetor de já impressos
            cout <<  tipoAtual << " | "; // imprime na tela o tipo
        }
    }
    cout << "\n\n";
}

// função que imprime no console o nome e preço do genérico mais barato
void genericoBarato(vector<struct medicamento> m){
    // loop para achar o primeiro generico e setar o preço deste como o menor
    int primeiro;
    float menor;
    string nomeProduto;
    for(primeiro = 0; primeiro < m.size(); primeiro++){
        if(m[primeiro].statusProduto == "Genérico"){
            break;
        }
    }
    menor = m[primeiro].PFSemImposto;
    nomeProduto = m[primeiro].produto;

    // começa o loop a partir do próximo elemento e caso seja genérico e tenha preço menor, os valores são atualizados
    for(int i = primeiro + 1; i < m.size(); i++){
        if(m[i].statusProduto == "Genérico" && m[i].PFSemImposto < menor){
            menor = m[i].PFSemImposto;
            nomeProduto = m[i].produto;
        }
    }

    // imprime o produto e o preço do genérico mais barato
    cout << "Genérico mais barato é: " << nomeProduto << " e custa: R$ " << menor << "\n\n";
}

// função que salva todos os registros com o preço final sem impostos superior a ‘100’, com comercialização 2018 marcada como ‘Sim’ e que sejam Tarja Vermelha em um arquivo chamado “output.csv”
void salvaRegistros(vector<struct medicamento> m){
   
    ofstream registro; // cria variavel de arquivo de saída
    registro.open("output.csv"); // abre o arquivo
    // loop para percorrer os registros e armazenar no arquivo de saída caso atenda as condições
    for(int i = 0; i < m.size(); i++){
        if(m[i].PFSemImposto > 100 && m[i].comercializacao2020 == "Sim" && m[i].tarja == "Tarja  Vermelha"){
            if(m[i].substancia.find(",") != -1){
                registro << "\"";
                registro << m[i].substancia;
                registro << "\"";
                registro << ",";
            }else registro << m[i].substancia << ",";
            
            registro << m[i].CNPJ << ",";

            if(m[i].laboratorio.find(",") != -1){
                registro << "\"";
                registro << m[i].laboratorio;
                registro << "\"";
                registro << ",";
            }else registro << m[i].laboratorio << ",";
            
            registro << m[i].GGREM << ",";
            registro << m[i].registro << ",";
            registro << m[i].EAN1 << ",";
            registro << m[i].EAN2 << ",";
            registro << m[i].EAN3 << ",";

            if(m[i].produto.find(",") != -1){
                registro << "\"";
                registro << m[i].produto;
                registro << "\"";
                registro << ",";
            }else registro << m[i].produto << ",";
            
            if(m[i].apresentacao.find(",") != -1){
                registro << "\"";
                registro << m[i].apresentacao;
                registro << "\"";
                registro << ",";
            }else registro << m[i].apresentacao << ",";
            
            if(m[i].classeTerapeutica.find(",") != -1){
                registro << "\"";
                registro << m[i].classeTerapeutica;
                registro << "\"";
                registro << ",";
            }else registro << m[i].classeTerapeutica << ",";
            
            registro << m[i].statusProduto << ",";
            registro << m[i].regimePreco << ",";

            registro << m[i].PFSemImposto << ",";
            registro << m[i].PF0 << ",";
            registro << m[i].PF12 << ",";
            registro << m[i].PF17 << ",";
            registro << m[i].PF17ALC << ",";
            registro << m[i].PF175 << ",";                     
            registro << m[i].PF175ALC << ",";          
            registro << m[i].PF18 << ",";
            registro << m[i].PF18ALC << ",";
            registro << m[i].PF20 << ",";
            registro << m[i].PMC0 << ",";
            registro << m[i].PMC12 << ",";
            registro << m[i].PMC17 << ",";
            registro << m[i].PMC17ALC << ",";
            registro << m[i].PMC175 << ",";
            registro << m[i].PMC175ALC << ",";
            registro << m[i].PMC18 << ",";
            registro << m[i].PMC18ALC << ",";
            registro << m[i].PMC20 << ",";

            registro << m[i].restricaoHospitalar << ",";
            registro << m[i].CAP << ",";
            registro << m[i].CONFAZ87 << ",";
            registro << m[i].ICMS0 << ",";
            registro << m[i].analiseRecursal << ",";
            registro << m[i].listaCCT << ",";
            registro << m[i].comercializacao2020 << ",";
            registro << m[i].tarja << "\n";
        }  
    }
    registro.close(); // fecha o arquivo
}

// função que coloca os dados nos seus respectivos campos da estrutura
void armazenaOutput(vector<struct medicamento> &m, string linha){
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

    // atribuições de número float
    getline(ss, buf, ',');
    novo.PFSemImposto = stof(buf);
    getline(ss, buf, ',');
    novo.PF0 = stof(buf);
    getline(ss, buf, ',');
    novo.PF12 = stof(buf);
    getline(ss, buf, ',');
    novo.PF17 = stof(buf);
    getline(ss, buf, ',');
    novo.PF17ALC = stof(buf);
    getline(ss, buf, ',');
    novo.PF175 = stof(buf);
    getline(ss, buf, ',');
    novo.PF175ALC = stof(buf);
    getline(ss, buf, ',');
    novo.PF18 = stof(buf);
    getline(ss, buf, ',');
    novo.PF18ALC = stof(buf);
    getline(ss, buf, ',');
    novo.PF20 = stof(buf);
    getline(ss, buf, ',');
    novo.PMC0 = stof(buf);
    getline(ss, buf, ',');
    novo.PMC12 = stof(buf);
    getline(ss, buf, ',');
    novo.PMC17 = stof(buf);
    getline(ss, buf, ',');
    novo.PMC17ALC = stof(buf);
    getline(ss, buf, ',');
    novo.PMC175 = stof(buf);
    getline(ss, buf, ',');
    novo.PMC175ALC = stof(buf);
    getline(ss, buf, ',');
    novo.PMC18 = stof(buf);
    getline(ss, buf, ',');
    novo.PMC18ALC = stof(buf);  
    getline(ss, buf, ',');
    novo.PMC20 = stof(buf);
    
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
void lerOutput(vector<struct medicamento> &m){
    ifstream arq; // declaração de variavel para entrada do arquivo
    arq.open("output.csv"); // abertura do arquivo
    if(!arq.is_open()) // teste para certificar que o arquivo abriu corretamente
        cout << "Erro ao tentar abrir arquivo!" << endl;
    else{
        string linha; // irá receber as linhas que forem lidas do arquivo
        getline(arq, linha); // le a primeira linha que corresponde ao nome dos campos do arquivo
        while(getline(arq, linha)){ // enquanto houver linhas no arquivo executa o loop
            armazenaOutput(m, linha); // coloca os valores nos respectivos campos da estrutura
        }
    }
    arq.close(); // fechamento do arquivo
}


int main(){
    SetConsoleOutputCP(65001); // funcionalidade da biblioteca Windows.h que permite que o console trate os dados com utf-8 que é o formato dos caracteres do arquivo .csv

    vector<struct medicamento> m = {};

    lerArquivo(m);
    maiorPF(m);
    tiposProdutos(m);
    genericoBarato(m);
    salvaRegistros(m);

    vector<struct medicamento> m2 = {};
    lerOutput(m2);

    return 0;
}