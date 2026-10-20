class Solution {
public:
    int sortableIntegers(vector<int>& nums) {
        int n = nums.size();
        long long ans = 0;

        vector<int> sorted = nums;
        sort(sorted.begin(), sorted.end());

        for (int k = 1; k <= n; k++) {
            if (n % k != 0)
                continue;

            bool valid = true;

            for (int start = 0; start < n && valid; start += k) {
                int len = k;
                int descents = 0;

                for (int i = 0; i < len; i++) {
                    int curr = nums[start + i];
                    int next = nums[start + (i + 1) % len];

                    if (curr > next)
                        descents++;
                }

                if (descents > 1)
                    valid = false;
            }

            if (valid) {
                // Check whether the resulting blocks can collectively
                // produce the globally sorted array.
                for (int start = 0; start < n && valid; start += k) {
                    vector<int> block(nums.begin() + start,
                                      nums.begin() + start + k);

                    sort(block.begin(), block.end());

                    for (int i = 0; i < k; i++) {
                        if (block[i] != sorted[start + i]) {
                            valid = false;
                            break;
                        }
                    }
                }
            }

            if (valid)
                ans += k;
        }

        return static_cast<int>(ans);
    }
};