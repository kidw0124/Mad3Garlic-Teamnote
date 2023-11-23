struct ONDC{
  // usage:
  // 1. connEdge(a, b, 0) : add edge (a, b) -> O(lg n)
  // 2. disconn(a, b) : remove edge (a, b) -> O(lg^2 n)
  // 3. qry(a, b, 0) : check if (a, b) is connected in level 0 -> O(lg n)
  struct node
  {
      node* p, *l, *r, *mn;
      int a, b, size;
      bool f;
      node() : p(nullptr), l(nullptr), r(nullptr), mn(nullptr), a(0), b(0), size(0), f(false) {};
  };
  
  struct edge
  {
      int a, b, k;
      edge() : a(0), b(0), k(0) {};
      edge(int a, int b, int k) : a(a), b(b), k(k) {};
      bool operator<(const edge& r) const {
          if (a != r.a) return a < r.a;
          if (b != r.b) return b < r.b;
          return k < r.k;
      }
  };
  
  map<edge, node*> mp;
  map<pair<int, int>, int> lv;
  map<int, int> vi[20][100009];
  vector<pair<int, int> > v[20][100009];
  int deg[20][100009];
  
  void update(node* x)
  {
      x->size = 1; x->mn = nullptr;
      if (x->f) x->mn = x;
      if (x->l) x->size += x->l->size;
      if (x->r) x->size += x->r->size;
  
      if (x->r && x->r->mn && !(x->f)) x->mn = x->r->mn;
      if (x->l && x->l->mn) x->mn = x->l->mn;
  }
  
  void rotate(node* x)
  {
      if (!x->p) return;
      node* p = x->p, *b;
      if (p->l == x) {
          p->l = b = x->r;
          x->r = p;
      }
      else {
          p->r = b = x->l;
          x->l = p;
      }
      x->p = p->p;
      p->p = x;
      if (b) b->p = p;
      if (x->p) {
          if (x->p->l == p)
              x->p->l = x;
          else
              x->p->r = x;
      }
      update(p); update(x);
  }
  
  void splay(node* x)
  {
      while (x->p) {
          node* p = x->p, *g = p->p;
          if (g) {
              if ((x == p->l) == (p == g->l)) rotate(p);
              else rotate(x);
          }
          rotate(x);
      }
  }
  
  void flagUp(int a, int b, int k, bool f) 
  {
      node* x = mp[edge(a, b, k)];
      splay(x);
      x->f = f;
      update(x);
  }
  
  void addR(node* x, node* t) //Splay tree의 가장 오른쪽에 수 추가
  {
      while (x->r) {
          x->size++;
          if (t->f && !x->mn)
              x->mn = t;
          x = x->r;
      }
      x->size++;
      if (t->f && !x->mn)
          x->mn = t;
      x->r = t;
      t->p = x;
      splay(t);
  }
  
  void join(node* a, node* b) //두 Splay tree를 연결
  {
      while (a->r) a = a->r;
      splay(a);
      a->r = b; b->p = a;
      update(a);
  }
  
  int qry(int a, int b, int k) //레벨 k의 그래프에서 a, b의 연결성 판별  with O(lgn)
  {
      if (mp.find(edge(a, a, k)) == mp.end() || mp.find(edge(b, b, k)) == mp.end()) return 0;
      node* na = mp[edge(a, a, k)], *nb = mp[edge(b, b, k)];
      splay(na);
      node* x = nb;
      while (x->p) x = x->p;
      splay(nb);
      if (x == na) return 1;
      else return 0;
  }
  
  void reroot(int a, int k) //레벨 k의 그래프에서 a를 Euler Tour의 루트로 만듦
  {
      node* n = mp[edge(a, a, k)];
      splay(n);
      node* tl = n->l, *tr = n->r;
      if (!tl || !tr) return;
      n->l = nullptr; n->r = nullptr; n->mn = nullptr; n->size = 1;
      if (n->f) n->mn = n;
      tl->p = nullptr; tr->p = nullptr;
      join(tr, tl);
      addR(tl->p, n);
  }
  
  void conn(int a, int b, int k) // 레벨 k의 포레스트에 간선 (a, b) 추가
  {                                    
      if (qry(a, b, k)) return;
      if (mp.find(edge(a, a, k)) == mp.end()) {
          node* t = new node();
          t->size = 1; t->a = a; t->b = a;
          mp[edge(a, a, k)] = t;
      }
      if (mp.find(edge(b, b, k)) == mp.end()) {
          node* t = new node();
          t->size = 1; t->a = b; t->b = b;
          mp[edge(b, b, k)] = t;
      }
      node* na = mp[edge(a, a, k)], *nb = mp[edge(b, b, k)];
      reroot(a, k); reroot(b, k);
      splay(na); splay(nb);
      node* x = new node(), *y = new node();
      x->size = y->size = 1;
      x->a = a; x->b = b;
      y->a = b; y->b = a;
      addR(na, x);
      join(x, nb);
      addR(x, y);
      mp[edge(a, b, k)] = x;
      mp[edge(b, a, k)] = y;
  }
  
  void connEdge(int a, int b, int k) //레벨 k의 그래프에서 간선 (a, b) 연결 with O(lgn)
  {
      if (qry(a, b, k)) {
          v[k][a].push_back(make_pair(b, v[k][b].size()));
          v[k][b].push_back(make_pair(a, (int)v[k][a].size() - 1));
          vi[k][a][b] = (int)v[k][b].size() - 1;
          vi[k][b][a] = (int)v[k][a].size() - 1;
          deg[k][a]++; deg[k][b]++;
          if (deg[k][a] == 1) flagUp(a, a, k, true);
          if (deg[k][b] == 1) flagUp(b, b, k, true);
      }
      else {
          conn(a, b, k);
          flagUp(a, b, k, true);
          flagUp(b, a, k, true);
      }
      lv[make_pair(a, b)] = k; lv[make_pair(b, a)] = k;
  }
  
  void disconn(int a, int b, int k) //레벨 k의 포레스트에서 간선 (a, b) 제거
  {
      if (mp.find(edge(a, b, k)) == mp.end()) return;
      node* x = mp[edge(a, b, k)], *y = mp[edge(b, a, k)];
      splay(x);
      node* tl = x->l, *tr = x->r;
      if (tl) tl->p = nullptr;
      if (tr) tr->p = nullptr;
      splay(y);
      bool f = (tl && (tl == y || tl->p));
      if (y->l) y->l->p = nullptr;
      if (y->r) y->r->p = nullptr;
      if (f) {
          if (y->l && tr)
              join(y->l, tr);
      }
      else {
          if (y->r && tl)
              join(tl, y->r);
      }
      x->l = x->r = x->p = x->mn = y->l = y->r = y->p = y->mn = nullptr;
      mp.erase(edge(a, b, k)); mp.erase(edge(b, a, k));
      delete x; delete y;
  }
  
  void disconn(int a, int b) //간선 (a, b) 제거 with O(lg^2 n)
  {
      if (lv.find(make_pair(a, b)) == lv.end()) return;
      int lp = lv[make_pair(a, b)];
      if (mp.find(edge(a, b, lp)) == mp.end()) { //포레스트에 포함되지 않은 간선일 경우
          v[lp][a][vi[lp][b][a]].first = 0; v[lp][b][vi[lp][a][b]].first = 0;
          deg[lp][a]--; deg[lp][b]--;
          if (!deg[lp][a]) flagUp(a, a, lp, false);
          if (!deg[lp][b]) flagUp(b, b, lp, false);
      }
      int rpa = 0, rpb = 0;
      for (int k = lp; k >= 0; k--) {
          disconn(a, b, k);
          if (qry(a, b, k)) continue;
          if (rpa) {
              conn(rpa, rpb, k);
              continue;
          }
          node* na = mp[edge(a, a, k)], *nb = mp[edge(b, b, k)];
          splay(na); splay(nb);
          if (na->size > nb->size)
              swap(na, nb);
          node* x = na->mn;
          while (x) { //작은 트리의 간선 레벨 증가
              int p = x->a, q = x->b;
              if (p > q) {
                  connEdge(p, q, k + 1);
                  flagUp(p, q, k, false);
                  flagUp(q, p, k, false);
              }
              splay(x);
              if (!x->r) x = nullptr;
              else x = x->r->mn;
          }
          splay(na);
          x = na->mn;
          while (x && !rpa) { //대체 간선 탐색
              int n = x->a;
              while (!v[k][n].empty() && !rpa) {
                  int tn = v[k][n].back().first;
                  if (tn) {
                      if (qry(n, tn, k))
                          connEdge(n, tn, k + 1);
                      else { //대체 간선 발견
                          rpa = n; rpb = tn;
                          conn(n, tn, k);
                          flagUp(n, tn, k, true);
                          flagUp(tn, n, k, true);
                      }
                      v[k][tn][v[k][n].back().second].first = 0;
                      deg[k][n]--; deg[k][tn]--;
                      if (!deg[k][n]) flagUp(n, n, k, false);
                      if (!deg[k][tn]) flagUp(tn, tn, k, false);
                  }
                  v[k][n].pop_back();
              }
              splay(x);
              if (!x->r) x = nullptr;
              else x = x->r->mn;
          }
      }
      lv.erase(make_pair(a, b)); lv.erase(make_pair(b, a));
  }
};