// usage :
// update(y, z, 1, 1, n);
// query(y, z, 1, 1, n).resval
ll n, m, x, y, z, i, trash = 1e9 + 1;
struct segnode{
  ll maxval, minval, resval;
}seg[4000000];
void update(ll pos, ll val, ll node, ll x, ll y){
  if (pos < x || y < pos)return;
  if (x == y) {
    seg[node].maxval = val;seg[node].minval = val;seg[node].resval = 0;return;
  }
  ll mid = (x + y) >> 1;
  update(pos, val, node * 2, x, mid);
  update(pos, val, node * 2 + 1, mid + 1, y);
  seg[node].maxval = max(seg[node * 2].maxval, seg[node * 2 + 1].maxval);
  seg[node].minval = min(seg[node * 2].minval, seg[node * 2 + 1].minval);
  seg[node].resval = max(max(seg[node * 2].resval, seg[node * 2 + 1].resval), seg[node * 2 + 1].maxval - seg[node * 2].minval);
  return;
}
segnode query(ll lo, ll hi, ll node, ll x, ll y){
  if (y < lo || hi < x) {
    segnode notin;
    notin.maxval = -trash; notin.minval = trash;notin.resval = -trash;return notin;
  }
  if (lo <= x && y <= hi)return seg[node];
  ll mid = (x + y) >> 1;
  segnode left = query(lo, hi, node * 2, x, mid);
  segnode right = query(lo, hi, node * 2 + 1, mid + 1, y);
  segnode toreturn;
  toreturn.maxval = max(left.maxval, right.maxval);
  toreturn.minval = min(left.minval, right.minval);
  toreturn.resval = max(max(left.resval, right.resval), right.maxval - left.minval);
  return toreturn;
}