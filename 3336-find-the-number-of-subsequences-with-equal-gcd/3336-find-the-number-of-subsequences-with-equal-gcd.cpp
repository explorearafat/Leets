class Solution {
public:
    static const int MOD = 1000000007;

    int subsequencePairCount(vector<int>& nums) {
        int m = *max_element(nums.begin(), nums.end());

        vector<vector<int>> dp(m + 1, vector<int>(m + 1));
        dp[0][0] = 1;

        for (int x : nums) {
            vector<vector<int>> ndp(m + 1, vector<int>(m + 1));

            for (int j = 0; j <= m; j++) {
                for (int k = 0; k <= m; k++) {
                    if (dp[j][k] == 0) continue;

                    int val = dp[j][k];

                    ndp[j][k] = (ndp[j][k] + val) % MOD;

                    int nj = gcd(j, x);
                    ndp[nj][k] = (ndp[nj][k] + val) % MOD;

                    int nk = gcd(k, x);
                    ndp[j][nk] = (ndp[j][nk] + val) % MOD;
                }
            }

            dp.swap(ndp);
        }

        int ans = 0;

        for (int g = 1; g <= m; g++) {
            ans = (ans + dp[g][g]) % MOD;
        }

        return ans;
    }
};