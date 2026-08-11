class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int n=s.size();
        int hashlen=256;
        int hash[hashlen];
        for(int i=0;i<hashlen;++i){
            hash[i]=-1;
        }
        int left=0,right=0,maxlen=0;
        while(right<n){
            if(hash [s[right]]!=-1){
                left=max(hash [s[right]]+1,left);
            }
            int len =right-left+1;
            maxlen=max(maxlen,len);
            hash[s[right]]=right;
            right++;
        }
        return maxlen;

        
    }
};