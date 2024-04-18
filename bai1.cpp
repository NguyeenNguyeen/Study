#include <iostream>

using namespace std;

struct Student
{
    char MSSV [10];
    char hoTen [30];
    double gpa ;
};


Student inputStudents()
{
    Student student;
    cout << "Enter student's ID: ";
    cin >> student.MSSV;
    cin.ignore(1);
    cout << "Enter student's name: ";
    cin.getline(student.hoTen, 30);
    cout << "Enter student's GPA: ";
    cin >> student.gpa;
    return student;
}


//1

Student * inputStudentList ( int & n ) 
{
    n = 0;
    cout << "The number of students: ";
    cin >> n;
    Student* student = nullptr;
    student = new Student[n];
    for (int i = 0; i < n; i++)
    {
        cout << "\nEnter details for student " << i+1 << endl;
        student[i] = inputStudents();
    }
    return student;
}


//2

void writeStudentList ( const char * fileName, Student* studentList, int n ) 
{
    FILE* fp = nullptr;
    fp = fopen(fileName, "wb");
    if(!fp)
    {
        cout << "Can not open file";
        return;
    }

    size_t n_size = fwrite(&n, sizeof(int), 1, fp);
    if (n_size > 0)
    {
        cout << "\nWriting successfully\n";
    }
    else
    {
        cout << "Error writing file";
        fclose(fp);
        fp = nullptr;
        return;
    }

    size_t s_size = fwrite(studentList, sizeof(*studentList), n, fp);
    if (s_size > 0)
    {
        cout << "\nWRITING successfully\n";
    }
    else
    {
        cout << "ERROR writing file";
        fclose(fp);
        fp = nullptr;
        return;
    }

    fclose(fp);
    fp = nullptr;
}


//3

Student * readStudentListFromFile ( const char * fileName)
{
    Student* studentList = nullptr;
    FILE* fp = nullptr;
    fp = fopen(fileName, "rb");
    if (!fp)
    {
        cout << "Can not open file";
        return nullptr;
    }

    int n = 0;
    size_t n_size = fread(&n, sizeof(int), 1, fp);
    if (n_size > 0)
    {
        cout << "\nReading successfully\n";
    }
    else
    {
        cout << "Error reading file";
        fclose(fp);
        fp = nullptr;
        return nullptr;
    }

    studentList = new Student[n];
    size_t s_size = fread(studentList, sizeof(*studentList), n, fp);
    if (s_size > 0)
    {
        cout << "\nREADING successfully\n";
    }
    else
    {
        cout << "ERROR reading file";
        fclose(fp);
        fp = nullptr;
        return nullptr;
    }

    fclose(fp);
    fp = nullptr;
    return studentList;
}


//4

void swap(Student* a, Student* b)
{
    Student* temp = nullptr;
    *temp = *a;
    *a = *b;
    *b = *a;
}

void sortStudentList ( Student *& studentList , int n ) 
{
    for (int k = 0; k < n - 1; k++)
    {
        for (int i = k + 1; i < n; i++)
        {
            if (studentList[i].gpa > studentList[k].gpa)
            {
                swap(studentList[i], studentList[k]);
            }
        }
    }
}


//5

void writeBestStudentList ( const char * bestStudentFile , Student * studentList , int n , int k )
{
    FILE* fp = nullptr;
    fp = fopen(bestStudentFile, "wb");
    if(!fp)
    {
        cout << "Can not open file";
        return;
    }

    if (k > n)
    {
        cout << "The number of students is less than that which is required";
        k = n;
    }

    size_t n_size = fwrite(&k, sizeof(int), 1, fp);
    if (n_size > 0)
    {
        cout << "Writing successfully";
    }
    else
    {
        cout << "Error writing file";
        fclose(fp);
        fp = nullptr;
        return;
    }
    
    sortStudentList(studentList, n);

    size_t s_size = fwrite(studentList, sizeof(*studentList), k, fp);
    if (s_size > 0)
    {
        cout << "WRITING successfully";
    }
    else
    {
        cout << "ERROR writing file";
        fclose(fp);
        fp = nullptr;
    }

    fclose(fp);
    fp = nullptr;
}



int main()
{
    int n = 0;
    Student* studentList = nullptr;
    const char* fileName = "fileStudent.bin";
    
    //1: studentList = inputStudentList(n);    
    
    //2: writeStudentList(fileName, studentList, n);

    //3: studentList = readStudentListFromFile(fileName);

    //4, 5:
    // int k = 0;
    // cout << "The number of best students that you want to write into the file: ";
    // cin >> k;

    // writeBestStudentList("bestStudent.bin", studentList, n, k);

    // delete[] studentList;
    // studentList = nullptr;

    return 0;
}