#include "Maquina.h"
#include "Utente.h"
#include <iostream>
 using namespace std;


string Maquina::getLocal() const{
	return local;
}


vector<BilheteOcasional> Maquina::getBilhetesO() const{
	return bilhetesO;
}


void Maquina::imprimeInfoPDV() const{

	if(eLoja())
		cout << "LOJA" << endl;
	else cout << "MAQUINA" << endl;

	cout << "Local: " << local << endl;
	cout << "Bilhetes Ocasionais:" << endl << endl;

	if(bilhetesO.size() == 0){

		cout << "Nao ha informacao sobre bilhetes ocasionais neste ponto de venda!" << endl << endl;
	}

	for(unsigned i = 0; i < bilhetesO.size(); i++){

		bilhetesO.at(i).imprimeInfoBilhete();
		cout << endl << endl;

	}

}


void Maquina::addBilheteO(BilheteOcasional& bilhete) {
	bilhetesO.push_back(bilhete);
}



vector<BilheteAssinatura> Loja::getBilhetesA() const{
	return bilhetesA;
}


int Loja::findUtente(unsigned int id) const{

	for(unsigned i = 0; i < bilhetesA.size(); i++){

		if(bilhetesA[i].getAssinante()->getId() == id)
			return i;

	}

	return -1;

}



void Loja::imprimeInfoPDV() const{

	Maquina::imprimeInfoPDV();

	cout << "Bilhetes Assinatura:" << endl << endl;


	if(bilhetesA.size() == 0){

		cout << "Nao ha informacao sobre bilhetes assinatura neste ponto de venda!" << endl << endl;
	}

	for(unsigned i = 0; i < bilhetesA.size(); i++){

		bilhetesA.at(i).imprimeInfoBilhete();
		cout << endl << endl;

	}


}



void Loja::addBilheteA(BilheteAssinatura& bilhete){
	bilhetesA.push_back(bilhete);
}



bool Maquina::eLoja() const{

	return false;
}


bool Loja::eLoja() const{

	return true;
}



vector<Utente*> Loja::getAssinantes() const{

	vector<Utente*> utentes;

	for(unsigned i = 0; i < bilhetesA.size(); i++)
		utentes.push_back(bilhetesA.at(i).getAssinante());

	return utentes;
}



bool Loja::eraseBilheteA(unsigned int id){
	int pos = findUtente(id);
	if(pos != -1){
		bilhetesA.erase(bilhetesA.begin() + pos);
		return true;
	}
	return false;

	/*bool encontrou = false;

		while(true){
			int pos = findUtente(id);

			if(pos != -1){
				bilhetesA.erase(bilhetesA.begin() + pos);
				encontrou = true;
			}
			else break;
		}

		return encontrou;*/
}


void Maquina::sortBilhetesCrescente(){

	sort(bilhetesO.begin(), bilhetesO.end());
}


void Loja::sortBilhetesCrescente(){

	Maquina::sortBilhetesCrescente();

	sort(bilhetesA.begin(), bilhetesA.end());
}


void Maquina::sortBilhetesDecrescente(){

	sort(bilhetesO.begin(), bilhetesO.end(), ordenaBilhetesODecrescente);

}


void Loja::sortBilhetesDecrescente(){

	Maquina::sortBilhetesDecrescente();

	sort(bilhetesA.begin(), bilhetesA.end(), ordenaBilhetesADecrescente);

}


bool ordenaPorLocal(const Maquina* m1, const Maquina* m2){

	return m1->getLocal() < m2->getLocal();
}
