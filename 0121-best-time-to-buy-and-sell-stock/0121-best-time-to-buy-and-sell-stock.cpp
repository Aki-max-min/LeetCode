class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n=prices.size();
        int minp=prices[0];
        int maxp=0;
        for(int i=0;i<n;i++){
            minp=min(minp,prices[i]);
            maxp=max(maxp,prices[i]-minp);
        }
        return maxp;
    }
};