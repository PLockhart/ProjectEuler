#include <iostream>
#include <math.h>

bool isNumberPalindrome(int number) {

	int numDigits = 0;
	int n = number;

	while (n > 0) {

		++numDigits;
		n /= 10;
	}

	//minus 2 each loop as we are taking off the front and the end
	for (int i = numDigits; i > 0; i -= 2) {

		int divider = _Pow_int(10, i - 1);
		int leftMostDigit = number / divider;
		int rightMostDigit = number % 10;

		if (leftMostDigit != rightMostDigit)
			return false;

		//drop the left most number
		number = number % divider;
		//drop the right most number
		number /= 10;
	}
	
	return true;
}

void main(int aNum, char** args) {

	int numDigits = 3;

	//work out the max N digit number we can have
	int maxDigit = 0;
	for (int i = 0; i < numDigits; ++i) {

		maxDigit *= 10;
		maxDigit += 9;
	}

	if (isNumberPalindrome(998899))
		std::cout << "Palindrom" << std::endl;

	int maxPalindrome = 0;

	//now work back from the max digit down through all the multiples checking for a palindrome
	for (int i = maxDigit; i > 0; --i) {

		for (int j = i; j > 0; --j) {

			int product = i * j;

			if (isNumberPalindrome(product) && product > maxPalindrome) {

				//we have reached the max along this vein. So move on to the next pdocut
				maxPalindrome = product;
				break;
			}
		}
	}
	std::cout << "Largest: " << maxPalindrome << std::endl;
}