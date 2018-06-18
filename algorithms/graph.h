#ifndef GRAPH_H_
#define GRAPH_H_

#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <list>

namespace graph {

using namespace std;
using Node = std::pair<int, int>;

class Graph {
public:
    Graph(int size) {
        adj = vector<list<Node>>(size);
        visited = vector<int>(size, 0);
    }
    void add(int a, int b, int w = 0) {
        adj[a].push_back(std::make_pair(b, w));
    }

    bool bfs(int a, int b) {
        generate(visited.begin(), visited.end(), [](){return 0;});

        deque<int> q;
        q.push_back(a);
        visited[a] = 1;

        while(!q.empty()) {
            a = q.front();
            q.pop_front();
            cout << a << " ";

            if(a == b)
                return true;

            for(auto i = adj[a].begin(); i != adj[a].end(); ++i) {
                if(!visited[i->first]) {
                    q.push_back(i->first);
                    visited[i->first] = 1;
                }
            }
        }
        cout << endl;
        return false;
    }

    bool dfs(int a, int b) {
        generate(visited.begin(), visited.end(), [](){return 0;});

        stack<int> s;
        s.push(a);

        while(!s.empty()) {
            a = s.top();
            s.pop();
            visited[a] = 1;
            cout << a << " ";

            if(a == b)
                return true;

            for(auto i = adj[a].begin(); i != adj[a].end(); ++i) {
                if(!visited[i->first]) {
                    s.push(i->first);
                }
            }

        }

        return false;
    }

    std::vector<int> dijkstra(int a, int b) {
        std::vector<int> rc;

        return rc;
    }

private:
    vector<list<Node>> adj;
    vector<int> visited;
};


inline void test() {
    Graph g(4);
    g.add(0, 1);
    g.add(0, 2);
    g.add(1, 2);
    g.add(2, 0);
    g.add(2, 3);
    g.add(3, 3);

    g.bfs(2, 1);
    std::cout << std::endl;
    g.dfs(2, 1);
    std::cout << std::endl;
}

}


#endif /* GRAPH_H_ */
