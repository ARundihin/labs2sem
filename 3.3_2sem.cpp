#include <iostream>
#include <fstream>
using namespace std;

const int M = 80;

struct Student
{
    char name[M];
    int age;
    int course;
    int performance;
};

void read(Student& stud)
{
    cout << "FIO = ";
    cin.getline(stud.name, M);
    cout << "Age = ";
    cin >> stud.age;
    cin.get();
    cout << "Course = ";
    cin >> stud.course;
    cin.get();
    cout << "Performance = ";
    cin >> stud.performance;
    cin.get();
    cout << endl;
}

void printStudent(Student stud)
{
    cout << "FIO = " << stud.name << endl;
    cout << "Age = " << stud.age << endl;
    cout << "Course = " << stud.course << endl;
    cout << "Performance = " << stud.performance << endl;
}

void createDB(ofstream& file) {
    Student stud;

    int amountOfStudents;
    cout << "Enter amount of students: " << endl;
    cin >> amountOfStudents;
    cin.ignore();
    cout << endl;

    for (int i = 0; i < amountOfStudents; i++) {
        read(stud);
        file.write(reinterpret_cast<char*>(&stud), sizeof(Student));
        cout << endl;
    }
}

void print(ifstream& file) {
    Student stud;

    while (file.read(reinterpret_cast<char*>(&stud), sizeof(Student)))
    {
        printStudent(stud);
        cout << endl;
    }
}

void findTopStudents(ifstream& inFile, ofstream& outFile, int selectCourse)
{
    Student stud;

    cout << "Top students in course " << selectCourse << ":" << endl;

    while (inFile.read(reinterpret_cast<char*>(&stud), sizeof(Student))) {
        if (stud.course == selectCourse && stud.performance == 5) {
            outFile.write(reinterpret_cast<char*>(&stud), sizeof(Student));
        }
    }
}

int main()
{
    ofstream write_f;
    write_f.open("DB.bin", ios::binary);

    if (!write_f.is_open())
    {
        cout << "Sorry, there some troubles with opening DB.bin for writing\n";
        return 0;
    }

    createDB(write_f);

    write_f.close();

    /*ifstream read_fin;
    read_fin.open("DB.bin", ios::binary);

    if (!read_fin.is_open())
    {
        cout << "Sorry, there some troubles with opening DB.bin for writing\n";
        return 0;
    }

    print(read_fin);

    read_fin.close();*/

    ifstream read_f;
    read_f.open("DB.bin", ios::binary);

    if (!read_f.is_open())
    {
        cout << "Sorry, there some troubles with opening DB.bin for writing\n";
        return 0;
    }

    ofstream write_fout;
    write_fout.open("fout.bin", ios::binary);

    if (!write_fout.is_open())
    {
        cout << "Sorry, there some troubles with opening fout.bin for writing\n";
        return 0;
    }

    int selectCourse;

    cout << "=======================" << endl;
    cout << "Choose course" << endl
        << "1. first" << endl
        << "2. second" << endl
        << "3. third" << endl
        << "4. fourth" << endl;
    cin >> selectCourse;

    findTopStudents(read_f, write_fout, selectCourse);

    read_f.close();
    write_fout.close();

    ifstream read_fout;
    read_fout.open("fout.bin", ios::binary);

    if (!read_fout.is_open())
    {
        cout << "Sorry, there some troubles with opening fout.bin for writing\n";
        return 0;
    }

    print(read_fout);

    read_fout.close();

    return 0;
}
