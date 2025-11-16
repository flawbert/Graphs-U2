 //Algoritmo de Hierholzer para caminho Euleriano em grafos não-direcionados
#include <iostream>
#include <map>
#include <set> // multiset será usado para armazenar arestas
#include <list>
#include <stack>
#include <vector>
#include <algorithm> // Para std::reverse e std::find

// Estrutura para representar o grafo não-direcionado
struct Grafo {
    // Usamos 'multiset' para que tenha uma remoção eficiente (O(logN)) de uma aresta específica
    std::map<int, std::multiset<int>> adj;
    std::map<int, int> degree; //esse mapa verifica a condição do caminho euleriano
    
    std::vector<int> nodes;//listas de todos vértices
    int vComecoPadrao = -1;

    /**
     * @brief Adiciona uma aresta não-direcionada (u - v) ao grafo.
     * @param u Vértice 1.
     * @param v Vértice 2.
     */
    void addEdge(int u, int v) {
        adj[u].insert(v);
        adj[v].insert(u);
        
        degree[u]++;
        degree[v]++;
        
        //Define o primeiro nó adicionado como padrão
        if (vComecoPadrao == -1) vComecoPadrao = u;

        if (std::find(nodes.begin(), nodes.end(), u) == nodes.end()) nodes.push_back(u);
        if (std::find(nodes.begin(), nodes.end(), v) == nodes.end()) nodes.push_back(v);
    }

    /**
     * @brief Encontra o nó inicial para o caminho Euleriano.
     * @desc Um grafo não-direcionado conectado tem um caminho euleriano
     * se tiver 0 ou 2 vértices de grau ímpar.
     * @return O nó inicial, ou -1 se não houver caminho.
     */
    int encontraVerticeInicial() {
        int verticeGrauImpar = 0;
        int verticeInicial = vComecoPadrao; //começa no primeiro nó adicionado (se for ciclo)
        for (int node : nodes) {
            if (degree[node] % 2 != 0) {
                verticeGrauImpar++;
                verticeInicial = node; //Se for caminho, este será o início
            }
        }
        std::cout << "Vértices com grau ímpar: " << verticeGrauImpar << std::endl;

        if (verticeGrauImpar == 0) {
            std::cout << "É um ciclo Euleriano. Começando no vértice " << verticeInicial << std::endl;
            return verticeInicial;
        } else if (verticeGrauImpar == 2) {
            std::cout << "É um caminho Euleriano. Começando no vértice " << verticeInicial << std::endl;
            return verticeInicial;
        } else {
            std::cout << "Não é um caminho nem ciclo Euleriano (possui " << verticeGrauImpar << " vértices de grau ímpar)." << std::endl;
            return -1; // Não possui caminho/ciclo
        }
    }
};

/**
 * @brief Implementação principal do Algoritmo de Hierholzer (Iterativo).
 * @desc Encontra e imprime um caminho Euleriano em um grafo não-direcionado.
 * @param g O grafo a ser processado.
 * @saida Esperada: Imprime a sequência de vértices que formam o caminho euleriano.
 */
void encontrarCaminhoEuleriano(Grafo& g) {
    // 1. Encontra o nó inicial
    int verticeInicial = g.encontraVerticeInicial();
    if (verticeInicial == -1) {
        return;
    }

    std::stack<int> s;
    std::list<int> path;
    s.push(verticeInicial);
    while (!s.empty()) {
        int u = s.top();
        if (!g.adj[u].empty()) {
            int v = *g.adj[u].begin();
            
            // Remove (u, v)
            g.adj[u].erase(g.adj[u].begin());
            // Remove (v, u)
            // find(u) retorna um iterador, que erase() usa para remover
            g.adj[v].erase(g.adj[v].find(u));
            s.push(v);
        }
        else {
            path.push_back(u);
            s.pop();
        }
    }
    std::reverse(path.begin(), path.end());

    std::cout << "\n|*****Algoritmo de Hierholzer (Caminhos)*****|" << std::endl;
    std::cout << "Caminho Euleriano encontrado:" << std::endl;
    for (int node : path) {
        std::cout << node << " -> ";
    }
}
int main() {
    Grafo g;
    int numArestas;
    std::cout << "|***** Algoritmo de Hierholzer (Caminhos) *****|" << std::endl;
    std::cout << "Digite o numero de arestas nao-direcionadas: ";
    std::cin >> numArestas;

    std::cout << "Digite as " << numArestas << " arestas (formato: vertice1 vertice2):" << std::endl;
    for (int i = 0; i < numArestas; ++i) {
        int u, v;
        std::cin >> u >> v;
        g.addEdge(u, v);
    }
    
    encontrarCaminhoEuleriano(g);

    return 0;
}