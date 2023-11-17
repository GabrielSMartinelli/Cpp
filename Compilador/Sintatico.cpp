#include "Sintatico.h"

bool ehEspacoEmBranco(char c) {
    return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

void ConsomeEspacoEmBranco() {
    while (posicao < entrada.length() && ehEspacoEmBranco(entrada[posicao])) {
        posicao++;
    }
}

int AcharLinha(int pos) {

    int i = 0;
    int linha = 1;
    while (i <= pos) {
        if(entrada[i] == '\n') {
            linha++;
        }
        i++;
    }
    return linha;
}

bool ehPrograma(No* raiz) {

    int i = 0;

    while(true) {

        aux = posicao;
        Token* DeclaracaoDeExpressao = new Token("REGRA", "DECLARACAODEEXPRESSAO", to_string(escopo), 0, 0);

        raiz->filhos.push_back(criarNo(DeclaracaoDeExpressao));

        if(!ehDeclaracaoDeExpressao(nullptr)) {
            raiz->filhos.pop_back();
            break;
        }
        i++;
    }

    posicao = aux;
    ConsomeEspacoEmBranco();

    while(true) {

        aux = posicao;
        Token* DefinicaoDeFuncao = new Token("REGRA", "DEFINICAODEFUNCAO", to_string(escopo), 0, 0);

        raiz->filhos.push_back(criarNo(DefinicaoDeFuncao));

        if(!ehDefinicaoDeFuncao(nullptr)) {
            raiz->filhos.pop_back();
            break;
        }
        i++;
    }

    posicao = aux;
    ConsomeEspacoEmBranco();

    Token* Principal = new Token("REGRA", "PRINCIPAL", to_string(escopo), 0, 0);

    raiz->filhos.push_back(criarNo(Principal));

    if(!ehPrincipal(nullptr)) {
        raiz->filhos.pop_back();
        cout << "Erro - nao ha funcao PRINCIPAL\n";
    }

    if(posicao >= entrada.length())
            return true;
    
    return false;
}

bool ehPrincipal(No* raiz) {

    int i = 0;

    ConsomeEspacoEmBranco();

    if(entrada.substr(posicao, 8) != "<TokInt>") {
        return false;
    }

    posicao+= 8;
    ConsomeEspacoEmBranco();

    if(entrada.substr(posicao, 9) != "<TokMain>") {
        return false;
    }

    posicao+= 9;
    ConsomeEspacoEmBranco();

    if (entrada.substr(posicao, 19) != "<TokAbreParenteses>") {
        cout << "Erro - linha " << AcharLinha(posicao) << ": esperado um (\n";
    }

    else {
        posicao+= 19;
    }
    
    ConsomeEspacoEmBranco();

    if (entrada.substr(posicao, 20) != "<TokFechaParenteses>") {
        cout << "Erro - linha " << AcharLinha(posicao) << ": esperado um )\n";
    }

    else {
        posicao+= 20;
    }

    ConsomeEspacoEmBranco();

    if(entrada.substr(posicao, 15) != "<TokAbreChaves>") {
        cout << "Erro - linha " << AcharLinha(posicao) << ": esperado um {\n";
    }

    posicao += 15;

    if(!ehListaDeDeclaracao(nullptr)) {
        cout << "Erro - linha " << AcharLinha(posicao) << ": esperado uma declaracao\n";
    }

    ConsomeEspacoEmBranco();

    if(entrada.substr(posicao, 16) != "<TokFechaChaves>") {
        cout << "Erro - linha " << AcharLinha(posicao) << ": esperado um }\n";
    }

    else {
        posicao += 16;
    }
    
    return true;
}

bool ehDefinicaoDeFuncao(No* raiz) {

    int i = 0;

    if (!ehEspecificadorDeTipoDeFuncao(nullptr)) {
        return false;
    }

    if (entrada.substr(posicao, 9) == "<TokMain>" || !ehIdentificador(nullptr)) {
        return false;
    }

    ConsomeEspacoEmBranco();

   if (entrada.substr(posicao, 19) != "<TokAbreParenteses>") {
        cout << "Erro - linha " << AcharLinha(posicao) << ": esperado um (\n";
    }

    else {
        posicao+= 19;
    }
    
    ConsomeEspacoEmBranco();

    if(entrada.substr(posicao, 20) != "<TokFechaParenteses>") {
        ehListaDeParametros(nullptr);
    }

    ConsomeEspacoEmBranco();

    if (entrada.substr(posicao, 20) != "<TokFechaParenteses>") {
        cout << "Erro - linha " << AcharLinha(posicao) << ": esperado um )\n";
    }

    else {
        posicao+= 20;
    }

    ConsomeEspacoEmBranco();

    if(entrada.substr(posicao, 15) != "<TokAbreChaves>") {
        cout << "Erro - linha " << AcharLinha(posicao) << ": esperado um {\n";
    }

    posicao += 15;

    if(!ehListaDeDeclaracao(nullptr)) {
        cout << "Erro - linha " << AcharLinha(posicao) << ": esperado uma declaracao\n";
    }

    ConsomeEspacoEmBranco();

    if(entrada.substr(posicao, 16) != "<TokFechaChaves>") {
        cout << "Erro - linha " << AcharLinha(posicao) << ": esperado um }\n";
    }

    else {
        posicao += 16;
    }

    return true;
}

bool ehEspecificadorDeTipo(No* raiz) {

    ConsomeEspacoEmBranco();

    std::string tipos[] = {"<TokInt>", "<TokFloat>", "<TokChar>", "<TokBool>"};

    for (const std::string& tipo : tipos) {
        if (entrada.substr(posicao, tipo.length()) == tipo) {
            posicao += tipo.length();
            return true;
        }
    }

    return false;
}

bool ehEspecificadorDeTipoDeFuncao(No* raiz) {

    ConsomeEspacoEmBranco();

    std::string tipos[] = {"<TokInt>", "<TokFloat>", "<TokChar>", "<TokBool>", "<TokVoid>"};

    for (const std::string& tipo : tipos) {
        if (entrada.substr(posicao, tipo.length()) == tipo) {
            posicao += tipo.length();
            return true;
        }
    }

    return false;
}

bool ehListaDeParametros(No* raiz) {

    int i = 0;
    
    if(!ehParametro(nullptr)) {
        return false;
    }

    ConsomeEspacoEmBranco();

    if(entrada.substr(posicao, 20) == "<TokFechaParenteses>") {
        return true;
    }

    else if(entrada.substr(posicao, 6) != "<TokV>") {
        cout << "Erro - linha " << AcharLinha(posicao) << ": esperado uma virgula separando os parametros\n";
    }

    else{
        posicao += 6;
    }

    if(!ehListaDeParametros(nullptr)) {
        return false;
    }

    if(entrada.substr(posicao, 20) != "<TokFechaParenteses>") {
        cout << "Erro - linha " << AcharLinha(posicao) << ": esperado um )\n";
    }

    return true;
}

bool ehParametro(No* raiz) {

    int i = 0;

    if(!ehEspecificadorDeTipo(nullptr)) {
        return false;
    }

    if(!ehIdentificador(nullptr)) {
        return false;
    }

    return true;
}

bool ehDeclaracaoComposta(No* raiz) {

    int i = 0;

    ConsomeEspacoEmBranco();

    if (entrada.substr(posicao, 15) != "<TokAbreChaves>") {
        return false;
    }

    else {
        posicao+= 15;
    }

    if(!ehListaDeDeclaracao(nullptr)) {
        return false;
    }

    ConsomeEspacoEmBranco();

    if (entrada.substr(posicao, 16) != "<TokFechaChaves>") {
        cout << "Erro - linha " << AcharLinha(posicao) << ": esperado um }\n";
    }

    else {
        posicao+= 16;
    }

    return true;
}

bool ehListaDeDeclaracao(No* raiz){

    int i = 0;

    if(!ehDeclaracao(nullptr)) {
        return false;
    }

    aux = posicao;

    if(!ehListaDeDeclaracao(nullptr)) {
        posicao = aux;
    }

    return true;
}

bool ehDeclaracao(No* raiz) {

    int i = 0;

    if(!ehDeclaracaoDeExpressao(nullptr) && !ehDeclaracaoComposta(nullptr) && !ehDeclaracaoDeSelecao(nullptr) && 
    !ehDeclaracaoDeIteracao(nullptr) && !ehDeclaracaoDeRetorno(nullptr) && !ehDeclaracaoDeRegraDeTres(nullptr)) {
        return false;
    }

    return true;
}

bool ehDeclaracaoDeExpressao(No* raiz) {

    int i = 0;

    aux = posicao;

    if(!ehEspecificadorDeTipo(nullptr)) {
        posicao = aux;
    }

    ConsomeEspacoEmBranco();

    if(entrada.substr(posicao, 9) == "<TokMain>") {
        return false;
    }

    if(!ehExpressaoDeAtribuicao(nullptr)) {
        return false;
    }

    ConsomeEspacoEmBranco();

    if(entrada.substr(posicao, 7) != "<TokPv>") {
        cout << "Erro - linha " << AcharLinha(posicao) << ": esperado um ; antes da nova declaracao\n";
    }

    else {
        posicao += 7;
    }

    return true;
}

bool ehDeclaracaoDeSelecao(No* raiz) {

    int i = 0;

    ConsomeEspacoEmBranco();

    if (entrada.substr(posicao, 7) == "<TokIf>") {

        posicao += 7;
        ConsomeEspacoEmBranco();

        if (entrada.substr(posicao, 19) != "<TokAbreParenteses>") {
            return false;
        }

        posicao += 19;

        if (!ehExpressaoDeAtribuicao(nullptr)) {
            return false;
        }

        ConsomeEspacoEmBranco();

        if (entrada.substr(posicao, 20) != "<TokFechaParenteses>") {
            return false;
        }

        posicao += 20;

        if (!ehDeclaracaoComposta(nullptr)) {
            return false;
        }

        ConsomeEspacoEmBranco();

        if (entrada.substr(posicao, 9) == "<TokElse>") {

            posicao += 9;

            if (!ehDeclaracaoComposta(nullptr)) {
                return false;
            }
        }

        return true;
    }

    return false;
}

bool ehDeclaracaoDeIteracao(No* raiz) {

    int i = 0;

    ConsomeEspacoEmBranco();

    if (entrada.substr(posicao, 10) == "<TokWhile>") {
        
        posicao += 10;
        ConsomeEspacoEmBranco();

        if (entrada.substr(posicao, 19) != "<TokAbreParenteses>") {
            cout << "Erro - linha " << AcharLinha(posicao) << ": esperado um (\n";
        }

        else {
            posicao+= 19;
        }

        if (!ehExpressaoDeAtribuicao(nullptr)) {
            return false;
        }

        ConsomeEspacoEmBranco();

        if (entrada.substr(posicao, 20) != "<TokFechaParenteses>") {
            cout << "Erro - linha " << AcharLinha(posicao) << ": esperado um )\n";
        }

        else {
            posicao+= 20;
        }

        if (!ehDeclaracaoComposta(nullptr)) {
            return false;
        }

        return true;
    }

    else if (entrada.substr(posicao, 8) == "<TokFor>") {

        posicao += 8;
        ConsomeEspacoEmBranco();

        if (entrada.substr(posicao, 19) != "<TokAbreParenteses>") {
            cout << "Erro - linha " << AcharLinha(posicao) << ": esperado um (\n";
        }

        else {
            posicao+= 19;
        }

        if (!ehDeclaracaoDeExpressao(nullptr)) {
            return false;
        }

        if (!ehExpressaoDeAtribuicao(nullptr)) {
            return false;
        }

        ConsomeEspacoEmBranco();

        if (entrada.substr(posicao, 7) != "<TokPv>") {
            return false;
        }

        posicao += 7;

        if (!ehExpressaoDeAtribuicao(nullptr)) {
            return false;
        }

        ConsomeEspacoEmBranco();

        if (entrada.substr(posicao, 20) != "<TokFechaParenteses>") {
            cout << "Erro - linha " << AcharLinha(posicao) << ": esperado um )\n";
        }

        else {
            posicao+= 20;
        }

        if (!ehDeclaracaoComposta(nullptr)) {
            return false;
        }

        return true;
    }

    return false;
}

bool ehDeclaracaoDeRetorno(No* raiz) {

    int i = 0;

    ConsomeEspacoEmBranco();

    if(entrada.substr(posicao, 11) != "<TokReturn>") {
        return false;
    }
    
    posicao += 11;
    ConsomeEspacoEmBranco();

    if (entrada.substr(posicao, 7) != "<TokPv>") {

        if (!ehExpressaoDeAtribuicao(nullptr)) {
            return false;
        }
    }

    ConsomeEspacoEmBranco();

    if(entrada.substr(posicao, 7) != "<TokPv>") {
        cout << "Erro - linha " << AcharLinha(posicao) << ": esperado um ;\n";
        return false;
    }

    else {
        posicao += 7;
    }

    return true;
}

bool ehDeclaracaoDeRegraDeTres(No* raiz) {

    int i = 0;

    ConsomeEspacoEmBranco();

    if (entrada.substr(posicao, 16) == "<TokRegraDeTres>") {

        posicao += 16;
        ConsomeEspacoEmBranco();

        if (entrada.substr(posicao, 19) != "<TokAbreParenteses>") {
            cout << "Erro - linha " << AcharLinha(posicao) << ": esperado um (\n";
        }

        else {
            posicao+= 19;
        }

        if (!ehExpressaoPrimaria(nullptr)) {
            cout << "Erro - linha " << AcharLinha(posicao) << ": esperado um identificador, constante ou expressao\n";
        }

        ConsomeEspacoEmBranco();

        if(entrada.substr(posicao, 6) != "<TokV>") {
            cout << "Erro - linha " << AcharLinha(posicao) << ": esperado uma virgula separando os parametros\n";
        }

        else{
            posicao += 6;
        }

        if (!ehExpressaoPrimaria(nullptr)) {
            cout << "Erro - linha " << AcharLinha(posicao) << ": esperado um identificador, constante ou expressao\n";
        }

        ConsomeEspacoEmBranco();

        if(entrada.substr(posicao, 6) != "<TokV>") {
            cout << "Erro - linha " << AcharLinha(posicao) << ": esperado uma virgula separando os parametros\n";
        }

        else{
            posicao += 6;
        }

        if (!ehExpressaoPrimaria(nullptr)) {
            cout << "Erro - linha " << AcharLinha(posicao) << ": esperado um identificador, constante ou expressao\n";
        }

        ConsomeEspacoEmBranco();

        if (entrada.substr(posicao, 20) != "<TokFechaParenteses>") {
            cout << "Erro - linha " << AcharLinha(posicao) << ": esperado um )\n";
        }

        else {
            posicao+= 20;
        }

        ConsomeEspacoEmBranco();

        if(entrada.substr(posicao, 7) != "<TokPv>") {
            cout << "Erro - linha " << AcharLinha(posicao) << ": esperado um ;\n";
        }

        else{
            posicao += 7;
        }
    }

    else {
        return false;
    }

    return true;
}

bool ehExpressaoDeAtribuicao(No* raiz) {

    int i = 0;

    int aux2;
    aux = aux2 = posicao;

    if(!ehExpressaoPosFixa(nullptr)) {

        posicao = aux;

        if(ehExpressaoLogicaOU(nullptr)) {
            return true;
        }

        return false;
    }

    ConsomeEspacoEmBranco();

    if(entrada.substr(posicao, 15) != "<TokAtribuicao>") {

        posicao = aux2;

        if(ehExpressaoLogicaOU(nullptr)) {
            return true;
        }

        return false;
    }

    posicao += 15;

    if(!ehExpressaoDeAtribuicao(nullptr)) {
        return false;
    }

    return true;
}

bool ehExpressaoLogicaOU(No* raiz) {

    int i = 0;

    if(!ehExpressaoLogicaE(nullptr)) {
        return false;
    }

    ConsomeEspacoEmBranco();

    if(entrada.substr(posicao, 7) != "<TokOr>") {
        return true;
    }

    else if(entrada.substr(posicao, 7) == "<TokOr>") {

        posicao += 7;

        if(!ehExpressaoLogicaOU(nullptr)) {
            return false;
        }
    }

    return true;
}

bool ehExpressaoLogicaE(No* raiz) {

    int i = 0;

    if(!ehExpressaoDeIgualdade(nullptr)) {
        return false;
    }

    ConsomeEspacoEmBranco();

    if(entrada.substr(posicao, 8) != "<TokAnd>") {
        return true;
    }

    else if(entrada.substr(posicao, 8) == "<TokAnd>") {

        posicao += 8;

        if(!ehExpressaoLogicaE(nullptr)) {
            return false;
        }
    }

    return true;
}

bool ehExpressaoDeIgualdade(No* raiz) {

    int i = 0;

    if(!ehExpressaoRelacional(nullptr)) {
        return false;
    }

    ConsomeEspacoEmBranco();

    if(entrada.substr(posicao, 15) != "<TokComparacao>" && entrada.substr(posicao, 14) != "<TokDiferente>") {
        return true;
    }

    else if(entrada.substr(posicao, 15) == "<TokComparacao>") {

        posicao += 15;
        ConsomeEspacoEmBranco();

        if(!ehExpressaoDeIgualdade(nullptr)) {
            return false;
        }
    }

    else {

        posicao += 14;

        if(!ehExpressaoDeIgualdade(nullptr)) {
            return false;
        }
    }

    return true;
}

bool ehExpressaoRelacional(No* raiz) {

    int i = 0;

    if(!ehExpressaoAditiva(nullptr)) {
        return false;
    }

    ConsomeEspacoEmBranco();

    if(entrada.substr(posicao, 10) != "<TokMaior>" && entrada.substr(posicao, 10) != "<TokMenor>" &&
    entrada.substr(posicao, 15) != "<TokMaiorIgual>" && entrada.substr(posicao, 15) != "<TokMenorIgual>") {
        return true;
    }

    else if(entrada.substr(posicao, 10) == "<TokMaior>") {

        posicao += 10;

        if(!ehExpressaoRelacional(nullptr)) {
            return false;
        }
    }

    else if(entrada.substr(posicao, 10) == "<TokMenor>") {

        posicao += 10;

        if(!ehExpressaoRelacional(nullptr)) {
            return false;
        }
    }

    else if(entrada.substr(posicao, 15) == "<TokMaiorIgual>") {

        posicao += 15;

        if(!ehExpressaoRelacional(nullptr)) {
            return false;
        }
    }

    else {

        posicao += 15;

        if(!ehExpressaoRelacional(nullptr)) {
            return false;
        }
    }

    return true;
}

bool ehExpressaoAditiva(No* raiz) {

    int i = 0;

    if(!ehExpressaoMultiplicativa(nullptr)) {
        return false;
    }

    ConsomeEspacoEmBranco();

    if(entrada.substr(posicao, 9) != "<TokMais>" && entrada.substr(posicao, 10) != "<TokMenos>") {
        return true;
    }

    else if(entrada.substr(posicao, 9) == "<TokMais>") {

        posicao += 9;

        if(!ehExpressaoAditiva(nullptr)) {
            return false;
        }
    }

    else {

        posicao += 10;

        if(!ehExpressaoAditiva(nullptr)) {
            return false;
        }
    }

    return true;
}

bool ehExpressaoMultiplicativa(No* raiz) {

    int i = 0;

    if(!ehExpressaoPosFixa(nullptr)) {
        return false;
    }

    ConsomeEspacoEmBranco();

    if(entrada.substr(posicao, 10) != "<TokVezes>" && entrada.substr(posicao, 8) != "<TokDiv>") {
        return true;
    }

    else if(entrada.substr(posicao, 10) == "<TokVezes>") {

        posicao += 10;

        if(!ehExpressaoMultiplicativa(nullptr)) {
            return false;
        }
    }

    else {

        posicao += 8;

        if(!ehExpressaoMultiplicativa(nullptr)) {
            return false;
        }
    }

    return true;
}

bool ehExpressaoPosFixa(No* raiz) {

    int i = 0;

    if(!ehExpressaoPrimaria(nullptr)) {
        return false;
    }

    ConsomeEspacoEmBranco();

    if(entrada.substr(posicao, 18) != "<TokAbreColchetes>" && entrada.substr(posicao, 19) != "<TokAbreParenteses>" && 
    entrada.substr(posicao, 6) != "<TokP>") {
        return true;
    }

    while(entrada.substr(posicao, 18) == "<TokAbreColchetes>" || entrada.substr(posicao, 19) == "<TokAbreParenteses>" || 
    entrada.substr(posicao, 6) == "<TokP>") {

        ConsomeEspacoEmBranco();

        if(entrada.substr(posicao, 18) == "<TokAbreColchetes>") {

            posicao += 18;

            if(!ehExpressaoDeAtribuicao(nullptr)) {
                return false;
            }

            ConsomeEspacoEmBranco();

            if(entrada.substr(posicao, 19) != "<TokFechaColchetes>") {
                cout << "Erro - linha " << AcharLinha(posicao) << ": esperado um ]\n";
            }

            else {
                posicao += 19;
            }
        }

        else if(entrada.substr(posicao, 19) == "<TokAbreParenteses>") {

            posicao += 19;
            ConsomeEspacoEmBranco();

            if(entrada.substr(posicao, 20) != "<TokFechaParenteses>") {

                if(!ehListaDeExpressaoDeArgumento(nullptr)) {
                    return false;
                }
            }

            ConsomeEspacoEmBranco();

            if(entrada.substr(posicao, 20) != "<TokFechaParenteses>") {
            cout << "Erro - linha " << AcharLinha(posicao) << ": esperado um )\n";
            }

            else {
                posicao += 20;
            }
        }

        else {

            posicao += 6;

            if(!ehIdentificador(nullptr)) {
                return false;
            }
        }
    }

    return true;

}

bool ehListaDeExpressaoDeArgumento(No* raiz) {

    int i = 0;

    if(!ehExpressaoDeAtribuicao(nullptr)) {
        return false;
    }

    ConsomeEspacoEmBranco();

    if(entrada.substr(posicao, 6) != "<TokV>") {
        return true;
    }

    posicao += 6;

    if(!ehListaDeExpressaoDeArgumento(nullptr)) {
        return false;
    }
    
    return true;
}

bool ehExpressaoPrimaria(No* raiz) {

    int i = 0;

    ConsomeEspacoEmBranco();
    
    if(!ehIdentificador(nullptr) && !ehConstante(nullptr) && entrada.substr(posicao, 19) != "<TokAbreParenteses>") {
        return false;
    }

    if(entrada.substr(posicao, 19) == "<TokAbreParenteses>") {

        posicao += 19;

        if(!ehExpressaoDeAtribuicao(nullptr)) {
            return false;
        }

        ConsomeEspacoEmBranco();

        if(entrada.substr(posicao, 20) != "<TokFechaParenteses>") {
            cout << "Erro - linha " << AcharLinha(posicao) << ": esperado um )\n";
        }

        else {
            posicao += 20;
        }
    }

    return true;
}

bool ehConstante(No* raiz) {

    int i = 0;

    if(!ehInteiro(nullptr) && !ehFlutuante(nullptr) && !ehCaractere(nullptr)) {
        return false;
    }

    return true;
}

bool ehIdentificador(No* raiz) {

    ConsomeEspacoEmBranco();

    if (entrada[posicao] != '<'){
        return false;
    }

    posicao++;

    if(entrada.substr(posicao, 5) != "TokID") {
        posicao--;
        return false;
    }

    posicao += 5;

    while(entrada[posicao] != '>') {
        posicao++;
    }

    posicao++;

    return true;
}

bool ehInteiro(No* raiz) {

    ConsomeEspacoEmBranco();

    if (entrada[posicao] != '<'){
        return false;
    }

    posicao++;

    if(entrada.substr(posicao, 9) != "TokNumint") {
        posicao--;
        return false;
    }

    posicao += 9;

    while(entrada[posicao] != '>') {
        posicao++;
    }

    posicao++;

    return true;
}

bool ehFlutuante(No* raiz) {

    ConsomeEspacoEmBranco();

    if (entrada[posicao] != '<'){
        return false;
    }

    posicao++;

    if(entrada.substr(posicao, 11) != "TokNumfloat") {
        posicao--;
        return false;
    }

    posicao += 11;

    while(entrada[posicao] != '>') {
        posicao++;
    }

    posicao++;

    return true;
}

bool ehCaractere(No* raiz) {

    ConsomeEspacoEmBranco();

    if (entrada[posicao] != '<'){
        return false;
    }

    posicao++;

    if(entrada.substr(posicao, 12) != "TokCaractere") {
        posicao--;
        return false;
    }

    posicao += 12;

    while(entrada[posicao] != '>') {
        posicao++;
    }

    posicao++;

    return true;
}

bool AnalisarSintatico(string nomedoarquivo, TabelaDeSimbolos* table) {

    std::ifstream arquivo(nomedoarquivo); // Abre o arquivo para leitura

    No* Arvore = nullptr;

    if (arquivo.is_open()) { // Verifica se o arquivo foi aberto com sucesso
        std::string conteudo((std::istreambuf_iterator<char>(arquivo)), std::istreambuf_iterator<char>());

        // Processa o conteúdo do arquivo
        entrada = conteudo;
        tabela = table;

        Token* programa = new Token("REGRA", "PROGRAMA", to_string(escopo), 0, 0);

        Arvore = criarNo(programa);

        if(ehPrograma(Arvore)) {
            return true;
        }

        else {
            deletarArvore(Arvore);
            return false;
        }

        arquivo.close(); // Fecha o arquivo
    } 
    else {
        std::cout << "Erro ao abrir o arquivo." << std::endl;
    }

    return false;
}