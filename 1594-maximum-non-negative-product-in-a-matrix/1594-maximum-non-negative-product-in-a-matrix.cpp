class Solution {
public:
    int maxProductPath(vector<vector<int>>& grid) {
        const long long MOD = 1e9 + 7;
        int m = grid.size(), n = grid[0].size();

        vector<vector<long long>> mx(m, vector<long long>(n));
        vector<vector<long long>> mn(m, vector<long long>(n));

        mx[0][0] = mn[0][0] = grid[0][0];

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (i == 0 && j == 0) continue;

                long long x = grid[i][j];

                long long maxPrev = LLONG_MIN;
                long long minPrev = LLONG_MAX;

                if (i > 0) {
                    maxPrev = max(maxPrev, mx[i - 1][j]);
                    minPrev = min(minPrev, mn[i - 1][j]);
                }

                if (j > 0) {
                    maxPrev = max(maxPrev, mx[i][j - 1]);
                    minPrev = min(minPrev, mn[i][j - 1]);
                }

                long long a = maxPrev * x;
                long long b = minPrev * x;

                mx[i][j] = max(a, b);
                mn[i][j] = min(a, b);
            }
        }

        if (mx[m - 1][n - 1] < 0)
            return -1;

        return mx[m - 1][n - 1] % MOD;
    }
};