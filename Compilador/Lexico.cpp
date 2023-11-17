#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include "TabelaDeSimbolos.cpp"
#include "Tabela_palavras_chave.cpp"

#ifndef ANALISADORLEXICO
#define ANALISADORLEXICO

using namespace std;

bool analisarLexico(string caminho,TabelaDeSimbolos *table, TabelaChave *reservadas) {
    char caracter;
    bool flutuante = false;
    string lexema;
    string aux;
    int count_linha = 1;
    int count_coluna = 0;
    int count_id = 0;
    
    ifstream arquivo1(caminho);
    if (!arquivo1.is_open()) {
    throw 2;
    }

    ofstream arquivo2("saida_lexica.txt", ofstream::out);
    if (!arquivo2.is_open()) {
    cout << "Arquivo de tokens nao pode ser aberto";
    return 0;
    }
    
    while(arquivo1.eof() == false) {
        lexema.clear();
        caracter = arquivo1.get();
        if (caracter >= 48 && caracter <= 57) {
            while (caracter >= 48 && caracter <= 57) {
                lexema.push_back(caracter);
                count_coluna++;
                caracter = arquivo1.get();
                if (caracter == '.') {
                    if (flutuante == true) {
                        cout << "Erro lexico encontrado na linha:" << count_linha << " coluna:" << count_coluna << " (mais de um ponto flutuante no numero)";
                        return false;
                    }
                    else flutuante = true;
                }
            }
            if(!isspace(caracter) && caracter != ';' && caracter != ']' && caracter != ')') {
                    cout << "Erro lexico encontrado na linha:" << count_linha << " coluna:" << count_coluna << " (numero invalido)";
                    return false;
            }
            count_id++;
            if (flutuante == false) {
                table->insere("NUMEROINTEIRO", lexema, to_string(count_id), count_linha, count_coluna);
                arquivo2 << "<TokNumint," << to_string(count_id) << ">";
            }
            if (flutuante == true) {
                table->insere("NUMEROFLUTUANTE",lexema, to_string(count_id), count_linha, count_coluna);
                arquivo2 << "<TokNumfloat," << to_string(count_id) << ">";
            }
            count_coluna++;
        }
        if ((caracter >= 65 && caracter <= 90) || (caracter >= 97 && caracter <= 122)) {
            while((caracter >= 65 && caracter <= 90) || (caracter >= 97 && caracter <= 122) || (caracter >= 48 && caracter <= 57)) {
                lexema.push_back(caracter);
                count_coluna++;
                caracter = arquivo1.get();
            }
            if(!isspace(caracter) && caracter != ';' && caracter != ']' && caracter != ')'  && caracter != ',') {
                    cout << "Erro lexico encontrado na linha:" << count_linha << " coluna:" << count_coluna << " (identificador ou funcao invalida)";
                    return false;
            }
            else {
                aux = reservadas->recupera(lexema);
                if (aux == "NAO ENCONTRADO") {
                    count_id++;
                    table->insere("IDENTIFICADOR",lexema, to_string(count_id), count_linha, count_coluna);
                    arquivo2 << "<TokID," << to_string(count_id) << ">";
                }
                else {
                    arquivo2 << "<" << aux << ">";
                }
            }

        }
        if (caracter == ',') {
                count_coluna++;
                arquivo2 << "<TokV>";
        }
        if (caracter == 34) {
            count_coluna++;
            caracter = arquivo1.get();
            if (caracter == 34) {
                cout << "Erro lexico encontrado na linha:" << count_linha << " coluna:" << count_coluna << " (esperado conteudo dentro das aspas)";
                return false;
            }
            else {
                while(caracter != 34) {
                    count_coluna++;
                    lexema.push_back(caracter);
                    caracter = arquivo1.get();         
                }
                count_coluna++;
                count_id++;
                table->insere("STRING", lexema, to_string(count_id), count_linha, count_coluna);
                arquivo2 << "<TokString>";
            }
        }
         if (caracter == 39) {
            lexema.push_back(caracter);
            count_coluna++;
            caracter = arquivo1.get();
            if (caracter == 39) {
                cout << "Erro lexico encontrado na linha:" << count_linha << " coluna:" << count_coluna << " (esperado conteudo dentro das aspas)";
                return false;
            }
            else {
                count_coluna++;
                lexema.push_back(caracter);
                caracter = arquivo1.get();
                if (caracter == 39) {
                    lexema.push_back(caracter);
                    count_coluna++;
                    count_id++;
                    table->insere("CHAR", lexema, to_string(count_id), count_linha, count_coluna);
                    arquivo2 << "<TokCaractere>";
                }
                else {
                    cout << "Erro lexico encontrado na linha:" << count_linha << " coluna:" << count_coluna << " (apenas um caractere pode ser inserido dentro de aspas simples)";
                    return false;
                }
            }
        }
        if (caracter == 91) {
            count_coluna++;
            arquivo2 << "<TokAbreColchetes>";
        }
        if (caracter == 93) {
            count_coluna++;
            arquivo2 << "<TokFechaColchetes>";
        }
        if (caracter == 40) {
            count_coluna++;
            arquivo2 << "<TokAbreParenteses>";
        }
        if (caracter == 41) {
            count_coluna++;
            arquivo2 << "<TokFechaParenteses>";
        }
        if (caracter == 123) {
            count_coluna++;
            caracter = arquivo1.get();
            if (caracter == '\n') {
                count_coluna = 0;
                arquivo2 << "<TokAbreChaves>";
            }
            else {
                cout << "Erro lexico encontrado na linha:" << count_linha << " coluna:" << count_coluna << " (esperado quebra de linha)";
                return false;
            } 
        }
        if (caracter == 125) {
            count_coluna++;
            caracter = arquivo1.get();
            if (caracter == '\n' || arquivo1.eof() == true) {
                count_coluna = 0;
                arquivo2 << "<TokFechaChaves>";
            }
            else {
                cout << "Erro lexico encontrado na linha:" << count_linha << " coluna:" << count_coluna << " (esperado quebra de linha)";
                return false;
            } 
        }
        if (caracter == 59) {
            count_coluna++;
            caracter = arquivo1.get();
            if (caracter == '\n') {
                count_coluna = 0;
                arquivo2 << "<TokPv>";
            }
            else {
                cout << "Erro lexico encontrado na linha:" << count_linha << " coluna:" << count_coluna << " (esperado quebra de linha)";
                return false;
            }
        }
        if (caracter == '\n') {
                count_linha++;
                count_coluna = 0;
                arquivo2 << "\n";
        }


    }
    arquivo1.close();
    arquivo2.close();
    return true;
};



#endif

