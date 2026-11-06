class Solution {
public:
    vector<int> countServers(int n, vector<vector<int>>& logs,
                             int x, vector<int>& queries) {

        sort(logs.begin(), logs.end(),
             [](const vector<int>& a, const vector<int>& b) {
                 return a[1] < b[1];
             });

        int m = queries.size();

        vector<pair<int, int>> q;

        for (int i = 0; i < m; i++) {
            q.push_back({queries[i], i});
        }

        sort(q.begin(), q.end());

        vector<int> freq(n + 1, 0);
        vector<int> ans(m);

        int left = 0;
        int right = 0;
        int activeServers = 0;

        for (auto& query : q) {

            int time = query.first;
            int index = query.second;

            int startTime = time - x;

            // Add logs with time <= query time
            while (right < logs.size() &&
                   logs[right][1] <= time) {

                int server = logs[right][0];

                if (freq[server] == 0) {
                    activeServers++;
                }

                freq[server]++;
                right++;
            }

            // Remove logs with time < startTime
            while (left < right &&
                   logs[left][1] < startTime) {

                int server = logs[left][0];

                freq[server]--;

                if (freq[server] == 0) {
                    activeServers--;
                }

                left++;
            }

            ans[index] = n - activeServers;
        }

        return ans;
    }
};