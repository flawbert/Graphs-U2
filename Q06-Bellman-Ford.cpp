#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <string>
#include <sstream>

// Estrutura para representar uma aresta ponderada no grafo
struct Aresta {
    int origem, destino, peso;
};

// Executa o algoritmo de Bellman-Ford para encontrar o caminho mais curto em um grafo ponderado
// Retorna falso se um ciclo de peso negativo for detectado, caso contrário retorna verdadeiro
bool bellmanFord(int numVertices, const std::vector<Aresta>& listaDeArestas, int s, 
                 std::vector<int>& distancia, std::vector<int>& predecessor) 
{
    // s.distância = 0;
    distancia[s] = 0;
    // Para i = 1 até |V| - 1 faça
    for (int i = 1; i <= numVertices - 1; ++i) {
        // Para toda aresta (u, v) faça
        for (const auto& aresta : listaDeArestas) {
            int u = aresta.origem;
            int v = aresta.destino;
            int peso = aresta.peso;
            // Se v.distância > u.distância + w(uv) então
            if (distancia[u] != INT_MAX && distancia[v] > distancia[u] + peso) {
                // v.distância = u.distância + w(uv)
                distancia[v] = distancia[u] + peso;
                // v.predecessor = u;
                predecessor[v] = u;
            }
        }
    }
    // Detecta os ciclos negativos, caso existam
    // Para toda aresta (u, v) faça
    for (const auto& aresta : listaDeArestas) {
        int u = aresta.origem;
        int v = aresta.destino;
        int peso = aresta.peso;
        // Se v.distância > u.distância + w(uv) então
        if (distancia[u] != INT_MAX && distancia[v] > distancia[u] + peso) {
            // Retorne falso
            return false; 
        }
    }
    // Retorne verdadeiro
    return true;
}

// Imprime o caminho formatado ("1 -> 2 -> 3") do vértice 'origem' ao vértice 'destino'
void imprimirCaminho(const std::vector<int>& predecessor, int origem, int destino) {
    if (destino == -1) {
        std::cout << "Nenhum caminho encontrado." << std::endl;
        return;
    }

    std::vector<int> caminho;
    int atual = destino;

    while (atual != -1) {
        caminho.push_back(atual);
        if (atual == origem) break;
        atual = predecessor[atual];
    }

    if (caminho.empty() || caminho.back() != origem) {
        std::cout << "Nenhum caminho" << std::endl;
        return;
    }

    std::reverse(caminho.begin(), caminho.end());

    for (size_t i = 0; i < caminho.size(); ++i) {
        std::cout << caminho[i];
        if (i < caminho.size() - 1) {
            std::cout << " -> ";
        }
    }
    std::cout << std::endl; 
}

int main() {
    int origem = 1;
    int destino = 15;
    int V = 19;

    std::vector<int> predecessor(V + 1, -1);
    std::vector<int> distancia(V + 1, INT_MAX);

    std::vector<Aresta> arestas = {
        {1, 6, 3}, {1, 11, 1},
        {2, 1, 2}, {2, 6, 7}, {2, 3, 8},
        {3, 2, 1}, {3, 4, 2}, {3, 8, 10},
        {4, 9, 9}, {4, 10, 7}, {4, 13, 15},
        {5, 4, 4},
        {6, 3, 9}, {6, 7, 2},
        {7, 8, 8}, {7, 12, 1},
        {8, 9, 7},
        {9, 3, 2}, {9, 14, 1},
        {10, 5, 5}, {10, 14, 6}, {10, 15, 9},
        {11, 6, 0}, {11, 16, 2},
        {12, 11, 4}, {12, 17, 1},
        {13, 7, 5}, {13, 18, 4},
        {14, 15, 1}, {14, 19, 18},
        {16, 12, 3},
        {17, 12, 1}, {17, 19, 5},
        {18, 9, 2}, {18, 17, 20}
    };

    bool CicloNegativo = bellmanFord(V, arestas, origem, distancia, predecessor);

    std::cout << "QUESTAO 06 - Algoritmo de Bellman-Ford" << std::endl;
    if (!CicloNegativo) {
        std::cout << "O grafo contem um ciclo de peso negativo!" << std::endl;
    } else {
        std::cout << "Distancia do vertice " << origem << " ao vertice " << destino << " e: ";
        if (distancia[destino] == INT_MAX) {
            std::cout << "INF" << std::endl;
        } else {
            std::cout << distancia[destino] << std::endl;
        }
        std::cout << "Caminho: ";
        imprimirCaminho(predecessor, origem, destino);
    }

    return 0;
}