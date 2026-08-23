class Solution {
public:
    bool sumGame(string num) {
        int n = num.size();
        int half = n / 2;

        int leftSum = 0, rightSum = 0;
        int leftQ = 0, rightQ = 0;

        for (int i = 0; i < half; i++) {
            if (num[i] == '?')
                leftQ++;
            else
                leftSum += num[i] - '0';
        }

        for (int i = half; i < n; i++) {
            if (num[i] == '?')
                rightQ++;
            else
                rightSum += num[i] - '0';
        }

        // If the number of '?' is odd, Alice can always make
        // the final sums unequal.
        if ((leftQ + rightQ) % 2 == 1)
            return true;

        int diff = leftSum - rightSum;
        int qDiff = leftQ - rightQ;

        // Bob can win only if the existing difference can be
        // exactly balanced by the '?' characters.
        return abs(diff + (qDiff / 2) * 9) != 0;
    }
};