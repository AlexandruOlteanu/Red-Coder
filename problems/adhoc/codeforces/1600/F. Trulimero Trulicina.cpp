/*
  ░█████╗░██╗░░░░░███████╗██╗░░██╗░█████╗░███╗░░██╗██████╗░██████╗░██╗░░░██╗██╗███╗░░██╗██╗░░░██╗
  ██╔══██╗██║░░░░░██╔════╝╚██╗██╔╝██╔══██╗████╗░██║██╔══██╗██╔══██╗██║░░░██║██║████╗░██║██║░░░██║
  ███████║██║░░░░░█████╗░░░╚███╔╝░███████║██╔██╗██║██║░░██║██████╔╝██║░░░██║██║██╔██╗██║╚██╗░██╔╝
  ██╔══██║██║░░░░░██╔══╝░░░██╔██╗░██╔══██║██║╚████║██║░░██║██╔══██╗██║░░░██║██║██║╚████║░╚████╔╝░
  ██║░░██║███████╗███████╗██╔╝╚██╗██║░░██║██║░╚███║██████╔╝██║░░██║╚██████╔╝██║██║░╚███║░░╚██╔╝░░
  ╚═╝░░╚═╝╚══════╝╚══════╝╚═╝░░╚═╝╚═╝░░╚═╝╚═╝░░╚══╝╚═════╝░╚═╝░░╚═╝░╚═════╝░╚═╝╚═╝░░╚══╝░░░╚═╝░░░
  They forged me in fire, they broke me in battle, yet here I rise, Invictus!
*/
// Link: https://codeforces.com/contest/2094/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;
template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// Useful
mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());
#define LightningFastReadWrite ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
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

// ifstream fin("input.in");
// ofstream fout("output.out");
// #define cin fin
// #define cout fout

const long long infll = numeric_limits<long long> :: max();
const int inf = numeric_limits<int> :: max();
const int maxn = 2e5 + 5;

vector<vector<int>> a;

int main() {

    LightningFastReadWrite
    HighPrecision
    int test = 1;
    cin >> test;
    for (int tt = 1; tt <= test; ++tt) {

        int n, m, k;
        cin >> n >> m >> k;
        a.resize(n + 1);
        for (int i = 0; i <= n; ++i) {
            a[i].resize(m + 1);
        }
        if (m % k == 0) {
            for (int i = 1; i <= n; ++i) {
                if (i % 2) {
                    for (int j = 1; j <= m; ++j) {
                        int x = j % k;
                        if (x == 0) x = k;
                        a[i][j] = x;
                    }
                } else {
                    int p = k;
                    for (int j = 1; j <= m; ++j) {
                        a[i][j] = p;
                        --p;
                        if (p == 0) p = k;
                    }
                }
            }

            for (int i = 2; i <= n; ++i) {
                for (int j = 1; j <= m; ++j) {
                    if (a[i][j] == a[i - 1][j]) {
                        swap(a[i][j], a[i][j + 1]);
                    }
                }
            }

            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= m; ++j) {
                    cout << a[i][j] << " ";
                }
                cout << '\n';
            }

            continue;
        }

        int p = 1;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                cout << p << " ";
                ++p;
                if (p > k) p = 1;
            }
            cout << '\n';
        }

    }

    return 0;
}