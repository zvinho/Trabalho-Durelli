#include <iostream>
#include <string>
#include <cmath>
#include "conversor.h"

using namespace std;

resultadoFracionario converterFracionarioParaBase(double valorFracionario, int baseDestino) {
    char digitos[] = "0123456789ABCDEF";
    string resultado = "";
    bool truncado = false;
    double resto = valorFracionario;
    
	if (resto < 0.000001) {
		resto = 0.0;
	}

    for (int i = 0; i < 16; i++) {
        resto *= baseDestino;
        int digitoInteiro = (int)resto;
        resultado += digitos[digitoInteiro];
        resto -= digitoInteiro;

        if (resto < 0.000001) {
            resto = 0.0;
            break;
        }
        if (i == 15 && resto > 0) truncado = true;
    }

    return {truncado, resultado}; 
}

string inverter(string num){
    string invertida = "";
    int tam = num.length();
    
    for(int i = tam - 1; i >= 0; i--){
        invertida += num[i];
    }
    return invertida;
}

int transformarChar(char n){
    if(n >= '0' && n <= '9'){
        return n - '0';
    }
    if(n >= 'a' && n <= 'f'){
        return n - 'a' + 10;
    }   
    if(n >= 'A' && n <= 'F'){
        return n - 'A' + 10;
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
        return "0";
    }

    string str = to_string(somaTotal);

    int tamStr = 0;
    while (str[tamStr] != '\0') {
        tamStr++;
    }

    int fimUtil = tamStr - 1;
    while (fimUtil >= 0 && str[fimUtil] == '0') {
        fimUtil--;
    }

    if (fimUtil >= 0 && (str[fimUtil] == '.' || str[fimUtil] == ',')) {
        fimUtil--;
    }
    string apenasFracao = "";
    bool encontrouPonto = false;

    for (int i = 0; i <= fimUtil; i++) {
        if (encontrouPonto) {
            apenasFracao += str[i];
        }
        if (str[i] == '.') {
            encontrouPonto = true;
        }
    }

    if (apenasFracao == "") {
        return "0";
    } else {
        return apenasFracao;
    }
}

string conversorDeDecimal(int num, int baseDestino){
    char digitos[] = "0123456789ABCDEF";
    string resultado = "";
    
    if(num == 0){
        return "0";
    }
    
    int resto;
    while(num > 0){
        resto = num % baseDestino;
        resultado += digitos[resto];
        num /= baseDestino;
    }
    resultado = inverter(resultado);
    return resultado;
}

int baseParaDecimal(string num, int baseNum) {
    int tam = num.length();
    int resultado = 0;
    int peso = 1; 

    for (int i = tam - 1; i >= 0; i--) {
        int n = transformarChar(num[i]);
        resultado += n * peso;
        peso *= baseNum; 
    }                                         

    return resultado;
}

string octalBin(char n){
    if(n=='0') {
        return "000";
    }
    if(n=='1') {
        return "001";
    }
    if(n=='2') {
        return "010";
    }
    if(n=='3') {
        return "011";
    }
    if(n=='4') {
        return "100";
    }
    if(n=='5') {
        return "101";
    }
    if(n=='6') {
        return "110";
    }
    return "111";
}

string hexBin(char n){
    if(n=='0') {
        return "0000";
    }
    if(n=='1'){ 
        return "0001";
    }
    if(n=='2'){
        return "0010";
    }
    if(n=='3'){ 
        return "0011";
    }
    if(n=='4'){ 
        return "0100";
    }
    if(n=='5'){ 
        return "0101";
    }
    if(n=='6'){ 
        return "0110";
    }
    if(n=='7'){ 
        return "0111";
    }
    if(n=='8'){ 
        return "1000";
    }
    if(n=='9'){ 
        return "1001";
    }
    if(n=='A' or n=='a'){ 
        return "1010";
    }
    if(n=='B' or n=='b'){ 
        return "1011";
    }
    if(n=='C' or n=='c'){
        return "1100";
    }
    if(n=='D' or n=='d'){ 
        return "1101";
    }
    if(n=='E' or n=='e'){ 
        return "1110";
    }
    return "1111";
}

string conversorDeBase(string num, int baseNum, int baseResultado){
    string resultado = "";
    int tam;
    
    if(baseResultado == 10){
        resultado = to_string(baseParaDecimal(num, baseNum));
        return resultado;
    }

    if(baseNum == 2){
        if(baseResultado == 8){
            while(num.length() % 3 != 0){
                num = "0" + num;
            }
            tam = num.length();

            for(int i = 0; i < tam; i += 3){
                string grupo = "";
                grupo += num[i];
                grupo += num[i+1];
                grupo += num[i+2];
                resultado += conversorDeBase(grupo, 2, 10);
            }
        }
        if(baseResultado == 16){
            while(num.length() % 4 != 0){
                num = "0" + num;
            }
            tam = num.length();

            for(int i = 0; i < tam; i += 4){
                string grupo = "";
                grupo += num[i];
                grupo += num[i+1];
                grupo += num[i+2];
                grupo += num[i+3];
                resultado += conversorDeBase(grupo, 2, 10);
            }
        }
    }
    
    if(baseNum == 8){
        tam = num.length();
        if(baseResultado == 2){
            for(int i = 0; i < tam; i++){
                resultado += octalBin(num[i]);
            }
        }   
        if(baseResultado == 16){
            string binario = "";
            for(int i = 0; i < tam; i++){
                binario += octalBin(num[i]);
            }
            resultado = conversorDeBase(binario, 2, 16);
        }
    }
    
    if(baseNum == 16){
        tam = num.length();
        if(baseResultado == 2){
            for(int i = 0; i < tam; i++){
                resultado += hexBin(num[i]);
            }
        }
        if(baseResultado == 8){
            string binario = "";
            for(int i = 0; i < tam; i++){
                binario += hexBin(num[i]);
            }
            resultado = conversorDeBase(binario, 2, 8);
        }   
    }
    
    return resultado;
}

double stringFracionariaParaDouble(string strFracao) {
    double resultado = 0.0;
    double peso = 0.1;

    for (size_t i = 0; i < strFracao.length(); i++) {
        int digito = strFracao[i] - '0'; 
        if (digito >= 0 && digito <= 9) {
            resultado += digito * peso;
            peso /= 10.0;
        }
    }
    return resultado;
}
