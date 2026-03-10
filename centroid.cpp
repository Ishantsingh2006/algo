#include <vector>
using namespace std;
struct CentroidDecomposition
{
    int n;
    vector<vector<int>> adj;
    vector<bool> removed;
    vector<int> subtree_size;
    vector<int> centroid_parent;
    CentroidDecomposition(const vector<vector<int>> &g) : n(g.size()), adj(g)
    {
        removed.assign(n, false);
        subtree_size.assign(n, 0);
        centroid_parent.assign(n, -1);
        build(0, -1);
    }
    void calc_size(int u, int p)
    {
        subtree_size[u] = 1;
        for (int v : adj[u])
        {
            if (v != p && !removed[v])
            {
                calc_size(v, u);
                subtree_size[u] += subtree_size[v];
            }
        }
    }
    int get_centroid(int u, int p, int total)
    {
        for (int v : adj[u])
        {
            if (v != p && !removed[v] && subtree_size[v] > total / 2)
            {
                return get_centroid(v, u, total);
            }
        }
        return u;
    }
    void build(int u, int p_centroid)
    {
        calc_size(u, -1);
        int centroid = get_centroid(u, -1, subtree_size[u]);
        centroid_parent[centroid] = p_centroid;
        removed[centroid] = true;
        // --- PROBLEM SPECIFIC LOGIC GOES HERE ---
        // E.g., solve_paths_passing_through(centroid);
        // ----------------------------------------
        for (int v : adj[centroid])
        {
            if (!removed[v])
            {
                build(v, centroid);
            }
        }
    }
};
