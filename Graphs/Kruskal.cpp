#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define edge pair<int,int>

class Graph {
private:
    vector<pair<int, edge>> graph; 
    vector<pair<int, edge>> tree; 
    int* parent;

public:
    Graph(int countNodes) {
        parent = new int[countNodes];

        for (int i = 0; i <= countNodes; i++)
            parent[i] = i;
    }
    
    void PushEdge(int from, int to, int weight) {
        graph.push_back(make_pair(weight, edge(from, to)));
    }
    
    int FindSet(int i) {
        if (i == parent[i])
            return i;
        else
            return FindSet(parent[i]);
    }

    void UnionSet(int from, int to) {
        parent[from] = parent[to];
    }

    void Kruskal() {
        int i, topFrom, topTo;
        sort(graph.begin(), graph.end()); 
        for (i = 0; i < graph.size(); i++) {
            topFrom = FindSet(graph[i].second.first);
            topTo = FindSet(graph[i].second.second);
            if (topFrom != topTo) {
                tree.push_back(graph[i]); 
                UnionSet(topFrom, topTo);
            }
        }
    }

    void PrintTree() {
        cout << "Edge :" << " Weight" << endl;
        for (int i = 0; i < tree.size(); i++) {
            cout << tree[i].second.first << " - " << tree[i].second.second << " : "
                << tree[i].first;
            cout << endl;
        }
    }
};

int main() {
    int countNodes = 0;
    int topFrom = 0, topTo = 0, weight = 0;
     
    cout << "Enter count tops: ";
    cin >> countNodes;

    Graph graph(countNodes);

    while (true) {
        cout << "Enter edge [from] [to] [weight]: ";
        cin >> topFrom >> topTo >> weight;

        if (topFrom == 0 && topTo == 0 && weight == 0)
            break;

        graph.PushEdge(topFrom, topTo, weight);
    }

    graph.Kruskal();
    graph.PrintTree();

    return 0;
}