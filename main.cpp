// Mariam Barakat,Haya Abusaq, Fatima Faiz, , , ,  احذفو هالكلام واكتبوا اساميكم
// Group 2, Class F06
//  IT IS WORKING TILL NOW 1: 27 pm
#include <ctime>
#include <fstream>
#include <iostream>
using namespace std;

// strucutre for student information
struct StudentInfo {
  string fullname, major, phone;
  char gender;
  int age;
  long int ID;
  double grades[5];
  string course[5] = {"CS222", "CS221", "BIO01", "STAT07", "CIS111"};
  double gpa, pGPA;
};
// two overloading functions prototype for GPA calculator
// + function prototype for phoneChecker
// string resetTime();
double GPAs(double[], int);
double GPAs(double[], int, double);
bool phoneChecker(string &);
void allSmall(string &);
long int idPrinter(int);
// void printInfo(StudentInfo,int);
// functions for the adding the user

string validateLettersOnlyInput(const string &prompt);

int main() {

  ifstream InfoFile;
  ofstream InfoFileOut, statFile;
  statFile.open("HEREALL/StaticalReport.txt", ios::out);
  InfoFile.open("HEREALL/InfoFile.txt", ios::in);
  time_t currentTime = time(nullptr);
  string timeString = ctime(&currentTime);
  int count = 3, SearchID;
  const int numStudents = 100;
  StudentInfo students[numStudents];
  StudentInfo temp[1];
  char option;
  bool studentFound = false;
  int numGrades = 5;

  cout << "[ Welcome to our program Students info. And GPA calculator !! ]\n"
       << endl;

  if (statFile.is_open()) {
    currentTime = time(nullptr);
    timeString = ctime(&currentTime);
    statFile << "The file opened at: " << timeString << endl;
  } else {
    cout << "File is not open" << endl;
  }
  /*This is the main loop of the program, which displays a menu of options for
   * managing student information and GPA calculation. The user can choose from
   * various options. The loop continues until the user chooses to exit.*/
  if (InfoFile.is_open()) {
    for (int n = 0; n < count; n++) {

      getline(InfoFile, students[n].fullname, ',');
      InfoFile >> students[n].gender;
      InfoFile.ignore(1);
      InfoFile >> students[n].age;
      InfoFile.ignore(1);
      getline(InfoFile, students[n].major, ',');
      for (int i = 0; i < 5; i++) {
        InfoFile >> students[n].grades[i];
        InfoFile.ignore(1);
      }

      students[n].gpa = GPAs(students[n].grades, numGrades);
      getline(InfoFile, students[n].phone, ',');
      InfoFile >> students[n].ID;
      // InfoFile.ignore(100,'\n');
    }
    InfoFile.close();
  } else {
    cout << "File not found" << endl;
  }

  while (true) {

    cout << "\n*   Choose one of the options below   * "
            "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n";
    cout << "~  1.  Adding a new student             ~" << endl;
    cout << "~  2.  Search for a specific student    ~" << endl;
    cout << "~  3.  Update existing student          ~" << endl;
    cout << "~  4.  Delete a student                 ~" << endl;
    cout << "~  5.  Sort students                    ~" << endl;
    cout << "~  6.  Display all students             ~" << endl;
    cout << "~  7.  Exit                             "
            "~\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
         << endl;

    cout << "Choose one of the options below: ";
    cin >> option;
    currentTime = time(nullptr);
    timeString = ctime(&currentTime);
    statFile << "The user choose: " << option << " at :" << timeString << endl;

    switch (option) {
    case '1': {
      cout << "|1. Adding a student | " << endl;
      // Read and ignore remaining newline character
      cin.ignore();

      cout << "Enter full name: ";
      getline(cin, students[count].fullname);

      cout << "Enter your age: ";
      cin >> students[count].age;

      students[count].major =
          validateLettersOnlyInput("Enter major (letters only): ");
      students[count].gender = validateLettersOnlyInput(
          "Enter gender (M/F/Others, letters only): ")[0];

      do {
        cout << "Enter a valid phone number: +966";
        cin >> students[count].phone;
      } while (phoneChecker(students[count].phone));

      string isFirstSemester;
      cout << "Is this your first semester? (yes/no): ";
      cin >> isFirstSemester;

      for (int i = 0; i < numGrades; i++) {
        cout << "Enter your grades out of 100 for " << students[count].course[i]
             << ": ";
        cin >> students[count].grades[i];
        if (students[count].grades[i] > 100 || students[count].grades[i] < 0)
          i--;
      }
      while (true) {
        for (char &c : isFirstSemester) {
          c = tolower(c);
        }
        if (isFirstSemester == "yes") {
          students[count].gpa = GPAs(students[count].grades, numGrades);
          break;
        } else if (isFirstSemester == "no") {
          cout << "Enter your previous GPA: ";
          cin >> students[count].pGPA;
          students[count].gpa =
              GPAs(students[count].grades, numGrades, students[count].pGPA);
          break;
        } else {
          cout << "Wrong input!!\n";
          continue;
        }
      }
      currentTime = time(nullptr);
      timeString = ctime(&currentTime);
      cout << "Student added. Your ID:  " << idPrinter(count) << endl;
      students[count].ID = idPrinter(count);
      statFile << students[count].fullname
               << " with the ID: " << idPrinter(count)
               << " has been added to the system in : " << timeString << endl;
      count++;
      break;
    }

    case '2':
      cout << "|2. Search for a student |" << endl;
      if (!(count < 2)) {
        cout << "Please complete the ID of the student you are looking for: "
                "223000";
        cin >> SearchID;
        SearchID = SearchID - 4310;
        statFile << "The user seaarched for the student with the ID: "
                 << SearchID;
        for (int i = 0; i < numStudents; i++) {
          if (students[i].ID == SearchID) {
            studentFound = true;
            cout << "Student is found! " << endl;
            cout << "Student's full name: " << students[i].fullname << endl;
            cout << "Student's age: " << students[i].age << endl;
            cout << "Student's gender: " << students[i].gender << endl;
            cout << "Student's phone: " << students[i].phone << endl;
            cout << "Student's major: " << students[i].major << endl;
            cout << "Student's GPA: " << students[i].gpa << endl;
            currentTime = time(nullptr);
            timeString = ctime(&currentTime);
            statFile
                << "The wanted student have been found and displaying their "
                   "information went successfully in: "
                << timeString << endl;
            break;
          }
        }
        if (!studentFound) {
          currentTime = time(nullptr);
          timeString = ctime(&currentTime);
          cout << "Student is not found :( " << endl;
          statFile << "The wanted student with the ID: "
                   << idPrinter(SearchID)
                   << " haven't been found which lead the system to "
                      "break from searching in: "
                   << timeString << endl;
      }
    }
    else {
      cout << "There is no students to sort";
    }
    break;

  case '3':
    cout << "|3. Update students' info. |" << endl;
    // Add code for updating student's info
    break;

  case '4':
    cout << "|4. Delete a student |" << endl;
    if (count > 0) {
      string sname;
      cout << "Enter student name to delete: ";
      cin.ignore();
      getline(cin, sname);

      studentFound = false;
      for (int i = 0; i < count; i++) {
        if (students[i].fullname == sname) {
          for (int j = i; j < count - 1; j++) {
            students[j] = students[j + 1];
          }
          count--;
          studentFound = true;
          cout << "Student " << sname << " deleted." << endl;
          break;
        }
      }

      if (!studentFound) {
        cout << "Student " << sname << " not found." << endl;
      }
    } else {
      cout << "No students to delete." << endl;
      break; // Exit the loop and return to the options menu
    }
    break;

  case '5':
    while (true) {
      cout << "|5. Sort |" << endl;
      cout << "Press 1 to sort by GPA or 2 to sort by name: ---> ";
      cin >> option;
      if (option == '1') {
        for (int i = 0; i < count; i++) {
          for (int j = i; j < count; j++) {
            if (students[i].gpa <
                students[j].gpa) { // This if statment is for sorting by GPA
              temp[0] = students[i];
              students[i] = students[j];
              students[j] = temp[0];
            }
          }
        }
        break;
      } else if (option == '2') {
        for (int i = 0; i < count; i++) {
          for (int j = i; j < count; j++) {
            if (students[i].fullname <
                students[j]
                    .fullname) { // This if statment is for sorting by name
              temp[0] = students[i];
              students[i] = students[j];
              students[j] = temp[0];
            }
          }
        }
        cout << "Sorting is done!\nPlease choose Display next if you wish "
                "to "
                "see the sorted list"
             << endl;
        break; /* If everything goes smoothly the loop will be exited
                succssfully to continue the program flow*/
      } else {
        cout << "Invalid option. Please try "
                "again.\n__________________________________"
             << endl;
        continue;
        /* This will handle the error if the user
           enters a wrong option by continuing the loop */
      }
    }
    break;
  case '6':
    cout << "|6. Display all students |" << endl;
    for (int i = 0; i < count; i++) {
      cout << "\nStudent's Information:\nFull Name: " << students[i].fullname
           << endl;
      cout << "ID: " << students[i].ID << endl;
      cout << "Age: " << students[i].age << endl;
      cout << "Gender: " << students[i].gender << endl;
      cout << "Phone: " << students[i].phone << endl;
      cout << "Major: " << students[i].major << endl;
      cout << "GPA: " << students[i].gpa << endl;
      cout << "Grades: " << endl;
      for (int j = 0; j < 5; j++) {
        cout << students[i].course[j] << ": " << students[i].grades[j] << " / ";
      }
    }
    // Add code for displaying all students
    break;
  case '7':
    currentTime = time(nullptr);
    timeString = ctime(&currentTime);
    cout << "|7. Exit |\n" << endl;
    statFile << "The user choose to end the program in: " << timeString;
    statFile << "\nWith a total of records = " << count << endl;

    statFile.close();
    cout << "Thank you for using our program. Goodbye!";
    return 0;
  default:
    cout << "Invalid option. Please choose a valid option." << endl;
  }
}

return 0;
}
// The body of every function we used so far:

