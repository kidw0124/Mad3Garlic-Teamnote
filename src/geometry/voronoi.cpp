typedef pair<ld, ld> pdd;
const ld EPS = 1e-12;
ll dcmp(ld x){ return x < -EPS? -1 : x > EPS ? 1 : 0; }
ld operator / (pdd a, pdd b){ return a.first * b.second - a.second * b.first; }
pdd operator * (ld b, pdd a){ return pdd(b * a.first, b * a.second); }
pdd operator + (pdd a,pdd b){ return pdd(a.first + b.first, a.second + b.second); }
pdd operator - (pdd a,pdd b){ return pdd(a.first - b.first, a.second - b.second); }
ld sq(ld x){ return x*x; }
ld size(pdd p){ return hypot(p.first, p.second); }
ld sz2(pdd p){ return sq(p.first) + sq(p.second); }
pdd r90(pdd p){ return pdd(-p.second, p.first); }
pdd inter(pdd a, pdd b, pdd u, pdd v){ return u+(((a-u)/b)/(v/b))*v; }
pdd get_circumcenter(pdd p0, pdd p1, pdd p2){ 
  return inter(0.5*(p0+p1), r90(p0-p1), 0.5*(p1+p2), r90(p1-p2)); }
ld pb_int(pdd left, pdd right, ld sweepline){
  if(dcmp(left.second-right.second) == 0) return (left.first + right.first) / 2.0;
  ll sign = left.second < right.second ? -1 : 1;
  pdd v = inter(left, right-left, pdd(0, sweepline), pdd(1, 0));
  ld d1 = sz2(0.5 * (left+right) - v), d2 = sz2(0.5 * (left-right));
  return v.first + sign * sqrt(max(0.0, d1 - d2)); }
class Beachline{
  public:
    struct node{
      node(){}
      node(pdd point, ll idx):point(point), idx(idx), end(0), 
        link{0, 0}, par(0), prv(0), nxt(0) {}
      pdd point; ll idx; ll end;
      node *link[2], *par, *prv, *nxt;
    };
    node *root;
    ld sweepline;
    Beachline() : sweepline(-1e20), root(NULL){ }
    inline ll dir(node *x){ return x->par->link[0] != x; }
    void rotate(node *n){
      node *p = n->par; ll d = dir(n); p->link[d] = n->link[!d];
      if(n->link[!d]) n->link[!d]->par = p; n->par = p->par;
      if(p->par) p->par->link[dir(p)] = n; n->link[!d] = p; p->par = n;
    } void splay(node *x, node *f = NULL){
      while(x->par != f){
        if(x->par->par == f);
        else if(dir(x) == dir(x->par)) rotate(x->par);
        else rotate(x);
        rotate(x);
      }
      if(f == NULL) root = x;
    } void insert(node *n, node *p, ll d){
      splay(p); node* c = p->link[d];
      n->link[d] = c; if(c) c->par = n; p->link[d] = n; n->par = p;
      node *prv = !d?p->prv:p, *nxt = !d?p:p->nxt;
      n->prv = prv; if(prv) prv->nxt = n; n->nxt = nxt; if(nxt) nxt->prv = n;
    } void erase(node* n){
      node *prv = n->prv, *nxt = n->nxt;
      if(!prv && !nxt){ if(n == root) root = NULL; return; }
      n->prv = NULL;   if(prv) prv->nxt = nxt;
      n->nxt = NULL;   if(nxt) nxt->prv = prv;
      splay(n);
      if(!nxt){
        root->par = NULL; n->link[0] = NULL;
        root = prv;
      }
      else{
        splay(nxt, n);     node* c = n->link[0];
        nxt->link[0] = c; c->par = nxt; n->link[0] = NULL;
        n->link[1] = NULL; nxt->par = NULL; root = nxt;
      }
    } bool get_event(node* cur, ld &next_sweep){
      if(!cur->prv || !cur->nxt) return false;
      pdd u = r90(cur->point - cur->prv->point);
      pdd v = r90(cur->nxt->point - cur->point);
      if(dcmp(u/v) != 1) return false;
      pdd p = get_circumcenter(cur->point, cur->prv->point, cur->nxt->point);
      next_sweep = p.second + size(p - cur->point); return true;
    } node* find_bl(ld x){
      node* cur = root;
      while(cur){
        ld left = cur->prv ? pb_int(cur->prv->point, cur->point, sweepline) : -1e30;
        ld right = cur->nxt ? pb_int(cur->point, cur->nxt->point, sweepline) : 1e30;
        if(left <= x && x <= right){ splay(cur); return cur; }
        cur = cur->link[x > right];
      }
    }
};
using BNode = Beachline::node; static BNode* arr; static ll sz;
static BNode* new_node(pdd point, ll idx){
  arr[sz] = BNode(point, idx); return arr + (sz++); }
