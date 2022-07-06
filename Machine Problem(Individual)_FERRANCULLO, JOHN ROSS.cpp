#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <array>
#include <iomanip>
#define MAX 100

using namespace std;

//Structure data for voter profile
typedef struct voter{
    string firstN;                          //for first name
    string lastN;                           //for last name
    string course;                          //for course
    string pw;                              //for account password
    string id;                              //for student id
    string pres;                            //voting history data for president
    string vp;                              //voting history data for vice president
    string sec;                             //voting history data for secretary
    struct voter *next;                     //pointer for structure next element
}VOT;

class record{

private:
    VOT *vt;                                //structure pointer declaration

public:
    void makenull();                        //makenull function
    void add(VOT y);                        //add function - use user inputted data to be add in the record
    void addHis(VOT y);                     //voter history data insert function
    void login();                           //login function
    void card();                            //function for usb drive insert checker
    void history();                         //display function for voter history
    void retrieve();                        //retrieve function - retrieve data from .dbf file
    void save();                            //save function - store data to .dbf file
    void reg();                             //voter data registration function
    int isempty();                          //determine if list is empty
    int votingMenu();                       //menu

};

void record::makenull(){
    vt = NULL;                              //set structure to NULL
}

int record::isempty(){
    return(vt == NULL);                     //return resulting value of st==NULL
}

void record::add(VOT y){
    VOT *p, *q, *temp;                      //declare a pointer p(for current record in the structure), q (for previous record), temp (for temporary data storage) for structure
    p=q=vt;                                 //make p and q equal to vt
    temp=new VOT;                           //allocate memory for new element in the structure and set it to temp

    temp->firstN = y.firstN;
    temp->lastN = y.lastN;                  //populate structure with the user inputted data from add menu.
    temp->course = y.course;                //temp will be pointing to the specific location to store each data
    temp->id = y.id;
    temp->pw = y.pw;

    while(p!=NULL && p->lastN < y.lastN){
        q=p;                                //sort list based on the last name of the students in the list
        p=p->next;
    }

    if(p==vt){
        vt=temp;                            //if p == temp, temp address = vt
    }
    else{
        q->next=temp;                       //else address of q pointing to the next element will be = to temp
    }

    temp->next=p;                           //temp pointing to next = p
    cout << endl;

}

void record::addHis(VOT y){
    VOT *p, *q;                             //declare a pointer p(for current record in the structure), q (for previous record)
    p=q=vt;                                 //make p and q equal to vt

    while(p!=NULL){

        p->pres = y.pres;                   //where p is last pointing in the structure store voting history in address of pres, vp, and sec
        p->vp = y.vp;
        p->sec = y.sec;                     //point p to the next element in the structure
        p=p->next;
    }
}

