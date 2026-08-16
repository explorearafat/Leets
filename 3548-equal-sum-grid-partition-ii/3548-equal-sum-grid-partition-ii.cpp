class Solution {
public:
    bool canRemove(const vector<vector<int>>& g, bool horizontal, int cut,
                   bool firstSide, long long diff,
                   const unordered_map<int,int>& freq) {
        int m = g.size();
        int n = g[0].size();

        if (horizontal) {
            int top = cut + 1;
            int bottom = m - cut - 1;
            int h = firstSide ? top : bottom;

            if (n == 1) {
                if (h == 1) return false;
                if (firstSide) {
                    return g[0][0] == diff || g[top - 1][0] == diff;
                } else {
                    return g[cut + 1][0] == diff || g[m - 1][0] == diff;
                }
            }

            if (h == 1) {
                int r = firstSide ? 0 : cut + 1;
                return g[r][0] == diff || g[r][n - 1] == diff;
            }

            return freq.find((int)diff) != freq.end();
        }

        int left = cut + 1;
        int right = n - cut - 1;
        int w = firstSide ? left : right;

        if (m == 1) {
            if (w == 1) return false;
            if (firstSide) {
                return g[0][0] == diff || g[0][left - 1] == diff;
            } else {
                return g[0][cut + 1] == diff || g[0][n - 1] == diff;
            }
        }

        if (w == 1) {
            int c = firstSide ? 0 : cut + 1;
            return g[0][c] == diff || g[m - 1][c] == diff;
        }

        return freq.find((int)diff) != freq.end();
    }

    bool canPartitionGrid(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        long long total = 0;

        unordered_map<int,int> all;
        for (auto& row : grid) {
            for (int x : row) {
                total += x;
                all[x]++;
            }
        }

        if (m > 1) {
            unordered_map<int,int> top, bottom = all;
            long long topSum = 0;

            for (int i = 0; i < m - 1; ++i) {
                for (int j = 0; j < n; ++j) {
                    int x = grid[i][j];
                    top[x]++;
                    if (--bottom[x] == 0) bottom.erase(x);
                    topSum += x;
                }

                long long bottomSum = total - topSum;

                if (topSum == bottomSum) return true;

                long long diff = llabs(topSum - bottomSum);

                if (topSum > bottomSum) {
                    if (canRemove(grid, true, i, true, diff, top))
                        return true;
                } else {
                    if (canRemove(grid, true, i, false, diff, bottom))
                        return true;
                }
            }
        }

        if (n > 1) {
            unordered_map<int,int> left, right = all;
            long long leftSum = 0;

            for (int j = 0; j < n - 1; ++j) {
                for (int i = 0; i < m; ++i) {
                    int x = grid[i][j];
                    left[x]++;
                    if (--right[x] == 0) right.erase(x);
                    leftSum += x;
                }

                long long rightSum = total - leftSum;

                if (leftSum == rightSum) return true;

                long long diff = llabs(leftSum - rightSum);

                if (leftSum > rightSum) {
                    if (canRemove(grid, false, j, true, diff, left))
                        return true;
                } else {
                    if (canRemove(grid, false, j, false, diff, right))
                        return true;
                }
            }
        }

        return false;
    }
};