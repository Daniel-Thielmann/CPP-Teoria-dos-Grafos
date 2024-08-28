#include <iostream>
#include "Graph.hpp"
#include "Graph.cpp"
#include "Node.cpp"
#include "Node.hpp"
#include "Edge.cpp"
#include "Edge.hpp"

using namespace std;

void showMenu()
{
    cout << "Escolha uma opção:" << endl;
    cout << "1. Carregar grafo de arquivo" << endl;
    cout << "2. Mostrar grafo" << endl;
    cout << "3. Caminho mínimo (Dijkstra)" << endl;
    cout << "4. Caminho mínimo (Floyd-Warshall)" << endl;
    cout << "5. Raio do grafo" << endl;
    cout << "6. Diâmetro do grafo" << endl;
    cout << "7. Centro do grafo" << endl;
    cout << "8. Periferia do grafo" << endl;
    cout << "9. Pontos de articulação" << endl;
    cout << "10. Sair" << endl;
}

int main()
{
    bool directed, weightedEdge, weightedNode;

    cout << "É um grafo direcionado? (1 para Sim, 0 para Não): ";
    cin >> directed;

    cout << "As arestas são ponderadas? (1 para Sim, 0 para Não): ";
    cin >> weightedEdge;

    cout << "Os nós são ponderados? (1 para Sim, 0 para Não): ";
    cin >> weightedNode;

    Graph graph(directed, weightedEdge, weightedNode);

    int option;
    do
    {
        showMenu();
        cout << "Opção: ";
        cin >> option;

        switch (option)
        {
        case 1:
        {
            string filename;
            cout << "Digite o nome do arquivo: ";
            cin >> filename;
            if (graph.loadFromFile(filename)) {
                cout << "Grafo carregado com sucesso." << endl;
            } else {
                cout << "Erro ao carregar o grafo." << endl;
            }
            break;
        }
        case 2:
            graph.printGraph();
            break;
        case 3:
            cout << "Dijkstra não implementado." << endl;
            break;
        case 4:
        {
            size_t startNode, endNode;
            cout << "Digite o nó inicial: ";
            cin >> startNode;
            cout << "Digite o nó final: ";
            cin >> endNode;
            vector<size_t> path = graph.shortestPathFloyd(startNode, endNode);
            cout << "Caminho: ";
            for (size_t node : path) {
                cout << node << " ";
            }
            cout << endl;
            break;
        }
        case 5:
            cout << "Raio do grafo: " << graph.getGraphRadius() << endl;
            break;
        case 6:
            cout << "Diâmetro do grafo: " << graph.getGraphDiameter() << endl;
            break;
        case 7:
        {
            vector<size_t> center = graph.getGraphCenter();
            cout << "Centro do grafo: ";
            for (size_t node : center) {
                cout << node << " ";
            }
            cout << endl;
            break;
        }
        case 8:
        {
            vector<size_t> periphery = graph.getGraphPeripheral();
            cout << "Periferia do grafo: ";
            for (size_t node : periphery) {
                cout << node << " ";
            }
            cout << endl;
            break;
        }
        case 9:
        {
            vector<size_t> articulationPoints = graph.getArticulationPoints();
            cout << "Pontos de articulação: ";
            for (size_t node : articulationPoints) {
                cout << node << " ";
            }
            cout << endl;
            break;
        }
        case 10:
            cout << "Saindo..." << endl;
            break;
        default:
            cout << "Opção inválida. Tente novamente." << endl;
        }

    } while (option != 10);

    return 0;
}