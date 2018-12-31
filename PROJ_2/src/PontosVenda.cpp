#include <fstream>
#include <algorithm>
#include "PontosVenda.h"

using namespace std;


PontosVenda::~PontosVenda(){

	for(unsigned i = 0; i < ptsVenda.size(); i++)
		delete ptsVenda.at(i);

	for(unsigned j= 0; j < utentes.size(); j++)
		delete utentes.at(j);

}



void PontosVenda::imprime() const{

	if(ptsVenda.size() == 0){
		cout << "Nao ha nenhuma informacao para imprimir!" << endl;
		return;
	}

	for(unsigned i = 0; i < ptsVenda.size(); i++){

		ptsVenda.at(i)->imprimeInfoPDV();
		cout << "--------------" << endl;

	}
}


void PontosVenda::imprimeSoMaquinas() const{

	bool haInfo = false;

	for(unsigned i = 0; i < ptsVenda.size(); i++){

		if(!ptsVenda.at(i)->eLoja()){ //o ponto de venda atual e uma maquina

			haInfo = true;
			ptsVenda.at(i)->imprimeInfoPDV();
			cout << "--------------" << endl;

		}
	}

	if(!haInfo)
		cout << "Nao ha nenhuma informacao relativa a maquinas para imprimir!" << endl;

}




void PontosVenda::imprimeSoLojas() const{

	bool haInfo = false;

	for(unsigned i = 0; i < ptsVenda.size(); i++){

		if(ptsVenda.at(i)->eLoja()){ //o ponto de venda atual e uma loja

			haInfo = true;
			ptsVenda.at(i)->imprimeInfoPDV();
			cout << "--------------" << endl;

		}
	}

	if(!haInfo)
		cout << "Nao ha nenhuma informacao relativa a lojas para imprimir!" << endl;

}



void PontosVenda::imprimeAssinantes() const{

	if(utentes.size() == 0){
		cout << "Nao ha informacao relativa a assinantes!" << endl;
		return;
	}

	cout << "Informacao relativa a todos os assinantes:" << endl << endl;

	for(unsigned i = 0; i < utentes.size(); i++){

		utentes.at(i)->imprimeInfoUtente();
		cout << endl << endl;

	}
}



void PontosVenda::imprimePDV(string local) const{

	bool encontrou = false;

	for(unsigned i = 0; i < ptsVenda.size(); i++){

		if(ptsVenda.at(i)->getLocal() == local){

			cout << "Local encontrado:" << endl;
			encontrou = true;
			ptsVenda.at(i)->imprimeInfoPDV();
		}

	}

	if(!encontrou)
		throw LocalInexistente(local);
}



