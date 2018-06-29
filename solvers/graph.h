#ifndef SOLVERS_GRAPH_H_
#define SOLVERS_GRAPH_H_

#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <list>
#include <iterator>
#include <cassert>

namespace graph {

using namespace std;
struct Node {
    int to = 0;
    int w = 0;
};


class Graph {
public:
    const int INF = 1000000;
    const int UNDEF = -1;

    Graph(int size) {
        adj = vector<vector<Node>>(size);
    }
    void add(int a, int b, int w = 1) {
        assert(a < (int)adj.size());
        assert(b < (int)adj.size());
        adj[a].push_back(Node{b, w});
    }

    std::list<int> bfs(const int a, const int b) {
        list<int> rc;
        vector<int> visited(adj.size(), 0);

        deque<int> q;
        q.push_back(a);
        visited[a] = 1;

        while(!q.empty()) {
            int a = q.front();
            q.pop_front();
            rc.push_back(a);
//            cout << a << " ";

            if(a == b) {
                return rc;
            }

            for(auto i = adj[a].begin(); i != adj[a].end(); ++i) {
                if(!visited[i->to]) {
                    q.push_back(i->to);
                    visited[i->to] = 1;
                }
            }
        }
//        cout << endl;
        return list<int>();
    }

    list<int> dfs(const int a_, const int b) {
        list<int> rc;
        vector<int> visited(adj.size(), 0);

        stack<int> s;
        s.push(a_);

        while(!s.empty()) {
            int a = s.top();
            s.pop();
            visited[a] = 1;
            rc.push_back(a);

            if(a == b) {
                return rc;
            }

            for(auto i = adj[a].begin(); i != adj[a].end(); ++i) {
                if(!visited[i->to]) {
                    s.push(i->to);
                }
            }

        }

        return list<int>();
    }

    int minDistNode(const std::vector<int>& dist,
                    const std::vector<int>& visited) {
        int u = -1;
        int min = INF;
        for(size_t i = 0; i < dist.size(); i++) {
            if(min > dist[i] && !visited[i]) {
                min = dist[i];
                u = i;
            }
        }
        return u;
    }

    // https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm
    std::list<int> dijkstra(int a, int b) {

        std::list<int> rc;

        vector<int> visited(adj.size(), 0);

        std::vector<int> dist(adj.size(), INF);
        dist[a] = 0;

        std::vector<int> prev = std::vector<int>(adj.size(), UNDEF);

        for(size_t i = 0; i < adj.size() - 1; i++) {
            int u = minDistNode(dist, visited);

            visited[u] = 1;
            for(auto& k : adj[i]) {
                int v = k.to;
                int alt = dist[u] + k.w;
                if(alt < dist[v]) {
                    dist[v] = alt;
                    prev[v] = u;
                }
            }
        }
//        copy(dist.begin(), dist.end(), ostream_iterator<int>(cout, " "));
//        cout << endl;

        stack<int> s;
        int u = b;
        while(prev[u] != UNDEF) {
            s.push(u);
            u = prev[u];
        }
        s.push(u);

        while(!s.empty()) {
            int u = s.top();
            s.pop();
            rc.push_back(u);
        }

        return rc;
    }

private:
    vector<vector<Node>> adj;
};

/*
0 1 1 0 0
1 0 1 0 0
1 1 0 1 0
0 0 1 0 1
0 0 0 1 0
 */

inline void test() {
    Graph g(5);
    g.add(0, 1);
    g.add(0, 2, 8);
    g.add(1, 2);
    g.add(2, 0);
    g.add(2, 3);
    g.add(3, 4);

    list<int> rc;

    rc = g.bfs(0, 4);
    copy(rc.begin(), rc.end(), ostream_iterator<int>(cout, " "));
    cout << endl;

    rc = g.dfs(0, 4);
    copy(rc.begin(), rc.end(), ostream_iterator<int>(cout, " "));
    cout << endl;

    g.add(0, 4, 5);

    rc = g.dijkstra(0, 4);
    copy(rc.begin(), rc.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
}

}


#endif /* SOLVERS_GRAPH_H_ */
