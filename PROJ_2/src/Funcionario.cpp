#include <iostream>
#include "Funcionario.h"

using namespace std;

string Funcionario::getNome() const { return nome;}

unsigned int Funcionario::getSalario() const { return salario;}

string Funcionario::getFuncao() const { return funcao;}

string Funcionario::getPtVenda() const { return pt_venda;}

void Funcionario::changeSalario(unsigned int s){
	this->salario = s;
}

void Funcionario::changeFuncao(string f){
	this->funcao = f;
}

void Funcionario::changePtVenda(string pt_vendaN){
	this->pt_venda = pt_vendaN;
}

bool Funcionario::operator<(const Funcionario &f) const{

	if(salario == f.getSalario())
		return nome < f.getNome();
	else return salario < f.getSalario();
}

bool Funcionario::operator==(const Funcionario &f) const{
	return (salario == f.getSalario() && nome == f.getNome());
}


string FuncionarioInexistente::getNome(){
	return nome;
}

unsigned int FuncionarioInexistente::getSalario(){
	return salario;
}
