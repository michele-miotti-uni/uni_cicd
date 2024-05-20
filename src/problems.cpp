#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <array>
#include <algorithm>
#include <tgmath.h>

// ############################### PROBLEM 1: Balanced Number [lvl 1] #############################################
//  A balanced number is a number where the sum of digits to the left of the middle digit(s)
//  and the sum of digits to the right of the middle digit(s) are equal.
//  If the number has an odd number of digits,
//  then there is only one middle digit. (For example, 92645 has one middle digit, 6.)
//  Otherwise, there are two middle digits. (For example, the middle digits of 1301 are 3 and 0.)
//  The middle digit(s) should not be considered when determining whether
//  a number is balanced or not, e.g. 413023 is a balanced number because the left sum and right sum are both 5.
//  Given a number, find if it is balanced, and return the string "Balanced" or "Not Balanced" accordingly.
//  The passed number will always be positive.

//  Examples
//  7 ==> return "Balanced"
//  Explanation:
//  middle digit(s): 7
//  sum of all digits to the left of the middle digit(s) -> 0
//  sum of all digits to the right of the middle digit(s) -> 0
//  0 and 0 are equal, so it's balanced.
//  295591 ==> return "Not Balanced"
//  Explanation:
//  middle digit(s): 55
//  sum of all digits to the left of the middle digit(s) -> 11
//  sum of all digits to the right of the middle digit(s) -> 10
//  11 and 10 are not equal, so it's not balanced.
//  959 ==> return "Balanced"
//  Explanation:
//  middle digit(s): 5
//  sum of all digits to the left of the middle digit(s) -> 9
//  sum of all digits to the right of the middle digit(s) -> 9
//  9 and 9 are equal, so it's balanced.
//  27102983 ==> return "Not Balanced"
//  Explanation:
//  middle digit(s): 02
//  sum of all digits to the left of the middle digit(s) -> 10
//  sum of all digits to the right of the middle digit(s) -> 20
//  10 and 20 are not equal, so it's not balanced.

bool balancedNumHelper(unsigned long long int number, unsigned long long int left_sum, unsigned long long int right_sum) {
	if (number < 100) {
		return left_sum == right_sum;
	}
	
	right_sum += number % 10;
	const std::string number_string = std::to_string(number);
	const std::string first_digit_string = number_string.substr(0, 1);
	const unsigned long long first_digit = std::stoull(first_digit_string);
	left_sum += first_digit;
	const unsigned long long reduced_number = (number - first_digit * std::pow(10, number_string.size()-1U)) / 10;
	return balancedNumHelper(reduced_number, left_sum, right_sum);
}

std::string balancedNum(unsigned long long int number)
{
  if (balancedNumHelper(number, 0, 0)) {
  	return "Balanced";
  }
  return "Not Balanced";
}

// ********************************************************************************************************


// ############################### PROBLEM 2: Isograms [lvl 1] #############################################
// An isogram is a word that has no repeating letters, consecutive or non-consecutive. Implement a function 
//that determines whether a string that contains only letters is an isogram. Assume the empty string is an isogram. Ignore letter case.
// Example: (Input --> Output)
// "Dermatoglyphics" --> true
// "aba" --> false
// "moOse" --> false (ignore letter case)

std::string str_tolower(std::string s)
{
    std::transform(s.begin(), s.end(), s.begin(), 
                // static_cast<int(*)(int)>(std::tolower)         // wrong
                // [](int c){ return std::tolower(c); }           // wrong
                // [](char c){ return std::tolower(c); }          // wrong
                   [](unsigned char c){ return std::tolower(c); } // correct
                  );
    return s;
}

bool is_isogram(std::string str) {
  const std::string lower_str = str_tolower(str);
  std::array<unsigned int, 26> occurrences = {};
  for (unsigned int i = 0; i < lower_str.size(); i++) {
  	const char character = lower_str[i];
  	if (character >= 'a' && character <= 'z') {
  		occurrences[character-'a']++;
  	}
  }
  for (unsigned int i = 0; i < 26; i++) {
  	if (occurrences[i] > 1) {
  		return false;
  	}
  }
  return true;
}

// ********************************************************************************************************

// ############################### PROBLEM 3: All or Nothing [lvl 1] #############################################
// Suppose a student can earn 100% on an exam by getting the answers all correct or all incorrect. 
// Given a potentially incomplete answer key and the student's answers, 
// write a function that determines whether or not a student can still score 100%. 
// Incomplete questions are marked with an underscore, "_".

// ["A", "_", "C", "_", "B"]   # answer key
// ["A", "D", "C", "E", "B"]   # student's solution

// ➞ True

// # Possible for student to get all questions correct.

// ["B", "_", "B"]   # answer key
// ["B", "D", "C"]   # student's solution

// ➞ False

// # First question is correct but third is wrong, so not possible to score 100%.

// ["T", "_", "F", "F", "F"]   # answer key
// ["F", "F", "T", "T", "T"]   # student's solution

// ➞ True

// # Possible for student to get all questions incorrect.

// Examples
// (["B", "A", "_", "_"], ["B", "A", "C", "C"]) ➞ True
// (["A", "B", "A", "_"], ["B", "A", "C", "C"]) ➞ True
// (["A", "B", "C", "_"], ["B", "A", "C", "C"]) ➞ False
// (["B", "_"], ["C", "A"]) ➞ True
// (["B", "A"], ["C", "A"]) ➞ False
// (["B"], ["B"]) ➞ True
// (["_"], ["B"]) ➞ True


