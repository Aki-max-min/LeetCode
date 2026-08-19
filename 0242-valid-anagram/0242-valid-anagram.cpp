class Solution {
public:
    bool isAnagram(string s, string t) {
        int mp[256]={0};
        if(s.size()!=t.size()) return false;
        for(int a:s){
            mp[a]++;
        }
        for(int a:t){
            mp[a]--;
        }
        for(int i=0;i<256;i++){
            if(mp[i]!=0){
                return false;
            }
        }
        return true;

        
    }
};