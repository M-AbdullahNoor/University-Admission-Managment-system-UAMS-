#include <iostream>
#include <conio.h>
#include <string>
#include <windows.h>
#include <fstream>
using namespace std;

int std_count = 0;
const int maxusers = 20;
int totalusers = 0;
const int max_std = 50;

// Arrays to store student data
string names[max_std];
string roll_numbers[max_std];
string fathersname[max_std];
string pref1[max_std];
string pref2[max_std];
string pref3[max_std];
string usernames[maxusers];
string passwords[maxusers];
float fsc_marks[max_std];
float ecat_marks[max_std];
float matric_marks[max_std];
float std_aggregate[max_std];

bool a = true;

// Function prototypes
void header();
void add();
void working();
void del();
void update();
void pref();
void view();
bool login();
void aggr();
void saveusers();
void loadusers();
void saveData();
void loadData();
void menu();
void createAccount();

int main()
{
    loadData();  // Load student data from file at the start
    loadusers(); // Load user accounts from file

    int choice_1;
    while (true)
    {
        system("cls");
        header();
        cout << "1. Login" << endl;
        cout << "2. Sign up" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice_1;

        if (choice_1 == 1)
        {
            if (login())
            {
                working();
            }
            else
            {
                cout << "Wrong username or password. Press any key to try again...";
                getch();
            }
        }
        else if (choice_1 == 2)
        {
            createAccount();
        }
        else if (choice_1 == 3)
        {
            cout << "Exiting program. Goodbye!" << endl;
            break;
        }
        else
        {
            cout << "Invalid choice. Try again." << endl;
            getch();
        }
    }

    return 0;
}

void header()
{
    cout << "________________________________________________________________________________________________" << endl;
    cout << " ###        ###         ###########        ####         ####           ###########              " << endl;
    cout << " ###        ###         ###########        ####         ####          ##         ###            " << endl;
    cout << " ###        ###         ##       ##        ##  ##     ##  ##        ###            #            " << endl;
    cout << " ###        ###         ##       ##        ##   ##  ##    ##          ###                       " << endl;
    cout << " ###        ###         ###########        ##     ###     ##           ###########              " << endl;
    cout << " ###        ###         ##       ##        ##      #      ##                     ##             " << endl;
    cout << "  ###########           ##       ##        ##             ##          #           ###           " << endl;
    cout << "   #########            ##       ##        ##             ##           ###########              " << endl;
    cout << "___________________________________________________________________________________[2024-CS-832]" << endl;
}

bool login()
{
    string user, pass;
    cout << "Enter the username: ";
    cin >> user;
    cout << "Enter the password: ";
    cin >> pass;

    for (int i = 0; i < totalusers; i++)
    {
        if (user == usernames[i] && pass == passwords[i])
        {
            cout << "Login successful! Press any key to continue..." << endl;
            getch();
            return true;
        }
    }

    return false;
}

void menu()
{
    cout << "1. Add Data" << endl;
    cout << "2. View Data" << endl;
    cout << "3. Update Data" << endl;
    cout << "4. Delete Data" << endl;
    cout << "5. Calculate Aggregate" << endl;
    cout << "6. Add Preference" << endl;
    cout << "7. Logout" << endl;
}

void working()
{
    while (true)
    {
        system("cls");
        header();
        menu();

        int num;
        cout << "Select the option (1-7): ";
        cin >> num;

        if (num == 1)
        {
            add();
        }
        else if (num == 2)
        {
            view();
        }
        else if (num == 3)
        {
            update();
        }
        else if (num == 4)
        {
            del();
        }
        else if (num == 5)
        {
            aggr();
        }
        else if (num == 6)
        {
            pref();
        }
        else if (num == 7)
        {
            saveData(); // Save data before exiting
            cout << "Exiting the program. Goodbye!" << endl;
            break;
        }
        else
        {
            cout << "Invalid option. Please try again." << endl;
            cout << "Press any key to continue...";
            getch();
        }
    }
}

