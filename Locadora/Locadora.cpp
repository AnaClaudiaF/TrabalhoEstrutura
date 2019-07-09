#include <iostream>
#include <cstdlib>
#include <string.h>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include<vector>

#include "Cliente.h"
#include "Filme.h"
#include "Locacao.h"
#include "Hash.h"
#include "Arquivo.h"

using namespace std;

//declara um ponteiro para a tabela hash
Hash<int, Cliente> hs_cliente;
Hash<int, Filme> hs_filme;
Hash<int, Locacao> hs_filme_alugar;
Arquivo arq;

/**
Método split para remover caracteres quebra de linha ";", ou qualquer
outro tipo de conteúdo
*/
vector<string> split(string str, char delimiter)
{
	vector<string> internal;
	stringstream ss(str);  // Turn the string into a stream.
	string tok;
  
	while(getline(ss, tok, delimiter))
	{
		internal.push_back(tok);
	} 
	return internal;
}

/**
Método responsável por inserir os dados do cliente no Hash
*/
void InserirCliente()
{
	int
	codigo_cliente = 0, // Codigo do cliente
	codigo_hash = 0; // Código Hash (Codigo_Cliente % Tamanho_Tabela)

	string
	nome, // Variável para guardar o nome
	sobrenome,// Variável para guardar o sobrenome
	telefone, // Variável para guardar o telefone
	endereco; // Variável para guardar o endereco
	
	Cliente c; // Cliente
				
	cout <<"Informe o codigo: "; // pede o codigo
	cin >> codigo_cliente; // recebe o codigo
	cout <<"Informe o nome: "; // pede o nome
	cin.ignore();
	getline(cin, nome); // recebe o nome
	cout <<"Informe o sobrenome: "; // pede o sobrenome
	cin.ignore();
	getline(cin, sobrenome); // recebe o sobrenome
	cout <<"Informe o telefone: "; // pede o telefone
	cin >> telefone; // recebe o telefone
	cout <<"Informe o endereco: "; // pede o endereço
	cin.ignore();
	getline(cin, endereco); // recebe o endereco
	
	c.setCodigo(codigo_cliente); // Seta o codigo do cliente na classe Cliente
	c.setnome(nome); // Seta o nomedo cliente na classe Cliente
	c.setsobrenome(sobrenome); // Seta o sobrenomedo cliente na classe Cliente
	c.setTelefone(telefone); // Seta o telefone do cliente na classe Cliente
	c.setEndereco(endereco); // Seta o endereco do cliente na classe Cliente
	
	// Insere na tabela hash
	codigo_hash = hs_cliente.Insert(codigo_cliente, c);
	
	// Chama a função da classe arquivo
	arq.CriarArquivo("cliente", c.imprimir(), codigo_hash); 
}

Cliente ConsultarNomeCliente(string nome, bool mostrar_dados)
{
	Cliente cliente; // Variavel de controle
	int op = -1; // Opcao de inserção

 	// Procura o nome do cliente e alimenta a variavel cliente
	cliente = hs_cliente.FindCliente(nome);
	
	// Se o cliente estiver vazio
	if (cliente.getnome().empty())
	{
		cout<<"Cliente nao encontrado. Deseja inserir um novo? \n 1 - Sim, 0 - Nao: ";
		cin >> op;
		
		// Verifica se a opcao do usuario foi igual 1
		if (op == 1)
		{
			// Chama a funcao inserir cliente
			InserirCliente(); 
		}
		
		else
		{
			return cliente;
		}
	}
	
	// Se for permitido mostrar os dados para o usuario
	if (mostrar_dados)
	{
		// Faz o split retirando o caracter ';'
		vector<string> separador = split(cliente.imprimir(), ';');
		
		cout<<"Codigo cliente: " << separador[1]<<endl; // Imprime o código do cliente
		cout<<"Nome completo: "<< separador[2] << " " <<separador[3]<<endl; // Imprime o nome + sobrenome
		cout<<"Telefone: " <<separador[4]<<endl; // Imprime o telefone
		cout<<"Endereco: "<<separador[5]<<endl; // Imprime o endereco
		system("Pause");
	}
	
	return cliente; // Retorna a estrutura
}

