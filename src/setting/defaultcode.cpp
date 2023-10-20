#include<bits/stdc++.h>
#pragma GCC optimize ("O3,unroll-loops")
#pragma GCC target ("avx,avx2,fma")
using namespace std;
using ll=long long;
using ull=unsigned long long;
using LL=__int128_t;
using ULL=__uint128_t;
using ld=long double;
using pll = pair<ll,ll>;

#ifdef kidw0124
constexpr bool ddebug = true;
#else
constexpr bool ddebug = false;
#endif

#define debug if(ddebug)cout<<"[DEBUG] "
#define debugv(x) if(ddebug)cout<<"[DEBUG] "<<#x<<" = "<<x<<'\n'
#define debugc(x) if(ddebug)cout<<"[DEBUG] "<<#x<<" = [";for(auto i:x)cout<<i<<' ';cout<<"]\n"
#define all(v) (v).begin(),(v).end()

ll gcd(ll a, ll b){return b?gcd(b,a%b):a;}
ll lcm(ll a, ll b){if(a&&b)return a*(b/gcd(a,b)); return a+b;}
ll powm(ll a, ll b, ll m){ll p=1;for(;b;b/=2,a=(a*a)%m)if(b&1)p=(p*a)%m;return p;}

void setup(){
  if(ddebug){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  }else{
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
  }
}

void preprocess(){
}

void solve(ll testcase){
  ll i,j,k;
}

int main(){
  ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
  setup();
  preprocess();
  ll t=1;
  // cin>>t;
  for(ll i=1;i<=t;i++)solve(i);
  return 0;
}