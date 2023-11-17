#include<iostream>

#ifndef PALAVRARESERVADA
#define PALAVRARESERVADA

class PalavraReservada{
    friend class TabelaChave;
    
    private:
    std::string categoria, tipo, cadeia;
    PalavraReservada *prox = NULL;

    public:
    PalavraReservada(std::string cadeia, std::string categoria, std::string tipo);
    //Cadeia eh a representacao no codigo da palavra reservada, tipo diz se eh uma palavra reservada ou um operador
    //Categoria vai ditar o qual automato executaremos: TokWhile, TokFor, TokMais
    std::string getCadeia() {return cadeia;}
    std::string getCategoria() {return categoria;}
    std::string getTipo() {return tipo;}

};

    PalavraReservada::PalavraReservada(std::string cadeia, std::string categoria, std::string tipo){
        PalavraReservada::cadeia = cadeia;
        PalavraReservada::categoria = categoria;
        PalavraReservada::tipo = tipo;
        
    }


#endif