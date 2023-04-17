#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<iomanip>
#include "contact.h"

using namespace std;

Contact::Contact(string fname, string lname, string email, string phone, string city, string country, bool isFav)
	:fname(fname), lname(lname), email(email), phone(phone), city(city), country(country), isFav(isFav){}

