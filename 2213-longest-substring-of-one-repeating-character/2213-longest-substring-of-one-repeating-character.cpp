class Solution {
public:
    struct Node {
        int len;
        int pref, suff, best;
        char left, right;

        Node() {
            len = pref = suff = best = 0;
            left = right = '#';
        }
    };

    vector<Node> seg;

    Node merge(Node a, Node b) {
        if (a.len == 0) return b;
        if (b.len == 0) return a;

        Node res;

        res.len = a.len + b.len;
        res.left = a.left;
        res.right = b.right;

        // Prefix
        res.pref = a.pref;
        if (a.pref == a.len && a.right == b.left) {
            res.pref = a.len + b.pref;
        }

        // Suffix
        res.suff = b.suff;
        if (b.suff == b.len && a.right == b.left) {
            res.suff = b.len + a.suff;
        }

        // Best
        res.best = max(a.best, b.best);

        if (a.right == b.left) {
            res.best = max(res.best, a.suff + b.pref);
        }

        return res;
    }

    void build(string &s, int node, int l, int r) {
        if (l == r) {
            seg[node].len = 1;
            seg[node].pref = 1;
            seg[node].suff = 1;
            seg[node].best = 1;
            seg[node].left = s[l];
            seg[node].right = s[l];
            return;
        }

        int mid = (l + r) / 2;

        build(s, 2 * node, l, mid);
        build(s, 2 * node + 1, mid + 1, r);

        seg[node] = merge(seg[2 * node], seg[2 * node + 1]);
    }

    void update(int node, int l, int r, int idx, char ch) {
        if (l == r) {
            seg[node].left = ch;
            seg[node].right = ch;
            seg[node].len = 1;
            seg[node].pref = 1;
            seg[node].suff = 1;
            seg[node].best = 1;
            return;
        }

        int mid = (l + r) / 2;

        if (idx <= mid)
            update(2 * node, l, mid, idx, ch);
        else
            update(2 * node + 1, mid + 1, r, idx, ch);

        seg[node] = merge(seg[2 * node], seg[2 * node + 1]);
    }

    vector<int> longestRepeating(string s, string queryCharacters,
                                 vector<int>& queryIndices) {
        
        int n = s.size();
        int k = queryIndices.size();

        seg.resize(4 * n);

        // Build segment tree
        build(s, 1, 0, n - 1);

        vector<int> ans;

        for (int i = 0; i < k; i++) {
            int idx = queryIndices[i];
            char ch = queryCharacters[i];

            // Update the character
            update(1, 0, n - 1, idx, ch);

            // Root contains the answer for the entire string
            ans.push_back(seg[1].best);
        }

        return ans;
    }
};