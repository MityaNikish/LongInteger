#include "pch.h"
#include "LongInteger.hpp"
#include <string>

LongInteger::LongInteger() : number({}), sign_negative(false) {};

LongInteger::LongInteger(int i) {
    if (i < 0) {
        sign_negative = true; i = -i;
    }
    else sign_negative = false;
    do {
        number.push_back(i % LongInteger::BASE);
        i /= LongInteger::BASE;
    } while (i != 0);
}

LongInteger::LongInteger(const char* iStr)
{
    std::string str(iStr);
	if (str.length() == 0) {
        sign_negative = false;
    }
    else {
        if (str[0] == '-') {
            str = str.substr(1);
            sign_negative = true;
        }
        else {
            sign_negative = false;
        }

        int _long = _storage_unit_size();

        for (int i = str.length(); i >= 0; i -= _long) {
            if (i < _long)
                    number.push_back(atoi(str.substr(0, i).c_str()));
            else
                    number.push_back(atoi(str.substr(i - _long, _long).c_str()));
        }
        _remove_leading_zeros();
    }
}

LongInteger::LongInteger(const LongInteger& val) : number(val.number), sign_negative(val.sign_negative) {}

LongInteger::~LongInteger() = default;

size_t LongInteger::ToString(char* buff, size_t buff_lenght) const {
    if ((number.size() == 0) || (number.size() == 1 && number[0] == 0)) {
        return 0;
    }

    int last_bloc = number[number.size() - 1], count_last_bloc = 0;
    while (last_bloc != 0) {
        last_bloc /= 10;
        count_last_bloc++;
    }
    int _long = _storage_unit_size();

    size_t size = (size_t)((number.size() - 1) * _long + count_last_bloc + sign_negative + 1);
    if (buff_lenght < size) {
        return size;
    }

    std::string str;
    if (sign_negative) {
        str.push_back('-');
    }
    int arg;
    for (int i = number.size() - 1; i > 0; i--) {
        str += std::to_string(number[i]);
    }

    str.push_back('\0');
    return size;

    std::string str_buff = buff;
    std::swap(str_buff, str);
}



LongInteger& LongInteger::operator= (int val) {
    return *this = LongInteger(val);
}

LongInteger& LongInteger::operator+=(int val) {
    return *this += LongInteger(val);
}

LongInteger& LongInteger::operator-=(int val) {
    return *this -= LongInteger(val);
}

LongInteger& LongInteger::operator*=(int val) {
    return *this *= LongInteger(val);
}

LongInteger& LongInteger::operator/=(int val) {
    return *this /= LongInteger(val);
}



LongInteger& LongInteger::operator= (const LongInteger& val) = default;

LongInteger& LongInteger::operator+=(const LongInteger& val) {
    return *this = *this + val;
}

LongInteger& LongInteger::operator-=(const LongInteger& val) {
    return *this = *this - val;
}

LongInteger& LongInteger::operator*=(const LongInteger& val) {
    return *this = *this * val;
}

LongInteger& LongInteger::operator/=(const LongInteger& val) {
    return *this = *this / val;
}



bool LongInteger::operator==(const LongInteger& right) const
{
    if (sign_negative != right.sign_negative) return false;

    if (number.empty()) {
        if (right.number.empty() || (right.number.size() == 1 && right.number[0] == 0)) return true;
        else return false;
    }

    if (right.number.empty()) {
        if ((number.size() == 1) && (number[0] == 0)) return true;
        else return false;
    }

    if (number.size() != right.number.size()) return false;

    for (size_t i = 0; i < number.size(); ++i) if (number[i] != right.number[i]) return false;

    return true;
}

bool LongInteger::operator<(const LongInteger& right) const {
    if (*this == right) return false;

    if (sign_negative) {
        if (right.sign_negative) return ((-right) < (-*this));
        else return true;
    }

    else if (right.sign_negative) return false;

    else {
        if (number.size() != right.number.size()) {
            return number.size() < right.number.size();
        }
        else {
            for (int i = number.size() - 1; i >= 0; --i) {
                if (number[i] != right.number[i]) return number[i] < right.number[i];
            }
            return false;
        }
    }
}

bool LongInteger::operator!=(const LongInteger& right) const {
    return !(*this == right);
}

