class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int,int> mp;
        mp[0]=1;
        int prefixsum=0;
        int count =0;
        for(int i=0;i<nums.size();i++){
            prefixsum+=nums[i];
            if(mp.find(prefixsum-k)!=mp.end()){
                count+=mp[prefixsum-k];
            }
            mp[prefixsum]++;
        }
        return count;
        
    }
};