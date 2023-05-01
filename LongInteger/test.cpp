#include "pch.h"

#include "LongInteger.hpp"
#include <random>

#include <time.h>
#include  <fstream>

//-----------------------------------------------------------------------------//

TEST(TestCase_Ctor, Test_nathing) {
	LongInteger number_1("123456");
	EXPECT_EQ(6 + 1, number_1.ToString(nullptr, 0));
}

TEST(TestCase_Ctor, Test_str) {
	LongInteger number_1("1251654654621");
	char* str = new char[14];
	EXPECT_EQ(14, number_1.ToString(str, 14));
	//EXPECT_TRUE(true);
	delete[](str);
}

TEST(TestCase_Ctor, Test_uncorestly_str) {
	EXPECT_THROW({ LongInteger("++1251654"); }, std::invalid_argument);
	EXPECT_THROW({ LongInteger("1.251654"); }, std::invalid_argument);
	EXPECT_THROW({ LongInteger("125sfd4"); }, std::invalid_argument);
}

TEST(TestCase_Ctor, Test_Int) {
	LongInteger number_1(12506151);
	EXPECT_EQ(8 + 1, number_1.ToString(nullptr, 0));
}

//-----------------------------------------------------------------------------//

TEST(TestCase_CtorCopy, Test) {
	LongInteger number_1(12506151);
	LongInteger number_2(number_1);
	EXPECT_TRUE(true);
}

//-----------------------------------------------------------------------------//

TEST(TestCase_ToString, Test1) {
	LongInteger number_1("-987654321");
	char* str = new char[5];
	EXPECT_EQ(11, number_1.ToString(str, 5));
	delete[](str);
	str = new char[11];
	EXPECT_EQ(11, number_1.ToString(str, 11));
	delete[](str);
}

TEST(TestCase_ToString, Test2) {
	LongInteger number_1("-987654321");
	LongInteger number_2("54");
	LongInteger number_3 = number_1 * number_2;
	char* str = new char[20];
	EXPECT_EQ(13, number_3.ToString(str, 20));
	delete[](str);
}

TEST(TestCase_ToString, Test3) {
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> number_length(15, 50);
	std::uniform_int_distribution<std::mt19937::result_type> numeral(0, 9);
	std::string input_str_number;
	char* bufer = new char;

	if (numeral(rng) % 2 == 0) {
		input_str_number.push_back('-');
	}
	input_str_number.push_back('8');
	
	for (size_t i = 0; i < number_length(rng); i++) {
		input_str_number.push_back(static_cast<char>(numeral(rng) + '0'));
	}
	input_str_number.push_back('\0');
	LongInteger number(input_str_number.c_str());

	size_t bufer_length = number.ToString(bufer, 1);
	delete(bufer);
	bufer = new char[bufer_length];
	EXPECT_EQ(number.ToString(bufer, bufer_length), bufer_length);
	EXPECT_STREQ(bufer, input_str_number.c_str());
	LongInteger _number(input_str_number.c_str());
	delete[](bufer);
}

TEST(TestCase_ToString, Test4) {
	std::string str_number("-1011111001111000111000011000001");
	str_number.push_back('\0');
	LongInteger number(str_number.c_str());
	size_t size_number = str_number.size();
	char* str = new char[size_number];
	EXPECT_EQ(size_number, number.ToString(str, size_number));
	EXPECT_STREQ(str, str_number.c_str());
	delete[](str);
}

//-----------------------------------------------------------------------------//

TEST(TestCase_OperatorEquals, Test_Empty_1) {
	LongInteger number_1("0");
	LongInteger number_2(number_1);
	EXPECT_TRUE(number_1 == number_2);
}

TEST(TestCase_OperatorEquals, Test_Empty_2) {
	LongInteger number_1;
	LongInteger number_2(number_1);
	EXPECT_TRUE(number_1 == number_2);
}

TEST(TestCase_OperatorEquals, Test_PositiveSign) {
	LongInteger number_1("102030405060708090908070605040302010");
	LongInteger number_2(number_1);
	EXPECT_TRUE(number_1 == number_2);
}

TEST(TestCase_OperatorEquals, Test_NegativeSign) {
	LongInteger number_1("-102030405060708090908070605040302010");
	LongInteger number_2(number_1);
	EXPECT_TRUE(number_1 == number_2);
}

TEST(TestCase_OperatorEquals, Test_OverLong) {
	std::string str;
	for (size_t i = 0; i < 10000; i++) {
		str.push_back('9');
	}
	LongInteger number_1(str.c_str());
	LongInteger number_2(str.c_str());
	EXPECT_TRUE(number_2 == number_1);
}

//-----------------------------------------------------------------------------//

