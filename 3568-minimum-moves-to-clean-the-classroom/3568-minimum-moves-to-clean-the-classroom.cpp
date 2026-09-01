class Solution {
public:
    struct State {
        int r, c;
        int mask;
        int energyLeft;
        int dist;
    };

    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size();
        int n = classroom[0].size();

        int startR = 0, startC = 0;
        vector<pair<int, int>> litter;

        // Find start and litter positions
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (classroom[i][j] == 'S') {
                    startR = i;
                    startC = j;
                } 
                else if (classroom[i][j] == 'L') {
                    litter.push_back({i, j});
                }
            }
        }

        int k = litter.size();

        if (k == 0) return 0;

        int fullMask = (1 << k) - 1;

        // Map each litter cell to a bit
        vector<vector<int>> litterId(m, vector<int>(n, -1));

        for (int i = 0; i < k; i++) {
            litterId[litter[i].first][litter[i].second] = i;
        }

        /*
        best[cell][mask] = maximum energy remaining when reaching
        this cell with this collected litter mask.

        Flattened for speed and memory efficiency.
        */
        int totalCells = m * n;
        int totalMasks = 1 << k;

        vector<int> best(totalCells * totalMasks, -1);

        auto getIndex = [&](int r, int c, int mask) {
            int cell = r * n + c;
            return cell * totalMasks + mask;
        };

        queue<State> q;

        q.push({startR, startC, 0, energy, 0});
        best[getIndex(startR, startC, 0)] = energy;

        int dr[4] = {-1, 1, 0, 0};
        int dc[4] = {0, 0, -1, 1};

        while (!q.empty()) {
            State cur = q.front();
            q.pop();

            int r = cur.r;
            int c = cur.c;
            int mask = cur.mask;
            int energyLeft = cur.energyLeft;
            int dist = cur.dist;

            // Ignore outdated dominated states
            if (energyLeft < best[getIndex(r, c, mask)]) {
                continue;
            }

            // All litter collected
            if (mask == fullMask) {
                return dist;
            }

            // Cannot move with zero energy
            if (energyLeft == 0) {
                continue;
            }

            for (int d = 0; d < 4; d++) {
                int nr = r + dr[d];
                int nc = c + dc[d];

                // Out of bounds
                if (nr < 0 || nr >= m || nc < 0 || nc >= n) {
                    continue;
                }

                // Obstacle
                if (classroom[nr][nc] == 'X') {
                    continue;
                }

                int newEnergy = energyLeft - 1;
                int newMask = mask;

                // Collect litter
                if (litterId[nr][nc] != -1) {
                    newMask |= (1 << litterId[nr][nc]);
                }

                // Reset energy
                if (classroom[nr][nc] == 'R') {
                    newEnergy = energy;
                }

                int idx = getIndex(nr, nc, newMask);

                // Only continue if this state has more energy
                // than any previously seen equivalent state
                if (newEnergy > best[idx]) {
                    best[idx] = newEnergy;

                    q.push({
                        nr,
                        nc,
                        newMask,
                        newEnergy,
                        dist + 1
                    });
                }
            }
        }

        return -1;
    }
};