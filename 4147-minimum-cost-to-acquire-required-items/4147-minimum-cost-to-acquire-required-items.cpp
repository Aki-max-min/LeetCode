class Solution {
public:
    long long minimumCost(int cost1, int cost2, int costBoth, int need1, int need2) {

        long long common = min(need1, need2);

        long long ans = 0;

        // Buy items that satisfy both requirements
        ans += common * min(costBoth, cost1 + cost2);

        // Remaining type 1 requirement
        ans += (need1 - common) * min(cost1, costBoth);

        // Remaining type 2 requirement
        ans += (need2 - common) * min(cost2, costBoth);

        return ans;
    }
};