int PontosVenda::load_file(string ficheiro){

	ifstream f;
	f.open(ficheiro);

	if(!f.is_open()){	//nao conseguiu abrir o ficheiro
		return 1;
	}


	//primeiros valores no ficheiro sao os precos de cada zona; sao extraidos no inicio
	float valor_unico, valor_diario, valor_ass;
	vector<vector<float> >	precosZona;

	for(unsigned i = 1; i <= 4; i++){

		f >> valor_unico >> valor_diario >> valor_ass;	//extrai os valores dos precos relativos aos diferentes tipos de bilhetes, para cada uma das 4 zonas
		vector<float> p;
		p.push_back(valor_unico);
		p.push_back(valor_diario);
		p.push_back(valor_ass);
		precosZona.push_back(p);

	}

	Bilhete::setPrecosZona(precosZona);



	unsigned int nextId;
	f >> nextId; //extrai o valor para a variavel nextId
	Utente::setNextId(nextId);


	string linha;

	while(!f.eof()){

		f >> linha;

		if(linha == "MAQUINA"){ //informacao sobre uma maquina

			f >> linha; //vai extrair o local

			linha = replaceUnderscoresWithSpaces(linha);

			Maquina* m = new Maquina(linha); //cria uma nova maquina com o local extraido


			while(1){
				f >> linha; //tenta extrair um bilhete (se existir)

				if(linha == "*****"){ //acabou a informacao sobre essa maquina
					this->addPDV(m);
					break;
				}
				else if(linha == "Ocasional"){ //informacao sobre bilhete ocasional

					string categoria, duracao;
					float preco;
					f >> categoria >> preco >> duracao;
					BilheteOcasional b1(categoria, preco, duracao); //cria o novo bilhete
					m->addBilheteO(b1); //adiciona o bilhete a maquina

				}
			}
		}else if(linha == "LOJA"){ //informacao sobre uma loja

			f >> linha; //vai extrair o local

			linha = replaceUnderscoresWithSpaces(linha);

			Loja* l = new Loja(linha); //cria uma nova loja com o local extraido


			while(1){

				f >> linha; //tenta extrair um bilhete (se existir)

				if(linha == "*****"){ //acabou a informacao sobre essa loja

					Maquina* w = dynamic_cast<Maquina*>(l);
					this->addPDV(w);
					break;
				}
				else if(linha == "Ocasional"){//informacao sobre bilhete ocasional

					string categoria, duracao;
					float preco;
					f >> categoria >> preco >> duracao;
					BilheteOcasional b2(categoria, preco, duracao); //cria o novo bilhete
					l->addBilheteO(b2); //adiciona o bilhete a loja


				}else if(linha == "Assinatura"){ //informacao sobre bilhete assinatura

					string categoria, tipo;
					float preco;
					f >> categoria >> preco >> tipo;

					//se bilhete for do tipo normal
					if(tipo == "normal"){

						string nome;
						unsigned int id;
						int numDias;

						f >> nome; //extrai o nome do utente
						nome = replaceUnderscoresWithSpaces(nome);

						f >> id; //extrai o id do utente

						f >> numDias; //extrai o numero de dias ate ficar inativo


						Utente* u = getUtente(id); //verifica se o utente ja existe

						if(u != 0){ //se o utente esta presente

							BilheteAssinatura b3(categoria, preco, tipo, u); //cria bilhete
							l->addBilheteA(b3); //adiciona bilhete
						}

						else{ //se utente nao esta presente

							u = new Utente(nome, id, numDias); //cria um novo utente normal

							BilheteAssinatura b3(categoria, preco, tipo, u); //cria um bilhete, associado a esse utente
							l->addBilheteA(b3);
							this->addUtente(u);
							//adiciona o bilhete a loja, e adiciona o utente ao vetor de utentes
						}


					} //se bilhete for do tipo junior
					else if(tipo == "junior"){

						string nome, cc;
						int numDias;
						int idade;
						unsigned int id;

						f >> nome >> id >> numDias >> idade >> cc; //extrai nome, id, numero de dias, idade e CC do utente

						nome = replaceUnderscoresWithSpaces(nome);

						Utente* u = getUtente(id); //verifica se o utente ja existe

						if(u != 0){ //se o utente esta presente

							BilheteAssinatura b4(categoria, preco, tipo, u); //cria bilhete
							l->addBilheteA(b4); //adiciona bilhete
						}

						else{ //se utente nao esta presente

							u = new UtenteJunior(nome, id, numDias, idade, cc); //cria um novo utente junior

							BilheteAssinatura b4(categoria, preco, tipo, u); //cria um bilhete, associado a esse utente
							l->addBilheteA(b4);
							this->addUtente(u);
							//adiciona o bilhete a loja, e adiciona o utente ao vetor de utentes
						}


					//se bilhete for do tipo senior
					}else if(tipo == "senior"){

						string nome, cc;
						int numDias;
						int idade;
						unsigned int id;

						f >> nome >> id >> numDias >> idade >> cc; //extrai nome, id, numero de dias, idade e CC do utente

						nome = replaceUnderscoresWithSpaces(nome);

						Utente* u = getUtente(id); //verifica se o utente ja existe

						if(u != 0){ //se o utente esta presente

							BilheteAssinatura b5(categoria, preco, tipo, u); //cria bilhete
							l->addBilheteA(b5); //adiciona bilhete
						}

						else{ //se utente nao esta presente

							u = new UtenteSenior(nome, id, numDias, idade, cc); //cria um novo utente senior

							BilheteAssinatura b5(categoria, preco, tipo, u); //cria um bilhete, associado a esse utente
							l->addBilheteA(b5);
							this->addUtente(u);
							//adiciona o bilhete a loja, e adiciona o utente ao vetor de utentes
						}


					//se bilhete for do tipo estudante
					}else if(tipo == "estudante"){

						string nome, cc, escola;
						int numDias;
						int idade;
						unsigned int id;

						f >> nome >> id >> numDias >> idade >> cc >> escola; //extrai nome, numero de dias, idade, CC e escola do utente

						nome = replaceUnderscoresWithSpaces(nome);
						escola = replaceUnderscoresWithSpaces(escola);

						Utente* u = getUtente(id); //verifica se o utente ja existe

						if(u != 0){ //se o utente esta presente

							BilheteAssinatura b6(categoria, preco, tipo, u); //cria bilhete
							l->addBilheteA(b6); //adiciona bilhete
						}

						else{ //se utente nao esta presente

							u = new UtenteEstudante(nome, id, numDias, idade, cc, escola); //cria um novo utente estudante

							BilheteAssinatura b6(categoria, preco, tipo, u); //cria um bilhete, associado a esse utente
							l->addBilheteA(b6);
							this->addUtente(u);
							//adiciona o bilhete a loja, e adiciona o utente ao vetor de utentes
						}


					}else{
					}

				}

			}

		}


	}

	f.close();
	return 0;
}