void record::login(){
    fstream f;
    VOT y, *p;
    std::array <std::string, MAX> temp{};   //define array temp
    int n, a=0, i=0, j=0;
    char choice;
    char c=' ';
    char pword[10];                         //char pword with 10 size

    system("cls");
    cout << endl << "================================================================================" << endl;
    cout << "\t\t\t   Enter Password: ";

    while(i<10){
        pword[i]=getch();                   //store input in pword
        c=pword[i];                         //copy data stored in pword to c

        if(c==13){
            break;                          //check if c is equal to 13 -  if true break from while loop
        }
        else{
            cout << "*";                    //if false display * in every input
        }

        i++;                                //increment index
    }

    pword[i]='\0';                          //set pword to null pointer
    i=0;                                    //declare i = 0

    f.open("E:\\Student profile.dbf", ios::in); //open file in the card

    if(!f){
        f.open("E:\\Student profile.dbf", ios::out);    //if file is nonexistent, create file
    }
    else{
        while(true){
            f >> y.firstN >> y.lastN >> y.id >> y.course >> y.pw;   //save data from file to structure

            if(f.eof()){
                break;                      //if file reach eof, break from loop
            }

            temp[j] = y.pw;                 //copy data from structure y.pw to temp with the index of current number of j

            if(pword==temp[j]){             //compare pword to temp
                system("cls");
                cout << endl << "================================================================================" << endl;
                cout << "\t                WELCOME TO STUDENT VOTING SYSTEM!!!";
                cout << endl << "================================================================================" << endl << endl;
                cout << "\t\t\tYou have already voted!" << endl << endl;
                cout << "\t\t\tThank you for using our program." << endl << endl;           //if pword is equal to temp display you've already voted, then terminate program
                cout << "\t\t\tTermination program..." << endl;
                getch();
                exit(0);
            }

            j++;                            //increment j for next password compare in temp[j]
            flush(f);
        }
    }

    f.close();                              //close file
    flush(f);

    int k;
    p=vt;

    while(p!=NULL && p->pw!=pword){
        p=p->next;                          //locate data corresponding to pword
    }

    if(p==NULL){
        cout << endl << endl;
        cout << "\t\t\t   INCORRECT PASSWORD!!" << endl;
        cout << endl << "\t\t\t   Register to Vote?(Y/N): ";        //ask user if he/she want to register to vote, this is if the user inputted password is incorrect
        cin >> choice;

        switch(toupper(choice)){
        case 'Y':
            reg();                          //if Y go to registration
            break;
        case 'N':
            login();                        //if N loop back to login
            break;
        default:
            cout << endl << "\t\t\t\tInvalid choice" << endl;
            getch();
        }

    }
    else{
        cout << endl << endl << endl;
        cout << "\t\t\t   WELCOME!!";
        cout << "\n\n\n\n\n\n\n\n\n\n\t\t\t   Press any key to continue....!!" << endl; //if login is correct procced
        cout << "================================================================================" << endl;
        getch();
    }
}

//Insert Card(usb drive)
void record::card(){
    fstream f;

    while(true)                                                  //loop
    {
        f.open("E:\\Student profile.dbf", ios::in);              //open file in loop
        if(!f)
        {
            system("cls");
            cout << "Please insert card";
            getch();

            system("cls");
            cout << "Please insert card.";                       //if file is null - display please insert card (usb drive)
            getch();

            system("cls");
            cout << "Please insert card..";
            getch();

            system("cls");
            cout << "Please insert card...";
            getch();
        }
        else                                                    //if file exist continue and break from loop
        {
            cout << "\n================================================================================" << endl;
            cout << "\n\n\n\t                WELCOME TO STUDENT VOTING SYSTEM!!!         ";
            cout << "\n\n\n\n\n\n\n\n================================================================================" << endl;
            getch();
            break;
        }

    }
    flush(f);                                                   //flush file buffer
    f.close();                                                  //close file
}

void record::history(){
    VOT *p;
    string pr, v, s;

    p=vt;
    system("cls");

    if(isempty()){
        cout << endl << "\t\t\tHistory is empty.";              //call isempty function then determined value returned
        getch();
    }
    else{
        cout << endl << "================================================================================" << endl;
        cout << "\t\t                  VOTING HISTORY";                                                                 //if false branch out to voting history
        cout << endl << "================================================================================";

        while(p!=NULL){
            pr = p->pres;
            v = p->vp;                                          //store data to pr, v, and s from structure where p is pointing to
            s = p->sec;
            p = p->next;                                        //move p pointer to the next element in the structure
        }
            cout << endl << "\t\t\t\tFor President:" << endl;
            cout << "\t\t\t\t" << pr << endl;

            cout << endl << "\t\t\t\tFor Vice President:" << endl;  //display pr, v, and s
            cout << "\t\t\t\t" << v << endl;

            cout << endl << "\t\t\t\tSecretary:" << endl;
            cout << "\t\t\t\t" << s << endl;
    }
}

void record::retrieve(){
    fstream f;

    VOT x;

    f.open("E:\\Student profile.dbf",ios::in);                  //open file for data retrieve
    if(!f){
        f.open("E:\\Student profile.dbf", ios::out);            //if file is NULL create dbf file
    }
    else{
        while(true){
            f >> x.firstN >> x.lastN >> x.id >> x.course >> x.pw;   //read first name, last name, student id, course and password from file
            if(f.eof()){
                break;                                          //if pointer reach end of file - break loop
            }
            add(x);                                             //pass data read from file to add() function to be inserted in structure record
        }
    }

    f.close();                                                  //close file
}

