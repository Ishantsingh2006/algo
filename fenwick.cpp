#include <vector>
using namespace std;
template <typename T>
// 0 indexed
struct fenwick
{
    int n;
    vector<T> bit;
    fenwick(int n_ = 0) : n(n_), bit(n_, T{}) {}
    void add(int x, T v)
    {
        for (; x < n; x |= x + 1)
        {
            bit[x] += v;
        }
    }
    // [0, x)
    T query(int x) const
    {
        T sum{};
        for (; x > 0; x &= x - 1)
        {
            sum += bit[x - 1];
        }
        return sum;
    }
    // [l, r]
    T query(int l, int r) const
    {
        if (l > r)
            return T{};
        return query(r + 1) - query(l);
    }
    int lower_bound(T v) const
    {
        int at = 0;
        T sum{};
        for (int len = 63 - __builtin_clzll(n); len > 0; len >>= 1)
        {
            if (at + len <= n && sum + bit[at + len - 1] < v) // change < to <=v for upper_bound
            {
                sum += bit[at + len - 1];
                at += len;
            }
        }
        return at;
    }
};
