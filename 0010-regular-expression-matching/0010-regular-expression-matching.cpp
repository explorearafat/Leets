class Solution {
public:
    bool isMatch(string s, string p) {
        int n = s.size(), m = p.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));

        function<bool(int, int)> solve = [&](int i, int j) -> bool {
            if (j == m) return i == n;

            if (dp[i][j] != -1) return dp[i][j] == 1;

            bool firstMatch = i < n && (s[i] == p[j] || p[j] == '.');

            if (j + 1 < m && p[j + 1] == '*') {
                return dp[i][j] = (
                    solve(i, j + 2) ||
                    (firstMatch && solve(i + 1, j))
                );
            }

            return dp[i][j] = firstMatch && solve(i + 1, j + 1);
        };

        return solve(0, 0);
    }
};