#include <iostream>
#include <bitset>
#include <string>
#include <ctime>
#include <cstdlib>

// subtracts b from a, replacing a with the result
template <typename A, typename B>
void Subtract(A& a, const B& b) 
{
    static const std::size_t minc = a.size() < b.size() ? a.size() : b.size();
    bool borrow = false;
    for (std::size_t i = 0; i < minc; ++i) {
        const bool dif = a[i] ^ b[i] ^ borrow;
        borrow = (a[i] && b[i] && borrow) || (!a[i] && (b[i] || borrow));
        a[i] = dif;
    }
    for (std::size_t i = minc; borrow && i < a.size(); ++i) {
        a[i] = borrow = !a[i];
    }
}

// Returns the index of the highest set bit in b
// Returns unsigned -1 if all bits are 0
template <typename B>
std::size_t HiBit(const B& b) 
{
    for (std::size_t i = b.size() - 1; i + 1; --i) {
        if (b[i]) return i;
    }
    // b is zero
    return ~std::size_t(0);
}

// Compare returns 1 if a>b, 0 if a==b or -1 if a<b
template <typename B>
int Compare(const B& a, const B& b) 
{
    const std::size_t high = a.size() - 1;
    for (std::size_t i = high; i + 1; --i) {
        if (a[i] != b[i]) {
            return int(a[i]) - int(b[i]);
        }
    }
    return 0;
}

// nr is changed from the dividend to the remainder
template <typename B>
void BsMod(B& nr, B d) 
{
    const std::size_t hi_n = HiBit(nr);
    const std::size_t hi_d = HiBit(d);
    if (hi_d > hi_n) return;                            // nr < d, keep n as r
    if (hi_d == hi_n && Compare(nr, d) == -1) return;   // nr < d, keep n as r

    const std::size_t dshift = hi_n - hi_d;
    d <<= dshift;

    for (std::size_t i = 0; i <= dshift; ++i) {
        const int cmp = Compare(nr, d);
        if (cmp == 0) { nr = B(); return; } // d evenly divides nr, so r is 0
        if (cmp > 0) {  // nr > shifted d
            // the quotient would accumulate a 1 bit here, at the d shift position
            Subtract(nr, d);
        }
        d >>= 1;   // divide d by 2, shift back toward original position
    }
}

template <typename B>
unsigned long long bs_to_ull(const B& b) 
{
    unsigned long long result = 0;
    for (std::size_t i = 0; i < sizeof(unsigned long long) * 8; ++i) {
        result |= static_cast<unsigned long long>(b[i]) << i;
    }
    return result;
}

template <typename B>
void ull_to_bs(B& b, unsigned long long n)
{
    b.reset();
    for (std::size_t i = 0; i < sizeof(unsigned long long) * 8; ++i) {
        if (n & ((unsigned long long)1 << i)) b.set(i, true);
    }
}

unsigned long long rand_ull() 
{
    unsigned long long r = 0;
    unsigned long long b = 0;
    for (int i = 0; i < sizeof(unsigned long long); ++i) {
        r = r * 33 + rand();
        b ^= rand();
        b <<= 8;
    }
    return ((r << sizeof(unsigned long long) * 4) | (r >> sizeof(unsigned long long) * 4)) ^ b;
}

void Test(unsigned long long max = 0, int max_iters = 0) 
{
    typedef unsigned long long uit;
    typedef std::bitset<sizeof(unsigned long long) * 8 + 8> bs;
    typedef unsigned long long uit;

    int iter_count = 0;
    for (;;) {
        uit a = rand_ull();
        uit b = rand_ull();
        if (max) {
            a %= max;
            b %= max;
        }
        if (rand() & 255) {
            while (b > a) b >>= rand() & 3;
        }
        if (!b) continue;

        bs bsa;
        ull_to_bs(bsa, a);
        bs bsb;
        ull_to_bs(bsb, b);

        BsMod(bsa, bsb);

        uit ibsm = bs_to_ull(bsa);
        uit m = a % b;

        std::cout << a << " % " << b << " = " << m << "    :    " << ibsm << '\n';

        if (ibsm != m) {
            std::cout << "Error\n";
            return;
        }

        ++iter_count;
        if (max_iters && iter_count > max_iters) break;
    }
}

std::string RandomBinaryString(unsigned bit_count) 
{
    std::string binstr;
    for (unsigned i = 0; i < bit_count; ++i) {
        binstr += ((rand() >> (i % 5)) ^ i) & 1 ? '1' : '0';
    }
    return binstr;
}

void TrimLeadingZeros(std::string& s) 
{
    if (s.length() < 2 || s[0] != '0') return;
    for (std::string::size_type i = 1; i < s.length() - 1; ++i) {
        if (s[i] != '0') {
            s = s.substr(i);
            return;
        }
    }
    s = s.substr(s.length() - 1);
}

int main() {
    srand((unsigned int)time(0));
 
    std::string a;
    std::string b;

    std::cout << "First binary digit:" << std::endl;
    std::cin >> a;
    std::cout << "Second binary digit:" << std::endl;
    std::cin >> b;
    static const int max_bitount = 220;
    typedef std::bitset<max_bitount> bs;

    bs bsa(a);
    bs bsb(b);

    // both arguments must have the same type (number of bits)
    // bsa gets replaced with bsa modulo bsb
    BsMod(bsa, bsb);


    std::string c = bsa.to_string();
    TrimLeadingZeros(c);

    std::cout << a << "\n   mod\n" << b << "\n   ==\n" << c << '\n';
}