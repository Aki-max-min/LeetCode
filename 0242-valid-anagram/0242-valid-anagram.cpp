class Solution {
public:
    bool isAnagram(string s, string t) {
        int m1[256]={0};
        if(s.size()!=t.size()) return false;
        for(char c: s){
            m1[c]++;
        }
        for(char c: t){
            m1[c]--;
        }
        for(int i=0;i<256;i++){
            if(m1[i]!=0) return false;
        }
        return true;
    }
};