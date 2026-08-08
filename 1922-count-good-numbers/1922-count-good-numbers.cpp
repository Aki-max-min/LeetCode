class Solution {
public:

    const long long MOD = 1000000007;

    long long power(long long base, long long exponent) {

        long long result = 1;

        while (exponent > 0) {

            // If exponent is odd
            if (exponent % 2 == 1) {
                result = (result * base) % MOD;
            }

            // Square the base
            base = (base * base) % MOD;

            // Divide exponent by 2
            exponent /= 2;
        }

        return result;
    }

    int countGoodNumbers(long long n) {

        // Even indices have 5 choices
        long long evenPositions = (n + 1) / 2;

        // Odd indices have 4 choices
        long long oddPositions = n / 2;

        long long evenWays = power(5, evenPositions);
        long long oddWays = power(4, oddPositions);

        return (evenWays * oddWays) % MOD;
    }
};