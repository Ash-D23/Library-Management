#include<fstream.h>
#include<iostream.h>
#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<string.h>
#include<iomanip.h>
#include<graphics.h>
#include<dir.h>
#include<dos.h>
class book{
public:
char bno[6];
char bookName[50]; //title of book
char authName[20]; //author of book

void create_book(){
cout<<"\n NEW BOOK ENTRY...\n";
cout<<"\n Enter Book Number: ";
cin>>bno;
cout<<"\n\n Enter Name of the Book: ";
gets(bookName);
cout<<"\n\n Enter Author's name: ";
gets(authName);
cout<<"\n\n\n Book Created...";
}

void show_book(){
cout<<"\n Book number:"<< bno;
cout<<"\n Book Name: ";
puts(bookName);
cout<<"Author Name: ";
puts(authName);
}

char* retbno(){ return bno; }

void report(){cout<<"   "<<bno<<setw(29)<<bookName<<setw(19)<<authName<<"\t\t"<<endl;}

}; //end of class book
class student{
public:
char admno[6]; //Admission number
char name[20]; //Name of the student
char stbno[6]; //Student Book number
int token;

void create_student(){
clrscr();
cout<<"\nNEW STUDENT ENTRY...\n";
cout<<"\nEnter Admission number: ";
cin>>admno;
cout << "\n\nEnter Name of Student: ";
gets(name);
token=0;
stbno[0]='/0';
cout<<"\n\nStudent Record Created..";
}

void show_student(){
cout<<"\nAdmission number: "<<admno;
cout<<"\nStudent Name: ";
puts(name);
cout<<"\nNumber of Book(s) issued: "<<token;
if(token==1) cout<<"\nBook No "<<stbno;
}

char* retadmno(){ return admno; }

char* retstbno(){ return stbno; }

int rettoken(){ return token; }

void addtoken(){ token=1; }

void resettoken(){ token=0; }

void getstbno(char t[]){strcpy(stbno,t);}

void report(){cout<<"\t"<<admno<<setw(20)<<name<<setw(10)<<token<<"\t\t"<<endl;}

};//end of class student


void write_student(){
char ch;
student s;
fstream f;
f.open("stud.dat",ios::binary|ios::app);
do{
s.create_student();
f.write((char*)&s,sizeof(s));
cout<<"\n\nDo you want to add more students...(y/n?)";
cin>>ch;
}while(ch=='y'||ch=='Y');
f.close();
}

void display_alls(){
clrscr();
student s;
fstream f;
f.open("stud.dat",ios::in|ios::binary);
if(!f){
cout<<"ERROR!!! FILE COULD NOT BE OPEN ";
getch();
return;
}

cout<<"\n\n\t\tSTUDENT LIST\t\t\n\n";
cout<<"========================================================\n";
cout<<"\tAdmission No."<<setw(10)<<"Name"<<setw(20)<<"Book Issued\t\n";
cout<<"========================================================\n";

while(f.read((char*)&s,sizeof(s)))s.report();

f.close();
getch();
}
void display_sps(char n[]){
cout<<"\nSTUDENT DETAILS\n";
int flag=0;
student s;
fstream f;
f.open("stud.dat",ios::in|ios::binary);
while(f.read((char*)&s,sizeof(s))){
if((strcmp(s.retadmno(),n)==0)){
s.show_student();
flag=1;
}
}
f.close();
if(flag==0)cout<<"\n\nStudent does not exist";
getch();
}

void delete_student(){
char n[6];
int flag=0;
clrscr();
cout<<"\n\n\n\tDELETE STUDENT...";
cout<<"\n\nEnter The admission no. of the Student You Want To Delete : ";
cin>>n;
student s;
fstream f;
f.open("stud.dat",ios::in|ios::out|ios::binary);
fstream f2;
f2.open("Temc.dat",ios::out|ios::binary);
f.seekg(0,ios::beg);
while(f.read((char*)&s,sizeof(s))){
if(strcmp(s.retadmno(),n)!=0)f2.write((char*)&s,sizeof(s));
else flag=1;
}

f2.close();
f.close();
remove("stud.dat");
rename("Temc.dat","stud.dat");
if(flag==1)cout<<"\n\n\tRecord Deleted ..";
else {cout<<"\n\nRecord not found";  }
getch();

}

