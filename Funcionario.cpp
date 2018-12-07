#include <iostream>
#include "Funcionario.h"
//FAZER OUTROS INCLUDES

using namespace std;

string Funcionario::getNome() const { return nome;}

unsigned int Funcionario::getSalario() const { return salario;}

string Funcionario::getFuncao() const { return funcao;}

string Funcionario::getPtVenda() const { return pt_venda;}

bool Funcionario::operator<(Funcionario f){

	if(getSalario() < f.getSalario())
		return true;

	else if(getNome() < f.getNome())
		return true;

	return false;
}
