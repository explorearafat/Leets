class Solution {
public:
    int divide(int dividend, int divisor) {
        if (dividend == INT_MIN && divisor == -1)
            return INT_MAX;

        long long a = dividend;
        long long b = divisor;

        bool negative = (a < 0) ^ (b < 0);

        a = llabs(a);
        b = llabs(b);

        long long quotient = 0;

        while (a >= b) {
            long long temp = b;
            long long multiple = 1;

            while ((temp << 1) <= a) {
                temp <<= 1;
                multiple <<= 1;
            }

            a -= temp;
            quotient += multiple;
        }

        return negative ? -quotient : quotient;
    }
};