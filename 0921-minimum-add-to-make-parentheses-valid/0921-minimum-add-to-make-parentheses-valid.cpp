class Solution {
public:
    int minAddToMakeValid(string s) {
        int open = 0;  // unmatched '('
        int ans = 0;   // parentheses we need to add

        for (char c : s) {
            if (c == '(') {
                open++;
            }
            else { // c == ')'
                if (open > 0) {
                    open--;  // match with an existing '('
                }
                else {
                    ans++;   // need to add '(' before this ')'
                }
            }
        }

        // Any remaining '(' need a ')' each
        ans += open;

        return ans;
    }
};