typedef unsigned long long ull;
const int sz = 100001 / 64 + 1;
struct bset {
  ull x[sz];
  bset(){
    memset(x, 0, sizeof x);
  }
  bset operator|(const bset &o) const {
    bset a;
    for (int i = 0; i < sz; i++)a.x[i] = x[i] | o.x[i];
    return a;
  }
  bset &operator|=(const bset &o) {
    for (int i = 0; i < sz; i++)x[i] |= o.x[i];
    return *this;
  }
  inline void add(int val){
    x[val >> 6] |= (1ull << (val & 63));
  }
  inline void del(int val){
    x[val >> 6] &= ~(1ull << (val & 63));
  }
  int kth(int k){
    int i, cnt = 0;
    for (i = 0; i < sz; i++){
      int c = __builtin_popcountll(x[i]);
      if (cnt + c >= k){
        ull y = x[i];
        int z = 0;
        for (int j = 0; j < 64; j++){
          z += ((x[i] & (1ull << j)) != 0);
          if (cnt + z == k)return i * 64 + j;
        }
      }
      cnt += c;
    }
    return -1;
  }
  int lower(int z){
    int i = (z >> 6), j = (z & 63);
    if (x[i]){
      for (int k = j - 1; k >= 0; k--)if (x[i] & (1ull << k))return (i << 6) | k;
    }
    while (i > 0)
    if (x[--i])
    for (j = 63;; j--)
    if (x[i] & (1ull << j))return (i << 6) | j;
    return -1;
  }
  int upper(int z){
    int i = (z >> 6), j = (z & 63);
    if (x[i]){
      for (int k = j + 1; k <= 63; k++)if (x[i] & (1ull << k))return (i << 6) | k;
    }
    while (i < sz - 1)if (x[++i])for (j = 0;; j++)if (x[i] & (1ull << j))return (i << 6) | j;
    return -1;
  }
};