void add()
{
    system("cls");
    header();

    while (a)
    {
        if (std_count >= max_std)
        {
            cout << "Maximum number of students reached." << endl;
            break;
        }

        cout << "Enter student name (or type 'STOP' to finish): ";
        cin >> names[std_count];

        if (names[std_count] == "STOP")
        {
            break;
        }

        cout << "Enter roll number: ";
        cin >> roll_numbers[std_count];
        cout << "Enter father's name: ";
        cin >> fathersname[std_count];
        cout << "Enter FSC part-1 marks (out of 570): ";
        cin >> fsc_marks[std_count];
        cout << "Enter ECAT marks (out of 400): ";
        cin >> ecat_marks[std_count];
        cout << "Enter Matric marks (out of 1100): ";
        cin >> matric_marks[std_count];

        std_aggregate[std_count] = ((matric_marks[std_count] / 1100) * 17) +
                                   ((fsc_marks[std_count] / 570) * 50) +
                                   ((ecat_marks[std_count] / 400) * 33);

        std_count++;
        saveData();
    }
}
void pref()
{
    system("cls");
    header();
    string search;
    cout << "Enter the name of the student to add preferences: ";
    cin >> search;

    for (int i = 0; i < std_count; i++)
    {
        if (names[i] == search)
        {
            cout << "Enter the first preference: ";
            cin >> pref1[i];
            cout << "Enter the second preference: ";
            cin >> pref2[i];
            cout << "Enter the third preference: ";
            cin >> pref3[i];
            cout << "Preferences added successfully." << endl;
            saveData();
            getch();
            return;
        }
    }
    cout << "Student not found." << endl;
    getch();
}
void del()
{
    int serial;
    view();
    if (std_count == 0)
    {
        return;
    }
    cout << "Enter the serial Number of the student you want to delete:";
    cin >> serial;
    matric_marks[serial - 1] = 0;
    fsc_marks[serial - 1] = 0;
    ecat_marks[serial - 1] = 0;
    names[serial - 1] = " ";
    roll_numbers[serial - 1] = " ";
    fathersname[serial - 1] = " ";
    std_aggregate[serial - 1] = 0;
    pref1[serial - 1] = " ";
    pref2[serial - 1] = " ";
    pref3[serial - 1] = " ";
    saveData();

    cout << "All information of the student " << serial << " is deleted successfully.";
    getch();
}
void update()
{
    int num;
    view();
    if (std_count == 0)
    {
        return;
    }
    cout << "Enter the serial number of the student you want to update the data:";
    cin >> num;
    cout << "Enter student name: ";
    cin >> names[num - 1];
    cout << "Enter roll number: ";
    cin >> roll_numbers[num - 1];
    cout << "Enter your Father name:";
    cin >> fathersname[num - 1];
    cout << "Enter Fsc part-1 Marks(out of 570):";
    cin >> fsc_marks[num - 1];
    cout << "Enter your ECAT marks(out of 400)";
    cin >> ecat_marks[num - 1];
    cout << "Enter your Matric marks(out of 1100)";
    cin >> matric_marks[num - 1];
    std_aggregate[num - 1] = ((matric_marks[num - 1] / 1100) * 17) + ((fsc_marks[num - 1] / 570) * 50) + ((ecat_marks[num - 1] / 400) * 33);
    saveData();
    cout << "Information added successfully!" << endl;
    cout << "Press any key to continue...";
    getch();
}
void aggr()
{
    system("cls");
    header();

    int num;
    float matric, inter, ecat;
    cout << "Enter your Matric marks(out of 1100):";
    cin >> matric;
    cout << "Enter your inter part 1 marks(out of 570):";
    cin >> inter;
    cout << "Enter your marks in ecat(out of 400):";
    cin >> ecat;
    if (matric > 1100 || inter > 570 || ecat > 400)
    {
        cout << "Either of your marks is greater then the maximum marks" << endl;
        cout << "Select '1' to enter values again" << endl;
        cout << "Select '2' to go to main menu" << endl;
        cin >> num;
        if (num == 1)
        {
            aggr();
        }
        else if (num == 2)
        {
            return;
        }
    }
    else if (matric < 1100 || inter < 570 || ecat < 400)
    {
        cout << "Your aggregate is:";
        cout << ((matric / 1100) * 17) + ((inter / 570) * 50) + ((ecat / 400) * 33) << endl;
        cout << "Press any key to continue....";
        getch();
    }
}

