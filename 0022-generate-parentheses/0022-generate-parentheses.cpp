class Solution {
public:
    vector<string> generateParenthesis(int n) {

        // Stores the current parentheses string
        vector<char> stack;

        // Stores all valid answers
        vector<string> res;

        // Backtracking function
        function<void(int, int)> backtrack = 
            [&](int openN, int closedN) {

            // If we have used n '(' and n ')',
            // we have a complete valid string
            if (openN == n && closedN == n) {
                
                // Convert vector<char> into string
                res.push_back(string(stack.begin(), stack.end()));
                return;
            }

            // We can add '(' only if we haven't
            // used n opening brackets yet
            if (openN < n) {

                stack.push_back('(');

                // Move to the next state
                backtrack(openN + 1, closedN);

                // Remove '(' to try another possibility
                stack.pop_back();
            }

            // We can add ')' only if the number
            // of closing brackets is less than opening brackets
            if (closedN < openN) {

                stack.push_back(')');

                // Move to the next state
                backtrack(openN, closedN + 1);

                // Remove ')' to try another possibility
                stack.pop_back();
            }
        };

        // Start with 0 opening and 0 closing brackets
        backtrack(0, 0);

        // Return all valid combinations
        return res;
    }
};