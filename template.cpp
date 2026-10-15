#include<bits/stdc++.h>
#include<atcoder/all>
using namespace std;
using namespace atcoder;
typedef long long int ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<vl> vvl;
typedef vector<vvl> vvvl;
typedef vector<vvvl> vvvvl;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef vector<vvb> vvvb;
typedef vector<vvvb> vvvvb;
typedef pair<ll,ll> pl;
typedef pair<ll,pl> ppl;
typedef pair<ll,ppl> pppl;
typedef pair<ll,pppl> pppppl;
#define rep(i,a,b) for(int i=(a);i<(b);i++)
#define rrep(i,a,b) for(int i=(b)-1;i>=(a);i--)
#define all(a) begin(a),end(a)
#define sz(a) (int)(a).size()
#define F first
#define S second
#define bs(A,x) binary_search(all(A),x)
#define lb(A,x) (ll)(lower_bound(all(A),x)-A.begin())
#define ub(A,x) (ll)(upper_bound(all(A),x)-A.begin())
#define cou(A,x) (ll)(upper_bound(all(A),x)-lower_bound(all(A),x))
template<typename T>using min_priority_queue=priority_queue<T,vector<T>,greater<T>>;
template<class T>bool chmax(T&a,T b){if(a<b){a=b;return 1;}return 0;}
template<class T>bool chmin(T&a,T b){if(b<a){a=b;return 1;}return 0;}
//*
using mint=modint998244353;
const ll mod=998244353;
//*/
/*
using mint=modint1000000007;
const ll mod=1000000007;
//*/
//using mint=modint;
//*
typedef vector<mint> vm;
typedef vector<vm> vvm;
typedef vector<vvm> vvvm;
typedef vector<vvvm> vvvvm;
ostream&operator<<(ostream&os,mint a){os<<a.val();return os;}
istream&operator>>(istream&is,mint&a){int x;is>>x;a=mint(x);return is;}
//*/
template<typename T1,typename T2>ostream&operator<<(ostream&os,pair<T1,T2>p){os<<p.F<<" "<<p.S;return os;}
template<typename T1,typename T2>istream&operator>>(istream&is,pair<T1,T2>&p){is>>p.F>>p.S;return is;}
template<typename T>ostream&operator<<(ostream&os,vector<T>v){rep(i,0,sz(v))os<<v[i]<<(i+1!=sz(v)?" ":"");return os;}
template<typename T>istream&operator>>(istream&is,vector<T>&v){for(T&in:v)is>>in;return is;}
int main(){
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  
  return 0;
}
