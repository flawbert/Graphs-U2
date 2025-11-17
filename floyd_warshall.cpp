//Gabrielle
//Implementação do algoritmo de floyd-warshall para encontrar o caminho mais curto.
#include <iostream>
#include <vector> 
#include <climits>
using namespace std; 

const int N = 19; //Número de vértices do grafo de exemplo
using Aresta = pair<int, int>; //Par (peso, vizinho)
vector<Aresta> adj[N + 1]; //Lista de adjacência (ajd[i] = lista de arestas do vértice i)
int dist[N + 1][N + 1]; //Matriz de distâncias
int pred[N + 1][N + 1]; //Matriz de predecessores
const int INF = 1000000; // Definindo infinito como um valor grande o suficiente

void carregarGrafo() {
    adj[1].push_back({3, 6});
    adj[1].push_back({1, 11});

    adj[2].push_back({2, 1});
    adj[2].push_back({8, 3});
    adj[2].push_back({7, 6});

    adj[3].push_back({1, 2});
    adj[3].push_back({2, 4});
    adj[3].push_back({10, 8});
    
    adj[4].push_back({9, 9});
    adj[4].push_back({7, 10});
    adj[4].push_back({15, 13});

    adj[5].push_back({4, 4});

    adj[6].push_back({2, 7});
    adj[6].push_back({9, 3});

    adj[7].push_back({8, 8});
    adj[7].push_back({1, 12});

    adj[8].push_back({7, 9});
       
    adj[9].push_back({2, 3});
    adj[9].push_back({1, 14});
    
    adj[10].push_back({5, 5});
    adj[10].push_back({6, 14});
    adj[10].push_back({9, 15});

    adj[11].push_back({0, 6});
    adj[11].push_back({2, 16});

    adj[12].push_back({1, 17});
    adj[12].push_back({4, 11});

    adj[13].push_back({5, 7});
    adj[13].push_back({4, 18});

    adj[14].push_back({1, 15});
    adj[14].push_back({18, 19});

    adj[16].push_back({3, 12});
    
    adj[17].push_back({1, 12});
    adj[17].push_back({5, 19});

    adj[18].push_back({2, 9});
    adj[18].push_back({20, 17});
}

void inicializarMatrizes() {
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            dist[i][j] = INF;
            pred[i][j] = -1;
        }
    }
    //Preenche com os pesos dados do digrafo
    for (int i = 1; i <= N; i++) {
        for (auto& aresta : adj[i]) {
            int j = aresta.second;  //Vértice de destino
            int peso = aresta.first; //Peso da aresta (i -> j)
            dist[i][j] = peso; //Distancia = peso da aresta
            pred[i][j] = i; 
        }
    }
    //Diagonal prinicipal -> 0
    for (int i = 1; i <= N; i++) {
        dist[i][i] = 0;
        pred[i][i] = i;
    }
}

void imprimirCaminhoRecursivo(int i, int j) {
    if (i == j) { //Caso origem == destino
        cout << i;
    }
    // Caso sem caminho
    else if (pred[i][j] == -1) {
        cout << "Nenhum caminho de " << i << " para " << j << " existe.";
    }
    //Caso dentro do caminho (recursão)
    else {
        //Funcao pra imprimir o caminho até o vértice anterior
        imprimirCaminhoRecursivo(i, pred[i][j]);
        // imprime o vértice atual
        cout << " -> " << j;
    }
}

/**
 * @brief Imprime o resultado final (distância e caminho)
 * para um par de vértices (inicio, fim).
 */
void imprimirResultadoFinal(int inicio, int fim) {
    
    // Distância Total (matriz 'dist')
    cout << "--- Caminho de " << inicio << " para " << fim << " ---" << endl;
    
    if (dist[inicio][fim] == INF) {
        cout << "Distância Total: Infinito (Nenhum caminho encontrado)\n";
    } else {
        cout << "Distância Total: " << dist[inicio][fim] << "\n";
    }

    //Caminho (matriz 'pred') ---
    cout << "Caminho: ";
    imprimirCaminhoRecursivo(inicio, fim);
    cout << endl;
}

/**
 * @brief Implementação do Algoritmo de Floyd-Warshall
 * para encontrar os caminhos mais curtos entre todos os pares de vértices.
 *
 */
void floydWarshall() {
    carregarGrafo();
    inicializarMatrizes();
    
    //Tres loops principais do algoritmo para atualizar distancias
    for (int k = 1; k <= N; k++) {
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];// Atualiza distancia
                    pred[i][j] = pred[k][j]; //Atualiza predecessor
                }
            }
        }
    }
    imprimirResultadoFinal(1, 15); //Exemplo: caminho de 1 a 15
}

int main() {
    floydWarshall();
    return 0;
}