/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LeetCodeMath.hpp
 * Author: xuwei.huang
 *
 * Created on 2018年3月27日, 下午8:41
 */

#ifndef LEETCODEMATH_HPP
#define LEETCODEMATH_HPP
#include "Common.h"

#include <algorithm>
#include <climits>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::unordered_map;
using std::vector;


// 7. Reverse Integer
// Topics: math

/*
 * Given a 32-bit signed integer, reverse digits of an integer.
 *
 * Input: 123
 * Output:  321
 *
 * Input: -123
 * Output: -321
 *
 * Note:
 * Assume we are dealing with an environment which could only hold integers within the 32-bit signed integer range. For the purpose of this problem, assume that your function returns 0 when the reversed integer overflows.
 */

class ReverseInteger {
public:

    int reverse(int x) {
        long long total = 0;
        while (x) {
            total = total * 10 + x % 10;
            x /= 10;
            if (total > INT_MAX || total < INT_MIN) {
                return 0;
            }
        }
        return total;
    }

    void Test() {
        int test = -1234555555;
        cout << "ReverseInteger: " << reverse(test) << endl;
    }
};


// 9. Palindrome Number
// Topics: math

/*
 * Determine whether an integer is a palindrome. Do this without extra space.
 *
 * Some hints:
 * Could negative integers be palindromes? (ie, -1)
 * If you are thinking of converting the integer to std::string, note the restriction of using extra space.
 * You could also try reversing an integer. However, if you have solved the problem "Reverse Integer", you know that the reversed integer might overflow. How would you handle such case?
 * There is a more generic way of solving this problem.
 */

class PalindromeNumber {
public:

    bool isPalindrome(int x) {
        if (x < 0 || (x != 0 && x % 10 == 0)) {
            return false;
        }
        int reverse = 0;
        while (x > reverse) {
            reverse = reverse * 10 + x % 10;
            x = x / 10;
        }
        return (x == reverse || x == reverse / 10);
    }

    void Test() {
        int test = 123454321;
        cout << "PalindromeNumber: " << isPalindrome(test) << endl;
    }
};


// 12. Integer to Roman
// Topics: math, std::string

/*
 * Given an integer, convert it to a roman numeral.
 * Input is guaranteed to be within the range from 1 to 3999.
 */

class Integer2Roman {
public:

    std::string intToRoman(int num) {
        // 1, 5, 10分界. 1可以重复3次表示3, 第四次需要加在5, 10的左侧表示减1. 增加一个分界
        // C++中的定义, 看中运算符的优先级, 先结合[], 表示是一个数组, int 表示存储的元素是 int 类型
        static int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
        // M 1000
        // D 500
        // C 100
        // L 50
        // X 10
        // V 5
        // I 1
        static std::string strings[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
        std::string romanStr;
        for (int i = 0; i < (int) (sizeof (values) / sizeof (int)); i++) {
            while (num >= values[i]) {
                num -= values[i]; // 依次相减
                romanStr.append(strings[i]);
            }
        }
        return romanStr;
    }

    std::string betterIntToRoman(int num) {
        // 将个十百千位上的数字表示完毕, 整除可得倍数
        //                       1000  2000   3000   
        static std::string M[] = {"", "M", "MM", "MMM"}; // 罗马数字在此后使用上划线, 表示扩大1000倍, 然后表示所有的数
        //                        100  200   300     400   500   600   700    800      900 
        static std::string C[] = {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};
        //                        10   20     30     40    50    60    70     80       90  
        static std::string X[] = {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
        //                        1    2      3      4     5     6     7      8        9  
        static std::string I[] = {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};

        return M[num / 1000] + C[num % 1000 / 100] + X[num % 100 / 10] + I[num % 10];
    }

    void Test() {
        int num = 3459;
        cout << "intToRoman: " << intToRoman(num) << endl;
        cout << "betterIntToRoman: " << betterIntToRoman(num) << endl;
    }
};

// 13. Roman to Integer
// Topics: math, std::string

/*
 * Given a roman numeral, convert it to an integer.
 * Input is guaranteed to be within the range from 1 to 3999.
 */

class Roman2Integer {
public:
    // case from left

    int romanToIntLeft(std::string s) {
        static unordered_map<char, int> T = {
            {'I', 1},
            {'V', 5},
            {'X', 10},
            {'L', 50},
            {'C', 100},
            {'D', 500},
            {'M', 1000}
        };
        if (s.empty()) {
            return -1;
        }

        int sum = 0;
        // 从左向右扫描
        // 注意 s.lenght() unsigned int. 直接 -2 会数据溢出.
        for (int i = 0; i <= int(s.length()) - 2; i++) {
            if (T[s[i]] < T[s[i + 1]]) // [i+1] 可能会越界, 使用 length()-2
                sum -= T[s[i]];
            else
                sum += T[s[i]];
        }
        sum += T[s.back()];
        return sum;
    }

    // case from right

    int romanToIntRight(std::string s) {
        static unordered_map<char, int> T = {
            {'I', 1},
            {'V', 5},
            {'X', 10},
            {'L', 50},
            {'C', 100},
            {'D', 500},
            {'M', 1000}
        };
        if (s.empty()) {
            return -1;
        }

        int sum = T[s.back()];
        // 从右向左扫描
        for (int i = s.length() - 2; i >= 0; i--) {
            if (T[s[i]] < T[s[i + 1]]) // [i+1] 可能会越界, 使用 length()-2
                sum -= T[s[i]];
            else
                sum += T[s[i]];
        }
        return sum;
    }

    void Test() {
        std::string s = "D";
        cout << "romanToIntLeft: " << romanToIntLeft(s) << endl;
        cout << "romanToIntRight: " << romanToIntRight(s) << endl;
    }
};


// 29. Divide Two Integers
// Topics: math, binary search

/*
 * Given two integers dividend and divisor, divide two integers without using multiplication, division and mod operator.
 * 
 * Return the quotient after dividing dividend by divisor.
 * 
 * Example 1:
 * 
 * Input: dividend = 10, divisor = 3
 * Output: 3
 * Example 2:
 * 
 * Input: dividend = 7, divisor = -3
 * Output: -2
 * Note:
 * 
 * Both dividend and divisor will be 32-bit signed integers.
 * The divisor will never be 0.
 * Assume we are dealing with an environment which could only store integers within the 32-bit signed integer range: [−231,  231 − 1]. For the purpose of this problem, assume that your function returns 231 − 1 when the division result overflows.
 */

class DivideTwoIntegers {
public:

    int divide(int dividend, int divisor) {
        if (!divisor || (dividend == INT_MIN && divisor == -1))
            return INT_MAX;
        int sign = (dividend < 0) ^ (divisor < 0) ? -1 : 1;
        long dvd = std::labs(dividend);
        long dvs = std::labs(divisor);
        int res = 0;
        while (dvd >= dvs) {
            long temp = dvs, multiple = 1;
            while (dvd >= (temp << 1)) {
                temp <<= 1; // 只能用移位, 2的倍数来计算, 不使用乘法 
                multiple <<= 1;
            }
            dvd -= temp; // 一次 2倍数处理之后的余数
            res += multiple;
        }
        return sign == 1 ? res : -res;
    }

    void Test() {
        int dvd = 80;
        int dvs = 3;
        cout << "divide: " << divide(dvd, dvs) << endl;
    }
};


#endif /* LEETCODEMATH_HPP */

