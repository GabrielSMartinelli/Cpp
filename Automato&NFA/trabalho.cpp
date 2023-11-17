#include <iostream>
#include <vector>

using namespace std;

class Automato {
    //clase automato, que permite a criacao do objeto automato (maquina de estados que reconhece uma linguagem)

    int Q, F; //atributos Q e F, que representam o numero de estados e o numero de estados finais, respectivamente

    vector<bool> transicoes; 
    /*atributo com as transicoes do automato, funciona como uma "matriz de adjacencia", as posicoes com valor true 
    representam uma transicao, sendo a linha o estado de onde a transicao sai e a coluna o estado para onde ela vai*/

    vector<string> str;
    /*atributo com as letras aceitas por cada transicao, funciona tambem como uma "matriz de adjacencia", mas armazena
    strings com as letras que validam as transicoes, ao inves dos valores true ou false*/

    vector<int> estadosFinais, caminho;
    /*o atributo estadosFinais armazena os numeros dos estados finais do automato, ao passo que o atributo caminho
    guarda os estados pelos quais o automato passa ao validar uma palavra*/

    vector<char> letras;
    //atributo que recebe as letras da palavra que se quer validar se pertence ou nao a linguagem e a armazena

public:

    Automato(int Q, int F, vector<int> estadosFinais, vector<bool> transicoes, vector<string> str) {
        this->Q = Q;
        this->F = F;
        this->estadosFinais = estadosFinais;
        this->transicoes = transicoes;
        this->str = str;
    }
    //construtor do automato, reebe os atributos Q, F, estadosFinais, transicoes e str

    void setcaminho(int e) { caminho.push_back(e); } 
    //metodo que permite armazenar os estados pelos quais o caminho para validar uma palavra passa

    void setLetras(char l) { letras.push_back(l); }
    /* metodo que permite armazenar as letras (incluindo a palavra vazia "&") pelos quais o caminho para 
    validar uma palavra passa*/

    void apagarCaminho() {
        while(caminho.size() > 0)
            caminho.erase(caminho.begin());
    }
    //metodo para apagar o caminho para que ele seja utilizado novamente para outra palavra

    void apagarLetras() {
        while(letras.size() > 0)
            letras.erase(letras.begin());
    }
    /*metodo para apagar as letras pelas quais o ultimo caminho passou para que as letras de um novo caminho de outra
    palavra possam ser armazenadas*/

    int getQ() { return Q; } //metodo que retorna o numero de estados do automato
    int getF() { return F; } //metodo que retorna o numero de estados finais do automato

    string getStr(int posicao) {
        return str[posicao];
    }
    //metodo para obter as letras aceitas por determinada transicao

    int getEstadosFinais(int cont) {
        return estadosFinais[cont];
    }
    //metodo para obter os estados finais do automato

    int getCaminho(int cont) {
        return caminho[cont];
    }
    //metodo para obter os estados pelos quais uma palavra passa para ser validada

    char getLetras(int cont) {
        return letras[cont];
    }
    /*metodo para obter as letras utilizadas (incluindo a palavra vazia "&") por um certo caminho para validar ou 
    nao uma palavra*/

    int getTamanhoCaminho() { return caminho.size(); }
    //metodo que retorna o tamanho (numero de estados) de um determinado caminho
};

int posicao(int X, int Q, int Y) {
    int pos = X*Q + Y;
    return pos;
}
/* posicao - funcao que recebe o estado inicial (X) e o estado final (Y) de uma transicao e calcula a posicao numa
matriz de adjacencia*/

bool reconheceTransicao(Automato eNFA, int posicao, char c) {
    string copia = eNFA.getStr(posicao);
    for(int i = 0; i < copia.size(); i++) {
        if(c == copia[i])
            return true;
    }
    return false;
}
/* reconheceTransicao - funcao que reconhece uma transicao que consome uma letra da string (palavra). A funcao recebe 
a posicao (da "matriz") e recebe uma letra, de modo que deve reconhecer se a letra valida ou nao a transicao. Ela entao 
recebe as letras dessa transicao e compara uma a uma com a letra que se quer validar. Caso a letra esteja na string das 
letras que permitem a transicao, a funcao retorna true. Se mesmo depois de todas as comparacoes ela nao for encontrada, 
retorna false.*/

