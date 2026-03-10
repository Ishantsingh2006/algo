#include <vector>
#include <cassert>
#include <utility>
using namespace std;
template <typename node>
class segtree
{
public:
    int n;
    vector<node> tree;
    segtree(int _n) : n(_n)
    {
        assert(n > 0);
        tree.resize(2 * n - 1);
        build(0, 0, n - 1);
    }
    template <typename M>
    segtree(const vector<M> &v) : n((int)v.size())
    {
        assert(n > 0);
        tree.resize(2 * n - 1);
        build(0, 0, n - 1, v);
    }
    node get(int p)
    {
        assert(0 <= p && p < n);
        return get(0, 0, n - 1, p, p);
    }
    node get(int ll, int rr)
    {
        assert(0 <= ll && ll <= rr && rr < n);
        return get(0, 0, n - 1, ll, rr);
    }
    template <typename... Args>
    void modify(int ll, int rr, Args &&...args)
    {
        assert(0 <= ll && ll <= rr && rr < n);
        modify(0, 0, n - 1, ll, rr, forward<Args>(args)...);
    }
    template <typename F>
    int find_first(int ll, int rr, F f)
    {
        assert(0 <= ll && ll <= rr && rr < n);
        return find_first(0, 0, n - 1, ll, rr, f);
    }
    template <typename F>
    int find_last(int ll, int rr, F f)
    {
        assert(0 <= ll && ll <= rr && rr < n);
        return find_last(0, 0, n - 1, ll, rr, f);
    }

private:
    void pull(int x, int z)
    {
        tree[x] = node::unite(tree[x + 1], tree[z]);
    }
    void push(int x, int l, int r)
    {
        int y = (l + r) >> 1;
        int z = x + ((y - l + 1) << 1);
        tree[x].push(tree[x + 1], tree[z], l, r, y);
    }
    void build(int x, int l, int r)
    {
        if (l == r)
            return;
        int y = (l + r) >> 1;
        int z = x + ((y - l + 1) << 1);
        build(x + 1, l, y);
        build(z, y + 1, r);
        pull(x, z);
    }
    template <typename M>
    void build(int x, int l, int r, const vector<M> &v)
    {
        if (l == r)
        {
            tree[x].apply(l, r, v[l]);
            return;
        }
        int y = (l + r) >> 1;
        int z = x + ((y - l + 1) << 1);
        build(x + 1, l, y, v);
        build(z, y + 1, r, v);
        pull(x, z);
    }
    node get(int x, int l, int r, int ll, int rr)
    {
        if (ll <= l && r <= rr)
            return tree[x];
        int y = (l + r) >> 1;
        int z = x + ((y - l + 1) << 1);
        push(x, l, r);
        node res{};
        if (rr <= y)
        {
            res = get(x + 1, l, y, ll, rr);
        }
        else if (ll > y)
        {
            res = get(z, y + 1, r, ll, rr);
        }
        else
        {
            res = node::unite(get(x + 1, l, y, ll, rr), get(z, y + 1, r, ll, rr));
        }
        pull(x, z);
        return res;
    }
    template <typename... Args>
    void modify(int x, int l, int r, int ll, int rr, Args &&...args)
    {
        if (ll <= l && r <= rr)
        {
            tree[x].apply(l, r, forward<Args>(args)...);
            return;
        }
        int y = (l + r) >> 1;
        int z = x + ((y - l + 1) << 1);
        push(x, l, r);
        if (ll <= y)
            modify(x + 1, l, y, ll, rr, forward<Args>(args)...);
        if (rr > y)
            modify(z, y + 1, r, ll, rr, forward<Args>(args)...);
        pull(x, z);
    }
    template <typename F>
    int find_first_knowingly(int x, int l, int r, F f)
    {
        if (l == r)
            return l;
        push(x, l, r);
        int y = (l + r) >> 1;
        int z = x + ((y - l + 1) << 1);
        int res;
        if (f(tree[x + 1]))
        {
            res = find_first_knowingly(x + 1, l, y, f);
        }
        else
        {
            res = find_first_knowingly(z, y + 1, r, f);
        }
        pull(x, z);
        return res;
    }
    template <typename F>
    int find_first(int x, int l, int r, int ll, int rr, F f)
    {
        if (ll <= l && r <= rr)
        {
            if (!f(tree[x]))
                return -1;
            return find_first_knowingly(x, l, r, f);
        }
        push(x, l, r);
        int y = (l + r) >> 1;
        int z = x + ((y - l + 1) << 1);
        int res = -1;
        if (ll <= y)
            res = find_first(x + 1, l, y, ll, rr, f);
        if (rr > y && res == -1)
            res = find_first(z, y + 1, r, ll, rr, f);
        pull(x, z);
        return res;
    }
    template <typename F>
    int find_last_knowingly(int x, int l, int r, F f)
    {
        if (l == r)
            return l;
        push(x, l, r);
        int y = (l + r) >> 1;
        int z = x + ((y - l + 1) << 1);
        int res;
        if (f(tree[z]))
        {
            res = find_last_knowingly(z, y + 1, r, f);
        }
        else
        {
            res = find_last_knowingly(x + 1, l, y, f);
        }
        pull(x, z);
        return res;
    }
    template <typename F>
    int find_last(int x, int l, int r, int ll, int rr, F f)
    {
        if (ll <= l && r <= rr)
        {
            if (!f(tree[x]))
                return -1;
            return find_last_knowingly(x, l, r, f);
        }
        push(x, l, r);
        int y = (l + r) >> 1;
        int z = x + ((y - l + 1) << 1);
        int res = -1;
        if (rr > y)
            res = find_last(z, y + 1, r, ll, rr, f);
        if (ll <= y && res == -1)
            res = find_last(x + 1, l, y, ll, rr, f);
        pull(x, z);
        return res;
    }
};
// Range add and range sum
struct SumNode
{
    long long sum = 0;
    long long lazy = 0;
    static SumNode unite(const SumNode &a, const SumNode &b)
    {
        SumNode res;
        res.sum = a.sum + b.sum;
        return res;
    }
    void apply(int l, int r, long long v)
    {
        sum += v * (r - l + 1);
        lazy += v;
    }
    void push(SumNode &left, SumNode &right, int l, int r, int y)
    {
        if (lazy != 0)
        {
            left.apply(l, y, lazy);
            right.apply(y + 1, r, lazy);
            lazy = 0;
        }
    }
};
// Range set and range max
struct SetMaxNode
{
    long long mx = 0;
    long long lazy = 0;
    bool has_lazy = false; // we might want to set range 0 so we can't check if(lazy!=0), so we use a boolean flag
    static SetMaxNode unite(const SetMaxNode &a, const SetMaxNode &b)
    {
        SetMaxNode res;
        res.mx = std::max(a.mx, b.mx);
        return res;
    }
    void apply(int l, int r, long long v)
    {
        mx = v;
        lazy = v;
        has_lazy = true;
    }
    void push(SetMaxNode &left, SetMaxNode &right, int l, int r, int y)
    {
        if (has_lazy)
        {
            left.apply(l, y, lazy);
            right.apply(y + 1, r, lazy);
            has_lazy = false;
        }
    }
};
// affine transformation (A*x + B) & range sum
struct AffineNode
{
    long long sum = 0;
    long long mul_lazy = 1; // multiplication identity is 1
    long long add_lazy = 0;
    static AffineNode unite(const AffineNode &a, const AffineNode &b)
    {
        AffineNode res;
        res.sum = a.sum + b.sum;
        return res;
    }
    void apply(int l, int r, long long a, long long b)
    {
        sum = sum * a + b * (r - l + 1);
        mul_lazy = mul_lazy * a;
        add_lazy = add_lazy * a + b;
    }
    void push(AffineNode &left, AffineNode &right, int l, int r, int y)
    {
        if (mul_lazy != 1 || add_lazy != 0)
        {
            left.apply(l, y, mul_lazy, add_lazy);
            right.apply(y + 1, r, mul_lazy, add_lazy);
            mul_lazy = 1;
            add_lazy = 0;
        }
    }
};
