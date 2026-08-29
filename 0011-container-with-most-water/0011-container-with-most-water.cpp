class Solution {
public:
    int maxArea(vector<int>& height) {
        int n=height.size();
        int left=0;
        int right=n-1;
        int ans=0;
        while(left<right){
            int maxwater=(right-left)*min(height[right],height[left]);
            ans=max(maxwater,ans);
            if(height[right]<height[left]){
                right--;
            }else{
                left++;
            }
        }
    return ans;

        
    }
};