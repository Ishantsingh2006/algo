#include <bits/stdc++.h>
using namespace std;
class dsu
{
public:
  vector<int> p;
  vector<int> sz;
  int n;
  dsu(int _n) : n(_n)
  {
    p.resize(n);
    iota(p.begin(), p.end(), 0);
    sz.assign(n, 1);
  }
  int get(int x)
  {
    return (x == p[x] ? x : (p[x] = get(p[x])));
  }
  void unite(int x, int y)
  {
    x = get(x), y = get(y);
    if (x != y)
    {
      if (sz[x] < sz[y])
        swap(x, y);
      p[y] = x;
      sz[x] += sz[y];
    }
  }
};
