class Solution {
public:
    int countCommas(int n) {
        if (n < 1000) return 0;

        if (n < 1000000)
            return n - 999;

        return 999000 + (n - 999999) * 2;
    }
};