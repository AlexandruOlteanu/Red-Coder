/*
    Programmer : Alexandru Olteanu
    Problem Link : https://codeforces.com/contest/1928/problem/D
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

// ifstream fin("input.in");
// ofstream fout("output.out");
// #define cin fin
// #define cout fout

const long long infll = numeric_limits<long long> :: max();
const int inf = numeric_limits<int> :: max();
const int maxn = 2e5 + 5;

ll calc(ll a, ll k) {
    ll r = a % k;
    ll x = a / k + 1;
    ll y = a / k;
    ll ans = x * x * r * (r - 1) / 2;
    ans += y * x * r * (k - r);
    ans += y * y * (k - r) * (k - r - 1) / 2;
    return ans;
}

map<int, int> a;
vector<int> u;

int main() {



    FastEverything
    HighPrecision
    int test = 1;
    cin >> test;
    for (int tt = 1; tt <= test; ++tt) {

        int n, b, x;
        cin >> n >> b >> x;
        a.clear();
        u.clear();
        int sum = 0;
        for (int i = 1; i <= n; ++i) {
            int x;
            cin >> x;
            ++a[x];
            if (a[x] == 1) u.push_back(x);
            sum = max(sum, x);
        }

        ll ans = 0;
        for (int k = 1; k <= sum; ++k) {
            ll sum = 0;
            for (auto x : u) {
                sum += 1LL * a[x] * calc(x, k);
            }
            sum *= b;
            sum -= 1LL * (k - 1) * x;
            ans = max(ans, sum); 
        }

        cout << ans << '\n';
        
        
    }

    return 0;
}

// r = a / k + 1
// p = a / k
// r^2 * (a%k - 1) * (a % k) / 2 +
// p * r * (a % k) * (k - a % k) +
// p^2 * (k - a % k - 1) * (k - a % k) / 2
