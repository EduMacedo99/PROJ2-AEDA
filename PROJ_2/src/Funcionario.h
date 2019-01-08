#include <string>

#ifndef FUNCIONARIO_H_
#define FUNCIONARIO_H_

using namespace std;


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

	/**
	 * Metodo que devolve a funcao do funcionario
	 * @return Funcao do funcionario
	 */
	string getFuncao() const;

	/**
	 * Metodo que devolve o local do ponto de venda em que o funcionario trabalha
	 * @return Local do ponto de venda
	 */
	string getPtVenda() const;

	/**
	 * Metodo que muda o salario do funcionario
	 * @param s Salario que o funcionario vai passar a ter
	 */
	void changeSalario(unsigned int s);

	/**
	 * Metodo que muda a funcao do funcionario
	 * @param f Funcao que o funcionario vai passar a ter
	 */
	void changeFuncao(string f);

	/**
	 * Metodo que muda o ponto de venda em que o funcionario trabalha
	 * @param pt_venda Ponto de venda em que o funcionario vai passar a trabalhar
	 */
	void changePtVenda(string pt_vendaN);

	/**
	 * Overload do operador menor para esta classe
	 * @param f Funcionario a comparar ao objeto que chama o metodo
	 * @return True se o funcionario que chama o metodo tem menor salario ou vem primeiro em ordem alfabetica ou false se nao
	 */
	bool operator<(const Funcionario &f) const;

	/**
	 * Overload do operador igual para esta classe
	 * @param f Funcionario a comparar ao objeto que chama o metodo
	 * @return True se ambos os funcionarios tiverem o mesmo id
	 */
	bool operator==(const Funcionario &f) const;

	/**
	 * Metodo que imprime no ecra a informacao relativa a um funcionario
	 */
	void imprimeInfoFuncionario() const;
};


class FuncionarioInexistente{

private:
	/**
	 * Nome do funcionario que se tentou procurar
	 */
	string nome;

	/**
	 * Salario do funcionario que se tentou procurar
	 */
	unsigned int salario;

public:
	/**
	 * Construtor da classe
	 * @param id Id do funcionario nao existente
	 */
	FuncionarioInexistente(string name, unsigned int s): nome(name), salario(s){}

	/**
	 * Metodo de acesso ao nome do funcionario que nao existe
	 * @return Nome do funcionario nao existente
	 */
	string getNome();

	/**
	 * Metodo de acesso ao salario do funcionario que nao existe
	 * @return Salario do funcionario nao existente
	 */
	unsigned int getSalario();
};

#endif /* FUNCIONARIO_H_ */

