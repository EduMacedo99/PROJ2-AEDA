#include <string>

#ifndef FUNCIONARIO_H_
#define FUNCIONARIO_H_

using namespace std;

//NUNO
//USAR SETS
//DEFINIR OPERADOR <
//O SET FICA NA CLASSE PONTOS DE VENDA, OU NUMA CLASSE COM A INFORMACAO NOVA
//MEMBRO COM STRING DO LOCAL DO PONTO DE VENDA

/**
 * Classe que representa os funcionarios que trabalham nos pontos de venda do metro
 */
class Funcionario{
protected:
	/**
	 * Nome do funcionario
	 */
	string nome;

	/**
	 * Salario do funcionario em euros
	 */
	unsigned int salario;

	/**
	 * Funcao do funcionario
	 */
	string funcao;

	/**
	 * Local do ponto de venda em que o funcionario trabalha; so ha um ponto de venda em cada local
	 */
	string pt_venda;

public:
	/**
	 * Construtor da classe
	 * @param n Nome do funcionario
	 * @param sal Salario do funcionario
	 * @param f Funcao do funcionario
	 * @param pt_v Ponto de venda em que o funcionario trabalha
	 */
	Funcionario(string n, unsigned int sal, string f, string pt_v):
		nome(n), salario(sal), funcao(f), pt_venda(pt_v){}

	/**
	 * Destrutor da classe
	 */
	~Funcionario() {}

	/**
	 * Metodo que devolve o nome do funcionario
	 * @return Nome do funcionario
	 */
	string getNome() const;

	/**
	 * Metodo que devolve o salario do funcionario
	 * @return Salario do funcionario
	 */
	unsigned int getSalario() const;

	/*
	 * Metodo que devolve a funcao do funcionario
	 * @return Funcao do funcionario
	 */
	string getFuncao() const;

	/*
	 * Metodo que devolve o local do ponto de venda em que o funcionario trabalha
	 * @return Local do ponto de venda
	 */
	string getPtVenda() const;

	/*
	 * Overload do operador menor para esta classe
	 * @param Funcionario a comparar ao objeto que chama o metodo
	 * @return True se o funcionario que chama o metodo tem menor salario ou vem primeiro em ordem alfabetica ou false se nao
	 */
	bool operator<(Funcionario f);
};

#endif /* FUNCIONARIO_H_ */
