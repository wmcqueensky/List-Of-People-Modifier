#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <windows.h>
#include <vector>
#include <cctype>
#include <stdexcept>

using namespace std;

class Person {
public:
    int age;
    string name;
    string surname;
    Person(string n, string s, int a) :
        name(n),
        surname(s),
        age(a) {}
};

ostream& operator<<(ostream& out, const Person& person) {
    out << person.name << " " << person.surname << " " << person.age << endl;
    return out;
}

bool contains_digits(string& str) {
    for (char c : str) {
        if (isdigit(c)) {
            return true;
        }
    }
    return false;
}

bool validation_process(string name = "T", string surname = "T", int age = 0) {
    if ((age < 0) || (age > 130) || (isupper(name[0]) == false) || (isupper(surname[0]) == false)
        || (contains_digits(name) == true) || (contains_digits(surname) == true)) {
        return false;
    }
    else {
        return true;
    }
}

void show_People(vector<Person>& people) {
    cout << endl;
    for (int i = 0; i < people.size(); i++) {
        cout << i + 1 << ". " << people[i] << endl;
    }
}

void delete_Person(vector<Person>& people, int index) {
    people.erase(people.begin() + (index - 1));
}

void display_Options(vector<Person>& people) {
    cout << "People you currently have on the list: " << endl << endl;
    show_People(people);

    cout << "1)Change name of the person on the list" << endl;
    cout << "2)Change surname of the person on the list" << endl;
    cout << "3)Change age of the person on the list" << endl;
    cout << "4)Add new person" << endl;
    cout << "5)Delete person" << endl;
    cout << "6)Save file" << endl << endl;
}

