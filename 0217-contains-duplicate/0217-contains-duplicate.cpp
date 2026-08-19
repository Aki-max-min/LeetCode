class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        int n=nums.size();
        unordered_map<int,int> mp;
        for(int n:nums){
            mp[n]++;
            if(mp[n]>=2){
                return true;
            }
        }
    return false; 
        
    }
};