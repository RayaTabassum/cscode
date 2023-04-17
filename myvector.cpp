#include<cstdlib>
#include<iomanip>
#include<fstream>
#include<sstream>
#include<stdexcept>
#include<iostream>
#include<vector>
#include "contact.h"
#include "myvector.h"
using namespace std;

template <typename T>
MyVector<T>::MyVector(int cap): v_size(0), v_capacity(cap), data(new T[cap])
{}

template <typename T>
MyVector<T>::~MyVector()
{
	delete[] data;
}
template <typename T>
void MyVector<T>::push_back(T element)
{
	if(v_capacity==v_size)
	{
		v_capacity=(v_capacity==0)?1:2*v_capacity;
		T* new_data=new T[v_capacity];
		for(int i=0; i<v_size; i++)
		{
			new_data[i]=data[i];
		}
		delete[] data;
		data=new_data;
	}
	data[v_size++]=element;
}
template <typename T>
void MyVector<T>::insert(int index, T element)
{
	if(index<0 || index>v_size)
	{
		cout<<"Index out of range!!"<<endl;
	}
	else if(v_capacity==v_size)
	{
		v_capacity=(v_capacity==0)?1:2*v_capacity;
		T* new_data=new T[v_capacity];
		for(int i=0; i<v_size; i++)
		{
			new_data[i]=data[i];
		}
		delete[] data;
		data=new_data;
	}
	for(int i=v_size; i>index; i--)
	{
		data[i]=data[i-1];
	}
	data[index]=element;
	v_size++;
}
template <typename T>
void MyVector<T>::erase(int index)
{
	if(index<0 || index>=v_size)
	{
		cout<<"Index out of range!!"<<endl;
	}
	for(int i=index; i<v_size-1; i++)
	{
		data[i]=data[i+1];
	}
	v_size--;
}
template <typename T>
T& MyVector<T>::at(int index)
{
	if(index<0 || index>=v_size)
	{
		cout<<"Index out of range!!"<<endl;
	}
	return data[index];
}
template <typename T>
const T& MyVector<T>::front()
{
	if(v_size==0)
	{
		cout<<"Vector is empty!!"<<endl;
	}
	return data[0];
}
template <typename T>
const T& MyVector<T>::back()
{
	if(v_size==0)
	{
		cout<<"Vector is empty!!"<<endl;
	}
	return data[v_size-1]; 
}
template <typename T>
int MyVector<T>::size() const
{
	return v_size;
}
template <typename T>
int MyVector<T>::capacity() const
{
	return v_capacity;
}
template <typename T>
bool MyVector<T>::empty() const
{
	return v_size==0;
}
template <typename T>
void MyVector<T>::shrink_to_fit()
{
	if(v_capacity>v_size)
	{
		v_capacity=v_size;
		T* temp= new T[v_capacity];
		for (int i=0; i<v_size; i++)
		{
			temp[i]=data[i];
		}
		delete[] data;
		data=temp;
	}
}
template <typename T>
void MyVector<T>::display()
{
	for(int i=0; i<v_size; i++)
	{
		cout<<data[i]<<" ";
	}
	cout<<endl;
}
template class MyVector<Contact*>;
