class Solution {
public:
    int numberOfSets(int n, int k) {
        const long long MOD = 1e9 + 7;

        long long ans = 1;

        // Calculate C(n + k - 1, 2k)
        int N = n + k - 1;
        int R = 2 * k;

        for (int i = 1; i <= R; i++) {
            ans = ans * (N - i + 1) % MOD;

            // Modular inverse of i using Fermat's theorem
            long long x = i;
            long long power = MOD - 2;
            long long inv = 1;

            while (power > 0) {
                if (power & 1)
                    inv = inv * x % MOD;

                x = x * x % MOD;
                power >>= 1;
            }

            ans = ans * inv % MOD;
        }

        return ans;
    }
};