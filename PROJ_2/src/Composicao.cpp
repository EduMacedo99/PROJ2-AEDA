#include "Composicao.h"
//FAZER MAIS INCLUDES
using namespace std;


int Composicao::getProxManut() const{
	return prox_manut;
}

bool Composicao::getAvaria() const{
	return avaria;
}


void Composicao::fazManutencao(){

	prox_manut = 30; //nova manutencao no proximo mes
	avaria = false;
}


bool Composicao::operator<(Composicao c){
	return prox_manut > c.getProxManut();
}
