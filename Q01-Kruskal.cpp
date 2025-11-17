#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

// Estrutura para representar uma aresta ponderada no grafo
struct Aresta {
    int origem, destino, peso;
};

// Estrutura auxiliar para o Union-Find
struct Subconjunto {
    int pai;
    int rank;
};

// Encontra o representante (raiz) do conjunto que contém o elemento i
int encontrar(Subconjunto subconjuntos[], int i) {
    if (subconjuntos[i].pai != i) {
        subconjuntos[i].pai = encontrar(subconjuntos, subconjuntos[i].pai);
    }
    return subconjuntos[i].pai;
}

// Une dois subconjuntos pelo rank
void unir(Subconjunto subconjuntos[], int x, int y) {
    int raizX = encontrar(subconjuntos, x);
    int raizY = encontrar(subconjuntos, y);

    if (subconjuntos[raizX].rank < subconjuntos[raizY].rank) {
        subconjuntos[raizX].pai = raizY;
    } 
    else if (subconjuntos[raizY].rank < subconjuntos[raizX].rank) {
        subconjuntos[raizY].pai = raizX;
    } 
    else {
        subconjuntos[raizY].pai = raizX;
        subconjuntos[raizX].rank++;
    }
}

// Executa o algoritmo de Kruskal para formar a Árvore Geradora Mínima (AGM)
std::vector<Aresta> kruskal(size_t numVertices, std::vector<Aresta>& arestas) {
    // Ordenar as arestas em ordem crescente de pesos
    std::sort(arestas.begin(), arestas.end(), [](Aresta a, Aresta b) {
        return a.peso < b.peso;
    });
    // Estrutura Union-Find
    std::vector<Subconjunto> subconjuntos(numVertices + 1);
    for (size_t v = 1; v <= numVertices; v++) {
        subconjuntos[v].pai = v;
        subconjuntos[v].rank = 0;
    }
    std::vector<Aresta> T;
    // T <- {h_1}
    T.push_back(arestas[0]);
    // unir conjuntos correspondentes
    unir(&subconjuntos[0], arestas[0].origem, arestas[0].destino);
    size_t i = 1;
    // enquanto T.tamanho < n - 1 faça
    while (T.size() < (numVertices - 1) && i < arestas.size()) {
        Aresta atual = arestas[i];
        // Se T U h_i é acíclico então
        int x = encontrar(&subconjuntos[0], atual.origem);
        int y = encontrar(&subconjuntos[0], atual.destino);
        if (x != y) {  
            // T <- T U h_i
            T.push_back(atual);
            unir(&subconjuntos[0], x, y);
        } else {
            // i <- i+1
            i++;
        }
    }
    return T; // Retorna a AGM 
}

int main() {
    size_t V = 19;

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

    std::vector<Aresta> AGM = kruskal(V, arestas);

    std::cout << "QUESTAO 01 - Algoritmo de Kruskal\n";
    std::cout << "T = {";
    int custo = 0;
    for (size_t i = 0; i < AGM.size(); i++) {
        std::cout << "(" << AGM[i].origem << "," << AGM[i].destino << ")";
        custo += AGM[i].peso;
        if (i < AGM.size() - 1) std::cout << ", ";
    }
    std::cout << "}\n";

    std::cout << "Custo = " << custo << "\n";

    return 0;
}