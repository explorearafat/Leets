class Solution {
public:
    string generateString(string str1, string str2) {
        int n = str1.size(), m = str2.size();
        int L = n + m - 1;

        vector<int> pi(m);
        for (int i = 1, j = 0; i < m; i++) {
            while (j > 0 && str2[i] != str2[j]) j = pi[j - 1];
            if (str2[i] == str2[j]) j++;
            pi[i] = j;
        }

        vector<int> match(L, 0);
        for (int i = 0, j = 0; i < L; i++) {
            while (j > 0 && str2[j] != '?') {
                j = pi[j - 1];
            }
        }

        vector<int> z(m);
        for (int i = 1, l = 0, r = 0; i < m; i++) {
            if (i <= r) z[i] = min(r - i + 1, z[i - l]);
            while (i + z[i] < m && str2[z[i]] == str2[i + z[i]]) z[i]++;
            if (i + z[i] - 1 > r) {
                l = i;
                r = i + z[i] - 1;
            }
        }

        string s = str2 + "#" + string(L, '{');
        int sz = s.size();
        vector<int> p(sz);
        for (int i = 1; i < sz; i++) {
            int j = p[i - 1];
            while (j > 0 && s[i] != s[j]) j = p[j - 1];
            if (s[i] == s[j]) j++;
            p[i] = j;
        }

        vector<int> required(L, 0);

        for (int i = 0; i < n; i++) {
            if (str1[i] == 'T') {
                for (int j = 0; j < m; j++) {
                    required[i + j] = max(required[i + j], 1);
                }
            }
        }

        string ans(L, 'a');

        for (int i = 0; i < n; i++) {
            if (str1[i] == 'T') {
                for (int j = 0; j < m; j++) {
                    char c = str2[j];
                    if (ans[i + j] == 'a' || ans[i + j] == '{') {
                        ans[i + j] = c;
                    } else if (ans[i + j] != c) {
                        return "";
                    }
                }
            }
        }

        for (int i = 0; i < L; i++) {
            if (ans[i] == 'a' && required[i] == 0) ans[i] = 'a';
        }

        vector<int> isT(n, 0);
        for (int i = 0; i < n; i++) {
            if (str1[i] == 'T') isT[i] = 1;
        }

        vector<int> lcp(L + 1);
        for (int i = L - 1; i >= 0; i--) {
            lcp[i] = lcp[i + 1];
            if (i < m) {
                int j = 0;
                while (j < m && i + j < L && ans[i + j] == str2[j]) j++;
                if (j == m && i < n) lcp[i] = 1;
            }
        }

        for (int i = 0; i < n; i++) {
            bool equal = true;
            for (int j = 0; j < m; j++) {
                if (ans[i + j] != str2[j]) {
                    equal = false;
                    break;
                }
            }

            if (str1[i] == 'T' && !equal) return "";
            if (str1[i] == 'F' && equal) {
                bool changed = false;

                for (int j = m - 1; j >= 0 && !changed; j--) {
                    int pos = i + j;
                    if (required[pos]) continue;
                    if (ans[pos] < 'z') {
                        ans[pos]++;
                        changed = true;
                    }
                }

                if (!changed) return "";

                for (int k = 0; k <= i; k++) {
                    if (str1[k] == 'T') {
                        for (int j = 0; j < m; j++) {
                            if (ans[k + j] != str2[j]) return "";
                        }
                    }
                }
            }
        }

        return ans;
    }
};