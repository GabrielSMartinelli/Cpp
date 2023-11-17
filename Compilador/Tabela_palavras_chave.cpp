#include<iostream>
#include "palavra_reservada.cpp"

using namespace std;

#ifndef FUNCAOHASH
#define FUNCAOHASH


const int PRIMO = 37;


int funcaoHash(string s, int M){
    long h = 0;
    for(unsigned i = 0; i<s.length(); i++){
        h = (PRIMO * h + s[i]) % M;
    }
    return h;
}
#endif

#ifndef TABELACHAVES
#define TABELACHAVES

class TabelaChave{

    public:
        TabelaChave();
        ~TabelaChave();

        string recupera(string cadeia);
        void percorre();



    private:
        void inserirPalavrasChave();
        PalavraReservada** elementos; //Define um vetor de ponteiros para os elementos na tabela de simbolos
        int capacidade = 50; //Vai ditar a capacidade da tabela de simbolos
        void insere(std::string cadeia, std::string categoria, std::string tipo);
        void remove(string cadeia);

};

TabelaChave::TabelaChave(){
    elementos = new PalavraReservada*[capacidade];   //define elementos como um vetor de ponteiros de capacidade igual a passada no construtor

    for (int i = 0; i < capacidade; i++){  //Vai inicializar todas as posicoes da tabela como null
        elementos[i] = NULL;
    }
    inserirPalavrasChave();
}

TabelaChave::~TabelaChave(){
     for (int i = 0; i < capacidade; ++i){  //Percorre toda a tabela hash
        PalavraReservada *atual = elementos[i];
        while(atual != NULL){
            PalavraReservada* aux = atual;
            atual = atual->prox;    //Percorre recursivamente todos os elementos da fila
            delete(aux);            //Deleta todos do ultimo ate o comeco
        }
     }
     delete[] elementos;            //libera a memoria do vetor de ponteiros da tabela
}

void TabelaChave::insere(std::string cadeia, std::string categoria, std::string tipo){
    string aux = cadeia;    //A funcao hash eh calculada pela cadeia da palavra chave
    int hash = funcaoHash(aux, capacidade);

    if(recupera(aux)=="NAO ENCONTRADO"){    //se nao encontra o id na tabela, insere um novo
        if(elementos[hash] == NULL){        //Se na posicao nao tiver nada, insere um novo
            elementos[hash] = new PalavraReservada(cadeia, categoria, tipo);
        }
        else{                               //Se ja houver um elemento naquela posicao, percorre toda a lista ligada para inserir o novo token no final dela
            //cout<<"Colidiu: "<< aux << endl;
            PalavraReservada* atual = elementos[hash];
            while(atual->prox != NULL){
                atual = atual->prox;
            }
            PalavraReservada* novo = new PalavraReservada(cadeia, categoria, tipo);
            atual->prox = novo;
        }
    }
    else{
    }
}

string TabelaChave::recupera(string cadeia){
    string aux = cadeia;
    int hash = funcaoHash(aux, capacidade);
    if (elementos[hash] != NULL && elementos[hash]->cadeia == cadeia){  //Se o id passado esta numa posicao na tabela no inicio da lista, retorna seu id
        return elementos[hash]->categoria;
    }
    else{       //Senao percorre toda a lista ligada na posicao da hash para encontrar o id, caso a posicao esteja nula ou nao haja esse valor naquela posicao, retorna nao encontrado
        PalavraReservada* atual = elementos[hash];
        
        while (atual != NULL && atual->cadeia != cadeia){
            atual = atual->prox;
        }

        if (atual != NULL && atual->cadeia == cadeia){
            return atual->categoria;
        }
        else{
            return "NAO ENCONTRADO";
        }
    }
}