int PontosVenda::save_file(string ficheiro){

	ofstream f;
	f.open(ficheiro, ofstream::out | ofstream::trunc); //apaga o conteudo do ficheiro, se existir

	if(!f.is_open()){	//nao conseguiu abrir o ficheiro
		cerr << "Nao foi possivel abrir o ficheiro!";
		return 1;
	}

	vector<vector<float> > precosZona = Bilhete::getPrecosZona();

	//insere no ficheiro os precos relativos as zonas e aos tipos de bilhete
	for(unsigned i = 0; i < precosZona.size(); i++){

		f << precosZona.at(i).at(0) << " " << precosZona.at(i).at(1) << " " << precosZona.at(i).at(2) << endl;
	}


	f << Utente::getNextId(); //insere no ficheiro o valor da variavel nextId, da classe Utente


	for(unsigned i = 0; i < ptsVenda.size(); i++){

		//verifica se o PDV atual e uma loja ou nao
		if(ptsVenda.at(i)->eLoja())
			f << endl << "LOJA" << endl;
		else f << endl << "MAQUINA" << endl;

		//insere o local no ficheiro
		f << replaceSpacesWithUnderscores(ptsVenda.at(i)->getLocal()) << endl;

		for(unsigned j = 0; j < ptsVenda.at(i)->getBilhetesO().size(); j++){ //info sobre bilhetes ocasionais

			f << "Ocasional" << endl;
			f << ptsVenda.at(i)->getBilhetesO().at(j).getCategoria() << endl;
			f << ptsVenda.at(i)->getBilhetesO().at(j).getPreco() << endl;
			f << ptsVenda.at(i)->getBilhetesO().at(j).getDuracao() << endl;

		}


		if(ptsVenda.at(i)->eLoja()){

			Loja* l = dynamic_cast<Loja*>(ptsVenda.at(i)); //info sobre bilhetes assinatura (se for loja)

			if(l != NULL){


				for(unsigned k = 0; k < l->getBilhetesA().size(); k++){

					f << "Assinatura" << endl;
					f << l->getBilhetesA().at(k).getCategoria() << endl;
					f << l->getBilhetesA().at(k).getPreco() << endl;

					string tipo = l->getBilhetesA().at(k).getTipo();
					f << tipo << endl;
					Utente* u = l->getBilhetesA().at(k).getAssinante();


					//insere no ficheiro a info do utente associado ao bilhete assinatura atual

					if(tipo == "normal"){

						f << *u << endl;

					}else if(tipo == "estudante"){

						UtenteEstudante *u1 = dynamic_cast<UtenteEstudante *>(u);

						if(u1 != NULL){
						f << *u1 << endl;

						}

					}else if(tipo == "senior"){

						UtenteSenior *u1 = dynamic_cast<UtenteSenior *>(u);

						if(u1 != NULL){
							f << *u1 << endl;

						}

					}else if(tipo == "junior"){

						UtenteJunior *u1 = dynamic_cast<UtenteJunior *>(u);

						if(u1 != NULL){
						f << *u1 << endl;

						}
					}else{
						cerr << "um ou mais utentes nao foram definidos corretamente!";
						return 1; //encontrado um tipo invalido
					}

			}

			}
		}


		f << "*****"; //usado para sinalizar o fim da informacao relativa a esse PDV
	}



	f.close();

	return 0;
}



