#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include "TabelaDeSimbolos.cpp"
#include "Tabela_palavras_chave.cpp"
#include "Lexico.cpp"
#include "Sintatico.cpp"

using namespace std;

int main(int argc, char *argv[]){
    
    try{
        string caminho_arquivo;
        if(argc>1){
            caminho_arquivo = argv[1];
        }
        else throw 1;
        
        
        TabelaChave *reservadas = new TabelaChave();
        TabelaDeSimbolos *table = new TabelaDeSimbolos(500);
        bool programa_valido = true;

        programa_valido = analisarLexico(caminho_arquivo, table, reservadas);
        if (programa_valido == false) {
            remove("saida_lexica.txt");
            return 0;
        }
        cout << "\n\n Analise lexica concluida com sucesso.\n\n";

        if(AnalisarSintatico("saida_lexica.txt", table)) {
            cout << "\nAnalise sintatica concluida com sucesso.\n";
        }

        else {
            cout << "\nAnalise sintatica mal-sucedida.\n";
        }
        
        delete(reservadas);
        delete(table);
        remove("saida_lexica.txt");


    }
    catch(int erro){
        if(erro == 1){
            cout<<"Nenhum caminho foi passado como argumento";
        }
        else if(erro ==2){
            cout<< "Nao foi possivel abrir o arquivo, caminho passado eh invalido";
        }
        
    }
    catch(...){
        cout<<"Erro desconhecido";
    }
    return 0;
}