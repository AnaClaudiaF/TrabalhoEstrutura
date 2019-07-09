#include <string>
#include <iostream>
#include <sstream>

using namespace std;

//declaração da classe Cliente
class Cliente
{
private:
	string nome;
	string sobrenome;
	int codigo;
	string telefone;
	string endereco;

public:
	Cliente();
	Cliente(string nome, string sobrenome, string telefone, string endereco);
	~Cliente();

	string getnome();
	void setnome(string nome);

	string getsobrenome();
	void setsobrenome(string nome);

	int getCodigo();
	void setCodigo(int codigo);

	string getTelefone();
	void setTelefone(string Telefone);

	string getEndereco();
	void setEndereco(string Endereco);

	string imprimir();
};

//implementação das funções da classe Cliente
Cliente::Cliente(){}

Cliente::Cliente(string nome, string sobrenome, string telefone, string endereco)
{
	this->nome = nome;
	this->sobrenome = sobrenome;
	this->telefone = telefone;
	this->endereco = endereco;
}

Cliente::~Cliente()
{
	// Implementar
}

string Cliente::getnome()
{
	return nome;
}

string Cliente::getsobrenome()
{
	return sobrenome;
}

int Cliente::getCodigo()
{
	return codigo;
}

string Cliente::getTelefone()
{
	return telefone;
}

string Cliente::getEndereco()
{
	return endereco;
}

void Cliente::setnome(string arg_nome)
{
	this->nome = arg_nome;
}

void Cliente::setsobrenome(string arg_sobrenome)
{
	this->sobrenome = arg_sobrenome;
}

void Cliente::setCodigo(int arg_codigo)
{
	this->codigo = arg_codigo;
}

void Cliente::setTelefone(string arg_telefone)
{
	this->telefone = arg_telefone;
}

void Cliente::setEndereco(string arg_endereco)
{
	this->endereco = arg_endereco;
}

//apresenta os dados da Cliente no console
string Cliente::imprimir()
{
	std::stringstream ss;
	
	ss << "Cliente"<< ";" << codigo <<";" << nome <<";" << sobrenome <<";" << telefone <<";" << endereco <<";" << endl;
	
	string s = ss.str();
	
	return s;
}
