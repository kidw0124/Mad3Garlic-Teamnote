int getCent(int id, int v, int p) {  // tree id, vertex, parent
  int ch = 0;
  for (auto i : inp[id][v]) {
    if (p == i) continue;
    int now = getCent(id, i, v);
    if (now > (n / 2)) break;
    ch += now;
  }
  if (n - ch - 1 <= n / 2) cent[id].push_back(v);
  return sz[v] = ch + 1;
}
