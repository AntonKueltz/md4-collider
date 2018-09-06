#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define F(x, y ,z) ((x & y) | (~x & z))
#define G(x, y, z) ((x & y) | (x & z) | (y & z))

#define LROT(x, n) ((x << n) | (x >> (32 - n)))
#define RROT(x, n) ((x >> n) | (x << (32 - n)))

#define PHI0(a, b, c, d, m, s) (LROT(((a + F(b, c, d) + m) & 0xffffffff), s))
#define INV0(x, a, b, c, d, s) ((RROT(x, s) - a - F(b, c, d)) & 0xffffffff)
#define PHI1(a, b, c, d, m, s) (LROT(((a + G(b, c, d) + mk + 0x5a827999) & 0xffffffff), s))
#define INV1(x, a, b, c, d, s) ((RROT(x, s) - a - G(b, c, d) - 0x5a827999) & 0xffffffff)

#define SET(x, i) (x | (1u << (i - 1)))
#define CLR(x, i) (x & ~((1u << (i - 1))))
#define EQ(x, y, i) (((y >> (i - 1)) & 1) ? SET(x, i) : CLR(x, i))

#define MD4_WORDS 16

const uint32_t IV[4] = {0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476};


void setConstraints(uint32_t * m) {
    uint32_t a = IV[0];
    uint32_t b = IV[1];
    uint32_t c = IV[2];
    uint32_t d = IV[3];
    uint32_t x;

    // ROUND 1 STEP 1
    x = a;
    a = PHI0(a, b, c, d, m[0], 3);
    a = EQ(a, b, 7);
    m[0] = INV0(a, x, b, c, d, 3);

    // ROUND 1 STEP 2
    x = d;
    d = PHI0(d, a, b, c, m[1], 7);
    d = CLR(d, 7);
    d = EQ(d, a, 8);
    d = EQ(d, a, 11);
    m[1] = INV0(d, x, a, b, c, 7);

    // ROUND 1 STEP 3
    x = c;
    c = PHI0(c, d, a, b, m[2], 11);
    c = SET(c, 7);
    c = SET(c, 8);
    c = CLR(c, 11);
    c = EQ(c, d, 26);
    m[2] = INV0(c, x, d, a, b, 11);

    // ROUND 1 STEP 4
    x = b;
    b = PHI0(b, c, d, a, m[3], 19);
    b = SET(b, 7);
    b = CLR(b, 8);
    b = CLR(b, 11);
    b = CLR(b, 26);
    m[3] = INV0(b, x, c, d, a, 19);

    // ROUND 1 STEP 5
    x = a;
    a = PHI0(a, b, c, d, m[4], 3);
    a = SET(a, 8);
    a = SET(a, 11);
    a = CLR(a, 26);
    a = EQ(a, b, 14);
    m[4] = INV0(a, x, b, c, d, 3);

    // ROUND 1 STEP 6
    x = d;
    d = PHI0(d, a, b, c, m[5], 7);
    d = CLR(d, 14);
    d = EQ(d, a, 19);
    d = EQ(d, a, 20);
    d = EQ(d, a, 21);
    d = EQ(d, a, 22);
    d = SET(d, 26);
    m[5] = INV0(d, x, a, b, c, 7);

    // ROUND 1 STEP 7
    x = c;
    c = PHI0(c, d, a, b, m[6], 11);
    c = EQ(c, d, 13);
    c = CLR(c, 14);
    c = EQ(c, d, 15);
    c = CLR(c, 19);
    c = CLR(c, 20);
    c = SET(c, 21);
    c = CLR(c, 22);
    m[6] = INV0(c, x, d, a, b, 11);

    // ROUND 1 STEP 8
    x = b;
    b = PHI0(b, c, d, a, m[7], 19);
    b = SET(b, 13);
    b = SET(b, 14);
    b = CLR(b, 15);
    b = EQ(b, c, 17);
    b = CLR(b, 19);
    b = CLR(b, 20);
    b = CLR(b, 21);
    b = CLR(b, 22);
    m[7] = INV0(b, x, c, d, a, 19);

    // ROUND 1 STEP 9
    x = a;
    a = PHI0(a, b, c, d, m[8], 3);
    a = SET(a, 13);
    a = SET(a, 14);
    a = SET(a, 15);
    a = CLR(a, 17);
    a = CLR(a, 19);
    a = CLR(a, 20);
    a = CLR(a, 21);
    a = EQ(a, b, 23);
    a = SET(a, 22);
    a = EQ(a, b, 26);
    m[8] = INV0(a, x, b, c, d, 3);

    // ROUND 1 STEP 10
    x = d;
    d = PHI0(d, a, b, c, m[9], 7);
    d = SET(d, 13);
    d = SET(d, 14);
    d = SET(d, 15);
    d = CLR(d, 17);
    d = CLR(d, 20);
    d = SET(d, 21);
    d = SET(d, 22);
    d = CLR(d, 23);
    d = SET(d, 26);
    d = EQ(d, a, 30);
    m[9] = INV0(d, x, a, b, c, 7);

    // ROUND 1 STEP 11
    x = c;
    c = PHI0(c, d, a, b, m[10], 11);
    c = SET(c, 17);
    c = CLR(c, 20);
    c = CLR(c, 21);
    c = CLR(c, 22);
    c = CLR(c, 23);
    c = CLR(c, 26);
    c = SET(c, 30);
    c = EQ(c, d, 32);
    m[10] = INV0(c, x, d, a, b, 11);

    // ROUND 1 STEP 12
    x = b;
    b = PHI0(b, c, d, a, m[11], 19);
    b = CLR(b, 20);
    b = SET(b, 21);
    b = SET(b, 22);
    b = EQ(b, c, 23);
    b = SET(b, 26);
    b = CLR(b, 30);
    b = CLR(b, 32);
    m[11] = INV0(b, x, c, d, a, 19);

    // ROUND 1 STEP 13
    x = a;
    a = PHI0(a, b, c, d, m[12], 3);
    a = CLR(a, 23);
    a = CLR(a, 26);
    a = EQ(a, b, 27);
    a = EQ(a, b, 29);
    a = SET(a, 30);
    a = CLR(a, 32);
    m[12] = INV0(a, x, b, c, d, 3);

    // ROUND 1 STEP 14
    x = d;
    d = PHI0(d, a, b, c, m[13], 7);
    d = CLR(d, 23);
    d = CLR(d, 26);
    d = SET(d, 27);
    d = SET(d, 29);
    d = CLR(d, 30);
    d = SET(d, 32);
    m[13] = INV0(d, x, a, b, c, 7);

    // ROUND 1 STEP 15
    x = c;
    c = PHI0(c, d, a, b, m[14], 11);
    c = EQ(c, d, 19);
    c = SET(c, 23);
    c = SET(c, 26);
    c = CLR(c, 27);
    c = CLR(c, 29);
    c = CLR(c, 30);
    m[14] = INV0(c, x, d, a, b, 11);

    // ROUND 1 STEP 16
    x = b;
    b = PHI0(b, c, d, a, m[15], 19);
    b = CLR(b, 19);
    b = SET(b, 26);
    b = SET(b, 27);
    b = SET(b, 29);
    b = CLR(b, 30);
    m[15] = INV0(b, x, c, d, a, 19);
}

void randomBlocks(uint32_t * m) {
    for(unsigned i = 0; i < MD4_WORDS; i++) {
        m[i] |= (rand() & 0xff);
        m[i] |= (rand() & 0xff) << 8;
        m[i] |= (rand() & 0xff) << 16;
        m[i] |= (rand() & 0xff) << 24;
    }
}

void printBlocks(uint32_t * m) {
    for(unsigned i = 0; i < MD4_WORDS; i++) {
        printf("%08x ", m[i]);
    }
    printf("\n");
}

int main(int argc, char * argv[]) {
    uint32_t m[MD4_WORDS] = {0};

    randomBlocks(m);
    printBlocks(m);
    setConstraints(m);

    uint32_t m_[MD4_WORDS];
    memcpy(m_, m, MD4_WORDS * sizeof(uint32_t));
    m_[1] = (m_[1] + (1u << 31)) & 0xffffffff;
    m_[2] = (m_[2] + ((1u << 31) - (1u << 28))) & 0xffffffff;
    m_[12] = (m_[12] - (1u << 16)) & 0xffffffff;

    printf("M = ");
    printBlocks(m);

    printf("M' = ");
    printBlocks(m_);

    return 0;
}
