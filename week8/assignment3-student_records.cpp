#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <limits>
#include <algorithm>

using namespace std;

struct Course {
    string name;
    int grade;
};

struct Student {
    string id;
    string firstName;
    string lastName;
    vector<Course> courses;
    double gpa;
};

double convertGradeToGPA(int grade) {
    if (grade >= 90) return 4.0;
    if (grade >= 80) return 3.0;
    if (grade >= 70) return 2.0;
    if (grade >= 60) return 1.0;
    return 0.0;
}

void processFile(const string& inputFileName, const string& outputFileName) {
    ifstream inFile(inputFileName);
    ofstream outFile(outputFileName);

    if (!inFile) {
        cerr << "Error: Cannot open input file.\n";
        return;
    }

    if (!outFile) {
        cerr << "Error: Cannot open output file.\n";
        return;
    }

    cout << "STUDENT ACADEMIC RECORD PROCESSOR\n---------------------------------\n";
    cout << "Reading student records from input file...\n\n";
    vector<Student> students;
    string line;
    int lineNumber = 0;

    while (getline(inFile, line)) {
        lineNumber++;
        if (line.empty() || line[0] == '#') continue;

        stringstream ss(line);
        Student student;
        ss >> student.id >> student.firstName >> student.lastName;
        if (student.id.empty() || student.firstName.empty() || student.lastName.empty()) {
            cerr << "Line " << lineNumber << " Error: Missing ID or name.\n";
            continue;
        }

        string courseData;
        while (ss >> courseData) {
            size_t pos = courseData.find(':');
            if (pos == string::npos) {
                cerr << "Line " << lineNumber << " Error: Invalid course format.\n";
                continue;
            }

            string courseName = courseData.substr(0, pos);
            int grade;
            try {
                grade = stoi(courseData.substr(pos + 1));
            } catch (...) {
                cerr << "Line " << lineNumber << " Error: Invalid grade format.\n";
                continue;
            }

            if (grade < 0 || grade > 100) {
                cerr << "Line " << lineNumber << " Error: Grade out of range (0-100).\n";
                continue;
            }

            student.courses.push_back({courseName, grade});
        }

        if (student.courses.empty()) {
            cerr << "Line " << lineNumber << " Error: No valid courses for student.\n";
            continue;
        }

        // Calculate GPA
        double totalGPA = 0.0;
        for (const Course& c : student.courses) {
            totalGPA += convertGradeToGPA(c.grade);
        }
        student.gpa = totalGPA / student.courses.size();
        students.push_back(student);
    }

    // Sort students by ID for consistent output
    sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.id < b.id;
    });

    cout << "STUDENT GRADE REPORT\n-------------------\n";
    cout << left << setw(8) << "ID" << setw(20) << "Name"
         << setw(17) << "Courses Taken" << setw(5) << "GPA" << endl;
    cout << "-----   ----------------   -------------    ----\n";

    double totalGPA = 0.0;
    int totalCourses = 0;
    Student* highest = nullptr;
    Student* lowest = nullptr;

    for (const Student& student : students) {
        string name = student.firstName + " " + student.lastName;
        cout << left << setw(8) << student.id
             << setw(20) << name
             << setw(17) << student.courses.size()
             << fixed << setprecision(2) << student.gpa << endl;

        totalGPA += student.gpa;
        totalCourses += student.courses.size();

        if (!highest || student.gpa > highest->gpa) highest = const_cast<Student*>(&student);
        if (!lowest || student.gpa < lowest->gpa) lowest = const_cast<Student*>(&student);
    }

    double averageGPA = students.empty() ? 0.0 : totalGPA / students.size();

    cout << "\nCLASS STATISTICS\n----------------\n";
    cout << "Total Students: " << students.size() << endl;
    cout << "Total Courses Taken: " << totalCourses << endl;
    cout << "Class Average GPA: " << fixed << setprecision(2) << averageGPA << endl;

    if (highest)
        cout << "\nHighest GPA: " << highest->firstName << " " << highest->lastName
             << " (" << fixed << setprecision(2) << highest->gpa << ")\n";
    if (lowest)
        cout << "Lowest GPA: " << lowest->firstName << " " << lowest->lastName
             << " (" << fixed << setprecision(2) << lowest->gpa << ")\n";

    // Write summary report to file
    outFile << "Summary Report\n==============\n";
    outFile << "Total Students: " << students.size() << endl;
    outFile << "Total Courses Taken: " << totalCourses << endl;
    outFile << "Class Average GPA: " << fixed << setprecision(2) << averageGPA << endl;
    if (highest)
        outFile << "Highest GPA: " << highest->firstName << " " << highest->lastName
                << " (" << highest->gpa << ")\n";
    if (lowest)
        outFile << "Lowest GPA: " << lowest->firstName << " " << lowest->lastName
                << " (" << lowest->gpa << ")\n";

    cout << "\nSummary report written to output file successfully.\n";

    inFile.close();
    outFile.close();
}

int main() {
    string inputFileName = "student_records.txt";
    string outputFileName = "summary_report.txt";

    processFile(inputFileName, outputFileName);
    return 0;
}
