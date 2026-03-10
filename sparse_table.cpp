#include <vector>
#include <cassert>
#include <bit>
using namespace std;
template <typename T, class F>
class sparsetable
{
public:
    int n;
    vector<vector<T>> st;
    F func;
    sparsetable(const vector<T> &a, const F &f) : n(a.size()), func(f)
    {
        assert(n > 0);
        int max_log = std::bit_width((unsigned)n);
        st.assign(max_log, vector<T>(n));
        st[0] = a;
        for (int k = 1; k < max_log; ++k)
        {
            for (int i = 0; i + (1 << k) <= n; ++i)
            {
                st[k][i] = func(st[k - 1][i], st[k - 1][i + (1 << (k - 1))]);
            }
        }
    }
    T query(int L, int R) const
    {
        assert(0 <= L && L <= R && R < n);
        int k = std::bit_width((unsigned)(R - L + 1)) - 1;
        return func(st[k][L], st[k][R - (1 << k) + 1]);
    }
};
