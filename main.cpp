#include <iostream>
#include <string>
#include <iomanip>
#include "conversor.h"
#include "parser.h"
#include "formatador.h"
#define NEGRITO "\033[1m"
#define RESET "\033[0m"
#define VERMELHO "\033[31m"
#define VERDE "\033[32m"

using namespace std;

int main() {
    string valor;
    int baseOrigem, baseFinal;

    cout << endl;
    cout << "--- Conversor Universal ---" << endl;
    cout << endl;

    cout << NEGRITO << "Digite o numero que deseja converter: " << RESET;
    cin >> valor;
    cout << endl;

    cout << NEGRITO << "Digite a base atual desse numero (2, 8, 10, 16): " << RESET;
    cin >> baseOrigem;
    cout << endl;

    if (!validarEntrada(valor, baseOrigem)) {
        return 1;
    }

    cout << NEGRITO << "Digite para qual base deseja converter esse numero (2, 8, 10, 16): " << RESET;
    cin >> baseFinal;
    cout << endl;

    string parteInteira = "";
    string parteFracionaria = "";
    bool encontrouPonto = false;

    for (size_t i = 0; i < valor.length(); i++) {
        if (valor[i] == '.' || valor[i] == ',') {
            encontrouPonto = true;
            continue;
        }

        if (!encontrouPonto) {
            parteInteira += valor[i];
        } else {
            parteFracionaria += valor[i];
        }
    }
    
    if (parteFracionaria == "") {
        parteFracionaria = "0";
    }

    int valorEmDecimal;
    if (baseOrigem == 10) {
        double numDecimalGeral = 0.0;
        double parteFracionariaRegressiva = 0.1;
        bool depoisDoPonto = false;
        
        for (size_t i = 0; i < valor.length(); i++) {
            if (valor[i] == '.' || valor[i] == ',') {
                depoisDoPonto = true;
                continue;
            }
            int digito = valor[i] - '0';
            if (digito >= 0 && digito <= 9) {
                if (!depoisDoPonto) {
                    numDecimalGeral = (numDecimalGeral * 10.0) + digito;
                }
            }
        }
        valorEmDecimal = (int)numDecimalGeral;
    } else {
        valorEmDecimal = baseParaDecimal(parteInteira, baseOrigem);
    }

    string inteiroFinal = conversorDeDecimal(valorEmDecimal, baseFinal);
    string fracaoEmDecimal = converterFracionarioParaDecimal(parteFracionaria, baseOrigem);
    double fracaoDouble = stringFracionariaParaDouble(fracaoEmDecimal);
    resultadoFracionario fracaoConvertida = converterFracionarioParaBase(fracaoDouble, baseFinal);

    cout << VERDE << "O resultado da conversao e: " << inteiroFinal << RESET;
    if (fracaoDouble > 0.000001 && fracaoConvertida.valor != "" && fracaoConvertida.valor != "0") {
		string str = fracaoConvertida.valor;
		int tamanho = 0;
		while(str[tamanho] != '\0') {
			tamanho++;
		}
		int ultimaPosicaoUtil = tamanho -1;
		while(ultimaPosicaoUtil >= 0 and str[ultimaPosicaoUtil] == '0') {
			ultimaPosicaoUtil--;
		}
        if(ultimaPosicaoUtil >= 0){
			cout << VERDE << ",";
			for(int i = 0; i <= ultimaPosicaoUtil; i++){
				cout << str[i];
			}
			cout << RESET;
		}
    }
    
    if (fracaoConvertida.truncado) {
        cout << VERMELHO << " (Houve truncamento)" << RESET;
    }
    cout << endl << endl;

    if (baseOrigem == 10) {
        mostrarDivisoes(valorEmDecimal, baseFinal);
        if (fracaoDouble > 0.000001) {
            cout << endl;
            cout << NEGRITO << "Passo a passo da conversao da parte fracionaria:" << RESET << endl;
            mostrarParteFracionaria(fracaoDouble, baseFinal);
        }
        } else {
            mostrarSomatorio(parteInteira, baseOrigem, 10);
            if (fracaoDouble > 0.000001) {
                cout << endl;
                cout << NEGRITO << "Passo a passo da conversao da parte fracionaria: " << RESET << endl;
                mostrarParteFracionaria(fracaoDouble, baseFinal);
            }
        if (baseFinal != 10){
            cout << endl;
            cout << NEGRITO << "Segunda etapa: Convertendo o resultado decimal: "<< RESET << endl;
            mostrarDivisoes(valorEmDecimal, baseFinal);
        }
    }
    return 0;
}
