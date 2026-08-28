class Solution {
public:
    string lexPalindromicPermutation(string s, string target) {
        int n = s.size();
        vector<int> freq(26, 0);

        for (char c : s) {
            freq[c - 'a']++;
        }

        // Check whether a palindromic permutation is possible
        int oddCount = 0;
        char middle = 0;

        for (int i = 0; i < 26; i++) {
            if (freq[i] % 2) {
                oddCount++;
                middle = char('a' + i);
            }
        }

        if (oddCount > 1) return "";

        // Frequency of characters needed for first half
        vector<int> halfFreq(26);

        for (int i = 0; i < 26; i++) {
            halfFreq[i] = freq[i] / 2;
        }

        int m = n / 2;

        // Build palindrome from first half
        auto buildPalindrome = [&](const string& half) {
            string ans = half;

            if (n % 2 == 1)
                ans += middle;

            string rev = half;
            reverse(rev.begin(), rev.end());
            ans += rev;

            return ans;
        };

        /*
         Try constructing the smallest possible first half H such that

             palindrome(H) > target

         We greedily match target's first half, and at some position
         increase the character, then fill the rest minimally.
        */

        string prefix = "";
        vector<int> remaining = halfFreq;

        // Store states before each position
        vector<vector<int>> states(m + 1);
        states[0] = remaining;

        int matched = 0;

        for (int i = 0; i < m; i++) {
            int x = target[i] - 'a';

            if (remaining[x] == 0)
                break;

            remaining[x]--;
            prefix += target[i];
            matched++;

            states[i + 1] = remaining;
        }

        // Case 1:
        // We can use exactly target's first half.
        if (matched == m) {
            string candidate = buildPalindrome(prefix);

            if (candidate > target)
                return candidate;
        }

        /*
         Find the smallest half lexicographically greater than
         target's first half.

         Try changing positions from right to left.
        */
        int start = min(matched, m - 1);

        for (int i = start; i >= 0; i--) {

            // We need state before position i
            vector<int> rem = states[i];

            int current = target[i] - 'a';

            // Find smallest available character > target[i]
            for (int c = current + 1; c < 26; c++) {
                if (rem[c] > 0) {

                    rem[c]--;

                    string half = target.substr(0, i);
                    half += char('a' + c);

                    // Fill remaining characters in sorted order
                    for (int k = 0; k < 26; k++) {
                        half.append(rem[k], char('a' + k));
                    }

                    return buildPalindrome(half);
                }
            }
        }

        return "";
    }
};