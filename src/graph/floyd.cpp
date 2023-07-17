// O(V^3)
// return pair(negative cycle, distance)
pair<bool,vector<vector<ll>>> floyd(){
  bool cycle = 0;
  vector<vector<ll>>dis(n,INF);
  for (ll i = 0; i < n; i++) dis[i][i] = 0;
  for (ll k = 0; k < n; k++)
    for (ll i = 0; i < n; i++)
      for (ll j = 0; j < n; j++)
        dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
  for (ll k = 0; k < n; k++) // Check negative cycle
    for (ll i = 0; i < n; i++)
      for (ll j = 0; j < n; j++)
        if (dis[i][j] > dis[i][k] + dis[k][j]) cycle = 1;
  return {!cycle, dis};
}