struct event{
  event(ld sweep, ll idx):type(0), sweep(sweep), idx(idx){}
  event(ld sweep, BNode* cur):type(1), sweep(sweep), prv(cur->prv->idx), cur(cur), nxt(cur->nxt->idx){}
  ll type, idx, prv, nxt;
  BNode* cur;
  ld sweep;
  bool operator>(const event &l)const{ return sweep > l.sweep; }
};
void Voronoi(vector<pdd> &input, vector<pdd> &vertex, vector<pll> &edge, vector<pll> &area){
  Beachline bl = Beachline();
  priority_queue<event, vector<event>, greater<event>> events;
  auto add_edge = [&](ll u, ll v, ll a, ll b, BNode* c1, BNode* c2){
    if(c1) c1->end = edge.size()*2;
    if(c2) c2->end = edge.size()*2 + 1;
    edge.emplace_back(u, v);
    area.emplace_back(a, b);
  };
  auto write_edge = [&](ll idx, ll v){ idx%2 == 0 ? edge[idx/2].first = v : edge[idx/2].second = v; };
  auto add_event = [&](BNode* cur){ ld nxt; if(bl.get_event(cur, nxt)) events.emplace(nxt, cur); };
  ll n = input.size(), cnt = 0;
  arr = new BNode[n*4]; sz = 0;
  sort(input.begin(), input.end(), [](const pdd &l, const pdd &r){
    return l.second != r.second ? l.second < r.second : l.first < r.first; });
  BNode* tmp = bl.root = new_node(input[0], 0), *t2;
  for(ll i = 1; i < n; i++){
    if(dcmp(input[i].second - input[0].second) == 0){
      add_edge(-1, -1, i-1, i, 0, tmp);
      bl.insert(t2 = new_node(input[i], i), tmp, 1);
      tmp = t2;
    }
    else events.emplace(input[i].second, i);
  }
  while(events.size()){
    event q = events.top(); events.pop();
    BNode *prv, *cur, *nxt, *site;
    ll v = vertex.size(), idx = q.idx;
    bl.sweepline = q.sweep;
    if(q.type == 0){
      pdd point = input[idx];
      cur = bl.find_bl(point.first);
      bl.insert(site = new_node(point, idx), cur, 0);
      bl.insert(prv = new_node(cur->point, cur->idx), site, 0);
      add_edge(-1, -1, cur->idx, idx, site, prv);
      add_event(prv); add_event(cur);
    }
    else{
      cur = q.cur, prv = cur->prv, nxt = cur->nxt;
      if(!prv || !nxt || prv->idx != q.prv || nxt->idx != q.nxt) continue;
      vertex.push_back(get_circumcenter(prv->point, nxt->point, cur->point));
      write_edge(prv->end, v); write_edge(cur->end, v);
      add_edge(v, -1, prv->idx, nxt->idx, 0, prv);
      bl.erase(cur);
      add_event(prv); add_event(nxt);
    }
  }
  delete arr;
}