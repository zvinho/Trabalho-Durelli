#include <iostream>
#include <string>
#include <cmath>
#include "conversor.h"
using namespace std;

struct resultadoFracionario {
	bool truncado;
	string valor;
};

resultadoFracionario converterFracionarioParaBase(double valorFracionario, int baseDestino) {
    char digitos[] = "0123456789ABCDEF";
    string resultado = "";
    bool truncado = false;
    double resto = valorFracionario;
	if (resto < 0.000001) resto = 0.0;

	for (int i = 0; i < 16; i++) {
        resto *= baseDestino;
        int digitoInteiro = (int)resto;
        resultado += digitos[digitoInteiro];
        resto -= digitoInteiro;

        if (resto == 0) {
			break;
		}
        if (i == 15 && resto > 0) truncado = true;
    }

	return {truncado, resultado}; 
}

string inverter(string num){
	string invertida="";
	int tam;
	
	tam = num.length();
	
	for(int i=tam-1;i>=0;i--){
		invertida+=num[i];
		}
	return invertida;
	
	}

int transformarChar(char n){
	if(n>='0' and n<='9'){
		return n - '0';
		}
	if(n>='a' and n<='f'){
		return n-'a'+10;
		}	
	if(n>='A' and n<='F'){
		return n-'A'+10;
		}	
	return -1;	
		
	}	

string converterFracionarioParaDecimal(string parteFracionaria, int baseOrigem) {
    double somaTotal = 0.0;
    int expoente = 1;

    for (size_t i = 0; i < parteFracionaria.length(); i++) {
        char c = parteFracionaria[i];

        if (c == '-' || c == '.' || c == ',') {
            continue;
        }

        int valorDigito = transformarChar(c);
        
        if (valorDigito >= 0) {
            somaTotal += valorDigito * pow(baseOrigem, -expoente);
            expoente++;
        }
    }

    if (abs(somaTotal) < 0.000001) {
        return "0.0";
    }

    return to_string(somaTotal);
}

string conversorDeDecimal(int num, int baseDestino){
	char digitos[]="0123456789ABCDEF";
	string resultado = "";
	
		if(num==0){
			return "0";
			}
	
	int resto;
	
	while(num>0){
		resto = num%baseDestino;
		resultado += digitos[resto];
		num/=baseDestino;
		
		}
		resultado = inverter(resultado);
	return resultado;
}

int baseParaDecimal(string num, int baseNum) {
    int n, tam;
    tam = num.length();
    int resultado = 0;
    int t = tam - 1;
    
    for (int i = 0; i < tam; i++) {
        n = transformarChar(num[i]);
        resultado += n * pow(baseNum, t); 
        t--;                                 
    }                                         

    return resultado;
}

string octalBin(char n){
    if(n=='0'){
		return "000";
	}
    else if(n=='1'){
		return "001";
	}
    else if(n=='2'){
		return "010";
	}
    else if(n=='3'){
		return "011";
	}
    else if(n=='4'){
		return "100";
	}
    else if(n=='5'){
		return "101";
	}
    else if(n=='6'){
		return "110";
	}
		return "111";
	
}

string hexBin(char n){
	if(n=='0'){
		return "0000";
	}
    else if(n=='1'){
		return "0001";
	}
    else if(n=='2'){
		return "0010";
	}
    else if(n=='3'){
		return "0011";
	}
    else if(n=='4'){
		return "0100";
	}
    else if(n=='5'){
		return "0101";
	}
    else if(n=='6'){
		return "0110";
	}
    else if(n=='7'){
		return "0111";
	}
    else if(n=='8'){
		return "1000";
	}
    else if(n=='9'){
		return "1001";
	}
    else if(n=='A'){
		return "1010";
	}
    else if(n=='B'){
		return "1011";
	}
    else if(n=='C'){
		return "1100";
	}
    else if(n=='D'){
		return "1101";
	}
    else if(n=='E'){
		return "1110";
	}
    return "1111";
}


string conversorDeBase(string num, int baseNum, int baseResultado){
	string resultado="";
	int tam;
	tam = num.length();
	
	if(baseResultado==10){
		resultado = to_string(baseParaDecimal(num, baseNum));
		return resultado;
		}
	if(baseNum==2){
		if(baseResultado==8){
		while(num.length() % 3 != 0){
			num = "0" + num;
		}

		for(int i=0;i<tam;i+=3){
			string grupo = num.substr(i, 3);
				resultado += conversorDeBase(grupo, 2, 10);
				}
			}
			if(baseResultado==16){
				while(num.length() % 4 != 0){
			num = "0" + num;
		}

		for(int i=0;i<tam;i+=4){
			string grupo=num.substr(i, 4);
				resultado += conversorDeBase(grupo, 2, 10);
					}
				}
	}
	
	if(baseNum==8){
		if(baseResultado==2){
			for(int i=0; i<tam;i++){
				resultado+=octalBin(num[i]);
				}
			}	
		if(baseResultado==16){
			string binario = "";
			for(int i=0;i<tam;i++){
			binario+=octalBin(num[i]);
			}
		resultado = conversorDeBase(binario,2,16);
			}
		
		}
	
	if(baseNum==16){
		if(baseResultado==2){
			for(int i=0;i<tam;i++){
				resultado+=hexBin(num[i]);
				}
			}
		
		if(baseResultado==8){
			string binario = "";
			for(int i=0;i<tam;i++){
			binario+=hexBin(num[i]);
			}
		resultado = conversorDeBase(binario,2,8);
			}	
		}
	
	return resultado;
}



