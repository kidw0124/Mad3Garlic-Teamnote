ll inf = 2e18;
struct Line {
  ll a, b;
  ll get(ll x) { return a * x + b; }
};
struct Node {
  int l, r;  // child
  ll s, e;   // range
  Line line;
};
struct Li_Chao {
  vector<Node> tree;
  void init(ll s, ll e) { tree.push_back({-1, -1, s, e, {0, -inf}}); }
  void update(int node, Line v) {
    ll s = tree[node].s, e = tree[node].e, m;
    m = (s + e) >> 1;
    Line low = tree[node].line, high = v;
    if (low.get(s) > high.get(s)) swap(low, high);
    if (low.get(e) <= high.get(e)) {
      tree[node].line = high;
      return;
    }
    if (low.get(m) < high.get(m)) {
      tree[node].line = high;
      if (tree[node].r == -1) {
        tree[node].r = tree.size();
        tree.push_back({-1, -1, m + 1, e, {0, -inf}});
      }
      update(tree[node].r, low);
    } else {
      tree[node].line = low;
      if (tree[node].l == -1) {
        tree[node].l = tree.size();
        tree.push_back({-1, -1, s, m, {0, -inf}});
      }
      update(tree[node].l, high);
    }
  }

  ll query(int node, ll x) {
    if (node == -1) return -inf;
    ll s = tree[node].s, e = tree[node].e, m;
    m = (s + e) >> 1;
    if (x <= m)
      return max(tree[node].line.get(x), query(tree[node].l, x));
    else
      return max(tree[node].line.get(x), query(tree[node].r, x));
  }
};
// usage : seg.init(-2e8, 2e8); seg.update(0, {-c[i], c[i] * a[i - 1]});
// seg.query(0, a[n - 1]);