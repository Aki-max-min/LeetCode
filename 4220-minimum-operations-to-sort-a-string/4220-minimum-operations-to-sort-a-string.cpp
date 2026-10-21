class Solution {
public:
    int minOperations(string s) {
        string sorted = s;
        sort(sorted.begin(), sorted.end());

        if (s == sorted) {
            return 0;
        }

        int n = s.size();

        if (n == 2) {
            return -1;
        }

        if (s[0] == sorted[0] || s[n - 1] == sorted[n - 1]) {
            return 1;
        }

        int minCount = count(s.begin(), s.end(), sorted[0]);
        int maxCount = count(s.begin(), s.end(), sorted[n - 1]);

        if (s[0] == sorted[n - 1] &&
            s[n - 1] == sorted[0] &&
            minCount == 1 &&
            maxCount == 1) {
            return 3;
        }

        return 2;
    }
};