//BOOK


void write_book(){
char ch;
book b;
fstream f;
f.open("bk.dat",ios::binary|ios::app);
do{
clrscr();
b.create_book();
f.write((char*)&b,sizeof(b));
cout<<"\n\nDo you want to add more books...(y/n?)";
cin>>ch;
}while(ch=='y'||ch=='Y');
f.close();
}

void display_allb(){
clrscr();
book b;
fstream f;
f.open("bk.dat",ios::in|ios::binary);
if(!f){
cout<<"ERROR!!! FILE COULD NOT BE OPEN ";
getch();
return;
}
cout<<"\n\n\t\tBook LIST\t\t\n\n";
cout<<"================================================================\n";
cout<<"  Book Number"<<setw(20)<<"Book Name"<<setw(22)<<"Author\t\t\n";
cout<<"================================================================\n";
while(f.read((char*)&b,sizeof(b)))b.report();
f.close();
getch();
}
void display_spb(char n[]){
cout<<"\nBOOK DETAILS\n";
int flag=0;
book b;
fstream f;
f.open("bk.dat",ios::in|ios::binary);
while(f.read((char*)&b,sizeof(b))){
if(strcmp(b.retbno(),n)==0){
b.show_book();
flag=1;
}
}

f.close();
if(flag==0)cout<<"\n\nBook does not exist";
getch();
}

void delete_book(){
char n[6];
clrscr();
cout<<"\n\n\n\tDELETE BOOK ...";
cout<<"\n\nEnter Book number of Book to Delete : ";
cin >> n;
book b;
fstream f;
f.open("bk.dat",ios::in|ios::app|ios::binary);
fstream f2;
f2.open("Te.dat",ios::app);
f.seekg(0,ios::beg);
while(f.read((char*)&b,sizeof(b)))if(strcmp(b.retbno(),n)!=0)                          f2.write((char*)&b, sizeof(b));
f2.close();
f.close();
remove("bk.dat");
rename("Te.dat","bk.dat");
cout<<"\n\n\tRecord Deleted ..";
getch();
}

void book_issue(){
char sn[6], bn[6];
int found=0,flag=0;
clrscr();
student s;
book b;
cout<<"\n\nBOOK ISSUE ...";
cout<<"\n\n\tEnter Student's Admission number : ";
cin>>sn;
fstream f;
fstream f1;
f.open("stud.dat",ios::in|ios::out|ios::binary);
f1.open("bk.dat", ios::in|ios::out|ios::binary);
while(f.read((char*)&s,sizeof(s))&&(found==0)){
if(strcmp(s.retadmno(),sn)==0){
found=1;
if(s.rettoken()==0){
cout<<"\n\n\tEnter Book number : ";
cin>>bn;
while(f1.read((char*)&b,sizeof(b))&&(flag==0)){
if(strcmpi(b.retbno(),bn)==0){
b.show_book();
flag=1;
s.addtoken();
s.getstbno(b.retbno());
int pos=-1*sizeof(s);
f.seekp(pos,ios::cur);
f.write((char*)&s,sizeof(s));
cout<<"\n\n\t Book issued successfully\n\nPlease Note: Write the current date in backside of your book \n and submit within 15 days. Fine Rs.10 for each day \n after 15 days period";
}
}
if(flag==0)cout<<"Book number does not exist";
}
else cout<<"You have not returned the last book ";

}
}
if(found==0)cout<<"Student record not exist...";
getch();
f.close();
f1.close();
}

