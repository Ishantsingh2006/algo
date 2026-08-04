#include <vector>
#include <cassert>
#include <utility>
using namespace std;
template <typename node>
class segtree {
public:
    int n;
    vector<node> tree;

    segtree(int _n) : n(_n), tree(2 * n - 1) {
        if (n > 0) build(0, 0, n - 1);
    }
    template <typename M>
    segtree(const vector<M> &v) : n((int)v.size()), tree(2 * n - 1) {
        if (n > 0) build(0, 0, n - 1, v);
    }

    node get(int p) { return get(0, 0, n - 1, p, p); }
    node get(int le, int rr) { return get(0, 0, n - 1, le, rr); }
    
    template <typename... Args>
    void modify(int le, int rr, Args &&...args) { 
        modify(0, 0, n - 1, le, rr, forward<Args>(args)...); 
    }
    template <typename F>
    int find_first(int le, int rr, F f) { 
        return find_first(0, 0, n - 1, le, rr, f); 
    }
    template <typename F>
    int find_last(int le, int rr, F f) { 
        return find_last(0, 0, n - 1, le, rr, f); 
    }

private:
    // Helper macro to calculate mid (y) and right child index (z)
    // Left child is always x + 1 due to the Euler tour flat indexing
    #define MID int y = (l + r) >> 1, z = x + ((y - l + 1) << 1)

    void pull(int x, int z) { tree[x] = node::unite(tree[x + 1], tree[z]); }
    void push(int x, int l, int r) { MID; tree[x].push(tree[x + 1], tree[z], l, r, y); }

    void build(int x, int l, int r) {
        if (l == r) return;
        MID; build(x + 1, l, y); build(z, y + 1, r);
        pull(x, z);
    }
    
    template <typename M>
    void build(int x, int l, int r, const vector<M> &v) {
        if (l == r) return void(tree[x].apply(l, r, v[l]));
        MID; build(x + 1, l, y, v); build(z, y + 1, r, v);
        pull(x, z);
    }

    node get(int x, int l, int r, int le, int rr) {
        if (le <= l && r <= rr) return tree[x];
        MID; push(x, l, r);
        if (rr <= y) return get(x + 1, l, y, le, rr);
        if (le > y) return get(z, y + 1, r, le, rr);
        return node::unite(get(x + 1, l, y, le, rr), get(z, y + 1, r, le, rr));
    }

    template <typename... Args>
    void modify(int x, int l, int r, int le, int rr, Args &&...args) {
        if (le <= l && r <= rr) return void(tree[x].apply(l, r, forward<Args>(args)...));
        MID; push(x, l, r);
        if (le <= y) modify(x + 1, l, y, le, rr, forward<Args>(args)...);
        if (rr > y) modify(z, y + 1, r, le, rr, forward<Args>(args)...);
        pull(x, z);
    }

    template <typename F>
    int find_first(int x, int l, int r, int le, int rr, F f) {
        if (le <= l && r <= rr && !f(tree[x])) return -1;
        if (l == r) return l;
        MID; push(x, l, r);
        int res = (le <= y) ? find_first(x + 1, l, y, le, rr, f) : -1;
        return (res == -1 && rr > y) ? find_first(z, y + 1, r, le, rr, f) : res;
    }

    template <typename F>
    int find_last(int x, int l, int r, int le, int rr, F f) {
        if (le <= l && r <= rr && !f(tree[x])) return -1;
        if (l == r) return l;
        MID; push(x, l, r);
        int res = (rr > y) ? find_last(z, y + 1, r, le, rr, f) : -1;
        return (res == -1 && le <= y) ? find_last(x + 1, l, y, le, rr, f) : res;
    }
    
    #undef MID
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
