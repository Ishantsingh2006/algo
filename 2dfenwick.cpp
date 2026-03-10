#include <vector>
using namespace std;
// 0 indexed
template <typename T>
struct fen2d
{
    int n, m;
    vector<vector<T>> bit;
    fen2d(int n_ = 0, int m_ = 0) : n(n_), m(m_), bit(n_, vector<T>(m_, T{})) {}
    void add(int x, int y, T v)
    {
        for (int i = x; i < n; i |= i + 1)
        {
            for (int j = y; j < m; j |= j + 1)
            {
                bit[i][j] += v;
            }
        }
    }
    //  [0, x) * [0, y)
    T query(int x, int y) const
    {
        T sum{};
        for (int i = x; i > 0; i &= i - 1)
        {
            for (int j = y; j > 0; j &= j - 1)
            {
                sum += bit[i - 1][j - 1];
            }
        }
        return sum;
    }
    //  [x1, x2] * [y1, y2]
    T query(int x1, int x2, int y1, int y2) const
    {
        if (x1 > x2 || y1 > y2)
            return T{};
        return query(x2 + 1, y2 + 1) - query(x1, y2 + 1) - query(x2 + 1, y1) + query(x1, y1);
    }
};