TEST(TestCase_OperatorNotEquals, Test_Empty_1) {
	LongInteger number_1("0");
	LongInteger number_2("1235");
	EXPECT_TRUE(number_1 != number_2);
}

TEST(TestCase_OperatorNotEquals, Test_Empty_2) {
	LongInteger number_1;
	LongInteger number_2("1235");
	EXPECT_TRUE(number_1 != number_2);
}

TEST(TestCase_OperatorNotEquals, Test_PositiveSign) {
	LongInteger number_1("102030405060708090908070605040302010");
	LongInteger number_2("90807060504030201010203040506070809");
	EXPECT_TRUE(number_1 != number_2);
}

TEST(TestCase_OperatorNotEquals, Test_NegativeSign) {
	LongInteger number_1("-102030405060708090908070605040302010");
	LongInteger number_2("-90807060504030201010203040506070809");
	EXPECT_TRUE(number_1 != number_2);
}

TEST(TestCase_OperatorNotEquals, Test_DifferentSigns_1) {
	LongInteger number_1("-102030405060708090908070605040302010");
	LongInteger number_2("90807060504030201010203040506070809");
	EXPECT_TRUE(number_1 != number_2);
}

TEST(TestCase_OperatorNotEquals, Test_DifferentSigns_2) {
	LongInteger number_1("102030405060708090908070605040302010");
	LongInteger number_2("-90807060504030201010203040506070809");
	EXPECT_TRUE(number_1 != number_2);
}

//-----------------------------------------------------------------------------//

TEST(TestCase_OperatorLess, Test_PositiveSign) {
	LongInteger number_1("102030405060708090908070605040302010");
	LongInteger number_2("102030405060708090908");
	EXPECT_TRUE(number_2 < number_1);
}

TEST(TestCase_OperatorLess, Test_NegativeSign) {
	LongInteger number_1("-9999999999999999999999999999999999999999999999999999999999999999999999999");
	LongInteger number_2("-9999999999999999999999999999999999999999999999999999999999999999999999999999");
	EXPECT_TRUE(number_2 < number_1);
}

TEST(TestCase_OperatorLess, Test_Empty_1) {
	LongInteger number_1("999999998888888887777777777777666666666555555555");
	LongInteger number_2("0");
	EXPECT_TRUE(number_2 < number_1);
}

TEST(TestCase_OperatorLess, Test_Empty_2) {
	LongInteger number_1("9999999999999999999999999999999999999999999999999999");
	LongInteger number_2;
	EXPECT_TRUE(number_2 < number_1);
}

TEST(TestCase_OperatorLess, Test_DifferentSigns) {
	LongInteger number_1("99999999999999999999999999999999999999999999999999999999999999999999999999");
	LongInteger number_2("-9999999999999999999999999999999999999999999999999999999999999999999999999999");
	EXPECT_TRUE(number_2 < number_1);
}

TEST(TestCase_OperatorLess, Test_OverLong) {
	std::string str;
	str.push_back('-');
	for (size_t i = 0; i < 10000; i++) {
		str.push_back('9');
	}
	LongInteger number_1(str.c_str());
	str.push_back('9');
	LongInteger number_2(str.c_str());
	EXPECT_TRUE(number_2 < number_1);
}

//-----------------------------------------------------------------------------//

TEST(TestCase_OperatorMore, Test_PositiveSign) {
	LongInteger number_1("102030405060708090908070605040302010");
	LongInteger number_2("102030405060708090908");
	EXPECT_TRUE(number_1 > number_2);
}

TEST(TestCase_OperatorMore, Test_NegativeSign) {
	LongInteger number_1("-9999999999999999999999999999999999999999999999999999999999999999999999999");
	LongInteger number_2("-9999999999999999999999999999999999999999999999999999999999999999999999999999");
	EXPECT_TRUE(number_1 > number_2);
}

TEST(TestCase_OperatorMore, Test_Empty_1) {
	LongInteger number_1("999999998888888887777777777777666666666555555555");
	LongInteger number_2("0");
	EXPECT_TRUE(number_1 > number_2);
}

TEST(TestCase_OperatorMore, Test_Empty_2) {
	LongInteger number_1("9999999999999999999999999999999999999999999999999999");
	LongInteger number_2;
	EXPECT_TRUE(number_1 > number_2);
}

TEST(TestCase_OperatorMore, Test_DifferentSigns) {
	LongInteger number_1("99999999999999999999999999999999999999999999999999999999999999999999999999");
	LongInteger number_2("-9999999999999999999999999999999999999999999999999999999999999999999999999999");
	EXPECT_TRUE(number_1 > number_2);
}