void view()
{
    system("cls");
    header();

    if (std_count == 0)
    {
        cout << "No data is entered." << endl;
        cout << "Press any key to continue..." << endl;
        getch();
        return;
    }

    cout << "Sr. No\tName\t\tRoll Number\tFather's Name\tFSC Marks\tMatric Marks\tECAT Marks\tAggregate\tPref1\tPref2\tPref3" << endl;

    for (int i = 0; i < std_count; i++)
    {
        if (!names[i].empty())
        {
            cout << i + 1 << "\t"
                 << names[i] << "\t\t"
                 << roll_numbers[i] << "\t\t"
                 << fathersname[i] << "\t\t"
                 << fsc_marks[i] << "\t\t"
                 << matric_marks[i] << "\t\t"
                 << ecat_marks[i] << "\t\t"
                 << std_aggregate[i] << "\t\t"
                 << pref1[i] << "\t"
                 << pref2[i] << "\t"
                 << pref3[i] << endl;
        }
    }

    cout << "Press any key to continue..." << endl;
    getch();
}

void createAccount()
{
    system("cls");
    header();
    if (totalusers >= maxusers)
    {
        cout << "Maximum number of users reached. Cannot create more accounts." << endl;
        getch();
        return;
    }

    string new_user, new_pass;
    cout << "Enter new username: ";
    cin >> new_user;
    cout << "Enter new password: ";
    cin >> new_pass;

    // Check if username already exists
    for (int i = 0; i < totalusers; i++)
    {
        if (usernames[i] == new_user)
        {
            cout << "Username already exists. Try a different username." << endl;
            getch();
            return;
        }
    }

    usernames[totalusers] = new_user;
    passwords[totalusers] = new_pass;
    totalusers++;
    saveusers();

    cout << "Account created successfully! Press any key to continue...";
    getch();
}

void saveusers()
{
    ofstream file("user.txt");
    if (!file)
    {
        cout << "Error saving user data." << endl;
        return;
    }
    file << totalusers << endl;
    for (int i = 0; i < totalusers; i++)
    {
        file << usernames[i] << endl;
        file << passwords[i] << endl;
    }
    file.close();
}

void loadusers()
{
    ifstream file("user.txt");
    if (!file)
    {
        cout << "No previous user data found. Starting fresh." << endl;
        return;
    }
    file >> totalusers;
    file.ignore();

    for (int i = 0; i < totalusers; i++)
    {
        getline(file, usernames[i]);
        getline(file, passwords[i]);
    }
    file.close();
}

void saveData()
{
    ofstream file("students.txt");
    if (!file)
    {
        cout << "Error saving student data to file!" << endl;
        return;
    }
    file << std_count << endl;
    for (int i = 0; i < std_count; i++)
    {
        file << names[i] << endl;
        file << roll_numbers[i] << endl;
        file << fathersname[i] << endl;
        file << fsc_marks[i] << endl;
        file << matric_marks[i] << endl;
        file << ecat_marks[i] << endl;
        file << std_aggregate[i] << endl;
        file << pref1[i] << endl;
        file << pref2[i] << endl;
        file << pref3[i] << endl;
    }
    file.close();
}

void loadData()
{
    ifstream file("students.txt");
    if (!file)
    {
        cout << "No previous student data found. Starting fresh." << endl;
        return;
    }

    file >> std_count;
    file.ignore();

    for (int i = 0; i < std_count; i++)
    {
        getline(file, names[i]);
        getline(file, roll_numbers[i]);
        getline(file, fathersname[i]);
        file >> fsc_marks[i] >> matric_marks[i] >> ecat_marks[i] >> std_aggregate[i];
        file.ignore();
        getline(file, pref1[i]);
        getline(file, pref2[i]);
        getline(file, pref3[i]);
    }
    file.close();
}
