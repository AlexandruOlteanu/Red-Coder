/*
    Programmer : Alexandru Olteanu
    Problem Link : https://www.pbinfo.ro/probleme/4449/patinaj
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

ifstream fin("patinaj.in");
ofstream fout("patinaj.out");
#define cin fin
#define cout fout

const long long infll = numeric_limits<long long> :: max();
const int inf = numeric_limits<int> :: max();
const int maxn = 2e5 + 5;

map<int, int> a1, f1, b1;


int main() {



    FastEverything
    HighPrecision
    int test = 1;
    // cin >> test;
    for (int tt = 1; tt <= test; ++tt) {

        int c, n;
        cin >> c >> n;
        vector<int> a(n), f(n), b(n);
        for (int i = 1; i <= 3; ++i) {
            for (int j = 1; j <= n; ++j) {
                int x;
                cin >> x;
                int s = 0;
                while (x) {
                    s += x % 10;
                    x /= 10;
                }
                if (i == 1) a[j - 1] = s;
                if (i == 2) f[j - 1] = s;
                if (i == 3) b[j - 1] = s;
            }
        }

        if (c == 1) {
            sort(all(a));
            sort(all(f));
            sort(all(b));
            int i = 0, j = 0, k = 0;
            int ans = 0;
            while (i < n && j < n && k < n) {
                int mn = min({a[i], f[j], b[k]});
                int mx = max({a[i], f[j], b[k]});
                if (mx - mn <= 1) {
                    ++ans;
                    ++i;
                    ++j;
                    ++k;
                    continue;
                }
                if (a[i] == mn) {
                    ++i;
                    continue;
                }
                if (f[j] == mn) {
                    ++j;
                    continue;
                }
                ++k;
            }

            cout << ans << '\n';
            return 0;
        }

        sort(rall(a));
        for (auto u : a) {
            ++a1[u];
        }
        for (auto u : f) {
            ++f1[u];
        }
        for (auto u : b) {
            ++b1[u];
        }

        int d[] = {-1, 0, 1};
        ll ans = 0;
        for (auto u : a) {
            
            for (int i = 0; i <= 2; ++i) {
                for (int j = 0; j <= 2; ++j) {
                    if (abs(i - j) > 1) continue;
                    int x = u + d[i], y = u + d[j];
                    if (f1[x] && b1[y]) {
                        ans += f1[x] * b1[y];
                    }
                }
            }
            ans *= a1[u];
            if (ans > 0) {
                cout << u << " " << ans << '\n';
                return 0;
            }
        }


        cout << "-1\n";
    }

    return 0;
}