Utente* PontosVenda::getUtente(unsigned int id){

	for(unsigned i = 0; i < utentes.size(); i++){

		if(utentes.at(i)->getId() == id)
			return utentes.at(i);

	}

	//throw UtenteInexistente(id);
	return 0;
}



vector<Utente*> PontosVenda::getUtentesAssinatura() const{
	return utentes;
}

void PontosVenda::comprarBilheteOcasional(string local, BilheteOcasional& bo){

	if(findPDV(local) != -1)
		ptsVenda[findPDV(local)]->addBilheteO(bo);
	else throw LocalInexistente(local);

}


bool PontosVenda::comprarBilheteAssinatura(string local, BilheteAssinatura& ba){

	/*for(unsigned i = 0; i < utentes.size(); i++){

		if(utentes.at(i)->getId() == ba.getAssinante()->getId())
			throw UtenteRepetido(ba.getAssinante()->getId());

	}

	if(findLoja(local) != -1){

		Loja* l = dynamic_cast<Loja*>(ptsVenda[findLoja(local)]);
		if(l != NULL){
			l->addBilheteA(ba);
			addUtente(ba.getAssinante());
			return true;
			}
	}
	else if(findPDV(local) != -1){ //verifica se ha uma maquina nesse local

		return false;
	}
	else throw LocalInexistente(local);*/


		if(findLoja(local) != -1){

			Loja* l = dynamic_cast<Loja*>(ptsVenda[findLoja(local)]);
			if(l != NULL){
				l->addBilheteA(ba);

				Utente* u = getUtente(ba.getAssinante()->getId()); //verifica se o utente ja existe

				if(u != 0){ //se o utente ja existe

					eliminaUtenteInat(u->getId()); //se ele estiver na tabela de dispersao, e eliminado

					u->resetDiasAteExpirar(); //da reset ao numero de dias que o utente tem ate ser considerado inativo

				}
				else{ //se o utente e novo, ou seja, ainda nao esta presente no vetor de utentes

					addUtente(ba.getAssinante()); //adiciona o utente ao vetor, assumindo que o numero de dias que este tem ate se tornar inativo ja se encontra no maximo
				}

				return true;
				}
		}
		else if(findPDV(local) != -1){ //verifica se ha uma maquina nesse local

			return false;
		}
		else throw LocalInexistente(local);

}



int PontosVenda::findPDV(string local) const{

	for(unsigned i = 0; i < ptsVenda.size(); i++){
		if(ptsVenda[i]->getLocal() == local)
			return i;
	}
	return -1;
}



