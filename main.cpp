#include "listaadj/Grafo.h" 
#include <fstream>
using namespace std;

int main (int argc, char **argv) 
{
    ifstream in ("dfs_input.txt");
    Grafo *grafo = new Grafo (in);
    
    //grafo->kruskal();
    //grafo->dijkstra(2);
    //grafo->FloydWarshall(2, 1);
    //int resultado = grafo->emparelhamentoMaximo();
    //std::cout << "Maior numero de atividades simultaneas: " << resultado << std::endl;
    //int raiz = 0;

                //grafo->buscaEmLargura();
                //grafo->buscaMenorCaminho(7, 1);
    grafo->buscaProfundidade();
    
    // Verificar se o grafo possui ciclo
     bool possuiCiclo = grafo->aciclico();
    if (possuiCiclo) {
        cout << "O grafo possui ciclo." << endl;
    } else {
        cout << "O grafo nao possui ciclo." << endl;
    }

    // Realizar ordenação topológica
    vector<int> ordemTopologica = grafo->ordemTopologica();
    cout << "Ordenacao Topologica: ";
    for (int i = 0; i < ordemTopologica.size(); i++) {
        cout << ordemTopologica[i] << " ";
    }
    cout << endl;

    // Verificar o número de componentes
    int numComponentes = grafo->numComponentes();
    cout << "Numero de componentes: " << numComponentes << endl;  



    //Chame a função Prim
    //Grafo::PrimResult resultadoPrim = grafo->prim(raiz);
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
