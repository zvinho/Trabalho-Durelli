#ifndef CONVERSOR_H
#define CONVERSOR_H

#include <iostream>
#include <string>
#include <cmath>

struct resultadoFracionario {
    bool truncado;
    std::string valor;
};

std::string conversorDeDecimal(int inteiroNum, int base);
std::string converterFracionarioParaDecimal(std::string parteFracionaria, int baseOrigem);
std::string conversorDeBase(std::string num, int baseNum, int baseResultado);
std::string inverter(std::string num);
int transformarChar(char n);
std::string converterFracionarioParaDecimal(std::string parteFracionaria, int baseOrigem);
std::string conversorDeDecimal(int num, int baseDestino);
int baseParaDecimal(std::string num, int baseNum);
resultadoFracionario converterFracionarioParaBase(double valorFracionario, int baseDestino);
std::string octalBin(char n);
std::string hexBin(char n);
std::string conversorDeBase(std::string num, int baseNum, int baseResultado);
double stringFracionariaParaDouble(std::string strFracao);


#endif
