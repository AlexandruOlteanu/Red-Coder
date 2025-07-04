// ============================================================================
//                              GENERIC TREE UTILITY
//            Binary‑Lifting LCA  +  Subtree & Diameter helpers
//                    1‑indexed, supports FORESTS (multiple trees)
// ============================================================================
//  QUICK REFERENCE   –  what you can call after `Tree T(n);`
// ----------------------------------------------------------------------------
//   addEdge(u,v)                     // undirected (u,v); repeat as needed
//
//   build()                          // auto‑root every component (no preference)
//   build(root)                      // … but make `root` the root of *its* comp
//   build({r1,r2,…})                 // preferred root for *each* component
//
//   build(adj)                       // build from existing adjacency list
//   build(adj,root)                  // … + single preferred root
//   build(adj,{r1,r2,…})             // … + several preferred roots
//
//   /* classical LCA queries */
//   lca(u,v)                         // lowest common ancestor (‑1 if diff comps)
//   dist(u,v)                        // #edges on the u‑v path (‑1 if diff comps)
//   kth_ancestor(v,k)                // k‑th ancestor (‑1 if non‑existent)
//
//   /* Subtree / leaf helpers */
//   const vector<int>& leaves() const           // all leaves in the forest
//   int                nrLeaves() const         // leaves().size()
//   int                subtreeSize(v) const     // |subtree of v|
//   vector<int>        subtreeOf(v) const       // vertices in v‑subtree
//   const vector<int>& allSubtreeSizes() const  // size for every vertex
//   bool               isAncestor(u,v) const    // true ⇔ u ancestor of v
//   int                rootOf(v) const          // root of v’s component
//
//   /* direct‑children helpers */
//   int                getNrOfChilds(v) const   // #direct children of v
//   vector<int>        getChilds(v) const       // direct children of v
//
//   /* NEW — diameter helpers */
//   int                getDiameter(v) const     // diameter length of v’s comp
//   const vector<int>& allDiameters() const     // diameter for every component
//
//   reset() / reset(new_n)                      // reuse object
//
//  GUARANTEES
//   • All queries return ‑1 when vertices lie in *different* trees.
//   • kth_ancestor(v,k) returns ‑1 if k ≥ depth(v)+1 (climbs past root).
//   • addEdge() *after* build(), or query *before* build()  → assert‑fail.
//
//  COMPLEXITIES
//   build(...)                O(n log n)
//   lca/dist/kth              O(log n) per query
//   subtree helpers           O(1) per query (subtreeOf: O(|subtree|))
//   children helpers          O(deg(v))
//   diameter helpers          O(1) per query (overall extra O(n))
//   memory                    O(n log n)
// ============================================================================

// https://github.com/AlexandruOlteanu/CompetitiveProgramming/blob/main/template/Graphs/Tree.cpp
struct Tree {
    explicit Tree(int _n = 0) { init(_n); }

    // ----------------------------- public API ----------------------------- //
    void addEdge(int u, int v) {
        assert(!built && "addEdge() must be called before build()");
        g[u].push_back(v), g[v].push_back(u);
    }

    // build overloads – same behaviour as Ancestor
    void build(int root = 1)                              { runBuild({root}); }
    void build(const vector<int>& roots)                  { runBuild(roots); }
    void build(const vector<vector<int>>& adj)            { g = adj; runBuild({}); }
    void build(const vector<vector<int>>& adj, int root)  { g = adj; runBuild({root}); }
    void build(const vector<vector<int>>& adj, const vector<int>& roots) { g = adj; runBuild(roots); }

    // classical LCA wrappers -------------------------------------------------
    int getKthAncestor(int v, int k) const { assertBuilt(); return lift(v,k); }
    int getLCA(int u, int v)          const { assertBuilt(); return lcaImpl(u,v); }
    int getDist(int u, int v)         const {
        assertBuilt();
        int a = lcaImpl(u,v);
        return a == -1 ? -1 : depth[u] + depth[v] - 2*depth[a];
    }

    // subtree / leaf helpers -------------------------------------------------
    const vector<int>& getLeaves()         const { assertBuilt(); return leaf_nodes; }
    int                getNrLeaves()       const { assertBuilt(); return (int)leaf_nodes.size(); }
    int                getSubtreeSize(int v) const { assertBuilt(); return subtree_sz[v]; }
    const vector<int>& getAllSubtreeSizes() const { assertBuilt(); return subtree_sz; }

    vector<int> getSubtreeOf(int v) const {
        assertBuilt();
        if (tin[v] == -1) return {};
        return vector<int>( euler.begin() + tin[v], euler.begin() + tout[v] );
    }

    bool isAncestor(int u, int v) const {
        assertBuilt();
        return comp[u] == comp[v] && tin[u] <= tin[v] && tout[v] <= tout[u];
    }

    int getRootOf(int v) const {
        assertBuilt();
        return root_of_comp[ comp[v] ];
    }

    // direct‑children helpers ---------------------------------------------- //
    int getNrOfChilds(int v) const {
        assertBuilt();
        int cnt = 0, p = up[0][v];
        for (int to : g[v]) if (to != p) ++cnt;
        return cnt;
    }
    vector<int> getChilds(int v) const {
        assertBuilt();
        vector<int> res;
        int p = up[0][v];
        for (int to : g[v]) if (to != p) res.push_back(to);
        return res;
    }

