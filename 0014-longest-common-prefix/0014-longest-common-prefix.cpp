class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if(strs.empty()) return "";
        string ans="";
        sort(strs.begin(),strs.end());
        string start = strs[0];
        string end =strs[strs.size()-1];
        int minlength = min(start.size(),end.size());
        for(int i=0;i<minlength;i++){
            if(start[i]!=end[i]) break;
            ans+=start[i];
        }
        return ans;


        
    }
};