#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <sstream>
#include <vector>

using namespace std;

const string JOURNAL_FILE = "journal.txt";
const string ENTRY_SEPARATOR = "----------------------------------------";

string getCurrentTimestamp() {
    time_t now = time(nullptr);
    tm* localTime = localtime(&now);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localTime);
    return string(buffer);
}

void addEntry() {
    ofstream outFile(JOURNAL_FILE, ios::app);
    if (!outFile) {
        cerr << "Error: Unable to open the journal file for writing.\n";
        return;
    }

    cout << "\nADD NEW JOURNAL ENTRY\n--------------------\n";
    cout << "Enter your journal entry (press Enter twice to finish):\n";

    string line, entryText;
    cin.ignore(); // Clear input buffer
    while (true) {
        getline(cin, line);
        if (line.empty()) break;
        entryText += line + "\n";
    }

    if (entryText.empty()) {
        cout << "Empty entry discarded.\n";
        return;
    }

    outFile << "Entry Date: " << getCurrentTimestamp() << "\n";
    outFile << entryText;
    outFile << ENTRY_SEPARATOR << "\n";

    outFile.close();
    cout << "Entry saved successfully!\n";
}

void viewEntries() {
    ifstream inFile(JOURNAL_FILE);
    if (!inFile) {
        cerr << "Error: Unable to open the journal file for reading.\n";
        return;
    }

    cout << "\nJOURNAL ENTRIES\n---------------\n";
    string line;
    bool empty = true;
    while (getline(inFile, line)) {
        empty = false;
        cout << line << endl;
    }

    if (empty) {
        cout << "No entries found.\n";
    }

    inFile.close();
}

void searchEntries() {
    ifstream inFile(JOURNAL_FILE);
    if (!inFile) {
        cerr << "Error: Unable to open the journal file for reading.\n";
        return;
    }

    cout << "\nSEARCH JOURNAL ENTRIES\n----------------------\n";
    cout << "Enter search keyword: ";
    string keyword;
    cin.ignore();
    getline(cin, keyword);

    string line, entry;
    bool found = false;
    vector<string> matchingEntries;

    while (getline(inFile, line)) {
        if (line == ENTRY_SEPARATOR) {
            if (entry.find(keyword) != string::npos) {
                matchingEntries.push_back(entry);
                found = true;
            }
            entry.clear();
        } else {
            entry += line + "\n";
        }
    }

    if (!entry.empty() && entry.find(keyword) != string::npos) {
        matchingEntries.push_back(entry);
        found = true;
    }

    if (found) {
        cout << "Found " << matchingEntries.size() << " matching entr"
             << (matchingEntries.size() > 1 ? "ies" : "y") << ":\n\n";
        for (const auto& e : matchingEntries) {
            cout << e << ENTRY_SEPARATOR << "\n";
        }
    } else {
        cout << "No matching entries found.\n";
    }

    inFile.close();
}

void showMenu() {
    cout << "\nPERSONAL JOURNAL SYSTEM\n-----------------------\n";
    cout << "1. Add New Entry\n";
    cout << "2. View All Entries\n";
    cout << "3. Search Entries\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    int choice;
    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                addEntry();
                break;
            case 2:
                viewEntries();
                break;
            case 3:
                searchEntries();
                break;
            case 4:
                cout << "Exiting journal system. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 4);

    return 0;
}
