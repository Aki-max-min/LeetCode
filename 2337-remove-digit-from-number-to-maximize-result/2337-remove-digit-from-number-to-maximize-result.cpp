class Solution {
public:
    string removeDigit(string number, char digit) {
        int n=number.length();
        for(int i=0;i<n;i++){
            if(number[i]==digit ){
                if((i+1)<n && number[i+1]>digit){
                    number.erase(i, 1);
                    return number; 
                }
            }
        }
        int pos=number.rfind(digit);
        number.erase(pos,1);
        return number;
    }
};