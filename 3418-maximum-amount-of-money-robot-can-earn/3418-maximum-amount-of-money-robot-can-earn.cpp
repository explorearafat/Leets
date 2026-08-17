class Solution {
public:
    int maximumAmount(vector<vector<int>>& coins) {
        int m = coins.size(), n = coins[0].size();
        const long long NEG = -(1LL << 60);

        vector<vector<array<long long, 3>>> dp(
            m, vector<array<long long, 3>>(n, {NEG, NEG, NEG})
        );

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == 0 && j == 0) {
                    dp[i][j][0] = coins[i][j];
                    if (coins[i][j] < 0)
                        dp[i][j][1] = 0;
                    continue;
                }

                array<long long, 3> prev = {NEG, NEG, NEG};

                if (i > 0) {
                    for (int k = 0; k <= 2; ++k)
                        prev[k] = max(prev[k], dp[i - 1][j][k]);
                }

                if (j > 0) {
                    for (int k = 0; k <= 2; ++k)
                        prev[k] = max(prev[k], dp[i][j - 1][k]);
                }

                for (int used = 0; used <= 2; ++used) {
                    if (prev[used] != NEG)
                        dp[i][j][used] = prev[used] + coins[i][j];

                    if (coins[i][j] < 0 && used > 0 && prev[used - 1] != NEG)
                        dp[i][j][used] = max(
                            dp[i][j][used],
                            prev[used - 1]
                        );
                }
            }
        }

        return max({
            dp[m - 1][n - 1][0],
            dp[m - 1][n - 1][1],
            dp[m - 1][n - 1][2]
        });
    }
};