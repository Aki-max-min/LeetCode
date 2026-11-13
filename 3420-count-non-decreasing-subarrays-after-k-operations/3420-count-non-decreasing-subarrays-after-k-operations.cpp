
class Solution {
public:
    long long countNonDecreasingSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        int LOG = 20;

        vector<int> nge(n, n);
        stack<int> st;

        // Find next greater element
        for (int i = n - 1; i >= 0; i--) {
            while (!st.empty() && nums[st.top()] <= nums[i]) {
                st.pop();
            }

            if (!st.empty()) {
                nge[i] = st.top();
            }

            st.push(i);
        }

        vector<vector<int>> up(LOG, vector<int>(n + 1, n));
        vector<vector<long long>> sum(LOG, vector<long long>(n + 1, 0));

        for (int i = 0; i < n; i++) {
            up[0][i] = nge[i];
            sum[0][i] = 1LL * nums[i] * (nge[i] - i);
        }

        // Binary lifting
        for (int p = 1; p < LOG; p++) {
            for (int i = 0; i < n; i++) {
                int mid = up[p - 1][i];

                up[p][i] = up[p - 1][mid];
                sum[p][i] = sum[p - 1][i] + sum[p - 1][mid];
            }
        }

        // Prefix sum
        vector<long long> pref(n + 1, 0);

        for (int i = 0; i < n; i++) {
            pref[i + 1] = pref[i] + nums[i];
        }

        // Calculate operations needed
        auto getCost = [&](int l, int r) -> long long {
            int cur = l;
            long long total = 0;

            for (int p = LOG - 1; p >= 0; p--) {
                if (up[p][cur] <= r) {
                    total += sum[p][cur];
                    cur = up[p][cur];
                }
            }

            total += 1LL * nums[cur] * (r - cur + 1);

            return total - (pref[r + 1] - pref[l]);
        };

        // Binary search
        long long ans = 0;

        for (int l = 0; l < n; l++) {
            int low = l, high = n - 1;
            int best = l - 1;

            while (low <= high) {
                int mid = low + (high - low) / 2;

                if (getCost(l, mid) <= k) {
                    best = mid;
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }

            ans += best - l + 1;
        }

        return ans;
    }
};
