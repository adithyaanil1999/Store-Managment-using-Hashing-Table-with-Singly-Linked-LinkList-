#include <iostream>
#include <fstream>
#include <windows.h>
#define nmax 10
using namespace std;
struct hashnode//Defintion of node in the linked list
{
int id;
string name;
int quantity;
float price;
hashnode *next;
};
bool check_empty()
{
ifstream file;
file.open("record.txt");
char x;
file>>x;
if (isalpha(x)) //if file is empty=false
{
file.close();
return true;
}e
lse
{
file.close();
return false;
}
}c
lass hashmap
{p
rivate:
hashnode **htable;
int bill[100];
int billcount=0;
public:
hashmap()
{
htable=new hashnode*[nmax];
for(int i=0;i<nmax;i++)
htable[i]=NULL;
}
int hashfunc(int id) {
return id%nmax;
}v
oid push(int idno,string name,float price,int quantity)
{
int index=hashfunc(idno);
hashnode *first;
hashnode *prev;
first=new hashnode;
if(htable[index]==NULL)
{
prev=first;
htable[index]=first;
first->id=idno;
first->name=name;
first->price=price;
first->quantity=quantity;
first->next=NULL;
}e
lse
{
prev->next=first;
first->next=NULL;
prev=first;
first->id=idno;
first->name=name;
first->price=price;
first->quantity=quantity;
}
}
//function to pop an element out of the Linked list
void pop(int idS)
{
int index=hashfunc(idS);
// cout<<"\nindex: "<<index<<endl;
hashnode *prev=new hashnode;
hashnode *bottom=htable[index];
while(bottom!=NULL)
{
if(bottom->id==idS && bottom==htable[index])
{
htable[index]=NULL;
delete bottom;
break;
}
if(bottom->id!=idS)
{
prev=bottom;
bottom=bottom->next;
}e
lse
{
prev->next=bottom->next;
delete bottom;
break;
}
}
}
//fucntion to display the contents of the Linked list
void display()
{
hashnode *bottom=NULL;
for(int i=0;i<nmax;i++)
{
if(htable[i]!=NULL)
{
bottom=htable[i];
while(bottom!=NULL)
{
cout<<"Name: "<<bottom->name<<'\n'<<"id:
"<<bottom->id<<'\n';
cout<<"Price: "<<bottom-
>price<<endl<<"Quantity: "<<bottom->quantity<<"\n\n";
bottom=bottom->next;
}}
}
}
void updatefile()
{
hashnode *bottom;
ofstream file;
file.open("record.txt");
for(int i=0;i<nmax;i++)
{
if(htable[i]!=NULL)
{
bottom=htable[i];
while(bottom!=NULL)
{
file<<bottom->name<<'\n'<<bottom->id<<'\n';
file<<bottom->price<<'\n'<<bottom-
>quantity<<'\n';
bottom=bottom->next;
}
}
}f
ile.close();
}
float bill_find(int ids)
{
float total_price=0;
int index=hashfunc(ids);
hashnode *bottom=htable[index];
while(bottom!=NULL)
{
if(bottom->id==ids)
{
cout<<"Name: "<<bottom->name<<endl<<"id:
"<<bottom->id<<endl;
cout<<"Price: "<<bottom-
>price<<endl<<"Quantity: "<<bottom->quantity<<endl;
if(bottom->quantity!=0)
{
bottom->quantity--;
updatefile();
cout<<"\nNEW QUANTITY after Bill:
"<<bottom->quantity<<endl;
return bottom->price;
}e
lse
{
cout<<"Stock is empty for this item"<<endl;
}
} bottom=bottom->next;
}
}i
nt verifyID(int ids)
{
int flag=0;
int index=hashfunc(ids);
hashnode *bottom=htable[index];
while(bottom!=NULL)
{
if(bottom->id==ids)
{
return 0;
} bottom=bottom->next;
}i
f(flag==0)
return -1;
}i
nt Search(int ids)
{
int flag=0;
int index=hashfunc(ids);
hashnode *bottom=htable[index];
while(bottom!=NULL)
{
if(bottom->id==ids)
{
cout<<"\nItem found!\n";
return 0;
} bottom=bottom->next;
}i
f(flag==0)
return -1;
}
void bill_func(int ids)
{
bill[billcount]=ids;
billcount++;
}v
oid billing()
{
float total_price=0;
for(int i=0;i<billcount;i++)
{
total_price=total_price+bill_find(bill[i]);
}c
out<<"\nTotal price is: "<<total_price<<endl;
}
};
bool check_file()
{
ifstream file;
file.open("record.txt");
if (file)
{f
ile.close();
return true;
}
else
{
file.close();
return false;
}
}
int get_no_of_node()
{
int counter=0;
string line;
ifstream file("record.txt");
while (getline(file, line))
counter++;
file.close();
return counter/4;
}
int loadfile(hashmap &s)
{
int no_nodes=get_no_of_node();
int id_temp[no_nodes];
string nametemp[no_nodes];
float price_temp[no_nodes];
int quantity_temp[no_nodes];
ifstream filein;
filein.open("record.txt");
if(check_file()&&check_empty())
{ for(int i=0;i<no_nodes;i++)
{
filein>>nametemp[i]>>id_temp[i]>>price_temp[i]>>quantity_temp[i];
}f
or(int i=0;i<no_nodes;i++)
s.push(id_temp[i],nametemp[i],price_temp[i],quantity_temp[i]);
}e
lse
return -1;
}v
oid dest_file()
{
hashmap t;
t.updatefile();
}v
oid menu(hashmap &s,int vef)
{
int choice;
int idno;
int flag=-1;
int ids;
string namet;
float pricet;
int quantityt;
char ans;
retry:
system("cls");
for(int i=0;i<60;i++)
cout<<"*";
cout<<"\n\tALLMART department store Management";
cout<<endl;
cout<<"Press: \n1.To view items in the database\n2.To add
items into the database\n3.Bill processing\n4.Search for an
item\n5.To delete an item\n6.Exit";
cout<<"\n Enter your Choice: ";
if(vef!=-1)
cin>>choice;
else
{
cout<<"AUTO(2)";
choice=2;
}s
witch(choice)
{c
ase 1:
cout<<endl;
system("cls");
cout<<"\tThe Items in the database are:"<<endl;
s.display();
cout<<"\n\n";
system("pause");
goto retry;
break;
case 2:
cout<<endl;
if(vef!=-1)
system("cls");
else
{
cout<<"\nWARNING! The Database is empty or has not
been created yet!"<<endl;
cout<<"\nYou need to update database first!\n";
}c
out<<"\nAdd items to database\n";
do
{
cout<<"\nEnter the ID no of the product: ";
cin>>idno;
int dup=s.verifyID(idno);
if(dup!=0)
{
cout<<"\nEnter the name of the product: ";
cin>>namet;
cout<<"\nEnter the price of the product: ";
cin>>pricet;
cout<<"\nEnter the quantity of the product: ";
cin>>quantityt;
s.push(idno,namet,pricet,quantityt);
vef++;
} else
{
cout<<"\nThis ID no has been assigned to
another product already!\n";
}
cout<<"\nDo you want to continue?(y/n): ";
cin>>ans;
}while(ans=='y'||ans=='Y');
s.updatefile();
if(ans!='y'||ans!='Y')
goto retry;
break;
case 3:
if(vef!=-1)
system("cls");
flag=-1;
cout<<"\nBilling!\n";
do
{
cout<<"\nEnter the ID of the product:\n";
cin>>ids;
s.bill_func(ids);
cout<<"\nDo you want to continue?(y/n): ";
cin>>ans;
}while(ans=='y'||ans=='Y');
cout<<"\nTHE ITEMS BILLED ARE: "<<endl;
s.billing();
system("pause");
flag++;
if(ans!='y'||ans!='Y'&&flag!=-1)
goto retry;
break;
case 4:
if(vef!=-1)
system("cls");
cout<<"\nSearching!\n";
flag=-1;
do
{
cout<<"\nEnter the ID of the product to be
searched:\n";
cin>>ids;
flag=s.Search(ids);
if(flag==-1)
cout<<"\nItem not found!\n";
cout<<"\nDo you want to continue?(y/n): ";
cin>>ans;
}while(ans=='y'||ans=='Y');
if(ans!='y'||ans!='Y')
goto retry;
break;
case 5:
if(vef!=-1)
system("cls");
cout<<"\nDeletion!\n";
do
{
cout<<"\nEnter the ID of the product to be
deleted:\n";
cin>>ids;
flag=s.Search(ids);
if(flag==-1)
cout<<"\nItem not found!\n";
else
s.pop(ids);
cout<<"\nDo you want to continue?(y/n): ";
cin>>ans;
}while(ans=='y'||ans=='Y');
s.updatefile();
if(ans!='y'||ans!='Y')
goto retry;
break;
case 6:
if(vef!=-1)
system("cls");
cout<<"Exit!";
exit(0);
break;
default:
if(vef!=-1)
system("cls");
cout<<"Wrong option!";
goto retry;
break;
}
}
int main()
{
hashmap h;
if(!check_file())
h.updatefile();
int verify=loadfile(h);
menu(h,verify);
}