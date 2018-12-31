#include "Composicao.h"
//FAZER MAIS INCLUDES
using namespace std;

int Composicao::manutProxima;

int Composicao::compNextId = 0;

int Composicao::getID() const{
	return idC;
}

int Composicao::getProxManut() const{
	return proxManut;
}

bool Composicao::getAvaria() const{
	return avaria;
}


void Composicao::fazManutencao(){

	proxManut = 30; //nova manutencao no proximo mes
	avaria = false;
}


int Composicao::getCompNextId(){
	return compNextId;
}

void Composicao::setCompNextId(int valor){
	compNextId = valor;
}


bool Composicao::operator<(Composicao c) const{
	return proxManut > c.getProxManut();
}

int Composicao::getManutProxima(){
	return manutProxima;
}

void Composicao::setManutProxima(int numDias){
	manutProxima = numDias;
}

void Composicao::poeAvariada(){
	avaria = true;
}


void Composicao::imprimeInfoComp(){

	cout << "ID: " << idC << endl;
	cout << "Num dias ate prox manutencao: " << proxManut << endl;
	cout << "Avariada: ";
	if(avaria)
		cout << "sim";
	else cout << "nao";
}

void Composicao::avancaDia(){
	proxManut--;
}
