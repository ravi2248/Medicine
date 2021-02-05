#include<iostream>
#include<fstream>
#include<string>
using namespace std;
static int count=0;   //static or global variable

/*---------------------------------------------------------------------------------------
---------------------------------------Base class----------------------------------------
-----------------------------------------------------------------------------------------*/

class Medicine   // 1 Base class(Hierarchical inheritance)
{
	string *name,*password;//defaultly these are private members.
	public:
	Medicine()//default constructor which compiler can arrange without definning.
	{	}
	string *l,*del;
	int i=0,*num;
	char med[30];
	inline void login();//inline member function
};
/*--------------------login---------------------*/
inline void Medicine::login()
{
	cout<<"WELCOME TO MEDICAL RECORD MANAGEMENT SYSTEM"<<endl;
	cout<<"First you have to login for security purpose"<<endl<<endl;
	cout<<"enter the username of your's : \n";
	name=new string;//allocating memory with dynamically.
	cin>>*name;
	cout<<"enter the password :\n";
	password=new string;
	cin>>*password;
	if(*name=="ravi"&&*password=="ravihari")
	{
		cout<<"Now You can\
 proceed\n\n<-------------------------------------WELCOME---------------------------------------->"<<endl<<endl<<endl;
		count++;
	}
	else
	{
		cout<<endl<<"Entered username or password are incorrect"<<endl;
		cout<<"Please Try again";
	}
	delete name;//deallocating memory
	delete password;
}

/*---------------------------------------------------------------------------------------
---------------------------------------Derived class 1-----------------------------------
-----------------------------------------------------------------------------------------*/

class Adding:private Medicine
{
	public:
		Adding()//constructor is invoked when the object is created
		{
			cout<<endl<<"enter how many medicine u want to enter : ";
			num=new int;
			cin>>*num;
			ofstream fout;
			fout.open("medicine_list.txt",ios::app);
			for(i=0;i<*num;i++)
			{
				cout<<"enter medicine : ";
				cin>>med;
				fout<<med<<endl;
				cout<<"Stored"<<endl;
			}
			delete num;
			//if we doesn't close the file, it atomatically closed when the block is end.
		}
};

/*---------------------------------------------------------------------------------------
---------------------------------------Derived class 2-----------------------------------
-----------------------------------------------------------------------------------------*/

class Seeing:private Medicine
{
	public:
		void see()//calling with object of Seeing
		{
			ifstream fin;
			fin.open("medicine_list.txt");
			if(fin.is_open())
			{
				while(!fin.eof())
				{
					l=new string;
					getline(fin,*l);
					cout<<*l<<endl;
				}
			fin.close();
			}
			else
			cout<<"Unable to open this file."<<endl;
			delete l;
		}
};

/*---------------------------------------------------------------------------------------
---------------------------------------Derived class 3-----------------------------------
-----------------------------------------------------------------------------------------*/

class Searching:private Medicine
{
	public:
		static void search()//static member function
		{
			int a=0;
			string line,*search;
			cout<<"Enter the medicine name which u want to search : ";
			search=new string;
			cin>>*search;
			ifstream fin("medicine_list.txt");
			if(fin.is_open())//is_open() is used to check the file is opening or not
			{
				while(!fin.eof())
				{
					getline(fin,line);
					if(*search==line)//checking the medicine is available or not
					{
						cout<<"Medicine is available in stock"<<" ("<<line<<")"<<endl;
						a=1;
					}	
				}
				if(a!=1)
				{
					cout<<"Sorry Medicine is out of stock";
				}
				fin.close();
				delete search;
			}
		}
};

/*---------------------------------------------------------------------------------------
---------------------------------------Derived class 4-----------------------------------
-----------------------------------------------------------------------------------------*/

class Deleting:private Medicine
{
	public:
		int operator++(int)//operator overloading(for post increment)
		{
			cout<<"enter the name of the medicine which u want to delete : ";
			del=new string;
			cin>>*del;
			ifstream fin("medicine_list.txt");
			ofstream fout("text.txt");
			while(!fin.eof())
			{
				l=new string;
				getline(fin,*l);
				if(*del==*l)
				{
					cout<<"Medicine is available in stock"<<" ("<<*l<<")"<<" and deleted"<<endl;
				}
				else 
				fout<<*l<<endl;
			}
			fin.close();
			fout.close();
			remove("medicine_list.txt");//we are deleting the file.
			rename("text.txt","medicine_list.txt");//we are giving rename(old file name) to the new file.
			delete del;
			delete l;
		}
};

/*---------------------------------------------------------------------------------------
---------------------------------------Derived class 5-----------------------------------
-----------------------------------------------------------------------------------------*/

class Updating:private Medicine
{
	public:
		friend void operator%(Updating u,Updating u1)//friend operator member function definition
		{
			string *update,up,str;
			cout<<"enter which medicine u want to update : ";
			update=new string;
			cin>>*update;
			ifstream fin("medicine_list.txt");
			ofstream fout("text.txt");
			while(!fin.eof())
			{
				getline(fin,str);
				if(*update==str)
				{
					cout<<"enter the medicine name : ";
					cin>>up;
					fout<<up<<endl;
					cout<<"Medicine is available in stock"<<" ("<<str<<")"<<" and updated"<<endl;
				}
				else 
				fout<<str<<endl;
			}
			fin.close();
			fout.close();
			remove("medicine_list.txt");
			rename("text.txt","medicine_list.txt");
			delete update;
		}
};

/*---------------------------------------------------------------------------------------
---------------------------------------Main function-------------------------------------
-----------------------------------------------------------------------------------------*/

main()
{
	Medicine m;
	m.login();//member function calling
	try//exception handling
	{
		if(count==1)
		{
			string x;
			cout<<"\nif you want to add medicines enter 'yes' otherwise 'no' : ";
			cin>>x;
			if(x=="yes")
			{
				Adding a;//constructor call
			}
			cout<<"\nif you want to see medicines enter 'yes' otherwise 'no' : ";
			cin>>x;
			if(x=="yes")
			{
				Seeing s;
				s.see();//calling function with object.
			}
			cout<<"\nif you want to search medicine enter 'yes' otherwise 'no' : ";
			cin>>x;
			if(x=="yes")
			{
				Searching s2;
				Searching::search();//static member fuction call
			}
			cout<<"\nif you want to delete any medicine enter 'yes' otherwise 'no' : ";
			cin>>x;
			if(x=="yes")
			{
				Deleting d;
				d++;//post increment operator call
			}
			cout<<"\nif you want to update any medicine enter 'yes' otherwise 'no' : ";
			cin>>x;
			if(x=="yes")
			{
				Updating u;
				operator%(u,u);//friend operator call
			}
		}
		else 
		throw(count);//it throws that variable to catch
	}	
	catch(int i)
	{
		cout<<endl<<"Exception is occured with your username and password\n";
	}
}