void InserirFilme()
{
	Filme filme; // variável de controle
	int codigo, codigo_hash; // variável de trabalho;
	string nome, genero; // variável de trabalho;
	
	cout <<"Informe o codigo: "; // pede o codigo
	cin >> codigo; // recebe o codigo
	cout <<"Informe o nome do filme: "; // pede o nome do filme
	cin >> nome; // recebe o nome
	cout <<"Informe o genero: "; // pede o genero do filme
	cin >> genero; // recebe o genero
	
	filme.setCodigo(codigo); // Seta o codigo do filme
	filme.setnome(nome); // Seta o nome do filme
	filme.setgenero(genero); // Seta o genero do filme

	// Insere o conteúdo na tabela Hash
	codigo_hash = hs_filme.Insert(codigo, filme); 
	
	// Armazena o conteudo no arquivo
	arq.CriarArquivo("filme", filme.imprimir(), codigo_hash);
}

void ConsultarNomeFilme(string nome_filme, bool mostrar_informacao)
{
	// Variável de controle
	Filme filme; 
	
	// Variável de opcao
	int op = -1;

 	// Busca o nome do filme
	filme = hs_filme.FindFilme(nome_filme);
	
	if (filme.getnome().empty())
	{
		cout<<"Filme nao encontrado. Deseja inserir um novo? \n 1 - Sim, 0 - Nao: ";
		cin >> op;
		
		if (op == 1)
		{
			// Chama o método de inserção de cliente
			InserirFilme();
		}
		
		else
		{
			return;
		}
	}
	
	if (mostrar_informacao)
	{
		vector<string> separador = split(filme.imprimir(), ';');
		
		cout<<"Codigo filme: " << separador[1]<<endl;
		cout<<"Nome: "<< separador[2]<<endl;
		cout<<"Genero: "<<separador[3]<<endl;
		system("Pause");
	}
}

Filme ConsultarFilmeCodigo(int codigo)
{
	Filme f;
	
	if (hs_filme.isEmpty())
	{
		cout <<"Lista vazia"<<endl;
		return f;
		system("Pause");
	}

	f = hs_filme.Find(codigo);

	return f;
}

void AlugarFilme()
{
	Locacao l;
	Filme f;
	Cliente c;
	int codigo_filme, codigo_reserva, codigo_hash; // variável de trabalho;
	string nome, data_aluguel, data_entrega; // variável de trabalho;
	
	cout <<"Informe o codigo da reserva"<<endl;
	cin >> codigo_reserva;
	cout <<"Informa a data do aluguel: "<<endl;
	cin >> data_aluguel;
	cout <<"Informe a data de entrega: "<<endl;
	cin >> data_entrega;
	cout <<"Informe o codigo do filme: "<<endl; // pede o codigo
	cin >> codigo_filme; // recebe o codigo
	cout << "Informe o nome do cliente: "<<endl;
	cin >> nome;

	// Pesquisa o codigo do filme
	f = ConsultarFilmeCodigo(codigo_filme);
	
	// Se nao tem conteudo
	if (f.getnome().empty())
	{
		cout<<"Filme nao encontrado. Cadastre o filme antes de alugar"<<endl;
		system("Pause");
	}

	c = ConsultarNomeCliente(nome, false);

	l.setCodigoLocacao(codigo_reserva);
	l.setNomeFilme(f.getnome());
	l.setNomeCliente(c.getnome());
	l.setDataAluguel(data_aluguel);
	l.setDataEntrega(data_entrega);
	
	codigo_hash = hs_filme_alugar.Insert(codigo_reserva, l);
	
	arq.CriarArquivo("filmealugar", l.imprimir(), codigo_hash); // chama a função da classe arquvivo
}

void ExcluirCliente()
{
	Cliente c;
	int codigo;
	
	cout<<"Informe o codigo do cliente a ser removido"<<endl;
	cin >> codigo;
	
	hs_cliente.Remove(codigo);
}

void ExcluirFilme()
{
	int codigo;
	Filme f;
	
	cout <<"Informe o codigo do filme: ";
	cin >> codigo;
	
	if (hs_filme.isEmpty())
	{
		cout<<"Nao ha registros na lista"<<endl;
		return;
		system("Pause");
	}
	
	f = hs_filme.Find(codigo);
	
	if (f.getnome().empty())
	{
		cout<<"Nao existem filmes com esse codigo"<<endl;
		return;
		system("Pause");
	}
	
	hs_filme.Remove(codigo);
	
	std::stringstream ss;
	
	ss << "filme_" << codigo <<".txt";
	
	std:string s = ss.str();

	std::remove(s.c_str());
	std::ofstream output(s.c_str());
}

void ConsultarFilmesAlugados()
{
	system("cls");
	hs_filme_alugar.ListarTodos();
	system("Pause");
}

