#include <vector>
#include <algorithm>
#include <utility>
using namespace std;
struct GraphCuts
{
    int n;
    int timer;
    vector<vector<int>> adj;
    vector<int> tin, low;
    vector<pair<int, int>> bridges;
    vector<bool> is_cut_vertex;
    GraphCuts(int _n) : n(_n), timer(0), adj(_n), tin(_n, -1), low(_n, -1), is_cut_vertex(_n, false) {}
    void add_edge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void dfs(int u, int p = -1)
    {
        tin[u] = low[u] = timer++;
        int children = 0;
        bool skipped_parent = false; // Protects against multi-edge bugs
        for (int v : adj[u])
        {
            if (v == p && !skipped_parent)
            {
                skipped_parent = true;
                continue;
            }
            if (tin[v] != -1)
            {
                low[u] = min(low[u], tin[v]);
            }
            else
            {
                dfs(v, u);
                low[u] = min(low[u], low[v]);
                // 1. Bridge Condition: No back-edge from v reaches u or above
                if (low[v] > tin[u])
                {
                    bridges.push_back({min(u, v), max(u, v)});
                }
                // 2. Articulation Point Condition (for non-root nodes)
                if (low[v] >= tin[u] && p != -1)
                {
                    is_cut_vertex[u] = true;
                }
                children++;
            }
        }
        // 3. Articulation Point Condition (for the root of the DFS tree)
        if (p == -1 && children > 1)
        {
            is_cut_vertex[u] = true;
        }
    }
    void build()
    {
        for (int i = 0; i < n; i++)
        {
            if (tin[i] == -1)
            {
                dfs(i);
            }
        }
    }
};
