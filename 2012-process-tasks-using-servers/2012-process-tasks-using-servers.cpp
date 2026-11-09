class Solution {
public:
    vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {

        int n = servers.size();
        int m = tasks.size();

        // Available servers: {weight, index}
        priority_queue<
            pair<int, int>,
            vector<pair<int, int>>,
            greater<pair<int, int>>
        > available;

        // Busy servers: {freeTime, weight, index}
        priority_queue<
            tuple<long long, int, int>,
            vector<tuple<long long, int, int>>,
            greater<tuple<long long, int, int>>
        > busy;

        // Initially, all servers are available
        for (int i = 0; i < n; i++) {
            available.push({servers[i], i});
        }

        vector<int> ans(m);

        long long time = 0;

        for (int j = 0; j < m; j++) {

            // Current task arrives at second j
            time = max(time, (long long)j);

            // Release all servers that are free
            while (!busy.empty() && get<0>(busy.top()) <= time) {

                auto [freeTime, weight, index] = busy.top();

                busy.pop();

                available.push({weight, index});
            }

            // If no server is available, wait
            if (available.empty()) {

                time = get<0>(busy.top());

                // Release all servers that become free at this time
                while (!busy.empty() && get<0>(busy.top()) <= time) {

                    auto [freeTime, weight, index] = busy.top();

                    busy.pop();

                    available.push({weight, index});
                }
            }

            // Select the server with smallest weight and index
            auto [weight, index] = available.top();

            available.pop();

            ans[j] = index;

            // Calculate when this server becomes free
            long long freeTime = time + tasks[j];

            busy.push({freeTime, weight, index});
        }

        return ans;
    }
};