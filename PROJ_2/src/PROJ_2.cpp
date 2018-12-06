#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include "Bilhete.h"
#include "Utente.h"
#include "Maquina.h"
#include "PontosVenda.h"
using namespace std;

/**
 * Funcao que pede ao utilizador do programa que insira os precos desejados para os bilhetes (unico, diario e assinatura), para cada zona
 */
void pedePrecoZonas(){

	float valor_unico, valor_diario, valor_ass;
	vector<vector<float> >	precosZona;

	for(unsigned i = 1; i <= 4; i++){

		do{
			cout << "Precos para a zona " << i << ": bilhete unico, diario e assinatura, por esta ordem" << endl;
			cin >> valor_unico >> valor_diario >> valor_ass;	//extrai os valores dos precos relativos aos diferentes tipos de bilhetes, para cada uma das 4 zonas

			if((valor_unico <= 0) || (valor_diario <= 0) || (valor_ass <= 0)){

				cout << "Valor(es) invalido(s). Tem de ser valores positivos " << endl;
			}

		}while((valor_unico <= 0) || (valor_diario <= 0) || (valor_ass <= 0));

		vector<float> p;
		p.push_back(valor_unico);
		p.push_back(valor_diario);
		p.push_back(valor_ass);
		precosZona.push_back(p);

		}

		Bilhete::setPrecosZona(precosZona);

}

/**
 * Funcao auxiliar que permite ao utilizador do programa a compra de um bilhete
 * @param pv Objeto que representa a totalidade dos pontos de venda da cidade
 */
void compraBilhete(PontosVenda& pv){

	string local, nome;
	char r;

	do{
		cout << endl << "O bilhete e ocasional ou de assinatura?" << endl;
		cout << endl << "o -> Ocasional";
		cout << endl << "a -> assinatura" << endl;
		cin >> r;

		if(r == 'o'){  //se for bilhete ocasional

			string categoria, duracao;

			//pede categoria e duracao
			do{

				cout << endl;
				cout << "Categoria: "; cin >> categoria;
				cout << "Duracao: "; cin >> duracao;

				//verifica se os inputs sao validos
				if( ((categoria != "Z1") && (categoria != "Z2") && (categoria != "Z3") && (categoria != "Z4")) || ((duracao != "unico") && (duracao != "diario"))){

					cout << "Valor(es) invalido(s). Insira novamente." << endl << endl;
				}

			}while( ((categoria != "Z1") && (categoria != "Z2") && (categoria != "Z3") && (categoria != "Z4")) || ((duracao != "unico") && (duracao != "diario")));


			//cria o bilhete a ser adicionado
			BilheteOcasional b1(categoria, duracao);


			cout << "Insira o local do ponto de venda: ";
			cin.ignore(10, '\n');
			getline(cin, local);

			//tenta comprar o bilhete no local dado
			try{

				pv.comprarBilheteOcasional(local, b1);
				cout << endl << "---------" << endl << "Operacao efetuada com sucesso!" << endl << "---------" << endl;

			}catch(LocalInexistente &li){

				cout << "Nao existe nenhum ponto de venda no local " << li.getLocal() << "!" << endl << endl;
			}


		}else if(r == 'a'){ //se for bilhete assinatura

			string categoria, tipo;

			//pede categoria e tipo
			do{
				cout << "Categoria: "; cin >> categoria;
				cout << "Tipo: "; cin >> tipo;

				if( ((categoria != "Z1") && (categoria != "Z2") && (categoria != "Z3") && (categoria != "Z4")) || ((tipo != "normal") && (tipo != "junior") && (tipo != "senior") && (tipo != "estudante"))){

					cout << "Valor(es) invalido(s). Insira novamente." << endl << endl;
				}

			}while( ((categoria != "Z1") && (categoria != "Z2") && (categoria != "Z3") && (categoria != "Z4")) || ((tipo != "normal") && (tipo != "junior") && (tipo != "senior") && (tipo != "estudante")));

			Utente* u;
			cout << endl;
			cout << "Nome: "; //pede o nome do utente
			cin.ignore(10, '\n');
			getline(cin, nome);


			//se o bilhete for do tipo normal, a unica informacao necessaria do utente e o nome
			if(tipo == "normal"){

				//cria o utente
				u = new Utente(nome);


			}else{ //se tipo diferente de normal, pede-se idade e CC


				int idade;
				string cc;

				cout << "Idade: "; cin >> idade;
				cout << "CC: "; cin >> cc;

				//se o tipo do bilhete for estudante, para alem do nome, idade e CC, precisamos de saber a escola
				if(tipo == "estudante"){

					string escola;
					cout << "Escola: ";
					cin.ignore(10, '\n');
					getline(cin, escola);

					//cria o utente
					u = new UtenteEstudante(nome, idade, cc, escola);

				}//se utent for do tipo senior ou junior, as informacoes requeridas sao o nome, idade e CC
				else if(tipo == "senior"){

					u = new UtenteSenior(nome, idade, cc);

				}else u = new UtenteJunior(nome, idade, cc);

			}

			//cria o bilhete assinatura a ser adicionado, ao qual esta associado o utente criado
			BilheteAssinatura b2(categoria, tipo, u);

			cout << "Insira o local do ponto de venda: ";


			//se o tipo foi junior ou senior, a ultima operacao foi um cin. Deste modo, faz-se cin.ignore,
			//de modo a podermos utilizar o getline sem haver problemas.
			if((tipo == "junior") || (tipo == "senior")){
				cin.ignore(10, '\n');
			}

			getline(cin, local);

			try{

				//se retornou false, quer dizer que existe uma maquina nesse local
				if(!pv.comprarBilheteAssinatura(local, b2))
					cout << endl << "O local introduzido e uma maquina! Nao e possivel comprar bilhetes assinatura." << endl << endl;
				else cout << endl << "---------" << endl << "Operacao efetuada com sucesso!" << endl << "---------" << endl;


			//local nao existe
			}catch(LocalInexistente &li){

				cout << "Nao existe nenhum ponto de venda no local " << li.getLocal() << "!" << endl << endl;

				//esta excecao, na verdade, nunca ira ser lancada, pois nesta funcao e criado um novo utente, com um novo id.
				//No entanto, achamos boa pratica adicionar o tratamento desta excecao, de qualquer das maneiras.
			}catch(UtenteRepetido & ur){

				cout << "Ja existe um assinante com id " << ur.getId() << "!" << endl << endl;
			}


		}else{

			cout << "Operacao invalida." << endl << endl;
		}


	}while((r != 'o') && (r != 'a'));



}


