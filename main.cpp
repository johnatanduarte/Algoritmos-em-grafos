#include "matrizadj/Grafo.h" 
#include <fstream>
using namespace std;

int main (int argc, char **argv) 
{
    ifstream in ("exemplo6.txt");
    Grafo *grafo = new Grafo (in);
    //grafo->kruskal();
    //grafo->dijkstra(2);
    grafo->FloydWarshall(2, 1);
    //grafo->imprime();
    delete grafo;
    //grafo->imprime ();  

    //grafo->buscaProfundidade();
    //grafo->buscaLargura();

    //Ex1: criar e imprimir grafo transposto.
    //Grafo *grafoT = grafo->grafoTransposto();
    //grafoT->imprime();

    //Ex2: Criar e imprimir um grafo não orientado.
    //Grafo *grafoND = grafo->grafoNaoDirecionado();
    //grafoND->imprime();
    
    //Ex3: Ler e inserir nova aresta, verificando se ela já existe.
    /*Grafo::Aresta *a = grafo->lerAresta();
    if(grafo->existeAresta(a->_v1(), a->_v2()))
        grafo->insereAresta(a->_v1(), a->_v2(), a->_peso());
    else cout << "Aresta ja existe!";
    grafo->imprime(); */

    //Ex4: Ler e remover uma aresta, verificando se ela já existe.
    /*Grafo::Aresta *a = grafo->lerAresta();
    if(grafo->existeAresta(a->_v1(), a->_v2()))
        grafo->retiraAresta(a->_v1(), a->_v2());
    else cout << "Aresta ja existe!";
    grafo->imprime(); */

    //Ex5: Imprimir uma lista adjacente de um determinado vértices.
    //grafo->listaAdj(3);

    //grauVertice
    //cout << grafo->grauVertice(3) ;

    //Grafo 
    /*
    if(grafo->completo()){ cout << "Completo" << endl;}
    if(grafo->regular()){ cout << "Regular" << endl;}
    if(grafo->euleriano()) {cout << "Euleriano" << endl;}
    if(grafo->subeuleriano()) {cout << "SubEuleriano" << endl;}
    */
    //grafo->buscaLargura();
    

}
