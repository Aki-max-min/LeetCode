class Solution {
public:
    int distinctSubseqII(string s) {
        const long long MOD = 1e9 + 7;
        // dp[i] = number of distinct subsequences
        // using the first i characters, including empty subsequence
        vector<long long> dp(s.size() + 1, 0);
        dp[0] = 1;
        // Last position where each character occurred
        vector<int> last(26, -1);
        for (int i = 1; i <= s.size(); i++) {
            int c = s[i - 1] - 'a';
            // Every old subsequence can either:
            // 1. stay as it is
            // 2. append s[i-1]
            dp[i] = (2 * dp[i - 1]) % MOD;
            // Remove duplicates created by the previous occurrence
            if (last[c] != -1) {
                dp[i] = (dp[i] - dp[last[c] - 1] + MOD) % MOD;
            }
            last[c] = i;
        }
        // dp[n] includes the empty subsequence
        return (dp[s.size()] - 1 + MOD) % MOD;
    }
};