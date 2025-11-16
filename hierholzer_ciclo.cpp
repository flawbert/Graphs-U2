// Algoritmo de Hierholzer para encontrar ciclo Euleriano em grafos dígrafos
#include <iostream>
#include <map>
#include <list>
#include <stack>
#include <vector>
#include <algorithm> // Para std::reverse e std::find

// Estrutura para representar o grafo dígrafo
struct Digrafo {
    // Lista de adjacência.
    std::map<int, std::list<int>> adj;
    // Mapas para verificar a condição do ciclo Euleriano
    std::map<int, int> grauEntrada;
    std::map<int, int> grauSaida;
    
    std::vector<int> vertices; // listas de todos vértices
    /**
     * @brief Adiciona uma aresta direcionada (u -> v) ao grafo.
     * @param u Vértice de origem.
     * @param v Vértice de destino.
     */
    void adcAresta(int u, int v) {
        adj[u].push_back(v);
        
        grauSaida[u]++;
        grauEntrada[v]++;
        // Garante que ambos os nós existam nos mapas de grau
        if (grauSaida.find(v) == grauSaida.end()) grauSaida[v] = 0;
        if (grauEntrada.find(u) == grauEntrada.end()) grauEntrada[u] = 0;
        // Adiciona nós à lista (se ainda não estiverem)
        if (std::find(vertices.begin(), vertices.end(), u) == vertices.end()) vertices.push_back(u);
        if (std::find(vertices.begin(), vertices.end(), v) == vertices.end()) vertices.push_back(v);
    }
    /**
     * @brief Verifica se o grafo possui um Ciclo Euleriano.
     * @desc Um dígrafo conectado possui um ciclo euleriano se e somente se
     * grau_de_entrada(v) == grau_de_saida(v) para todo vértice 'v'.
     * @return true se a condição for satisfeita, false se não.
     */
    bool temCicloEuleriano() {
        for (int vertice : vertices) {
            if (grauEntrada[vertice] != grauSaida[vertice]) {
                std::cout << "Condição para Ciclo Euleriano FALHOU." << std::endl;
                std::cout << "Vértice " << vertice << ": Grau_de_entrada(" << grauEntrada[vertice]
                          << ") != Grau_de_saída(" << grauSaida[vertice] << ")" << std::endl;
                return false;
            }
        }
        std::cout << "Condição de grau (Entrada == Saída) satisfeita para todos os vértices." << std::endl;
        return true;
    }
};
/**
 * @brief Implementação principal do Algoritmo de Hierholzer (Iterativo).
 * @desc Encontra e imprime um Ciclo Euleriano em um dígrafo.
 * @param g O dígrafo a ser processado.
 * @param verticeInicio O vértice inicial do ciclo.
 * @saida Esperada: Imprime a sequência de vértices que formam o ciclo euleriano.
 */
void encontraCicloEuleriano(Digrafo& g, int verticeInicio) {
    if (!g.temCicloEuleriano()) {
        std::cout << "O grafo não possui um Ciclo Euleriano." << std::endl;
        return;
    }
    // Verifica se o nó inicial existe
    if (g.adj.find(verticeInicio) == g.adj.end() && g.grauEntrada.find(verticeInicio) == g.grauEntrada.end()) {
        std::cout << "O vértice inicial " << verticeInicio << " não existe no grafo." << std::endl;
        return;
    }
    std::stack<int> s;
    std::list<int> cycle;

    s.push(verticeInicio);

    while (!s.empty()) {
        int u = s.top();
        if (!g.adj[u].empty()) {
            int v = g.adj[u].front();
            g.adj[u].pop_front();
            s.push(v);
        }
        else {
            cycle.push_back(u);
            s.pop();
        }
    }
    std::reverse(cycle.begin(), cycle.end());
    std::cout << "\n|***** Algoritmo de Hierholzer (Ciclos) *****|" << std::endl;
    std::cout << "Ciclo Euleriano encontrado:" << std::endl;
    for (int vertice : cycle) {
        std::cout << vertice << " -> ";
    }
}

int main() {
    Digrafo g;
    int numEdges;
    int verticeInicio;

    std::cout << "|***** Algoritmo de Hierholzer (Ciclos) *****|" << std::endl;
    std::cout << "Digite o numero de arestas direcionadas: ";
    std::cin >> numEdges;

    std::cout << "Digite as " << numEdges << " arestas (formato: origem destino):" << std::endl;
    for (int i = 0; i < numEdges; ++i) {
        int u, v;
        std::cin >> u >> v;
        g.adcAresta(u, v);
    }

    std::cout << "Digite o vértice inicial para o ciclo: ";
    std::cin >> verticeInicio;

    encontraCicloEuleriano(g, verticeInicio);

    return 0;
}