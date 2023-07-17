// O(ElogV)
vector<ll> dijk(ll n, ll s){
  vector<ll>dis(n,INF);
  priority_queue<pll, vector<pll>, greater<pll> > q; // pair(dist, v)
  dis[s] = 0;
  q.push({dis[s], s});
  while (!q.empty()){
    while (!q.empty() && visit[q.top().second]) q.pop();
    if (q.empty()) break;
    ll next = q.top().second; q.pop();
    visit[next] = 1;
    for (ll i = 0; i < adj[next].size(); i++)
      if (dis[adj[next][i].first] > dis[next] + adj[next][i].second){
        dis[adj[next][i].first] = dis[next] + adj[next][i].second;
        q.push({dis[adj[next][i].first], adj[next][i].first});}}
  for(ll i=0;i<n;i++)if(dis[i]==INF)dis[i]=-1;
  return dis;
}