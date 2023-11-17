#include <iostream>
#include <fstream>
#include <string>
#include "TabelaDeSimbolos.cpp"
#include "Tabela_palavras_chave.cpp"
#include "ArvoreSintatica.cpp"

using namespace std;

// Variáveis globais
string entrada;    // entrada a ser analisada
int posicao = 0;     // Posição atual no entrada
int aux = 0;    //Variável auxiliar
int valor = 0;
int escopo = 0;
TabelaDeSimbolos* tabela;

bool ehEspacoEmBranco(char c);

void ConsomeEspacoEmBranco();

int AcharLinha(int pos);

bool ehPrograma(No* raiz);

bool ehPrincipal(No* raiz);

bool ehDefinicaoDeFuncao(No* raiz);

bool ehListaDeParametros(No* raiz);

bool ehParametro(No* raiz);

bool ehDeclaracaoComposta(No* raiz);

bool ehEspecificadorDeTipo(No* raiz);

bool ehEspecificadorDeTipoDeFuncao(No* raiz);

bool ehListaDeDeclaracao(No* raiz);

bool ehDeclaracao(No* raiz);

bool ehDeclaracaoDeExpressao(No* raiz);

bool ehDeclaracaoDeSelecao(No* raiz);

bool ehDeclaracaoDeIteracao(No* raiz);

bool ehDeclaracaoDeRetorno(No* raiz);

bool ehDeclaracaoDeRegraDeTres(No* raiz);

bool ehExpressaoDeAtribuicao(No* raiz);

bool ehExpressaoLogicaOU(No* raiz);

bool ehExpressaoLogicaE(No* raiz);

bool ehExpressaoDeIgualdade(No* raiz);

bool ehExpressaoRelacional(No* raiz);

bool ehExpressaoAditiva(No* raiz);

bool ehExpressaoMultiplicativa(No* raiz);

bool ehExpressaoPosFixa(No* raiz);

bool ehListaDeExpressaoDeArgumento(No* raiz);

bool ehExpressaoPrimaria(No* raiz);

bool ehConstante(No* raiz);

bool ehIdentificador(No* raiz);

bool ehInteiro(No* raiz);

bool ehFlutuante(No* raiz);

bool ehCaractere(No* raiz);