TEST(TestCase_OperatorMore, Test_OverLong) {
	std::string str;
	str.push_back('-');
	for (size_t i = 0; i < 10000; i++) {
		str.push_back('9');
	}
	LongInteger number_1(str.c_str());
	str.push_back('9');
	LongInteger number_2(str.c_str());
	EXPECT_TRUE(number_1 > number_2);
}

//-----------------------------------------------------------------------------//

TEST(TestCase_OperatorMoreAndEquals, Test_PositiveSign) {
	LongInteger number_1("102030405060708090908070605040302010");
	LongInteger number_2("102030405060708090908");
	EXPECT_TRUE(number_1 >= number_2);
	number_2 = number_1;
	EXPECT_TRUE(number_1 >= number_2);
}

TEST(TestCase_OperatorMoreAndEquals, Test_NegativeSign) {
	LongInteger number_1("-102030405060708090908070605040302010");
	LongInteger number_2("-1020304050607080909084050405080706058070605");
	EXPECT_TRUE(number_1 >= number_2);
	number_2 = number_1;
	EXPECT_TRUE(number_1 >= number_2);
}

//-----------------------------------------------------------------------------//

TEST(TestCase_OperatorLessAndEquals, Test_PositiveSign) {
	LongInteger number_1("102030405060708090908070605040302010");
	LongInteger number_2("102030405060708090908405060708090908405060708090908");
	EXPECT_TRUE(number_1 <= number_2);
	number_2 = number_1;
	EXPECT_TRUE(number_1 <= number_2);
}

TEST(TestCase_OperatorLessAndEquals, Test_NegativeSign) {
	LongInteger number_1("-1020304050607080909080706050403020108070605");
	LongInteger number_2("-102030405060708090908405060708090908405060");
	EXPECT_TRUE(number_1 <= number_2);
	number_2 = number_1;
	EXPECT_TRUE(number_1 <= number_2);
}

//-----------------------------------------------------------------------------//

TEST(TestCase_OperatorAditionNotChanging, Test_PositiveSign) {
	LongInteger number_1("1000000000000000000000000000000000000000000000000000000000001");
	LongInteger number_2("8999999999999999999999999999999999999999999999999999999999999");
	LongInteger result_supposed("10000000000000000000000000000000000000000000000000000000000000");
	LongInteger result = number_1 + number_2;
	EXPECT_TRUE(result == result_supposed);
}

TEST(TestCase_OperatorAditionNotChanging, Test_NegativeSign) {
	LongInteger number_1("-1000000000000000000000000000000000000000000000000000000000001");
	LongInteger number_2("-8999999999999999999999999999999999999999999999999999999999999");
	LongInteger result_supposed("-10000000000000000000000000000000000000000000000000000000000000");
	LongInteger result = number_1 + number_2;
	EXPECT_TRUE(result == result_supposed);
}

TEST(TestCase_OperatorAditionNotChanging, Test_DifferentSigns_1) {
	LongInteger number_1("1000000000000000000000000000000000000000000000000000000000001");
	LongInteger number_2("-11000000000000000000000000000000000000000000000000000000000001");
	LongInteger result_supposed("-10000000000000000000000000000000000000000000000000000000000000");
	LongInteger result = number_1 + number_2;
	EXPECT_TRUE(result == result_supposed);
}

TEST(TestCase_OperatorAditionNotChanging, Test_DifferentSigns_2) {
	LongInteger number_1("-11000000000000000000000000000000000000000000000000000000000001");
	LongInteger number_2("1000000000000000000000000000000000000000000000000000000000001");
	LongInteger result_supposed("-10000000000000000000000000000000000000000000000000000000000000");
	LongInteger result = number_1 + number_2; 
	EXPECT_TRUE(result == result_supposed);
}

TEST(TestCase_OperatorAditionNotChanging, Test_WithZero) {

	EXPECT_TRUE(LongInteger{} == LongInteger{} + LongInteger{});
	EXPECT_TRUE(LongInteger("0") == LongInteger{} + LongInteger{});
	EXPECT_TRUE(LongInteger{} == LongInteger{} + LongInteger("0"));
	EXPECT_TRUE(LongInteger("0") == LongInteger{} + LongInteger("0"));
	EXPECT_TRUE(LongInteger("0") == LongInteger{} + LongInteger("-0"));
	EXPECT_TRUE(LongInteger{} == LongInteger("0") + LongInteger{});
	EXPECT_TRUE(LongInteger("0") == LongInteger("0") + LongInteger{});
	EXPECT_TRUE(LongInteger("0") == LongInteger("-0") + LongInteger{});
	EXPECT_TRUE(LongInteger{} == LongInteger("0") + LongInteger("0"));
	EXPECT_TRUE(LongInteger("0") == LongInteger("0") + LongInteger("0"));
	EXPECT_TRUE(LongInteger("0") == LongInteger("-0") + LongInteger("-0"));
}

