#include <vector>
#include <string>
#include <array>
#include <cassert>
using namespace std;
class Trie
{
public:
    struct Node
    {
        array<int, 26> next;
        int exact_count = 0;
        int prefix_count = 0;
        Node()
        {
            next.fill(-1);
        }
    };
    vector<Node> nodes;
    Trie()
    {
        nodes.emplace_back();
    }
    void clear()
    {
        nodes.clear();
        nodes.emplace_back();
    }
    void insert(const string &s)
    {
        int u = 0;
        nodes[u].prefix_count++;
        for (char c : s)
        {
            int v = c - 'a';
            if (nodes[u].next[v] == -1)
            {
                nodes[u].next[v] = nodes.size();
                nodes.emplace_back();
            }
            u = nodes[u].next[v];
            nodes[u].prefix_count++;
        }
        nodes[u].exact_count++;
    }
    // Exact match count
    int count(const string &s) const
    {
        int u = 0;
        for (char c : s)
        {
            int v = c - 'a';
            if (nodes[u].next[v] == -1)
                return 0;
            u = nodes[u].next[v];
        }
        return nodes[u].exact_count;
    }
    // Prefix match count
    int countPref(const string &s) const
    {
        int u = 0;
        for (char c : s)
        {
            int v = c - 'a';
            if (nodes[u].next[v] == -1)
                return 0;
            u = nodes[u].next[v];
        }
        return nodes[u].prefix_count;
    }
    int get_lcp(const string &s) const
    {
        int u = 0;
        int len = 0;
        for (char c : s)
        {
            int v = c - 'a';
            if (nodes[u].next[v] == -1)
                break;
            u = nodes[u].next[v];
            len++;
        }
        return len;
    }
    bool erase(const string &s)
    {
        if (count(s) == 0)
            return false;
        int u = 0;
        nodes[u].prefix_count--;
        for (char c : s)
        {
            int v = c - 'a';
            u = nodes[u].next[v];
            nodes[u].prefix_count--;
        }
        nodes[u].exact_count--;
        return true;
    }
};
