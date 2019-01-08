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
 * Funcao que pede ao utilizador o numero de meses necessario sem comprar bilhete para um utente ser considerado inativo
 */
void pedeNumDiasExpiracao(){
	int valor;

	do{
		cout << "Indique o numero de meses que um utente tem de ficar sem comprar bilhete para ser considerado inativo: ";
		cin >> valor;

		if(valor <= 0){
			cout << "Valor invalido." << endl;
		}

	}while(valor <= 0);

	Utente::setNumDiasExpiracao(valor*30);
}


/**
 * Funcao que pede ao utilizador o numero de dias maximos que deverao faltar para uma manutencao de uma composicao se considerar proxima
 */
void pedeManutProx(){
		int valor;

	do{
		cout << "Indique o numero de dias para uma manutencao se considerar proxima: ";
		cin >> valor;

		if(valor <= 0){
		cout << "Valor invalido." << endl;
		}

	}while(valor <= 0);

	Composicao::setManutProxima(valor);
}


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

			//--
			char opcaoUtente;
			do{
				cout << endl << "O utente ja se encontra na base de dados? Ou e um utente novo?" << endl;
				cout << "1 -> ja se encontra na base de dados" << endl;
				cout << "2 -> e novo" << endl;
				cin >> opcaoUtente;

				if((opcaoUtente != '1') && (opcaoUtente != '2'))
					cout << "Valor invalido." << endl;


			}while((opcaoUtente != '1') && (opcaoUtente != '2'));

			//--

			if(opcaoUtente == '1'){

				string categoria, tipo;

				//pede categoria e tipo
				do{
					cout << "Categoria: "; cin >> categoria;

					if((categoria != "Z1") && (categoria != "Z2") && (categoria != "Z3") && (categoria != "Z4")){

						cout << "Valor(es) invalido(s). Insira novamente." << endl << endl;
					}

				}while((categoria != "Z1") && (categoria != "Z2") && (categoria != "Z3") && (categoria != "Z4"));


				unsigned int id;
				cout << endl << "Indique o valor do id do utente: "; cin >> id;

				string local;
				cout << "Insira o local do ponto de venda: ";
				cin.ignore(10, '\n');
				getline(cin, local);

				Utente* u = pv.getUtente(id); //verifica se o utente em questao existe

				if(u == 0){ //se o utente nao existe...
					cout << "Nao existe nenhum utente de id igual a " << id << "!" << endl << endl;
					return;
				}

				UtenteEstudante *u1 = dynamic_cast<UtenteEstudante *>(u);


				if(u1 != NULL)
					tipo = "estudante"; //utente ja existente e do tipo estudante

				else{

					UtenteJunior *u2 = dynamic_cast<UtenteJunior *>(u);

					if(u2 != NULL)
						tipo = "junior"; //utente ja existente e do tipo junior

					else{

						UtenteSenior *u3 = dynamic_cast<UtenteSenior *>(u);

						if(u3 != NULL)
							tipo = "senior"; //utente ja existente e do tipo senior

						else
							tipo = "normal"; //utente ja existente e do tipo normal
					}
				}

				BilheteAssinatura b2(categoria, tipo, u); //cria um bilhete com aquele utente

				try{

					//se retornou false, quer dizer que existe uma maquina nesse local
					if(!pv.comprarBilheteAssinatura(local, b2))
						cout << endl << "O local introduzido e uma maquina! Nao e possivel comprar bilhetes assinatura." << endl << endl;
					else cout << endl << "---------" << endl << "Operacao efetuada com sucesso!" << endl << "---------" << endl;


				//local nao existe
				}catch(LocalInexistente &li){

					cout << "Nao existe nenhum ponto de venda no local " << li.getLocal() << "!" << endl << endl;
				}




			}else if(opcaoUtente == '2'){ //utente e novo

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
			}

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


	//----------------------

	cout << endl;

	char sndFileOp;

	do{
		cout << "Prentende carregar a informacao sobre os funcionarios, composicoes, e utentes inativos de algum ficheiro? (s -> sim; n -> nao)" << endl;
		cin >> sndFileOp;

		if(sndFileOp == 's'){ //a informacao vai ser extraida de um ficheiro

			bool good_file;

			do{

				good_file = true;
				string ficheiro;

				cout << "indique o nome do ficheiro: ";
				cin >> ficheiro;

				if(pv.load_file2(ficheiro) != 0){
					cout << "Houve problemas com a abertura deste ficheiro. Por favor escolha outro" << endl;
					good_file = false;
				}

			}while(!good_file);

		}
		else if(sndFileOp == 'n'){ //nao ha informacao para ser extraida

			cout << "Indique, entao, o seguinte:" << endl << endl;

			pedeManutProx(); //pede o numero de dias maximos que deverao faltar para uma manutencao de uma composicao se considerar proxima
			cout << endl << endl;

			pedeNumDiasExpiracao(); //pede ao utilizador o numero de meses necessario sem comprar bilhete para um utente ser considerado inativo
			cout << endl << endl;

		}
		else cout << "Essa operacao nao e valida." << endl;


	}while((sndFileOp != 's') && (sndFileOp != 'n'));


	cout << endl << endl;


	char sndOp;

	do{

		//mostra ao utilizador todas as operacoes que sao possiveis de ser efetuadas
		cout << "Indique qual a operacao que pretende efetutar:" << endl;
		cout << "i -> imprimir a informacao (ou so sobre maquinas, ou so sobre lojas, ou sobre ambas) do sistema de pontos de venda" << endl;
		cout << "z -> modificar os valores dos precos dos bilhetes, para cada zona" << endl;
		cout << "d -> imprimir os valores dos precos dos bilhetes (em euros), para cada zona" << endl;
		cout << "p -> imprimir a informacao especifica a um ponto de venda (maquina ou loja), a especificar pelo seu local" << endl;
		cout << "u -> imprimir toda a informacao relativa aos utentes que possuem bilhetes assinatura" << endl;
		cout << "c -> comprar/adicionar um bilhete qualquer, num determinado ponto de venda" << endl;
		cout << "a -> apagar um utente da base de dados, removendo-o a si e a todos os bilhetes associados" << endl;
		cout << "r -> remover um ponto de venda qualquer do sistema (e consequentemente todos os seus bilhetes), especificado pelo seu local" << endl;
		cout << "n -> adicionar um novo ponto de venda (maquina ou loja) ao sistema" << endl << endl;

		cout << "Novas funcoes:" << endl;

/*-->*/ cout << "o -> adicionar um novo funcionario a base de dados" << endl;
/*-->*/ cout << "q -> remover um funcionario da base de dados" << endl;
/*-->*/ cout << "m -> imprimir a informacao relativa a um grupo de funcionarios" << endl;
/*-->*/ cout << "k -> modificar o salario de um funcionario existente" << endl;
/*-->*/ cout << "f -> modificar a funcao de um funcionario existente" << endl;
/*-->*/ cout << "g -> modificar o ponto de venda de um funcionario existente" << endl;

		cout << endl;

/*-->*/ cout << "b -> adicionar uma nova composicao a base de dados" << endl;
/*-->*/ cout << "e -> eliminar uma composicao da base de dados" << endl;
/*-->*/ cout << "y -> imprimir toda a informacao relativa as composicoes do metro" << endl;
/*-->*/ cout << "v -> indicar que uma determinada composicao se avariou" << endl;
/*-->*/ cout << "w -> modificar o numero de dias maximos que deverao faltar para uma manutencao de uma composicao se considerar proxima" << endl;

		cout << endl;

/*-->*/ cout << "1 -> imprimir a informacao de todos os clientes inativos da tabela" << endl;
/*-->*/ cout << "2 -> dar reset ao numero de dias inativos de um determinado utente" << endl;
/*-->*/ cout << "3 -> redefinir o numero de meses necessario sem comprar bilhetes assinatura, para que o utente fique inativo (atualiza a tabela)" << endl;
/*-->*/ cout << "4 -> imprimir a informacao do grupo de utentes inativos, que nao efetuam compras por mais de x meses" << endl;

		cout << endl;
		cout << "+ -> simular o avanco de um dia, atualizando as composicoes e os utentes e as suas estruturas relacionadas" << endl;
		cout << "- -> simular o avanco de um mes (30 dias), atualizando as composicoes e os utentes e as suas estruturas relacionadas" << endl;

		cout << endl << "s -> sair do programa" << endl;
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
	//escolheu-se a eliminacao de um utente qualquer (apaga-se o utente e os bilhetes associados a ele)
	}else if(sndOp == 'a'){


			//o utente a eliminar e identificado pelo seu id; utilizador tem de especificar o id
			unsigned int id;
			cout << "Indique o id do assinante a eliminar: ";
			cin >> id;


			//tenta eliminar a assinatura (excecao e lancada se nao existe nenhum utente com o id)
			try{

				pv.eliminaUtente(id);
				cout << endl << "---------" << endl << "Operacao efetuada com sucesso!" << endl << "---------" << endl;

			}catch(UtenteInexistente& ui){

				cout << "Nao existe nenhum utente com id " << ui.getId() << "!" << endl << endl;

			//esta excecao nunca ira ser lancada (em principio) pois cada utente esta obrigatoriamente associado a
			//pelo menos um bilhete assinatura. Mais uma vez, consideramos que seria boa pratica inserir o
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
	//escolheu-se a opcao de adicao de um novo funcionario
	}else if(sndOp == 'o'){

		int salario;
		string nome, funcao, pt_venda;

		cout << "Qual o nome do funcionario? ";
		cin.ignore(10, '\n');
		getline(cin, nome);

		cout << "Qual a funcao do funcionario? ";
		getline(cin, funcao);


		do{
			cout << "Qual o salario do funcionario? ";
			cin >> salario;

			if(salario <= 0)
				cout << "Valor invalido." << endl << endl;

		}while(salario <= 0);


		cout << "Qual o local do ponto de venda a que o funcionario ficara associado? ";
		cin.ignore(10, '\n');
		getline(cin, pt_venda);


		if(pv.findPDV(pt_venda) == -1)
			cout << endl << "O ponto de venda " << pt_venda << " nao existe!" << endl << endl;

		else{

			Funcionario func(nome, salario, funcao, pt_venda);

			if(!pv.insertFuncionario(func))
				cout << endl << "Ja existe um funcionario de nome " << nome << " e salario de " << salario << "!" << endl << endl << endl;
			else cout << endl << "---------" << endl << "Operacao efetuada com sucesso!" << endl << "---------" << endl;


		}



	//---------------
	//escolheu-se a opcao de remocao de um funcionario
	}else if(sndOp == 'q'){

		int salario;
		string nome;

		cout << "Qual o nome do funcionario? ";
		cin.ignore(10, '\n');
		getline(cin, nome);

		do{
			cout << "Qual o salario do funcionario? ";
			cin >> salario;

			if(salario <= 0)
				cout << "Valor invalido." << endl << endl;

		}while(salario <= 0);


		if(!pv.removeFuncionario(nome, salario))
			cout << endl << "Nao existe nenhum funcionario de nome " << nome << " e salario de " << salario << "!" << endl << endl << endl;
		else cout << endl << "---------" << endl << "Operacao efetuada com sucesso!" << endl << "---------" << endl;



	//---------------
	//escolheu-se a opcao de impressao no ecra de um grupo de funcionarios
	}else if(sndOp == 'm'){

		char option;

		do{
			cout << "Que informacao pretende obter?" << endl;
			cout << "t -> informacao sobre todos os funcionarios" << endl;
			cout << "p -> informacao sobre todos os funcionarios de um determinado ponto de venda" << endl;
			cout << "f -> informacao sobre todos os funcionarios com uma determinada funcao" << endl;
			cin >> option;

			if(option == 't'){

				cout << endl;
				pv.imprimeTodosFuncionarios();

			}else if(option == 'p'){

				string pdv;
				cout << "Qual o local do ponto de venda? ";
				cin.ignore(10, '\n');
				getline(cin, pdv);

				cout << endl;
				pv.imprimeFuncionariosPDV(pdv);
			}

			else if(option == 'f'){

				string func;
				cout << "Qual a funcao desempenhada pelos funcionarios? ";
				cin.ignore(10, '\n');
				getline(cin, func);


				cout << endl;
				pv.imprimeFuncionariosFuncao(func);

			}
			else
				cout << "Operacao invalida." << endl;


		}while((option != 't') && (option != 'p') && (option != 'f'));


	//---------------
	//escolheu-se a opcao de modificacao do salario de um funcionario
	}else if(sndOp == 'k'){

		int salario, novoSalario;
		string nome;

		cout << "Qual o nome do funcionario? ";
		cin.ignore(10, '\n');
		getline(cin, nome);

		do{
			cout << "Qual o salario do funcionario? ";
			cin >> salario;

			if(salario <= 0)
				cout << "Valor invalido." << endl << endl;

		}while(salario <= 0);


		do{
			cout << "Qual o novo salario para atribuir ao funcionario? ";
			cin >> novoSalario;

			if(novoSalario <= 0)
				cout << "Valor invalido." << endl << endl;

		}while(novoSalario <= 0);


		if(!pv.setFuncSalario(nome, salario, novoSalario))
			cout << endl << "Nao existe nenhum funcionario de nome " << nome << " e salario de " << salario << "!" << endl << endl << endl;
		else cout << endl << "---------" << endl << "Operacao efetuada com sucesso!" << endl << "---------" << endl;



	//---------------
	//escolheu-se a opcao de modificacao da funcao de um funcionario
	}else if(sndOp == 'f'){

		int salario;
		string nome, novaFuncao;

		cout << "Qual o nome do funcionario? ";
		cin.ignore(10, '\n');
		getline(cin, nome);

		do{
			cout << "Qual o salario do funcionario? ";
			cin >> salario;

			if(salario <= 0)
				cout << "Valor invalido." << endl << endl;

		}while(salario <= 0);


		cout << "Qual a nova funcao do funcionario? ";
		cin.ignore(10, '\n');
		getline(cin, novaFuncao);


		if(!pv.setFuncFuncao(nome, salario, novaFuncao))
			cout << endl << "Nao existe nenhum funcionario de nome " << nome << " e salario de " << salario << "!" << endl << endl << endl;
		else cout << endl << "---------" << endl << "Operacao efetuada com sucesso!" << endl << "---------" << endl;



	//---------------
	//escolheu-se a opcao de modificacao do ponto de venda de um funcionario
	}else if(sndOp == 'g'){

		int salario;
		string nome, novoLocal;

		cout << "Qual o nome do funcionario? ";
		cin.ignore(10, '\n');
		getline(cin, nome);

		do{
			cout << "Qual o salario do funcionario? ";
			cin >> salario;

			if(salario <= 0)
				cout << "Valor invalido." << endl << endl;

		}while(salario <= 0);


		cout << "Qual o local do novo ponto de venda do funcionario? ";
		cin.ignore(10, '\n');
		getline(cin, novoLocal);


		if(pv.findPDV(novoLocal) == -1)
			cout << endl << "O ponto de venda " << novoLocal << " nao existe!" << endl << endl;

		else{

			if(!pv.setFuncPtVenda(nome, salario, novoLocal))
				cout << endl << "Nao existe nenhum funcionario de nome " << nome << " e salario de " << salario << "!" << endl << endl << endl;
			else cout << endl << "---------" << endl << "Operacao efetuada com sucesso!" << endl << "---------" << endl;

		}

	//---------------
	//escolheu-se a opcao de criacao de uma nova composicao
	}else if (sndOp == 'b'){

		int numDias;
		bool avaria;
		char av;

		do{
			cout << "Quantos dias faltam para a proxima manutencao da composicao? ";
			cin >> numDias;

			if(numDias <= 0)
				cout << "Valor invalido." << endl;

		}while(numDias <= 0);

		do{
			cout << "A composicao esta avariada?" << endl << "s -> sim" << endl << "n -> nao" << endl;
			cin >> av;

			if((av != 's') && (av != 'n'))
				cout << "Valor invalido." << endl;


		}while((av != 's') && (av != 'n'));


		if(av == 's')
			avaria = true;
		else avaria = false;

		Composicao nova(numDias, avaria);

		cout << endl;

		//Na verdade, como nao irao haver IDs repetidos, ira dar sempre para adicionar; mais uma vez,
		//achamos que seria boa pratica adicionar na mesma o tratamento do caso.

		if(!pv.adicionaComposicao(nova))
			cout << "Ja existente uma composicao equivalente na base de dados!" << endl;
		else cout << endl << "---------" << endl << "Operacao efetuada com sucesso!" << endl << "---------" << endl;



	//---------------
	//escolheu-se a opcao de eliminacao de uma composicao
	}else if(sndOp == 'e'){

		int id;
		cout << "Indique o ID da composicao a eliminar: ";
		cin >> id;

		if(pv.eliminaComposicao(id))
			cout << endl << "---------" << endl << "Operacao efetuada com sucesso!" << endl << "---------" << endl;
		else cout << "Nao existe nenhuma composicao com ID igual a " << id << "!" << endl << endl;




	//---------------
	//escolheu-se a opcao de impressao de toda a informacao relativa as composicoes
	}else if(sndOp == 'y'){

		pv.imprimeInfoComposicoes();


	//---------------
	//escolheu-se a opcao de modificar o numero de dias para uma manutencao de uma composicao se considerar proxima
	}else if(sndOp == 'w'){

		pedeManutProx();

	//---------------
	//escolheu-se a opcao de indicar que uma dada composicao se avariou
	}else if(sndOp == 'v'){
		int id;
		cout << "Indique o ID da composicao a modificar: ";
		cin >> id;

		if(pv.poeCompAvariada(id))
			cout << endl << "---------" << endl << "Operacao efetuada com sucesso!" << endl << "---------" << endl;
		else cout << "Nao existe nenhuma composicao com ID igual a " << id << "!" << endl << endl;



	//---------------
	//escolheu a opcao de imprimir a tabela com utentes inativos
	}else if(sndOp == '1'){

		pv.imprimeInfoInativos();
		cout << endl << endl;


	//---------------
	//escolheu-se a opcao de dar reset ao numero de dias ate ser considerado inativo
	}else if(sndOp == '2'){

		int id;

		cout << "Qual o id do funcionario? ";
		cin >> id;

		try{

			pv.resetUtenteInativo(id);
			cout << endl << "---------" << endl << "Operacao efetuada com sucesso!" << endl << "---------" << endl;

		}catch(UtenteInexistente& ui){

			cout << "Nao existe nenhum utente com id igual a " << ui.getId() << "!" << endl << endl;
		}


	//---------------
	//escolheu-se a opcao de modificar o numero de meses necessario para que um utente fique inativo
	}else if(sndOp == '3'){

		pedeNumDiasExpiracao();
		pv.removeUtentesInat(Utente::getNumDiasExpiracao());
		cout << endl << "---------" << endl << "Operacao efetuada com sucesso!" << endl << "---------" << endl;

	//---------------
	//escolheu-se a opcao de imprimir a informacao do grupo de utentes inativos, que se nao efetuam compras por mais de x meses
	}else if(sndOp == '4'){

		int mes;
		int numMesesMin = Utente::getNumDiasExpiracao() / 30;

		do{

			cout << endl << "Insira o numero de meses: ";
			cin >> mes;

			if(mes < numMesesMin)
				cout << "O numero de meses precisa de ser maior ou igual que o numero de meses minimo para um utente ficar inativo (" << numMesesMin << ")." << endl << endl;


		}while(mes < numMesesMin);


		pv.imprimeInfoInativosMes(mes);


	//---------------
	//escolheu-se a opcao de avanco de um dia
	}else if(sndOp == '+'){

		pv.avancaDiaTudo();
		cout << endl << endl;
		cout << "O sistema foi avancado em um dia!";
		cout << endl << endl;


	//---------------
	//escolheu-se a opcao de avanco de um mes
	}else if(sndOp == '-'){

		pv.avancaMesTudo();
		cout << endl << endl;
		cout << "O sistema foi avancado em um mes!";
		cout << endl << endl;



	}else if(sndOp != 's'){

			cout << "Operacao invalida." << endl << endl;
	}



}while(sndOp != 's');



	char trdOp;
	bool validExit;

	do{

		validExit = false;
		cout << endl << endl;
		cout << "Pretende guardar a informacao modificada em ficheiros?" << endl;
		cout << "s -> guardar" << endl << "n -> nao guardar" << endl;
		cout << "Operacao: ";
		cin >> trdOp;

		//o utilizador pretende gravar a informacao em ficheiros
		if(trdOp == 's'){

			bool good_saveFile1, good_saveFile2;
			string ficheiro1, ficheiro2;

			do{

				good_saveFile1 = true;
				cout << endl << "Qual o nome do primeiro ficheiro? ";
				cin >> ficheiro1;

				//grava a informacao no ficheiro de nome especificado
				if(pv.save_file(ficheiro1) != 0){

					cout << "Ocorreu um erro com um ficheiro. Por favor tente novamente.";
					good_saveFile1 = false;
				}


			}while(!good_saveFile1);


			cout << endl;

			do{

				good_saveFile2 = true;
				cout << endl << "Qual o nome do segundo ficheiro? ";
				cin >> ficheiro2;

				//grava a informacao no ficheiro de nome especificado
				if(pv.save_file2(ficheiro2) != 0){

					cout << "Ocorreu um erro com um ficheiro. Por favor tente novamente.";
					good_saveFile2 = false;
				}


			}while(!good_saveFile2);


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
