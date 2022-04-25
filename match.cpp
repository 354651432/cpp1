#include "match.h"
#include "vf2-vector/vf2.h"

bool graphEq(Graph g1, Graph g2) {
    int n = g1.V.size();
    if (n != g2.V.size()) {
        return false;
    }
    for (size_t i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (g1.G[i][j] != g2.G[i][j]) {
                return false;
            }
        }
    }

    return true;
}

vector<VType> match(Graph g1, Graph g2) {
    int n = g2.V.size();

    Combination<char> cb(g1.V);
    auto points = cb.arrangement(n);

    vector<VType> result;
    for (VType arr : points) {
        Graph subGrap = g1.subGraph(arr);
        if (graphEq(subGrap, g2)) {
            result.push_back(arr);
        }
    }

    return result;
}

vector<vector<int>> getEdges(Graph g) {
    vector<vector<int>> edges;
    int next = 100;
    for (int i = 0; i < g.G.size(); i++) {
        for (int j = 0; j < g.G[i].size(); j++) {
            if (g.G[i][j]) {
                edges.push_back({i, j, ++next});
            }
        }
    }

    return edges;
}

GraphVec GraphVecFromGraph(Graph g) {
    // n number of nodes
    // e nubmer of edges
    int n = g.V.size();

    auto edges = getEdges(g);
    int e = edges.size();

    GraphVec gV1(n, e);

    for (int i = 0; i < g.V.size(); i++) {
        gV1.node[i] = (int)g.V[i];
    };

    for (auto arr : edges) {
        // u 入度点id
        // v 出度点id
        // w label 我们这里的边没有 label
        gV1.addedge(arr[0], arr[1], 0);
    }

    return gV1;
}

bool vf2(Graph g1, Graph g2) {
    GraphVec gg1 = GraphVecFromGraph(g1);
    GraphVec gg2 = GraphVecFromGraph(g2);

    State s(gg1.getSize(), gg1.getSize());

    return match(gg1, gg2, s);
}