#include "pch.h"
#include "LongInteger.hpp"

//-----------------------------------------------------------------------------//

TEST(TestCase_Ctor, Test_nathing) {
	LongInteger number_1("123456");
	char* str;
	EXPECT_TRUE(6 + 1, number_1.ToString(str, 0));
}

TEST(TestCase_Ctor, Test_str) {
	LongInteger number_1("1251654654621");
	char* str = new char[14];
	EXPECT_EQ(14, number_1.ToString(str, 14));
	//EXPECT_TRUE(true);
	delete[](str);
}

TEST(TestCase_Ctor, Test_Int) {
	LongInteger number_1(12506151);
	char* str;
	EXPECT_TRUE(8 + 1, number_1.ToString(str, 0));
}

//-----------------------------------------------------------------------------//

TEST(TestCase_CtorCopy, Test) {
	LongInteger number_1(12506151);
	LongInteger number_2(number_1);
	EXPECT_TRUE(true);
}

//-----------------------------------------------------------------------------//

TEST(TestCase_ToString, Test) {
	LongInteger number_1("-987654321");
	char* str = new char[5];
	EXPECT_EQ(11, number_1.ToString(str, 5));
	delete[](str);
	str = new char[11];
	EXPECT_EQ(11, number_1.ToString(str, 11));
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

TEST(TestCase_RealBigNumbers, Test_) {
	std::string str;
	for (size_t i = 0; i < 10000000; i++) {
		str.push_back('9');
	}
	LongInteger number_1(str.c_str());
	LongInteger number_2(str.c_str());
	number_2 /= 333333333;
	number_1 -= number_2;
	//number_1 += (number_1 % number_2);
	//number_1 = number_1 / number_2;
	//number_2 = number_1 + number_2;
	//number_2 -= 999999999;
	//number_2 *= 7;
	//number_1 = number_1 + number_2 * number_1;
	EXPECT_TRUE(number_2 != number_1);
}

//TEST(TestCaseName, TestName) {
//  EXPECT_EQ(1, 1);
//  EXPECT_TRUE(true);
//}