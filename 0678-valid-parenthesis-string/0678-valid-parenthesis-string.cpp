class Solution {
public:
    bool checkValidString(string s) {
        int low = 0;   // Minimum possible number of open '('
        int high = 0;  // Maximum possible number of open '('

        for (char c : s) {

            if (c == '(') {
                low++;
                high++;
            }

            else if (c == ')') {
                low--;
                high--;
            }

            else { // '*'
                // '*' can be ')', '(' or empty
                low--;   // Treat '*' as ')'
                high++;  // Treat '*' as '('
            }

            // We can never have negative open brackets
            if (high < 0)
                return false;

            // Minimum cannot be negative
            // because we can treat some '*' as empty/'('
            low = max(low, 0);
        }

        // If minimum possible open brackets is 0,
        // we can make the string valid.
        return low == 0;
    }
};