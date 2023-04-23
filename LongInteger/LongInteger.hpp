#pragma once
#include <vector>

class LongInteger final{
public:
	LongInteger();
	LongInteger(int i);
	LongInteger(const char* iStr);
	LongInteger(const LongInteger& val);
	~LongInteger();
	size_t ToString(char* buff, size_t buff_lenght) const;

	LongInteger& operator= (int val);
	LongInteger& operator+=(int val);
	LongInteger& operator-=(int val);
	LongInteger& operator*=(int val);
	LongInteger& operator/=(int val);

	LongInteger& operator= (const LongInteger& val);
	LongInteger& operator+=(const LongInteger& val);
	LongInteger& operator-=(const LongInteger& val);
	LongInteger& operator*=(const LongInteger& val);
	LongInteger& operator/=(const LongInteger& val);

	bool operator==(const LongInteger& right) const;
	bool operator!=(const LongInteger& right) const;
	bool operator>=(const LongInteger& right) const;
	bool operator<=(const LongInteger& right) const;
	bool operator>(const LongInteger& right) const;
	bool operator<(const LongInteger& right) const;

	LongInteger operator+(const LongInteger& right) const;
	LongInteger operator-(const LongInteger& right) const;
	LongInteger operator*(const LongInteger& right) const;
	LongInteger operator/(const LongInteger& right) const;
	LongInteger operator%(const LongInteger& right) const;

private:
	void _remove_leading_zeros();
	static int _storage_unit_size();
	const LongInteger operator -() const;
	void _shift_right();
	LongInteger& adder(const LongInteger& _right, const bool negative);

private:
	static const int BASE = 1000000000;
	std::vector<int> number;
	bool sign_negative;
};