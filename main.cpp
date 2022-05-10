#include <iostream>
#include <windows.h>
#include <mysql.h>
#include <sstream>
#include <iomanip>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <process.h>
#include <stdlib.h>
#include <unistd.h> // for sleep()
#define CLS() system("cls")
#define RULE(x) cout<<'\n'; for(int _=0;_<80;_++) cout<<x; cout<<'\n' //Outputs Horizontal Consisting of 'x's

using namespace std;

const char* hostname = "localhost";
const char* username = "root";
const char* password = "";
const char* database = "cppdb";
unsigned int port = 3306 ;
const char* unixsocket = NULL;
unsigned long clientflag = 0;

MYSQL* connectdatabase(){
    MYSQL* conn;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, hostname, username, password, database, port, unixsocket, clientflag);
    if(conn){
             cout<<"connected to database"<<endl;
             return conn;
             }
             else{
                cout<<"Failed to connect to database"<<endl;
                return conn;
             }
}

void load();
void gotoxy();

void gotoxy(int x, int y)
{
	COORD d;
	d.X = x;
	d.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), d);
}
void load()
{
	char a = 219;
	gotoxy(36, 14);
	cout << "Loading..."<< endl;
	gotoxy(30,16);
	for(int r =1; r<=20; r++)
	{
		for(int q=0; q<=20000000; q++);
		cout << a;
	}
}


insertion(MYSQL* conn){
    CLS();
    load();
    CLS();
    int qstate = 0;
    stringstream ss;
    string stu_name, roll_no, dob, address, phone_no, blood_grp;
    cout<<"Enter student name: "<<endl;
    cin>>stu_name;
    cout<<"Enter roll number: "<<endl;
    cin>>roll_no;
    cout<<"Enter date-of-birth: "<<endl;
    cin>>dob;
    cout<<"Enter address: "<<endl;
    cin>>address;
    cout<<"Enter phone number: "<<endl;
    cin>>phone_no;
    cout<<"Enter blood group: "<<endl;
    cin>>blood_grp;
    ss << "INSERT INTO student (student_name, roll_number, dob, address, phone_no, blood_group) VALUES ('"+stu_name+"', '"+roll_no+"', '"+dob+"', '"+address+"', '"+phone_no+"', '"+blood_grp+"')";
    string query = ss.str();
    const char* q = query.c_str();
    qstate = mysql_query(conn, q);
    if(qstate == 0){
        cout<<"record inserted... \n";
    }
    else{
        cout<<"failed to insert record... \n";
    }
}

display(MYSQL* conn){
    CLS();
    load();
    CLS();
    cout<<"\n\n\n"<<endl;
    MYSQL_ROW row;
    MYSQL_RES* res;
    if(conn){
        int qstate = mysql_query(conn, "SELECT * FROM student");
        if(!qstate){
            res = mysql_store_result(conn);
            int count = mysql_num_fields(res);
            while(row = mysql_fetch_row(res)){
                  for(int i=0;i<count;i++){
                        cout<<"\t"<<"|"<<row[i]<<"|";
                  }
                  cout<<endl;
        }
    }

}
else{
    cout<<"failed to fetch";
}
}

deletedb(MYSQL* conn){
    CLS();
    load();
    CLS();
    MYSQL_ROW row;
    MYSQL_RES* res;
    int qstate = 0;
    string roll_no;
    stringstream ss,sss;
    cout<<"enter the roll number of student record: ";
    cin>>roll_no;
    sss << "SELECT * FROM student WHERE roll_number = '"+roll_no+"' ";
    string query = sss.str();
    const char* q = query.c_str();
    mysql_query(conn, q);
    res = mysql_store_result(conn);
    int count = mysql_num_fields(res);
    my_ulonglong x = mysql_num_rows(res);
    if(x > 0)
        {
            ss << "DELETE FROM student WHERE roll_number = '"+roll_no+"' ";
            string query = ss.str();
            const char* q = query.c_str();
            qstate = mysql_query(conn, q);
            cout<< x <<" " << roll_no <<" " <<"Record Found! \n Deleted \n";

        }
    else{

        cout<<"No record found ";
    }
}

