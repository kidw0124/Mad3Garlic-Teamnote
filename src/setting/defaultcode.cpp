#include<bits/stdc++.h>
using namespace std;
#pragma warning(disable:4996)
#pragma comment(linker, "/STACK:336777216")
using ll=long long;
using ull=unsigned long long;
using LL=__int128_t;
using ULL=__uint128_t;
using ld=long double;
ll gcd(ll a, ll b){return b?gcd(b,a%b):a;}
ll lcm(ll a, ll b){if(a&&b)return a*(b/gcd(a,b)); return a+b;}
ll powm(ll a, ll b, ll rem){ll p=1;for(;b;b/=2,a=(a*a)%rem)if(b&1)p=(p*a)%rem;return p;}
int main(){
  ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
  ll i,j;
  return 0;
}