TEST(TestCase_OperatorAditionNotChanging, Test_All) {

	EXPECT_TRUE(LongInteger("1000000000") == LongInteger("999999999") + LongInteger("1"));
	EXPECT_TRUE(LongInteger("1999999998") == LongInteger("999999999") + LongInteger("999999999"));
	EXPECT_TRUE(LongInteger("9999999998") == LongInteger("4999999999") + LongInteger("4999999999"));
	EXPECT_TRUE(LongInteger("999999999") == LongInteger("1000000000") + LongInteger("-1"));
	EXPECT_TRUE(LongInteger("0") == LongInteger("+1234567890") + LongInteger("-1234567890"));
	EXPECT_TRUE(LongInteger("-999999999") == LongInteger("-1000000000") + LongInteger("1"));
	EXPECT_TRUE(LongInteger("1000000000") == LongInteger("500000000") + LongInteger("500000000"));
	EXPECT_TRUE(LongInteger("-1000000000") == LongInteger("-1000000000") + LongInteger("0"));
	EXPECT_TRUE(LongInteger("1000000000") == LongInteger("1000000000") + LongInteger("0"));
	EXPECT_TRUE(LongInteger("-1000000000") == LongInteger("-1000000000") + LongInteger("-0"));
	EXPECT_TRUE(LongInteger("1000000000") == LongInteger("1000000000") + LongInteger("-0"));
}

//-----------------------------------------------------------------------------//

TEST(TestCase_OperatorAditionChanging, Test_PositiveSign) {
	LongInteger number_1("1000000000000000000000000000000000000000000000000000000000001");
	LongInteger number_2("8999999999999999999999999999999999999999999999999999999999999");
	LongInteger result_supposed("10000000000000000000000000000000000000000000000000000000000000");
	number_1 += number_2;
	EXPECT_TRUE(number_1 == result_supposed);
}

TEST(TestCase_OperatorAditionChanging, Test_NegativeSign) {
	LongInteger number_1("-1000000000000000000000000000000000000000000000000000000000001");
	LongInteger number_2("-8999999999999999999999999999999999999999999999999999999999999");
	LongInteger result_supposed("-10000000000000000000000000000000000000000000000000000000000000");
	number_1 += number_2;
	EXPECT_TRUE(number_1 == result_supposed);
}

TEST(TestCase_OperatorAditionChanging, Test_DifferentSigns_1) {
	LongInteger number_1("1000000000000000000000000000000000000000000000000000000000001");
	LongInteger number_2("-11000000000000000000000000000000000000000000000000000000000001");
	LongInteger result_supposed("-10000000000000000000000000000000000000000000000000000000000000");
	number_1 += number_2;
	EXPECT_TRUE(number_1 == result_supposed);
}

TEST(TestCase_OperatorAditionChanging, Test_DifferentSigns_2) {
	LongInteger number_1("-11000000000000000000000000000000000000000000000000000000000001");
	LongInteger number_2("1000000000000000000000000000000000000000000000000000000000001");
	LongInteger result_supposed("-10000000000000000000000000000000000000000000000000000000000000");
	number_1 += number_2;
	EXPECT_TRUE(number_1 == result_supposed);
}

TEST(TestCase_OperatorAditionChanging, Test_Corectly_1) {
	LongInteger number_1("80509740938211948536753469621962264689830310329122849810180724");
	LongInteger number_2("752988030804275145849205212476531422325926585142571146");
	LongInteger result_supposed("80509741691199979341028615471167477166361732655049434952751870");
	number_1 += number_2;
	EXPECT_TRUE(number_1 == result_supposed);
}

//-----------------------------------------------------------------------------//

TEST(TestCase_OperatorSubtractionNotChanging, Test_PositiveSign) {
	LongInteger number_1("12111111111111111111111111111111111111111111111111111111111111111");
	LongInteger number_2("11111111111111111111111111111111111111111111111111111111111111111");
	LongInteger result_supposed("1000000000000000000000000000000000000000000000000000000000000000");
	LongInteger result = number_1 - number_2;
	EXPECT_TRUE(result == result_supposed);
}

TEST(TestCase_OperatorSubtractionNotChanging, Test_NegativeSign) {
	LongInteger number_1("-12111111111111111111111111111111111111111111111111111111111111111");
	LongInteger number_2("-11111111111111111111111111111111111111111111111111111111111111111");
	LongInteger result_supposed("-1000000000000000000000000000000000000000000000000000000000000000");
	LongInteger result = number_1 - number_2;
	EXPECT_TRUE(result == result_supposed);
}

