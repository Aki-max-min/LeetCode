class Solution {
public:
    bool checkDivisibility(int n) {
        int sum=0;
        int product=1;
        int original=n;
        while(n>0){
            int digit=n%10;
            sum=sum+digit;
            product=product*digit;
            n=n/10;
        }
        if(original%(sum+product)==0){
            return true;
        }
        return false;       
    }
};