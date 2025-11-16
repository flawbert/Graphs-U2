//Gabrielle
//Implementação do algoritmo de prim para encontrar a árvore geradora mínima.
#include <iostream>
#include <vector>
#include <queue>    
#include <functional>
using namespace std; 

const int N = 19; //Número de vértices do grafo de exemplo
using Aresta = pair<int, int>; //Par (peso, vizinho)
vector<Aresta> adj[N + 1]; //Lista de adjacência (ajd[i] = lista de arestas do vértice i)

void carregarGrafo() {
    adj[1].push_back({2, 2});
    adj[2].push_back({2, 1});
    adj[1].push_back({3, 6});
    adj[6].push_back({3, 1});
    adj[1].push_back({1, 11});
    adj[11].push_back({1, 1});
    adj[2].push_back({1, 3});
    adj[3].push_back({1, 2});
    adj[2].push_back({7, 6});
    adj[6].push_back({7, 2});
    adj[3].push_back({2, 4});
    adj[4].push_back({2, 3});
    adj[3].push_back({9, 6});
    adj[6].push_back({9, 3});
    adj[3].push_back({10, 8});
    adj[8].push_back({10, 3});
    adj[3].push_back({2, 9});
    adj[9].push_back({2, 3});
    adj[4].push_back({4, 5});
    adj[5].push_back({4, 4});
    adj[4].push_back({9, 9});
    adj[9].push_back({9, 4});
    adj[4].push_back({7, 10});
    adj[10].push_back({7, 4});
    adj[4].push_back({15, 13});
    adj[13].push_back({15, 4});
    adj[5].push_back({5, 10});
    adj[10].push_back({5, 5});
    adj[6].push_back({2, 7});
    adj[7].push_back({2, 6});
    adj[6].push_back({0, 11});
    adj[11].push_back({0, 6});
    adj[7].push_back({8, 8});
    adj[8].push_back({8, 7});
    adj[7].push_back({1, 12});
    adj[12].push_back({1, 7});
    adj[7].push_back({5, 13});
    adj[13].push_back({5, 7});
    adj[8].push_back({7, 9});
    adj[9].push_back({7, 8});
    adj[9].push_back({1, 14});
    adj[14].push_back({1, 9});
    adj[9].push_back({2, 18});
    adj[18].push_back({2, 9});
    adj[10].push_back({6, 14});
    adj[14].push_back({6, 10});
    adj[10].push_back({9, 15});
    adj[15].push_back({9, 10});
    adj[11].push_back({4, 12});
    adj[12].push_back({4, 11});
    adj[11].push_back({2, 16});
    adj[16].push_back({2, 11});
    adj[12].push_back({3, 16});
    adj[16].push_back({3, 12});
    adj[12].push_back({1, 17});
    adj[17].push_back({1, 12});
    adj[13].push_back({4, 18});
    adj[18].push_back({4, 13});
    adj[14].push_back({1, 15});
    adj[15].push_back({1, 14});
    adj[14].push_back({18, 19});
    adj[19].push_back({18, 14});
    adj[17].push_back({20, 18});
    adj[18].push_back({20, 17});
    adj[17].push_back({5, 19});
    adj[19].push_back({5, 17});
}

void prim(){
    carregarGrafo(); 

    vector<bool> visitado(N + 1, false);
    int pesoTotal = 0;
    
    using Item = tuple<int,int,int>; //Tuplas {peso, vertice, pai}
    priority_queue<Item, vector<Item>, greater<Item>> pq; //Menor peso primeiro

    pq.push( {0, 1, -1} ); //Marca o inicio em 1 com o pai sendo -1

    vector<pair<int,int>> mst_arestas; // para armazenar as arestas na ordem de entrada

    while (!pq.empty()) {
        auto [peso, u, pai] = pq.top();
        pq.pop();

        // Se o vértice ja foi visitado, ele é ignorado e o algoritmo continua
        if (visitado[u]) {
            continue;
        }

        visitado[u] = true;   // Marca como visitado
        pesoTotal += peso;    // Soma o custo no peso total

        //Se pai != -1 (pra definir o primeiro vertice como raiz)
        if (pai != -1) {
            mst_arestas.push_back({pai, u});
        }

        //Coloca todas as arestas de u na fila de prioridade
        for (auto& aresta_vizinha : adj[u]) {
            int peso_vizinho = aresta_vizinha.first;
            int v_vizinho = aresta_vizinha.second;

            if (!visitado[v_vizinho]) {
                //Organiza a fila pra pegar o menor peso primeiro, agora pai = u
                pq.push( {peso_vizinho, v_vizinho, u} );
            }
        }
    }

    cout << "Arestas da MST:\n";
    for (auto& aresta : mst_arestas)
        cout << aresta.first << " - " << aresta.second << "\n";
    cout << "Peso Total: " << pesoTotal << "\n";
}

int main() {
    prim();
    return 0;
}
