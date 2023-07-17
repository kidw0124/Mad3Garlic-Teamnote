// O(ElogV)
ll prim() {
  priority_queue<pll, vector<pll>, greater<pll> > q;
  ll count = 0; ll ret = 0;
  q.push(make_pair(0, 0)); // (cost, vertex)
  while (!q.empty()){
    ll x = q.top().second; // also able to get edges
    visit[x] = 1; ret += q.top().first; q.pop(); count++;
    for (ll i = 0; i < adj[x].size(); i++) 
      q.push({adj[x][i].second, adj[x][i].first});
    while (!q.empty() && visit[q.top().second]) q.pop();
  }
  if (count != n) return -1;
  else return ret;
}

ll Kruskal(){
  ll ret = 0;vector<ll>par;
  iota(par.beging(),par.end(),0);
  vector<pair<ll, pll>> e;
  for(ll i= 0; i < n; i++)
    for(ll j=0; j < adj[i].size(); j++)
      e.push_back({adj[i][j].second, {i, adj[i][j].first}});
  sort(e.begin(), e.end());
  for(ll i=0; i < e.size(); i++){
    ll x = e[i].second.first,y = e[i].second.second;
    if(find(x) != find(y)){
      union(x, y);
      ret += e[i].first;
    }
  }
  ll p=find(0);
  for(ll i=1;i<n;i++){
    if(find(i)!=p)return -1;
  }
  else return ret;
}