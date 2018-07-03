/*
 * graph.test.cpp
 *
 *  Created on: Jul 3, 2018
 *      Author: vasyaa
 */

#include "../solvers/graph.h"

namespace solvers {
namespace graph {

/*
0 1 1 0 0
1 0 1 0 0
1 1 0 1 0
0 0 1 0 1
0 0 0 1 0
 */

void test() {
    Graph g(5);
    g.add(0, 1);
    g.add(0, 2, 8);
    g.add(1, 2);
    g.add(2, 0);
    g.add(2, 3);
    g.add(3, 4);

    Graph::return_type rc;

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
}
