#ifndef BILHETE_H_
#define BILHETE_H_

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Utente.h"
using namespace std;

/**
 * Classe utilizada para retratar bilhetes de metro (possui duas subclasses).
 */
class Bilhete{

protected:
	/**
	 * Categoria do bilhete.
	 */
	string categoria;

	/**
	* Preco do bilhete.
	*/
	float preco;

	/**
    * Vector que relaciona cada zona com os precos de cada tipo de bilhete (vetor externo contem os vetores
    * com os precos relativos as zonas Z1, Z2, Z3 e Z4, respetivamente, e cada subvetor de zona contem os precos
    * relativos a um bilhete unico, diario, ou de assinatura normal, respetivamente).
    */
	static vector<vector<float> > pZonas;



public:

	/**
	 * Construtor da classe.
	 * @param categoria Categoria do bilhete.
	 * @param preco Preco do bilhete.
	 */
	Bilhete(string categoria, float preco): categoria(categoria), preco(preco) {}

	/**
	 * Construtor da classe (variavel preco ira ser inicializada pelas subclasses, quando se souber a especificacao).
	 * @param categoria Categoria do bilhete.
	 */
	Bilhete(string categoria): categoria(categoria), preco(0){}

	/**
	 * Destrutor virtual da classe (apenas declarado).
	 */
	virtual ~Bilhete(){}

	/**
     * Metodo que devolve a categoria do bilhete.
     * @return Categoria do bilhete.
	 */
	string getCategoria() const;


	/**
	 * Metodo que devolve o preco do bilhete.
	 * @return Preco do bilhete.
	 */
	float getPreco() const;


	/**
	 * Metodo que devolve o vetor contendo os precos de cada zona.
	 * @return Vetor com todos os precos relativos a cada zona.
	 */
	static vector<vector<float> > getPrecosZona();


	/**
	 * Metodo que determina o preco para um bilhete de uma determianda categoria e especificacao (diario, unico ou tipo de assinatura (junior, estudante etc.).
	 * Se categoria ou especificacao sao invalidos, retorna com preco igual a 0.
	 * @param categoria categoria do bilhete.
	 * @param especificacao especificacao do bilhete.
	 * @return Preco do bilhete determinado.
	 */
	float makePreco(string categoria,string especificacao) const;

	/**
	 * Metodo que inicializa/muda o valor da variavel preco.
	 * @param preco Preco que queremos dar ao bilhete.
	 */
	void setPreco(float preco);

	/**
	 * Metodo que imprime no ecra a informacao do bilhete que invoca o metodo (declarado como virtual devido
	 * as classes derivadas; metodo virtual abstrato pois nao ha a necessidade de criar objetos do tipo Bilhete,
	 * mas sim dos tipos BilheteAssinatura e BilheteOcasional).
	 */
	virtual void imprimeInfoBilhete() const = 0;

	/**
	 * Metodo que insere o valor dos precos de cada zona na variavel pZonas.
	 * @param precos Vetor com todos os precos.
	 */
	static void setPrecosZona(vector<vector<float> > precos);

	/**
	 * Metodo static que imprime os precos dos bilhetes relativos a cada zona.
	 */
	static void imprimePrecosZona();

	/**
	 * Overload do operador menor para esta classe.
	 * @param b Bilhete a comparar com o objeto que chama o metodo.
	 * @return Se e menor ou nao.
	 */
	bool operator<(const Bilhete& b) const;
};



/**
 * Classe utilizada para retratar bilhetes de metro do tipo ocasional.
 */
class BilheteOcasional : public Bilhete{

private:
	/**
	 * Duracao do bilhete, sendo que pode ser um bilhete unico ou diario.
	 */
	string duracao;

public:

	/**
	 * Construtor da classe bilhete ocasional.
	 * @param categoria Categoria do bilhete.
	 * @param preco Preco do bilhete.
	 * @param duracao Duracao da validade do bilhete.
	 */
	BilheteOcasional(string categoria, float preco,  string duracao): Bilhete(categoria, preco), duracao(duracao){}

	/**
	 * Construtor da classe bilhete ocasional (o preco e calculado em funcao da categoria e duracao).
	 * @param categoria Categoria do bilhete.
	 * @param duracao Duracao da validade do bilhete.
	 */
	BilheteOcasional(string categoria, string duracao): Bilhete(categoria), duracao(duracao){ this->setPreco(makePreco(categoria, duracao));}

	/**
	 * Destrutor da classe (apenas declarado)
	 */
	 ~BilheteOcasional(){}


	/**
	 * Metodo que devolve a duracao da viagem.
	 * @return Duracao da viagem.
	 */
	string getDuracao() const;

	/**
	 * Metodo que imprime no ecra a informacao do bilhete ocasional que invoca o metodo.
	 */
	void imprimeInfoBilhete() const;

};


/**
 * Classe utilizada para retratar bilhetes de metro do tipo assinatura.
 */
class BilheteAssinatura : public Bilhete{

private:
	/**
	 * Tipo da assinatura (se e normal, estudante, junior ou senior)
	 */
	string tipo;

	/**
	 * Dados do assinante.
	 */
	Utente* assinante;

public:


	/**
	 * Construtor da classe bilhete assinatura
	 * @param categoria Categoria do bilhete
	 * @param preco Preco do bilhete
	 * @param tipo Tipo do bilhete
	 * @param assinante Dados do assinante
	 */
	BilheteAssinatura(string categoria, float preco,  string tipo, Utente* assinante): Bilhete(categoria, preco), tipo(tipo), assinante(assinante){}

	/**
	 * Construtor da classe bilhete assinatura (o preco e calculado em funcao da categoria e duracao).
	 * @param categoria Categoria do bilhete.
	 * @param tipo Tipo do bilhete
	 * @param assinante Dados do assinante
	 */
	BilheteAssinatura(string categoria, string tipo, Utente* assinante): Bilhete(categoria), tipo(tipo), assinante(assinante){ this->setPreco(makePreco(categoria, tipo));}

	/**
	 * Destrutor da classe (apenas declarado).
	 */
	~BilheteAssinatura() {}


	/**
	 * Metodo que devolve o tipo de assinatura.
	 * @return Tipo da assinatura.
	 */
	string getTipo() const;

	/**
	 * Metodo de acesso ao assinante de um bilhete assinatura especifico.
	 * @return Apontador para o assinante do bilhete.
     */
	Utente* getAssinante() const;


	/**
	 * Metodo que imprime no ecra a informacao do bilhete assinatura que invoca o metodo.
	 */
	void imprimeInfoBilhete() const;

};


/**
 * Funcao para ordenar bilhetes ocasionais por ordem decrescente de preco.
 */
bool ordenaBilhetesODecrescente(const BilheteOcasional &b1, const BilheteOcasional &b2);

/**
 * Funcao para ordenar bilhetes assinatura por ordem decrescente de preco.
 */
bool ordenaBilhetesADecrescente(const BilheteAssinatura &b1, const BilheteAssinatura &b2);


/**
 * Classe utilizada para lancar excecoes em caso de procura de um bilhete que nao existe (nao tem atributos/metodos, apenas indica que nao existe).
 */
class BilheteInexistente{};



#endif /* BILHETE_H_ */
