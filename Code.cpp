#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <Windows.h>
using namespace std;

class Validations // class for input validations
{
public:
    bool idValidation(const string &idString)
    {
        if (idString.empty() || idString.find(' ') != string::npos)
        {
            return false;
        }

        for (char ch : idString)
        {
            if (!isdigit(ch))
            {
                return false;
            }
        }
        return true;
    }

    bool stringValidation(const string &str)
    {
        if (str.empty())
        {
            return false;
        }

        for (char ch : str)
        {
            if (!isspace(ch))
            {
                return true;
            }
        }
        return false;
    }

    bool phoneNumberValidation(const string &number)
    {
        if (number.size() != 8)
        {
            return false;
        }

        for (char ch : number)
        {
            if (!isdigit(ch))
            {
                return false;
            }
        }
        return true;
    }

    bool emailValidation(const string &email)
    {
        const string gmailSuffix = "@gmail.com";
        if (email.empty())
        {
            return false;
        }

        for (char ch : email)
        {
            if (isspace(ch))
            {
                return false;
            }
        }
        if (email.size() < gmailSuffix.size() + 5)
        {
            return false;
        }

        string prefix = email.substr(0, email.size() - gmailSuffix.size());
        for (char ch : prefix)
        {
            if (!islower(ch) && !isdigit(ch) && ch != '.' && ch != '_' && ch != '-')
            {
                return false;
            }
        }

        string suffix = email.substr(email.size() - gmailSuffix.size());
        return suffix == gmailSuffix;
    }
};

class Contact
{
protected:
    string name;
    string number;
    string email;
    string type;

public:
    Contact() {}

    Contact(const string &name, const string &number, const string &email, const string &type)
        : name(name), number(number), email(email), type(type) {}

    // Getters
    string getName() const { return name; }
    string getNumber() const { return number; }
    string getEmail() const { return email; }
    string getType() const { return type; }

    // Setters
    void setName(const string &name) { this->name = name; }
    void setNumber(const string &number) { this->number = number; }
    void setEmail(const string &email) { this->email = email; }
    void setType(const string &type) { this->type = type; }
};
class AddContact : public Validations
{
public:
    void addContact(Contact ptclContacts[], int &ptclCount, Contact localContacts[], int &localCount, Contact emergencyContacts[], int &emergencyCount)
    {
        system("cls");
        bool main_page = false;
        while (!main_page)
        {
            cout << "\n\n\t ____________________________________________\n";
            cout << "\t|\t   Choose Contact Type\t\t     |\n";
            cout << "\t|____________________________________________|\n";
            cout << "\t|   |" << setw(42) << "|\n";
            cout << "\t| 1 |  PTCL Number" << setw(29) << "|\n";
            cout << "\t| 2 |  Emergency Number" << setw(24) << "|\n";
            cout << "\t| 3 |  Local Number" << setw(28) << "|\n";
            cout << "\t| 0 |  Back to Main Menu" << setw(23) << "|\n";
            cout << "\t|___|________________________________________|\n\n";
            string choice;
            while (true)
            {
                cout << "\tEnter your choice: ";
                getline(cin, choice);
                if (stringValidation(choice) && (choice == "1" || choice == "2" || choice == "3" || choice == "0"))
                {
                    break;
                }
                cout << "\n\tInvalid input. Please enter a valid choice (0, 1, 2, or 3).\n";
            }

            if (choice == "0")
            {
                main_page = true;
                continue;
            }
            else if (choice == "1" && ptclCount < 100)
            {
                addSpecificContact(ptclContacts, ptclCount, "PTCL", ptclContacts, ptclCount, localContacts, localCount, emergencyContacts, emergencyCount);
            }
            else if (choice == "2" && emergencyCount < 100)
            {
                addSpecificContact(emergencyContacts, emergencyCount, "Emergency", ptclContacts, ptclCount, localContacts, localCount, emergencyContacts, emergencyCount);
            }
            else if (choice == "3" && localCount < 100)
            {
                addSpecificContact(localContacts, localCount, "Local", ptclContacts, ptclCount, localContacts, localCount, emergencyContacts, emergencyCount);
            }
            else
            {
                cout << "\n\tInvalid choice or maximum contacts reached for this type.\n";
            }
            string addMore;
            while (true)
            {
                cout << "\n\n\tDo you want to add another contact? (y/n): ";
                getline(cin, addMore);
                if (stringValidation(addMore) && (addMore == "y" || addMore == "Y" || addMore == "n" || addMore == "N"))
                {
                    if (addMore == "n" || addMore == "N")
                    {
                        main_page = true;
                    }
                    break;
                }
                cout << "\n\tInvalid input. Please enter 'y' or 'n'.\n";
            }
        }
    }

