// #pragma GCC target("avx2")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define DEBUG
#ifdef DEBUG
template <class T, class U>
ostream &operator<<(ostream &os, const pair<T, U> &p) {
    os << '(' << p.first << ',' << p.second << ')';
    return os;
}
template <class T> ostream &operator<<(ostream &os, const vector<T> &v) {
    os << '{';
    for(int i = 0; i < (int)v.size(); i++) {
        if(i) { os << ','; }
        os << v[i];
    }
    os << '}';
    return os;
}
void debugg() { cerr << endl; }
template <class T, class... Args>
void debugg(const T &x, const Args &... args) {
    cerr << " " << x;
    debugg(args...);
}
#define debug(...)                                                             \
    cerr << __LINE__ << " [" << #__VA_ARGS__ << "]: ", debugg(__VA_ARGS__)
#define dump(x) cerr << __LINE__ << " " << #x << " = " << (x) << endl
#else
#define debug(...) (void(0))
#define dump(x) (void(0))
#endif
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef vector<vl> vvl;
typedef vector<char> vc;
typedef vector<string> vs;
typedef vector<bool> vb;
typedef vector<double> vd;
typedef pair<ll,ll> P;
typedef pair<int,int> pii;
typedef vector<P> vpl;
typedef tuple<ll,ll,ll> tapu;
#define rep(i,n) for(int i=0; i<(n); i++)
#define REP(i,a,b) for(int i=(a); i<(b); i++)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
const int inf = (1<<30)-1;
const ll linf = 1LL<<61;
const int MAX = 510000;
int dy[8] = {0,1,0,-1,1,-1,-1,1};
int dx[8] = {-1,0,1,0,1,-1,1,-1};
const double pi = acos(-1);
const double eps = 1e-8;
template<typename T1,typename T2> inline bool chmin(T1 &a,T2 b){
	if(a>b){
		a = b; return true;
	}
	else return false;
}
template<typename T1,typename T2> inline bool chmax(T1 &a,T2 b){
	if(a<b){
		a = b; return true;
	}
	else return false;
}
template<typename T> inline void print(T &a){
    int sz = a.size();
    for(auto itr = a.begin(); itr != a.end(); itr++){
		cout << *itr;
        sz--;
        if(sz) cout << " ";
	}
    cout << "\n";
}
template<typename T1,typename T2> inline void print2(T1 a, T2 b){
	cout << a << " " << b << "\n";
}
template<typename T1,typename T2,typename T3> inline void print3(T1 a, T2 b, T3 c){
	cout << a << " " << b << " " << c << "\n";
}
void mark() {cout << "#" << "\n";}
ll pcount(ll x) {return __builtin_popcountll(x);}
//#include <atcoder/all>
//using namespace atcoder;
//const int mod = 1e9 + 7;
const int mod = 998244353;

using Point = complex<double>;

double dot(Point a, Point b){
    return a.real() * b.real() + a.imag() * b.imag();
}

double cross(Point a, Point b){
    return a.real() * b.imag() - a.imag() * b.real();
}

struct Segment{
    Point a,b;
    Segment(Point a, Point b) : a(a), b(b) {}
};

double dist(Segment l, Point p){
    if(dot(l.b-l.a, p-l.a) < eps) return abs(p-l.a);
    if(dot(l.a-l.b, p-l.b) < eps) return abs(p-l.b);
    return abs(cross(l.b-l.a, p-l.a)) / abs(l.b-l.a);
}

bool dp[1<<16];

int main(){
    int n; cin >> n;
    vl r(n);
    vector<vector<Point>> p(n,vector<Point>(2));
    rep(i,n){
        int a,b,c,d;
        cin >> r[i] >> a >> b >> c >> d;
        p[i][0] = Point(a,b);
        p[i][1] = Point(c,d);
    }
    dp[0] = 1;
    rep(bit,1<<n){
        rep(i,n){
            bool f = true;
            Segment seg(p[i][0],p[i][1]);
            rep(j,n){
                if(i==j) continue;
                if(dist(seg,p[j][bit>>j&1]) <= eps + r[i] + r[j]){
                    f = false;
                }
            }
            if(f) dp[bit|1<<i] |= dp[bit];
        }
    }
    int ans = 0;
    rep(bit,1<<n) if(dp[bit]) chmax(ans, pcount(bit));
    cout << ans << endl; 
}