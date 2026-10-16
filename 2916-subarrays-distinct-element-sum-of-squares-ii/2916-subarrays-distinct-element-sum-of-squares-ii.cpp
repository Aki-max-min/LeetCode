class Solution {
public:
    int sumCounts(vector<int>& nums) {
        const long long MOD = 1'000'000'007;
        int n = nums.size();

        vector<long long> sum(4 * n, 0), sq(4 * n, 0);
        vector<int> lazy(4 * n, 0);
        vector<int> last(100001, -1);

        function<void(int, int, int, int)> apply =
            [&](int node, int l, int r, int val) {
                long long len = r - l + 1;
                long long oldSum = sum[node];

                sq[node] = (sq[node] + 2LL * val * oldSum
                            + len * val * val) % MOD;
                sum[node] = (sum[node] + len * val) % MOD;
                lazy[node] += val;
            };

        function<void(int, int, int)> push =
            [&](int node, int l, int r) {
                if (lazy[node] == 0 || l == r) return;

                int mid = (l + r) / 2;
                apply(node * 2, l, mid, lazy[node]);
                apply(node * 2 + 1, mid + 1, r, lazy[node]);
                lazy[node] = 0;
            };

        function<void(int, int, int, int, int)> update =
            [&](int node, int l, int r, int ql, int qr) {
                if (ql <= l && r <= qr) {
                    apply(node, l, r, 1);
                    return;
                }

                push(node, l, r);
                int mid = (l + r) / 2;

                if (ql <= mid)
                    update(node * 2, l, mid, ql, qr);

                if (qr > mid)
                    update(node * 2 + 1, mid + 1, r, ql, qr);

                sum[node] = (sum[node * 2] + sum[node * 2 + 1]) % MOD;
                sq[node] = (sq[node * 2] + sq[node * 2 + 1]) % MOD;
            };

        long long ans = 0;

        for (int i = 0; i < n; i++) {
            int left = last[nums[i]] + 1;
            update(1, 0, n - 1, left, i);

            ans = (ans + sq[1]) % MOD;
            last[nums[i]] = i;
        }

        return (int)ans;
    }
};