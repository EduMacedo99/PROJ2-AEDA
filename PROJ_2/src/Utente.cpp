#include "Utente.h"

unsigned int Utente::nextId = 0;

int Utente::numDiasExpiracao;


int Utente::getNumDiasExpiracao(){
	return numDiasExpiracao;
}

void Utente::setNumDiasExpiracao(int numDias){
	numDiasExpiracao = numDias;
}

string replaceUnderscoresWithSpaces(string s){

	string sFinal = s;

	for(unsigned i = 0; i < sFinal.length(); i++){

		if(sFinal.at(i) == '_')
			sFinal.at(i) = ' ';
	}

	return sFinal;
}


string replaceSpacesWithUnderscores(string s){

	string sFinal = s;

	for(unsigned i = 0; i < sFinal.length(); i++){

		if(sFinal.at(i) == ' ')
			sFinal.at(i) = '_';
	}

		return sFinal;

}


ostream& operator<<(ostream &os, const UtenteSenior&u){

	os << replaceSpacesWithUnderscores(u.nome) << endl << u.id << endl << u.diasAteExpirar << endl << u.idade << endl << u.cc;
	return os;

}

ostream& operator<<(ostream &os, const UtenteJunior&u){

	os << replaceSpacesWithUnderscores(u.nome) << endl << u.id << endl << u.diasAteExpirar << endl << u.idade << endl << u.cc;
	return os;

}


ostream& operator<<(ostream &os, const UtenteEstudante&u){

	os << replaceSpacesWithUnderscores(u.nome) << endl << u.id << endl << u.diasAteExpirar << endl << u.idade << endl << u.cc << endl << replaceSpacesWithUnderscores(u.escola);
	return os;

}


ostream& operator<<(ostream &os, const Utente&u){

	os << replaceSpacesWithUnderscores(u.nome) << endl << u.id << endl << u.diasAteExpirar;
	return os;

}


unsigned int Utente::getNextId(){
	return nextId;
}


void Utente::setNextId(unsigned int valor){
	nextId = valor;
}


void Utente::avancaDia(){
	diasAteExpirar--;
}


void Utente::resetDiasAteExpirar(){
	diasAteExpirar = numDiasExpiracao;
}


void Utente::imprimeInfoUtente() const{

	cout << "ID: " << id << endl;
	cout << "Nome: " << nome << endl;
	cout << "Num dias ate expirar: " << diasAteExpirar;
}



string Utente::getNome() const{

	return nome;
}


unsigned int Utente::getId() const{

	return id;
}


int Utente::getDiasAteExpirar() const{

	return diasAteExpirar;
}



int UtenteEstudante::getIdade() const{

	return idade;
}



string UtenteEstudante::getCC() const{

	return cc;
}



string UtenteEstudante::getEscola() const{

	return escola;
}


void UtenteEstudante::imprimeInfoUtente() const{

	cout << "ID: " << id << endl;
	cout << "Nome: " << nome << endl;
	cout << "Num dias ate expirar: " << diasAteExpirar << endl;
	cout << "Idade: " << idade << endl;
	cout << "CC: " << cc << endl;
	cout << "Escola: " << escola;
}


int UtenteSenior::getIdade() const{

	return idade;
}


string UtenteSenior::getCC() const{

	return cc;
}


void UtenteSenior::imprimeInfoUtente() const{

	cout << "ID: " << id << endl;
	cout << "Nome: " << nome << endl;
	cout << "Num dias ate expirar: " << diasAteExpirar << endl;
	cout << "Idade: " << idade << endl;
	cout << "CC: " << cc;
}



int UtenteJunior::getIdade() const{

	return idade;
}


string UtenteJunior::getCC() const{

	return cc;
}



void UtenteJunior::imprimeInfoUtente() const{

	cout << "ID: " << id << endl;
	cout << "Nome: " << nome << endl;
	cout << "Num dias ate expirar: " << diasAteExpirar << endl;
	cout << "Idade: " << idade << endl;
	cout << "CC: " << cc;
}


bool ordenaUtentesNome(const Utente* u1, const Utente* u2){

	return u1->getNome() < u2->getNome();
}

bool ordenaUtentesId(const Utente* u1, const Utente* u2){

	return u1->getId() < u2->getId();

}
