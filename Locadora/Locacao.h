#include <string>
#include <iostream>
#include <sstream>

using namespace std;

//declaração da classe Cliente
class Locacao
{
	private:
		int codigo_locacao;
		string nome_filme;
		string nome_cliente;
		string data_aluguel;
		string data_entrega;

	public:
		Locacao();
		~Locacao();

		int getCodigoLocacao();
		void setCodigoLocacao(int codigo_locacao);

		string getNomeFilme();
		void setNomeFilme(string nome_filme);

		string getNomeCliente();
		void setNomeCliente(string nome_cliente);
		
		string getDataEntrega();
		void setDataEntrega(string data_entrega);
		
		string getDataAluguel();
		void setDataAluguel(string data_aluguel);

		string imprimir();
		
		void ImprimirTodos();
};

//implementação das funções da classe Locacao
Locacao::Locacao(){}

Locacao::~Locacao()
{
	// Implementar
}

void Locacao::setCodigoLocacao(int codigo_locacao)
{
	this->codigo_locacao = codigo_locacao;
}

void Locacao::setNomeFilme(string nome_filme)
{
	this->nome_filme = nome_filme;
}

void Locacao::setNomeCliente(string nome_cliente)
{
	this->nome_cliente = nome_cliente;
}

void Locacao::setDataEntrega(string data_entrega)
{
	this->data_entrega = data_entrega;
}

void Locacao::setDataAluguel(string data_aluguel)
{
	this->data_aluguel = data_aluguel;
}

int Locacao::getCodigoLocacao()
{
	return codigo_locacao;
}

string Locacao::getNomeFilme()
{
	return nome_filme;
}

string Locacao::getNomeCliente()
{
	return nome_cliente;
}

string Locacao::getDataEntrega()
{
	return data_entrega;
}

string Locacao::getDataAluguel()
{
	return data_aluguel;
}

void Locacao::ImprimirTodos()
{
	cout<<"Codigo locacao: "<<codigo_locacao<<endl;
	cout<<"Nome do filme: "<<nome_filme<<endl;
	cout<<"Nome do cliente: "<<nome_cliente<<endl;
	cout<<"Data do emprestimo: "<<data_aluguel<<endl;
	cout<<"Data de entrega: "<<data_entrega<<endl;
}


//apresenta os dados da Locacao no console
string Locacao::imprimir()
{
	stringstream ss;

	ss << "Locacao" << ";" << codigo_locacao <<";" << nome_filme <<";" << nome_cliente <<";" <<data_aluguel << ";"<< data_entrega <<endl;
	
	string s = ss.str();
	
	return s;
}
