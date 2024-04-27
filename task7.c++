#include <iostream>
#include <vector>
#include <stack>
#include <list>
using namespace std;

class Graph {
    int V;    
    list<int> *adj; 

public:
    Graph(int V);
    void addEdge(int v, int w);
    void DFS(int v, vector<bool>& visited, stack<int>& finishStack);
    void fillOrder(int v, vector<bool>& visited, stack<int>& Stack);
    Graph getTranspose();
    void printSCCs();

    void DFSUtil(int v, vector<bool>& visited);
};

Graph::Graph(int V) {
    this->V = V;
    adj = new list<int>[V];
}

void Graph::addEdge(int v, int w) {
    adj[v].push_back(w); 
}

void Graph::DFS(int v, vector<bool>& visited, stack<int>& finishStack) {
    visited[v] = true;

    for(auto i = adj[v].begin(); i != adj[v].end(); ++i)
        if(!visited[*i])
            DFS(*i, visited, finishStack);

    finishStack.push(v);
}

Graph Graph::getTranspose() {
    Graph g(V);
    for (int v = 0; v < V; v++) {
        for(auto i = adj[v].begin(); i != adj[v].end(); ++i) {
            g.adj[*i].push_back(v);
        }
    }
    return g;
}

void Graph::printSCCs() {
    stack<int> Stack;

    vector<bool> visited(V, false);

    for(int i = 0; i < V; i++)
        if(visited[i] == false)
            DFS(i, visited, Stack);

    Graph gr = getTranspose();

    fill(visited.begin(), visited.end(), false);

    while (!Stack.empty()) {
        int v = Stack.top();
        Stack.pop();

        if (visited[v] == false) {
            gr.DFSUtil(v, visited);
            cout << endl;
        }
    }
}

void Graph::DFSUtil(int v, vector<bool>& visited) {
    visited[v] = true;
    cout << v << " ";
    for(auto i = adj[v].begin(); i != adj[v].end(); ++i)
        if(!visited[*i])
            DFSUtil(*i, visited);
}

int main() {
    Graph g(5);
    g.addEdge(1, 0);
    g.addEdge(0, 2);
    g.addEdge(2, 1);
    g.addEdge(0, 3);
    g.addEdge(3, 4);

    cout << "Following are strongly connected components in given graph \n";
    g.printSCCs();

    return 0;
}
