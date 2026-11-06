#include <iostream>
#include <vector>
#include <climits>
#include <cctype>
using namespace std;

class Graph {
private:
    int V;
    vector<vector<int>> adjMatrix;

    // Hitung jarak terpendek dari source, simpan juga parent untuk menyusun rute
    void hitungDijkstra(int source, vector<int>& distance, vector<int>& parent) {
        distance.assign(V, INT_MAX);
        parent.assign(V, -1);
        vector<bool> visited(V, false);
        distance[source] = 0;

        for (int i = 0; i < V; i++) {
            int u = -1;

            for (int j = 0; j < V; j++) {
                if (!visited[j] &&
                    (u == -1 || distance[j] < distance[u])) {
                    u = j;
                }
            }

            if (u == -1 || distance[u] == INT_MAX)
                break;

            visited[u] = true;

            for (int v = 0; v < V; v++) {
                if (adjMatrix[u][v] != 0 && !visited[v]) {
                    int newDistance = distance[u] + adjMatrix[u][v];

                    if (newDistance < distance[v]) {
                        distance[v] = newDistance;
                        parent[v] = u;
                    }
                }
            }
        }
    }

    // Cetak rute dari source sampai vertex v (rekursif lewat parent)
    void printPath(const vector<int>& parent, int v) {
        if (parent[v] == -1) {
            cout << char('A' + v);
            return;
        }
        printPath(parent, parent[v]);
        cout << " -> " << char('A' + v);
    }

public:
    Graph(int jumlahVertex) {
        V = jumlahVertex;
        adjMatrix.resize(V, vector<int>(V, 0));
    }

    void addEdge(int u, int v, int weight) {
        adjMatrix[u][v] = weight;
        adjMatrix[v][u] = weight;
    }

    void printAdjMatrix() {
        cout << "   ";
        for (int i = 0; i < V; i++) {
            cout << char('A' + i) << "  ";
        }
        cout << endl;
        for (int i = 0; i < V; i++) {
            cout << char('A' + i) << "  ";
            for (int j = 0; j < V; j++) {
                cout << adjMatrix[i][j] << "  ";
            }
            cout << endl;
        }
    }

    // Rute terpendek dari source ke semua lokasi lain + total jarak
    void dijkstra(int source) {
        vector<int> distance, parent;
        hitungDijkstra(source, distance, parent);

        cout << "Jarak terpendek dari lokasi " << char('A' + source) << ":" << endl;

        for (int i = 0; i < V; i++) {
            if (i == source) continue;

            cout << char('A' + source) << " ke " << char('A' + i) << " : ";
            if (distance[i] == INT_MAX) {
                cout << "Tidak terjangkau" << endl;
            } else {
                printPath(parent, i);
                cout << " | Total jarak: " << distance[i] << " km" << endl;
            }
        }
    }

    // Rekomendasi rute tercepat dari satu lokasi ke lokasi lain
    void rekomendasiRute(int source, int tujuan) {
        vector<int> distance, parent;
        hitungDijkstra(source, distance, parent);

        cout << "Rekomendasi rute tercepat " << char('A' + source)
             << " ke " << char('A' + tujuan) << ":" << endl;

        if (distance[tujuan] == INT_MAX) {
            cout << "Tidak terjangkau" << endl;
        } else {
            cout << "Rute        : ";
            printPath(parent, tujuan);
            cout << endl;
            cout << "Total jarak : " << distance[tujuan] << " km" << endl;
        }
    }
};

int main() {
    Graph graph(6); // 6 lokasi: A - F

    graph.addEdge(0, 1, 4); // A-B
    graph.addEdge(0, 2, 2); // A-C
    graph.addEdge(1, 2, 1); // B-C
    graph.addEdge(1, 3, 5); // B-D
    graph.addEdge(1, 4, 3); // B-E
    graph.addEdge(2, 3, 8); // C-D
    graph.addEdge(2, 4, 6); // C-E
    graph.addEdge(3, 4, 2); // D-E
    graph.addEdge(3, 5, 4); // D-F
    graph.addEdge(4, 5, 3); // E-F

    cout << "Adjacency Matrix (jarak dalam km):" << endl;
    graph.printAdjMatrix();
    cout << endl;

    // Rute terpendek dari A ke semua lokasi lain
    graph.dijkstra(0);
    cout << endl;

    // Rekomendasi rute berdasarkan input pengguna
    char asal, tujuan;
    cout << "Masukkan lokasi asal (A-F)   : ";
    cin >> asal;
    cout << "Masukkan lokasi tujuan (A-F) : ";
    cin >> tujuan;
    asal = toupper(asal);
    tujuan = toupper(tujuan);

    if (asal < 'A' || asal > 'F' || tujuan < 'A' || tujuan > 'F') {
        cout << "Lokasi nonvalid" << endl;
        return 1;
    }

    cout << endl;
    graph.rekomendasiRute(asal - 'A', tujuan - 'A');

    return 0;
}