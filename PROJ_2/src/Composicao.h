#ifndef COMPOSICAO_H_
#define COMPOSICAO_H_

//EDUARDO RIBEIRO
//DEFINIR OPERADOR <


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

/**
 * Classe utilizada para retratar as composicoes do metro.
 */
class Composicao{

private:

	/**
	 * Numero de dias que falta ate a proxima manutencao da composicao
	 */
	int proxManut;

	/**
	 * Indica se a composicao se encontra avariada ou nao
	 */
	bool avaria;

	/**
	 * Variavel static que indica se a manutencao de uma dada composicao se encontra proxima (em dias)
	 */
	static int manutProxima;

	/**
	 * Indica o id da composicao (proprio de cada uma)
	 */
	int idC;

	/**
	 * Variavel static utilizada para atribuir um id a cada uma das composicoes
	 */
	static int compNextId;


public:

	/**
	 * Construtor da classe
	 * @param prox_manut Dias que faltam ate a proxima manutencao da composicao
	 * @param avaria Se a maquina esta avariada ou nao
	 */
	Composicao(int prox_manut, bool avaria): proxManut(prox_manut), avaria(avaria), idC(++compNextId){}

	/**
	 * Metodo que retorna o numero de id de uma dada composicao
	 * @return Numero de id
	 */
	int getID() const;

	/**
	 * Metodo que retorna o numero de dias que falta para a proxima manutencao dessa composicao
	 * @return Numero de dias que falta para a manutencao
	 */
	int getProxManut() const;

	/**
	 * Metodo que retorna true se a composicao esta avariada; false caso contrario
	 * @return True se ha uma avaria, false caso contrario
	 */
	bool getAvaria() const;

	/**
	 * Metodo que simula a manutencao de uma composicao, marcando uma nova data de manutencao, e resolvendo a avaria se ela existir
	 */
	void fazManutencao();

	/**
	 * Metodo que retorna o numero de dias que indica se a data de manutencao de uma composicao esta proxima ou nao
	 * @return Numero de dias
	 */
	static int getManutProxima();

	/**
	 * Metodo que atribui um valor ao numero de dias que indica se a manutencao de uma composicao esta proxima ou nao
	 * @param numDias Numero de dias a ser atribuido
	 */
	static void setManutProxima(int numDias);


	/**
	 * Metodo que modifica uma composicao, indicando que ela se avariou
	 */
	void poeAvariada();


	/**
	 * Overload do operador menor para a classe Composicao (permitindo assim o seu uso em filas de prioridade)
	 * @param c Composicao a comparar com o objeto que chamou o metodo
	 * @return True se a 1a composicao e menor
	 */
	bool operator<(Composicao c) const;

	/**
	 * Imprime no ecra as informacoes relativas a composicao que chamou o metodo
	 */
	void imprimeInfoComp();

	/**
	 * Metodo que simula o avanco de um dia; atualiza o numero de dias que falta ate a manutencao da composicao
	 */
	void avancaDia();
};

#endif /* COMPOSICAO_H_ */