// we passed an array and its size by value to
// calcualte the GPA for first semester's students
double GPAs(double a[], int size) {
  double sum = 0;
  for (int i = 0; i < size; i++)
    sum += a[i];
  // sum = sum * (5.0 / 100.0)/5.0; which is equivalent to sum * 0.01
  // assuming that the courses have the same hours
  return sum * 0.01;
}
// we passed an array and its size by value to calcualte the GPA for any
// semester's students except the first.
double GPAs(double a[], int size,
            double pGPA) { // pGPA stands for previos GPA
  double sum = 0;
  for (int i = 0; i < size; i++) {
    sum += a[i];
  }
  if (pGPA == 0) {
    return sum * 0.01;
  } else {
    sum = ((sum * 0.01) + pGPA) / 2.0;
    return sum;
  }
}
/* This function is used to check if the phone number is
valid or not and valid it if posible by adding 966 */
bool phoneChecker(string &phone) {
  for (int i = 0; i < phone.length(); i++) {
    if (!isdigit(phone[i])) {
      return false;
    }
  }
  if ((phone.substr(0, 2) == "05") && (phone.length() == 10)) {
    /* If the phone number starts with 05 and has 12 digits after adding 2
     * (which is for 966 )*/
    phone = "+966" +
            phone.substr(
                1, phone.length()); // Add 966 to the phone number succssfully
    return false;
  } else if (phone[0] == '5' && phone.length() == 9) {
    /* If the phone number doesn't start with 05 and/or has less than 12
     * digits */
    phone = "+966" + phone;
    return false;
  }

  else
    return true;
}

