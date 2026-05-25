#include <iostream>
#include <string>
#include "conversor.h"
#include "parser.h"
#include "formatador.h"


using namespace std;


int main(){
	int escolha;
	int baseOrigem;

	cout<<endl;
	cout<<"--- Conversor Universal ---"<<endl;
	cout<<endl;
	cout<<"Digite 1 para converter decimal para base"<<endl;
	cout<<"Digite 2 para converter base para decimal"<<endl;
	cout<<endl;
	
	cin>>escolha;

	
	if(escolha==1){
		baseOrigem = 10;
		double num;
		int base;
		string resultado;
		bool truncamento=false;
		
		cout<<"Digite o numero decimal que deseja converter: ";
		cin>>num;
		cout<<endl;
		cout<<"Digite para qual base deseja converter o decimal (2, 8, 10, 16): ";
		cin>>base;
		cout<<endl;

		if (!validarEntrada(to_string(num), base)) {
			return 1;
		}
		
		int inteiroNum = (int) num;
		double fracao = num - inteiroNum;
		if (std::abs(fracao) < 0.000001) {
    		fracao = 0.0;
		} else {
    		fracao = std::abs(fracao);
		}
		string inteiroConvertido = conversorDeDecimal(inteiroNum, base);
		string fracaoConvertida = converterFracionarioParaDecimal(to_string(fracao), base);
		
		cout << inteiroConvertido;

		if (fracao > 0.000001) {
    		cout << "," << fracaoConvertida;
		}

		if (truncamento == true) {
    		cout << " Houve truncamento";
		}
		cout << endl;
		}

	if(escolha==2){
		string valor;
		int baseValor, baseFinal;
		string resultado;

		cout<<"Digite o numero que deseja converter: ";
		cin>>valor;
		cout<<endl;

		cout<<"Digite a base desse numero: ";
		cin>>baseValor;

		if (!validarEntrada(valor, baseValor)) {
			return 1;
		}

		baseOrigem = baseValor;
		cout<<endl;
		cout<<"Digite para qual base deseja converter esse numero: ";
		cin>>baseFinal;
		cout<<endl;
		
		if (!validarEntrada(valor, baseValor)) {
			return 1;
		}

		int valorEmDecimal = baseParaDecimal(valor, baseValor);
		
		resultado = conversorDeDecimal(valorEmDecimal, baseFinal);
		cout<<"O resultado da conversao e: "<<resultado<<endl;
		}

	return 0;
}
