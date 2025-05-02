#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <cctype>
#include <algorithm>
#include <unordered_set>

using namespace std;

// Helper function to trim punctuation from beginning and end
string trimPunctuation(const string& word) {
    size_t start = 0, end = word.size();
    while (start < end && ispunct(word[start])) ++start;
    while (end > start && ispunct(word[end - 1])) --end;
    return word.substr(start, end - start);
}

// Capitalize first letter of each sentence
string capitalizeSentences(string text) {
    bool capitalizeNext = true;
    for (size_t i = 0; i < text.length(); ++i) {
        if (capitalizeNext && isalpha(text[i])) {
            text[i] = toupper(text[i]);
            capitalizeNext = false;
        }
        if (text[i] == '.' || text[i] == '!' || text[i] == '?') {
            capitalizeNext = true;
        }
    }
    return text;
}

int main() {
    cout << "TEXT MESSAGE ANALYZER\n---------------------\n";
    cout << "Enter your message: ";

    string message;
    getline(cin, message);

    int totalChars = 0;
    int sentenceCount = 0;
    int wordCount = 0;
    int totalWordLength = 0;
    vector<string> longWords;
    unordered_set<string> emojis = {":)", ":(", ":D", ":P"};
    unordered_set<string> foundEmojis;
    unordered_set<string> textSpeak = {"LOL", "BRB", "OMG", "BTW", "IMHO"};
    unordered_set<string> foundTextSpeak;

    // Count characters excluding spaces
    for (char c : message) {
        if (!isspace(c)) {
            ++totalChars;
        }
        if (c == '.' || c == '!' || c == '?') {
            ++sentenceCount;
        }
    }

    stringstream ss(message);
    string word;
    while (ss >> word) {
        ++wordCount;

        string trimmed = trimPunctuation(word);
        totalWordLength += trimmed.length();

        // Emoji check
        if (emojis.count(trimmed)) {
            foundEmojis.insert(trimmed);
        }

        // Text speak check
        string upperWord = trimmed;
        transform(upperWord.begin(), upperWord.end(), upperWord.begin(), ::toupper);
        if (textSpeak.count(upperWord)) {
            foundTextSpeak.insert(upperWord);
        }

        if (trimmed.length() > 5) {
            longWords.push_back(trimmed);
        }
    }

    double averageLength = wordCount > 0 ? (double)totalWordLength / wordCount : 0.0;

    // Display output
    cout << "\nMessage Analysis:\n";
    cout << "Total characters: " << totalChars << '\n';
    cout << "Word count: " << wordCount << '\n';
    cout << "Sentence count: " << sentenceCount << '\n';
    cout << fixed << setprecision(1);
    cout << "Average word length: " << averageLength << " characters\n";
    cout << "Contains emoji: " << (foundEmojis.empty() ? "No" : "Yes") << "\n";

    if (!longWords.empty()) {
        cout << "\nWords longer than 5 characters:\n";
        for (const string& w : longWords) {
            cout << "- " << w << '\n';
        }
    }

    if (!foundTextSpeak.empty()) {
        cout << "\nText Speak Abbreviations Found (" << foundTextSpeak.size() << "):\n";
        for (const string& abbr : foundTextSpeak) {
            cout << "- " << abbr << '\n';
        }
    }

    cout << "\nProperly capitalized message:\n";
    cout << capitalizeSentences(message) << "\n";

    return 0;
}