    // NEW: diameter helpers ------------------------------------------------- //
    /** Diameter length (in edges) of the component containing `v`. */
    int getDiameter(int v) const {
        assertBuilt();
        return diam_of_comp[ comp[v] ];
    }
    /** Diameter for every component (same order as root_of_comp). */
    const vector<int>& allDiameters() const { assertBuilt(); return diam_of_comp; }

    // Re‑use --------------------------------------------------------------- //
    void reset()          { init(n); }
    void reset(int new_n) { init(new_n); }

private:
    // State ---------------------------------------------------------------- //
    int n = 0, LOG = 0;
    vector<vector<int>> g;            // adjacency list
    vector<vector<int>> up;           // up[k][v] = 2^k‑ancestor (0 ⇒ none)
    vector<int> depth;                // depth[v]
    vector<int> comp;                 // component id of v
    vector<int> root_of_comp;         // root vertex for each component

    // Euler tour / subtree data
    vector<int> tin, tout, euler;     // entry/exit positions in Euler order
    vector<int> subtree_sz;           // |subtree rooted at v|
    vector<int> leaf_nodes;           // vertices with no children

    // diameter per component
    vector<int> diam_of_comp;         // length (edges) of diameter for comp

    bool built = false;

    void init(int _n) {
        n = _n;
        LOG = 32 - __builtin_clz(max(1, n)) + 1;
        g.assign(n + 1, {});
        up.assign(LOG, vector<int>(n + 1, 0));
        depth.assign(n + 1, 0);
        comp.assign(n + 1, -1);
        subtree_sz.assign(n + 1, 0);
        tin.assign(n + 1, -1);
        tout.assign(n + 1, -1);
        root_of_comp.clear();
        euler.clear();
        leaf_nodes.clear();
        diam_of_comp.clear();
        built = false;
    }

    // Build helpers -------------------------------------------------------- //
    void runBuild(const vector<int>& roots) {
        assert(!built && "build() called twice");
        vector<char> used_root(n + 1, 0);
        int cid = 0;

        // 1) DFS from user‑designated roots
        for (int r : roots)
            if (1 <= r && r <= n && !used_root[r] && comp[r] == -1) {
                used_root[r] = 1;
                root_of_comp.push_back(r);
                dfs(r, 0, cid++);
            }

        // 2) Any remaining vertices become roots of their own components
        for (int v = 1; v <= n; ++v)
            if (comp[v] == -1) {
                root_of_comp.push_back(v);
                dfs(v, 0, cid++);
            }

        // 3) Compute diameter for every component (extra O(n)).
        computeDiameters(cid);

        built = true;
    }

    void dfs(int v, int p, int cid) {
        comp[v] = cid;
        up[0][v] = p;
        for (int k = 1; k < LOG; ++k)
            up[k][v] = up[k-1][v] ? up[k-1][ up[k-1][v] ] : 0;

        tin[v] = (int)euler.size();
        euler.push_back(v);
        subtree_sz[v] = 1;

        int child_cnt = 0;
        for (int to : g[v]) if (to != p) {
            depth[to] = depth[v] + 1;
            dfs(to, v, cid);
            subtree_sz[v] += subtree_sz[to];
            ++child_cnt;
        }

        if (child_cnt == 0) leaf_nodes.push_back(v);
        tout[v] = (int)euler.size();
    }

    // Diameter helpers ----------------------------------------------------- //
    /** Return {vertex, dist} farthest from `src` within its component. */
    pair<int,int> bfsFarthest(int src, vector<int>& dist) const {
        queue<int> q;
        q.push(src);
        dist[src] = 0;
        int far = src;
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (int to : g[v]) if (comp[to] == comp[src] && dist[to] == -1) {
                dist[to] = dist[v] + 1;
                q.push(to);
                if (dist[to] > dist[far]) far = to;
            }
        }
        return {far, dist[far]};
    }

    void computeDiameters(int C) {
        diam_of_comp.assign(C, 0);
        vector<int> dist(n + 1, -1);
        for (int cid = 0; cid < C; ++cid) {
            int start = root_of_comp[cid];
            fill(dist.begin(), dist.end(), -1);
            auto [u, _du] = bfsFarthest(start, dist);
            fill(dist.begin(), dist.end(), -1);
            auto [v, diam] = bfsFarthest(u, dist);
            diam_of_comp[cid] = diam;
        }
    }

    // Lift & LCA ----------------------------------------------------------- //
    int lift(int v, int k) const {
        for (int i = 0; v && k; ++i, k >>= 1)
            if (k & 1) v = up[i][v];
        return v ? v : -1;
    }

    int lcaImpl(int u, int v) const {
        if (comp[u] != comp[v]) return -1;      // different components
        if (depth[u] < depth[v]) swap(u, v);
        u = lift(u, depth[u] - depth[v]);
        if (u == v) return u;
        for (int i = LOG - 1; i >= 0; --i)
            if (up[i][u] && up[i][u] != up[i][v]) {
                u = up[i][u];
                v = up[i][v];
            }
        return up[0][u] ? up[0][u] : -1;
    }

    void assertBuilt() const { assert(built && "build() must be called first"); }
};