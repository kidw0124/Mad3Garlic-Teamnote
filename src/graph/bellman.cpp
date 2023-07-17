// O(VE)
// return pair(negative cycle, distance)
pair<bool,vector<ll>> bellman(ll x){
  bool cycle = 0;
  vector<ll>dis(N,INF);
  dis[x] = 0;
  for (ll i = 0; i < n; i++)
    for (ll j = 0; j < n; j++)
      for (ll k = 0; k < adj[j].size(); k++){
        ll next = adj[j][k].first;
        ll cost = adj[j][k].second;
        if (dis[j] != INF && dis[next] > dis[j] + cost){
          dis[next] = dis[j] + cost;
          if (i == n - 1) cycle = 1;} }
  return {!cycle, dis};
}