int PontosVenda::findLoja(string local) const{

	for(unsigned i = 0; i < ptsVenda.size(); i++){
		if((ptsVenda[i]->getLocal() == local) && (ptsVenda[i]->eLoja()))
			return i;
	}
	return -1;
}




void PontosVenda::eliminaUtente(unsigned int id){
	/*bool bexiste = false;
	bool existe = false;
	for(unsigned i = 0; i < utentes.size() ; i++){
		if(utentes[i]->getId() == id){
			utentes.erase(utentes.begin() + i);
			existe = true;
		}
	}
	if(existe){
		for(unsigned i = 0; i < ptsVenda.size(); i++){
			if(ptsVenda[i]->eLoja()){

				Loja* l = dynamic_cast<Loja*>(ptsVenda.at(i));
				if(l != NULL){
				if(l->eraseBilheteA(id))
					bexiste = true;

				}
			}
		}

	}
	else throw UtenteInexistente(id);

	if(!bexiste)
		throw BilheteInexistente();*/


	Utente* u = getUtente(id); //verifica se o utente existe

	if(u == 0)
		throw UtenteInexistente(id); //utente nao existe no vetor; lanca excecao


	for(unsigned i = 0; i < utentes.size() ; i++){
		if(utentes[i]->getId() == id){
			utentes.erase(utentes.begin() + i); //apaga o utente do vetor
		}
	}


	eliminaUtenteInat(id); //elimina o utente da tabela de dispersao, se este se encontrar la


	bool existeBilhete = false;

	for(unsigned i = 0; i < ptsVenda.size(); i++){

		if(ptsVenda.at(i)->eLoja()){ //se for uma loja

			Loja* l = dynamic_cast<Loja*>(ptsVenda.at(i));

			if(l->eraseBilheteA(id))
				existeBilhete = true; //o utente tinha pelo menos um bilhete

		}

	}


	if(!existeBilhete)
		throw BilheteInexistente(); //o utente nao tinha nenhum bilhete de assinatura; lanca excecao

}



void PontosVenda::eliminaPDV(string local){
	/*int pos;
	pos = findPDV(local);
	if(pos != -1){

			if(ptsVenda[pos]->eLoja()){

				Loja* l = dynamic_cast<Loja*>(ptsVenda.at(pos));

			if(l != NULL){
				for(unsigned j = 0; j < l->getAssinantes().size(); j++)

					for(unsigned k = 0; k < utentes.size(); k++){

						if(l->getAssinantes()[j] == utentes[k]) //apontador de utente no bilhete assinatura aponta para o mesmo endereco que o apontador de utente no vetor utentes!
						utentes.erase(utentes.begin() + k);
				}
			}
			}
			ptsVenda.erase(ptsVenda.begin() + pos);
}
	else throw LocalInexistente(local);*/


	int pos;
	pos = findPDV(local);
	if(pos != -1){

		if(ptsVenda[pos]->eLoja()){

			Loja* l = dynamic_cast<Loja*>(ptsVenda.at(pos));

			if(l != NULL){

				vector<Utente*> assinantesDaLoja = l->getAssinantes(); //vetor com os utentes que tinham bilhetes nessa loja



				for(unsigned i = 0; i < assinantesDaLoja.size(); i++){

					bool bilhetesNoutraLoja = false; //bool que ira indicar se o utente possui bilhetes noutra(s) loja(s)

					for(unsigned j = 0; j < ptsVenda.size(); j++){

						if(j == pos) //se estivermos no ponto de venda que iremos apagar, passar a frente
							continue;

						if(ptsVenda.at(j)->eLoja()){

							Loja* l = dynamic_cast<Loja*>(ptsVenda.at(j));

							if(l != NULL){

								if(l->findUtente(assinantesDaLoja.at(i)->getId()) != -1) //se o utente tem bilhetes nesta loja...
									bilhetesNoutraLoja = true;
							}

						}
					}

					if(!bilhetesNoutraLoja){ //o utente nao tem bilhetes noutras lojas

						for(unsigned k = 0; k < utentes.size(); k++){

							if(utentes.at(k)->getId() == assinantesDaLoja.at(i)->getId()){

								eliminaUtenteInat(utentes.at(k)->getId()); //elimina o utente da tabela (se ele la estiver)
								utentes.erase(utentes.begin() + k); //ao encontrar o utente certo, apaga-o
							}
						}
					}

				}
			}
		}
		ptsVenda.erase(ptsVenda.begin() + pos);
	}
	else throw LocalInexistente(local);
}



