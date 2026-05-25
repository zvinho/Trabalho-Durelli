#include <iostream>
#include <string>
#include "parser.h"

using namespace std;

bool validarEntrada(string valor, int base) {
	int separadores = 0;
	if(valor.empty()){
		cout << "ERRO: Não foi digitado nenhum valor para conversão." << endl;
		return false;
	}
	if ((base == 2) or (base == 8) or (base == 10) or (base == 16)){
	for(char c : valor) {
		if(c == '.' or c == ',') {
			separadores++;
			if(separadores > 1) {
				cout << "ERRO: O valor informado possui mais de um separador decimal." << endl;
				return false;
			}
		continue;
		}
	if (valor.length() == 1 and separadores == 1){
		cout << "ERRO: O valor informado não pode conter somente o separador decimal" << endl;
		return false;
	}
int valorDigito;
if(c >= '0' and c <= '9') {
	valorDigito = c - '0';
}else if(c >= 'A' and c <= 'F') {
	valorDigito = c - 'A' + 10;
}else if(c >= 'a' and c <= 'f') {
	valorDigito = c - 'a' + 10;
}else {
	cout << "ERRO: Caractere '" << c << "' invalido." << endl;
	return false;
}
if(valorDigito >= base) {
	cout << "ERRO: O dígito '" << c << "' nao pertence a base " << base << "." << endl;
	return false;
}
}
	return true;
}
else{
	cout << "ERRO: A base informada não corresponde a um sistema numérico válido (2, 8, 10 ou 16)." << endl;
	return false;
}
}

