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
	int prox_manut;

	/**
	 * Indica se a composicao se encontra avariada ou nao
	 */
	bool avaria;


public:

	/**
	 * Construtor da classe
	 * @param prox_manut Dias que faltam ate a proxima manutencao da composicao
	 * @param avaria Se a maquina esta avariada ou nao
	 */
	Composicao(int prox_manut, bool avaria): prox_manut(prox_manut), avaria(avaria){}


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
	 * Overload do operador menor para a classe Composicao (permitindo assim o seu uso em filas de prioridade)
	 * @param c Composicao a comparar com o objeto que chamou o metodo
	 * @return True se a 1a composicao e menor
	 */
	bool operator<(Composicao c);
};

#endif /* COMPOSICAO_H_ */
