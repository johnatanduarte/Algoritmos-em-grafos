#include "Lista.h" 
#include "FPHeapMinIndireto.h"
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <array>
#include <cstring>
#include <float.h>
#include <cmath> // Para o valor infinito
using namespace std;

	class Grafo {
	public:
		class Aresta {
	  private:
	    int v1, v2, peso; 
	  public: 
	    Aresta (int v1, int v2, int peso) {
	      this->v1 = v1; this->v2 = v2; this->peso = peso;
	    }
	    int _peso () { return this->peso; }
	    int _v1 () { return this->v1; }
	    int _v2 () { return this->v2; }
      bool operator<(const Aresta &p) const{
        return peso<p.peso;
      }
	    ~Aresta(){}
	  };
	private:	
		class Celula {
    friend class Grafo;
    friend ostream& operator<< (ostream& out, const Celula& celula) {
      out << "vertice:" << celula.vertice << endl;
      out << "peso:"    << celula.peso    << endl;
      return out;
    }    
		private:	
	    int vertice, peso;
	  public:
	    Celula (int v, int p) {
	    	this->vertice = v; this->peso = p;
	    }
	    Celula (const Celula& cel) { *this = cel; }      
      bool operator== (const Celula& celula) const {
        return this->vertice == celula.vertice;
      }
      bool operator!= (const Celula& celula) const {
        return this->vertice != celula.vertice;
      }
      const Celula& operator= (const Celula& cel) {     
        this->vertice = cel.vertice; this->peso = cel.peso;
        return *this; // @{\it permite atribui\c{c}\~oes encadeadas}@
      }      
      ~Celula () {}	    
	  }; 
    Lista<Celula> *adj; 
    int numVertices;
  public:
    Grafo( istream &in );
    Grafo (int numVertices);	  
    Grafo (int numVertices, int numArestas);	  
	  void insereAresta (int v1, int v2, int peso);
	  bool existeAresta (int v1, int v2) const;
	  bool listaAdjVazia (int v) const;
    Aresta *lerAresta ();
	  Aresta *primeiroListaAdj (int v);
	  Aresta *proxAdj (int v);
	  Aresta *retiraAresta (int v1, int v2);
	  void imprime () const ;
	  int _numVertices () const;
	  Grafo *grafoTransposto ();
    void visitaDfs(int u, int *cor, int *antecessor);
    void buscaProfundidade(); 
    bool ciclico(); //fazer
    int numComponentes(); //fazer
    vector<int> ordemTopologica(); //fazer
    void buscaLargura();
    void visitaBfs(int u, int *cor, int *dist, int *antecessor);
    void imprimeCaminho(int u, int v, int *antecessor);
    void kruskal();
    int* prim(int raiz);
    void dijkstra(int raiz);

    ~Grafo ();	  
	};

  Grafo::Grafo( istream &in )
  {
   int v1, v2, peso, numVertices;
   in >> numVertices;
  
   this->adj = new Lista<Celula>[numVertices]; 
   this->numVertices = numVertices; 	  	  	
   
    while (in>>v1>>v2>>peso) {
      Grafo::Aresta *a = new Grafo::Aresta (v1, v2, peso);
      this->insereAresta (a->_v1 (), a->_v2 (), a->_peso ()); 
      delete a;
    }
  }

  Grafo::Grafo (int numVertices) {
  	this->adj = new Lista<Celula>[numVertices]; 
  	this->numVertices = numVertices; 	  	
  }	  
  Grafo::Grafo (int numVertices, int numArestas) {
  	this->adj = new Lista<Celula>[numVertices]; 
  	this->numVertices = numVertices; 	  	
  }	  

  Grafo::Aresta *lerAresta () {
    cout << "Aresta:" << endl;
    cout << "  V1:"; int v1 = 0;
    cin >> v1;
    cout << "  V2:"; int v2 = 0;
    cin >> v2;
    cout << "  Peso:"; int peso = 0;
    cin >> peso;
    return new Grafo::Aresta (v1, v2, peso);
  }

  void Grafo::insereAresta (int v1, int v2, int peso) {
    Celula item (v2, peso); 
    this->adj[v1].insere (item); 
  }
  bool Grafo::existeAresta (int v1, int v2) const {
    Celula item (v2, 0);
    return (this->adj[v1].pesquisa (item) != NULL);
  }
  bool Grafo::listaAdjVazia (int v) const {
		return this->adj[v].vazia ();  
  }	  
  Grafo::Aresta *Grafo::primeiroListaAdj (int v) {
    // @{\it Retorna a primeira aresta que o v\'ertice v participa ou}@
    // @{\it {\bf NULL} se a lista de adjac\^encia de v for vazia}@ 
    Celula *item = this->adj[v]._primeiro ();    
    return item != NULL ? new Aresta(v,item->vertice,item->peso) : NULL;
  }
  Grafo::Aresta *Grafo::proxAdj (int v) {
    // @{\it Retorna a pr\'oxima aresta que o v\'ertice v participa ou}@
    // @{\it {\bf NULL} se a lista de adjac\^encia de v estiver no fim}@
    Celula *item = this->adj[v].proximo ();    
    return item != NULL ? new Aresta(v,item->vertice,item->peso) : NULL;
  }
  Grafo::Aresta *Grafo::retiraAresta (int v1, int v2) {
    Celula chave (v2, 0);
    Celula *item = this->adj[v1].retira (chave);
    Aresta *aresta = item != NULL ? new Aresta(v1,v2,item->peso) : NULL;
    delete item; return aresta;
  }
  void Grafo::imprime () const {
    for (int i = 0; i < this->numVertices; i++) { 
      cout << i << ":";
      Celula *item = this->adj[i]._primeiro ();
      while (item != NULL) {
        cout << "  " << item->vertice << " (" <<item->peso<< ")";
        item = this->adj[i].proximo ();
      }
      cout << endl;
    }
  }
  int Grafo::_numVertices () const { return this->numVertices; }
  Grafo *Grafo::grafoTransposto () {  	
    Grafo *grafoT = new Grafo (this->numVertices); 
    for (int v = 0; v < this->numVertices; v++)
      if (!this->listaAdjVazia (v)) {
        Aresta *adj = this->primeiroListaAdj (v);
        while (adj != NULL) {
          grafoT->insereAresta (adj->_v2 (), adj->_v1 (), adj->_peso ());
          delete adj;
          adj = this->proxAdj (v);
        }
      }
    return grafoT;
  } 

  void Grafo::buscaProfundidade(){
    int *cor = new int [this->_numVertices()];
    int *antecessor = new int [this->_numVertices()];

    for (int u = 0; u < this->numVertices; u++){
      cor[u]=0;
      antecessor[0]=-1;
    }
    for (int u = 0; u < this->numVertices; u++){
      if(cor[u] == 0){
        this->visitaDfs(u, cor, antecessor);
      }
    }
  }

  void Grafo::visitaDfs(int u, int *cor, int *antecessor){
    cor[u] = 1;
    cout << "cinza: " << u << endl;
    if (!this->listaAdjVazia (u)) {
        Aresta *adj = this->primeiroListaAdj (u);
        while (adj != NULL) {
          int v = adj->_v2();
          if(cor[v]==0){
            antecessor[v] = u;
            this->visitaDfs(v, cor, antecessor);
          }
          delete adj;
          adj = this->proxAdj (u);
        }
      }
    cor[u] = 2;
    cout << "preto: " << u << endl;
  }

  void Grafo::buscaLargura()
{
  int *cor = new int[this->_numVertices()];
  int *antecessor = new int[this->_numVertices()];
  int *dist = new int[this->_numVertices()];
  for (int i = 0; i < this->_numVertices(); i++)
  {
    cor[i] = 0;
    dist[i] = 1e9;
    antecessor[i] = -1;
  }
  for (int i = 0; i < this->_numVertices(); i++)
  {
    if (cor[i] == 0)
    {
      this->visitaBfs(i, cor, dist, antecessor);
    }
  }
}

  void Grafo::visitaBfs(int u, int *cor, int *dist, int *antecessor){
    queue <int> fila;

    fila.push(u);

    while (!fila.empty())
    {
      u= fila.front();
      while (!this->listaAdjVazia(u))
      {
        Aresta *adj = this->primeiroListaAdj(u);
        while (adj != NULL)
        {
          int v = adj->_v2();
          if(cor[v]==0){
            dist[v]= dist[u]+1;
            cor[v]= 1;
            antecessor[v] = u;
            fila.push(v);
            cout<< "Visitou: " << v <<endl;
          }
        }
        
        
      }
      
      
    }
    
      
  }

