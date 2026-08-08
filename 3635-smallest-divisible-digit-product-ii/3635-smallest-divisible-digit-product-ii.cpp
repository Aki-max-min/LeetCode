#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    // Prime factor contribution of digits 1..9
    int e2[10] = {0, 0, 1, 0, 2, 0, 1, 0, 3, 0};
    int e3[10] = {0, 0, 0, 1, 0, 0, 1, 0, 0, 2};
    int e5[10] = {0, 0, 0, 0, 0, 1, 0, 0, 0, 0};
    int e7[10] = {0, 0, 0, 0, 0, 0, 0, 1, 0, 0};

    int min23[50][35];

    int minDigits(int a, int b, int c, int d) {
        return min23[a][b] + c + d;
    }

    string buildSmallest(
        int len,
        int a,
        int b,
        int c,
        int d
    ) {
        if (minDigits(a, b, c, d) > len)
            return "";

        string ans;

        for (int pos = 0; pos < len; pos++) {

            int remaining = len - pos - 1;

            for (int digit = 1; digit <= 9; digit++) {

                int na = max(0, a - e2[digit]);
                int nb = max(0, b - e3[digit]);
                int nc = max(0, c - e5[digit]);
                int nd = max(0, d - e7[digit]);

                if (minDigits(na, nb, nc, nd)
                    <= remaining) {

                    ans.push_back('0' + digit);

                    a = na;
                    b = nb;
                    c = nc;
                    d = nd;

                    break;
                }
            }
        }

        return ans;
    }

    string smallestNumber(string num, long long t) {

        // ------------------------------------------
        // 1. Factorize t
        // ------------------------------------------

        int a = 0, b = 0, c = 0, d = 0;

        while (t % 2 == 0) {
            a++;
            t /= 2;
        }

        while (t % 3 == 0) {
            b++;
            t /= 3;
        }

        while (t % 5 == 0) {
            c++;
            t /= 5;
        }

        while (t % 7 == 0) {
            d++;
            t /= 7;
        }

        // Any remaining factor cannot be produced
        // by digits 1..9.
        if (t != 1)
            return "-1";


        // ------------------------------------------
        // 2. Precompute minimum digits for 2^a * 3^b
        // ------------------------------------------

        for (int i = 0; i < 50; i++) {
            for (int j = 0; j < 35; j++) {

                min23[i][j] = INT_MAX;

                // x = number of digit 6's
                for (int x = 0; x <= min(i, j); x++) {

                    int need2 = i - x;
                    int need3 = j - x;

                    // 8 gives 3 twos
                    // 9 gives 2 threes
                    int count =
                        x +
                        (need2 + 2) / 3 +
                        (need3 + 1) / 2;

                    min23[i][j] =
                        min(min23[i][j], count);
                }
            }
        }


        int n = num.size();


        // ------------------------------------------
        // 3. Check if num itself already works
        // ------------------------------------------

        bool zeroFree = true;

        int p2 = 0;
        int p3 = 0;
        int p5 = 0;
        int p7 = 0;

        for (char ch : num) {

            int digit = ch - '0';

            if (digit == 0) {
                zeroFree = false;
                continue;
            }

            p2 += e2[digit];
            p3 += e3[digit];
            p5 += e5[digit];
            p7 += e7[digit];
        }

        if (zeroFree &&
            p2 >= a &&
            p3 >= b &&
            p5 >= c &&
            p7 >= d) {

            return num;
        }


        // ------------------------------------------
        // 4. Prefix factor counts
        // ------------------------------------------

        vector<int> pref2(n + 1);
        vector<int> pref3(n + 1);
        vector<int> pref5(n + 1);
        vector<int> pref7(n + 1);

        vector<bool> zero(n + 1, false);

        for (int i = 0; i < n; i++) {

            int digit = num[i] - '0';

            pref2[i + 1] = pref2[i];
            pref3[i + 1] = pref3[i];
            pref5[i + 1] = pref5[i];
            pref7[i + 1] = pref7[i];

            zero[i + 1] = zero[i];

            if (digit == 0) {
                zero[i + 1] = true;
            }
            else {
                pref2[i + 1] += e2[digit];
                pref3[i + 1] += e3[digit];
                pref5[i + 1] += e5[digit];
                pref7[i + 1] += e7[digit];
            }
        }


        // ------------------------------------------
        // 5. Try to make a number of same length
        // ------------------------------------------

        for (int i = n - 1; i >= 0; i--) {

            // Prefix before i cannot contain zero.
            if (zero[i])
                continue;

            int original = num[i] - '0';

            // Increase current digit.
            for (int digit = original + 1;
                 digit <= 9;
                 digit++) {

                int cur2 = pref2[i] + e2[digit];
                int cur3 = pref3[i] + e3[digit];
                int cur5 = pref5[i] + e5[digit];
                int cur7 = pref7[i] + e7[digit];

                int need2 = max(0, a - cur2);
                int need3 = max(0, b - cur3);
                int need5 = max(0, c - cur5);
                int need7 = max(0, d - cur7);

                int remaining = n - i - 1;

                if (minDigits(
                        need2,
                        need3,
                        need5,
                        need7
                    ) <= remaining) {

                    string suffix =
                        buildSmallest(
                            remaining,
                            need2,
                            need3,
                            need5,
                            need7
                        );

                    if (remaining > 0 && suffix.empty())
                        continue;

                    string ans = num.substr(0, i);

                    ans.push_back('0' + digit);

                    ans += suffix;

                    return ans;
                }
            }
        }


        // ------------------------------------------
        // 6. Need more digits
        // ------------------------------------------

        int requiredLength =
            minDigits(a, b, c, d);

        /*
            IMPORTANT FIX:

            We don't only try n + 1.

            We need at least:
                n + 1

            because same-length numbers failed,

            AND at least:
                requiredLength

            because that's the minimum number of
            digits needed to satisfy t.
        */

        int newLen =
            max(n + 1, requiredLength);

        string ans =
            buildSmallest(
                newLen,
                a,
                b,
                c,
                d
            );

        if (ans.empty())
            return "-1";

        return ans;
    }
};