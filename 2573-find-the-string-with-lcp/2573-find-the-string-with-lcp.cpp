class Solution {
public:
    string findTheString(vector<vector<int>>& lcp) {
        int n = lcp.size();
        string word(n, '?');
        char c = 'a';

        for (int i = 0; i < n; ++i) {
            if (word[i] != '?') continue;

            if (c > 'z') return "";

            word[i] = c;

            for (int j = i + 1; j < n; ++j) {
                if (lcp[i][j] > 0) {
                    word[j] = c;
                }
            }

            ++c;
        }

        vector<vector<int>> dp(n + 1, vector<int>(n + 1));

        for (int i = n - 1; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j) {
                if (word[i] == word[j]) {
                    dp[i][j] = 1 + dp[i + 1][j + 1];
                }

                if (dp[i][j] != lcp[i][j]) {
                    return "";
                }
            }
        }

        return word;
    }
};