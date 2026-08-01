class Solution {
public:
    string largestOddNumber(string num) {
        int lastodd = -1;
        int i=0;
        for(i = num.length(); i>=0;i--){
            if((num[i]-'0') % 2==1){
                lastodd= i;
                break;
            }
        }
        i = 0;
        while (i <= lastodd && num[i] == '0') i++;
        return num.substr(i, lastodd - i + 1);
    }
        
    
};