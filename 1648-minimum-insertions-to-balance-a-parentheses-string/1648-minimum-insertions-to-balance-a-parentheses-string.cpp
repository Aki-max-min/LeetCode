class Solution {
public:
    int minInsertions(string s) {
        int open = 0;
        int insertions = 0;

        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '(') {
                open++;
            } 
            else {
                if (i + 1 < s.length() && s[i + 1] == ')') {
                    i++;  // Consume the second ')'
                } 
                else {
                    insertions++;  // Insert a missing ')'
                }

                if (open > 0) {
                    open--;
                } 
                else {
                    insertions++;  // Insert a missing '('
                }
            }
        }

        return insertions + open * 2;
    }
};