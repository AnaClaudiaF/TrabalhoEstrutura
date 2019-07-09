#include <iostream>
#include <cstdlib>
#include <string.h>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <dirent.h>

using namespace std;

class Arquivo
{
	private:
		char nome_arquivo[40];
		
		public:
			void CriarArquivo(string nome_arquivo, string conteudo, int codigo);
			void AbrirArquivo();
};

void Arquivo::CriarArquivo(string nome_arquivo, string conteudo, int codigo)
{
	stringstream ss;
	
	ss << nome_arquivo <<"_"<<codigo << ".txt";
	
	ofstream arquivo;
	
	string s = ss.str();
	
	arquivo.open(s.c_str());
	
	if (arquivo.is_open())
	{
	 	arquivo << conteudo << endl;
	  	arquivo.close();
	}
}

void Arquivo::AbrirArquivo()
{	
	DIR *diretorio = NULL;
	diretorio = opendir("..\\Trabalho_Arquivo");
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
			ifstream arquivo (fn.c_str());
	
		    if (arquivo.is_open())
		    {
	        	getline(arquivo, novo);
	        	
	        	cout<<"Novo \n"<<novo<<endl;
	        	system("Pause");
		    }
	   		arquivo.close();
		}
	}

	closedir (diretorio);
}