void PontosVenda::addPDV(Maquina* m){

	for(unsigned i = 0; i < ptsVenda.size(); i++){

		if(ptsVenda.at(i)->getLocal() == m->getLocal())
			throw LocalRepetido(m->getLocal());

	}

	ptsVenda.push_back(m);
}



void PontosVenda::addPDV(string local, bool loja){

	for(unsigned i = 0; i < ptsVenda.size(); i++){

		if(ptsVenda.at(i)->getLocal() == local)
			throw LocalRepetido(local);

	}

	Maquina* m;

	if(loja)
		m = new Loja(local);
	else m = new Maquina(local);

	ptsVenda.push_back(m);

}



void PontosVenda::addUtente(Utente* u){

	/*for(unsigned i = 0; i < utentes.size(); i++){

		if(utentes.at(i)->getId() == u->getId())	//nao deixa haver dois utentes com o mesmo id!!
			throw UtenteRepetido(u->getId());

	}

	utentes.push_back(u);*/


	for(unsigned i = 0; i < utentes.size(); i++){

		if(utentes.at(i)->getId() == u->getId())	//nao deixa haver dois utentes com o mesmo id!!
			return;

	}

	utentes.push_back(u);
}




void PontosVenda::sortUtentesNome(){

	sort(utentes.begin(), utentes.end(), ordenaUtentesNome);
}




void PontosVenda::sortUtentesId(){

	sort(utentes.begin(), utentes.end(), ordenaUtentesId);
}




void PontosVenda::sortPDVsPorLocal(){

	sort(ptsVenda.begin(), ptsVenda.end(), ordenaPorLocal);
}




void PontosVenda::sortPDV(string local, bool crescente){

	if(findPDV(local) != -1){

		if(crescente)
			ptsVenda.at(findPDV(local))->sortBilhetesCrescente();
		else ptsVenda.at(findPDV(local))->sortBilhetesDecrescente();


	}else throw LocalInexistente(local);


}


//----------FUNCIONARIOS------------


set<Funcionario> PontosVenda::getFuncionarios() {return funcionarios;}


Funcionario PontosVenda::getFuncionario(string name, unsigned int salario) const {

	set<Funcionario>::iterator itr = funcionarios.begin();
	set<Funcionario>::iterator itre = funcionarios.end();

	while(itr != itre){
		if(itr->getNome() == name && itr->getSalario() == salario)
			return *itr;

		itr++;
	}

	throw FuncionarioInexistente(name, salario);
}


//Nota: nao podem haver 2 funcionarios com o mesmo nome e salario, pois a estrutura set nao pode ter
//dois membros iguais
bool PontosVenda::insertFuncionario(Funcionario f){
	return funcionarios.insert(f).second;
}


void PontosVenda::imprimeTodosFuncionarios(){

	if(funcionarios.empty()){
		cout << "Nao ha informacao relativa a funcionarios!" << endl << endl;
		return;
	}

	set<Funcionario>::iterator itr = funcionarios.begin();
	set<Funcionario>::iterator itre = funcionarios.end();

	cout << endl << "Funcionarios:" << endl;

	while(itr != itre){

		itr->imprimeInfoFuncionario();
		cout << endl << endl;

		itr++;
	}
}