bool reconheceTransicaoVazia(Automato eNFA, int posicao) {
    string copia = eNFA.getStr(posicao);
    for(int i = 0; i < copia.size(); i++) {
        if('&' == copia[i])
            return true;
    }
    return false;
}
/* reconheceTransicaoVazia - funcao que reconhece uma transicao vazia (ou que consome "&"). A funcao recebe a posicao 
(da "matriz"), de modo que deve reconhecer se a palavra vazia valida ou nao a transicao. Ela entao recebe as letras 
dessa transicao e compara uma a uma com a palavra vazia "&". Caso ela esteja na string das letras que permitem 
a transicao, a funcao retorna true. Se mesmo depois de todas as comparacoes ela nao for encontrada, retorna false.*/

bool Validade(Automato &eNFA, int X, string palavra, int cont, bool transicao) {

    for(int Y=0; Y<eNFA.getQ(); Y++) { //passa por todos os estados
        int pos = posicao(X, eNFA.getQ(), Y); //a variavel pos recebe a posicao na "matriz" com base em X e Y
        if(reconheceTransicaoVazia(eNFA, pos) == true) { //caso uma transicao vazia seja valida, executa o que esta dentro
            if(Validade(eNFA, Y, palavra, cont, false) == true) {
                /*chama a funcao validade de forma recursiva, a fim de percorrer o automato. Se ao final desse percurso
                verificar-se que a palavra eh valida, executa o que esta dentro*/
                eNFA.setcaminho(X);
                eNFA.setLetras('&');
                return true;
                /*caso seja valida, guarda o ultimo estado pelo qual passou, e define que foi consumida uma palavra
                vazia "&", retornando true, ou seja, que a palavra pertence a linguagem*/
            }
        }
    }
    /*esse passo eh sempre executado antes da condicao de parada da recursao, pois a palavra vazia nao consome letras
    da palavra que se quer verificar se pertence ou nao a linguagem*/
    
    if(cont >= palavra.size()) { 
        //condicao de parada, ocorre quando todas as letras foram consumidas e a transicao vazia nao eh valida

        for(int i=0; i<eNFA.getF(); i++) { //passa pelos estados finais do automato
            if(X == eNFA.getEstadosFinais(i)) { //verifica se o estado atual eh igual a um dos estados finais
                eNFA.setcaminho(X); //se for igual, armazena esse estado no caminho
                if(transicao == false)
                    //se a ultima transicao foi vazia, define que foi consumida uma palavra vazia "&"
                    eNFA.setLetras('&');
                else
                    //senao, define que a ultima letra da palavra foi consumida
                    eNFA.setLetras(palavra[cont-1]);
                return true;
                    //retorna true, ou seja, que a palavra pertence a linguagem
            }
        }
        return false; //se nao eh um estado final, retorna false, portanto, a palavra nao pertence a linguagem
    }

    for(int Y=0; Y<eNFA.getQ(); Y++) { //passa por todos os estados
        int pos = posicao(X, eNFA.getQ(), Y); //a variavel pos recebe a posicao na "matriz" com base em X e Y
        if(reconheceTransicao(eNFA, pos, palavra[cont]) == true) { 
            //caso uma transicao seja valida, executa o que esta dentro
            cont++; 
            //o contador aumenta em 1, de modo que uma letra da palavra eh consumida
            if(Validade(eNFA, Y, palavra, cont, true) == true) {
                /*chama a funcao validade de forma recursiva, a fim de percorrer o automato. Se ao final desse percurso
                verificar-se que a palavra eh valida, executa o que esta dentro*/
                eNFA.setcaminho(X);
                eNFA.setLetras(palavra[cont-1]);
                return true;
                /*caso seja valida, guarda o ultimo estado pelo qual passou, e define que foi consumida uma letra da
                palavra, retornando true, ou seja, que a palavra pertence a linguagem*/
            }
        }
    }
    return false;
    /*se nao for possivel realizar mais nenhuma transicao, a palavra foi totalmente consumida e o estado atual nao
    eh final, retorna false, ou seja, a palavra nao pertence a linguagem*/
}

void imprimeCaminho(Automato eNFA) {
    for(int i=eNFA.getTamanhoCaminho()-1; i>0; i--) {
        //percorre o caminho de traz pra frente, pois ele foi salvo invertido devido a recursao
        cout << eNFA.getCaminho(i) << " -> " << eNFA.getLetras(i) << " -> " << eNFA.getCaminho(i-1) << endl;
        /*imprime o estado do qual a transicao do caminho sai, a letra da palavra que validou a transicao, ou a palavra
        vazia "&" se for o caso, e imprime o estado para o qual a transicao levou*/
    }
}