void record::save(){
    fstream f;
    VOT *p;
    p=vt;


    f.open("E:\\Student profile.dbf", ios::out);                //open dbf file for saving data
    while(p!=NULL){
        f << p->firstN << " " << p->lastN << " " << p->id << " " << p->course << " " << p->pw << endl;  //save first name, last name, student id, course, and password from record to dbf file
        p=p->next;                                              //move pointer to the next record for file data read
    }
    f.close();                                                  //close file
}

void record::reg(){
    VOT a;

    system("cls");

    cout << "\n================================================================================\n";
    cout << "\t\t                   REGISTER MODE         ";
    cout << "\n================================================================================\n";
    cout << "\t\t\tInput Required Information\n";

    cout << "\n\t\t\tFirst Name: ";
    cin >> a.firstN;                                                                                        //enter first name then store in a.firstN
    cout << "\n\t\t\tLast Name: ";
    cin >> a.lastN;                                                                                         //enter last name then store in a.lastN
    cout << "\n\t\t\tStudent ID: ";
    cin >> a.id;                                                                                            //enter student id then store in a.id
    cout << "\n\t\t\tCourse(abbrev. only): ";
    cin >> a.course;                                                                                        //enter course then store in a.course
    cout << "\n\t\t\tPassword(5 digits): ";
    cin >> a.pw;                                                                                            //enter password then store in a.pw
    cout << "\n\t  The information is successfully added. You are now registered!";
    cout << "\n================================================================================";

    add(a);                                                     //pass data in VOT a to add function
    getch();
    login();                                                    //call log in function
}

int record::votingMenu(){
    int i, op;

    system("cls");
    cout << "\n================================================================================\n";
    cout << "\t\t          STUDENT VOTING SYSTEM MENU      ";
    cout << "\n================================================================================";
    cout << "\n\t\t\t   1. Student Election\n";                                                                //display voting menu
    cout << "\n\t\t\t   2. Voting History\n";
    cout << "\n\t\t\t   3. Exit\n";

    cout << "\n\t\t\t   Select 1-3: ";
    cin >> op;                                                  //store data enter in op

    return(op);                                                 //return op value

}