TEST(TestCase_OperatorSubtractionNotChanging, Test_DifferentSigns_1) {
	LongInteger number_1("-8999999999999999999999999999999999999999999999999999999999999");
	LongInteger number_2("1000000000000000000000000000000000000000000000000000000000001");
	LongInteger result_supposed("-10000000000000000000000000000000000000000000000000000000000000");
	LongInteger result = number_1 - number_2;
	EXPECT_TRUE(result == result_supposed);
}

TEST(TestCase_OperatorSubtractionNotChanging, Test_DifferentSigns_2) {
	LongInteger number_1("1000000000000000000000000000000000000000000000000000000000001");
	LongInteger number_2("-8999999999999999999999999999999999999999999999999999999999999");
	LongInteger result_supposed("10000000000000000000000000000000000000000000000000000000000000");
	LongInteger result = number_1 - number_2;
	EXPECT_TRUE(result == result_supposed);
}

TEST(TestCase_OperatorSubtractionNotChanging, Test_WithZero) {

	EXPECT_TRUE(LongInteger{} == LongInteger{} - LongInteger{});
	EXPECT_TRUE(LongInteger("0") == LongInteger{} - LongInteger{});
	EXPECT_TRUE(LongInteger{} == LongInteger{} - LongInteger("0"));
	EXPECT_TRUE(LongInteger("0") == LongInteger{} - LongInteger("0"));
	EXPECT_TRUE(LongInteger{} == LongInteger("0") - LongInteger{});
	EXPECT_TRUE(LongInteger("0") == LongInteger("0") - LongInteger{});
	EXPECT_TRUE(LongInteger{} == LongInteger("0") - LongInteger("0"));
	EXPECT_TRUE(LongInteger("0") == LongInteger("0") - LongInteger("0"));
}

//-----------------------------------------------------------------------------//

TEST(TestCase_OperatorSubtractionChanging, Test_PositiveSign) {
	LongInteger number_1("12111111111111111111111111111111111111111111111111111111111111111");
	LongInteger number_2("11111111111111111111111111111111111111111111111111111111111111111");
	LongInteger result_supposed("1000000000000000000000000000000000000000000000000000000000000000");
	number_1 -= number_2;
	EXPECT_TRUE(number_1 == result_supposed);
}

TEST(TestCase_OperatorSubtractionChanging, Test_NegativeSign) {
	LongInteger number_1("-12111111111111111111111111111111111111111111111111111111111111111");
	LongInteger number_2("-11111111111111111111111111111111111111111111111111111111111111111");
	LongInteger result_supposed("-1000000000000000000000000000000000000000000000000000000000000000");
	number_1 -= number_2;
	EXPECT_TRUE(number_1 == result_supposed);
}

TEST(TestCase_OperatorSubtractionChanging, Test_DifferentSigns_1) {
	LongInteger number_1("-8999999999999999999999999999999999999999999999999999999999999");
	LongInteger number_2("1000000000000000000000000000000000000000000000000000000000001");
	LongInteger result_supposed("-10000000000000000000000000000000000000000000000000000000000000");
	number_1 -= number_2;
	EXPECT_TRUE(number_1 == result_supposed);
}

TEST(TestCase_OperatorSubtractionChanging, Test_DifferentSigns_2) {
	LongInteger number_1("1000000000000000000000000000000000000000000000000000000000001");
	LongInteger number_2("-8999999999999999999999999999999999999999999999999999999999999");
	LongInteger result_supposed("10000000000000000000000000000000000000000000000000000000000000");
	number_1 -= number_2;
	EXPECT_TRUE(number_1 == result_supposed);
}

//-----------------------------------------------------------------------------//

TEST(TestCase_OperatorMultiplicationNotChanging, Test_CorrecttRansfer) {
	LongInteger number_1("35000000000000000000002000000000001");
	LongInteger number_2("-65");
	LongInteger result_supposed("-2275000000000000000000130000000000065");
	LongInteger result = number_1 * number_2;
	EXPECT_TRUE(result == result_supposed);
}

TEST(TestCase_OperatorMultiplicationNotChanging, Test_PositiveSign) {
	LongInteger number_1("111111111111111111111111111111111111111111111111111111111111");
	LongInteger number_2("11");
	LongInteger result_supposed("1222222222222222222222222222222222222222222222222222222222221");
	LongInteger result = number_1 * number_2;
	EXPECT_TRUE(result == result_supposed);
}

TEST(TestCase_OperatorMultiplicationNotChanging, Test_NegativeSign) {
	LongInteger number_1("-111111111111111111111111111111111111111111111111111111111111");
	LongInteger number_2("-11");
	LongInteger result_supposed("1222222222222222222222222222222222222222222222222222222222221");
	LongInteger result = number_1 * number_2;
	EXPECT_TRUE(result == result_supposed);
}

