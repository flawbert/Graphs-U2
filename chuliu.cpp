#include <algorithm>
#include <climits>
#include <iostream>
#include <queue>
#include <vector>
#include <unordered_set>
#include <fstream>

using namespace std;

// Estrutura de aresta
struct aresta {
    int u, v;
    int w;
};

int chuliu(int raiz, vector<aresta>& arestas, int N) {
    int res = 0;

    while (true) {
        vector<int> in(N, INT_MAX);
        vector<int> pre(N, -1);
        vector<int> id(N, -1);
        vector<int> vis(N, -1);

        // escolher a menor aresta de entrada em cada vertice
        for (auto& e : arestas) {
            if (e.u != e.v && e.w < in[e.v]) {
                in[e.v] = e.w;
                pre[e.v] = e.u;
            }
        }

        in[raiz] = 0;  // raiz não tem aresta de entrada

        // Se algum vertice (exceto raiz) não recebeu aresta de entrada, não é possivel formar arborescência
        for (int i = 0; i < N; i++) {
            if (i == raiz) continue;
            if (in[i] == INT_MAX) {
                return -1; // impossível formar arborescência, retorna
            }
        }

        // Soma dos mínimos
        for (int i = 0; i < N; i++){
            res += in[i];
        }

        int ciclos = 0;

        // detectar ciclos
        for (int i = 0; i < N; i++) {
            int v = i;
            while (vis[v] != i && id[v] == -1 && v != raiz) {
                vis[v] = i;
                v = pre[v];
            }

            if (v != raiz && id[v] == -1) {
                for (int u = pre[v]; u != v; u = pre[u])
                    id[u] = ciclos;
                id[v] = ciclos++;
            }
        }

        // Se não houver ciclos, finaliza
        if (ciclos == 0){
            break;
        }

        // indexa novamente os vértices sem ciclo
        for (int i = 0; i < N; i++){
            if (id[i] == -1){
                id[i] = ciclos++;
            }
        }

        // ajusta arestas
        vector<aresta> novasarestas;
        for (auto& e : arestas) {
            int u = id[e.u];
            int v = id[e.v];
            int w = e.w;
            if (u != v) {
                w -= in[e.v];
                novasarestas.push_back({u, v, w});
            }
        }

        N = ciclos;
        raiz = id[raiz];
        arestas = novasarestas;
    }

    return res;
}

int main() {
    ifstream file("testes.txt");

    if (!file.is_open()) {
        cerr << "Erro ao abrir arquivo!\n";
        return 1;
    }

    vector<aresta> arestas;
    int u, v, w;
    unordered_set<int> vertices;

    while (file >> u >> v >> w) {
        arestas.push_back({u-1, v-1, w});
        vertices.insert(u-1);
        vertices.insert(v-1);
    }

    file.close();

    int result = chuliu(0, arestas, vertices.size());

    if (result == -1) {
        cout << "Nao existe arborescencia com todos os vertices alcançaveis da raiz.\n";
    } else {
        cout << "Custo minimo da arborescencia: " << result << "\n";
    }

    return 0;
}
