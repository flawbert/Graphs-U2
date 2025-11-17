#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string.h>
#include <climits>
#include <fstream>
#include <algorithm>

using namespace std;

typedef pair<int, int> arestas; // (vizinho, peso)
map <int, vector<arestas>> matriz; // matriz de adjacência
int inicio, fim = 0; // arestas de inicio e fim da execução

void recebe_arestas(const string& nome_arquivo) {
    ifstream arquivo(nome_arquivo);

    if (!arquivo.is_open()) {
        cerr << "Erro ao ler o arquivo." << endl;
        return;
    }

    arquivo >> inicio >> fim;

    int u, v, peso;
    while (arquivo >> u >> v >> peso) {
        matriz[u].push_back({v, peso});
    }

    arquivo.close();
}

void dijkstra() {
    // inicializa distancias com valor máximo em todos os vertices
    map<int, int> distancias;
    map<int, int> subjacentes;
    for (auto& par : matriz) {
        distancias[par.first] = INT_MAX;
        subjacentes[par.first] = -1;

        for (auto& viz : par.second) {
            distancias[viz.first] = INT_MAX;
            subjacentes[viz.first] = -1;
        }
    }

    distancias[inicio] = 0; // distancia do inicio para ele mesmo é 0

    priority_queue<arestas, vector<arestas>, greater<arestas>> pq;
    pq.push({0, inicio}); // (distancia_atual, vertice_atual)

    while (!pq.empty()) {
        int distancia_atual = pq.top().first;
        int vertice_atual = pq.top().second;
        pq.pop();

        if (distancia_atual > distancias[vertice_atual]) { // se já encontramos um caminho melhor, ignora o vertice
            continue;
        }

        for (const auto& vizinho : matriz[vertice_atual]) { // para cada vizinho do vertice atual pega o tamanho para o vizinho e o peso
            int v = vizinho.first;
            int peso = vizinho.second;

            if (distancias[vertice_atual] + peso < distancias[v]) { // se o caminho encontrado for melhor, atualiza a distancia atual 
                distancias[v] = distancias[vertice_atual] + peso;
                subjacentes[v] = vertice_atual;
                pq.push({distancias[v], v});
            }
        }
    }

    // Imprime o caminho do vertice inicial ao vertice final
    if (distancias[fim] == INT_MAX) {
        cout << "Nao existe caminho entre os vertices!" << endl;
        return;
    } else {
        // Imprime a distancia do vertice inicial ao vertice final
        cout << "Distancia do vertice " << inicio << " ao vertice " << fim << " e: " << distancias[fim] << endl;
        
        vector<int> caminho;
        for (int v = fim; v != -1; v = subjacentes[v]) {
            caminho.push_back(v);
        }

        reverse(caminho.begin(), caminho.end());

        cout << "Caminho: ";
        for (int v : caminho) {
            cout << v;
            if (v != caminho.back()) cout << " -> ";
        }
        cout << endl;
    }
}

int main() {
    recebe_arestas("grafo_dijkstra.txt");

    dijkstra();

    return 0;
}
