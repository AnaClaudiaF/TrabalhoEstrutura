#include<string>
#include<list>
#include<sstream>
#include<iostream>
#include<typeinfo>

#define TABLE_SIZE 5 // Define o tamanho da tabela

template<typename K, typename V>
class HashEntry
{
	private:
		K key;
		V value;
      	HashEntry *next;
	public:
		HashEntry(K const& key, V const& value)
		{	
			this->key = key;
			this->value = value;
			this->next = NULL;
		}
		
		K getKey()
		{
			return key;
		}
		
		V getValue()
		{
			return value;
		}
		
		void setValue(K const& key, V const& value)
		{
      		this->key = key;
			this->value = value;
		}
		
		HashEntry *getNext()
		{
			return next;
		}
		
		void setNext(HashEntry *next)
		{
			this->next = next;
		}
};

		/*Chave,	Valor*/
template<typename K, typename V>
class Hash
{
	private:
	      HashEntry<K,V> **table;
	      int contador;
	public:
		int Insert(K const& key, V const& value); // Insere no vetor
		V Find(K const& key); // Busca realizada pelo código, retornando assim a posição que se encontra no vetor
		V FindCliente(string nome);
		V FindFilme(string nome);
		void ListarTodos();
		void Remove(K const& key);
		bool isEmpty();
		int size();
		Hash(K const& key, V const& elem); // Construtur recebendo métodos
		Hash(); // Construtor vazio
		~Hash(); // Destruct da classe
};

template<typename K, typename V>
Hash<K, V>::Hash()
{
    table = new HashEntry<K,V>*[TABLE_SIZE];
    
    for (int i = 0; i < TABLE_SIZE; i++)
    {
          table[i] = NULL;
    }
}

template<typename K, typename V>
int Hash<K,V>::Insert(K const& key, V const& value)
{
	int hash = (key % TABLE_SIZE);
	
    if (table[hash] == NULL)
    {
		table[hash] = new HashEntry<K,V>(key, value);
	}
	
    else
	{
		HashEntry<K,V> *entry = table[hash];
		
		while (entry->getNext() != NULL)
		{
			entry = entry->getNext();
		}
		
		if (entry->getKey() == key)
		{
			entry->setValue(key, value);
		}
	
		else
		{
			entry->setNext(new HashEntry<K,V>(key, value));
		}
    }
	
	contador++;
	
	return hash;
}

template<typename K, typename V>
V Hash<K,V>::Find(K const& key)
{
	int posicao = (key % TABLE_SIZE);
	V valor_retornar;

    while (table[posicao] != NULL)
    {
    	if (table[posicao]->getKey() == key)
    	{
    		valor_retornar = table[posicao]->getValue();
    		break;
    	}
    	
		posicao = (posicao + 1) % TABLE_SIZE;
	}
	
	return valor_retornar;
}

template<typename K, typename V>
V Hash<K,V>::FindCliente(string value)
{
	Cliente c;
	V valor_retornar;

	for (int i = 0; i < TABLE_SIZE; i++)
	{
		if (table[i] != NULL)
		{
			c = table[i]->getValue();
			
			if (c.getnome() == value)
			{
				valor_retornar = table[i]->getValue();
			}
		}	
	}

	return valor_retornar;
}

template<typename K, typename V>
V Hash<K,V>::FindFilme(string value)
{
	Filme f;
	V valor_retornar;

	for (int i = 0; i < TABLE_SIZE; i++)
	{
		if (table[i] != NULL)
		{
			f = table[i]->getValue();
			
			if (f.getnome() == value)
			{
				valor_retornar = table[i]->getValue();
			}
		}	
	}

	return valor_retornar;
}

template<typename K, typename V>
void Hash<K,V>::ListarTodos()
{
	Locacao l;
	V valor_retornar;

	for (int i = 0; i < TABLE_SIZE; i++)
	{
		if (table[i] != NULL)
		{
			l = table[i]->getValue();
			
			l.ImprimirTodos();
			cout<<"\n";
		}
	}
}

template<typename K, typename V>
void Hash<K,V>::Remove(K const& key)
{
    int hash = (key % TABLE_SIZE);
    if (table[hash] != NULL)
	{
          HashEntry<K,V> *prevEntry = NULL;
          HashEntry<K,V> *entry = table[hash];
          while (entry->getNext() != NULL && entry->getKey() != key)
		  {
                prevEntry = entry;
                entry = entry->getNext();
          }
          if (entry->getKey() == key)
		  {
                if (prevEntry == NULL)
				{
                     HashEntry<K,V> *nextEntry = entry->getNext();
                     delete entry;
                     table[hash] = nextEntry;
                }
				
				else
				{
                     HashEntry<K,V> *next = entry->getNext();
                     delete entry;
                     prevEntry->setNext(next);
                }
          }
    }
}

template<typename K, typename V>
Hash<K,V>::~Hash()
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
	      if (table[i] != NULL)
		  {
	            HashEntry<K,V> *prevEntry = NULL;
	            HashEntry<K,V> *entry = table[i];
	            while (entry != NULL)
				{
	                 prevEntry = entry;
	                 entry = entry->getNext();
	                 delete prevEntry;
	            }
	      }
      }
          
    delete[] table;
}

template<typename K, typename V>
bool Hash<K,V>::isEmpty()
{
	return contador == 0;	
}
