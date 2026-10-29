class Solution {
public:
    vector<vector<int>> adj;
    vector<int> parent, depth, heavy, head, pos, sz, bit;
    string s;
    int timer, n;

    int dfs(int u, int p) {
        sz[u] = 1;
        parent[u] = p;
        int maxSize = 0;

        for (int v : adj[u]) {
            if (v == p) continue;

            depth[v] = depth[u] + 1;
            int childSize = dfs(v, u);
            sz[u] += childSize;

            if (childSize > maxSize) {
                maxSize = childSize;
                heavy[u] = v;
            }
        }

        return sz[u];
    }

    void decompose(int u, int h) {
        head[u] = h;
        pos[u] = timer++;

        if (heavy[u] != -1)
            decompose(heavy[u], h);

        for (int v : adj[u]) {
            if (v != parent[u] && v != heavy[u])
                decompose(v, v);
        }
    }

    void updateBIT(int idx, int val) {
        for (++idx; idx <= n; idx += idx & -idx)
            bit[idx] ^= val;
    }

    int queryBIT(int idx) {
        int res = 0;
        for (++idx; idx > 0; idx -= idx & -idx)
            res ^= bit[idx];
        return res;
    }

    int rangeQuery(int l, int r) {
        if (l > r) return 0;
        return queryBIT(r) ^ (l ? queryBIT(l - 1) : 0);
    }

    int pathQuery(int u, int v) {
        int mask = 0;

        while (head[u] != head[v]) {
            if (depth[head[u]] < depth[head[v]])
                swap(u, v);

            mask ^= rangeQuery(pos[head[u]], pos[u]);
            u = parent[head[u]];
        }

        if (depth[u] > depth[v])
            swap(u, v);

        mask ^= rangeQuery(pos[u], pos[v]);

        return mask;
    }

    vector<bool> palindromePath(int n, vector<vector<int>>& edges,
                                string s, vector<string>& queries) {
        this->n = n;
        this->s = s;

        adj.assign(n, {});
        parent.assign(n, -1);
        depth.assign(n, 0);
        heavy.assign(n, -1);
        head.assign(n, 0);
        pos.assign(n, 0);
        sz.assign(n, 0);
        bit.assign(n + 1, 0);
        timer = 0;

        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        dfs(0, -1);
        decompose(0, 0);

        for (int u = 0; u < n; u++)
            updateBIT(pos[u], 1 << (s[u] - 'a'));

        vector<bool> ans;

        for (string& q : queries) {
            stringstream ss(q);
            string type;
            int u;
            ss >> type >> u;

            if (type == "update") {
                char c;
                ss >> c;

                int change = (1 << (s[u] - 'a')) ^ (1 << (c - 'a'));
                updateBIT(pos[u], change);
                s[u] = c;
            } else {
                int v;
                ss >> v;

                int mask = pathQuery(u, v);
                ans.push_back((mask & (mask - 1)) == 0);
            }
        }

        return ans;
    }
};