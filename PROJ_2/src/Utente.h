#ifndef UTENTE_H_
#define UTENTE_H_

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

/**
 * Classe usada para retratar um utente que possui um bilhete de assinatura
 */
class Utente{

protected:
	/**
	 * Nome do utente
	 */
	string nome;

	/**
	 * Id do utente
	 */
	unsigned int id;

	/**
	 * Variavel static que atribui aos utentes um id sequencial, nao repetido
	 */
	static unsigned int nextId;

	/**
	 * Variavel que indica o numero de dias que um utente esta inativo
	 */
	int diasInativo;

	/**
	 * Variavel static que indica o numero de dias que um utente pode ficar sem comprar um bilhete, ate ser considerado inativo
	 */
	static int numDiasExpiracao;


public:

	/**
	 * Construtor da classe (cria um utente novo, logo o numero de dias inativo e o maximo)
	 * @param nome Nome do utente
	 */
	Utente(string nome): nome(nome), id(++nextId), diasInativo(0) {}

	/**
	 * Outro construtor da classe
	 * @param nome Nome do utente
	 * @param numDias Numero de dias inativo
	 */
	Utente(string nome, int numDias): nome(nome), id(++nextId), diasInativo(numDias){}

	/**
	 * Terceiro construtor da classe
	 * @param nome Nome do utente
	 * @param id Id do utente
	 * @param numDias Numero de dias inativo
	 */
	Utente(string nome, unsigned int id, int numDias): nome(nome), id(id), diasInativo(numDias){}

	/**
	 * Destrutor virtual da classe (apenas declarado)
	 */
	virtual ~Utente(){}

	/**
	 * Metodo que imprime no ecra a informacao do utente que invoca o metodo (declarado como virtual devido as classes derivadas)
	 */
	virtual void imprimeInfoUtente() const;

	/**
	 * Metodo que retorna o nome do utente
	 * @return Nome do utente
	 */
	string getNome() const;

	/**
	 * Metodo que retorna o id do utente
	 * @return Id do utente
	 */
	unsigned int getId() const;

	/**
	 * Metodo que retorna a variavel static nextId
	 * @return Variavel static que indica o ultimo id utilizado
	 */
	static unsigned int getNextId();

	/**
	 * Metodo que atribui um determinado valor a variavel static nextId
	 * @param valor Valor a ser atribuido
	 */
	static void setNextId(unsigned int valor);

	/**
	 * Metodo que retorna o numero de dias que um determinado utente esta inativo
	 * @return Numero de dias
	 */
	int getDiasInativo() const;

	/**
	 * Metodo que da reset ao numero de dias que o utente ficou inativo (regressa a 0)
	 */
	void resetDiasInativo();

	/**
	 * Metodo que simula o avanco de um dia; atualiza o numero de dias que o utente ficou inativo
	 */
	void avancaDia();

	/**
	 * Metodo que retorna o numero maximo de dias que um utente pode ficar sem comprar um bilhete, ate ser considerado inativo
	 * @return Numero de dias
	 */
	static int getNumDiasExpiracao();

	/**
	 * Metodo que da o valor passado como argumento a variavel que indica o numero maximo de dias que um utente pode ficar sem comprar um bilhete, ate ficar inativo
	 * @param numDias Numero de dias
	 */
	static void setNumDiasExpiracao(int numDias);

	/**
	 * Operador de insercao (utilizado para a escrita em ficheiros)
	 */
	friend ostream& operator<<(ostream &os, const Utente&u);

};



/**
 * Classe utilizada para representar um estudante que possui uma assinatura
 */
class UtenteEstudante : public Utente{

private:
	/**
	 * Idade do utente
	 */
	int idade;

	/**
	 * Numero do cartao de cidadao
	 */
	string cc;

