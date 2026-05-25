#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include "conversor.h"

using namespace std;

void mostrarDivisoes(int num, int baseDestino){
	cout<<"---------Passo-a-passo-Divisoes-Sucessivas---------"<<endl;
	cout<<"Dividendo"<<" | "<<"Divisor(Base)"<<" | "<<"Quociente"<<" | "<<"Resto"<<endl;
	cout<<"---------------------------------------------------"<<endl;
	
	cout<<"Numero: "<<num<<endl;
	
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
		cout<<num<<" | "<<baseDestino<<" | "<<quociente<<" | "<<resto<<endl;
		num=quociente;
		}
		resultado = inverter(resultado);
	
	cout<<"---------Resultado-----------"<<endl;
	cout<<resultado<<endl;
	}
	
void mostrarSomatorio(string num, int baseNum, int baseResultado){
	cout<<"---------Passo-a-passo-Somatorio----------"<<endl;
	int n, tam;
	tam = num.length();
	int resultado=0;
	
	cout<<"Numero: "<<num<<endl;
	cout<<"Base do numero: "<<baseNum<<endl;
	cout<<"Converter para base: "<<baseResultado<<endl;
	
	if(baseResultado==10){
		int t=tam-1;
	for(int i=0;i<tam;i++){
		n = transformarChar(num[i]);
		resultado+=n*pow(baseNum,t);
		cout<<num[i]<<" = "<<n<<" * "<<baseNum<<" ^ "<<t<<" = "<<resultado<<endl; 
		t--;
			}
		cout<<"Soma total em decimal: "<<resultado<<endl;											
		}
		
		if(baseNum==2){
		if(baseResultado==8){
			if(num.length()%3==0){
				cout<<"Numero = "<<num;
				}
		while(num.length() % 3 != 0){
			num = "0" + num;
		}
			tam = num.length();
		cout<<"Numero = "<<num;

		for(int i=0;i<tam;i+=3){
			int cont=1;
			string grupo = num.substr(i, 3);
			cout<<cont<<" grupo: "<<grupo;
			int valor = baseParaDecimal(grupo,2,10);
			mostrarDivisoes(valor, 2);
			cont++;
			resultado += conversorDeBase(grupo, 2, 10);
				}
			cout<<"Conversao final: "<<resultado<<endl;	
				}
		if(baseResultado==16){
				if(num.length()%4==0){
					cout<<"Numero = "<<num<<endl;
					}
				while(num.length() % 4 != 0){
			num = "0" + num;
		}
			tam = num.length();
		cout<<"Numero = "<<num<<endl;

		int cont=1;
		for(int i=0;i<tam;i+=4){
			string grupo=num.substr(i, 4);
			cout<<cont<<" grupo: "<<grupo;
			int valor = baseParaDecimal(grupo,2,10);
			mostrarDivisoes(valor, 2);
			cont++;
			resultado += valor;
					}
				cout<<"Conversao final: "<<resultado<<endl;	
			}
		}
		
		if(baseNum==8){
			string binario="";
		if(baseResultado==2){
			cout<<"Primeiro transforme cada numero em binario."<<endl;
			for(int i=0; i<tam;i++){
				cout<<num[i]<<" octal = "<<octalBin(num[i])<<" binario."<<endl;
				resultado+=octalBin(num[i]);
				}
				cout<<"Soma dos resultados: ";
				cout<<resultado<<endl;
			cout<<"Conversao final: "<<resultado<<endl;	
			}	
		if(baseResultado==16){
			string resultado = "";
			for(int i=0;i<tam;i++){
				cout<<"Primeiro transforme "<<num[i]<<" em binario."<<endl;
				cout<<num[i]<<" octal = "<<octalBin(num[i])<<" binario."<<endl;
				binario+=octalBin(num[i]);
			}
		cout<<"Juncao dos binarios: ";
		cout<<binario<<endl;
		cout<<"Agora, faca a conversao de binario para base("<<baseResultado<<"): ";
		mostrarSomatorio(binario,2,16);
		resultado = conversorDeBase(binario,2,16);
		cout<<"Conversao final: "<<resultado<<endl;
			}
		}
		
		if(baseNum==16){
		if(baseResultado==2){
			for(int i=0;i<tam;i++){
				cout<<"Primeiro transforme "<<num[i]<<" em binario."<<endl;
				cout<<num[i]<<" hexadecimal = "<<hexBin(num[i])<<" binario."<<endl;
				resultado+=hexBin(num[i]);
				}
				cout<<"Soma dos resultados: ";
				cout<<resultado<<endl;
				cout<<"Conversao final: "<<resultado<<endl;
			}
		
		if(baseResultado==8){
			string binario = "";
			for(int i=0;i<tam;i++){
				cout<<"Primeiro transforme "<<num[i]<<" em binario."<<endl;
				cout<<num[i]<<" hexadecimal = "<<hexBin(num[i])<<" binario."<<endl;
				binario+=hexBin(num[i]);
			}
			cout<<"Juncao dos binarios: "<<binario<<endl;
			cout<<"Agora, faca a conversao de binario para base("<<baseResultado<<"): ";
			mostrarSomatorio(binario,2,8);
			resultado = conversorDeBase(binario,2,8);
			cout<<"Conversao final: "<<resultado<<endl;
			}	
		}	
	}	
	
void mostrarParteFracionaria(double valorFracionario, int baseDestino){
	char digitos[] = "0123456789ABCDEF";
	bool truncado=false;
	double resto=valorFracionario;
	string resultado="";
	
	cout<<"--------Passo-a-passo-Parte-Fracionaria---------"<<endl;
	cout<<"Parte fracionaria: "<<valorFracionario<<endl;
	cout<<"Converter para base: "<<baseDestino<<endl;
	
	for (int i = 0; i < 16; i++) {
		double multiplicacao = resto*baseDestino;
        cout<<resto<<" * "<<baseDestino<<" = "<<multiplicacao<<endl;
        int digitoInteiro = (int)multiplicacao;
        cout<<"Convertendo os digitos: "<<digitoInteiro<<endl;
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
