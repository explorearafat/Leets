class Solution {
public:
    vector<int> survivedRobotsHealths(vector<int>& positions, vector<int>& healths, string directions) {
        int n = positions.size();
        vector<int> order(n);
        iota(order.begin(), order.end(), 0);

        sort(order.begin(), order.end(), [&](int a, int b) {
            return positions[a] < positions[b];
        });

        vector<int> st;

        for (int idx : order) {
            if (directions[idx] == 'R') {
                st.push_back(idx);
            } else {
                while (!st.empty()) {
                    int j = st.back();

                    if (healths[j] < healths[idx]) {
                        healths[idx]--;
                        healths[j] = 0;
                        st.pop_back();
                    } else if (healths[j] > healths[idx]) {
                        healths[j]--;
                        healths[idx] = 0;
                        break;
                    } else {
                        healths[j] = 0;
                        healths[idx] = 0;
                        st.pop_back();
                        break;
                    }
                }
            }
        }

        vector<int> ans;
        for (int i = 0; i < n; i++) {
            if (healths[i] > 0) {
                ans.push_back(healths[i]);
            }
        }

        return ans;
    }
};