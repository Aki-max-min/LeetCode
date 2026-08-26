class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {
        int n = s.size();
        int left = 0;
        int ones = 0;
        int minLen = INT_MAX;
        string ans = "";

        for (int right = 0; right < n; right++) {
            if (s[right] == '1')
                ones++;

            // Shrink until we have exactly k ones
            while (ones > k) {
                if (s[left] == '1')
                    ones--;
                left++;
            }

            // We have exactly k ones
            if (ones == k) {
                // Remove leading zeros because they make the substring
                // longer without changing the number of ones.
                while (left <= right && s[left] == '0')
                    left++;

                int len = right - left + 1;
                string curr = s.substr(left, len);

                if (len < minLen) {
                    minLen = len;
                    ans = curr;
                } 
                else if (len == minLen && curr < ans) {
                    ans = curr;
                }
            }
        }

        return ans;
    }
};