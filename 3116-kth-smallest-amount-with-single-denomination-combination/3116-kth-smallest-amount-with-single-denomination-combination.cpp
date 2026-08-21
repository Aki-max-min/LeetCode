class Solution {
public:
    long long findKthSmallest(vector<int>& coins, int k) {
        int n = coins.size();

        auto gcd = [](long long a, long long b) {
            while (b) {
                long long t = a % b;
                a = b;
                b = t;
            }
            return a;
        };

        auto count = [&](long long x) {
            long long ans = 0;

            for (int mask = 1; mask < (1 << n); mask++) {
                long long L = 1;
                int bits = 0;
                bool valid = true;

                for (int i = 0; i < n; i++) {
                    if (mask & (1 << i)) {
                        bits++;

                        long long g = gcd(L, (long long)coins[i]);
                        L = L / g * coins[i];

                        if (L > x) {
                            valid = false;
                            break;
                        }
                    }
                }

                if (!valid) continue;

                if (bits % 2 == 1)
                    ans += x / L;
                else
                    ans -= x / L;
            }

            return ans;
        };

        long long low = 1;
        long long high = 1LL * (*min_element(coins.begin(), coins.end())) * k;

        while (low < high) {
            long long mid = low + (high - low) / 2;

            if (count(mid) >= k)
                high = mid;
            else
                low = mid + 1;
        }

        return low;
    }
};