TEST(TestCase_OperatorMultiplicationNotChanging, Test_DifferentSigns_1) {
	LongInteger number_1("222222222222222222222222222222");
	LongInteger number_2("-4");
	LongInteger result_supposed("-888888888888888888888888888888");
	LongInteger result = number_1 * number_2;
	EXPECT_TRUE(result == result_supposed);
}

TEST(TestCase_OperatorMultiplicationNotChanging, Test_DifferentSigns_2) {
	LongInteger number_1("-33333333333333333333333333333333333333333333333");
	LongInteger number_2("3");
	LongInteger result_supposed("-99999999999999999999999999999999999999999999999");
	LongInteger result = number_1 * number_2;
	EXPECT_TRUE(result == result_supposed);
}

TEST(TestCase_OperatorMultiplicationNotChanging, Test_Breaking) {
	LongInteger result = LongInteger{ "987654321987654321" } * LongInteger{ "123456789123456789" };
	LongInteger result_supposed("121932631356500531347203169112635269");
	EXPECT_TRUE(result == result_supposed);
}

//-----------------------------------------------------------------------------//

TEST(TestCase_OperatorMultiplicationChanging, Test_CorrecttRansfer) {
	LongInteger number_1("35000000000000000000002000000000001");
	LongInteger number_2("-65");
	LongInteger result_supposed("-2275000000000000000000130000000000065");
	number_1 *= number_2;
	EXPECT_TRUE(number_1 == result_supposed);
}

TEST(TestCase_OperatorMultiplicationChanging, Test_PositiveSign) {
	LongInteger number_1("111111111111111111111111111111111111111111111111111111111111");
	LongInteger number_2("11");
	LongInteger result_supposed("1222222222222222222222222222222222222222222222222222222222221");
	number_1 *= number_2;
	EXPECT_TRUE(number_1 == result_supposed);
}

TEST(TestCase_OperatorMultiplicationChanging, Test_NegativeSign) {
	LongInteger number_1("-111111111111111111111111111111111111111111111111111111111111");
	LongInteger number_2("-11");
	LongInteger result_supposed("1222222222222222222222222222222222222222222222222222222222221");
	number_1 *= number_2;
	EXPECT_TRUE(number_1 == result_supposed);
}

TEST(TestCase_OperatorMultiplicationChanging, Test_DifferentSigns_1) {
	LongInteger number_1("222222222222222222222222222222");
	LongInteger number_2("-4");
	LongInteger result_supposed("-888888888888888888888888888888");
	number_1 *= number_2;
	EXPECT_TRUE(number_1 == result_supposed);
}

TEST(TestCase_OperatorMultiplicationChanging, Test_DifferentSigns_2) {
	LongInteger number_1("-33333333333333333333333333333333333333333333333");
	LongInteger number_2("3");
	LongInteger result_supposed("-99999999999999999999999999999999999999999999999");
	number_1 *= number_2;
	EXPECT_TRUE(number_1 == result_supposed);
}

//-----------------------------------------------------------------------------//

TEST(TestCase_OperatorDivisionNotChanging, Test_ExceptionNull) {
	LongInteger number_1("987654321159263487852741963654852357241689");
	LongInteger number_2("0");
	LongInteger result_supposed("-2275000000000000000000130000000000065");
	EXPECT_THROW({ LongInteger result = number_1 / number_2; }, std::exception);
}

TEST(TestCase_OperatorDivisionNotChanging, Test_CorrecttRansfer) {
	LongInteger number_1("1000000000000000000000000000000000000000000000000000000");
	LongInteger number_2("-1000000000000000000000000000");
	LongInteger result_supposed("-1000000000000000000000000000");
	LongInteger result = number_1 / number_2;
	EXPECT_TRUE(result == result_supposed);
}

TEST(TestCase_OperatorDivisionNotChanging, Test_DivisionByZero) {
	EXPECT_THROW({ LongInteger(25) / LongInteger{}; }, std::invalid_argument);
	EXPECT_THROW({ LongInteger(25) / LongInteger(0);}, std::invalid_argument);
}

TEST(TestCase_OperatorDivisionNotChanging, Test_PositiveSign) {
	LongInteger number_1("1222222222222222222222222222222222222222222222222222222222221");
	LongInteger number_2("11");
	LongInteger result_supposed("111111111111111111111111111111111111111111111111111111111111");
	LongInteger result = number_1 / number_2;
	EXPECT_TRUE(result == result_supposed);
}

TEST(TestCase_OperatorDivisionNotChanging, Test_NegativeSign) {
	LongInteger number_1("-1222222222222222222222222222222222222222222222222222222222221");
	LongInteger number_2("-11");
	LongInteger result_supposed("111111111111111111111111111111111111111111111111111111111111");
	LongInteger result = number_1 / number_2;
	EXPECT_TRUE(result == result_supposed);
}

