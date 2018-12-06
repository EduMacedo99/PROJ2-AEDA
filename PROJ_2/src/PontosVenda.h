#ifndef PONTOSVENDA_H_
#define PONTOSVENDA_H_

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "Maquina.h"
#include "Bilhete.h"
#include "Utente.h"

/**
 * Classe utilizada para englobar toda a informacao referente aos pontos de venda da cidade
 */
class PontosVenda{

private:

	/**
	 * Vetor com todos os pontos de venda da cidade
	 */
	vector<Maquina*> ptsVenda;

	/**
	 * Vetor com todos os utentes que possuem um bilhete assinatura
	 */
	vector<Utente*> utentes;


public:

	/**
	 * Destrutor da classe
	 */
	~PontosVenda();

	/**
	 * Metodo que imprime toda a informacao que possui sobre todos os pontos de venda da cidade
	 */
	void imprime() const;

	/**
	 * Metodo que imprime toda a informacao que possui sobre todas as maquinas da cidade
	 */
	void imprimeSoMaquinas() const;

	/**
	 * Metodo que imprime toda a informacao que possui sobre todas as lojas da cidade
	 */
	void imprimeSoLojas() const;

	/**
	 * Metodo que imprime a informacao relativa aos utentes que possuem um bilhete assinatura
	 */
	void imprimeAssinantes() const;

	/**
	 * Metodo que imprime toda a informacao relativa a um ponto de venda, especificado pelo local onde se encontra
	 * @param local Local onde se encontra o ponto de venda
	 */
	void imprimePDV(string local) const;

	/**
	 * Metodo que extrai a informacao de um ficheiro, atualizando a informacao dos utentes e pontos de venda
	 * @param ficheiro Nome do ficheiro onde esta guardada a informacao
	 * @return Retorna 0 se executou sem problemas, 1 se ocorreu um erro (ex: ficheiro nao existente)
	 */
	int load_file(string ficheiro);

	/**
	 * Metodo que guarda toda a informacao que possui num ficheiro de texto, para uso futuro
	 * @param ficheiro Nome do ficheiro onde vai ser guardada a informacao
	 * @return Retorna 0 se executou sem problemas, 1 se ocorreu um erro
	 */
	int save_file(string ficheiro);

	/**
	 * Metodo que procura por um determinado utente, dado o seu id, e o retorna, se for encontrado
	 * @param id Id do utente que se quer encontrar
	 * @return Utente que se queria encontrar
	 */
	Utente* getUtente(unsigned int id) const;


	/**
	 * Retorna o vetor com todos os utentes que possuem um bilhete assinatura
	 * @return Vetor com os utentes
	 */
	vector<Utente*> getUtentesAssinatura() const;


	/**
	 * Metodo que "compra" um bilhete ocasional num ponto de venda especificado pelo seu local
	 * @param local Local do ponto de venda
	 * @param bo Bilhete que se pretende comprar
	 */
	void comprarBilheteOcasional(string local, BilheteOcasional& bo);

	/**
	 * Metodo que "compra" um bilhete assinatura numa loja especificada pelo seu local (lanca uma excecao se nao existir nenhum PDV no local)
	 * @param local Local da loja
	 * @param ba Bilhete que se pretende comprar
	 * @return True se conseguiu comprar, false caso contrario (PDV e uma maquina)
	 */
	bool comprarBilheteAssinatura(string local, BilheteAssinatura& ba);

	/**
	 * Metodo que tenta encontrar uma loja que esteja num determinado local, retornando o indice dessa loja no vetor dos pontos de venda (se ela existir)
	 * @param local Local da loja
	 * @return Indice da loja no vetor dos pontos de venda (-1 se nao existir)
	 */
	int findLoja(string local) const;


	/**
	 * Metodo que tenta encontrar um ponto de venda que esteja num determinado local, retornando o indice desse elemento no vetor dos pontos de venda (se existir)
	 * @param local Local onde queremos procurar o ponto de venda
	 * @return Indice no vetor (-1 se nao existir)
	 */
	int findPDV(string local) const;

	/**
	 * Metodo que elimina um utente da base de dados, assim como a informacao relativa ao seu bilhete de assinatura
	 * @param id Id do utente que se pretende eliminar
	 */
	void eliminaAssinatura(unsigned int id);

	/**
	 * Metodo que elimina uma loja ou maquina, com base no local onde se encontra
	 * @param local Local onde o ponto de venda se encontra
	 */
	void eliminaPDV(string local);


	/**
	 * Metodo que adiciona um novo ponto de venda a base de dados (lanca uma excecao se ja existe um ponto de venda nesse local)
	 * @param m Nova maquina/loja a ser adicionada
	 */
	void addPDV(Maquina* m);

	/**
	 * Metodo que adiciona um novo ponto de venda a base de dados (lanca uma excecao se ja existe um ponto de venda nesse local)
	 * @param local Local do novo ponto de venda
	 * @param loja Indica se o ponto de venda a adicionar e uma loja ou nao
	 */
	void addPDV(string local, bool loja);


	/**
	 * Metodo que adiciona um novo utente ao vetor de utentes
	 * @param u Utente que ira ser adicionado
	 */
	void addUtente(Utente* u);

	/**
	 * Metodo que ordena os elementos do vetor de utentes por ordem alfabetica
	 */
	void sortUtentesNome();

	/**
	 * Metodo que ordena os elementos do vetor de utentes por ordem crescente de id
	 */
	void sortUtentesId();

	/**
	 * Metodo que ordena os elementos do vetor de PDVs por ordem crescente de local
	 */
	void sortPDVsPorLocal();

	/**
	 * Metodo que ordena os bilhetes num determinado ponto de venda
	 * @param local Local do ponto de venda
	 * @param crescente Indica se a ordem desejada e a ordem crescente ou decrescente do preco dos bilhetes
	 */
	void sortPDV(string local, bool crescente);

};

#endif /* PONTOSVENDA_H_ */
