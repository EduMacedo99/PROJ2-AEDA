#include <iostream>
#include "Funcionario.h"

using namespace std;

unsigned int Funcionario::nextIdF = 0;

string Funcionario::getNome() const { return nome;}

unsigned int Funcionario::getSalario() const { return salario;}

string Funcionario::getFuncao() const { return funcao;}

string Funcionario::getPtVenda() const { return pt_venda;}

unsigned int Funcionario::getId() const { return id;}

bool Funcionario::operator<(const Funcionario &f) const{

	if(salario == f.getSalario())
		return nome < f.getNome();
	else return salario < f.getSalario();
}

bool Funcionario::operator==(const Funcionario &f) const{
	return (salario == f.getSalario() && nome == f.getNome());
}


unsigned int FuncionarioInexistente::getId(){
	return id;
}