TEST(TestCase_OperatorDivisionNotChanging, Test_DifferentSigns_1) {
	LongInteger number_1("-888888888888888888888888888888");
	LongInteger number_2("4");
	LongInteger result_supposed("-222222222222222222222222222222");
	LongInteger result = number_1 / number_2;
	EXPECT_TRUE(result == result_supposed);
}

TEST(TestCase_OperatorDivisionNotChanging, Test_DifferentSigns_2) {
	LongInteger number_1("99999999999999999999999999999999999999999999999");
	LongInteger number_2("-3");
	LongInteger result_supposed("-33333333333333333333333333333333333333333333333");
	LongInteger result = number_1 / number_2;
	EXPECT_TRUE(result == result_supposed);
}

//-----------------------------------------------------------------------------//

TEST(TestCase_OperatorDivisionChanging, Test_ExceptionNull) {
	LongInteger number_1("987654321159263487852741963654852357241689");
	LongInteger number_2("0");
	LongInteger result_supposed("-2275000000000000000000130000000000065");
	EXPECT_THROW({ number_1 /= number_2; }, std::exception);
}

TEST(TestCase_OperatorDivisionChanging, Test_CorrecttRansfer) {
	LongInteger number_1("1000000000000000000000000000000000000000000000000000000");
	LongInteger number_2("-1000000000000000000000000000");
	LongInteger result_supposed("-1000000000000000000000000000");
	number_1 /= number_2;
	EXPECT_TRUE(number_1 == result_supposed);
}

TEST(TestCase_OperatorDivisionChanging, Test_PositiveSign) {
	LongInteger number_1("1222222222222222222222222222222222222222222222222222222222221");
	LongInteger number_2("11");
	LongInteger result_supposed("111111111111111111111111111111111111111111111111111111111111");
	number_1 /= number_2;
	EXPECT_TRUE(number_1 == result_supposed);
}

TEST(TestCase_OperatorDivisionChanging, Test_NegativeSign) {
	LongInteger number_1("-1222222222222222222222222222222222222222222222222222222222221");
	LongInteger number_2("-11");
	LongInteger result_supposed("111111111111111111111111111111111111111111111111111111111111");
	number_1 /= number_2;
	EXPECT_TRUE(number_1 == result_supposed);
}

TEST(TestCase_OperatorDivisionChanging, Test_DifferentSigns_1) {
	LongInteger number_1("-888888888888888888888888888888");
	LongInteger number_2("4");
	LongInteger result_supposed("-222222222222222222222222222222");
	number_1 /= number_2;
	EXPECT_TRUE(number_1 == result_supposed);
}

TEST(TestCase_OperatorDivisionChanging, Test_DifferentSigns_2) {
	LongInteger number_1("99999999999999999999999999999999999999999999999");
	LongInteger number_2("-3");
	LongInteger result_supposed("-33333333333333333333333333333333333333333333333");
	number_1 /= number_2;
	EXPECT_TRUE(number_1 == result_supposed);
}

//-----------------------------------------------------------------------------//

TEST(TestCase_OperatorAditionChanging_WithInt, Test_) {
	LongInteger number_1("11099999999999999999999999999999999999999999211");
	LongInteger result_supposed("11100000000000000000000000000000000000000000000");
	number_1 += 789;
	EXPECT_TRUE(number_1 == result_supposed);
}

//-----------------------------------------------------------------------------//

TEST(TestCase_OperatorSubtractionChanging_WithInt, Test_) {
	LongInteger number_1("1000000000000000000000000000000000000000000000000000000000000");
	LongInteger result_supposed("999999999999999999999999999999999999999999999999999999999877");
	number_1 -= 123;
	EXPECT_TRUE(number_1 == result_supposed);
}

//-----------------------------------------------------------------------------//

TEST(TestCase_OperatorMultiplicationChanging_WithInt, Test_) {
	LongInteger number_1("35000000000000000000002000000000001");
	LongInteger result_supposed("-2275000000000000000000130000000000065");
	number_1 *= -65;
	EXPECT_TRUE(number_1 == result_supposed);
}

//-----------------------------------------------------------------------------//

TEST(TestCase_OperatorDivisionChanging_WithInt, Test_) {
	LongInteger number_1("233233233233233233");
	LongInteger result_supposed("1001001001001001");
	number_1 /= 233;
	EXPECT_TRUE(number_1 == result_supposed);
}

//-----------------------------------------------------------------------------//

