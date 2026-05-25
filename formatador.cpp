#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include "conversor.h"

using namespace std;

void mostrarDivisoes(int num, int baseDestino){
	cout<<endl;
	cout<<"---------Passo-a-passo-Divisoes-Sucessivas---------"<<endl;
	cout<<"Dividendo"<<" | "<<"Divisor(Base)"<<" | "<<"Quociente"<<" | "<<"Resto"<<endl;
	cout<<"---------------------------------------------------"<<endl;
	cout<<endl;
	
	cout<<"Numero: "<<num<<endl;
	cout<<endl;
	
	char digitos[]="0123456789ABCDEF";
	string resultado = "";
	
		if(num==0){
			cout<<"0"<<" | "<<baseDestino<<" | "<<"0"<<" | "<<"0"<<endl;
			}
	
	int resto;
	
	while(num>0){
		int quociente;
		resto = num%baseDestino;
		resultado += digitos[resto];
		quociente=num/baseDestino;
		cout<<"------------------------"<<endl;
		cout<<"D"<<" | "<<"D"<<" | "<<"Q"<<" | "<<"R"<<endl;
		cout<<num<<" | "<<baseDestino<<" | "<<quociente<<" | "<<resto<<endl;
		num=quociente;
		}
		resultado = inverter(resultado);
	
	cout<<"---------Resultado-----------"<<endl;
	cout<<resultado<<endl;
	}
	
void mostrarSomatorio(string num, int baseNum, int baseResultado){
	cout<<endl;
	cout<<"---------Passo-a-passo-Somatorio----------"<<endl;
	int n, tam;
	tam = num.length();
	int resultado=0;
	char digitos[]="0123456789ABCDEF";

	cout<<"Numero: "<<num<<endl;
	cout<<"Base do numero: "<<baseNum<<endl;
	cout<<"Converter para base: "<<baseResultado<<endl;
	cout<<endl;
	
	if(baseResultado==10){
		int t=tam-1;
		int valor;
	for(int i=0;i<tam;i++){
		n = transformarChar(num[i]);
		valor = n*(pow(baseNum,t));
		resultado+=valor;
		cout<<num[i]<<" = "<<n<<" * "<<baseNum<<" ^ "<<t<<" = "<<valor<<endl;
		t--;
			}
		cout<<"Soma total em decimal: "<<resultado<<endl;											
		}
		
		string resultadoFinal = "";
		
		if(baseNum==2){
		if(baseResultado==8){
			if(num.length()%3==0){
				cout<<"Numero = "<<num<<endl;
				}
		while(num.length() % 3 != 0){
			num = "0" + num;
		}
			tam = num.length();
		cout<<"Numero em grupos de 3 = "<<num<<endl;
		cout<<endl;

			int cont=1;
		for(int i=0;i<tam;i+=3){
			string grupo = num.substr(i, 3);
			cout<<cont<<" grupo: "<<grupo<<endl;
			int valor = baseParaDecimal(grupo,2);
			mostrarSomatorio(grupo,2,10);
			cont++;
			resultadoFinal += digitos[valor];
			cout<<endl;
				}
			cout<<"Conversao final: "<<resultadoFinal<<endl;	
				}
		if(baseResultado==16){
				if(num.length()%4==0){
					cout<<"Numero = "<<num<<endl;
					}
				while(num.length() % 4 != 0){
			num = "0" + num;
		}
			tam = num.length();
		cout<<"Numero em grupos de 4 = "<<num<<endl;

		int cont=1;
		for(int i=0;i<tam;i+=4){
			string grupo=num.substr(i, 4);
			cout<<cont<<" grupo: "<<grupo<<endl;
			int valor = baseParaDecimal(grupo,2);
			mostrarSomatorio(grupo, 2, 10);
			cont++;
			resultadoFinal += digitos[valor];
			cout<<endl;
					}
				cout<<"Conversao final: "<<resultadoFinal<<endl;	
			}
		}
		
		if(baseNum==8){
			string binario="";
		if(baseResultado==2){
			cout<<"Transforme cada numero em binario."<<endl;
			for(int i=0; i<tam;i++){
				cout<<num[i]<<" octal = "<<octalBin(num[i])<<" binario."<<endl;
				binario+=octalBin(num[i]);
				}
				cout<<"Soma dos resultados: ";
				cout<<binario<<endl;
			cout<<"Conversao final: "<<binario<<endl;	
			}	
		if(baseResultado==16){
			cout<<"Transforme cada numero em binario."<<endl;
			string binario = "";
			for(int i=0;i<tam;i++){
				cout<<num[i]<<" octal = "<<octalBin(num[i])<<" binario."<<endl;
				binario+=octalBin(num[i]);
			}
		cout<<"Juncao dos binarios: ";
		cout<<binario<<endl;
		cout<<"Agora, faca a conversao de binario para base("<<baseResultado<<"): "<<endl;
		mostrarSomatorio(binario,2,16);
		resultadoFinal = conversorDeBase(binario,2,16);
		cout<<"Conversao final: "<<resultadoFinal<<endl;
			}
		}
		
		if(baseNum==16){
		if(baseResultado==2){
			for(int i=0;i<tam;i++){
				cout<<"Transforme "<<num[i]<<" em binario."<<endl;
				cout<<num[i]<<" hexadecimal = "<<hexBin(num[i])<<" binario."<<endl;
				resultadoFinal+=hexBin(num[i]);
				}
				cout<<"Soma dos resultados: ";
				cout<<resultadoFinal<<endl;
				cout<<"Conversao final: "<<resultadoFinal<<endl;
			}
		
		if(baseResultado==8){
			string binario = "";
			for(int i=0;i<tam;i++){
				cout<<"Transforme "<<num[i]<<" em binario."<<endl;
				cout<<num[i]<<" hexadecimal = "<<hexBin(num[i])<<" binario."<<endl;
				binario+=hexBin(num[i]);
			}
			cout<<"Juncao dos binarios: "<<binario<<endl;
			cout<<"Agora, faca a conversao de binario para base("<<baseResultado<<"): "<<endl;
			mostrarSomatorio(binario,2,8);
			resultadoFinal = conversorDeBase(binario,2,8);
			cout<<"Conversao final: "<<resultadoFinal<<endl;
			}	
		}	
	}	
	
void mostrarParteFracionaria(double valorFracionario, int baseDestino){
	char digitos[] = "0123456789ABCDEF";
	bool truncado=false;
	double resto=valorFracionario;
	string resultado="";
	
	cout<<endl;
	cout<<"--------Passo-a-passo-Parte-Fracionaria---------"<<endl;
	cout<<"Parte fracionaria: "<<valorFracionario<<endl;
	cout<<"Converter para base: "<<baseDestino<<endl;
	
	for (int i = 0; i < 16; i++) {
		double multiplicacao = resto*baseDestino;
        cout<<resto<<" * "<<baseDestino<<" = "<<multiplicacao<<endl;
		cout<<endl;
        int digitoInteiro = (int)multiplicacao;
        cout<<"Convertendo os digitos: "<<digitoInteiro<<endl;
		cout<<endl;
        resultado += digitos[digitoInteiro];
        resto = multiplicacao-digitoInteiro;
        
        cout<<"Novo valor fracionario: "<<resto<<endl;
        cout<<"Resultado parcial: "<<resultado<<endl;
        
        if (resto == 0) {
			break;
			}
        if (i == 15 and resto > 0) truncado = true;
			}
		cout<<"Conversao final: "<<resultado<<endl;
		if(truncado){
		cout<<"Resultado truncado apos 16 casas."<<endl;
			}			
	}
