class Solution:
    def smallestPalindrome(self, s: str, k: int) -> str:
        cnt = [0] * 26

        for ch in s:
            cnt[ord(ch) - 97] += 1

        half = [0] * 26
        middle = ""

        for i in range(26):
            if cnt[i] % 2:
                middle = chr(i + 97)
            half[i] = cnt[i] // 2

        def combination(n, r):
            r = min(r, n - r)
            res = 1

            for i in range(1, r + 1):
                res = res * (n - r + i) // i
                if res >= k:
                    return k

            return res

        def count_permutations():
            total = sum(half)
            res = 1

            for c in half:
                if c == 0:
                    continue

                ways = combination(total, c)
                res *= ways

                if res >= k:
                    return k

                total -= c

            return res

        left = []

        for _ in range(len(s) // 2):
            for i in range(26):
                if half[i] == 0:
                    continue

                half[i] -= 1
                ways = count_permutations()

                if ways >= k:
                    left.append(chr(i + 97))
                    break

                k -= ways
                half[i] += 1
            else:
                return ""

        left = "".join(left)
        return left + middle + left[::-1]