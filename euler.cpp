#include <vector>
#include <algorithm>
using namespace std;
// Euler Path: A path that traverses every edge exactly once.
// Euler Circuit: An Euler Path that starts and ends at the same vertex.
// Directed Euler Path Conditions: Graph must be connected (ignoring isolated vertices)
// circuit All nodes have $in[i] == out[i]$.
// Path: Start node has $out = in + 1$, End node has $in = out + 1$. Others equal.
struct DirectedEuler
{
    int n;
    int edges_count = 0;
    vector<vector<int>> adj;
    vector<int> in_deg, out_deg;
    vector<int> path;
    DirectedEuler(int n) : n(n), adj(n), in_deg(n, 0), out_deg(n, 0) {}
    void add_edge(int u, int v)
    {
        adj[u].push_back(v);
        out_deg[u]++;
        in_deg[v]++;
        edges_count++;
    }
    // Returns true if an Euler Path/Circuit exists, false otherwise.
    bool build()
    {
        if (edges_count == 0)
        {
            path = {0};
            return true;
        }
        int start_node = -1, end_node = -1;
        for (int i = 0; i < n; i++)
        {
            if (out_deg[i] - in_deg[i] == 1)
            {
                if (start_node != -1)
                    return false;
                start_node = i;
            }
            else if (in_deg[i] - out_deg[i] == 1)
            {
                if (end_node != -1)
                    return false;
                end_node = i;
            }
            else if (in_deg[i] != out_deg[i])
            {
                return false;
            }
        }
        if (start_node == -1)
        {
            for (int i = 0; i < n; i++)
            {
                if (out_deg[i] > 0)
                {
                    start_node = i;
                    break;
                }
            }
        }
        auto dfs = [&](this auto &&self, int u) -> void
        {
            while (!adj[u].empty())
            {
                int v = adj[u].back();
                adj[u].pop_back();
                self(v);
            }
            path.push_back(u);
        };
        dfs(start_node);
        reverse(path.begin(), path.end());
        if (path.size() != edges_count + 1)
            return false;
        return true;
    }
};
// Undirected Euler Path Conditions: Graph connected (non-zero degree nodes).
// Circuit: 0 nodes with odd degree.
// Path: Exactly 2 nodes with odd degree. (Start at one of them).
struct UndirectedEuler
{
    int n;
    int edges_count = 0;
    // Adjacency list stores pairs of {neighbor_node, edge_index} to handle multigraphs
    vector<vector<pair<int, int>>> adj;
    vector<int> deg;
    vector<bool> used;
    vector<int> path;
    UndirectedEuler(int n) : n(n), adj(n), deg(n, 0) {}
    void add_edge(int u, int v)
    {
        adj[u].push_back({v, edges_count});
        adj[v].push_back({u, edges_count});
        deg[u]++;
        deg[v]++;
        used.push_back(false);
        edges_count++;
    }
    bool build()
    {
        if (edges_count == 0)
        {
            path = {0};
            return true;
        }
        int start_node = -1, odd_count = 0;
        for (int i = 0; i < n; i++)
        {
            if (deg[i] % 2 != 0)
            {
                odd_count++;
                if (start_node == -1)
                    start_node = i;
            }
        }
        if (odd_count != 0 && odd_count != 2)
            return false;
        if (start_node == -1)
        {
            for (int i = 0; i < n; i++)
            {
                if (deg[i] > 0)
                {
                    start_node = i;
                    break;
                }
            }
        }
        auto dfs = [&](this auto &&self, int u) -> void
        {
            while (!adj[u].empty())
            {
                auto edge = adj[u].back();
                adj[u].pop_back();
                int v = edge.first;
                int id = edge.second;

                if (used[id])
                    continue;
                used[id] = true;
                self(v);
            }
            path.push_back(u);
        };
        dfs(start_node);
        reverse(path.begin(), path.end());
        if (path.size() != edges_count + 1)
            return false;
        return true;
    }
};
