/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    return ~(~x | ~y);
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return ~(x & y) & ~(~x & ~y);
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    return !((x ^ y) >> 31) && !(!x ^ !y);
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    int has16 = (v >> 16) > 0;
    int shift16 = has16 << 4;
    v = v >> shift16;

    int has8 = (v >> 8) > 0;
    int shift8 = has8 << 3;
    v = v >> shift8;

    int has4 = (v >> 4) > 0;
    int shift4 = has4 << 2;
    v = v >> shift4;

    int has2 = (v >> 2) > 0;
    int shift2 = has2 << 1;
    v = v >> shift2;

    int shift1 = v >> 1;
    return shift16 | shift8 | shift4 | shift2 | shift1;
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    int ns = n << 3;
    int ms = m << 3;
    int a = (x >> ns) & 0xFF;
    int b = (x >> ms) & 0xFF;
    int d = a ^ b;
    return x ^ (d << ns) ^ (d << ms);
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    v = ((v & 0xAAAAAAAAU) >> 1) | ((v & 0x55555555U) << 1);
    v = ((v & 0xCCCCCCCCU) >> 2) | ((v & 0x33333333U) << 2);
    v = ((v & 0xF0F0F0F0U) >> 4) | ((v & 0x0F0F0F0FU) << 4);
    v = ((v & 0xFF00FF00U) >> 8) | ((v & 0x00FF00FFU) << 8);
    v = ((v & 0xFFFF0000U) >> 16) | ((v & 0x0000FFFFU) << 16);
    return v;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    return (x >> n) & ~((~0) << (32 + ~n) << 1);
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    int v = x;
    v = v & (v >> 1);
    v = v & (v >> 2);
    v = v & (v >> 4);
    v = v & (v >> 8);
    v = v & (v >> 16);

    int count_all = !!v;

    int has16 = !!(v << 16);
    int add16 = has16 << 4;
    v = v << add16;

    int has8 = !!(v << 8);
    int add8 = has8 << 3;
    v = v << add8;

    int has4 = !!(v << 4);
    int add4 = has4 << 2;
    v = v << add4;

    int has2 = !!(v << 2);
    int add2 = has2 << 1;
    v = v << add2;

    int add1 = !!(v << 1);

    return count_all + add1 + add2 + add4 + add8 + add16;
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
 unsigned float_i2f(int x) {
    if (x == 0) {
        return 0;
    }

    unsigned s = x & 0x80000000;
    unsigned m = x, e = 158;

    if (x < 0) {
        m = ~x + 1;
    }

    while ((m & 0x80000000) == 0) {
        m = m << 1;
        e = e - 1;
    }

    int r = 0;
    if ((m & 0xFF) > 0x80) {
        r = 1;
    } else if ((m & 0xFF) == 0x80) {
        if (m & 0x100) {
            r = 1;
        }
    }

    if (r) {
        unsigned o = m;
        m = m + 0x100;
        if (m < o) {
            e = e + 1;
        }
    }

    return s | (e << 23) | ((m >> 8) & 0x7FFFFF);
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    if ((uf & 0x7FFFFFFF) >= 0x7F800000) {
        return uf;
    }
    
    unsigned s = uf & 0x80000000;
    unsigned e = uf & 0x7F800000;
    unsigned m = uf & 0x7FFFFF;

    if (e == 0) {
        return s | (m << 1);
    } else {
        return s | (e + 0x800000) | m;
    }
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    unsigned s = uf2 >> 31;
    unsigned e = (uf2 & 0x7FF00000) >> 20;

    if (e < 1023) {
        return 0;
    }

    if (e >= 1054) {
        return 0x80000000;
    }

    unsigned intv = 0x80000000 | ((uf2 & 0xFFFFF) << 11) | (uf1 >> 21);
    intv = intv >> (1054 - e);

    int ret = intv;
    if (s) {
        ret = -ret;
    }

    return ret;
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    if (x < -149) {
        return 0;
    }

    if (x < -126) {
        return 1 << (x + 149);
    }

    if (x < 128) {
        return (x + 127) << 23;
    }

    return 0x7F800000;
}