int main(){

	cout << "---------GESTAO DE BILHETES NO METRO---------" << endl << endl;

	PontosVenda pv;
	char op;
	bool valid = false;

	do{

		valid = false;

		cout << "Prentende carregar a informacao sobre os pontos de venda de algum ficheiro? (s -> sim; n -> nao)" << endl;

		cin >> op;

		//a informacao ira ser carregada de um ficheiro
		if(op == 's'){

			bool good_file;
			do{

			good_file = true;
			string ficheiro;
			valid = true;
			cout << "indique o nome do ficheiro: ";
			cin >> ficheiro;

			if(pv.load_file(ficheiro) != 0){
				cout << "Houve problemas com a abertura deste ficheiro. Por favor escolha outro" << endl;
				good_file = false;
			}

			}while(!good_file);


		//a base de dados ira "comecar do zero"; e necessario especificar os precos desejados relativos a cada zona,
		//para a futura compra de bilhetes.
		}else if(op == 'n'){

			valid = true;
			cout << "Indique, entao, quais irao ser os precos dos bilhetes respetivos as diferentes zonas." << endl << endl;

			pedePrecoZonas();
		}


		if(!valid){
			cout << "Essa operacao nao e valida." << endl;

		}

	}while(!valid);


	cout << endl << endl;
	char sndOp;

	do{

		//mostra ao utilizador todas as operacoes que sao possiveis de ser efetuadas
		cout << "Indique qual a operacao que pretende efetutar:" << endl;
		cout << "i -> imprimir a informacao (ou so sobre maquinas, ou so sobre lojas, ou sobre ambas) do sistema de pontos de venda" << endl;
		cout << "z -> modificar os valores dos precos dos bilhetes, para cada zona" << endl;
		cout << "d -> imprimir os valores dos precos dos bilhetes (em euros), para cada zona" << endl;
		cout << "p -> imprimir a informacao especifica a um ponto de venda (maquina ou loja), a especificar pelo seu local" << endl;
		cout << "u -> imprimir toda a informacao relativa aos utentes que possuem um bilhete assinatura" << endl;
		cout << "c -> comprar/adicionar um bilhete qualquer, num determinado ponto de venda" << endl;
		cout << "a -> apagar uma assinatura do sistema, eliminando o utente e o seu bilhete assinatura" << endl;
		cout << "r -> remover um ponto de venda qualquer do sistema (e consequentemente todos os seus bilhetes), especificado pelo seu local" << endl;
		cout << "n -> adicionar um novo ponto de venda (maquina ou loja) ao sistema" << endl;
		cout << "s -> sair do programa" << endl;
		cout << "Operacao: ";
		cin >> sndOp;
		cout << endl;

	//---------------
	//escolheu-se a impressao de toda a informacao disponivel sobre os PDVs
	if(sndOp == 'i'){

			char opOrd;

			do{

			cout << "Pretende ordenar os pontos de venda por ordem crescente de local?" << endl;
			cout << "s -> sim" << endl << "n -> nao" << endl;

			cin >> opOrd;

			//ordena por local
			if(opOrd == 's')
				pv.sortPDVsPorLocal();


			if((opOrd != 's') && (opOrd != 'n'))
				cout << "Operacao invalida." << endl;


			}while((opOrd != 's') && (opOrd != 'n'));


			char opMLT;

			do{

				cout << "Deve ser impressa a informacao relativa a..." << endl;
				cout << "m -> apenas maquinas" << endl << "l -> apenas lojas" << endl << "t -> toda a informacao" << endl;

				cin >> opMLT;

				if(opMLT == 'm'){

					cout << endl;
					pv.imprimeSoMaquinas(); //metodo que imprime a informacao relativa a todas as maquinas
					cout << endl << endl;

				}
				else if(opMLT == 'l'){

					cout << endl;
					pv.imprimeSoLojas(); //metodo que imprime a informacao relativa a todas as lojas
					cout << endl << endl;

				}
				else if(opMLT == 't'){

					cout << endl;
					pv.imprime(); //metodo que imprime a informacao relativa a ambas
					cout << endl << endl;

				}
				else cout << "Operacao invalida." << endl;

			}while((opMLT != 'm') && (opMLT != 'l') && (opMLT != 't'));

	//---------------
	//escolheu-se a modificacao dos precos relativos a cada zona
	}else if(sndOp == 'z'){

			pedePrecoZonas();
			cout << endl << "---------" << endl << "Operacao efetuada com sucesso!" << endl << "---------" << endl;


	//---------------
	//escolheu-se a impressao dos precos relativos a cada zona
	}else if(sndOp == 'd'){

			cout << endl;
			Bilhete::imprimePrecosZona();
			cout << endl;


	//---------------
	//escolheu-se a impressao da informacao relativa a um PDV especifico
	}else if(sndOp == 'p'){


			//utilizador insere o local do PDV
			string local;
			char cresc;
			cout << "Insira o local do ponto de venda: ";
			cin.ignore(10, '\n');
			getline(cin, local);

		do{

			cout << "Pretende a ordenacao crescente ou decrescente dos precos dos bilhetes?" << endl;
			cout << "c -> crescente" << endl << "d -> decrescente" << endl;
			cin >> cresc;

			//escolheu-se a ordenacao crescente
			if(cresc == 'c'){

				try{
					pv.sortPDV(local, true);
					pv.imprimePDV(local);


				}catch(LocalInexistente &li){
					cout << "Nao existe nenhum ponto de venda no local " << li.getLocal() << "!" << endl << endl;
				}

			//escolheu-se a ordenacao decrescente
			}else if(cresc == 'd'){

				try{
					pv.sortPDV(local, false);
					pv.imprimePDV(local);

				}catch(LocalInexistente &li){
					cout << "Nao existe nenhum ponto de venda no local " << li.getLocal() << "!" << endl << endl;
				}


			}else cout << "Operacao invalida." << endl << endl;

		}while((cresc != 'c') && (cresc != 'd'));

	//---------------
	//escolheu-se a impressao da informacao relativa a todos os assinantes
	}else if(sndOp == 'u'){

		char opUtente;

		do{
			cout << "Como pretende a ordenacao dos utentes?" << endl;
			cout << "a -> por ordem alfabetica" << endl << "i -> por ordem crescente de id" << endl;

			cin >> opUtente;

			//escolheu-se a ordenacao por nome
			if(opUtente == 'a')
				pv.sortUtentesNome();

			//escolheu-se a ordenacao por id
			else if(opUtente == 'i')
				pv.sortUtentesId();


			else cout << "Operacao invalida." << endl;


		}while((opUtente != 'a') && (opUtente != 'i'));


		pv.imprimeAssinantes(); //imprime a informacao
		cout << endl << endl;


	//---------------
	//escolheu-se a compra de um bilhete num PDV qualquer
	}else if(sndOp == 'c'){

			compraBilhete(pv); //e chamada a funcao de compra de um bilhete



	//---------------
	//escolheu-se a eliminacao de uma assinatura qualquer (apaga-se o utente e o bilhete associado a ele)
	}else if(sndOp == 'a'){


			//o utente a eliminar e identificado pelo seu id; utilizador tem de especificar o id
			unsigned int id;
			cout << "Indique o id do assinante a eliminar: ";
			cin >> id;


			//tenta eliminar a assinatura (excecao e lancada se nao existe nenhum utente com o id)
			try{

				pv.eliminaAssinatura(id);
				cout << endl << "---------" << endl << "Operacao efetuada com sucesso!" << endl << "---------" << endl;

			}catch(UtenteInexistente& ui){

				cout << "Nao existe nenhum utente com id " << ui.getId() << "!" << endl << endl;

			//esta excecao nunca ira ser lancada (em principio) pois cada utente esta obrigatoriamente associado
			//a um, e um so, bilhete assinatura. Mais uma vez, consideramos que seria boa pratica inserir o
			//tratamento da excecao, de qualquer das maneiras.
			}catch(BilheteInexistente& bi){

				cout << "Ocorreu um erro no sistema; o utente existe, mas nao possui bilhete na base de dados!" << endl << endl;
			}



	//---------------
	//escolheu-se a opcao de eliminacao de um PDV qualquer da base de dados
	}else if(sndOp == 'r'){

			//utilizador especifica o local do ponto de venda
			string local;
			cout << "Insira o local do ponto de venda: ";
			cin.ignore(10, '\n');
			getline(cin, local);


			try{

				pv.eliminaPDV(local);
				cout << endl << "---------" << endl << "Operacao efetuada com sucesso!" << endl << "---------" << endl;


			}catch(LocalInexistente & li){

				cout << "Nao existe nenhum ponto de venda no local " << li.getLocal() << "!" << endl << endl;
			}


	//---------------
	//escolheu-se a opcao de criacao de um novo PDV (num local novo)
	}else if(sndOp == 'n'){

			//utilizador especifica o local do PDV
			string local;
			char l;
			cout << "Insira o local do ponto de venda: ";
			cin.ignore(10, '\n');
			getline(cin, local);

			Maquina* m;


			do{
				cout << endl << "O ponto de venda sera uma maquina ou loja?" << endl;
				cout << endl << "m -> maquina";
				cout << endl << "l -> loja" << endl;
				cin >> l;

				//o PDV e uma maquina
				if(l == 'm'){

					m = new Maquina(local);


				//o PDV e uma loja
				}else if(l == 'l'){

					m = new Loja(local);


				}else{

					cout << "Operacao invalida." << endl << endl;
				}


			}while((l != 'm') && (l != 'l'));


			//tenta adicionar o novo PDV a base de dados (lanca excecao se o local ja esta a ser ocupado por outro PDV)
			try{

				pv.addPDV(m);
				cout << endl << "---------" << endl << "Operacao efetuada com sucesso!" << endl << "---------" << endl;

			}catch(LocalRepetido& lr){

				cout << "Ja existe um ponto de venda no local " << lr.getLocal() << "!" << endl << endl;
			}


	//---------------
	//escolheu-se a operacao de sair do programa
	}else if(sndOp != 's'){

			cout << "Operacao invalida." << endl << endl;
	}



}while(sndOp != 's');



	char trdOp;
	bool validExit;

	do{

		validExit = false;
		cout << endl << endl;
		cout << "Pretende guardar a informacao modificada dos pontos de venda num ficheiro?" << endl;
		cout << "s -> guardar" << endl << "n -> nao guardar" << endl;
		cout << "Operacao: ";
		cin >> trdOp;

		//o utilizador pretende gravar a informacao num ficheiro
		if(trdOp == 's'){

			bool good_saveFile;
			string ficheiro;

			do{

				good_saveFile = true;
				cout << endl << "Qual o nome do ficheiro? ";
				cin >> ficheiro;

			//grava a informacao no ficheiro de nome especificado
			if(pv.save_file(ficheiro) != 0){

				cout << "Ocorreu um erro com um ficheiro. Por favor tente novamente.";
				good_saveFile = false;
			}


			}while(! good_saveFile);

			validExit = true;

		}//o utilizador pretende descartar as alteracoes feitas a base de dados
		else if(trdOp == 'n'){

			validExit = true;

		}
		else{

			cout << "Operacao invalida.";

		}


	}while(! validExit);


	cout << "Desligando o programa..." << endl;
	cout << "Obrigado!";

	return 0;

}