void ArquivoAbrir()
{
	vector<string>sep;
	DIR *diretorio = NULL;
	diretorio = opendir("..\\Locadora");
	string novo;
	 
	struct dirent *pent = NULL;
	
	// Se o diretorio nao foi encontrado
	if (diretorio == NULL)
	{
		// Mostra a mensagem de erro
		cout<<"\nErro! Diretorio nao encontrado";
		system("Pause");
		return;
	}
	
	// Percorre os  arquivos encontrado no diretorio
	while (pent = readdir(diretorio))
	{
		// Se nao foi encontrado o arquivo
		if (pent == NULL)
		{
			// Mostra a mensagem de erro
			cout<<"\nErro! Arquivo nao encontrado!";
			system("Pause");
			return;
		}
	
		// Recupera o nome do arquivo encontrado
		string fn = pent->d_name;

		// Se o tipo de arquivo for do tipo .txt
		if(fn.substr(fn.find_last_of(".") + 1) == "txt")
		{
			ifstream arquivo(fn.c_str());
	
		    if (arquivo.is_open())
		    {
	        	getline(arquivo, novo);
	        	
	        	sep = split(novo, ';');
	        	
	        	if (sep[0].compare("Cliente") == 0)
	        	{
		        	Cliente c;
					c.setCodigo(atoi(sep[1].c_str()));
					c.setnome(sep[2]);
					c.setsobrenome(sep[3]);
					c.setTelefone(sep[4]);
					c.setEndereco(sep[5]);
					
					hs_cliente.Insert(atoi(sep[1].c_str()), c);
					continue;
	        	}
	        	
	        	if (sep[0].compare("Filme") == 0)
	        	{
	        		Filme f;
					f.setCodigo(atoi(sep[1].c_str()));
					f.setnome(sep[2]);
					f.setgenero(sep[3]);
					
					hs_filme.Insert(atoi(sep[1].c_str()), f);
					continue;
	        	}
	        	
	        	if(sep[0].compare("Locacao") == 0)
	        	{
	             	Locacao l;
					l.setCodigoLocacao(atoi(sep[1].c_str()));
					l.setNomeFilme(sep[2]);
					l.setNomeCliente(sep[3]);
					l.setDataAluguel(sep[4]);
					l.setDataEntrega(sep[5]);
					
					hs_filme_alugar.Insert(atoi(sep[1].c_str()), l);
					continue;
	        	}
		    }
	   		arquivo.close();
		}
	}

	closedir (diretorio);
}

int main()
{
	
	ArquivoAbrir();
	int op = -1, codigo = 0;
	string nome;

	while (op != 0)
	{
		system("cls");
		cout << "-----------------------------" << endl;
		cout << "\tLocadora de filmes" << endl;
		cout << "1 - Cadastro de filmes" << endl;
		cout << "2 - Cadastro de cliente" << endl;
		cout << "3 - Consultar filme" <<endl;
		cout << "4 - Consultar cliente" <<endl;
		cout << "5 - Listar filmes alugados" <<endl;
		cout << "6 - Alugar Filme" <<endl;
		cout << "7 - Remover cliente" << endl;
		cout << "8 - Remover filme" << endl;
		cout << "0 - Sair" << endl;
		cout << "-----------------------------" << endl;
		cout << "Digite a opcao desejada: ";
		cin >> op;

		switch (op)
		{
			case 0:
			{
				exit(0);
				break;
			}

			case 1:
			{			
				InserirFilme(); // Chama o método que irá inserir o filme no mapa e gerar o arquivo
				
				break; // para o processamento
			}

			case 2:
			{
				InserirCliente(); // chama o método que irá gerar o arquivo e inserir no HashTable
				
				break; // para o processamento
			}

			case 3:
			{
				if (hs_filme.isEmpty())
				{
					cout <<"Nao ha filmes inseridos na lista"<<endl;
					system("Pause");
					break;
				}
				
				cout <<"Informe o nome do filme: "; // pede o nome do filme
				cin >> nome; // recebe o nome
				
				ConsultarNomeFilme(nome, true); // chama o método que consulta o nome do filme
				
				break;
			}
			
			case 4:
			{
				if (hs_cliente.isEmpty())
				{
					cout<<"Nao ha registros inseridos na lista"<<endl;
					system("Pause");
					break;
				}
				cout <<"Informe o nome do cliente: ";
				cin >> nome;
				ConsultarNomeCliente(nome, true);
				break;
			}
			
			case 5:
			{
				ConsultarFilmesAlugados();
				break;
			}

			case 6:
			{
				AlugarFilme();
				break;
			}

			case 7:
			{
				ExcluirCliente();
				break;
			}

			case 8:
			{
				ExcluirFilme();
				break;
			}
		}
	}

	return 0;
}
