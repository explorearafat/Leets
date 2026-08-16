class Solution {
public:
    string smallestPalindrome(string s) {
        int n = s.size();
        vector<int> freq(26, 0);
        for (int i = 0; i < n / 2; i++) {
            freq[s[i] - 'a']++;
        }

        string left = "";
        for (int i = 0; i < 26; i++) {
            left += string(freq[i], 'a' + i);
        }
        string right = left;
        reverse(right.begin(), right.end());
        char mid = (n % 2 == 1) ? s[n / 2] : '\0';

        if (n % 2 == 1) {
            return left + string(1, mid) + right;
        }

        return left + right;
    }
};