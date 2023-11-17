#include<iostream>
#include "Tokens.cpp"

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

#ifndef TABELASIMBOLOS
#define TABELASIMBOLOS

class TabelaDeSimbolos{

    public:
        TabelaDeSimbolos(int cap);
        ~TabelaDeSimbolos();
        void insere(string type, string identificador, string value, int linha, int coluna);
        void altera(string identificador, string valor, int novaLinha, int novaColuna);
        void remove(string identificador);
        string recupera(string identificador);
        void percorre();



    private:
        Token** elementos; //Define um vetor de ponteiros para os elementos na tabela de simbolos
        int capacidade; //Vai ditar a capacidade da tabela de simbolos

};

TabelaDeSimbolos::TabelaDeSimbolos(int cap=100){
    capacidade = cap;
    elementos = new Token*[cap];   //define elementos como um vetor de ponteiros de capacidade igual a passada no construtor

    for (int i = 0; i < cap; i++){  //Vai inicializar todas as posicoes da tabela como null
        elementos[i] = NULL;
    }
}

TabelaDeSimbolos::~TabelaDeSimbolos(){
     for (int i = 0; i < capacidade; ++i){  //Percorre toda a tabela hash
        Token *atual = elementos[i];
        while(atual != NULL){
            Token* aux = atual;
            atual = atual->prox;    //Percorre recursivamente todos os elementos da fila
            delete(aux);            //Deleta todos do ultimo ate o comeco
        }
     }
     delete[] elementos;            //libera a memoria do vetor de ponteiros da tabela
}

void TabelaDeSimbolos::insere(string type, string identificador, string value, int linha, int coluna){
    string aux = identificador;    //A funcao hash eh calculada pelo identificador da variavel
    int hash = funcaoHash(aux, capacidade);

    if(recupera(aux)=="NAO ENCONTRADO"){    //se nao encontra o id na tabela, insere um novo
        if(elementos[hash] == NULL){        //Se na posicao nao tiver nada, insere um novo
            elementos[hash] = new Token(type, identificador, value, linha, coluna);
        }
        else{                               //Se ja houver um elemento naquela posicao, percorre toda a lista ligada para inserir o novo token no final dela
            //cout<<"Colidiu: "<< aux << endl;
            Token* atual = elementos[hash];
            while(atual->prox != NULL){
                atual = atual->prox;
            }
            Token* novo = new Token(type, identificador, value, linha, coluna);
            atual->prox = novo;
        }
    }

}

string TabelaDeSimbolos::recupera(string identificador){
    string aux = identificador;
    int hash = funcaoHash(aux, capacidade);
    if (elementos[hash] != NULL && elementos[hash]->id == identificador){  //Se o id passado esta numa posicao na tabela no inicio da lista, retorna seu id
        return elementos[hash]->id;
    }
    else{       //Senao percorre toda a lista ligada na posicao da hash para encontrar o id, caso a posicao esteja nula ou nao haja esse valor naquela posicao, retorna nao encontrado
        Token* atual = elementos[hash];
        
        while (atual != NULL && atual->id != identificador){
            atual = atual->prox;
        }

        if (atual != NULL && atual->id == identificador){
            return atual->id;
        }
        else{
            return "NAO ENCONTRADO";
        }
    }
}

void TabelaDeSimbolos::altera(string identificador, string valor, int novaLinha, int novaColuna){
    int hash = funcaoHash(identificador, capacidade);
    if(elementos[hash]!=NULL && elementos[hash]->id==identificador){
        elementos[hash]->nova_ocorrencia(novaLinha, novaColuna, valor);  //Registra a alteracao de valor e onde a foi mudado: linha e coluna

    }
    else{
        Token* atual = elementos[hash];         //Novamente, se o valor nao estiver na primeira posicao da fila, percorre ela ate achar o id certo, registrando a alteracao
        while(atual!=NULL && atual->id != identificador){
            atual = atual->prox;
        }
        if(atual!=NULL && atual->id == identificador){
            atual->nova_ocorrencia(novaLinha, novaColuna, valor);
        }
        else{
            cout<<"Erro na alteracao"<< endl;   //esses couts devem ser substituidos por excessoes
        }
    }
}

void TabelaDeSimbolos::remove(string identificador){
    int hash = funcaoHash(identificador, capacidade);
    if (elementos[hash] != NULL && elementos[hash]->id == identificador){
        Token* aux = elementos[hash];
        elementos[hash] = elementos[hash]->prox;
        delete aux;
    } 
    else {
        Token* atual = elementos[hash];
        Token* anterior;
        while (atual != NULL && atual->id != identificador){
            anterior = atual;
            atual = atual->prox;
        }
        if (atual != NULL && atual->id == identificador){
            anterior->prox = atual->prox;
            delete atual;
        } 
        else {
            cout << "ERRO NA REMOÇÃO" << endl;  //Mais uma excessao a implementar
        }
    }
}

void TabelaDeSimbolos::percorre(){  //Imprime a toda a tabela hash posicao por posicao, cada linha contendo toda a fila numa determinada posicao hash
    Token* atual;
    cout<<"!------------------------!"<< endl;
    for(int i=0; i<capacidade; i++){
        cout<<i<<":";
        atual = elementos[i];
        while(atual!=NULL){
            cout<<"{TIPO:["<< atual->tipo<<"] ID: ["<<atual->id<< "] VALOR:[" << atual->valor<< "]} -->";
            atual = atual->prox;
        }
        cout<< "NULL"<< endl;
    }
    cout<<"!------------------------!"<< endl;
}

#endif