TEST(TestCase_OperatorWithZero, Test_Equals)
{
	EXPECT_TRUE(LongInteger{} == LongInteger{});
	EXPECT_TRUE(LongInteger{} == LongInteger{ "0" });
	EXPECT_TRUE(LongInteger{"0"} == LongInteger{});
	EXPECT_TRUE(LongInteger{"0"} == LongInteger{"0"});
	EXPECT_TRUE(LongInteger{ "0" } == LongInteger{ "-0" });
	EXPECT_TRUE(LongInteger{ "-0" } == LongInteger{ "0" });
	EXPECT_TRUE(LongInteger{ "-0" } == LongInteger{ "-0" });
	EXPECT_TRUE(LongInteger{ "-00000000000000000" } == LongInteger{ "000" });
}

TEST(TestCase_OperatorWithZero, Test_Less)
{
	EXPECT_TRUE(!(LongInteger{} < LongInteger{}));
	EXPECT_TRUE(!(LongInteger{} < LongInteger{ "0" }));
	EXPECT_TRUE(!(LongInteger{ "0" } < LongInteger{}));
	EXPECT_TRUE(!(LongInteger{ "0" } < LongInteger{ "0" }));
}

TEST(TestCase_OperatorWithZero, Test_LessEquals)
{
	EXPECT_TRUE(LongInteger{} <= LongInteger{});
	EXPECT_TRUE(LongInteger{} <= LongInteger{ "0" });
	EXPECT_TRUE(LongInteger{ "0" } <= LongInteger{});
	EXPECT_TRUE(LongInteger{ "0" } <= LongInteger{ "0" });
}

TEST(TestCase_OperatorWithZero, Test_More)
{
	EXPECT_TRUE(!(LongInteger{} > LongInteger{}));
	EXPECT_TRUE(!(LongInteger{} > LongInteger{ "0" }));
	EXPECT_TRUE(!(LongInteger{ "0" } > LongInteger{}));
	EXPECT_TRUE(!(LongInteger{ "0" } > LongInteger{ "0" }));
}

TEST(TestCase_OperatorWithZero, Test_MoreEquals)
{
	EXPECT_TRUE(LongInteger{} >= LongInteger{});
	EXPECT_TRUE(LongInteger{} >= LongInteger{ "0" });
	EXPECT_TRUE(LongInteger{ "0" } >= LongInteger{});
	EXPECT_TRUE(LongInteger{ "0" } >= LongInteger{ "0" });
}

TEST(TestCase_OperatorWithZero, Test_NotEquals)
{
	EXPECT_TRUE(!(LongInteger{} != LongInteger{}));
	EXPECT_TRUE(!(LongInteger{} != LongInteger{ "0" }));
	EXPECT_TRUE(!(LongInteger{ "0" } != LongInteger{}));
	EXPECT_TRUE(!(LongInteger{ "0" } != LongInteger{ "0" }));
}

//TEST(TestCase_Timer, Test_comparison_operators)
//{
//	std::random_device dev;
//	std::mt19937 rng(dev());
//	std::uniform_int_distribution<std::mt19937::result_type> number_length(10000, 10000);
//	std::uniform_int_distribution<std::mt19937::result_type> numeral(0, 9);
//	std::string input_str_number;
//
//	input_str_number.push_back('1');
//	for (size_t i = 0; i < number_length(rng); i++) {
//		input_str_number.push_back(numeral(rng) + '0');
//	}
//
//	const LongInteger number_1(input_str_number.c_str());
//
//	input_str_number.clear();
//	input_str_number.push_back('1');
//	for (size_t i = 0; i < number_length(rng); i++) {
//		input_str_number.push_back(numeral(rng) + '0');
//	}
//
//	const LongInteger number_2(input_str_number.c_str());
//
//	std::ofstream iof;
//	iof.open("result_time.txt", std::ios::app);
//
//	clock_t start = clock();
//
//	const bool result_operator = number_1 < number_2;
//
//	clock_t end = clock();
//	const long double seconds = static_cast<long double>(end - start) / CLOCKS_PER_SEC;
//
//	if (iof.is_open())
//	{
//		iof << std::endl;
//		iof << "The time: " << seconds  << " seconds." << std::endl;
//	}
//
//	iof.close();
//}

//TEST(TestCase_RealBigNumbers, Test_) {
//	std::string str;
//	for (size_t i = 0; i < 10000000; i++) {
//		str.push_back('9');
//	}
//	LongInteger number_1(str.c_str());
//	LongInteger number_2(str.c_str());
//	number_2 /= 333333333;
//	number_1 -= number_2;
//	//number_1 += (number_1 % number_2);
//	//number_1 = number_1 / number_2;
//	//number_2 = number_1 + number_2;
//	//number_2 -= 999999999;
//	//number_2 *= 7;
//	//number_1 = number_1 + number_2 * number_1;
//	EXPECT_TRUE(number_2 != number_1);
//}

//TEST(TestCaseName, TestName) {
//  EXPECT_EQ(1, 1);
//  EXPECT_TRUE(true);
//}
