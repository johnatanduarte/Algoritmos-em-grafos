#include <iostream>     //linha 156 ate linha 164 vou usar bastante 
#include <vector>
#include <queue>      
#include <algorithm>
#include <array>
#include <cstring>
#include <float.h>
#include <climits> 
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
	    ~Aresta () {}
	  };
	private:
	  int **mat; // @{\it pesos do tipo inteiro}@
    int numVertices;
    int *pos; // @{\it posi\c{c}\~ao atual ao se percorrer os adjs de um v\'ertice v}@

  public:
    Grafo (int numVertices);
    Grafo(istream &in);
    Grafo(int numVertices, int numArestas);
    void insereAresta(int v1, int v2, int peso);
    bool existeAresta(int v1, int v2) const;
    bool listaAdjVazia(int v) const;
    Aresta *lerAresta();
    Aresta *primeiroListaAdj(int v);
    Aresta *proxAdj(int v);
    Aresta *retiraAresta(int v1, int v2);
    void imprime() const;
    int _numVertices() const;
    Grafo *grafoTransposto();
    Grafo *grafoNaoDirecionado();
    void listaAdj(int v);
    int grauVertice(int v);
    bool completo();
    bool regular();
    bool euleriano();
    bool subeuleriano();
    void FloydWarshall(int verticeOrigem, int verticeDestino);
    int maiorNumeroAtividadesSimultaneas();
    int emparelhamentoMaximo();
    bool buscaAumentante();
    bool augmentingPath(int u, bool visitado[], int matchTrabalhador[], int matchAtividade[]);
    ~Grafo ();	  
	};

  Grafo::Grafo( istream &in )
  {
   int v1, v2, peso;
   in >> this->numVertices;
   this->mat = new int*[numVertices];
    for (int i = 0; i < numVertices; i++) 
      this->mat[i] = new int[numVertices];
    this->pos = new int[numVertices]; 
    
    for (int i = 0; i < this->numVertices; i++) {
      for (int j = 0; j < this->numVertices; j++) this->mat[i][j] = 0;
      this->pos[i] = -1; 
    }
    while (in>>v1>>v2>>peso) {
      Grafo::Aresta *a = new Grafo::Aresta (v1, v2, peso);
      this->insereAresta (a->_v1 (), a->_v2 (), a->_peso ()); 
      delete a;
    }
  }

  Grafo::Grafo (int numVertices) {
    this->mat = new int*[numVertices];
    for (int i = 0; i < numVertices; i++) 
      this->mat[i] = new int[numVertices];
    this->pos = new int[numVertices]; 
    this->numVertices = numVertices; 
    for (int i = 0; i < this->numVertices; i++) {
      for (int j = 0; j < this->numVertices; j++) this->mat[i][j] = 0;
      this->pos[i] = -1; 
    }
  }	  
  
  Grafo::Grafo (int numVertices, int numArestas) {
    this->mat = new int*[numVertices];
    for (int i = 0; i < numVertices; i++) 
      this->mat[i] = new int[numVertices];
    this->pos = new int[numVertices]; 
    this->numVertices = numVertices; 
    for (int i = 0; i < this->numVertices; i++) {
      for (int j = 0; j < this->numVertices; j++) this->mat[i][j] = 0;
      this->pos[i] = -1; 
    }
  }	  

  void Grafo::insereAresta (int v1, int v2, int peso) {
    this->mat[v1][v2] = peso; 
  }
  bool Grafo::existeAresta (int v1, int v2) const {
    return (this->mat[v1][v2] > 0);
  }
  bool Grafo::listaAdjVazia (int v) const {
    for (int i = 0; i < this->numVertices; i++)
      if (this->mat[v][i] > 0) return false;
    return true;
  }

  Grafo::Aresta *Grafo::lerAresta()
  {
    cout << "Aresta:" << endl;
    cout << "  V1:"; int v1 = 0;
    cin >> v1;
    cout << "  V2:"; int v2 = 0;
    cin >> v2;
    cout << "  Peso:"; int peso = 0;
    cin >> peso;
    return new Aresta (v1, v2, peso);
  }

  Grafo::Aresta *Grafo::primeiroListaAdj (int v) {
    // @{\it Retorna a primeira aresta que o v\'ertice v participa ou}@ 
    // @{\it {\bf NULL} se a lista de adjac\^encia de v for vazia}@
    this->pos[v] = -1; return this->proxAdj (v);
  }
  
  Grafo::Aresta *Grafo::proxAdj (int v) {
    // @{\it Retorna a pr\'oxima aresta que o v\'ertice v participa ou}@ 
    // @{\it {\bf NULL} se a lista de adjac\^encia de v estiver no fim}@ 
    this->pos[v] ++;
    while ((this->pos[v] < this->numVertices) && 
           (this->mat[v][this->pos[v]] == 0)) this->pos[v]++;
    if (this->pos[v] == this->numVertices) return NULL;
    else return new Aresta (v, this->pos[v], this->mat[v][this->pos[v]]);
  }
  
  Grafo::Aresta *Grafo::retiraAresta (int v1, int v2) {
    if (this->mat[v1][v2] == 0) return NULL; // @{\it Aresta n\~ao existe}@
    else {
      Aresta *aresta = new Aresta (v1, v2, this->mat[v1][v2]);
      this->mat[v1][v2] = 0; return aresta;
    }
  }
  
  void Grafo::imprime () const {
    cout << "   ";
    for (int i = 0; i < this->numVertices; i++) 
      cout << i << "   "; 
    cout << endl;
    for (int i = 0; i < this->numVertices; i++) { 
      cout << i <<  "  ";
      for (int j = 0; j < this->numVertices; j++)
        cout << this->mat[i][j] << "   ";
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

  Grafo *Grafo::grafoNaoDirecionado () {
    Grafo *grafoND = new Grafo (this->numVertices); 
    //Ex5: Implementar o grafo não direcionado
    for (int v = 0; v < this->numVertices; v++)
      if (!this->listaAdjVazia (v)) {
        Aresta *adj = this->primeiroListaAdj (v);
        while (adj != NULL) {
          grafoND->insereAresta (adj->_v2 (), adj->_v1 (), adj->_peso ());
          grafoND->insereAresta (adj->_v1 (), adj->_v2 (), adj->_peso ());
          delete adj;
          adj = this->proxAdj (v);
        }
      }
    return grafoND;
  }

  void Grafo::listaAdj(int V){
      for (int j = 0; j < this->numVertices; j++){
      if(this->mat[V][j]>0)
      cout << j << " ";
      }
  }

  int Grafo::grauVertice(int V){
      int g=0;
      for (int j = 0; j < this->numVertices; j++){
        if(this->existeAresta(V,j)){
          g++;
        }
      }
      return g;
  }

  bool Grafo::completo(){
    for(int i = 0; i < this->numVertices; i++){
      if(this->grauVertice(i)<this->numVertices-1)
      return false;
    } 
    return true;
  } 

  bool Grafo::regular(){
    for(int i = 1; i < this->numVertices-1; i++){
      if(this->grauVertice(i) != this->grauVertice(0)){
        return 0;
      }
    }
    return 1;
  }

  bool Grafo::euleriano(){
    int cont = 0;
    for(int i = 0; i < this->numVertices-1; i++){
      if(this->grauVertice(i) != this->numVertices-1){
        return false;
      }
    }
    return true;
  }

  bool Grafo::subeuleriano(){
    int cont = 0;
    for(int i = 0; i < this->numVertices-1; i++){
      if(this->grauVertice(i)% 2 != 0){
        cont++;
      }
    }
    if(cont == 2){
      return true;
    }
      else return false;
  }

 void Grafo::FloydWarshall(int verticeOrigem, int verticeDestino) {
    int **d, **antecessor;
    d = new int*[this->_numVertices()];
    antecessor = new int*[this->_numVertices()];

    for(int i = 0; i < this->_numVertices(); i++) {
        d[i] = new int[this->_numVertices()];
        antecessor[i] = new int[this->_numVertices()];
    }

    for (int i = 0; i < this->_numVertices(); i++) {
        for (int j = 0; j < this->_numVertices(); j++) {
            if (this->existeAresta(i, j)) {
                d[i][j] = this->mat[i][j];
                antecessor[i][j] = i;
            } else {
                if(i == j) {
                    d[i][j] = 0;
                } else {
                    d[i][j] = INT_MAX;
                }
                antecessor[i][j] = -1;
            }
        }
    }

    for (int k = 0; k < this->_numVertices(); k++) {
        for (int i = 0; i < this->_numVertices(); i++) {
            for (int j = 0; j < this->_numVertices(); j++) {
                if(d[i][k] == INT_MAX || d[k][j] == INT_MAX) 
                    continue;
                if (d[i][k] + d[k][j] < d[i][j]) {
                    d[i][j] = d[i][k] + d[k][j];
                    antecessor[i][j] = antecessor[k][j];
                }
            }
        }
    }

    // Print da distancia da matrix
    cout << "Distancia matrix:" << endl;
    for (int i = 0; i < this->_numVertices(); i++) {
        for (int j = 0; j < this->_numVertices(); j++) {
            cout << d[i][j] << " ";
        }
        cout << endl;
    }

    // Print do predecessor da matrix
    cout << "Predecessor matrix:" << endl;
    for (int i = 0; i < this->_numVertices(); i++) {
        for (int j = 0; j < this->_numVertices(); j++) {
            cout << antecessor[i][j] << " ";
        }
        cout << endl;
    }

    // Mostrar a menor distância entre os vértices fornecidos
    cout << "Menor distancia entre " << verticeOrigem << " e " << verticeDestino << ": " << d[verticeOrigem][verticeDestino] << endl;
}

  Grafo::~Grafo()
  {
    for (int i = 0; i < numVertices; i++) 
      delete [] this->mat[i];
    delete [] this->mat;
    delete [] this->pos;
  }

int Grafo::emparelhamentoMaximo() {
    int* matchTrabalhador = new int[numVertices];
    int* matchAtividade = new int[numVertices];
    memset(matchTrabalhador, -1, sizeof(int) * numVertices);
    memset(matchAtividade, -1, sizeof(int) * numVertices);

    int resultado = 0;

    for (int i = 0; i < numVertices; i++) {
        if (matchTrabalhador[i] == -1) {
            bool visitado[numVertices];
            memset(visitado, false, sizeof(visitado));

            if (augmentingPath(i, visitado, matchTrabalhador, matchAtividade)) {
                resultado++;
            }
        }
    }

    delete[] matchTrabalhador;
    delete[] matchAtividade;

    return resultado;
}

bool Grafo::augmentingPath(int u, bool visitado[], int matchTrabalhador[], int matchAtividade[]) {
    for (int v = 0; v < numVertices; v++) {
        if (mat[u][v] && !visitado[v]) {
            visitado[v] = true;

            if (matchAtividade[v] == -1 || augmentingPath(matchAtividade[v], visitado, matchTrabalhador, matchAtividade)) {
                matchTrabalhador[u] = v;
                matchAtividade[v] = u;
                return true;
            }
        }
    }

    return false;
}


		
