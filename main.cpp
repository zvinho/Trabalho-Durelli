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


int main(){
	int escolha;
	int baseOrigem;

	cout<<endl;
	cout<<"--- Conversor Universal ---"<<endl;
	cout<<endl;
	cout<<NEGRITO<<"Digite 1 para converter decimal para base"<<RESET<<endl;
	cout<<endl;
	cout<<NEGRITO<<"Digite 2 para converter base para decimal"<<RESET<<endl;
	cout<<endl;
	
	cin>>escolha;
	
	if(escolha==1){
		baseOrigem = 10;
		string numStr;
		int base;
		string resultado;
		bool truncamento=false;
		
		cout<<endl;
		cout<< NEGRITO << "Digite o numero decimal que deseja converter: " << RESET;
		cout<<endl;
		cin>>numStr;
		cout<<endl;
		if (!validarEntrada(numStr, 10)) {
			return 1;
		}
		cout<< NEGRITO << "Digite para qual base deseja converter o decimal (2, 8, 10, 16): " << RESET;
		cout<<endl;
		cin>>base;
		cout<<endl;


		for(size_t i = 0; i < numStr.length(); i++){
			if(numStr[i] == ','){
				numStr[i] = '.';
			}
		}
		
		double num = 0.0;
        double parteFracionariaRegressiva = 0.1;
        bool depoisDoPonto = false;
        
        for (size_t i = 0; i < numStr.length(); i++) {
            if (numStr[i] == '.') {
                depoisDoPonto = true;
                continue;
            }
            int digito = numStr[i] - '0';
            if (digito >= 0 && digito <= 9) {
                if (!depoisDoPonto) {
                    num = (num * 10.0) + digito;
                } else {
                    num += digito * parteFracionariaRegressiva;
                    parteFracionariaRegressiva /= 10.0;
                }
            }
		}

		int inteiroNum = (int) num;
		if (!validarEntrada(conversorDeDecimal(inteiroNum, 10), 10)) {
			return 1;
		}
		
		double fracao = num - inteiroNum;
		if (abs(fracao) < 0.000001) {
    		fracao = 0.0;
		} else {
    		fracao = abs(fracao);
		}
		string inteiroConvertido = conversorDeDecimal(inteiroNum, base);
		resultadoFracionario fracaoConvertida = converterFracionarioParaBase(fracao, base);
		
		cout << VERDE << "O resultado da conversao e: " <<inteiroConvertido << RESET;

		if (fracao > 0.000001 and fracaoConvertida.valor != "" and fracaoConvertida.valor != "0") {
    		cout << VERDE << "," << fracaoConvertida.valor << RESET;
			mostrarParteFracionaria(fracao, base);
		}

		if (fracaoConvertida.truncado == true) {
    		cout << VERMELHO << "Houve truncamento" << RESET;
		}
		cout << endl;
		mostrarDivisoes(inteiroNum, base);
		}

	if(escolha==2){
		string valor;
		int baseValor, baseFinal;
		string resultado;

		cout<<NEGRITO<<"Digite o numero que deseja converter: "<<RESET;
		cin>>valor;
		cout<<endl;

		cout<<NEGRITO<<"Digite a base desse numero: "<<RESET;
		cin>>baseValor;

		if (!validarEntrada(valor, baseValor)) {
			return 1;
		}

		baseOrigem = baseValor;
		cout<<endl;
		cout<<NEGRITO<<"Digite para qual base deseja converter esse numero: "<<RESET;
		cin>>baseFinal;
		cout<<endl;

		string parteInteira = "";
		string parteFracionaria = "";
		bool encontrouPonto = false;

		for(size_t i = 0; i < valor.length(); i++){
			if(valor[i] == '.' or valor[i] == ','){
				encontrouPonto = true;
				continue;
			}

			if(!encontrouPonto){
				parteInteira += valor[i];
			}else{
				parteFracionaria += valor[i];
			}
			}
		if(parteFracionaria == ""){
			parteFracionaria = "0";
		}
		
		int valorEmDecimal = baseParaDecimal(parteInteira, baseValor);
		string inteiroFinal = conversorDeDecimal(valorEmDecimal, baseFinal);
		string fracaoEmDecimal = converterFracionarioParaDecimal(parteFracionaria, baseValor);
		double fracaoDouble = stringFracionariaParaDouble(fracaoEmDecimal);
		resultadoFracionario fracaoConvertida = converterFracionarioParaBase(fracaoDouble, baseFinal);



		cout<<VERDE<<"O resultado da conversao e: "<< inteiroFinal << "" << RESET;
		if (fracaoDouble > 0.000001 && fracaoConvertida.valor != "" && fracaoConvertida.valor != "0") {
            cout << VERDE << "," << fracaoConvertida.valor << RESET;
        }
        
        if (fracaoConvertida.truncado) {
            cout << VERMELHO << " (Houve truncamento)" << RESET;
        }
        cout << endl;

		if (baseValor == 10){
			mostrarDivisoes(valorEmDecimal, baseFinal);
		}else{
			mostrarSomatorio(parteInteira, baseValor, 10);
		}
		
    }

	return 0;
}
