class Solution {
public:
    bool isPalindrome(string s) {
        string result="";
        for(char &c : s){
            c=tolower(c);
            if(isalnum(c)){
                result += c;
            }
        }
        if(result==""){
            return true;
        }
        int left=0;
        int right=result.length()-1;
        while(left<right){
            if(result[left]!=result[right]){
                return false;
            }
            left++;
            right--;
        }
    return true; 
    }
};