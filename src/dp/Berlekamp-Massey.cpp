// Usage: berlekampMassey({0, 1, 1, 3, 5, 11}) // {1, 2}
// Time: O(N^2)
vector<ll> berlekampMassey(vector<ll> s) {
  ll n = s.size(), L = 0, m = 0, d, coef;
  vector<ll> C(n), B(n), T;
  C[0] = B[0] = 1;
  ll b = 1;
  for (ll i = 0; i < n; i++) {
    ++m, d = s[i] % mod;
    for (ll j = 1; j <= L; j++) d = (d + C[j] * s[i - j]) % mod;
    if (!d) continue;
    T = C, coef = d * modpow(b, mod - 2) % mod;
    for (j = m; j < n; j++) C[j] = (C[j] - coef * B[j - m]) % mod;
    if (2 * L > i) continue;
    L = i + 1 - L, B = T, b = d, m = 0;
  }
  C.resize(L + 1), C.erase(C.begin());
  for (ll& x : C) x = (mod - x) % mod;
  return C;
}