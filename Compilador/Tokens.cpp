#include <iostream>
#include <vector>
#include "palavra_reservada.cpp"


#ifndef TOKEN
#define TOKEN

class Token{
    friend class TabelaDeSimbolos;
    public:

    Token(std::string type, std::string identificador, std::string value, int linha, int coluna);
    void nova_ocorrencia(int linha, int coluna, std::string value);
    std::string getTipo() {return tipo;}
    std::string getId() {return id;}
    std::string getValor() {return valor;}
    int getLinha(int ocorrencia) {return posicoes.at(ocorrencia).at(1);}
    int getColuna(int ocorrencia) {return posicoes.at(ocorrencia).at(0);}
    bool operator==(const Token& Tok) const;
    bool operator!=(const Token& Tok) const;
    bool operator>(const Token& Tok) const;
    bool operator<(const Token& Tok) const;
    Token* converteReservada_Token(PalavraReservada* palavra);


    private:
        std::string id;
        int contador_posicoes = 0;  //variavel auxiliar para contar as ocorrencias da variavel
        std::string tipo;   //Tipo da variavel fica armazenado aqui
        std::string valor;  //Valor da variavel armazenado no formato de string, depois deve ser convertido para o tipo especificado na variavel tipo
        std::vector<std::vector<int>> posicoes; //vetor que contem outro vetor com os valores das posicoes de coluna e linha onde houve a ocorrencia desse token
        Token* prox = NULL;

};


    Token::Token(std::string type, std::string identificador, std::string value, int linha, int coluna){
        valor = value;
        id = identificador;
        tipo = type;
        std::vector<int> aux;
        aux.push_back(coluna);
        aux.push_back(linha);
        posicoes.push_back(aux);
        contador_posicoes++;
    }

    void Token::nova_ocorrencia(int linha, int coluna, std::string value){
        valor = value;
        std::vector<int> aux;
        aux.push_back(coluna);
        aux.push_back(linha);
        posicoes.push_back(aux);
        contador_posicoes++;
    }

    bool Token::operator==(const Token& Tok) const {
        return tipo == Tok.tipo &&
               id == Tok.id &&
               valor == Tok.valor &&
               posicoes == Tok.posicoes;
    }

    bool Token::operator!=(const Token& Tok) const {
        return !(tipo == Tok.tipo) &&
               !(id == Tok.id) &&
               !(valor == Tok.valor) &&
               !(posicoes == Tok.posicoes);
    }

    bool Token::operator>(const Token& Tok) const {
        return stoi(valor) > stoi(Tok.valor);
    }

    bool Token::operator<(const Token& Tok) const {
        return stoi(valor) < stoi(Tok.valor);
    }

    Token* Token::converteReservada_Token(PalavraReservada* palavra) {
        Token* Tok = new Token(palavra->getCategoria(), palavra->getCadeia(), "0", 0, 0);
        return Tok;
    }

#endif