int main()
{
    system("chcp 65001  > nul");
    string file_name;

    cout << "Insert a file name: ";
    while (true) {
        try {
            cin >> file_name;

            if (file_name != "input_file.txt") {
                throw 1;
            }
            else {
                break;
            }
        }
        catch (int x) {
            system("cls");
            cout << "Wrong file name, try again" << endl;
            cout << "Insert a file name: ";
        }
    }
    cout << endl;

    ifstream my_file;
    my_file.open(file_name);

    vector<Person> People;
    int number_of_the_people = 0;

    if (my_file.is_open())
    {
        cout << "You have access to the file" << endl << endl;

        string line;
        int number_of_line = 0;

        while (getline(my_file, line)) {
            try {
                number_of_line++;
                size_t pos = line.find(' ');
                string name = line.substr(0, pos);
                line.erase(0, pos + 1);
                pos = line.find(' ');
                string surname = line.substr(0, pos);
                line.erase(0, pos + 1);
                int age = stoi(line);
                if ((validation_process(name, surname, age) == false)) {
                    throw 4;
                }
                else {
                    People.push_back(Person(name, surname, age));
                    number_of_the_people++;
                }

            }
            catch (invalid_argument& e) {
                cout << "Wrong format of data on line: " << number_of_line << endl;
                cout << "All data should be separated by one white space and segregated like this: ";
                cout << " name surname age " << endl << endl;
                continue;

            }
            catch (int x) {
                cout << "Invalid name, surname or age on line: " << number_of_line << endl;
                cout << "Name and surname have to start with a big letter." << endl;
                cout << "Name and surname must not contain digits." << endl;
                cout << "Age must not be a negative number or number above 130." << endl << endl;
                continue;

            }
            catch (out_of_range& e) {
                cout << "Invalid age on line: " << number_of_line << endl;
                cout << "Age must not be a negative number or number above 130." << endl << endl;
                continue;
            }
        }

        while (true) {

            cout << "People you currently have on the list: " << endl << endl;
            show_People(People);

            cout << "1)Change name of the person on the list" << endl;
            cout << "2)Change surname of the person on the list" << endl;
            cout << "3)Change age of the person on the list" << endl;
            cout << "4)Add new person" << endl;
            cout << "5)Delete person" << endl;
            cout << "6)Save file" << endl << endl;

            char choice1;

            cout << "Choose one of the options above" << endl;
            while (true) {
                try {
                    cin >> choice1;
                    if (choice1 == '1' || choice1 == '2' || choice1 == '3' || choice1 == '4' || choice1 == '5' || choice1 == '6') {
                        break;
                    }
                    else {
                        throw 2;
                    }
                }
                catch (int x) {
                    system("cls");
                    display_Options(People);
                    cout << "You have to choose one of the available options! Try again: " << endl;
                }
            }

            switch (choice1) {
            case '1':
                unsigned int choice2;
                if (People.size() == 0) {
                    system("cls");
                    cout << "YOUR LIST IS EMPTY" << endl;
                }
                else {
                    cout << "Choose number of the person to change his/her name: " << endl;
                    while (true) {
                        try {
                            cin >> choice2;

                            if (cin.fail()) {
                                system("cls");
                                cin.clear();
                                cin.ignore(10000, '\n');
                                display_Options(People);
                                cout << "Error! Choose number of the person again: " << endl;
                            }
                            else  if ((choice2 > 0) && (choice2 <= number_of_the_people)) {
                                string input_name;
                                cout << "Insert new name: " << endl;
                                while (true) {
                                    try {
                                        cin >> input_name;
                                        if (validation_process(input_name) == false) {
                                            throw 9;
                                        }
                                        else {
                                            People[choice2 - 1].name = input_name;
                                            system("cls");
                                            break;
                                        }
                                    }
                                    catch (int x) {
                                        system("cls");
                                        display_Options(People);
                                        cout << "Name should start with a big letter and should not contain digits. Insert name again." << endl;
                                    }
                                }
                                break;
                            }
                            else {
                                throw 3;
                            }

                        }
                        catch (int x) {
                            system("cls");
                            display_Options(People);
                            cout << "Error! Choose number of the person again: " << endl;
                        }
                    }
                }
                break;

            case '2':
                if (People.size() == 0) {
                    system("cls");
                    cout << "YOUR LIST IS EMPTY" << endl;
                }
                else {
                    cout << "Choose number of the person to change his/her surname: " << endl;
                    while (true) {
                        try {
                            cin >> choice2;

                            if (cin.fail()) {
                                system("cls");
                                cin.clear();
                                cin.ignore(10000, '\n');
                                display_Options(People);
                                cout << "Error! Choose number of the person again: " << endl;
                            }
                            else  if ((choice2 > 0) && (choice2 <= number_of_the_people)) {
                                string input_surname;
                                cout << "Insert new surname: " << endl;
                                while (true) {
                                    try {
                                        cin >> input_surname;
                                        if (validation_process("T", input_surname, 0) == false) {
                                            throw 9;
                                        }
                                        else {
                                            People[choice2 - 1].surname = input_surname;
                                            system("cls");
                                            break;
                                        }
                                    }
                                    catch (int x) {
                                        system("cls");
                                        display_Options(People);
                                        cout << "Surname should start with a big letter and should not contain digits. Insert surname again." << endl;
                                    }
                                }
                                break;
                            }
                            else {
                                throw 3;
                            }

                        }
                        catch (int x) {
                            system("cls");
                            display_Options(People);
                            cout << "Error! Choose number of the person again: " << endl;
                        }
                    }
                    system("cls");
                }
                break;

            case '3':
                if (People.size() == 0) {
                    system("cls");
                    cout << "YOUR LIST IS EMPTY" << endl;
                }
                else {
                    cout << "Choose number of the person to change his/her age: " << endl;
                    while (true) {
                        bool if_end = false;
                        try {
                            cin >> choice2;

                            if (cin.fail()) {
                                system("cls");
                                cin.clear();
                                cin.ignore(10000, '\n');
                                display_Options(People);
                                cout << "Error! Choose number of the person again: " << endl;
                            }
                            else  if ((choice2 > 0) && (choice2 <= number_of_the_people)) {
                                string input_age;
                                cout << "Insert new age: " << endl;
                                while (true) {
                                    try {
                                        cin >> input_age;
                                        int INPUT_AGE = stoi(input_age);
                                        if (validation_process("T", "T", INPUT_AGE) == false) {
                                            throw 9;
                                        }
                                        else {
                                            People[choice2 - 1].age = INPUT_AGE;
                                            if_end = true;
                                            break;
                                        }
                                    }
                                    catch (int x) {
                                        system("cls");
                                        display_Options(People);
                                        cout << "Age must not be a negative number or number above 130. Insert age again." << endl;
                                        continue;
                                    }
                                    catch (invalid_argument& e) {
                                        system("cls");
                                        display_Options(People);
                                        cout << "Age must not be a negative number or number above 130. Insert age again." << endl;
                                        continue;
                                    }
                                    catch (out_of_range& e) {
                                        system("cls");
                                        display_Options(People);
                                        cout << "Age must not be a negative number or number above 130. Insert age again." << endl;
                                        continue;
                                    }
                                }
                            }
                            else {
                                throw 3;
                            }

                        }
                        catch (int x) {
                            system("cls");
                            display_Options(People);
                            cout << "Error! Choose number of the person again: " << endl;
                            continue;
                        }

                        if (if_end == true) {
                            system("cls");
                            break;
                        }

                    }
                }
                break;

            case '5':
                if (People.size() != 0) {
                    cout << "Choose number of the person you want to delete: " << endl;
                    while (true) {
                        try {
                            cin >> choice2;

                            if (cin.fail()) {
                                system("cls");
                                cin.clear();
                                cin.ignore(10000, '\n');
                                display_Options(People);
                                cout << "Error! Choose number of the person again: " << endl;
                            }
                            else  if ((choice2 > 0) && (choice2 <= number_of_the_people)) {
                                delete_Person(People, choice2);
                                system("cls");
                                break;
                            }
                            else {
                                throw 3;
                            }

                        }
                        catch (int x) {
                            system("cls");
                            display_Options(People);
                            cout << "Error! Choose number of the person again: " << endl;
                        }
                    }
                }
                else {
                    system("cls");
                    cout << endl << "YOUR LIST IS EMPTY" << endl << endl;
                }
                break;

            case '4':
                string new_name;
                string new_surname;
                string new_age;
                int NEW_AGE;

                while (true) {
                    try {
                        cout << "Insert name: " << endl;
                        cin >> new_name;
                        cout << "Insert surname: " << endl;
                        cin >> new_surname;
                        cout << "Insert age: " << endl;
                        cin >> new_age;

                        NEW_AGE = stoi(new_age);

                        if ((validation_process(new_name, new_surname, NEW_AGE) == false)) {
                            throw 3;
                        }
                        else {
                            People.push_back(Person(new_name, new_surname, NEW_AGE));
                            number_of_the_people++;
                            system("cls");
                            break;
                        }

                    }
                    catch (int x) {
                        system("cls");
                        display_Options(People);
                        cout << "Error!" << endl;
                        cout << "Name and surname have to start with a big letter." << endl;
                        cout << "Name and surname must not contain digits." << endl;
                        cout << "Age must not be a negative number or number above 130." << endl << endl;
                    }
                    catch (invalid_argument& e) {
                        system("cls");
                        display_Options(People);
                        cout << "Age must not be a negative number or number above 130. Try again." << endl;
                    }
                    catch (out_of_range& e) {
                        system("cls");
                        display_Options(People);
                        cout << "Age must not be a negative number or number above 130. Try again." << endl;
                    }
                }
                break;
            }
            if (choice1 == '6') break;
        }

        system("cls");

        string output_name;
        while (true) {
            try {
                cout << "Insert the name of the output file: " << endl;
                cin.ignore();
                getline(cin, output_name);
                if (output_name.size() > 30) {
                    throw 1;
                }
                else break;
            }
            catch (int x) {
                system("cls");
                cout << "Name of the file is too long. Try again." << endl;
            }
        }

        ofstream output_file;
        output_file.open(output_name);

        for (int i = 0; i < People.size(); i++) {
            output_file << People[i];
        }

        output_file.close();
        my_file.close();
    }
    else
    {
        cout << "Error, something is wrong with your file" << endl;
        exit(-1);
    }

    return 0;
}
