#include <iostream>
#include <string>
#include <vector>
#include <iomanip> // For std::setprecision

struct Address {
    std::string street;
    std::string city;
    std::string state;
    std::string zip;
};

struct Person {
    std::string name;
    int age;
    Address address;
};

struct Course {
    std::string code;
    std::string name;
    int creditHours;
};

struct Student {
    Person person;
    int id;
    Course courses[5];
    double gpa;
};

// Function to initialize sample data
std::vector<Student> initializeSampleStudents() {
    std::vector<Student> students;

    students.push_back({
        {"Maria Rodriguez", 20, {"123 College Ave", "Berkeley", "CA", "94704"}},
        1001,
        {
            {"CS101", "Introduction to Programming", 3},
            {"MATH201", "Calculus II", 4},
            {"PHYS101", "Physics I", 4},
            {"ENG105", "English Composition", 3},
            {"HIST100", "World History", 3}
        },
        3.85
    });

    students.push_back({
        {"James Smith", 19, {"456 University Dr", "Berkeley", "CA", "94704"}},
        1002,
        {
            {"CS101", "Introduction to Programming", 3},
            {"MATH101", "Calculus I", 4},
            {"CHEM101", "Chemistry I", 4},
            {"SOC200", "Introduction to Sociology", 3},
            {"ART105", "Drawing Fundamentals", 2}
        },
        3.42
    });

    students.push_back({
        {"Sarah Johnson", 21, {"789 Campus Rd", "Berkeley", "CA", "94704"}},
        1003,
        {
            {"CS201", "Data Structures", 3},
            {"MATH201", "Calculus II", 4},
            {"BIO101", "Biology I", 4},
            {"PSYCH101", "Introduction to Psychology", 3},
            {"ECON200", "Microeconomics", 3}
        },
        3.91
    });

    return students;
}

// Function to display all students
void displayAllStudents(const std::vector<Student>& students) {
    std::cout << "\nStudent Information:\n";
    for (const auto& s : students) {
        std::cout << "\nID: " << s.id << " - " << s.person.name << "\n";
        std::cout << "Age: " << s.person.age << "\n";
        std::cout << "Address: " << s.person.address.street << ", "
                  << s.person.address.city << ", "
                  << s.person.address.state << " "
                  << s.person.address.zip << "\n";
        std::cout << "GPA: " << std::fixed << std::setprecision(2) << s.gpa << "\n";
        std::cout << "Courses:\n";
        for (const auto& c : s.courses) {
            std::cout << "  " << c.code << ": " << c.name
                      << " (" << c.creditHours << " credits)\n";
        }
    }
}

// Function to find student by ID
void findStudentByID(const std::vector<Student>& students, int id) {
    bool found = false;
    for (const auto& s : students) {
        if (s.id == id) {
            std::cout << "Student found:\n";
            std::cout << "  " << s.person.name << " (ID: " << s.id << ")\n";
            std::cout << "  GPA: " << std::fixed << std::setprecision(2) << s.gpa << "\n";
            found = true;
            break;
        }
    }
    if (!found) {
        std::cout << "Student with ID " << id << " not found.\n";
    }
}

// Function to calculate average GPA
void calculateAverageGPA(const std::vector<Student>& students) {
    if (students.empty()) {
        std::cout << "No students to calculate GPA.\n";
        return;
    }
    double totalGPA = 0;
    for (const auto& s : students) {
        totalGPA += s.gpa;
    }
    double avg = totalGPA / students.size();
    std::cout << "Average GPA: " << std::fixed << std::setprecision(2) << avg << "\n";
}

// Function to list students by course code
void listStudentsByCourse(const std::vector<Student>& students, const std::string& courseCode) {
    bool found = false;
    std::cout << "Students taking " << courseCode << ":\n";
    for (const auto& s : students) {
        for (const auto& c : s.courses) {
            if (c.code == courseCode) {
                std::cout << "  " << s.person.name << " (ID: " << s.id << ")\n";
                found = true;
                break;
            }
        }
    }
    if (!found) {
        std::cout << "  No students found for that course.\n";
    }
}

void enrollInNewCourse(std::vector<Student>& students) {
    int id;
    std::cout << "\nEnter student ID to enroll in a new course: ";
    std::cin >> id;

    for (auto& s : students) {
        if (s.id == id) {
            std::cout << "Student found: " << s.person.name << "\n";

            std::string code, name;
            int credits;

            std::cout << "Enter new course code: ";
            std::cin >> code;
            std::cin.ignore(); // clear newline for getline
            std::cout << "Enter course name: ";
            std::getline(std::cin, name);
            std::cout << "Enter credit hours: ";
            std::cin >> credits;

            // Replace last course with the new one
            s.courses[4] = {code, name, credits};

            std::cout << "New course enrolled successfully! (Note: Replaces 5th course slot)\n";
            return;
        }
    }

    std::cout << "Student with ID " << id << " not found.\n";
}


// MAIN MENU
int main() {
    std::vector<Student> students = initializeSampleStudents();

    int choice;
    do {
        std::cout << "\nSCHOOL MANAGEMENT SYSTEM\n";
        std::cout << "------------------------\n";
        std::cout << "1. Display all student information\n";
        std::cout << "2. Find student by ID\n";
        std::cout << "3. Calculate average GPA\n";
        std::cout << "4. List students by course code\n";
        std::cout << "5. Enroll a student in a new course\n";
        std::cout << "6. Exit\n";
        std::cout << "------------------------\n";
        std::cout << "Enter your choice (1-6): ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                displayAllStudents(students);
                break;
            case 2: {
                int id;
                std::cout << "Enter student ID to search: ";
                std::cin >> id;
                findStudentByID(students, id);
                break;
            }
            case 3:
                calculateAverageGPA(students);
                break;
            case 4: {
                std::string code;
                std::cout << "Enter course code to search for: ";
                std::cin >> code;
                listStudentsByCourse(students, code);
                break;
            }
            case 5: {
            enrollInNewCourse(students);
            break;
            }
            case 6:
                std::cout << "Goodbye!\n";
                break;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 6);

    return 0;
}
