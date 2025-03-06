#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <algorithm>

using namespace std;

// Định nghĩa lớp Student
class Student {
public:
    string fullName;
    double PT1, PT2, PT3, Lab1, Lab2, Pres1, Pres2, FE, FR; // Điểm

    void computeFinalResult(); // Tính điểm cuối cùng
    void display() const; // Hiển thị thông tin
    void exportToCSV(ofstream& file) const; // Xuất thông tin ra CSV
};

// Tính điểm cuối cùng theo trọng số
void Student::computeFinalResult() {
    FR = ((PT1 + PT2 + PT3) / 3) * 0.3 + ((Lab1 + Lab2) / 2) * 0.2 + ((Pres1 + Pres2) / 2) * 0.1 + FE * 0.4;
}

// Hiển thị thông tin sinh viên theo bảng
void Student::display() const {
    cout << left << setw(20) << fullName
         << setw(5) << PT1 << setw(5) << PT2 << setw(5) << PT3
         << setw(5) << Lab1 << setw(5) << Lab2
         << setw(5) << Pres1 << setw(5) << Pres2
         << setw(5) << FE << setw(8) << FR << endl;
}

// Xuất thông tin sinh viên ra file CSV
void Student::exportToCSV(ofstream& file) const {
    file << fullName << "," << PT1 << "," << PT2 << "," << PT3 << ","
         << Lab1 << "," << Lab2 << "," << Pres1 << "," << Pres2 << ","
         << FE << "," << FR << endl;
}

// Hiển thị tiêu đề bảng
void displayTableHeader() {
    cout << "\n================= DANH SACH SINH VIEN =================\n";
    cout << left << setw(20) << "Ho Ten"
         << setw(5) << "PT1" << setw(5) << "PT2" << setw(5) << "PT3"
         << setw(5) << "L1" << setw(5) << "L2"
         << setw(5) << "P1" << setw(5) << "P2"
         << setw(5) << "FE" << setw(8) << "Final" << endl;
    cout << "------------------------------------------------------\n";
}

// Nhập danh sách sinh viên theo từng dòng
void inputStudents(vector<Student>& students, int n) {
    for (int i = 0; i < n; i++) {
        Student s;
        cin.ignore();
        
        cout << "\n=== Nhap thong tin cho sinh vien " << i + 1 << " ===\n";
        cout << "Ho ten: ";
        getline(cin, s.fullName);

        cout << "PT1: "; cin >> s.PT1;
        cout << "PT2: "; cin >> s.PT2;
        cout << "PT3: "; cin >> s.PT3;
        cout << "Lab1: "; cin >> s.Lab1;
        cout << "Lab2: "; cin >> s.Lab2;
        cout << "Pres1: "; cin >> s.Pres1;
        cout << "Pres2: "; cin >> s.Pres2;
        cout << "Final Exam: "; cin >> s.FE;
        
        students.push_back(s);
    }
}

// Tính điểm cho tất cả sinh viên
void computeResults(vector<Student>& students) {
    for (auto& student : students) {
        student.computeFinalResult();
    }
}

// Sắp xếp danh sách sinh viên theo điểm giảm dần
void sortStudents(vector<Student>& students) {
    sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.FR > b.FR;
    });
}

// Hiển thị danh sách sinh viên theo bảng
void displayStudents(const vector<Student>& students) {
    displayTableHeader();
    for (const auto& student : students) {
        student.display();
    }
}

// Xuất danh sách sinh viên ra file CSV
void exportToExcel(const vector<Student>& students) {
    ofstream file("students.csv");
    if (!file) {
        cout << "Loi khi mo file!\n";
        return;
    }
    file << "Full Name,PT1,PT2,PT3,Lab1,Lab2,Pres1,Pres2,FE,Final Score\n";
    for (const auto& student : students) {
        student.exportToCSV(file);
    }
    file.close();
    cout << "✅ Da xuat danh sach sinh vien ra file 'students.csv'!\n";
}

int main() {
    int n;
    cout << "Nhap so luong sinh vien: ";
    cin >> n;

    vector<Student> students;
    inputStudents(students, n);
    computeResults(students);
    sortStudents(students);
    displayStudents(students);

    // Hỏi người dùng có muốn xuất ra file Excel không?
    char choice;
    cout << "\nBan co muon xuat danh sach ra file Excel (y/n)? ";
    cin >> choice;
    
    if (choice == 'y' || choice == 'Y') {
        exportToExcel(students);
    } else {
        cout << "❌ Khong xuat file.\n";
    }

    cout << "Nhan phim Enter de thoat...";
    cin.ignore();
    cin.get();
    
    return 0;
}