void PontosVenda::imprimeFuncionariosPDV(string local){

	bool existe = false; //se nao houver nenhum funcionario no ponto de venda, existe continuara false

	set<Funcionario>::iterator itr = funcionarios.begin();
	set<Funcionario>::iterator itre = funcionarios.end();

	cout << endl;

	while(itr != itre){

		if(itr->getPtVenda() == local){
			existe = true;
			itr->imprimeInfoFuncionario();
			cout << endl << endl;
		}

		itr++;
	}

	if(!existe)
		cout << "Nao existem funcionarios no ponto de venda " << local << "!" << endl << endl << endl;

}


void PontosVenda::imprimeFuncionariosFuncao(string funcao){

	bool existe = false; //se nao houver nenhum funcionario com a funcao, existe continuara false

	set<Funcionario>::iterator itr = funcionarios.begin();
	set<Funcionario>::iterator itre = funcionarios.end();

	cout << endl;

	while(itr != itre){

		if(itr->getFuncao() == funcao){
			existe = true;
			itr->imprimeInfoFuncionario();
			cout << endl << endl;
		}


		itr++;
	}

	if(!existe)
		cout << "Nao existem funcionarios com a funcao " << funcao << "!" << endl << endl << endl;
}


bool PontosVenda::removeFuncionario(string nome, unsigned salario){

	//como o find apenas procura atraves do nome e do salario, a funcao e o ponto de venda nao irao ser relevantes
	Funcionario funcARemover(nome, salario, "", "");

	set<Funcionario>::iterator itr = funcionarios.find(funcARemover);


	if(itr == funcionarios.end()) //nao existe nenhum funcionario com aquele nome e salario
		return false;


	funcionarios.erase(itr); //apaga o funcionario
	return true;
}


//Como objetos dentro de um set nao podem ser alterados, tem que se remover o funcionario e voltar a
//inseri-lo depois de alterar o salario, ficando este ja inserido na ordem correta

bool PontosVenda::setFuncSalario(string nome, unsigned salario, unsigned int novoSalario){

	//como o find apenas procura atraves do nome e do salario, a funcao e o ponto de venda nao irao ser relevantes
	Funcionario funcARemover(nome, salario, "", "");

	set<Funcionario>::iterator itr = funcionarios.find(funcARemover);


	if(itr == funcionarios.end()) //nao existe nenhum funcionario com aquele nome e salario
		return false;

	Funcionario func = *itr;
	funcionarios.erase(itr); //apaga o funcionario

	func.changeSalario(novoSalario); //muda o salario

	funcionarios.insert(func); //insere de novo

	return true;
}


bool PontosVenda::setFuncFuncao(string nome, unsigned salario, string funcao){

	//como o find apenas procura atraves do nome e do salario, a funcao e o ponto de venda nao irao ser relevantes
	Funcionario funcARemover(nome, salario, "", "");

	set<Funcionario>::iterator itr = funcionarios.find(funcARemover);

	if(itr == funcionarios.end()) //nao existe nenhum funcionario com aquele nome e salario
		return false;

	Funcionario func = *itr;
	funcionarios.erase(itr); //apaga o funcionario

	func.changeFuncao(funcao); //muda a funcao

	funcionarios.insert(func); //insere de novo

	return true;
}


bool PontosVenda::setFuncPtVenda(string nome, unsigned salario, string pt_venda){

	//como o find apenas procura atraves do nome e do salario, a funcao e o ponto de venda nao irao ser relevantes
	Funcionario funcARemover(nome, salario, "", "");

	set<Funcionario>::iterator itr = funcionarios.find(funcARemover);

	if(itr == funcionarios.end()) //nao existe nenhum funcionario com aquele nome e salario
		return false;

	Funcionario func = *itr;
	funcionarios.erase(itr); //apaga o funcionario

	func.changePtVenda(pt_venda); //muda o ponto de venda

	funcionarios.insert(func); //insere de novo

	return true;
}


//----------COMPOSICAO------------

