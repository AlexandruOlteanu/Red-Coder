/*
    Programmer : Alexandru Olteanu
    Problem Link : https://www.pbinfo.ro/probleme/4392/arhitect
*/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;
template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// Useful
mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());
#define FastEverything  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define HighPrecision cout << fixed << setprecision(17);
typedef long long ll;
typedef pair<int, int> pii;
const int mod = 1000000007;
const int mod1 = 998244353;
ll mypowr(ll a, ll b, ll mod1) {ll res = 1; if(b < 0)b = 0; a %= mod1; assert(b >= 0);
for(; b; b >>= 1){if (b & 1) res = res * a % mod1;a = a * a % mod1;} return res;}
ll mypow(ll a, ll b) {ll res = 1; if(b < 0)b = 0;assert(b >= 0);
for(; b; b >>= 1){if(b & 1) res = res * a;a = a * a;} return res;}
#define pb push_back
#define fi first
#define se second
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()

ifstream fin("arhitect.in");
ofstream fout("arhitect.out");
#define cin fin
#define cout fout

const long long infll = numeric_limits<long long> :: max();
const int inf = numeric_limits<int> :: max();
const int maxn = 1e5 + 5;

pii l[maxn], r[maxn];
map<pii, int> m;

int main() {

    FastEverything
    HighPrecision
    int test = 1;
    // cin >> test;
    for (int tt = 1; tt <= test; ++tt) {

        int n;
        cin >> n;
        int ans = 0;
        int cnt = 0;
        for (int i = 1; i <= n; ++i) {
            cin >> l[i].fi >> l[i].se;
            cin >> r[i].fi >> r[i].se;
            if (l[i].fi == r[i].fi || l[i].se == r[i].se) {
                ++ans;
                continue;
            }
            ll x = r[i].se - l[i].se;
            ll y = r[i].fi - l[i].fi;
            ll g = __gcd(x, y);
            x /= g, y /= g;
            if (x * y < 0) {
                if (x > 0) x = -x, y = -y;
            }
            ++m[{x, y}];
            cnt = max(cnt, m[{x, y}]);
            ll x1 = -y, y1 = x;
            if (x1 * y1 < 0) {
                if (x1 > 0) x1 = -x1, y1 = -y1;
            }
            ++m[{x1, y1}];
            cnt = max(cnt, m[{x1, y1}]);
        }

        ans = max(ans, cnt);

        cout << ans << '\n';
        
    }

    return 0;
}