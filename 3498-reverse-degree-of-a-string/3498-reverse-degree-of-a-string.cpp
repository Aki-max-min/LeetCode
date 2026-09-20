class Solution {
public:
    int reverseDegree(string s) {
        int pos=1;
        int ans=0;
        for(char a: s){
            int rev=26-(a-'a');
            ans+=rev*pos;
            pos++;
        }
        return ans;   
    }
};