int main(){
    VOT y;
    record s;                                                   //declare public class elements in main
    int i, op, c1, c2, c3, p=0;
    char confirm;
    char c=' ';
    char pword[10];

    std::array <std::string, 2> pres {"Frenzy Reyes", "Rasheed Riga"};
    std::array <std::string, 2> vp {"Angelo Andres", "Joshua Garcia"};              //candidates stored in array using array class
    std::array <std::string, 2> sec {"Jeorge Dans", "Mika Gajeto"};

    system("COLOR B4");                                         //change console background and foreground color
    s.makenull();                                               //call makenull function
    s.retrieve();                                               //call retrieve function
    s.card();                                                   //call card function
    s.login();                                                  //call login function

    system("cls");
    while(true)                                                 //loop set to always true
    {
        op=s.votingMenu();                                      //call voting menu and store return value into op
        switch(op)                                              //switch case using op
        {
        case 1:                                                 //case 1 voting system,

            system("cls");
            cout << "\n================================================================================\n";
            cout << "\t\t                   VOTE WISELY         ";
            cout << "\n================================================================================";
            cout << "\n\t\tWho would you like to be the next President?\n" << endl;
            for(i=0;i<2;i++)
            {
                std::cout << setw(20) << i+1 << " ." << pres[i] << endl;                                        //display elements in array pres
            }
            while(true)
            {
                cout << "\n\t\tEnter the number of your choice!: ";                                             //while loop set to always true - ask user to whom he/she will vote for pres
                cin >> c1;                                                                                      //store choice in c1
                if(c1>2)
                {
                    cout << "\n\t\tUnknown input." << endl;                                                     //if c1 > 2 display unknown input and continue to loop
                    getch();
                }
                else
                {
                    break;                                                                                      //else break from loop
                }
            }
            y.pres = pres[c1-1];                                                                                //store data from array pres with index of c1 -1 to structure y

            system("cls");
            cout << "\n================================================================================\n";
            cout << "\t\t                   VOTE WISELY         ";
            cout << "\n================================================================================";
            cout << "\n\t\tWho would you like to be the next Vice President?\n" << endl;
            for(i=0;i<2;i++)
            {
                std::cout << setw(20) << i+1 << " ." << vp[i] << endl;                                          //display elements in array vp
            }
            while(true)
            {
                cout << "\n\t\tEnter the number of your choice!: ";                                             //while loop set to always true - ask user to whom he/she will vote for vp
                cin >> c2;                                                                                      //store choice in c2
                if(c2>2)
                {
                    cout << "\n\t\tUnknown input." << endl;                                                     //if c2 > 2 display unknown input and continue to loop
                    getch();
                }
                else
                {
                    break;                                                                                      //else break from loop
                }
            }
            y.vp = vp[c2-1];                                                                                    //store data from array vp with index of c2-1 to structure y

            system("cls");
            cout << "\n================================================================================\n";
            cout << "\t\t                   VOTE WISELY         ";
            cout << "\n================================================================================";
            cout << "\n\t\tWho would you like to be the next Secretary?\n" << endl;
            for(i=0;i<2;i++)
            {
                std::cout << setw(20) << i+1 << " ." << sec[i] << endl;                                         //display elements in array vp
            }
            while(true)
            {
                cout << "\n\t\tEnter the number of your choice!: ";                                             //while loop set to always true - ask user to whom he/she will vote for sec
                cin >> c3;                                                                                      //store choice in c3
                if(c3>2)
                {
                    cout << "\n\t\tUnknown input." << endl;                                                     //if c3 > 2 display unknown input and continue to loop
                    getch();
                }
                else
                {
                    break;                                                                                      //else break from loop
                }
            }
            y.sec = sec[c3-1];                                                                                  //store data from array sec with index of c3-1 to structure y

            system("cls");
            cout << "\n================================================================================\n";
            cout << "\t\t                   VOTE WISELY         ";
            cout << "\n================================================================================";
            cout << "\n\t\t\tREMINDER: YOU CAN ONLY VOTE ONCE!" << endl;
            cout << "\n\t\tONCE YOU'VE VOTED YOU CANNOT LOGIN YOUR ACCOUNT AGAIN TO VOTE!" << endl;
            cout << "\n\t\t\tDo you want to continue?(Y/N): ";                                                  //voting confirmation
            cin >> confirm;

            switch(toupper(confirm))
            {
                case 'Y':                                                                   //if user enter Y

                    cout << "\n\t\tEnter your password to confirm your vote: ";             //user password confirmation

                    while(p<10)
                    {
                        pword[p] = getch();
                        c = pword[p];
                        if(c == 13)
                        {
                            break;                                                          //hide inputted password in ***** same with login function
                        }
                        else
                        {
                            cout << "*";
                        }
                        p++;
                    }

                    pword[p]='\0';
                    p=0;

                    y.pw = pword;                                                           //store password to structure y
                    break;

                case 'N':                                                                   //if user enter N
                    system("pause");
                    exit(0);                                                                //terminate program
                default:
                    cout << "\n\t\tUnknown input!" << endl;                                 //unknown input repeat loop
                    getch();
            }
            s.addHis(y);                                                                    //pass data from structure y to addhis function
            break;

        case 2:
            s.history();                                                                    //call voting history function
            getch();
            break;

        case 3:
            s.save();                                                                       //call save function
            exit(0);                                                                        //terminate program

        default:
            cout << "\n\t\t\tSelect 1-3 only!.\n";                                          //invalid input repeat loop
            getch();
        }
    }

return(0);
}