int main() {

    int A, Q, F, X, Y, pos;
    /*variaveis, sendo que A eh o tamanho do alfabeto, Q eh o numero de estados do automato, F eh o numero de estados
    finais do automato, X e Y fazem parte da funcao de transicao e pos eh a posicao numa matriz (semelhante a uma matriz
    de adjacencia de um grafo, onde a linha representa o estado "atual" e a coluna o estado "futuro" (para o qual a 
    letra leva)*/

    string alfabeto, letras, palavra;
    /*strings, sendo que alfabeto armazena o alfabeto que a linguagem aceita, letras guarda as letras para as quais eh
    possivel fazer a transicao entre dois estados (informacao passada pelo usuario), e palavra armazena uma palavra
    digitada pelo usuario para verificar se ela pertence ou nao a linguagem, e serve para colocar ela no vector str*/

    vector<bool> transicoes; 
    /*"funciona" como uma matriz de adjacencia, sendo que possui Q*Q posicoes, tal que a linha indica o estado do qual
    se sai e a coluna o estado para o qual a letra leva, de modo que se o valor for igual a true, significa que ao menos
    uma letra ou a palavra vazia "&" faz a transicao do primeiro estado para o segundo*/

    vector<int> finais;
    //vector que possui os estados finais do automato

    vector<string> str;
    //vector que repassa para o vector do Automato strings vazias, e depois guarda as palavras digitadas pelo usuario

    cin >> A >> alfabeto; //entrada do usuario com o tamanho do alfabeto e o alfabeto em si
    cin >> Q; //entrada do usuario com o numero de estados do automato
    cin >> F; //entrada do usuario com o numero de estados finais do automato

    for(int i=0; i<F; i++) {
        int n;
        cin >> n;
        finais.push_back(n);
    }
    //laco que recebe quais sao os estados finais do automato e coloca eles num vector

    for(int i=0; i<Q*Q; i++) {
        transicoes.push_back(false);
        str.push_back("\0");
    }
    //laco que deixa todas as transicoes do automato em false e deixa as strings com o caractere \0

    cin >> X >> letras >> Y; //entrada do usuario com a primeira transicao

    while(X != -1 and letras != "*" and Y != -1) {
        pos = posicao(X, Q, Y);
        transicoes[pos] = true;
        str[pos] = letras;
        cin >> X >> letras >> Y;
    }
    /*laco que roda enquanto o usuario digitar transicoes validas, coloca o valor delas como true na "matriz"
    (vector) das transicoes e salva a string com as letras que validam a transicao no vector str.*/

    Automato eNFA(Q, F, finais, transicoes, str); 
    /*cria o automato passando para o construtor o numero de estados, de estados finais, alem de passar os estados
    finais em si, o vector com as transicoes e o vector com as letras aceitas por cada transicao*/

    while(str.size() > 0) {
        str.erase(str.begin());
    }
    //laco que apaga as informacoes do vector str para reutiliza-lo

    cin >> palavra; //entrada do usuario com a primeira palavra a ser verificada se pertence ou nao a linguagem

    while(palavra != "*") {
        str.push_back(palavra);
        cin >> palavra;
    }
    /*laco que roda enquanto o usuario digitar palavras validas a fim de verificar se ela pertence ou nao a linguagem,
    e as guarda num vector*/

    while(str.size() > 0) { //executa enquanto todas as palavras nao forem validadas ou nao
        if(Validade(eNFA, 0, str[0], 0, false) == true) {
            //se a palavra pertence a linguagem, executa o que esta dentro
            cout << str[0] << ": sim" << endl; //diz que a palavra pertence a linguagem
            imprimeCaminho(eNFA); //imprime o caminho pelo qual ela passou
            cout << endl;
        }
        else //se a palavra nao pertence a linguagem, executa o que esta a seguir
            cout << str[0] << ": nao" << endl << '\n'; //diz que a palavra pertence a linguagem
        str.erase(str.begin()); //depois apaga a palavra analisada
        eNFA.apagarCaminho(); //apaga o caminho percorrido para validar ela
        eNFA.apagarLetras(); //apaga as letras usadas pelo caminho (incluindo a palavra vazia "&")
    }


    return 0;
}