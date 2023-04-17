
//=================================================================================
// Name         : DS Assignment#2 
// Author       : 
// Version      : 1.0
// Date Created : 05-Nov-2022
// Date Modified: 
// Description  : Starter Code for Contact Management System using BST Tree in C++
//=================================================================================
#include<sstream>
#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>

#include "myvector.h"
#include "myvector.cpp"
#include "contact.h"
#include "contact.cpp"
#include "contactbst.h"
#include "contactbst.cpp"
//==========================================================
void listCommands()
{
	cout<<"----------------------------------"<<endl;
	cout<<"import <path>      :Import contacts from a CSV file"<<endl
		<<"export <path>      :Export contacts to a CSV file"<<endl
		<<"add                :Add a new contact"<<endl
		<<"update <key>       :Update a contact's details"<<endl
		<<"remove <key>       :Delete a contact"<<endl
		<<"searchFor <key>    :Search for a contact"<<endl
		<<"markFav <key>      :Mark as favourite"<<endl
		<<"unmarkFav <key>    :Unmark as favourite"<<endl
		<<"printASC           :Print contacts in ascending order"<<endl
		<<"printDES           :Print contacts in descending order"<<endl
		<<"printFav           :Print all favourite contacts"<<endl
		<<"help               :Display the available commands"<<endl
		<<"exit               :Exit the program"<<endl;
}

//==========================================================
int main()
{
	ContactBST contacts;

    listCommands();
    string user_input;
    string command;
    string parameter;

    while(true)
    {
        cout << ">";
        getline(cin, user_input);

        stringstream sstr(user_input);
        getline(sstr, command, ' ');
        getline(sstr, parameter);

        try
        {
            Node* root=contacts.getRoot();
            if(command == "import") 
            {
                int result=contacts.importCSV(parameter);
                if(result>=0)
                {
                    cout<<result<<" contacts imported successfully"<<endl;
                }
                else
                {
                    cout<<"Error importing contacts!!"<<endl;
                }
            }
            else if(command == "export") 
            {
                std::ofstream file(parameter);
                int result=contacts.exportCSV(root, file);
                if(result>=0)
                {
                    cout<<result<<" contacts exported successfully"<<endl;
                }
                else
                {
                    cout<<"Error exporting contacts!!"<<endl;
                }
                file.close();
            }
            else if (command == "add") 
            {
                string fname, lname, email, phone, city, country, isFav_str;
                string fullname;
                bool isFav;
                fullname= fname+" "+lname;
                cout<<"Enter the new contact details: "<<endl;
                //Error checking for all the inputs
                do
                {
                    cout<<"First Name: ";
                    getline(cin, fname);
                    if(fname.empty() || !isalpha(fname.front()) || !isalpha(fname.back()))
                    {
                        cout<<"Error! Please enter a valid first name:"<<endl;
                    }
                }
                while(fname.empty() || !isalpha(fname.front()) || !isalpha(fname.back()));
                
                do
                {
                    cout<<"Last Name: ";
                    getline(cin, lname);
                    if(lname.empty() || !isalpha(lname.front()) || !isalpha(lname.back()))
                    {
                        cout<<"Error! Please enter a valid last name:"<<endl;
                    }
                }
                while(lname.empty() || !isalpha(lname.front()) || !isalpha(lname.back()));

                do
                {
                    cout<<"Email Address: ";
                    getline(cin, email);
                    if(email.empty() || email.find('@')==string::npos || email.find('.')==string::npos)
                    {
                        cout<<"Error! Please enter a valid email address:"<<endl;
                    }
                }
                while(email.empty() || email.find('@')==string::npos || email.find('.')==string::npos);
                
                do
                {
                    cout<<"Phone number: ";
                    getline(cin, phone);
                    if(phone.empty() || !isdigit(phone.front()) || !isdigit(phone.back()))
                    {
                        cout<<"Error! Please enter a valid phone number:"<<endl;
                    }
                }
                while(phone.empty() || !isdigit(phone.front()) || !isdigit(phone.back()));

                do
                {
                    cout<<"City: ";
                    getline(cin, city);
                    if(city.empty() || !isalpha(city.front()) || !isalpha(city.back()))
                    {
                        cout<<"Error! Please enter a valid city:"<<endl;
                    }
                }
                while(city.empty() || !isalpha(city.front()) || !isalpha(city.back()));

                do
                {
                    cout<<"Country: ";
                    getline(cin, country);
                    if(country.empty() || !isalpha(country.front()) || !isalpha(country.back()))
                    {
                       cout<<"Error! Please enter a valid country: "<<endl;
                    }
                }
                while(country.empty() || !isalpha(country.front()) || !isalpha(country.back()));

                cout<<"Do you want to mark the new contact as Favorite? (yes/no): ";
                getline(cin, isFav_str);
                if(isFav_str=="yes")
                {
                    isFav=true;
                }
                else if(isFav_str=="no")
                {
                    isFav=false;
                }
                else
                {
                    cout<<"Incorrect output!"<<endl;
                }
                //Create new contact and add to the list
                Contact *newcontact= new Contact(fname, lname, email, phone, city, country, isFav);
                contacts.add(root, fullname, newcontact);
                cout<<"Contact added successfully!"<<endl;

            }
            else if(command == "update") 
            {
                contacts.update(parameter);
            }
            else if(command == "remove") 
            {
                contacts.remove(root, parameter);
            }
            else if(command == "searchFor") 
            {
                Node* node=contacts.searchFor(root, parameter);
                if(contacts.searchFor(root, parameter)==NULL)
                {
                    cout<<"Missing key!!"<<endl;
                }
                else
                {
                    node->print();
                }                
            }
            else if(command == "markFav") 
            {
                contacts.markFav(parameter);
            }
            else if(command == "unmarkFav") 
            {
                contacts.unmarkFav(parameter);
            } 
            else if(command == "printASC") 
            {
                contacts.printASC(root);
            } 
            else if(command == "printDES") 
            {
                contacts.printDES(root);
            } 
            else if(command == "printFav") 
            {
                contacts.printFav(root);
            }
            else if(command == "help") 
            {
                listCommands();
            } 
            else if(command == "exit")
            {
                break;
            }
            else 
            {
                throw invalid_argument("Invalid command: " + command);
            }
        } 
        catch(exception& e) 
        {
            cout<<"Error: "<< e.what()<<endl;
        }
    }
    return 0;
}