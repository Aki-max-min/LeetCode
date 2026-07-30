class Solution {
public:
    using ll = long long;
    const ll LIM = 1000000LL;

    // nCr capped at cap+1
    ll comb(int n, int r, ll cap) {
        if (r < 0 || r > n) return 0;
        r = min(r, n - r);
        ll ans = 1;
        for (int i = 1; i <= r; i++) {
            ans = ans * (n - r + i) / i;
            if (ans > cap) return cap + 1;
        }
        return ans;
    }

    // Number of distinct permutations for given counts.
    ll countWays(vector<int>& cnt, ll cap) {
        int total = 0;
        ll ans = 1;

        for (int x : cnt) {
            if (x == 0) continue;
            ll c = comb(total + x, x, cap);
            ans *= c;
            if (ans > cap) return cap + 1;
            total += x;
        }
        return ans;
    }

    string smallestPalindrome(string s, int k) {
        vector<int> freq(26, 0);
        for (char c : s) freq[c - 'a']++;

        vector<int> half(26);
        char mid = 0;

        for (int i = 0; i < 26; i++) {
            half[i] = freq[i] / 2;
            if (freq[i] & 1) mid = char('a' + i);
        }

        if (countWays(half, k) < k) return "";

        string left;
        int len = s.size() / 2;

        for (int pos = 0; pos < len; pos++) {
            for (int c = 0; c < 26; c++) {
                if (half[c] == 0) continue;

                half[c]--;
                ll ways = countWays(half, k);

                if (ways >= k) {
                    left.push_back(char('a' + c));
                    break;
                }

                k -= ways;
                half[c]++;
            }
        }

        string right = left;
        reverse(right.begin(), right.end());

        if (mid) return left + string(1, mid) + right;
        return left + right;
    }
};