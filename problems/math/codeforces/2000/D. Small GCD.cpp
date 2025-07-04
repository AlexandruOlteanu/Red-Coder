/*
  ░█████╗░██╗░░░░░███████╗██╗░░██╗░█████╗░███╗░░██╗██████╗░██████╗░██╗░░░██╗██╗███╗░░██╗██╗░░░██╗
  ██╔══██╗██║░░░░░██╔════╝╚██╗██╔╝██╔══██╗████╗░██║██╔══██╗██╔══██╗██║░░░██║██║████╗░██║██║░░░██║
  ███████║██║░░░░░█████╗░░░╚███╔╝░███████║██╔██╗██║██║░░██║██████╔╝██║░░░██║██║██╔██╗██║╚██╗░██╔╝
  ██╔══██║██║░░░░░██╔══╝░░░██╔██╗░██╔══██║██║╚████║██║░░██║██╔══██╗██║░░░██║██║██║╚████║░╚████╔╝░
  ██║░░██║███████╗███████╗██╔╝╚██╗██║░░██║██║░╚███║██████╔╝██║░░██║╚██████╔╝██║██║░╚███║░░╚██╔╝░░
  ╚═╝░░╚═╝╚══════╝╚══════╝╚═╝░░╚═╝╚═╝░░╚═╝╚═╝░░╚══╝╚═════╝░╚═╝░░╚═╝░╚═════╝░╚═╝╚═╝░░╚══╝░░░╚═╝░░░
  They forged me in fire, they broke me in battle, yet here I rise, Invictus!
*/
// Link: https://codeforces.com/contest/1900/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;
template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// Useful
mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
#define LightningFastReadWrite ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define RealValuesHighPrecision cout << fixed << setprecision(17);
typedef long long ll;
typedef pair<int, int> pii;
const int mod = 1000000007;
const int mod1 = 998244353;
ll mypowr(ll a, ll b, ll mod1) {ll res = 1; if(b < 0)b = 0; a %= mod1; assert(b >= 0);
for(; b; b >>= 1){if (b & 1) res = res * a % mod1;a = a * a % mod1;} return res;}
ll mypow(ll a, ll b) {ll res = 1; if(b < 0)b = 0;assert(b >= 0);
for(; b; b >>= 1){if(b & 1) res = res * a;a = a * a;} return res;}
#define YES cout << "YES\n";
#define NO cout << "NO\n";
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
const int maxn = 1e5 + 2;

vector<int> d[maxn];
vector<int> pos[maxn];
int a[maxn];
ll cnt[maxn];

void solveTask(int testNr) {

    int n;
    cin >> n;
    for (int i = 1; i <= 100000; ++i) {
        pos[i].clear();
        cnt[i] = 0;
    }

    for (int i = 1; i <= n; ++i) {
        cin >> a[i];

    }
    sort(a + 1, a + n + 1);

    for (int i = 1; i <= n; ++i) {
        for (auto u : d[a[i]]) {
            pos[u].pb(i);
        }
    }
    int maxi = a[n];
    long long ans = 0;
    for (int i = maxi; i >= 1; --i) {
        int sz = (int) pos[i].size();
        for (int j = 1; j < sz; ++j) {
            cnt[i] += 1LL * j * (n - pos[i][j]);
        }

        for (int j = i + i; j <= maxi; j += i) {
            cnt[i] -= cnt[j];
        }
        ans += i * cnt[i];
    }
    cout << ans << '\n';
}

void precompute() {

    for (int i = 1; i <= 100000; ++i) {
        for (int j = i; j <= 100000; j += i) {
            d[j].pb(i);
        }
    }
}

int main() {

    LightningFastReadWrite
    RealValuesHighPrecision

    int totalNrOfTests = 1;
    cin >> totalNrOfTests;
    precompute();
    for (int testNr = 1; testNr <= totalNrOfTests; ++testNr) {
        solveTask(testNr);
    }

    return 0;
}