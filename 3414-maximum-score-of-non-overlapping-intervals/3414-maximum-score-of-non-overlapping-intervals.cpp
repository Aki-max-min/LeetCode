class Solution {
public:
    struct State {
        long long score;
        vector<int> ans;
    };

    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();

        // Store: {left, right, weight, original index}
        vector<array<long long, 4>> a;

        for (int i = 0; i < n; i++) {
            a.push_back({
                intervals[i][0],
                intervals[i][1],
                intervals[i][2],
                i
            });
        }

        // Sort by starting point
        sort(a.begin(), a.end());

        // next[i] = first interval whose left > a[i].right
        vector<int> next(n);

        for (int i = 0; i < n; i++) {
            int l = i + 1;
            int r = n;

            while (l < r) {
                int mid = l + (r - l) / 2;

                if (a[mid][0] > a[i][1])
                    r = mid;
                else
                    l = mid + 1;
            }

            next[i] = l;
        }

        // dp[i][k] = best answer from i onward
        // if we can still choose k intervals
        vector<vector<State>> dp(n + 1, vector<State>(5));

        // Base case
        for (int k = 0; k <= 4; k++) {
            dp[n][k].score = 0;
        }

        for (int i = n - 1; i >= 0; i--) {
            for (int k = 1; k <= 4; k++) {

                // Option 1: Don't take this interval
                State skip = dp[i + 1][k];

                // Option 2: Take this interval
                State take;

                take.score = a[i][2] + dp[next[i]][k - 1].score;
                take.ans = dp[next[i]][k - 1].ans;

                // Add original index
                take.ans.push_back((int)a[i][3]);

                // We need indices in increasing order
                sort(take.ans.begin(), take.ans.end());

                // Choose the better score
                if (take.score > skip.score) {
                    dp[i][k] = take;
                }
                else if (take.score < skip.score) {
                    dp[i][k] = skip;
                }
                else {
                    // Same score -> lexicographically smaller answer
                    if (take.ans < skip.ans)
                        dp[i][k] = take;
                    else
                        dp[i][k] = skip;
                }
            }
        }

        return dp[0][4].ans;
    }
};