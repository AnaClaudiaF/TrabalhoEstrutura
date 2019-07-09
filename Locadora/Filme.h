#include <string>
#include <iostream>
#include <sstream>

using namespace std;

//declaração da classe Filme
class Filme
{
private:
	string nome;
	string genero;
	int codigo;

public:
	Filme();
	Filme(int codigo, string nome, string genero);
	~Filme();

	int getCodigo();
	void setCodigo(int codigo);

	string getnome();
	void setnome(string nome);

	string getgenero();
	void setgenero(string genero);

	string imprimir();
};

//implementação das funções da classe Filme
Filme::Filme(){}

Filme::Filme(int codigo, string nome, string genero)
{
	this->codigo = codigo;
	this->nome = nome;
	this->genero = genero;

}

Filme::~Filme()
{
	// Implementar
}

int Filme::getCodigo()
{
	return codigo;
}

string Filme::getnome()
{
	return nome;
}

string Filme::getgenero()
{
	return genero;
}

void Filme::setCodigo(int Codigo)
{
	this->codigo = Codigo;
}

void Filme::setnome(string nome)
{
	this->nome = nome;
}


void Filme::setgenero(string genero)
{
	this->genero = genero;
}

//apresenta os dados da Filme no console
string Filme::imprimir()
{
	std::stringstream ss;

	ss << "Filme" << ";" << codigo <<";" << nome <<";" << genero <<";" << endl;
	
	string s = ss.str();
	
	return s;
}