/*view(MYSQL* conn)
{
    MYSQL_ROW row;
    MYSQL_RES* res;
    int roll;
cout<<"enter student roll number to be searched: ";
cin>>roll;
int qstate = 0;
qstate = mysql_query(conn, "SELECT * FROM student WHERE roll_number = '"+roll+"' ");
if (!qstate)
    {
        res = mysql_store_result(conn);
        row = mysql_fetch_row(res);
        cout << "\n" << row[0] << "\t" << row[1] << "\t" << row[2] << "\t" << row[3] << "\n" "\t" << row[4] << "\n" "\t" << row[5] << "\n";
        }
        else
		{
			cout<<"record not found";
		}

}


update(MYSQL* conn)
{
    string st_name;
    string address;
    string dob;
    string blood;

    int x;
    int roll;
    int phone;

    if(conn){
        int qstate = 0;
        string name;
        cout<<"Enter the name to modify: ";
        cin>>name;

        cout<<"press 1 for name change: ";
        cout<<"press 2 for roll number change: ";
        cout<<"press 3 for DOB change: ";
        cout<<"press 4 for address change: ";
        cout<<"press 5 for phone number change: ";
        cout<<"press 6 for blood group change: ";

        cout<<"Enter your choice: ";
        cin>>x;

        if(x==1){
            cout<<"enter new name: "<<"";
            cin>>st_name;
            string ss;
            ss <<"UPDATE student SET student_name = "<<st_name<<"WHERE CODE ='"+name+"'";
            string query = ss.str();
            const char* q = query.c_str();
            qstate = mysql_query(conn, q);
            if(qstate==0){
                cout<<"\nrecord updated"<<endl;
            }
            else{
                cout<<"error";
            }
        }
    }

}*/


int main()
{
    load();
    CLS();
    cout<<"\n\n";
    string username;
    string password;
    char ch1;
    int choice;
    RULE("-");
    cout<<"Enter (1) for admin \t///\t Enter (2) for student"<<endl;
    RULE("-");
    cin>>choice;

    if(choice == 1){
        cout<<"\n\n";
        cout<<"Hello admin!!!"<<endl;
        cout<<"please enter user name: ";
        cin>>username;
        cout<<"please enter the password: ";
        cin>>password;

        if(username == "admin" && password == "admin")
        {
            CLS();
            cout<<"Welcome admin!!!"<<endl;
            int c;
            MYSQL* conn = connectdatabase();
            op:
            if(conn){
                RULE("*");
                cout<<"\n\t\t\t STUDENT MANAGEMENT SYSTEM \t\t\t\n";
                RULE("*");
                cout<<"\t\t\t\t1.INSERTION\n\t\t\t\t2.DISPLAY\n\t\t\t\t3.DELETE\n\t\t\t\t4.UPDATE\n\t\t\t\t6.EXIT\n\n";
                cin>>c;
                switch(c){
                    case 1:
                        insertion(conn);
                        goto op;
                        break;
                    case 2:
                        display(conn);
                        goto op;
                        break;
                    case 3:
                        deletedb(conn);
                        goto op;
                        break;
                    /*case 4:
                        view(conn);
                        goto op;
                        break;*/
                    /*case 5:
                        update(conn);
                        goto op;
                        break;*/
                    case 6:
                        CLS();
                        load();
                        CLS();
                        exit(0);
                        break;
                    default:
                        cout<<"please give the valid input"<<endl;
                        goto op;
                    }

            }
            insertion(conn);
            display(conn);
            return 0;
        }
        else{
            cout<<"Invalid login: pls try again";
            exit(0);
        }
    }
    if(choice == 2){
        cout<<"Hello student!!!"<<endl;
        MYSQL* conn = connectdatabase();
        /*view(conn);*/
    }
    else{
        cout<<"Invalid input!!!"<<endl;
        exit(0);
    }
}

