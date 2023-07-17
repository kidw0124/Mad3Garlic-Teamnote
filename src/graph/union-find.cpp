// O(logn)
vector<ll> par;
iota(par.begin(),par.end(),0);
ll find(ll x){
  if(p[x]==x) return x;
  return p[x] = find(p[x]);
}
void union(ll x, ll y){
  p[find(y)]=find(x);
  find(y);
}