#include <vector>
#include <bit>
#include <queue>
#include <utility>
#include <algorithm>
#include <cassert>
using namespace std;
struct Tree
{
    int n;
    int max_log;
    vector<vector<pair<int, long long>>> adj;
    vector<vector<int>> up;
    vector<int> depth;
    vector<long long> dist;
    Tree(int _n) : n(_n)
    {
        assert(n > 0);
        max_log = 32 - __builtin_clz(n);
        adj.resize(n);
        up.assign(n, vector<int>(max_log, 0));
        depth.assign(n, 0);
        dist.assign(n, 0LL);
    }
    void add_edge(int u, int v, long long w = 1)
    {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    void build(int root = 0)
    {
        queue<int> q;
        q.push(root);
        up[root][0] = root;
        depth[root] = 0;
        dist[root] = 0;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            for (auto &edge : adj[u])
            {
                int v = edge.first;
                long long w = edge.second;
                if (v != up[u][0])
                {
                    up[v][0] = u;
                    depth[v] = depth[u] + 1;
                    dist[v] = dist[u] + w;
                    q.push(v);
                }
            }
        }
        for (int j = 1; j < max_log; ++j)
        {
            for (int i = 0; i < n; ++i)
            {
                up[i][j] = up[up[i][j - 1]][j - 1];
            }
        }
    }
    int jump(int u, int k) const
    {
        if (depth[u] < k)
            return -1;
        for (int j = 0; j < max_log; ++j)
        {
            if ((k >> j) & 1)
            {
                u = up[u][j];
            }
        }
        return u;
    }
    int lca(int u, int v) const
    {
        if (depth[u] < depth[v])
            swap(u, v);
        u = jump(u, depth[u] - depth[v]);
        if (u == v)
            return u;
        for (int j = max_log - 1; j >= 0; --j)
        {
            if (up[u][j] != up[v][j])
            {
                u = up[u][j];
                v = up[v][j];
            }
        }
        return up[u][0];
    }
    int unweighted_dist(int u, int v) const
    {
        return depth[u] + depth[v] - 2 * depth[lca(u, v)];
    }
    long long weighted_dist(int u, int v) const
    {
        return dist[u] + dist[v] - 2 * dist[lca(u, v)];
    }
    int path_k(int u, int v, int k) const
    {
        int a = lca(u, v);
        int dist_u_a = depth[u] - depth[a];
        int dist_v_a = depth[v] - depth[a];
        if (k <= dist_u_a)
        {
            return jump(u, k);
        }
        k -= dist_u_a;
        if (k <= dist_v_a)
        {
            return jump(v, dist_v_a - k);
        }
        return -1;
    }
};
