class Solution {
public:
    int totalNumbers(vector<int>& digits) {
        int count = 0;

        // Count how many times each digit appears
        vector<int> freq(10, 0);

        for (int d : digits) {
            freq[d]++;
        }

        // Try every possible 3-digit number
        for (int num = 100; num <= 999; num++) {

            // Number must be even
            if (num % 2 != 0)
                continue;

            int x = num;
            vector<int> needed(10, 0);

            // Extract its 3 digits
            while (x > 0) {
                needed[x % 10]++;
                x /= 10;
            }

            // Check if we have enough copies of every digit
            bool possible = true;

            for (int d = 0; d <= 9; d++) {
                if (needed[d] > freq[d]) {
                    possible = false;
                    break;
                }
            }

            if (possible)
                count++;
        }

        return count;
    }
};