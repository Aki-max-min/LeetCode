class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        if (head == nullptr || head->next == nullptr || head->next->next == nullptr) {
            return {-1, -1};
        }

        ListNode* prev = head;
        ListNode* curr = head->next;

        int index = 1;

        int firstCritical = -1;
        int prevCritical = -1;
        int minDistance = INT_MAX;

        while (curr->next != nullptr) {
            ListNode* next = curr->next;

            // Check if current node is a local maxima or local minima
            bool isMax = (curr->val > prev->val && curr->val > next->val);
            bool isMin = (curr->val < prev->val && curr->val < next->val);

            if (isMax || isMin) {
                if (firstCritical == -1) {
                    firstCritical = index;
                } else {
                    // Distance from previous critical point
                    minDistance = min(minDistance, index - prevCritical);
                }

                prevCritical = index;
            }

            prev = curr;
            curr = curr->next;
            index++;
        }

        // Less than 2 critical points
        if (firstCritical == -1 || firstCritical == prevCritical) {
            return {-1, -1};
        }

        int maxDistance = prevCritical - firstCritical;

        return {minDistance, maxDistance};
    }
};