#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
using namespace std;

// Student class
class Student {
private:
    string name;
    int ID;
    double GPA;

public:
    // Constructor
    Student(string studentName, int studentID, double studentGPA)
        : name(studentName), ID(studentID), GPA(studentGPA) {}

    // Getters
    string getName() const { return name; }
    int getID() const { return ID; }
    double getGPA() const { return GPA; }

    // Update GPA with validation
    bool updateGPA(double newGPA) {
        if (newGPA >= 0.0 && newGPA <= 4.0) {
            GPA = newGPA;
            return true;
        }
        return false;
    }

    // Display student info
    void displayInfo() const {
        cout << "ID: " << ID << " - " << name << endl;
        cout << fixed << setprecision(2) << "GPA: " << GPA << "\n";
    }
};

// Course class
class Course {
private:
    string code;
    string title;
    int creditHours;

public:
    // Constructor
    Course(string courseCode, string courseTitle, int courseCredits)
        : code(courseCode), title(courseTitle), creditHours(courseCredits) {}

    // Getters
    string getCode() const { return code; }
    string getTitle() const { return title; }
    int getCreditHours() const { return creditHours; }

    // Display course info
    void displayInfo() const {
        cout << code << ": " << title << " (" << creditHours << " credits)\n";
    }
};

int main() {
    vector<Student> students = {
        {"Alex Johnson", 1001, 3.75},
        {"Maria Garcia", 1002, 3.92},
        {"Jamal Williams", 1003, 3.45}
    };

    vector<Course> courses = {
        {"CS101", "Introduction to Programming", 3},
        {"MATH201", "Calculus II", 4}
    };

    int choice;
    do {
        cout << "\n=== UNIVERSITY MANAGEMENT SYSTEM ===\n";
        cout << "1. Display all students\n";
        cout << "2. Display all courses\n";
        cout << "3. Update a student's GPA\n";
        cout << "4. Exit\n";
        cout << "Select an option (1-4): ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "\nStudent Information:\n";
                for (const auto& s : students) {
                    s.displayInfo();
                    cout << endl;
                }
                break;

            case 2:
                cout << "\nCourse Information:\n";
                for (const auto& c : courses) {
                    c.displayInfo();
                }
                break;

            case 3: {
                int id;
                double newGPA;
                cout << "\nEnter the student ID to update GPA: ";
                cin >> id;
                bool found = false;
                for (auto& s : students) {
                    if (s.getID() == id) {
                        cout << "Enter new GPA (0.0 - 4.0): ";
                        cin >> newGPA;
                        if (s.updateGPA(newGPA)) {
                            cout << "GPA updated successfully.\n";
                            cout << "Updated Information:\n";
                            s.displayInfo();
                        } else {
                            cout << "Invalid GPA. Must be between 0.0 and 4.0.\n";
                        }
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << "Student ID not found.\n";
                }
                break;
            }

            case 4:
                cout << "Exiting program. Goodbye!\n";
                break;

            default:
                cout << "Invalid choice. Please select 1-4.\n";
        }
    } while (choice != 4);

    return 0;
}
