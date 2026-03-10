#include <bits/stdc++.h>
using namespace std;
// for associative a*(b*c)=(a*b)*c
template <typename T, class F>
class DisjointSparseTable
{
public:
  int n, sz, levels;
  vector<T> st;
  F func;
  DisjointSparseTable(const vector<T> &a, const F &f) : func(f)
  {
    n = (int)a.size();
    if (n == 0)
      return;
    sz = 2;
    levels = 1;
    while (sz < n)
    {
      sz *= 2;
      levels++;
    }
    vector<T> b = a;
    b.resize(sz, b.back());
    st.resize(levels * sz);
    for (int level = 0; level < levels; level++)
    {
      int half = 1 << level;
      int offset = level * sz;
      for (int i = half; i < sz; i += 2 * half)
      {
        st[offset + i - 1] = b[i - 1];
        for (int j = i - 2; j >= i - half; j--)
        {
          st[offset + j] = func(b[j], st[offset + j + 1]);
        }
        st[offset + i] = b[i];
        for (int j = i + 1; j < i + half; j++)
        {
          st[offset + j] = func(st[offset + j - 1], b[j]);
        }
      }
    }
  }
  T query(int l, int r) const
  {
    assert(0 <= l && l <= r && r < n);
    if (l == r)
    {
      return st[l];
    }
    int level = 31 - __builtin_clz(l ^ r);
    return func(st[level * sz + l], st[level * sz + r]);
  }
};

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  vector<long long> a = {2, 4, 1, 5, 3};

  // CTAD deduces the types automatically
  DisjointSparseTable dst(a, [&](long long x, long long y)
                          { return x + y; });

  // Query sum of range [1, 3] -> a[1] + a[2] + a[3] -> 4 + 1 + 5 = 10
  cout << dst.query(1, 3) << '\n';

  return 0;
}
