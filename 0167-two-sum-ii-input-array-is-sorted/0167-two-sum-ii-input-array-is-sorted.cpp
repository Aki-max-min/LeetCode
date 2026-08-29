class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int n=numbers.size();
        vector<int> result;
        int left=0;
        int right=n-1;
        while(left<right){
            int sum=numbers[left]+ numbers[right];
            if(sum==target){
                result.push_back(left+1);
                result.push_back(right+1);
                return result;
            }
            if(sum<target){
                left++;
            }else{
                right--;
            }
        }
    return {};   
    }
};