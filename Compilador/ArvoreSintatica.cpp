#include <iostream>
#include <vector>
#include "Tokens.cpp"
#include "palavra_reservada.cpp"

struct No{
    Token* info;
    std::vector<No*> filhos;
};

No* criarNo(Token* chave) {
    No* novoNo = new No();
    novoNo->info = chave;
    return novoNo;
}

void deletarArvore(No* root) {
    if(root != nullptr) {
        int i = 0;
        while(i < root->filhos.size()) {
            deletarArvore(root->filhos.at(i));
            i++;
        }
    }
    delete(root);
}