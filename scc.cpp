#include <vector>
#include <algorithm>
#include <cassert>
using namespace std;
struct SCC
{
    int n;
    int timer = 0;
    int scc_cnt = 0;
    vector<vector<int>> adj;
    vector<vector<int>> dag; // Adjacency list of the condensed graph
    vector<int> num, low, st;
    vector<int> comp; // comp[u]: ID of the SCC that node u belongs to
    vector<bool> on_st;
    vector<vector<int>> comps; // comps[i]: list of nodes in SCC i
    SCC(int _n) : n(_n), adj(_n), num(_n, -1), low(_n, -1), on_st(_n, false), comp(_n, -1) {}
    void add_edge(int u, int v)
    {
        adj[u].push_back(v);
    }
    void dfs(int u)
    {
        num[u] = low[u] = timer++;
        st.push_back(u);
        on_st[u] = true;
        for (int v : adj[u])
        {
            if (num[v] == -1)
            {
                dfs(v);
                low[u] = min(low[u], low[v]);
            }
            else if (on_st[v])
            {
                low[u] = min(low[u], num[v]);
            }
        }
        if (low[u] == num[u])
        {
            comps.push_back({});
            while (true)
            {
                int v = st.back();
                st.pop_back();
                on_st[v] = false;
                comp[v] = scc_cnt;
                comps.back().push_back(v);
                if (u == v)
                    break;
            }
            scc_cnt++;
        }
    }
    void build()
    {
        for (int i = 0; i < n; i++)
        {
            if (num[i] == -1)
            {
                dfs(i);
            }
        }
        dag.assign(scc_cnt, vector<int>());
        for (int u = 0; u < n; u++)
        {
            for (int v : adj[u])
            {
                if (comp[u] != comp[v])
                {
                    dag[comp[u]].push_back(comp[v]);
                }
            }
        }
        for (auto &edges : dag)
        {
            sort(edges.begin(), edges.end());
            edges.erase(unique(edges.begin(), edges.end()), edges.end());
        }
    }
};
