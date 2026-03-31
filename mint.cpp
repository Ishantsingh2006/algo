#include <bits/stdc++.h>
using namespace std;
template <int MOD>
struct Mint
{
    int val;

private:
    static long long extended_gcd(long long a, long long b, long long &x, long long &y)
    {
        if (b == 0)
        {
            x = 1;
            y = 0;
            return a;
        }
        long long x1, y1;
        long long d = extended_gcd(b, a % b, x1, y1);
        x = y1;
        y = x1 - y1 * (a / b);
        return d;
    }
    static long long mod_inverse(long long a, long long m)
    {
        long long x, y;
        long long g = extended_gcd(a, m, x, y);
        assert(g == 1);
        (void)g;
        return (x % m + m) % m;
    }
    static int normalize(long long x)
    {
        int v;
        if (-MOD <= x && x < MOD)
            v = static_cast<int>(x);
        else
            v = static_cast<int>(x % MOD);
        if (v < 0)
            v += MOD;
        return v;
    }

public:
    Mint(long long v = 0) { val = normalize(v); }
    static Mint raw(int v)
    {
        Mint m;
        m.val = v;
        return m;
    }
    static constexpr int mod() { return MOD; }
    Mint inv() const
    {
        return Mint::raw(mod_inverse(val, MOD));
    }
    Mint pow(long long p) const
    {
        assert(p >= 0);
        Mint res = 1, a = *this;
        while (p > 0)
        {
            if (p & 1)
                res *= a;
            a *= a;
            p >>= 1;
        }
        return res;
    }
    Mint operator+() const { return *this; }
    Mint operator-() const { return Mint(0) - *this; }
    Mint &operator++()
    {
        val++;
        if (val == MOD)
            val = 0;
        return *this;
    }
    Mint &operator--()
    {
        if (val == 0)
            val = MOD;
        val--;
        return *this;
    }
    Mint operator++(int)
    {
        Mint temp = *this;
        ++*this;
        return temp;
    }
    Mint operator--(int)
    {
        Mint temp = *this;
        --*this;
        return temp;
    }
    Mint &operator+=(const Mint &other)
    {
        val += other.val;
        if (val >= MOD)
            val -= MOD;
        return *this;
    }
    Mint &operator-=(const Mint &other)
    {
        val -= other.val;
        if (val < 0)
            val += MOD;
        return *this;
    }
    Mint &operator*=(const Mint &other)
    {
        val = (1LL * val * other.val) % MOD;
        return *this;
    }
    Mint &operator/=(const Mint &other)
    {
        *this *= other.inv();
        return *this;
    }
    template <typename U>
    Mint &operator+=(const U &other) { return *this += Mint(other); }
    template <typename U>
    Mint &operator-=(const U &other) { return *this -= Mint(other); }
    template <typename U>
    Mint &operator*=(const U &other) { return *this *= Mint(other); }
    template <typename U>
    Mint &operator/=(const U &other) { return *this /= Mint(other); }
    friend Mint operator+(const Mint &a, const Mint &b) { return Mint(a) += b; }
    friend Mint operator-(const Mint &a, const Mint &b) { return Mint(a) -= b; }
    friend Mint operator*(const Mint &a, const Mint &b) { return Mint(a) *= b; }
    friend Mint operator/(const Mint &a, const Mint &b) { return Mint(a) /= b; }
    template <typename U>
    friend Mint operator+(const Mint &a, U b) { return Mint(a) += Mint(b); }
    template <typename U>
    friend Mint operator-(const Mint &a, U b) { return Mint(a) -= Mint(b); }
    template <typename U>
    friend Mint operator*(const Mint &a, U b) { return Mint(a) *= Mint(b); }
    template <typename U>
    friend Mint operator/(const Mint &a, U b) { return Mint(a) /= Mint(b); }
    template <typename U>
    friend Mint operator+(U a, const Mint &b) { return Mint(a) += b; }
    template <typename U>
    friend Mint operator-(U a, const Mint &b) { return Mint(a) -= b; }
    template <typename U>
    friend Mint operator*(U a, const Mint &b) { return Mint(a) *= b; }
    template <typename U>
    friend Mint operator/(U a, const Mint &b) { return Mint(a) /= b; }
    friend bool operator==(const Mint &a, const Mint &b) { return a.val == b.val; }
    friend bool operator!=(const Mint &a, const Mint &b) { return a.val != b.val; }
    template <typename U>
    friend bool operator==(const Mint &a, U b) { return a == Mint(b); }
    template <typename U>
    friend bool operator!=(const Mint &a, U b) { return a != Mint(b); }
    template <typename U>
    friend bool operator==(U a, const Mint &b) { return Mint(a) == b; }
    template <typename U>
    friend bool operator!=(U a, const Mint &b) { return Mint(a) != b; }
    friend ostream &operator<<(ostream &os, const Mint &m)
    {
        os << m.val;
        return os;
    }
    friend istream &operator>>(istream &is, Mint &m)
    {
        long long v;
        is >> v;
        m.val = normalize(v);
        return is;
    }
};
template <int MOD>
Mint<MOD> power(const Mint<MOD> &a, long long b)
{
    return a.pow(b);
}
using mint = Mint<998244353>; // Mint<1000000007>;
int MAXN = 1e5;
struct comb
{
    vector<mint> fact, invFact;
    comb()
    {
        fact.assign(MAXN + 1, 1);
        invFact.assign(MAXN + 1, 1);
        for (int i = 1; i <= MAXN; i++)
        {
            fact[i] = fact[i - 1] * i;
        }
        invFact[MAXN] = fact[MAXN].inv();
        for (int i = MAXN - 1; i >= 0; i--)
        {
            invFact[i] = invFact[i + 1] * (i + 1);
        }
    }
    mint nCr(int n, int r) const
    {
        if (r < 0 || r > n)
            return 0;
        return fact[n] * invFact[r] * invFact[n - r];
    }
    mint nPr(int n, int r) const
    {
        if (r < 0 || r > n)
            return 0;
        return fact[n] * invFact[n - r];
    }
};