bool LongInteger::operator>=(const LongInteger& right) const {
    return !(*this < right);
}

bool LongInteger::operator<=(const LongInteger& right) const {
    return (*this < right || *this == right);
}

bool LongInteger::operator>(const LongInteger& right) const {
    return !(*this <= right);
}



LongInteger LongInteger::operator+(const LongInteger& right) const {
    LongInteger left(*this);

    if (left.sign_negative) {
        if (right.sign_negative) return -(-left + (-right));
        else return right - (-left);
    }
    else if (right.sign_negative) return left - (-right);

    int extra = 0;
    for (size_t i = 0; i < std::max(left.number.size(), right.number.size()) || extra != 0; ++i) {
        if (i == left.number.size()) left.number.push_back(0);
        left.number[i] += extra + (i < right.number.size() ? right.number[i] : 0);
        extra = left.number[i] >= LongInteger::BASE;
        if (extra != 0) left.number[i] -= LongInteger::BASE;
    }
    return left;
}

LongInteger LongInteger::operator-(const LongInteger& right) const {
    LongInteger left(*this);

    if (right.sign_negative) return left + (-right);
    else if (left.sign_negative) return -(-left + right);
    else if (left < right) return -(right - left);

    int extra = 0;
    for (size_t i = 0; i < right.number.size() || extra != 0; ++i) {
        left.number[i] -= extra + (i < right.number.size() ? right.number[i] : 0);
        extra = left.number[i] < 0;
        if (extra != 0) left.number[i] += LongInteger::BASE;
    }

    left._remove_leading_zeros();
    return left;
}

LongInteger LongInteger::operator*(const LongInteger& right) const {
    LongInteger left(*this);
    LongInteger result;
    result.number.resize(left.number.size() + right.number.size());
    for (size_t i = 0; i < left.number.size(); ++i) {
        int extra = 0;
        for (size_t j = 0; j < right.number.size() || extra != 0; ++j) {
            long long cur = result.number[i + j] +
                left.number[i] * (j < right.number.size() ? right.number[j] : 0) + extra;
            result.number[i + j] = cur % LongInteger::BASE;
            extra = cur / LongInteger::BASE;
        }
    }

    result.sign_negative = left.sign_negative != right.sign_negative;
    result._remove_leading_zeros();
    return result;
}

LongInteger LongInteger::operator/(const LongInteger& right) const {
    LongInteger left(*this);
    if (right == 0) throw std::exception("Division by zero");
    LongInteger temp = right;
    temp.sign_negative = false;
    LongInteger result, current;

    result.number.resize(left.number.size());
    for (int i = left.number.size() - 1; i >= 0; --i) {
        current._shift_right();
        current.number[0] = left.number[i];
        current._remove_leading_zeros();

        int x = 0, left_meaning = 0, right_meaning = LongInteger::BASE;

        while (left_meaning <= right_meaning) {
            int m = (left_meaning + right_meaning) / 2;
            LongInteger t = temp * m;
            if (t <= current) {
                x = m;
                left_meaning = m + 1;
            }
            else right_meaning = m - 1;
        }

        result.number[i] = x;
        current = current - temp * x;
    }

    result.sign_negative = left.sign_negative != right.sign_negative;
    result._remove_leading_zeros();
    return result;
}

LongInteger LongInteger::operator%(const LongInteger& right) const {
    LongInteger left(*this);
    LongInteger result = left - (left / right) * right;
    return result;
}



void LongInteger::_remove_leading_zeros() {
    while (number.size() > 1 && number.back() == 0) {
        number.pop_back();
    }
    if (number.size() == 1 && number[0] == 0) sign_negative = false;
}

int LongInteger::_storage_unit_size(){
    int _long = 0, i = LongInteger::BASE;
    while (i >= 10) {
        _long++;
        i /= 10;
    };
    return _long;
}

const LongInteger LongInteger::operator -() const {
    LongInteger copy(*this);
    copy.sign_negative = !copy.sign_negative;
    return copy;
}

void LongInteger::_shift_right() {
    if (number.size() == 0) {
        number.push_back(0);
        return;
    }
    number.push_back(number[number.size() - 1]);
    
    for (size_t i = number.size() - 2; i > 0; --i) number[i] = number[i - 1];
    number[0] = 0;
}