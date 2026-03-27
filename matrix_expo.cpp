#include <vector>
#include <cassert>
using namespace std;
const long long MOD = 1e9 + 7;
template <typename T>
struct Matrix
{
    int r, c;
    vector<vector<T>> m;
    Matrix(int r, int c, T v = 0) : r(r), c(c), m(r, vector<T>(c, v)) {}
    Matrix(const vector<vector<T>> &v) : r(v.size()), c(v.empty() ? 0 : v[0].size()), m(v) {}
    vector<T> &operator[](int i) { return m[i]; }
    const vector<T> &operator[](int i) const { return m[i]; }
    Matrix operator+(const Matrix &B) const
    {
        assert(r == B.r && c == B.c);
        Matrix R(r, c);
        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < c; j++)
            {
                R[i][j] = m[i][j] + B[i][j];
                if (R[i][j] >= MOD)
                    R[i][j] -= MOD;
            }
        }
        return R;
    }
    Matrix operator*(const Matrix &B) const
    {
        assert(c == B.r);
        Matrix R(r, B.c, 0);
        for (int i = 0; i < r; i++)
        {
            for (int k = 0; k < c; k++)
            {
                if (m[i][k] == 0)
                    continue;
                for (int j = 0; j < B.c; j++)
                {
                    R[i][j] = (R[i][j] + m[i][k] * B[k][j]) % MOD;
                }
            }
        }
        return R;
    }
    Matrix &operator+=(const Matrix &B) { return *this = *this + B; }
    Matrix &operator*=(const Matrix &B) { return *this = *this * B; }
    static Matrix eye(int n)
    {
        Matrix R(n, n, 0);
        for (int i = 0; i < n; i++)
        {
            R[i][i] = 1;
        }
        return R;
    }
    Matrix pow(long long p) const
    {
        assert(r == c);
        Matrix R = eye(r);
        Matrix A = *this;
        while (p > 0)
        {
            if (p & 1)
                R *= A;
            A *= A;
            p >>= 1;
        }
        return R;
    }
};
