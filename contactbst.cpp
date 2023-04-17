#include<iostream>
#include<sstream>
#include<fstream>
#include<cstdlib>
#include<string>
#include<iomanip>
#include<vector>
#include<exception>
#include "contactbst.h"
#include "myvector.h"
#include "contact.h"

using namespace std;

//Constructor
ContactBST::ContactBST(): root(NULL){}

//Destructor
ContactBST::~ContactBST()
{
	removeAll(root);
}
//Helper function for destructor
void ContactBST::removeAll(Node* ptr)
{
	if(ptr==NULL)
	{
		return;
	}
	removeAll(ptr->left);
	removeAll(ptr->right);
	delete ptr;
}
//Return the root
Node* ContactBST::getRoot()
{
	return root;
}
//Add new contact 
void ContactBST::add(Node* ptr, string key, Contact* data)
{
	if(root==NULL)
	{
		Node* old=new Node(key, data);
		root=old;
		old->parent=root;
	}
	else if(key==ptr->key)
	{
		ptr->contactVector.push_back(data);
	}
	else if(key<ptr->key)
	{
		if(ptr->left==NULL)
		{
			Node* newptr=new Node(key, data);
			ptr->left=newptr;
			newptr->parent=ptr;
		}
		else
		{
			add(ptr->left, key, data);
		}
	}
	else
	{
		if(ptr->right==NULL)
		{
			Node* newptr=new Node(key, data);
			ptr->right=newptr;
			newptr->parent=ptr;
		}
		else
		{
			add(ptr->right, key, data);
		}
	}
}
//Update the node with given key
void ContactBST::update(string key)
{
	Node* node=searchFor(root, key);
	if(node==NULL)
	{
		cout<<"Error:key does not exist!!"<<endl;
		return;
	}
	node->print();
	int index, contactIndex;
	cout<<"Enter index of the contact to update";
	cin>>index;
	if(index>node->contactVector.size())
	{
		cout<<"Error:Invalid index!!"<<endl;
	}
	else
	{
		Contact* contact=node->contactVector.at(index-1);
		while(true)
		{
			cout<<"Which record do you want to update?"<<endl
			<<"1. First Name"<<endl
			<<"2. Last Name"<<endl
			<<"3. Email Address"<<endl
			<<"4. Phone Number"<<endl
			<<"5. City"<<endl
			<<"6. Country"<<endl;
			cin>>contactIndex;
			switch(contactIndex)
			{
			case 1:
				cout<<"Please Enter the new First Name: "<<endl;
				cin>>contact->fname;
				break;
			case 2:
				cout<<"Please Enter the new Last Name: "<<endl;
				cin>>contact->lname;
				break;
			case 3:
				cout<<"Please Enter the new Email Address: "<<endl;
				cin>>contact->email;
				break;
			case 4:
				cout<<"Please Enter the new Phone Number: "<<endl;
				cin>>contact->phone;
				break;
			case 5:
				cout<<"Please Enter the new city: "<<endl;
				cin>>contact->city;
				break;
			case 6:
				cout<<"Please Enter the new country: "<<endl;
				cin>>contact->country;
				break;
			default:
				cout<<"Invalid index!!"<<endl;
				break;
			}
			cout<<"Contact updated successfully!"<<endl;
			string answer;
			cout<<"Do you want to update another record? (yes/no)"<<endl;
			cin>>answer;
			if(answer!="yes" || answer!="YES" || answer!="Yes")
			{
				break;
			}					
		}		
		string fullname=contact->fname+" "+contact->lname;
		if(fullname!=key)
		{
			node->contactVector.erase(index-1);
			add(root, fullname, contact);
			if(node->contactVector.size()==0)
			{
				remove(root, node->key);
			}
		}
	}
}
//Delete a contact
void ContactBST::remove(Node* ptr, string key)
{
	//Search for the node to be removed
	Node* node=searchFor(root, key);
	//If node not found
	if(node==NULL)
	{
		cout<<"Error: key does not exist!!"<<endl;
		return;
	}
	//Print the node being removed
	node->print();
	int index=0;
	cout<<"Enter index of the contact to delete: ";
	cin>>index;
	if(index>node->contactVector.size())
	{
		cout<<"Error:Invalid index!!"<<endl;
	}
	//If there's only one contact
	else if(node->contactVector.size()<=1)
	{
		if(key<node->key)
		{
			remove(node->left, key);
		}
		else if(key>node->key)
		{
			remove(node->right, key);
		}
		else
		{
			//If the node has no child
			if(node->left==NULL && node->right==NULL)
			{
				if(node->parent->left==node)
				{
					node->parent->left=NULL;
				}
				else
				{
					node->parent->right=NULL;
				}
				delete node;
			}
			//If the node has only one child
			else if(node->left==NULL && node->right!=NULL)
			{
				//If node is the left child of its parent, set parent's left child to node's right child
				if(node->parent->left==node)
				{
					node->parent->left=node->right;
				}
				//Else set parent's right child to node's right child
				else
				{
					node->parent->right=node->right;
				}
				delete node;
			}
			else if(node->left!=NULL && node->right==NULL)
			{
				//If node is the left child of its parent, set parent's left child to node's left child
				if(node->parent->left==node)
				{
					node->parent->left=node->left;
				}
				//Else set parent's right child to node's left child
				else
				{
					node->parent->right=node->left;
				}
				delete node;
			}
			//If the node has two children
			else
			{
				//Find the successor of the node
				Node* successor=findMin(node->right);
				//Replace the node's key with the successor's key
				node->key=successor->key;
				//Remove the successor from the right subtree
				remove(successor->right, successor->key);
			}
		}
	}
	//If there are multiple contacts, remove the contact at the given index
	else
	{
		node->contactVector.erase(index-1);
	}
}
//Recursively search for a contact
Node* ContactBST::searchFor(Node* ptr, string key)
{
	if(ptr==NULL)
	{
		return NULL;
	}
	else if(key<ptr->key)
	{
		return searchFor(ptr->left, key);
	}
	else if(key>ptr->key)
	{
		return searchFor(ptr->right, key);
	}
	else
	{
		return ptr;
	}	
}
//Mark a contact as favorite
bool ContactBST::markFav(string key)
{
	Node* node=searchFor(root, key);
	if(node==NULL)
	{
		return false;
	}
	int index;
	node->print();
	cout<<"Enter index of the contact you want to mark as favorite: ";
	cin>>index;
	if(index>node->contactVector.size())
	{
		cout<<"Index out of range!!"<<endl;
	}
	else
	{
		node->contactVector.at(index-1)->isFav=1;
	}
	cout<<node->contactVector.at(index-1)->fname<<" "<<node->contactVector.at(index-1)->lname<<" "<<"has been marked as favorite!"<<endl;
	return true;
}
//Unmark a contact as favorite
bool ContactBST::unmarkFav(string key)
{
	Node* node=searchFor(root, key);
	if(node==NULL)
	{
		return false;
	}
	int index;
	node->print();
	cout<<"Enter index of the contact you want to unmark as favorite: ";
	cin>>index;
	if(index>node->contactVector.size())
	{
		cout<<"Index out of range!!"<<endl;
	}
	else
	{
		node->contactVector.at(index-1)->isFav=0;
	}
	cout<<node->contactVector.at(index-1)->fname<<" "<<node->contactVector.at(index-1)->lname<<" "<<"has been unmarked as favorite!"<<endl;
	return true;
}
//Print the contacts in an ascending order
void ContactBST::printASC(Node* ptr)
{
	if(ptr!=NULL)
	{
		printASC(ptr->left);
		for(int i=0; i<ptr->contactVector.size(); i++)
		{
			Contact* contact=ptr->contactVector.at(i);
			cout<<" "<<contact->fname<<","<<contact->lname<<","<<contact->email<<","<<contact->phone<<","<<contact->city<<","<<contact->country<<","<<contact->isFav<<endl;
		}
		printASC(ptr->right);
	}
}
//Print the contacts in an descending order
void ContactBST::printDES(Node* ptr)
{
	if(ptr!=NULL)
	{
		printDES(ptr->right);
		for(int i=0; i<ptr->contactVector.size(); i++)
		{
			Contact* contact=ptr->contactVector.at(i);
			cout<<" "<<contact->fname<<","<<contact->lname<<","<<contact->email<<","<<contact->phone<<","<<contact->city<<","<<contact->country<<","<<contact->isFav<<endl;
		}
		printDES(ptr->left);
	}
}
//Print all the favorite contacts in an ascending order
void ContactBST::printFav(Node* ptr)
{
	if(ptr!=NULL)
	{
		printFav(ptr->left);
		for(int i=0; i<ptr->contactVector.size(); i++)
		{
			Contact* contact=ptr->contactVector.at(i);
			if(ptr->contactVector.at(i)->isFav==1)
			{
				cout<<" "<<contact->fname<<","<<contact->lname<<","<<contact->email<<","<<contact->phone<<","<<contact->city<<","<<contact->country<<","<<contact->isFav<<endl;
			}
		}
		printFav(ptr->right);
	}
}
//Import a CSV file
int ContactBST::importCSV(string path)
{
	ifstream file;
	file.open(path);
	if(!file)
	{
		cout<<"Error: couldn't open file!"<<endl;
		return -1;
	}
	string line=" ";
	int counterimp;
	while(file)
	{
		counterimp++;
		getline(file, line);
		stringstream ss(line);
		string fname, lname, email, phone, city, country, isFav_str;
		string fullname;
		getline(ss, fname, ',');
		getline(ss, lname, ',');
		getline(ss, email, ',');
		getline(ss, phone, ',');
		getline(ss, city, ',');
		getline(ss, country, ',');
		getline(ss, isFav_str, ',');
		bool isFav=(isFav_str=="1");
		fullname=fname+" "+lname;
		Contact* contact=new Contact(fname, lname, email, phone, city, country, isFav);
		add(root, fullname, contact);
	}
	return counterimp;
}
//Export the contacts into a CSV file 
int ContactBST::exportCSV(Node* ptr, ofstream& file)
{
	//ofstream outfile;
	int counterexp;
	if(ptr!=NULL)
	{
		exportCSV(ptr->left, file);
		for(int i=0; i<ptr->contactVector.size(); i++)
		{
			counterexp++;
			Contact* contact=ptr->contactVector.at(i);
			file<<" "<<contact->fname<<","<<contact->lname<<","<<contact->email<<","<<contact->phone<<","<<contact->city<<","<<contact->country<<","<<contact->isFav<<endl;
		}
		exportCSV(ptr->right, file);
	}
	return counterexp;
}
//Recursively find the key with minimum
Node* ContactBST::findMin(Node* ptr)
{
	if(root==NULL)
	{
		return NULL;
	}
	else if(ptr->left==NULL)
	{
		return ptr;
	}
	else
	{
		return findMin(ptr->left);
	}
}
