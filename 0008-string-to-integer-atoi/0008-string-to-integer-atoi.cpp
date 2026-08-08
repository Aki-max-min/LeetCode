class Solution {
public:

    int myAtoi(string s, int i = 0) {

        // Skip leading spaces
        while (i < s.size() && s[i] == ' ')
            i++;

        // Default sign is positive
        int sign = 1;

        // Check for + or -
        if (i < s.size() && (s[i] == '-' || s[i] == '+')) {
            sign = (s[i] == '-') ? -1 : 1;
            i++;   // IMPORTANT: move past the sign
        }

        return helper(s, i, 0, sign);
    }


    int helper(const string &s, int i, long long num, int sign) {

        // Stop at end of string or non-digit
        if (i >= s.size() || !isdigit(s[i]))
            return (int)(sign * num);

        // Add current digit
        num = num * 10 + (s[i] - '0');

        // Check overflow
        if (sign * num <= -2147483648LL)
            return -2147483648;

        if (sign * num >= 2147483647LL)
            return 2147483647;

        // Process next digit
        return helper(s, i + 1, num, sign);
    }
};