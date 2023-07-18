int get_siz(int v, int p = -1) {
  siz[v] = 1;
  for (auto [nxt, w] : g[v])
    if (ok(nxt)) siz[v] += get_siz(nxt, v);
  return siz[v];
}
int get_cent(int v, int p, int S) {
  for (auto [nxt, w] : g[v])
    if (ok(nxt) && siz[nxt] * 2 > S) return get_cent(nxt, v, S);
  return v;
}
void dfs(int v, int p, int depth, int len, vector<pii>& t) {
  if (len > k) return;
  t.eb(depth, len);
  for (auto [nxt, w] : g[v])
    if (ok(nxt)) dfs(nxt, v, depth + 1, len + w, t);
}
void dnc(int v) {
  int cent = get_cent(v, -1, get_siz(v));
  vector<pii> t;
  vector<int> reset;
  for (auto [nxt, w] : g[cent]) {
    if (vis[nxt]) continue;
    t.clear();
    dfs(nxt, cent, 1, w, t);
    for (auto [d, l] : t) ans = min(ans, A[k - l] + d);
    for (auto [d, l] : t) {
      if (d < A[l]) {
        A[l] = d;
        reset.pb(l);
      }
    }
  }
  for (auto l : reset) A[l] = inf;
  vis[cent] = 1;
  for (auto [nxt, w] : g[cent])
    if (!vis[nxt]) dnc(nxt);
}
void solve() {
  cin >> n >> k;
  for (int i = 1; i <= k; i++) A[i] = inf;
  rep(i, n - 1) {
    int a, b, w;
    cin >> a >> b >> w;
    g[a].eb(b, w);
    g[b].eb(a, w);
  }
  dnc(0);
  if (ans == inf) ans = -1;
  cout << ans << nl;
}