	/**
	 * Nome da escola que o estudante frequenta
	 */
	string escola;

public:
	/**
	 * Construtor da classe
	 * @param nome Nome do utente
	 * @param idade Idade do utente
	 * @param cc Numero do cartao de cidadao do utente
	 * @param escola Nome da escola do utente
	 */
	UtenteEstudante(string nome, int idade, string cc, string escola): Utente(nome), idade(idade), cc(cc), escola(escola){}

	/**
	 * Outro construtor da classe
	 * @param nome Nome do utente
	 * @param numDias Numero de dias ate expirar
	 * @param idade Idade do utente
	 * @param cc Numero do cartao de cidadao do utente
	 * @param escola Nome da escola do utente
	 */
	UtenteEstudante(string nome, int numDias, int idade, string cc, string escola): Utente(nome, numDias), idade(idade),cc(cc), escola(escola){}

	/**
	 * Terceiro construtor da classe
	 * @param nome Nome do utente
	 * @param id Id do utente
	 * @param numDias Numero de dias ate expirar
	 * @param idade Idade do utente
	 * @param cc Numero do cartao de cidadao do utente
	 * @param escola Nome da escola do utente
	 */
	UtenteEstudante(string nome, unsigned int id, int numDias, int idade, string cc, string escola): Utente(nome, id, numDias), idade(idade), cc(cc), escola(escola){}

	/**
	 * Destrutor virtual da classe (apenas declarado)
	 */
	~UtenteEstudante(){}

	/**
	 * Metodo que retorna a idade do utente
	 * @return Idade do utente
	 */
	int getIdade() const;

	/**
	 * Metodo que retorna o numero do cartao de cidadao do utente
	 * @return Numero de cc do utente
	 */
	string getCC() const;

	/**
	 * Metodo que retorna a escola do utente
	 * @return Escola do utente
	 */
	string getEscola() const;

	/**
	 * Metodo que imprime no ecra a informacao do utente estudante que invoca o metodo
	 */
	void imprimeInfoUtente() const;

	/**
	 * Operador de insercao (utilizado para a escrita em ficheiros)
	 */
	friend ostream& operator<<(ostream &os, const UtenteEstudante&u);
};



/**
 * Classe utilizada para representar um utente senior que possui uma assinatura
 */
class UtenteSenior : public Utente{

private:
	/*
	 * Idade do utente
	 */
	int idade;

	/**
	 * Numero do cartao de cidadao do utente
	 */
	string cc;

public:
	/**
	 * Construtor da classe
	 * @param nome Nome do utente
	 * @param idade Idade do utente
	 * @param cc Numero de cartao de cidadao do utente
	 */
	UtenteSenior(string nome, int idade, string cc): Utente(nome), idade(idade), cc(cc){}

	/**
	 * Outro construtor da classe
	 * @param nome Nome do utente
	 * @param numDias Numero de dias ate expirar
	 * @param idade Idade do utente
	 * @param cc Numero de cartao de cidadao do utente
	 */
	UtenteSenior(string nome, int numDias, int idade, string cc): Utente(nome, numDias), idade(idade), cc(cc){}

	/**
	 * Terceiro construtor da classe
	 * @param nome Nome do utente
	 * @param id Id do utente
	 * @param numDias Numero de dias ate expirar
	 * @param idade Idade do utente
	 * @param cc Numero de cartao de cidadao do utente
	 */
	UtenteSenior(string nome, unsigned int id, int numDias, int idade, string cc): Utente(nome, id, numDias), idade(idade), cc(cc){}


	/**
	 * Destrutor virtual da classe (apenas declarado)
	 */
	~UtenteSenior(){}

	/**
	 * Metodo que retorna a idade do utente
	 * @return Idade do utente
	 */
	int getIdade() const;

	/**
	 * Metodo que retorna o numero de cartao de cidadao do utente
	 * @return Numero de cc do utente
	 */
	string getCC() const;

	/**
	 * Metodo que imprime no ecra a informacao do utente senior que invoca o metodo
	 */
    void imprimeInfoUtente() const;

    /**
     * Operador de insercao (utilizado para a escrita em ficheiros)
     */
   	friend ostream& operator<<(ostream &os, const UtenteSenior&u);

};



