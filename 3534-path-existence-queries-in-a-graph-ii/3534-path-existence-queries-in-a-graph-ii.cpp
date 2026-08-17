class Solution {
public:
    vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        vector<pair<int,int>> a(n);

        for (int i = 0; i < n; i++)
            a[i] = {nums[i], i};

        sort(a.begin(), a.end());

        vector<int> pos(n);
        vector<int> val(n);

        for (int i = 0; i < n; i++) {
            val[i] = a[i].first;
            pos[a[i].second] = i;
        }

        vector<int> nxt(n);

        int r = 0;

        for (int i = 0; i < n; i++) {
            r = max(r, i);

            while (r + 1 < n && val[r + 1] - val[i] <= maxDiff)
                r++;

            nxt[i] = r;
        }

        int LOG = 18;

        while ((1 << LOG) <= n)
            LOG++;

        vector<vector<int>> up(LOG, vector<int>(n));

        for (int i = 0; i < n; i++)
            up[0][i] = nxt[i];

        for (int k = 1; k < LOG; k++) {
            for (int i = 0; i < n; i++) {
                up[k][i] = up[k - 1][up[k - 1][i]];
            }
        }

        vector<int> ans;

        for (auto &q : queries) {
            int u = q[0];
            int v = q[1];

            int x = pos[u];
            int y = pos[v];

            if (x == y) {
                ans.push_back(0);
                continue;
            }

            if (x > y)
                swap(x, y);

            if (nxt[x] >= y) {
                ans.push_back(1);
                continue;
            }

            int cur = x;
            int jumps = 0;

            for (int k = LOG - 1; k >= 0; k--) {
                if (up[k][cur] < y) {
                    cur = up[k][cur];
                    jumps += (1 << k);
                }
            }

            if (nxt[cur] >= y)
                ans.push_back(jumps + 1);
            else
                ans.push_back(-1);
        }

        return ans;
    }
};