void allSmall(string &x) {
  for (int i = 0; i < x.length(); i++)
    x[i] = tolower(x[i]);
}
long int idPrinter(int x) { return 2230004310 + x; }

string validateLettersOnlyInput(const string &prompt) {
  string input;
  while (true) {
    cout << prompt;
    getline(cin, input);
    bool valid = true;
    cin.ignore();
    for (char c : input) {
      if (!isalpha(c) && c != ' ') {
        cout << "Invalid input. Please use letters only." << endl;
        valid = false;
        break;
      }
    }
    if (valid) {
      return input;
    }
  }
}

/*
     void printInfo(StudentInfo student[], int n){
       cout << "Student is found! " << endl;
       cout << "Student's full name: " << student[n].fullname << endl;
       cout << "Student's age: " << student[n].age << endl;
       cout << "Student's gender: " << student[n].gender << endl;
       cout << "Student's phone: " << student[n].phone << endl;
       cout << "Student's major: " << student[n].major << endl;
       cout << "Student's GPA: " << student[n].gpa << endl;
       cout << "Students grades: " << endl;
       for (int j = 0; j < 5; j++){
         cout << student[n].course[j] << ": " << student[n].grades[j] <<endl;
       }
     }*/
/*
string resetTime() {
  time_t currentTime = time(nullptr);
  string timeString = ctime(&currentTime);
  return timeString ;
}*/
