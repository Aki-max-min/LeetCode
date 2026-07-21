class Solution {
public:
    int maxActiveSectionsAfterTrade(string s) {
        int n = s.size();
        int ones = 0;
        for (char c : s) {
            if (c == '1') ones++;
        }

        string t = "1" + s + "1";
        int m = t.size();

        vector<pair<char, int>> seg;
        for (int i = 0; i < m;) {
            int j = i;
            while (j < m && t[j] == t[i]) j++;
            seg.push_back({t[i], j - i});
            i = j;
        }

        int best = 0;

        for (int i = 1; i + 1 < (int)seg.size(); i++) {
            if (seg[i].first == '1' &&
                seg[i - 1].first == '0' &&
                seg[i + 1].first == '0') {

                best = max(best, seg[i - 1].second + seg[i + 1].second);
            }
        }

        return ones + best;
    }
};