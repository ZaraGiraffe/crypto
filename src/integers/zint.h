#ifndef CRYPTOLABS_ZINT_H
#define CRYPTOLABS_ZINT_H

#include <vector>
#include <string>
#include <climits>
#include <algorithm>
#include <random>

typedef unsigned long long u64;


struct uzint {
    // this struct implements unsinged long arithmetic
    // the fou64owing basic operations is implemented
    // a + b
    // a - b only if a >= b else undefined behaviour
    // a * b
    // a / b division by zero is undefined behaviour
    // a % b mod zero is undefined behaviour
    // a < b
    // a == b
    // a >> n delets starting n 64 bit numbers
    // a << n multiplies by 2**(64*n)

    std::vector<u64> mas;

    void norm() {
        while (!mas.empty() && !mas.back()) {
            mas.pop_back();
        }
    }

    u64 to_u64() const {
        if (this->is_zero())
            return (u64)0;
        else
            return mas[0];
    }

    static u64 add_overflow(u64 a, u64 b, u64 carry) {
        // checks whether a + b + carry > Uu64ONG_MAX (returns 1)
        // we should be carefuu64 with overflow
        // if a + b + carry > (Uu64ONG_MAX + 1) + Uu64ONG_MAX returns 2
        u64 res = 0;
        if (b > ULLONG_MAX - carry) {
            res++;
            u64 d = b + carry;
            if (a > ULLONG_MAX - d)
                res++;
        }
        else {
            if (a > ULLONG_MAX - (b + carry))
                res++;
        }
        return res;
    }

    static u64 sub_overflow(u64 a, u64 b, u64 carry) {
        // returns whether a < b + carry
        // we should be carefuu64 with overflow
        if (a > b)
            return (u64)0;
        else if (a < b)
            return (u64)1;
        else
            return (u64)(carry == (u64)1);
    }

    static std::pair<u64, u64> umul(u64 a, u64 b) {
        // multiplies two 64 bit unsigned integers and 
        // stores 128 bit result as a pair
        u64 a_upper = a >> 32;
        u64 b_upper = b >> 32;
        u64 a_lower = a & 0xFFFFFFFF;
        u64 b_lower = b & 0xFFFFFFFF;

        u64 p1 = a_lower * b_lower;
        u64 p2 = a_lower * b_upper;
        u64 p3 = a_upper * b_lower;
        u64 p4 = a_upper * b_upper;

        u64 r_lower = p1 + (p2 << 32) + (p3 << 32);
        u64 carry = add_overflow(p1, p2 << 32, p3 << 32);
        u64 r_upper = (p2 >> 32) + (p3 >> 32) + p4 + carry;

        return {r_lower, r_upper};
    }

    uzint(u64 num) {
        mas.push_back(num);
    }

    uzint(std::vector<u64> nums) {
        mas = nums;
    }

    uzint() {
        mas = std::vector<u64>();
    }

    uzint copy() const {
        return uzint(mas);
    }

    u64 get(int ord) const {
        if (ord >= mas.size()) {
            return 0;
        } else {
            return mas[ord];
        }
    }

    int get_length() const {
        return (int)mas.size();
    }

    void set(int ord, u64 num) {
        while (ord >= mas.size())
            mas.push_back(0);
        mas[ord] = num;
    }

    bool is_zero() const {
        return mas.empty();
    }

    void operator=(const uzint& other) {
        this->mas = other.mas;
    }

    uzint operator<<(int num) const {
        std::vector<u64> new_nums = mas;
        new_nums.insert(new_nums.begin(), num, (u64)0);
        return uzint(new_nums);
    }

    uzint operator>>(int num) const {
        std::vector<u64> new_nums(mas.begin() + num, mas.end());
        return uzint(new_nums);
    }

    bool operator==(const uzint& other) const {
        if (this->get_length() == other.get_length()) {
            for (int i = 0; i < other.get_length(); i++) {
                if (this->get(i) != other.get(i))
                    return false;
            }
            return true;
        }
        return false;
    }

    bool operator!=(const uzint& other) const {
        return !(*this == other);
    }

    bool operator<(const uzint& other) const {
        if (this->get_length() < other.get_length())
            return true;
        else if (this->get_length() > other.get_length())
            return false;
        else {
            for (int i = this->get_length(); i >= 0; i--) {
                if (this->get(i) < other.get(i))
                    return true;
                else if (this->get(i) > other.get(i))
                    return false;
            }
            return false;
        }
    }

    bool operator>(const uzint& other) const {
        return other < *this;
    }

    bool operator<=(const uzint& other) const {
        return *this < other || *this == other;
    }

    bool operator>=(const uzint& other) const {
        return *this > other || *this == other;
    }

    uzint operator+(const uzint& other) const {
        uzint new_int = uzint();
        u64 carry = 0;
        for (int i = 0; carry || i < this->get_length() || i < other.get_length(); i++) {
            u64 a = this->get(i);
            u64 b = other.get(i);
            new_int.set(i, a + b + carry);
            carry = add_overflow(a, b, carry);
        }
        new_int.norm();
        return new_int;
    }

