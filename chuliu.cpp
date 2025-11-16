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
    int peso;
};

int chuliu(int raiz, vector<aresta>& arestas, int N) {
    int res = 0;

    while (true) {
        vector<int> entrada(N, INT_MAX);
        vector<int> pre(N, -1);
        vector<int> id(N, -1); 
        vector<int> vis(N, -1); 

        // escolher a menor aresta de entrada em cada nó
        for (auto& e : arestas) {
            if (e.u != e.v && e.peso < entrada[e.v]) {
                entrada[e.v] = e.peso;
                pre[e.v] = e.u;
            }
        }

        entrada[raiz] = 0;  // raiz não tem aresta de entrada

        // Se algum nó (exceto raiz) não recebeu aresta de entrada
        for (int i = 0; i < N; i++) {
            if (i == raiz) continue;
            if (entrada[i] == INT_MAX) {
                return -1; // impossível formar arborescência, retorna
            }
        }

        // Soma dos mínimos
        for (int i = 0; i < N; i++){
            res += entrada[i];
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

        // Se não houve ciclos, finaliza
        if (ciclos == 0){
            break;
        }

        // indexa novamente os nós sem ciclo
        for (int i = 0; i < N; i++){
            if (id[i] == -1){
                id[i] = ciclos++;
            }
        }

        // contrai ciclos e ajusta arestas
        vector<aresta> novasarestas;
        for (auto& e : arestas) {
            int u = id[e.u];
            int v = id[e.v];
            int peso = e.peso;
            if (u != v) {
                peso -= entrada[e.v];
                novasarestas.push_back({u, v, peso});
            }
        }

        N = ciclos;
        raiz = id[raiz];
        arestas = novasarestas;
    }

    return res;
}

int main() {
    ifstream file("grafo_chuliu.txt");

    if (!file.is_open()) {
        cerr << "Erro ao abrir arquivo!\n";
        return 1;
    }

    vector<aresta> arestas;
    int u, v, peso;
    unordered_set<int> vertices;

    while (file >> u >> v >> peso) {
        arestas.push_back({u-1, v-1, peso});
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
