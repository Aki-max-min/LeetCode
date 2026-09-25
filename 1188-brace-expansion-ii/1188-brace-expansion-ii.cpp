class Solution {
public:

    set<string> solve(string &s, int &i) {
        set<string> result;
        set<string> current = {""};

        while (i < s.size() && s[i] != '}') {

            // Comma -> union
            if (s[i] == ',') {
                result.insert(current.begin(), current.end());
                current = {""};
                i++;
            }

            // Opening brace -> recursively solve
            else if (s[i] == '{') {
                i++; // skip '{'

                set<string> inside = solve(s, i);

                i++; // skip '}'

                // Concatenate current with inside
                set<string> next;

                for (string a : current) {
                    for (string b : inside) {
                        next.insert(a + b);
                    }
                }

                current = next;
            }

            // Normal character
            else {
                char c = s[i];
                i++;

                set<string> next;

                for (string x : current) {
                    next.insert(x + c);
                }

                current = next;
            }
        }

        // Add final part
        result.insert(current.begin(), current.end());

        return result;
    }

    vector<string> braceExpansionII(string expression) {

        int i = 0;

        set<string> result = solve(expression, i);

        return vector<string>(result.begin(), result.end());
    }
};