void TabelaChave::remove(string cadeia){
    int hash = funcaoHash(cadeia, capacidade);
    if (elementos[hash] != NULL && elementos[hash]->cadeia == cadeia){
        PalavraReservada* aux = elementos[hash];
        elementos[hash] = elementos[hash]->prox;
        delete aux;
    } 
    else {
        PalavraReservada* atual = elementos[hash];
        PalavraReservada* anterior;
        while (atual != NULL && atual->cadeia != cadeia){
            anterior = atual;
            atual = atual->prox;
        }
        if (atual != NULL && atual->cadeia == cadeia){
            anterior->prox = atual->prox;
            delete atual;
        } 
        else {
            cout << "ERRO NA REMOÇÃO" << endl;  //Mais uma excessao a implementar
        }
    }
}

void TabelaChave::percorre(){  //Imprime a toda a tabela hash posicao por posicao, cada linha contendo toda a fila numa determinada posicao hash
    PalavraReservada* atual;
    cout<<"!------------------------!"<< endl;
    for(int i=0; i<capacidade; i++){
        cout<<i<<":";
        atual = elementos[i];
        while(atual!=NULL){
            cout<<"{CADEIA:["<< atual->cadeia<<"] CATEGORIA: ["<<atual->categoria<< "] TIPO:[" << atual->tipo<< "]} -->";
            atual = atual->prox;
        }
        cout<< "NULL"<< endl;
    }
    cout<<"!------------------------!"<< endl;
}

void TabelaChave::inserirPalavrasChave(){

    //PALAVRAS RESERVADAS PARA FUNCOES
    insere("SE", "TokIf", "PALAVRA_RESERVADA");
    insere("SENAO", "TokElse", "PALAVRA_RESERVADA");
    insere("PARA", "TokFor", "PALAVRA_RESERVADA");
    insere("ENQUANTO", "TokWhile", "PALAVRA_RESERVADA");
    insere("REGRADETRES", "TokRegraDeTres", "PALAVRA_RESERVADA");
    insere("PRINCIPAL", "TokMain", "PALAVRA_RESERVADA");
    insere("RETORNA", "TokReturn", "PALAVRA_RESERVADA");

    //PALAVRAS RESERVADAS PARA TIPOS
    insere("INTEIRO", "TokInt", "TIPO");
    insere("FLUTUANTE", "TokFloat", "TIPO");
    insere("CARACTERE", "TokChar", "TIPO");
    insere("SIMOUNAO", "TokBool", "TIPO");
    insere("VAZIO", "TokVoid", "TIPO");

    //PALAVRAS RESERVADAS PARA OPERADORES
    insere("MAIS", "TokMais", "OPERADOR");
    insere("MENOS", "TokMenos", "OPERADOR");
    insere("VEZES", "TokVezes", "OPERADOR");
    insere("DIVIDIDO", "TokDiv", "OPERADOR");
    insere("IGUAL", "TokAtribuicao", "OPERADOR");
    insere("DIFERENTE", "TokDiferente", "OPERADOR");
    insere("MAIOR", "TokMaior", "OPERADOR");
    insere("MENOR", "TokMenor", "OPERADOR");
    insere("MAIOROUIGUAL", "TokMaiorIgual", "OPERADOR");
    insere("MENOROUIGUAL", "TokMenorIgual", "OPERADOR");
    insere("NAO", "TokNegacao", "OPERADOR");
    insere("E", "TokAnd", "OPERADOR");
    insere("OU", "TokOr", "OPERADOR");
    insere("COMPARADO", "TokComparacao", "OPERADOR");

    //PALAVRAS RESERVADAS PARA SIMBOLOS DE DELIMITACAO
    insere(";", "TokPv", "DELIMITADOR");
    insere(".", "TokP", "DELIMITADOR");
    insere(",", "TokV", "DELIMITADOR");
    insere("(", "TokAbreParenteses", "DELIMITADOR");
    insere(")", "TokFechaParenteses", "DELIMITADOR");
    insere("{", "TokAbreChaves", "DELIMITADOR");
    insere("}", "TokFechaChaves", "DELIMITADOR");
    insere("[", "TokAbreColchetes", "DELIMITADOR");
    insere("]", "TokFechaColchetes", "DELIMITADOR");


}

#endif