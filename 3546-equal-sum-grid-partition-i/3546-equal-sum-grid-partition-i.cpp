class Solution {
public:
    bool canPartitionGrid(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        long long total = 0;

        for (auto& row : grid) {
            for (int x : row) {
                total += x;
            }
        }

        long long cur = 0;

        for (int i = 0; i < m - 1; i++) {
            for (int j = 0; j < n; j++) {
                cur += grid[i][j];
            }

            if (cur * 2 == total) {
                return true;
            }
        }

        cur = 0;

        for (int j = 0; j < n - 1; j++) {
            for (int i = 0; i < m; i++) {
                cur += grid[i][j];
            }

            if (cur * 2 == total) {
                return true;
            }
        }

        return false;
    }
};