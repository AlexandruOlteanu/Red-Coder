/*
    Programmer : Alexandru Olteanu
    Problem Link : https://codeforces.com/contest/1108/problem/E1
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

// ifstream fin("input.txt");
// ofstream fout("output.txt");
// #define cin fin
// #define cout fout

const long long infll = numeric_limits<long long> :: max();
const int inf = numeric_limits<int> :: max();
const int maxn = 2e5 + 5;

int a[maxn], l[maxn], r[maxn], b[maxn];

int main() {

    FastEverything
    HighPrecision
    int test = 1;
    // cin >> test;
    for (int tt = 1; tt <= test; ++tt) {

        int n, m;
        cin >> n >> m;
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
        }

        for (int i = 1; i <= m; ++i) {
            cin >> l[i] >> r[i];
        }

        int ans = -inf;
        int idx = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                b[j] = a[j];
            }
            vector<int> have(n + 2);
            for (int j = 1; j <= m; ++j) {
                if (i >= l[j] && i <= r[j]) {
                    ++have[l[j]];
                    --have[r[j] + 1];
                }
            }
            int mx = b[1] - have[1];
            for (int j = 2; j <= n; ++j) {
                have[j] += have[j - 1];
                mx = max(mx, b[j] - have[j]);
            }
            if (mx - a[i] + have[i] > ans) {
                ans = mx - a[i] + have[i];
                idx = i;
            }
        }


        cout << ans << '\n';
        vector<int> res;
        for (int i = 1; i <= m; ++i) {
            if (l[i] <= idx && idx <= r[i]) {
                res.push_back(i);
            }
        }

        cout << res.size() << '\n';
        for (auto u : res) {
            cout << u << " ";
        }
        cout << '\n';
        
    }

    return 0;
}