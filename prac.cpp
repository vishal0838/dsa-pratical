#include<iostream>
#include<vector>
#include<algorithm>
#include<map>
using namespace std;

struct Edge {
    int u, v, w;
};

bool cmp(Edge a, Edge b) {
    return a.w < b.w;
}

int find(vector<int>& p, int x) {
    if (p[x] != x)
        p[x] = find(p, p[x]);
    return p[x];
}

int main() {
    int n, m;
    cout << "Enter number of cities and connections: ";
    cin >> n >> m;

    map<string, int> city;
    vector<string> names(1); // starting from index 1
    int id = 1;
    vector<Edge> edges;

    
    cout << "\nEnter edges (city1 city2 weight):\n";
    for (int i = 0; i < m; i++) {
        string a, b;
        int w;
        cin >> a >> b >> w;
        if (city.find(a) == city.end()) {
            city[a] = id++;
            names.push_back(a);
        }
        if (city.find(b) == city.end()) {
            city[b] = id++;
            names.push_back(b);
        }
        edges.push_back({city[a], city[b], w});
    }

    sort(edges.begin(), edges.end(), cmp);

    vector<int> parent(id);
    for (int i = 0; i < id; i++) parent[i] = i; // Initialize properly

    int cost = 0;
    cout << "\nMST edges:\n";

    for (size_t i = 0; i < edges.size(); ++i) {
        Edge e = edges[i];
        int u = find(parent, e.u), v = find(parent, e.v);
        if (u != v) {
            parent[u] = v;
            cout << names[e.u] << " -- " << names[e.v] << " : " << e.w << endl;
            cost += e.w;
        }
    }

    cout << "\nTotal cost: " << cost << endl;

    return 0;
}
