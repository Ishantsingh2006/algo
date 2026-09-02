#include <bits/stdc++.h>
using namespace std;
#include <cassert>
template <int MOD> struct Mint {
  int val;
  Mint(long long v = 0) {
    if (-MOD <= v && v < MOD)
      val = v;
    else
      val = v % MOD;
    if (val < 0)
      val += MOD;
  }
  static Mint raw(int v) {
    Mint m;
    m.val = v;
    return m;
  }

  Mint inv() const {
    long long a = val, b = MOD, x = 1, u = 0;
    while (b) {
      long long q = a / b;
      a -= q * b;
      swap(a, b);
      x -= q * u;
      swap(x, u);
    }
    assert(a == 1);
    return raw((x % MOD + MOD) % MOD);
  }
  Mint pow(long long p) const {
    assert(p >= 0);
    Mint res = 1, a = *this;
    for (; p > 0; p >>= 1, a *= a)
      if (p & 1)
        res *= a;
    return res;
  }
  Mint operator-() const { return Mint() - *this; }
  Mint &operator++() {
    if (++val == MOD)
      val = 0;
    return *this;
  }
  Mint &operator--() {
    if (val-- == 0)
      val = MOD - 1;
    return *this;
  }
  Mint operator++(int) {
    Mint t = *this;
    ++*this;
    return t;
  }
  Mint operator--(int) {
    Mint t = *this;
    --*this;
    return t;
  }

  Mint &operator+=(const Mint &o) {
    if ((val += o.val) >= MOD)
      val -= MOD;
    return *this;
  }
  Mint &operator-=(const Mint &o) {
    if ((val -= o.val) < 0)
      val += MOD;
    return *this;
  }
  Mint &operator*=(const Mint &o) {
    val = (1LL * val * o.val) % MOD;
    return *this;
  }
  Mint &operator/=(const Mint &o) { return *this *= o.inv(); }

  friend Mint operator+(Mint a, const Mint &b) { return a += b; }
  friend Mint operator-(Mint a, const Mint &b) { return a -= b; }
  friend Mint operator*(Mint a, const Mint &b) { return a *= b; }
  friend Mint operator/(Mint a, const Mint &b) { return a /= b; }
  friend bool operator==(const Mint &a, const Mint &b) {
    return a.val == b.val;
  }
  friend bool operator!=(const Mint &a, const Mint &b) {
    return a.val != b.val;
  }
  friend ostream &operator<<(ostream &os, const Mint &m) { return os << m.val; }
  friend istream &operator>>(istream &is, Mint &m) {
    long long v;
    is >> v;
    m = Mint(v);
    return is;
  }
};

using mint = Mint<998244353>; // Mint<1000000007>

struct comb {
  vector<mint> fact, invfact;
  comb(int n) : fact(n + 1, 1), invfact(n + 1, 1) {
    for (int i = 1; i <= n; i++)
      fact[i] = fact[i - 1] * i;
    invfact[n] = fact[n].inv();
    for (int i = n; i >= 1; i--)
      invfact[i - 1] = invfact[i] * i;
  }
  mint nCr(int n, int r) const {
    return r < 0 || r > n ? 0 : fact[n] * invfact[r] * invfact[n - r];
  }
  mint nPr(int n, int r) const {
    return r < 0 || r > n ? 0 : fact[n] * invfact[n - r];
  }
};
