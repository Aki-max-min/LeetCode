class Solution {
public:
    int scoreOfParentheses(string s) {
        stack<int> st;

        // Start with 0 as the base score
        st.push(0);

        for (char ch : s) {

            if (ch == '(') {
                // Start a new inner parentheses group
                st.push(0);
            }
            else {
                // Get the score inside the current ()
                int inside = st.top();
                st.pop();

                // Score of () = 1
                // Score of (A) = 2 * A
                int score;

                if (inside == 0)
                    score = 1;
                else
                    score = 2 * inside;

                // Add this score to the previous level
                st.top() += score;
            }
        }

        return st.top();
    }
};