void book_deposit()
{
char sn[6],bn[6];
int found=0,flag=0,day,fine;
clrscr();
student s;
book b;
cout<<"\n\nBOOK DEPOSIT ...";
cout<<"\n\n\tEnter Students Admission number : ";
cin>>sn;
fstream f;
f.open("stud.dat",ios::in|ios::out|ios::binary);
fstream f1;
f1.open("bk.dat",ios::in|ios::out|ios::binary);
while(f.read((char*)&s,sizeof(s))&&(found==0)){
if(strcmp(s.retadmno(),sn)==0){
found=1;
if(s.rettoken()==1){
while(f1.read((char*)&b,sizeof(b))&&(flag==0)){
if(strcmp(b.retbno(),s.retstbno())==0){
b.show_book();
flag=1;
cout<<"\n\nBook deposited in no. of days : ";
cin>>day;
if(day>15){
fine=(day-15)*10;
cout<<"\n\nFine to be deposited is Rs. "<<fine;
}
s.resettoken();
int pos=-1*sizeof(s);
f.seekp(pos,ios::cur);
f.write((char*)&s,sizeof(s));
cout<<"\n\n\t Book deposited successfully";
}
}
if(flag==0)cout<<"Book no does not exist";
}
else cout<<"No book is issued..please check!!";
}
}
if(found==0)cout<<"Student record not exist...";
getch();
f.close();
f1.close();
}

void admin_menu(){
clrscr();
int ch2;
cout<<"\n\n\n\tADMINISTRATOR MENU";
cout<<"\n\n\t(1) CREATE STUDENT RECORD";
cout<<"\n\n\t(2) DISPLAY ALL STUDENTS RECORD";
cout<<"\n\n\t(3) DISPLAY SPECIFIC STUDENT RECORD ";
cout<<"\n\n\t(4) DELETE STUDENT RECORD";
cout<<"\n\n\t(5) CREATE BOOK ";
cout<<"\n\n\t(6) DISPLAY ALL BOOKS ";
cout<<"\n\n\t(7) DISPLAY SPECIFIC BOOK ";
cout<<"\n\n\t(8) DELETE BOOK ";
cout<<"\n\n\t(9) BACK TO MAIN MENU";
cout<<"\n\n\tPlease Enter Your Choice (1-9) ";
cin>>ch2;
switch(ch2){
case 1:
clrscr();
write_student();
break;
case 2:
display_alls();
break;
case 3:
char nume[6];
clrscr();
cout<<"\n\n\tPlease Enter The Admission No. ";
cin>>nume;
display_sps(nume);
break;
case 4:
delete_student();
break;
case 5:
clrscr();
write_book();
break;
case 6:
display_allb();
break;
case 7:
char num[6];
clrscr();
cout<<"\n\n\tPlease Enter The book No. ";
cin>>num;
display_spb(num);
break;
case 8:
delete_book();
break;
case 9: return;
default: cout<<"\nWrong choice!!!";
}
admin_menu(); //recursion
}
void credit()
{
 clrscr();
 cout<<"\n\n\n\t\t\t     Welcome To School Library\t\t\t\t";
getch();
 }
void menu()
{clrscr();
 char ch;
do{
clrscr();
cout<<"\n\n\n\tMAIN MENU";
cout<<"\n\n\t(1) BOOK ISSUE";
cout<<"\n\n\t(2) BOOK DEPOSIT";
cout<<"\n\n\t(3) ADMINISTRATOR MENU";
cout<<"\n\n\t(4) Instructions";
cout<<"\n\n\t(5) Exit";
cout<<"\n\n\tPlease Select Your Option (1-4) ";
ch=getch();
switch(ch){
case '1':
clrscr();
book_issue();
break;
case '2':
book_deposit();
break;
case '3':
admin_menu();
break;
case '4':{       clrscr();
cout<<"\n\t\t\t\tInstructions\t\t\t";
cout<<"\n\n\n\t1.This Program maintains a record of students who have taken books";
cout<<"\n\t  from the library";
cout<<"\n\t2.A Student can borrow only 1 book at a time.";
cout<<"\n\t3.Student should return the book to the library within 15 days ";
cout<<"\n\t  if not they have to pay fine of Rs.10 per day.";
cout<<"\n\t4.Each book in the library contains many copies.";
cout<<"\n\t5.If the book returned is not in proper condition as before or";
cout<<"\n\t  student has lost the book then the student has to pay  the";
cout<<"\n\t  cost of the book.";
getch();
menu();

}
case '5': exit(0);
default :{  clrscr();
cout<<"\n wrong choice";
}
}//end of switch
}while(ch!='5');

getch();
}

void main()
{
clrscr();
int gdriver=DETECT,gmode;
initgraph(&gdriver,&gmode,"c:\\tc\\bgi");
setbkcolor(RED);
setcolor(RED);
clearviewport();
credit();
menu();
closegraph();
}
