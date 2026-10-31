class Solution {
public:
    int shortestPath(int n, vector<vector<int>>& edges, string labels, int k) {

        vector<vector<pair<int,int>>> adj(n);

        for (auto &e : edges) {
            adj[e[0]].push_back({e[1], e[2]});
        }

        // State: node, last character, consecutive count
        // Encode state into a single integer.
        auto encode = [&](int node, int ch, int cnt) {
            return ((long long)node * 26 + ch) * (k + 1) + cnt;
        };

        // {cost, node, last character, count}
        using T = tuple<long long,int,int,int>;

        priority_queue<T, vector<T>, greater<T>> pq;

        unordered_map<long long, long long> dist;

        int start = labels[0] - 'a';

        long long startState = encode(0, start, 1);

        dist[startState] = 0;
        pq.push({0, 0, start, 1});

        while (!pq.empty()) {

            auto [cost, node, last, cnt] = pq.top();
            pq.pop();

            long long state = encode(node, last, cnt);

            if (dist[state] != cost)
                continue;

            if (node == n - 1)
                return (int)cost;

            for (auto [next, weight] : adj[node]) {

                int ch = labels[next] - 'a';

                int newCnt = (ch == last) ? cnt + 1 : 1;

                if (newCnt > k)
                    continue;

                long long newCost = cost + weight;

                long long newState = encode(next, ch, newCnt);

                if (!dist.count(newState) || newCost < dist[newState]) {

                    dist[newState] = newCost;

                    pq.push({
                        newCost,
                        next,
                        ch,
                        newCnt
                    });
                }
            }
        }

        return -1;
    }
};