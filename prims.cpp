#include <iostream>
#include <vector>
#include <climits>
using namespace std;

class Graph {
    private:
        int v;
        vector<vector<int>> adjMatrix;

    public:
        Graph(int jumlahVertex) {
            v = jumlahVertex;
            adjMatrix.resize(v, vector<int>(v, 0));
        }

        void addEdge(int u, int v, int weight) {
                adjMatrix[u][v] = weight;
                adjMatrix[v][u] = weight; // karena undirected graph
        }

        int minKey(vector<int>& key, vector<bool>& mstSet) {
            int min = INT_MAX;
            int minIndex = -1;

            for (int v = 0; v < this->v; v++) {
                if (!mstSet[v] && key[v] < min) {
                    min = key[v];
                    minIndex = v;
                }
            }
            return minIndex;
        }

        void prim(){
            vector<int> parent(v, -1);
            vector<int> key(v, INT_MAX);
            vector<bool> mstSet(v, false);

            key[0] = 0;

            for (int count = 0; count < v - 1; count++) {
                int u = minKey(key, mstSet);
                mstSet[u] = true;

                if (u == -1) {
                    cout << "graph tidak terhubung." << endl;
                    return;
                }

                mstSet[u] = true;

                for (int v = 0; v < this->v; v++) {
                    if (adjMatrix[u][v] && !mstSet[v] && adjMatrix[u][v] < key[v]) {
                        parent[v] = u;
                        key[v] = adjMatrix[u][v];
                    }
                }
        }
        int totalWeight = 0;
        cout<<"Edge pada MST (prim): "<<endl;

        for (int i = 1; i < v; i++) {
            cout << parent[i] << " - " << i << " (weight: " << adjMatrix[i][parent[i]] << ")" << endl;
            totalWeight += adjMatrix[i][parent[i]];
        }
        cout << "Total bobot MST: " << totalWeight << endl;
    }
};

int main() {
    Graph graph(5);

    graph.addEdge(0, 1, 2);
    graph.addEdge(0, 3, 6);
    graph.addEdge(1, 2, 3);
    graph.addEdge(1, 3, 8);
    graph.addEdge(1, 4, 5);
    graph.addEdge(2, 4, 7);
    graph.addEdge(3, 4, 9);

    graph.prim();

    return 0;
}