struct Fenwick {
  const ll MAXN = 100000;
  vector<ll> tree;
  Fenwick(ll sz) : tree(sz + 1) {}
  Fenwick() : Fenwick(MAXN) {}
  ll query(ll p) {  // sum from index 1 to p, inclusive
    ll ret = 0;
    for (; p > 0; p -= p & -p) ret += tree[p];
    return ret;
  }
  void add(ll p, ll val) {
    for (; p <= TSIZE; p += p & -p) tree[p] += val;
  }
};
