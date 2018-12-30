#ifndef PONTOSVENDA_H_
#define PONTOSVENDA_H_

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <queue>
#include <unordered_set>
#include "Maquina.h"
#include "Bilhete.h"
#include "Utente.h"
#include "Funcionario.h"
#include "Composicao.h"

/**
 * Struct que encapsula a hash function e a equal function para a organizacao dos utentes inativos na tabela de dispersao
 */
struct UtenteInativoHash{

	/**
	 * Hash Function
	 */
	int operator()(const Utente* u) const{

		//como cada utente tem um id especifico e nao repetido, a hash function, ao organizar
		//os elementos da tabela de dispersao pelo id, evita deste modo a ocorrencia de
		//muitas colisoes.
		return u->getId();
	}

	/**
	 * Equal Function
	 */
	bool operator()(const Utente* u1, const Utente* u2) const{

		//dois utentes sao iguais quando tem IDs iguais
		return (u1->getId() == u2->getId());
	}
};


typedef unordered_set<Utente*, UtenteInativoHash, UtenteInativoHash> tabDispUtentesInat;



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


	//-------Novas estruturas-------//

	/**
	 * Set (arvore binaria de pesquisa) com todos os funcionarios do metro
	 */
	set<Funcionario> funcionarios;


	/**
	 * Fila de prioridade que tem todas as composicoes de metros na base de dados, e informacao relativa
	 */
	priority_queue<Composicao> composicoes;


	/**
	 * Tabela de dispersao contendo todos os utentes inativos
	 */
	tabDispUtentesInat utentesInativos;


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


	//----------FUNCIONARIOS------------

	/**
	 * Funcao que retorna a estrutura com os funcionarios do metro
	 * @return Set com os funcionarios do metro
	 */
	set<Funcionario> getFuncionarios();

	/**
	 * Funcao que procura o funcionario com o id introduzido no set e lanca uma excecao se nao encontrar
	 * @param name Nome do funcionario que se procura
	 * @param salario Salario do funcionario que se procura
	 * @return Funcionario com o nome e salario introduzidos
	 */
	Funcionario getFuncionario(string name, unsigned int salario) const;

	/**
	 * Funcao que adiciona um funcionario ao set funcionarios
	 * @param f Funcionario que se pretende adicionar
	 * @return True se for adicionado com sucesso e false se nao for
	 */
	bool insertFuncionario(Funcionario f);

	/**
	 * Metodo que remove o funcionario com um determinado nome e salario da estrutura dos funcionarios
	 * @param nome Nome do funcionario a remover
	 * @param salario Salario do funcionario a remover
	 * @return True se e removido com sucesso e false se nao e (se nao existir nenhum funcionario equivalente)
	 */
	bool removeFuncionario(string nome, unsigned salario);

	/**
	 * Metodo que imprime a informacao relativa a todos os funcionarios
	 */
	void imprimeTodosFuncionarios();

	/**
	 * Metodo que imprime todos os funcionarios que trabalham num determinado ponto de venda
	 * @param local Local onde se encontra o ponto de venda
	 */
	void imprimeFuncionariosPDV(string local);


	/**
	 * Metodo que imprime todos os funcionarios que desempenham uma determinada funcao
	 * @param funcao Funcao desempenhada pelos funcionarios
	 */
	void imprimeFuncionariosFuncao(string funcao);


	/**
	 * Funcao que muda o salario de um funcionario
	 * @param nome Nome do funcionario
	 * @param salario Salario do funcionario
	 * @param novoSalario Novo salario que o funcionario vai ter
	 * @return True se alterou com sucesso e false se o funcionario nao foi encontrado
	 */
	bool setFuncSalario(string nome, unsigned salario, unsigned int novoSalario);

	/**
	 * Funcao que muda a funcao de um funcionario
	 * @param nome Nome do funcionario
	 * @param salario Salario do funcionario
	 * @param funcao Nova funcao que o funcionario vai ter
	 * @return True se alterou com sucesso e false se o funcionario nao foi encontrado
	 */
	bool setFuncFuncao(string nome, unsigned salario, string funcao);

	/**
	 * Funcao que muda o ponto de venda em que um funcionario trabalha
	 * @param nome Nome do funcionario
	 * @param salario Salario do funcionario
	 * @param pt_venda Novo ponto de venda em que o funcionario vai trabalhar
	 * @return True se alterou com sucesso e false se o funcionario nao foi encontrado
	 */
	bool setFuncPtVenda(string nome, unsigned salario, string pt_venda);


	//----------COMPOSICAO------------

	/**
	 * Metodo que imprime toda a informacao relativa as composicoes do metro
	 */
	void imprimeInfoComposicoes() const;

	/**
	 * Metodo que adiciona uma composicao a estrutura que mantem a informacao sobre as composicoes
	 * @param c Composicao que se pretende adicionar
	 * @return True se adicionou, false caso contrario (composicao ja estava presente na estrutura)
	 */
	bool adicionaComposicao(Composicao c);

	/**
	 * Metodo que elimina uma composicao da estrutura de dados
	 * @param id ID da composicao a eliminar
	 * @return True se conseguiu eliminar, false caso contrario (composicao nao esta presente na estrutura)
	 */
	bool eliminaComposicao(unsigned id);

	/**
	 * Metodo que modifica uma determinada composicao da base de dados, para indicar que ela se avariou
	 * @param id ID da composicao
	 * @return True se modificou, false caso contrario (composicaonao esta presente na estrutura)
	 */
	bool poeCompAvariada(unsigned id);

	/**
	 * Metodo que simula o avanco de um dia, atualizando as composicoes presentes na estrutura de dados
	 */
	void avancaDiaComp();

	/**
	 * Metodo para ser chamado na funcao principal; atualiza todas as composicoes, avancando um dia e realizando as manutencoes necessarias
	 */
	void atualizaComp();

	//----------UTENTES INATIVOS------------

	/**
	 * Metodo que adiciona um utente inativo a tabela de dispersao (se o utente ja se encontra la, nao faz nada)
	 * @param u Utente a ser adicionado
	 */
	void adicionaUtenteInat(Utente* u);

	/**
	 * Metodo que elimina um dado utente da tabela de dispersao, dado pelo seu id (se nao existe nenhum utente com esse ID, nao faz nada)
	 * @param id ID do utente a eliminar
	 */
	void eliminaUtenteInat(unsigned id);


	/**
	 * Metodo a ser chamado na funcao principal, simulando a passagem de um dia e atualizando a tabela de dispersao adequadamente.
	 * Este metodo decrementa o numero de dias ate serem considerados inativos para todos os utentes do vetor
	 */
	void atualizaInat();

	/**
	 * Metodo que imprime a informacao da tabela de dispersao, relativa aos utentes inativos
	 */
	void imprimeInfoInativos();

};

#endif /* PONTOSVENDA_H_ */
