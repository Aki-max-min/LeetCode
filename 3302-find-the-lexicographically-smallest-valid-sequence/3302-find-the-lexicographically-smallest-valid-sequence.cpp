#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();

        // Store positions of every character in word1
        vector<vector<int>> pos(26);

        for (int i = 0; i < n; i++) {
            pos[word1[i] - 'a'].push_back(i);
        }

        /*
            exact[j] =
            latest index from which word2[j...] can be
            matched EXACTLY as a subsequence.

            one[j] =
            latest index from which word2[j...] can be
            matched using AT MOST ONE mismatch.
        */

        vector<int> exact(m + 1, -1);
        vector<int> one(m + 1, -1);

        // Empty suffix can start at n
        exact[m] = n;
        one[m] = n;

        // Find contiguous runs in word1
        vector<int> runStart(n), runEnd(n);

        for (int i = 0; i < n; i++) {
            if (i == 0 || word1[i] != word1[i - 1])
                runStart[i] = i;
            else
                runStart[i] = runStart[i - 1];
        }

        for (int i = n - 1; i >= 0; i--) {
            if (i == n - 1 || word1[i] != word1[i + 1])
                runEnd[i] = i;
            else
                runEnd[i] = runEnd[i + 1];
        }

        // Find the latest occurrence of c strictly before bound
        auto prevOccurrence = [&](char c, int bound) {
            auto &v = pos[c - 'a'];

            int k = lower_bound(v.begin(), v.end(), bound) - v.begin();

            if (k == 0)
                return -1;

            return v[k - 1];
        };

        /*
            Build exact[] and one[] from right to left.
        */
        for (int j = m - 1; j >= 0; j--) {

            // Case 1: word2[j] is matched exactly
            exact[j] = prevOccurrence(word2[j], exact[j + 1]);

            /*
                For one[j], there are two possibilities:

                1. Match word2[j] exactly and use the
                   one allowed mismatch later.

                2. Change word1[i] into word2[j] here,
                   meaning the remaining suffix must match exactly.
            */

            int exactCurrent =
                prevOccurrence(word2[j], one[j + 1]);

            int mismatchCurrent = -1;

            int bound = exact[j + 1];

            if (bound > 0) {

                int p = bound - 1;

                if (word1[p] != word2[j]) {
                    // We can use this position as the mismatch
                    mismatchCurrent = p;
                }
                else {
                    /*
                        p has the same character as word2[j].

                        We need the closest position before p
                        having a DIFFERENT character.

                        runStart[p] is the beginning of the
                        consecutive block of this character.
                    */
                    mismatchCurrent = runStart[p] - 1;
                }
            }

            one[j] = max(exactCurrent, mismatchCurrent);
        }

        vector<int> answer;

        int prev = -1;

        // false = mismatch has not been used
        // true  = mismatch has already been used
        bool usedMismatch = false;

        for (int j = 0; j < m; j++) {

            char target = word2[j];

            /*
                If the mismatch was already used,
                we MUST match the remaining characters exactly.
            */
            if (usedMismatch) {

                auto &v = pos[target - 'a'];

                int k =
                    lower_bound(v.begin(), v.end(), prev + 1)
                    - v.begin();

                if (k == v.size())
                    return {};

                int idx = v[k];

                // Remaining suffix must also be exactly matchable
                if (idx >= exact[j + 1])
                    return {};

                answer.push_back(idx);
                prev = idx;
            }

            /*
                We still have our one mismatch available.
            */
            else {

                /*
                    Option 1:
                    Use an exact occurrence of target here.

                    Then the remaining suffix may use
                    the one mismatch.
                */
                auto &v = pos[target - 'a'];

                int k =
                    lower_bound(v.begin(), v.end(), prev + 1)
                    - v.begin();

                int exactIdx = n;

                if (k < v.size()) {
                    exactIdx = v[k];

                    if (exactIdx >= one[j + 1])
                        exactIdx = n;
                }

                /*
                    Option 2:
                    Use the mismatch at the current position.

                    Then the remaining suffix must be exact.
                */
                int mismatchIdx = prev + 1;

                if (mismatchIdx < n &&
                    word1[mismatchIdx] == target) {

                    // Skip the whole run of the same character
                    mismatchIdx = runEnd[mismatchIdx] + 1;
                }

                if (mismatchIdx >= n ||
                    mismatchIdx >= exact[j + 1]) {

                    mismatchIdx = n;
                }

                // Neither choice works
                if (exactIdx == n && mismatchIdx == n)
                    return {};

                /*
                    Take whichever gives the smaller index.

                    This is crucial because the problem asks for
                    lexicographically smallest INDICES.
                */
                if (exactIdx <= mismatchIdx) {

                    answer.push_back(exactIdx);
                    prev = exactIdx;
                }
                else {

                    answer.push_back(mismatchIdx);
                    prev = mismatchIdx;

                    usedMismatch = true;
                }
            }
        }

        return answer;
    }
};