void PontosVenda::imprimeInfoComposicoes() const{

	cout << "Num de dias de uma manutencao proxima: " << Composicao::getManutProxima() << endl;

	priority_queue<Composicao> buffer = composicoes;

	if(buffer.empty()){
		cout << "Nao ha informacao relativa as composicoes!" << endl << endl << endl;
		return;
	}

	cout << endl << "Composicoes:" << endl;
	while(!buffer.empty()){

		Composicao atual = buffer.top();
		buffer.pop();

		atual.imprimeInfoComp();
		cout << endl << endl;
	}
}


bool PontosVenda::adicionaComposicao(Composicao c){

	priority_queue<Composicao> buffer = composicoes;

	while(!buffer.empty()){

		Composicao atual = buffer.top();
		buffer.pop();

		if(atual.getID() == c.getID())
			return false;
	}

	composicoes.push(c);
	return true;
}


bool PontosVenda::eliminaComposicao(unsigned id){

	priority_queue<Composicao> buffer;
	bool encontrou = false;

	while(!composicoes.empty()){

		Composicao atual = composicoes.top();
		composicoes.pop();

		if(atual.getID() == id)
			encontrou = true;
		else buffer.push(atual);

	}

	composicoes = buffer;
	if(encontrou)
		return true;
	else return false;
}


bool PontosVenda::poeCompAvariada(unsigned id){

		priority_queue<Composicao> buffer;
		bool encontrou = false;

		while(!composicoes.empty()){

			Composicao atual = composicoes.top();
			composicoes.pop();

			if(atual.getID() == id){
				encontrou = true;
				atual.poeAvariada();
				buffer.push(atual);
			}
			else buffer.push(atual);

		}

		composicoes = buffer;
		if(encontrou)
			return true;
		else return false;
}


void PontosVenda::avancaDiaComp(){

	priority_queue<Composicao> buffer;

	while(!composicoes.empty()){

		Composicao atual = composicoes.top();
		composicoes.pop();

		atual.avancaDia();

		buffer.push(atual);
	}

	composicoes = buffer;
}


void PontosVenda::atualizaComp(){

	avancaDiaComp(); //avanca um dia

	priority_queue<Composicao> buffer;

	while(!composicoes.empty()){

		Composicao atual = composicoes.top();
		composicoes.pop();

		//se estamos no dia da manutencao, ou se a composicao esta avariada e falta menos de x dias para a manutencao
		if((atual.getProxManut() == 0) || ((atual.getAvaria()) && (atual.getProxManut() < Composicao::getManutProxima()))){

			atual.fazManutencao();
		}

		buffer.push(atual);

	}

	composicoes = buffer;
}

//----------UTENTES INATIVOS------------

void PontosVenda::adicionaUtenteInat(Utente* u){
	utentesInativos.insert(u); //se ja se encontrar na tabela um utente com o mesmo id, nao faz nada
}

void PontosVenda::eliminaUtenteInat(unsigned id){

	tabDispUtentesInat::iterator itr = utentesInativos.begin();
	tabDispUtentesInat::iterator itre = utentesInativos.end();

	while(itr != itre){

		Utente* atual = (*itr);

		if(atual->getId() == id){

			utentesInativos.erase(itr);
			return;
		}

		itr++;
	}
}


void PontosVenda::atualizaInat(){

	for(unsigned i = 0; i < utentes.size(); i++){

		if(utentes[i]->getDiasAteExpirar() > 0)
			utentes[i]->avancaDia();
		if(utentes[i]->getDiasAteExpirar() == 0)
			adicionaUtenteInat(utentes[i]);
	}
}


void PontosVenda::imprimeInfoInativos(){

	cout << "LISTA DE UTENTES INATIVOS: " << endl << endl;
	tabDispUtentesInat::iterator it = utentesInativos.begin();
	while(it != utentesInativos.end()){
		(*it)->imprimeInfoUtente();
		cout << endl << endl;
		it++;
	}
}
