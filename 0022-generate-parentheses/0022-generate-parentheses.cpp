class Solution {
public:
    void generate(string curr, int open, int close, int n, vector<string>& ans) {
        if (curr.size() == 2 * n) {
            ans.push_back(curr);
            return;
        }

        if (open < n) {
            generate(curr + "(", open + 1, close, n, ans);
        }

        if (close < open) {
            generate(curr + ")", open, close + 1, n, ans);
        }
    }

    vector<string> generateParenthesis(int n) {
        vector<string> ans;
        generate("", 0, 0, n, ans);
        return ans;
    }
};