void Grafo::imprimeCaminho(int u, int v, int *antecessor) {
    if (u == v) {
        cout << v; // Chegamos ao vértice de destino, imprima-o
    } else if (antecessor[v] == -1) {
        cout << "Não existe caminho de " << u << " para " << v;
    } else {
        imprimeCaminho(u, antecessor[v], antecessor); // Passe o vetor antecessor
        cout << " -> " << v; // Imprime o vértice atual após o retorno da recursão
    }
}

  int encontrarConjunto(int *conjunto, int v){
    if(conjunto[v] == -1)
    return v;
    return encontrarConjunto(conjunto, conjunto[v]);
  }

  void unirConjunto(int *conjunto, int v1, int v2){
    int raizv1 = encontrarConjunto(conjunto, v1);
    int raizv2 = encontrarConjunto(conjunto, v2);
    conjunto[raizv1] = raizv2;
  }

void Grafo::kruskal() {
  vector<Aresta> S; // AGM arvore
  int *conjunto = new int[this->_numVertices()];

  memset(conjunto, -1, sizeof(int) * this->_numVertices());

  vector<Aresta> A;

  // Adicionar arestas em A
  for (int v = 0; v < this->numVertices; v++) {
    if (!this->listaAdjVazia(v)) {
      Aresta *adj = this->primeiroListaAdj(v);
      while (adj != NULL) {
        A.push_back(*adj);
        delete adj;
        adj = this->proxAdj(v);
      }
    }
  }

  // Ordenar as arestas pelo peso
  sort(A.begin(), A.end());

  int pesoTotal = 0; // Inicializa o peso total como zero

  for (int i = 0; i < A.size(); i++) {
    int v1 = A[i]._v1();
    int v2 = A[i]._v2();

    // Verificar se adicionar a aresta forma um ciclo
    if (encontrarConjunto(conjunto, v1) != encontrarConjunto(conjunto, v2)) {
      S.push_back(A[i]);
      unirConjunto(conjunto, v1, v2);
      pesoTotal += A[i]._peso(); // Adiciona o peso da aresta ao peso total
    }
  }

  // Imprimir a Árvore Geradora Mínima
  for (int i = 0; i < S.size(); i++) {
    cout << "V" << S[i]._v1() << " - V" << S[i]._v2() << " (Peso: " << S[i]._peso() << ")" << endl;
  }

  cout << "Peso minimo da AGM: " << pesoTotal << endl; // Imprime o peso mínimo

  delete[] conjunto;
}

  Grafo::~Grafo () {
    delete [] this->adj;
  }	  

  int* Grafo::prim(int raiz) {
    int n = this->_numVertices();
    int* antecessor = new int[n];
    double* peso = new double[n];
    int* vs = new int[n + 1];
    bool* itensHeap = new bool[n];

    for (int i = 0; i < n; i++) {
        peso[i] = INFINITY;
        antecessor[i] = -1;
        itensHeap[i] = true;
        vs[i + 1] = i;
    }

    peso[raiz] = 0;

    FPHeapMinIndireto Q(peso, vs, n);
    Q.constroi();

    while (!Q.vazio()) {
        int u = Q.retiraMin();
        itensHeap[u] = false;
        if (!this->listaAdjVazia(u)) {
            Aresta* adj = this->primeiroListaAdj(u);
            while (adj != NULL) {
                int v = adj->_v2();
                int pesoAresta = adj->_peso();

                if (itensHeap[v] && pesoAresta < peso[v]) {
                    antecessor[v] = u;
                    Q.diminuiChave(v, pesoAresta);
                }
                delete adj;
                adj = this->proxAdj(u); // próxima aresta de u
            }
        }
    }

    delete[] itensHeap;
    delete[] vs;

    return antecessor;
}

