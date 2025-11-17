//Flawbert Costa
//Algoritmo de Boruvka para encontrar AGM em um grafo ponderado e não-direcionado
#include <iostream>
#include <vector>
#include <limits>

//Estrutura de aresta ponderada
struct Aresta {
    int src, dest, weight;
};

//Estrutura de grafo para lista de arestas
struct Grafo {
    int V;
    std::vector<Aresta> arestas;

    Grafo(int vertices) : V(vertices) {}

    void adcAresta(int u, int v, int w) {
        arestas.push_back({u, v, w});
    }
};
//Estruturas auxiliares para DSU/Union-Find, ferramenta essencial para o algoritmo de Boruvka
struct Subconjunto {
    int parent;
    int rank;
};

int find(std::vector<Subconjunto>& subconjuntos, int i) {
    if (subconjuntos[i].parent != i)
        subconjuntos[i].parent = find(subconjuntos, subconjuntos[i].parent);
    return subconjuntos[i].parent;
}

void unite(std::vector<Subconjunto>& subconjuntos, int x, int y) {
    int rootX = find(subconjuntos, x);
    int rootY = find(subconjuntos, y);
    if (rootX == rootY) return;
    if (subconjuntos[rootX].rank < subconjuntos[rootY].rank)
        subconjuntos[rootX].parent = rootY;
    else if (subconjuntos[rootX].rank > subconjuntos[rootY].rank)
        subconjuntos[rootY].parent = rootX;
    else {
        subconjuntos[rootY].parent = rootX;
        subconjuntos[rootX].rank++;
    }
}

//Implementação do algoritmo de Boruvka
void boruvkaMST(Grafo& graph) {
    int V = graph.V;
    // DSU inicial
    std::vector<Subconjunto> subconjuntos(V + 1);
    for (int v = 1; v <= V; ++v) {
        subconjuntos[v].parent = v;
        subconjuntos[v].rank = 0;
    }
    int numComponents = V;
    int mstWeight = 0;
    std::vector<Aresta> mstResult;
    std::cout << "\n--- Algoritmo de Boruvka ---\n";

    while (numComponents > 1) {

        // cheapest[c] é a aresta mais barata que sai do componente c
        std::vector<Aresta> cheapest(V + 1, {-1, -1, std::numeric_limits<int>::max()});

        //Esse for encontra a aresta mais barata para cada componente conectado (1)
        for (const auto& e : graph.arestas) {
            int setU = find(subconjuntos, e.src);
            int setV = find(subconjuntos, e.dest);

            if (setU == setV) continue;

            if (e.weight < cheapest[setU].weight) cheapest[setU] = e;
            if (e.weight < cheapest[setV].weight) cheapest[setV] = e;
        }

        // Depois de encontrar as arestas mais baratas, adiciona elas à AGM (2)
        for (int comp = 1; comp <= V; comp++) {
            Aresta e = cheapest[comp];
            if (e.src == -1) continue;
            int setU = find(subconjuntos, e.src);
            int setV = find(subconjuntos, e.dest);

            if (setU == setV) continue;

            mstResult.push_back(e);
            mstWeight += e.weight;
            unite(subconjuntos, setU, setV);
            numComponents--;
            std::cout << "Aresta: " << e.src << " - " << e.dest
                      << "  (Peso: " << e.weight << ")\n";
        }
    }

    std::cout << "\nPeso total da AGM = " << mstWeight << "\n";
}
int main() {
    int V, E;
    std::cout << "|*****Algoritmo de Boruvka (AGM)*****|\n";
    std::cout << "Digite o número de vértices: ";
    std::cin >> V;

    Grafo g(V);

    std::cout << "Digite o número de arestas: ";
    std::cin >> E;

    std::cout << "Digite as " << E << " arestas (vertice1 vertice2 peso):\n";

    for (int i = 0; i < E; i++) {
        int u, v, w;
        std::cin >> u >> v >> w;
        g.adcAresta(u, v, w);
    }
    boruvkaMST(g);

    return 0;
}
