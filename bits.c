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
    if (!x && !y) {
        return 1;
    }
    if (!x) {
        return 0;
    }
    if (!y) {
        return 0;
    }
    return !(((x ^ y) >> 31) & 1);
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
    int f16 = (v >> 16) > 0;
    int s4 = f16 << 4;
    v = v >> s4;
    int f8 = (v >> 8) > 0;
    int s3 = f8 << 3;
    v = v >> s3;
    int f4 = (v >> 4) > 0;
    int s2 = f4 << 2;
    v = v >> s2;
    int f2 = (v >> 2) > 0;
    int s1 = f2 << 1;
    v = v >> s1;
    int f1 = v >> 1;
    return s4 | s3 | s2 | s1 | f1;
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
    int n2 = n << 3;
    int m2 = m << 3;
    int mask1 = 0xFF << n2;
    int mask2 = 0xFF << m2;
    int cbyte1 = x & mask1;
    int cbyte2 = x & mask2;
    int rbyte1 = ((cbyte1 >> n2) & 0xFF) << m2;
    int rbyte2 = ((cbyte2 >> m2) & 0xFF) << n2;
    return x ^ cbyte1 ^ cbyte2 ^ rbyte1 ^ rbyte2;
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
    unsigned l;
    unsigned r;

    l = 0xAAAAAAAA;
    r = 0x55555555;
    v = ((v & l) >> 1) | ((v & r) << 1);

    l = 0xCCCCCCCC;
    r = 0x33333333;
    v = ((v & l) >> 2) | ((v & r) << 2);

    l = 0xF0F0F0F0;
    r = 0x0F0F0F0F;
    v = ((v & l) >> 4) | ((v & r) << 4);

    l = 0xFF00FF00;
    r = 0x00FF00FF;
    v = ((v & l) >> 8) | ((v & r) << 8);

    l = 0xFFFF0000;
    r = 0x0000FFFF;
    v = ((v & l) >> 16) | ((v & r) << 16);

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

    int t = !!v;

    int f16 = !!(v << 16);
    int s4 = f16 << 4;
    v = v << s4;

    int f8 = !!(v << 8);
    int s3 = f8 << 3;
    v = v << s3;

    int f4 = !!(v << 4);
    int s2 = f4 << 2;
    v = v << s2;

    int f2 = !!(v << 2);
    int s1 = f2 << 1;
    v = v << s1;

    int f1 = !!(v << 1);

    return (s4 | s3 | s2 | s1 | f1) + t;
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

    unsigned intv = 0x80000000 | ((uf2 & 0xFFFFF) << 11) | (uf1 >> 12);
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
