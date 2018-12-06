#ifndef MAQUINA_H_
#define MAQUINA_H_

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "Bilhete.h"
#include "Utente.h"

 using namespace std;



 /**
  * Classe que retrata as maquinas de metro, que vendem bilhetes ocasionais (tem como subclasse a classe Loja).
  */
 class Maquina {

 protected:
	 /**
	  * Local da maquina/loja
	  */
	 string local;

	 /**
	  * Vetor de bilhetes ocasionais que contem todos os bilhetes ocasionais vendidos nesse ponto de venda.
	  */
	 vector<BilheteOcasional> bilhetesO;


 public:
	 /**
	  * Construtor da classe maquina.
	  * @param local Local da maquina.
	  */
	 Maquina(string local): local(local){}

	 /**
	  * Destrutor virtual da classe (apenas declarado).
	  */
	 virtual ~Maquina(){};

	 /**
	  * Retorna o local da maquina/loja.
	  * @return Local da maquina/loja.
	  */
	 string getLocal() const;

	 /**
	  * Retorna o vetor de bilhetes ocasionais da maquina (ou loja).
	  * @return Bilhetes ocasionais vendidos no ponto de venda.
	  */
	 vector<BilheteOcasional> getBilhetesO() const;

	 /**
	  * Imprime no ecra as informacoes da maquina
	  */
	 virtual void imprimeInfoPDV() const;

	 /**
	  * Acrescenta o bilhete ocasional ao vetor bilhetesO
	  * @param bilhete Bilhete ocasional que se pretende adicionar ao vetor bilhetesO
	  */
	 void addBilheteO(BilheteOcasional& bilhete);


	 /**
	  * Metodo virtual utilizado para se saber, tendo um apontador para Maquina (Maquina*), se este aponta para uma Maquina ou para uma Loja, para nao se recorrer a metodos mais complicados
	  * @return Retorna falso se for uma maquina, verdadeiro se for uma loja
      */
	 virtual bool eLoja() const;

	 /**
	  * Metodo que ordena os bilhetes de uma maquina, por ordem crescente de preco
	  */
	 virtual void sortBilhetesCrescente();

	 /**
	  * Metodo que ordena os bilhetes de uma maquina, por ordem decrescente de preco
	  */
	 virtual void sortBilhetesDecrescente();
 };



/**
 * Classe (derivada de Maquina) que caracteriza todas as lojas, em que se pode comprar os dois tipos de bilhetes
 */
class Loja : public Maquina{

private:

	/**
     * Vector que contem todos os bilhetes de assinatura que ja foram vendidos na loja
     */
	vector<BilheteAssinatura> bilhetesA;

public:
		/**
		 * Construtor da classe
		 * @param local Local da loja
		 */
		Loja(string local): Maquina(local) {}

		/**
		 * Destrutor da classe (apenas declarado)
		 */
		~Loja(){}


		/**
		 * Metodo que devolve os bilhetes assinatura vendidos na loja
		 * @return Vetor que contem todos os bilhetes assinatura vendidos na loja
		 */
		vector<BilheteAssinatura> getBilhetesA() const;

		/**
		 * Metodo que devolve a posicao do bilhete assinatura cujo utente tem um determinado id
		 * @param id Id do utente que se quer encontrar
		 * @return Indice do utente (-1 se nao existir)
		 */
		int findUtente(unsigned int id) const;

		/**
		* Metodo que imprime a informacao da loja
		**/
		void imprimeInfoPDV() const;

		/**
		* Metodo que adiciona um bilhete assinatura ao vetor bilhetesA
		* @param bilhete Bilhete assinatura que se deseja adicionar
		*/
		void addBilheteA(BilheteAssinatura& bilhete);

		/**
		 * Metodo que elimina bilhete assinatura do vetor bilhetesA com base no id do utente
		 * @param id Id do utente cujo bilhete assinatura sera eliminado
		 * @return True se conseguiu apagar o bilhete, false caso contrario
		 */
		bool eraseBilheteA(unsigned int id);

		/**
		 * Metodo virtual utilizado para se saber, tendo um apontador para Maquina (Maquina*), se este aponta para uma Maquina ou para uma Loja, para nao se recorrer a metodos mais complicados
		 * @return Retorna falso se for uma maquina, verdadeiro se for uma loja
	     */
		bool eLoja() const;

		/**
		 * Metodo que retorna os utentes associados a bilhetes assinatura, que foram comprados nessa loja
		 * @return Vetor com os utentes/assinantes
		 */
		vector<Utente*> getAssinantes() const;

		/**
		 * Metodo que ordena os bilhetes de uma loja, por ordem crescente de preco
		 */
		void sortBilhetesCrescente();

		/**
		 * Metodo que ordena os bilhetes de uma loja, por ordem decrescente de preco
		 */
		void sortBilhetesDecrescente();
};


/**
 * Funcao utilizada para a ordenacao de pontos de venda, por ordem crescente de local
 */
bool ordenaPorLocal(const Maquina* m1, const Maquina* m2);


/**
 * Classe que vai ser utilizada quando se procura uma maquina/loja num local que nao existe (irao ser lancadas excecoes desta classe)
 */
class LocalInexistente{

private:
	/**
	 * Local nao existente
	 */
	string local;

public:
	/**
	 * Construtor da classe
	 * @param local Local nao existente
	 */
	LocalInexistente(string local): local(local){}

	/**
	 * Metodo de acesso ao nome do local que nao existe
	 * @return Local nao existente
	 */
	string getLocal() { return local; }

};


/**
 * Classe que vai ser utilizada quando se tenta adicionar uma maquina/loja num local em que ja existe uma (irao ser lancadas excecoes desta classe)
 */
class LocalRepetido{

private:
	/**
	 * Local repetido
	 */
	string local;

public:
	/**
	 * Construtor da classe
	 * @param local Local repetido
	 */
	LocalRepetido(string local): local(local){}

	/**
	 * Metodo de acesso ao nome do local repetido
	 * @return Local repetido
	 */
	string getLocal() { return local; }

};
#endif /* MAQUINA_H_ */
