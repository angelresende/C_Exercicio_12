#include<iostream>
#include<locale.h>
#include<stdlib.h>
using namespace std;

struct Dados {
	string nome;
};

struct No {
	No* antNo;
	Dados dados;
	No* proxNo;
};

struct Lista {
	No* inicio;
};

//--------------------------------------------------------
// DECLARAÇÃO DE FUNÇÕES
//--------------------------------------------------------

//CRIAÇÃO, EXCLUSÃO e EXIBIÇÃO
Lista* criarLista();
void liberarLista(Lista* ptrLista);
void exibirLista(Lista* ptrLista);

//INSERÇÕES
bool inserirListaOrdenada(Lista* ptrLista, string nome);

//********************************************************
// FUNÇÃO MAIN
//********************************************************
int main() {
	setlocale(LC_ALL, "portuguese");
	Lista* pLista;
	pLista = criarLista();


	//--------- INSERIR ORDENADO DA LISTA ------------
	cout << "---- INSERINDO LISTA POR ORDEM ALFABETICA ----" << endl;
	inserirListaOrdenada(pLista, "\t\tMatheus");
	inserirListaOrdenada(pLista, "\t\tMaria") ;
	inserirListaOrdenada(pLista, "\t\tAndressa");
	inserirListaOrdenada(pLista, "\t\tFernando");
	inserirListaOrdenada(pLista, "\t\tFernanda");

	exibirLista(pLista);
    liberarLista(pLista);

	system("pause");
	system("cls");

    return 0;
}

//--------------------------------------------------------
// CRIAR LISTA
//--------------------------------------------------------
Lista* criarLista() {
	Lista* ptrLista;

	ptrLista = new Lista;

	if (ptrLista == NULL) {
		cout << "Não foi possivel criar a lista..." << endl;
		return NULL;

	}

	ptrLista->inicio = NULL;

	return ptrLista;
}

//--------------------------------------------------------
// INSERIR EM LISTA ORDENADA
//--------------------------------------------------------
bool inserirListaOrdenada(Lista* ptrLista, string nome) {
	No* ptrNoNovo;
	No* ptrNoAnterior;
	No* ptrNoAtual;

	//---------------------------------------------------------------
	//	Cria o novo nó
	//---------------------------------------------------------------
	ptrNoNovo = new No;

	if (ptrNoNovo == NULL) {
		cout << "Memória insulficiente!" << endl;
		return false;
	}

	ptrNoNovo->dados.nome = nome;

	ptrNoNovo->antNo = NULL;
	ptrNoNovo->proxNo = NULL;

	//Se a lista estiver vazia
	if (ptrLista->inicio == NULL) {
		ptrLista->inicio = ptrNoNovo;
	}
	else
	{
		ptrNoAnterior = NULL;
		ptrNoAtual = ptrLista->inicio;

		// Localiza a posição de inserção
		while (ptrNoAtual != NULL && ptrNoAtual->dados.nome < nome) {
			ptrNoAnterior = ptrNoAtual;
			ptrNoAtual = ptrNoAtual->proxNo;
		}

		// Insere no INÍCIO da lista
		if (ptrNoAtual == ptrLista->inicio) {
			ptrNoNovo->proxNo = ptrLista->inicio;
			ptrLista->inicio->antNo = ptrNoNovo;
			ptrLista->inicio = ptrNoNovo;
		}
		else { // Insere no MEIO ou FIM da lista

			ptrNoNovo->proxNo = ptrNoAtual;
			ptrNoNovo->antNo = ptrNoAnterior;

			ptrNoAnterior->proxNo = ptrNoNovo;

			// Se for o meio da lista
			if (ptrNoAtual != NULL) {
				ptrNoAtual->antNo = ptrNoNovo;
			}
		}
	}
	return true;
}

//--------------------------------------------------------
// EXIBIR A LISTA
//--------------------------------------------------------
void exibirLista(Lista* ptrLista) {
	No* ptrNoAtual;

	//Se a lista NÃO foi criada
	if (ptrLista == NULL) {
		cout << "A lista não está criada!" << endl;
		return;
	}


	//Se não tiver nenhum Nó na lista
	if (ptrLista->inicio == NULL) {
		cout << "A lista esta vazia!" << endl;
		return;
	}

	ptrNoAtual = ptrLista->inicio;
	
	while (ptrNoAtual != NULL) {
		cout << ptrNoAtual->dados.nome << endl;
		ptrNoAtual = ptrNoAtual->proxNo;
	}
}

////--------------------------------------------------------
//// LIBERAR LISTA
////--------------------------------------------------------
void liberarLista(Lista* ptrLista) {
	No* ptrNoAtual;

	//Se a lista NÃO foi criada
	if (ptrLista == NULL) {
		cout << "A lista não está criada!" << endl;
		return;
	}

	// Exclui cada Nó da lista
	while (ptrLista->inicio != NULL)
	{
		ptrNoAtual = ptrLista->inicio;

		ptrLista->inicio = ptrLista->inicio->proxNo;

		delete  ptrNoAtual;
	}

	delete ptrLista;
}