void Grafo::dijkstra(int raiz) {
    double* peso = new double[this->_numVertices()];
    int* antecessor = new int[this->_numVertices()];
    int* vs = new int[this->_numVertices() + 1];
    bool* processado = new bool[this->_numVertices()];

    for (int v = 0; v < this->numVertices; v++) {
        peso[v] = DBL_MAX; // Inicializa o peso como infinito
        antecessor[v] = -1; // Inicializa o antecessor como indefinido
        vs[v + 1] = v;
        processado[v] = false; // Inicializa o vetor de processamento como falso
    }

    peso[raiz] = 0;

    FPHeapMinIndireto heap(peso, vs, this->_numVertices());
    heap.constroi();

    while (!heap.vazio()) {
        int u = heap.retiraMin();
        processado[u] = true;

        if (!this->listaAdjVazia(u)) {
            Aresta* adj = this->primeiroListaAdj(u);
            while (adj != NULL) {
                int v = adj->_v2();
                double peso_uv = adj->_peso();

                if (!processado[v] && peso[u] + peso_uv < peso[v]) {
                    peso[v] = peso[u] + peso_uv;
                    antecessor[v] = u;
                    heap.diminuiChave(v, peso[v]);
                }

                delete adj;
                adj = this->proxAdj(u); // Próxima aresta de u
            }
        }
    }

    // Imprime os resultados do algoritmo de Dijkstra
    for (int v = 0; v < this->_numVertices(); v++) {
        cout << "Menor caminho do vertice " << raiz << " para o vertice " << v << ": ";
        if (antecessor[v] != -1) {
            // Reconstrói o caminho a partir do vetor "antecessor"
            vector<int> caminho;
            int u = v;
            while (u != -1) {
                caminho.push_back(u);
                u = antecessor[u];
            }

            // Imprime o caminho na ordem correta (do vértice raiz ao vértice v)
            for (int i = caminho.size() - 1; i >= 0; i--) {
                cout << caminho[i];
                if (i > 0) {
                    cout << " -> ";
                }
            }

            cout << ", Peso: " << peso[v];
        } else {
            cout << "Nao existe caminho.";
        }
        cout << endl;
    }

    delete[] peso;
    delete[] antecessor;
    delete[] vs;
    delete[] processado;
}