/**
 * Classe utilizada para representar um utente junior que possui uma assinatura
 */
class UtenteJunior : public Utente{

private:
	/**
	 * Idade do utente
	 */
	int idade;

	/**
	 * Numero do cartao de cidadao do utente
	 */
	string cc;

public:
	/**
	 * Construtor da classe
	 * @param nome Nome do utente
	 * @param idade Idade do utente
	 * @param cc Numero de cartao de cidadao do utente
	 */
	UtenteJunior(string nome, int idade, string cc): Utente(nome), idade(idade), cc(cc){}

	/**
	 * Outro construtor da classe
	 * @param nome Nome do utente
	 * @param numDias Numero de dias ate expirar
	 * @param idade Idade do utente
	 * @param cc Numero de cartao de cidadao do utente
	 */
	UtenteJunior(string nome, int numDias, int idade, string cc): Utente(nome, numDias), idade(idade), cc(cc){}

	/**
	 * Terceiro construtor da classe
	 * @param nome Nome do utente
	 * @param id Id do utente
	 * @param numDias Numero de dias ate expirar
	 * @param idade Idade do utente
	 * @param cc Numero de cartao de cidadao do utente
	 */
	UtenteJunior(string nome, unsigned int id, int numDias, int idade, string cc): Utente(nome, id, numDias), idade(idade), cc(cc){}

	/**
	 * Destrutor virtual da classe (apenas declarado)
	 */
	~UtenteJunior(){}

	/**
	 * Metodo que retorna a idade do utente
	 * @return Idade do utente
	 */
	int getIdade() const;

	/**
	 * Metodo que retorna o numero de cartao de cidadao do utente
	 * @return Numero de cc do utente
	 */
	string getCC() const;

	/**
	 * Metodo que imprime no ecra a informacao do utente junior que invoca o metodo
	 */
    void imprimeInfoUtente() const;

    /**
     * Operador de insercao (utilizado para a escrita em ficheiros)
     */
   	friend ostream& operator<<(ostream &os, const UtenteJunior&u);

};

/**
 * Funcao utilizada para ordenacao de utentes, por ordem crescente do nome
 */
bool ordenaUtentesNome(const Utente* u1, const Utente* u2);

/**
 * Funcao utilizada para ordenacao de utentes, por ordem crescente do numero de id
 */
bool ordenaUtentesId(const Utente* u1, const Utente* u2);



/**
 * Funcao auxiliar para a leitura de ficheiros
 * @param s String com os underscores
 * @return String com os espacos
 */
string replaceUnderscoresWithSpaces(string s);


/**
 * Funcao auxiliar para a escrita de ficheiros
 * @param s String com os espacos
 * @return String com os underscores
 */
string replaceSpacesWithUnderscores(string s);



/**
 * Classe que vai ser utilizada quando se procura um utente que nao existe (irao ser lancadas excecoes desta classe)
 */
class UtenteInexistente{

private:
	/**
	 * Id do utente nao existente
	 */
	unsigned int id;

public:
	/**
	 * Construtor da classe
	 * @param id Id do utente nao existente
	 */
	UtenteInexistente(unsigned int id): id(id){}

	/**
	 * Metodo de acesso ao id do utente que nao existe
	 * @return Id do utente nao existente
	 */
	unsigned int getId() {return id; }

};


/**
 * Classe que vai ser utilizada quando se tenta adiciona um assinante que ja existe (irao ser lancadas excecoes desta classe)
 */
class UtenteRepetido{

private:
	/**
	 * Id do utente repetido
	 */
	unsigned int id;

public:
	/**
	 * Construtor da classe
	 * @param id Id do utente repetido
	 */
	UtenteRepetido(unsigned int id): id(id){}

	/**
	 * Metodo de acesso ao id do utente repetido
	 * @return Id do utente repetido
	 */
	unsigned int getId() {return id; }

};
#endif /* UTENTE_H_ */
