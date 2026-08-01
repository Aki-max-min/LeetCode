class Solution {
public:
    bool rotateString(string s, string goal) {
        if(s.length() != goal.length()) return false;
        string double2 = s+s;
        return double2.find(goal)!= string::npos;
        
    }
};