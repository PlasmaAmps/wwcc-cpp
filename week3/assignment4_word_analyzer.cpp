#include <iostream>
#include <string>
#include <cctype>
using namespace std;

// Function to count vowels
int countVowels(string word) {
    int count = 0;
    for (char c : word) {
        c = tolower(c);
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            count++;
        }
    }
    return count;
}

// Function to count consonants
int countConsonants(string word) {
    int count = 0;
    for (char c : word) {
        if (isalpha(c)) {
            c = tolower(c);
            if (!(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')) {
                count++;
            }
        }
    }
    return count;
}

// Function to check if the word is a palindrome
bool isPalindrome(string word) {
    int left = 0;
    int right = word.length() - 1;
    while (left < right) {
        char l = tolower(word[left]);
        char r = tolower(word[right]);
        if (l != r) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}

// Function to get the first letter
char firstLetter(string word) {
    if (word.empty()) {
        return '\0'; // Return null character if string is empty
    }
    return word[0];
}

// Function to reverse the word
string reverse(string word) {
    string reversed = "";
    for (int i = word.length() - 1; i >= 0; i--) {
        reversed += word[i];
    }
    return reversed;
}

// (Bonus) Function to get formatted stats
string getStats(string word) {
    int vowels = countVowels(word);
    int consonants = countConsonants(word);
    bool palindrome = isPalindrome(word);
    int characters = word.length();

    string result = "STATS: " + word + " has " + to_string(characters) + " characters, "
                    + to_string(vowels) + " vowels, "
                    + to_string(consonants) + " consonants, and "
                    + (palindrome ? "is" : "is not") + " a palindrome.";
    return result;
}

int main() {
    string word;
    char choice;

    do {
        cout << "Enter a word: ";
        cin >> word;

        cout << endl;
        cout << "Word Analysis:\n";
        cout << "-------------\n";
        cout << "Original word: " << word << endl;
        cout << "Number of vowels: " << countVowels(word) << endl;
        cout << "Number of consonants: " << countConsonants(word) << endl;
        
        char first = firstLetter(word);
        if (first != '\0') {
            cout << "First letter: " << first << endl;
        } else {
            cout << "First letter: (none - empty word)\n";
        }

        cout << "Reversed: " << reverse(word) << endl;
        cout << "Is palindrome: " << (isPalindrome(word) ? "Yes" : "No") << endl;

        // Bonus output
        cout << getStats(word) << endl;

        cout << endl;
        cout << "Would you like to analyze another word? (y/n): ";
        cin >> choice;
        cout << endl;

    } while (tolower(choice) == 'y');

    cout << "Goodbye and thank you for reading this sentence!\n";

    return 0;
}