// Notes:
// Test has at least one question.
// len(key) == len(answers)

bool possibly_perfect(const std::vector<char>& key, const std::vector<char>& answers)
{
  // We iterate through both vectors, skipping the "_" characters.
  unsigned int correct = 0;
  unsigned int skipped = 0;
  for (int i = 0; i < key.size(); i++) {
    if (key[i] == '_') {
      skipped++;
      continue;
    }

    if (key[i] == answers[i]) {
      correct++;
    }
  }

  // If the number of correct answers is equal to the size of the key, then the student can score 100%.
  if (correct+skipped == key.size()) {
    return true;
  }

  // If the number of correct answers is equal to 0, then the student can score 100%.
  if (correct == 0) {
    return true;
  }

  return false;
}

// ********************************************************************************************************


// ############################### PROBLEM 4: Find the odd int [lvl 2] #############################################
//  Given an array of integers, find the one that appears an odd number of times.
//  There will always be only one integer that appears an odd number of times.
//  Examples
//  [7] should return 7, because it occurs 1 time (which is odd).
//  [0] should return 0, because it occurs 1 time (which is odd).
//  [1,1,2] should return 2, because it occurs 1 time (which is odd).
//  [0,1,0,1,0] should return 0, because it occurs 3 times (which is odd).
//  [1,2,2,3,3,3,4,3,3,3,2,2,1] should return 4, because it appears 1 time (which is odd).

int findOdd(const std::vector<int> &numbers)
{
  // We begin by creating a hash table to store the frequency of each number.
  std::unordered_map<int, int> freq;

  // Loop through the numbers and increment the frequency of each number.
  for (int i = 0; i < numbers.size(); i++) {
    freq[numbers[i]]++;
  }

  // Loop through the hash table and return the number that has an odd frequency.
  for (auto it = freq.begin(); it != freq.end(); it++) {
    if (it->second % 2 != 0) {
      return it->first;
    }
  }

  return -1;
}

// ********************************************************************************************************



// ############################### PROBLEM 5: The Vowel Code [lvl 2] #############################################
// Step 1: Create a function called encode() to replace all the lowercase vowels in 
// a given string with numbers according to the following pattern:
// a -> 1
// e -> 2
// i -> 3
// o -> 4
// u -> 5
// For example, encode("hello") would return "h2ll4". There is no need to worry about uppercase vowels in this exercise.
// Step 2: Now create a function called decode() to turn the numbers back into vowels according to the same pattern shown above.
// For example, decode("h3 th2r2") would return "hi there".
// For the sake of simplicity, you can assume that any numbers passed into the function will correspond to vowels.

std::string encode(const std::string &str) {
  // Create a new string.
  std::string newStr = "";

  // Loop through the string.
  for (int i = 0; i < str.length(); i++) {
    // Check if the character is a vowel.
    if (str[i] == 'a') {
      newStr += "1";
    } else if (str[i] == 'e') {
      newStr += "2";
    } else if (str[i] == 'i') {
      newStr += "3";
    } else if (str[i] == 'o') {
      newStr += "4";
    } else if (str[i] == 'u') {
      newStr += "5";
    } else {
      newStr += str[i];
    }
  }

  return newStr;
}

std::string decode(const std::string &str) {
  // Create a new string.
  std::string newStr = "";

  // Loop through the string.
  for (int i = 0; i < str.length(); i++) {
    // Check if the character is a number.
    if (str[i] == '1') {
      newStr += "a";
    } else if (str[i] == '2') {
      newStr += "e";
    } else if (str[i] == '3') {
      newStr += "i";
    } else if (str[i] == '4') {
      newStr += "o";
    } else if (str[i] == '5') {
      newStr += "u";
    } else {
      newStr += str[i];
    }
  }

  return newStr;
}

// ********************************************************************************************************



// ############################### PROBLEM 6: Bananas [lvl 3] #############################################
// > "What is your name" said Tim.
// "My name" said the mouse "Is Dinglemouse".
// > "What were you before the witch turned you into a mouse" said Rose.
// "I was a banana" said Dingle the mouse, "So be careful. If you see her, run away!".
// - Badjelly the Witch (12:32), Spike Milligan

// Given a string of letters a, b, n how many different ways can you make the word "banana" 
// by crossing out various letters and then reading left-to-right?
// (Use - to indicate a crossed-out letter)

// Example:

// Input
// bbananana

// Output
// b-anana--
// b-anan--a
// b-ana--na
// b-an--ana
// b-a--nana
// b---anana
// -banana--
// -banan--a
// -bana--na
// -ban--ana
// -ba--nana
// -b--anana

// Notes
// You must return all possible bananas, but the order does not matter
// The example output above is formatted for readability. Please refer to the example tests for expected format of your result.

std::unordered_set<std::string> bananas(const std::string& s) {
  // Create a set to store all possible bananas.
  std::unordered_set<std::string> bananas;

  // Create all possible bit masks.
  for (int i = 0; i < (1 << s.length()); i++) {
    // Create a new string.
    std::string newStr = "";
    std::string strippedStr = "";

    // Loop through the string.
    for (int j = 0; j < s.length(); j++) {
      // Check if the bit is set.
      if (i & (1 << j)) {
        newStr += "-";
      } else {
        newStr += s[j];
        strippedStr += s[j];
      }
    }

    // Check if the stripped string is equal to "banana".
    if (strippedStr == "banana") {
      bananas.insert(newStr);
    }
  }

  return bananas;
}

// ********************************************************************************************************
