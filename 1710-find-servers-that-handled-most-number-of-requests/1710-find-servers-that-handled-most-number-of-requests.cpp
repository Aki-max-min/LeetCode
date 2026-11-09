class Solution {
public:
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {
        vector<int> cnt(k, 0);

        // Available servers
        set<int> available;

        for (int i = 0; i < k; i++) {
            available.insert(i);
        }

        // {finishTime, serverID}
        priority_queue<
            pair<long long, int>,
            vector<pair<long long, int>>,
            greater<pair<long long, int>>
        > busy;

        int n = arrival.size();

        for (int i = 0; i < n; i++) {

            // Release servers that have completed their requests
            while (!busy.empty() && busy.top().first <= arrival[i]) {
                int server = busy.top().second;

                busy.pop();

                available.insert(server);
            }

            // If all servers are busy, drop the request
            if (available.empty()) {
                continue;
            }

            // Preferred server
            int preferred = i % k;

            // Find the next available server
            auto it = available.lower_bound(preferred);

            // Wrap around if necessary
            if (it == available.end()) {
                it = available.begin();
            }

            int server = *it;

            // Assign request
            available.erase(it);

            cnt[server]++;

            long long finishTime = (long long)arrival[i] + load[i];

            busy.push({finishTime, server});
        }

        // Find maximum number of requests handled
        int maxRequests = *max_element(cnt.begin(), cnt.end());

        vector<int> ans;

        // Collect all busiest servers
        for (int i = 0; i < k; i++) {
            if (cnt[i] == maxRequests) {
                ans.push_back(i);
            }
        }

        return ans;
    }
};