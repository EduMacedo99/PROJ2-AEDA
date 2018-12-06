#include "Bilhete.h"

using namespace std;

vector<vector<float> > Bilhete::pZonas;

float Bilhete::getPreco() const{
	return preco;
}

string Bilhete::getCategoria() const{
	return categoria;
}


string BilheteOcasional::getDuracao() const{
	return duracao;
}



Utente* BilheteAssinatura::getAssinante() const{
	return assinante;
}


string BilheteAssinatura::getTipo() const{
	return tipo;
}


vector<vector<float> > Bilhete::getPrecosZona(){
	return pZonas;
}



float Bilhete::makePreco(string categoria,string especificacao) const{

	unsigned int catIndice; //indice para aceder a categoria correta

	if(categoria == "Z1")
		catIndice = 0;
	else if(categoria == "Z2")
		catIndice = 1;
	else if(categoria == "Z3")
		catIndice = 2;
	else if(categoria == "Z4")
		catIndice = 3;
	else return 0;



	if(especificacao == "unico")
		return pZonas.at(catIndice).at(0);
	else if(especificacao == "diario")
		return pZonas.at(catIndice).at(1);
	else if(especificacao == "normal")
		return pZonas.at(catIndice).at(2);
	else if((especificacao == "estudante") || (especificacao == "junior") || (especificacao == "senior"))
		return pZonas.at(catIndice).at(2) * 0.75; //25% de desconto
	else return 0;

}



void Bilhete::setPreco(float preco){

	this->preco = preco;
}


void Bilhete::setPrecosZona(vector<vector<float> > precos){
	pZonas = precos;
}


void Bilhete::imprimePrecosZona(){

	for(unsigned i = 0; i < pZonas.size(); i++){

		cout << endl << "Zona " << i + 1 << ":" << endl;

		cout << "Unico: " << pZonas.at(i).at(0) << " ; ";
		cout << "Diario: " << pZonas.at(i).at(1) << " ; ";
		cout << "Assinatura: " << pZonas.at(i).at(2) << " ; ";
		cout << "Assinatura c/ desconto (25%): " << pZonas.at(i).at(2)* 0.75;

	}

	cout << endl << endl;
}


void BilheteOcasional::imprimeInfoBilhete() const{
	cout << "Bilhete: Ocasional" << endl;
	cout << "Categoria: " << categoria << endl;
	cout << "Preco: " << preco << endl;
	cout << "Duracao: " << duracao;
}


void BilheteAssinatura::imprimeInfoBilhete() const{
	cout << "Bilhete: Assinatura" << endl;
	cout << "Categoria: " << categoria << endl;
	cout << "Preco: " << preco << endl;
	cout << "Tipo: " << tipo << endl;
	cout << "Assinante: " << endl;

	assinante->imprimeInfoUtente();
}


bool Bilhete::operator<(const Bilhete& b) const{

	return preco < b.getPreco();
}



bool ordenaBilhetesADecrescente(const BilheteAssinatura &b1, const BilheteAssinatura &b2){

	return b1.getPreco() > b2.getPreco();
}


bool ordenaBilhetesODecrescente(const BilheteOcasional &b1, const BilheteOcasional &b2){

	return b1.getPreco() > b2.getPreco();
}
