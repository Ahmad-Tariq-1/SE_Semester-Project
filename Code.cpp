#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <Windows.h>
using namespace std;

class validations // class for input validations
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
        if (number.size() !=8)
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

