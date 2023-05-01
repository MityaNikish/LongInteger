#include "pch.h"
#include "LongInteger.hpp"
#include <string>

LongInteger::LongInteger() : sign_negative(false) {};

LongInteger::LongInteger(int i) {
    const LongInteger number_instance(std::to_string(i).c_str());
    number = number_instance.number;
    sign_negative = number_instance.sign_negative;
}

LongInteger::LongInteger(const char* iStr)
{
    const char set_of_numbers[11] = "0123456789";
    const char plus = '+';
    const char minus = '-';

    std::string str(iStr);
	if (str.length() == 0) {
        sign_negative = false;
        return;
    }

    if (str[0] == minus) {
        str = str.substr(1);
        sign_negative = true;
    }
    else {
        if (str[0] == plus) {
            str = str.substr(1);
        }
        sign_negative = false;
    }

    if (str.find_first_not_of(set_of_numbers) != std::string::npos) {
        sign_negative = false;
        number.clear();
        throw std::invalid_argument("Invalid string in constructor.");
    }

    const int size_exponent = _storage_unit_size();

    for (long long i = static_cast<long long>(str.size()); i >= 0; i -= size_exponent) {
        if (i < size_exponent) {
            number.push_back(atoi(str.substr(0, i).c_str()));
        }
        else {
            number.push_back(atoi(str.substr(i - size_exponent, size_exponent).c_str()));
        }
    }
    _remove_leading_zeros();

}

LongInteger::LongInteger(const LongInteger& val) = default;

LongInteger::~LongInteger() = default;

size_t LongInteger::ToString(char* buff, size_t buff_lenght) const {
    if (number.empty() || (number.size() == 1 && number[0] == 0)) {
        return 0;
    }

    int last_bloc = number[number.size() - 1], count_last_bloc = 0;
    while (last_bloc != 0) {
        last_bloc /= 10;
        count_last_bloc++;
    }
    const size_t max_size_exponent = _storage_unit_size();

    const size_t size = ((number.size() - 1) * max_size_exponent + count_last_bloc + static_cast<int>(sign_negative) + 1);
    if ((buff == nullptr) || (buff_lenght < size)) {
        return size;
    }

    std::string str;
    if (sign_negative) {
        str.push_back('-');
    }

    str += std::to_string(number[number.size() - 1]);
    for (long long i = static_cast<long long>(number.size()) - 2; i >= 0; i--) {
        for (size_t size_exponent = std::to_string(number[i]).size(); size_exponent < max_size_exponent; size_exponent++) {
            str += '0';
        }
        str += std::to_string(number[i]);
    }


    str.push_back('\0');
    strcpy_s(buff, buff_lenght, str.c_str());
    return size;
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

bool LongInteger::is_zero() const
{
    return (number.empty() || (number.size() == 1 && number[0] == 0));
}

bool LongInteger::operator==(const LongInteger& right) const
{
    if (sign_negative != right.sign_negative) {
        return false;
    }

    if (this->is_zero() && right.is_zero()) {
        return true;
    }

    return number == right.number;
}

bool LongInteger::operator<(const LongInteger& right) const {
    if (*this == right) return false;

    if (sign_negative) {
        if (right.sign_negative) {
            return ((-right) < (-*this));
        }
        return true;
    }

    if (right.sign_negative) {
        return false;
    }

    if (number.size() != right.number.size()) {
        return number.size() < right.number.size();
    }

    for (long long i = static_cast<long long>(number.size()) - 1; i >= 0; --i) {
        if (number[i] != right.number[i]) {
            return number[i] < right.number[i];
        }
    }
    return false;
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
        if (right.sign_negative) {
            return -(-left + (-right));
        }
        return right - (-left);
    }
    if (right.sign_negative) {
        return left - (-right);
    }
    if (left.number.size() > right.number.size()) {
        return right + *this;
    }

    return left.adder(right, false);
}

LongInteger LongInteger::operator-(const LongInteger& right) const {
    LongInteger left(*this);

    if (right.sign_negative) {
        return left + (-right);
    }
    if (left.sign_negative) {
        return -(-left + right);
    }
    if (left < right) {
        return -(right - left);
    }

    return left.adder(right, true);
}

LongInteger LongInteger::operator*(const LongInteger& right) const {
    LongInteger result;
    result.number.resize(this->number.size() + right.number.size());
    for (size_t i = 0; i < this->number.size(); ++i) {
        int extra = 0;
        for (size_t j = 0; j < right.number.size() || extra != 0; ++j) {
            const long long cur = result.number[i + j] +
                static_cast<long long>(this->number[i]) * (j < right.number.size() ? right.number[j] : 0) + extra;
            result.number[i + j] = static_cast<int>(cur % LongInteger::BASE);
            extra = static_cast<int>(cur / LongInteger::BASE);
        }
    }

    result.sign_negative = this->sign_negative != right.sign_negative;
    result._remove_leading_zeros();
    return result;
}

LongInteger LongInteger::operator/(const LongInteger& right) const {
    if (right == 0) {
        throw std::invalid_argument("Division by zero");
    }

    LongInteger right_positive = right;
    right_positive.sign_negative = false;

    LongInteger result, current;

    result.number.resize(this->number.size());
    for (long long i = static_cast<long long>(this->number.size()) - 1; i >= 0; --i) {
        current.number.insert(current.number.begin(), 0);
        current.number[0] = this->number[i];
        current._remove_leading_zeros();
        result.number[i] = partial_quotient_calculation(right_positive, current);
 
    }

    result.sign_negative = this->sign_negative != right.sign_negative;
    result._remove_leading_zeros();
    return result;
}

LongInteger LongInteger::operator%(const LongInteger& right) const {
    LongInteger result = *this - (*this / right) * right;
    return result;
}



void LongInteger::_remove_leading_zeros() {
    while (number.size() > 1 && number.back() == 0) {
        number.pop_back();
    }
    if (number.size() == 1 && number[0] == 0) {
        sign_negative = false;
    }
}

int LongInteger::_storage_unit_size(){
    int _long = 0, i = LongInteger::BASE;
    while (i >= 10) {
        _long++;
        i /= 10;
    }
    return _long;
}

const LongInteger LongInteger::operator -() const {
    LongInteger copy(*this);
    copy.sign_negative = !copy.sign_negative;
    return copy;
}

LongInteger& LongInteger::adder(const LongInteger& right, const bool negative)
{
    int extra = 0;

    for (size_t i = 0; i < right.number.size() || extra != 0; ++i) {
        if (i == this->number.size()) {
            this->number.push_back(0);
        }
        this->number[i] += (extra + (i < right.number.size() ? right.number[i] : 0)) * (negative ? -1 : 1);
        extra = negative ? (this->number[i] < 0) : (this->number[i] >= LongInteger::BASE);
        if (extra != 0) {
            this->number[i] += LongInteger::BASE * (negative ? 1 : -1);
        }
    }
    this->_remove_leading_zeros();
    return *this;
}

int LongInteger::partial_quotient_calculation(const LongInteger& right, LongInteger &current)
{
    int incomplete_quotient = 0, left_meaning = 0, right_meaning = LongInteger::BASE;
    while (left_meaning <= right_meaning) {
        const int meaning = (left_meaning + right_meaning) / 2;
        LongInteger t = right * meaning;
        if (t <= current) {
            incomplete_quotient = meaning;
            left_meaning = meaning + 1;
        }
        else right_meaning = meaning - 1;
    }
    current = current - right * incomplete_quotient;
    return incomplete_quotient;
}