    uzint operator-(const uzint& other) const {
        // you should have this >= other, otherwise there wiu64 be undefined behaviour
        uzint new_int = uzint();
        u64 carry = 0;
        for (int i = 0; i < this->get_length(); i++) {
            u64 carry_dop = sub_overflow(this->get(i), other.get(i), carry);
            new_int.set(i, this->get(i) - other.get(i) - carry);
            carry = carry_dop;
        }
        new_int.norm();
        return new_int;
    }

    uzint operator*(const uzint& other) const {
        uzint new_int = uzint();
        for (int i = 0; i < this->get_length(); i++) {
            u64 carry = 0;
            for (int j = 0; j < other.get_length(); j++) {
                std::pair<u64, u64> a = umul(this->get(i), other.get(j));
                carry += add_overflow(new_int.get(i + j), a.first, 0);
                new_int.set(i + j, new_int.get(i + j) + a.first);
                u64 carry_dop = add_overflow(new_int.get(i + j + 1), a.second, carry);
                new_int.set(i + j + 1, new_int.get(i + j + 1) + a.second + carry);
                carry = carry_dop;
            }
            new_int.set(i + other.get_length(), carry + new_int.get(i + other.get_length()));
        }
        new_int.norm();
        return new_int;
    }

    uzint operator/(const uzint& other) const {
        if (*this < other)
            return uzint();
        int ans_length = this->get_length() - other.get_length();
        if ((other << ans_length) <= *this)
            ans_length++;
        uzint ans;
        for (int i = ans_length - 1; i >= 0; i--) {
            u64 l = (u64)0;
            u64 r = ULLONG_MAX;
            while (l < r) {
                u64 m = (l >> (u64)1) + (r >> (u64)1);
                if (l & (u64)1 || r & (u64)1) m++;
                ans.set(i, m);
                if (ans * other > *this)
                    r = m - (u64)1;
                else
                    l = m;
            }
            ans.set(i, l);
        }
        ans.norm();
        return ans;
    }

    uzint operator%(const uzint& other) const {
        return *this - (*this / other) * other;
    }

    uzint pow(const uzint& other, const uzint& p) const {
        // this is a function that calculates power modulo number p
        // p is not nessesarily prime
        if (this->is_zero())
            return uzint();
        uzint b = other.copy();
        uzint a = this->copy();
        uzint res = uzint((u64)1);
        while (!b.is_zero()) {
            if (b.to_u64() & (u64)1)
                res = (res * a) % p;
            a = (a * a) % p;
            b = b / uzint((u64)2);
        }
        return res;
    }

};


std::string get_bits(const uzint& a) {
    std::string res;
    for (int i = 0; i < a.get_length(); i++) {
        u64 cur = a.get(i);
        for (int j = 0; j < 64; j++) {
            u64 now = cur & 1;
            res += std::to_string(now);
            cur >>= 1;
        }
    }
    std::reverse(res.begin(), res.end());
    return res;
}


std::string get_base10(const uzint& a) {
    uzint b = a.copy();
    uzint ten = uzint(10);
    std::string res;
    while (!b.is_zero()) {
        u64 ost = (b % ten).to_u64();
        res += std::to_string(ost);
        b = b / ten;
    }
    std::reverse(res.begin(), res.end());
    return res;
}


std::string BASE64ENCODE = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghigklmnopqrstuvwxyz0123456789+/";

std::string get_base64(const uzint& a) {
    uzint b = a.copy();
    uzint sf = uzint(64);
    std::string res;
    while (!b.is_zero()) {
        u64 ost = (b % sf).to_u64();
        res += BASE64ENCODE[(int)ost];
        b = b / sf;
    }
    return res;
}


uzint get_from_base10(std::string num) {
    uzint ten = uzint((u64)10);
    uzint step = uzint((u64)1);
    uzint res = uzint();
    for (int i = num.size() - 1; i > -1; i--) {
        u64 cur = (u64)(num[i] - '0');
        res = res + step * uzint(cur);
        step = step * ten;
    }
    return res;
}


struct RandomUzintGenerator {
    std::mt19937_64 gen;
    std::uniform_int_distribution<u64> dist_u64;
    std::uniform_int_distribution<u64> dist_main;
    uzint max_gen_num;
    uzint offset;

    RandomUzintGenerator(const uzint& mini, const uzint& maxi) {
        max_gen_num = maxi - mini;
        offset = mini.copy();
        dist_u64 = std::uniform_int_distribution<u64>(0, ULLONG_MAX);
        u64 maxi_main = max_gen_num.get(max_gen_num.get_length() - 1);
        dist_main = std::uniform_int_distribution<u64>(0, maxi_main);
    }

    uzint generate() {
        while (true) {
            uzint res;
            for (int i = 0; i < max_gen_num.get_length(); i++) {
                if (i != max_gen_num.get_length() - 1)
                    res.set(i, dist_u64(gen));
                else
                    res.set(i, dist_main(gen));
            }
            if (res <= max_gen_num)
                return offset + res;
        }
    }
};


#endif //CRYPTOLABS_ZINT_H