    // protected:
    void addSpecificContact(Contact contacts[], int &count, const string &type, Contact ptclContacts[], int ptclCount, Contact localContacts[], int localCount, Contact emergencyContacts[], int emergencyCount)
    {
        system("cls");
        while (true)
        {
            string name, number, email;
            cout << "\n\n\tEnter details for the new " << type << " contact:\n";

            // Get name
            while (true)
            {
                cout << "\tName : \t\t";
                getline(cin, name);
                if (stringValidation(name))
                {
                    break;
                }
                cout << "\n\tInvalid input. Please enter a valid name.\n";
            }

            // Get number
            while (true)
            {
                cout << "\tNumber :\t";
                getline(cin, number);

                if (type == "Emergency" && idValidation(number))
                {
                    if (isUniqueNumber(number, ptclContacts, ptclCount, localContacts, localCount, emergencyContacts, emergencyCount))
                    {
                        break;
                    }
                    else
                    {
                        cout << "\n\tThis number is already registered. Please enter a different number.\n";
                    }
                }
                else if ((type == "Local" && localPhoneNumberValidation(number)) ||
                         (type != "Local" && type != "Emergency" && phoneNumberValidation(number)))
                {
                    if (isUniqueNumber(number, ptclContacts, ptclCount, localContacts, localCount, emergencyContacts, emergencyCount))
                    {
                        break;
                    }
                    else
                    {
                        cout << "\n\tThis number is already registered. Please enter a different number.\n";
                    }
                }
                else
                {
                    cout << "\n\tInvalid input. Please enter a valid phone number.\n";
                }
            }

            // Get email if not emergency
            if (type != "Emergency")
            {
                while (true)
                {
                    cout << "\tEmail : \t";
                    getline(cin, email);
                    if (emailValidation(email))
                    {
                        if (isUniqueEmail(email, ptclContacts, ptclCount, localContacts, localCount))
                        {
                            break;
                        }
                        else
                        {
                            cout << "\n\tThis email is already registered. Please enter a different email.\n";
                        }
                    }
                    else
                    {
                        cout << "\n\tInvalid input. Please enter a valid email ending with @gmail.com.\n";
                    }
                }
            }

            // Add contact
            contacts[count++] = Contact(name, number, email, type);
            cout << "\n\n\tContact added successfully!\n";
            break;
        }
    }

    bool localPhoneNumberValidation(const string &number)
    {
        if (((number.substr(0, 4) == "+923") && (number.size() == 13)) || ((number.substr(0, 2) == "03") && (number.size() == 11)))
        {
            for (char ch : number)
            {
                if (!isdigit(ch))
                {
                    return false;
                }
            }
            return true;
        }
        return false;
    }

    bool isUniqueNumber(const string &number, Contact ptclContacts[], int ptclCount, Contact localContacts[], int localCount, Contact emergencyContacts[], int emergencyCount)
    {
        for (int i = 0; i < ptclCount; ++i)
        {
            if (ptclContacts[i].getNumber() == number)
            {
                return false;
            }
        }
        for (int i = 0; i < localCount; ++i)
        {
            if (localContacts[i].getNumber() == number)
            {
                return false;
            }
        }
        for (int i = 0; i < emergencyCount; ++i)
        {
            if (emergencyContacts[i].getNumber() == number)
            {
                return false;
            }
        }
        return true;
    }

    bool isUniqueEmail(const string &email, Contact ptclContacts[], int ptclCount, Contact localContacts[], int localCount)
    {
        for (int i = 0; i < ptclCount; ++i)
        {
            if (ptclContacts[i].getEmail() == email)
            {
                return false;
            }
        }
        for (int i = 0; i < localCount; ++i)
        {
            if (localContacts[i].getEmail() == email)
            {
                return false;
            }
        }
        return true;
    }
};
