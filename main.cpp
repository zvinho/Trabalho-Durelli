#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <cmath>
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
	int opcao;

    cout << endl;
    cout << "--- Conversor Universal ---" << endl;
    cout << endl;
	cout<<"Escolha o metodo de conversao:"<<endl;
	cout<<endl;
	cout<<"1. Conversao manual."<<endl;
	cout<<"2. Modo batch(arquivo.csv)."<<endl;
	cout<<"3. Quiz"<<endl;
	cout<<"4. Calculadora de maximos."<<endl;
	cout<<endl;
	cout<<"Escolha: ";
	cin>>opcao;
	cout<<endl;

	if(opcao == 1) {

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

	cout<<"Deseja ver o passo a passo da conversao? (s/n): "<<endl;
	char resposta;
	cin>>resposta;

	if(resposta=='s' or resposta=='S'){
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
		}
	}
   


else if(opcao == 2) {
	ifstream entrada("entrada.csv");
	ofstream saida("saida.csv");

	if(!entrada.is_open()) {
		cout << "Erro ao abrir o arquivo de entrada." << endl;
		return 1;
	}
	string linha;
	
	getline(entrada, linha);
	saida<<"valor; base_origem; resultado; base_destino"<<endl;

	while(getline(entrada,linha)){
		string valor="";
		string baseOrigem="";
		string baseDestino="";
		int tipo=0;

		for(int i=0;i<linha.length();i++){
			if(linha[i]==';'){
				tipo++;
			}else{
				if(tipo==0){
					valor+=linha[i];
				}else if(tipo==1){
					baseOrigem+=linha[i];
				}else if(tipo==2){
					baseDestino+=linha[i];
				}
			}
		}
		int baseNum=0;
		int baseResultado=0;
		for(int i=0;i<baseOrigem.length();i++){
			baseNum = baseNum * 10 + transformarChar(baseOrigem[i]);
			}
		for(int i=0;i<baseDestino.length();i++){
			baseResultado = baseResultado * 10 + transformarChar(baseDestino[i]);
		}


		if (!validarEntrada(valor, baseNum)) {
			saida << valor << ";" << baseOrigem << ";" << "ERRO" << ";" << baseDestino << endl;
			continue;
		}

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
		if (baseNum == 10) {
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
			valorEmDecimal = baseParaDecimal(parteInteira, baseNum);
		}

		string inteiroFinal = conversorDeDecimal(valorEmDecimal, baseResultado);
		string fracaoEmDecimal = converterFracionarioParaDecimal(parteFracionaria, baseNum);
		double fracaoDouble = stringFracionariaParaDouble(fracaoEmDecimal);
		resultadoFracionario fracaoConvertida = converterFracionarioParaBase(fracaoDouble, baseResultado);
		string resultadoCompleto = inteiroFinal;

		if (fracaoDouble > 0.000001 && fracaoConvertida.valor != "" && fracaoConvertida.valor != "0") {
			resultadoCompleto += ",";
			string str = fracaoConvertida.valor;
			int tamanho = 0;
			while(str[tamanho] != '\0') {
				tamanho++;
			}
			int ultimaPosicaoUtil = tamanho -1;
			while(ultimaPosicaoUtil >= 0 and str[ultimaPosicaoUtil] == '0') {
				ultimaPosicaoUtil--;
			}
			for(int i = 0; i <= ultimaPosicaoUtil; i++) {
				resultadoCompleto += str[i];
			}
		}

		saida<<valor<<";"<<baseOrigem<<";"<<resultadoCompleto<<";"<<baseDestino<<endl;

		}
		entrada.close();
		saida.close();
	}
	
else if(opcao == 3) {
	cout<<"------Quiz de conversao de bases------"<<endl;
	cout<<"O quiz tera 5 questoes, sendo cada com determinado nivel."<<endl;
	int acertos=0;
	int questao=5;
	for(int i=1;i<=questao;i++){
		int bases[]={2,8,10,16};
		int baseNum = bases[rand()%4];
		int baseResultado = bases[rand()%4];
	
		while(baseResultado==baseNum){
			baseResultado = bases[rand()%4];
		}

		string num = "";
		char digitos[] = "0123456789ABCDEF";
		int tam;

		if(i==1){
			tam=1;
		}else if(i==2){
			tam=2;
		}else if(i==3 or i==4){
			tam=3;
		}else{
			tam=4;
		}

		for(int j=0;j<tam;j++){
			int lim;

			if(baseNum==2){
				lim=2;
			}else if(baseNum==8){
				lim=8;
			}else if(baseNum==10){
				lim=10;
			}else {
				lim=16;
			}
			num+=digitos[rand()%lim];

		}

		if(i>=4){
			num+=",";

			for(int i=0;i<2;i++){
				int lim;

				if(baseNum==2){
					lim=2;
				}else if(baseNum==8){
					lim=8;
				}else if(baseNum==10){
					lim=10;
				}else {
					lim=16;
				}
				num+=digitos[rand()%lim];
			}
		}
		cout<<"NIVEL "<<i<<endl;
		cout<<endl;
		cout<<"Converta "<<num<<" da base("<<baseNum<<") para base("<<baseResultado<<")."<<endl;
		string resposta;

		cin>>resposta;

		string parteInteira = "";
		string parteFracionaria = "";
		bool encontrouPonto = false;

		for(size_t i=0;i<num.length();i++){
			if(num[i]=='.' or num[i]==','){
				encontrouPonto=true;
				continue;
			}
			if(!encontrouPonto){
				parteInteira+=num[i];
			}else {
				parteFracionaria+=num[i];
			}
		}
		int decimalInteiro=baseParaDecimal(parteInteira, baseNum);
		string resultado=conversorDeDecimal(decimalInteiro, baseResultado);

		if(parteFracionaria!=""){
			string decimalFracao=converterFracionarioParaDecimal(parteFracionaria, baseNum);
			double fracaoDouble=stringFracionariaParaDouble(decimalFracao);
			resultadoFracionario fracaoConvertida=converterFracionarioParaBase(fracaoDouble, baseResultado);
			 	if(fracaoConvertida.valor!="0" and fracaoConvertida.valor!=""){
					resultado+=",";
					resultado+=fracaoConvertida.valor;
				}
			}

				if(resposta==resultado){
					cout<<VERDE<<"Resposta correta!"<<RESET<<endl;
					acertos++;
		}else{
			cout<<VERMELHO<<"Resposta incorreta!"<<RESET<<endl;
			cout<<"A resposta correta: "<<fixed<<setprecision(3)<<resultado<<RESET<<endl;
		}
	}
		cout<<endl;

		cout<<"Quiz finalizado!"<<endl;
		cout<<"Voce acertou "<<acertos<<" de "<<questao<<" questoes."<<endl;
		
	}
	
	
	else if(opcao == 4) {
		cout<<"------Calculadora de maximos------"<<endl;
		int K;
		cout<<"Digite a quantidade de bits: ";
		cin>>K;
		cout<<endl;

		unsigned long long maximo;
		maximo= pow(2, K)-1;

		string bin, oct, hex;

		bin=conversorDeDecimal(maximo, 2);
		oct=conversorDeDecimal(maximo, 8);
		hex=conversorDeDecimal(maximo, 16);
		
		mostrarMaximos(K, maximo, bin, oct, hex);

	}


    return 0;
}
