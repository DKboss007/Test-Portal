#include<iostream>
#include<cstring>
#include<fstream>
using namespace std;

class QuestionPaper
{
    char paperChoice;
    string answerText,resultText;

    void inputSubject();
    void inputAnswer();
    void setSubject(ifstream &);
    void display();
    void displayAnswer();
public:
    void select();
    void result();
};

class login: public QuestionPaper
{
    string name;
    string userName;
    string password;
    void signUp();
    void signIn();
public:
    void userLogin(login &);
};


void login::signUp()
{
    string tempUserName;
    int condition = 1;
    while(condition==1)
    {
        cout<<"\nStudent Sign Up\n";
        cout<<"Name :";
        cin>>name;
        cout<<"User Name :";
        cin>>tempUserName;
        if(tempUserName==userName)
        {
            cout<<"\nUser Name already Exist!\n";
            continue;
        }
        userName = tempUserName;
        cout<<"Password :";
        cin>>password;
        cout<<"\nSign Up Successful!\n";
        condition = 0;
    }
}

void login::signIn()
{
    string tempUserName;
    string tempPassword;
    int condition = 1;

    while(condition == 1)
    {
        int response = 1;
        cout<<"\nStudent Sign In\n";
        cout<<"User Name :";
        cin>>tempUserName;
        cout<<"Password :";
        cin>>tempPassword;
        if(tempUserName==userName&&tempPassword==password)
        {
            cout<<"Login Successful!\n";
            cout<<"\nHello "<<name<<endl;
            condition = 0;
        }
        else
        {
            cout<<"Login Failed!\n";
            cout<<"1. Retry     2.Sign Up :";
            cin>>response;
            if(response == 1)
                continue;
            else
                signUp();
        }

    }
}

void login::userLogin(login &student_1)
{
    int choice;
    int condition = 1;
    while(condition==1)
    {
        cout<<"\n*-*-*-*Online Test Portal*-*-*-*\n";
        cout<<"\n1. SignUp\n2. SignIn\n";
        cout<<"Enter your choice :";
        cin>>choice;
        if(choice == 1)
        {
            student_1.signUp();
            cout<<"Please SignIn to Continue\n";
            continue;
        }
        else if(choice == 2)
            student_1.signIn();
        else
        {
            cout<<"Selection not Valid!\n";
            continue;
        }
        condition = 0;
    }
}


void QuestionPaper::select()
{
    cout<<"\nSelect the Subject\n";
    cout<<"1. C++\n2. C\n3. JAVA\n";
    cout<<"Choice :";
    cin>>paperChoice;
    cout<<endl;
    display();
}

void QuestionPaper::inputSubject()
{
    ofstream subject("Answer.txt",ios::out);
    subject.clear();
    subject.write((char *)&paperChoice,sizeof(char));
    subject.close();
}

void QuestionPaper::inputAnswer()
{
    char ans;
    ofstream ansInput("Answer.txt",ios::app|ios::out);
    cout<<"Answer :";
    cin>>ans;
    if(ans!='a'&&ans!='b'&&ans!='c'&&ans!='d')
    {
        cout<<"Invalid Option! Retry\n";
        inputAnswer();
    }
    else
    {
        ansInput.write((char *)&ans,sizeof(char));
        cout<<endl;
        ansInput.close();
    }
}

void QuestionPaper::setSubject(ifstream &question)
{
    switch(paperChoice)
    {
    case '1':
        question.open("Question1.txt",ios::in);
        answerText = "Answers for C++ test";
        resultText = "Result for C++ test";
        break;
    case '2':
        question.open("Question2.txt",ios::in);
        answerText = "Answers for C test";
        resultText = "Result for C test";
        break;
    case '3':
        question.open("Question3.txt",ios::in);
        answerText = "Answers for JAVA test";
        resultText = "Result for JAVA test";
        break;
    default:
        cout<<"No Question paper Present\n";
        select();
    }
}

void QuestionPaper::display()
{
    char ch;
    inputSubject();
    ifstream question;
    setSubject(question);
    question.seekg(0);
    question.get(ch);
    while(question.good())
    {
        while(ch!=')')
        {
            cout<<ch;
            question.get(ch);

        }
        inputAnswer();
        question.get(ch);
    }
    question.close();
}

void QuestionPaper::displayAnswer()
{
    char studentAnswer,adminAnswer,que;
    ifstream student_Answer("Answer.txt");
    ifstream admin_Answer("Answer Key.txt");
    ifstream question;
    student_Answer.seekg(0);
    admin_Answer.seekg(0);
    student_Answer.get(studentAnswer);
    admin_Answer.get(adminAnswer);
    while(adminAnswer!=studentAnswer)
    {
        admin_Answer.get(adminAnswer);
    }
    admin_Answer.get(adminAnswer);
    setSubject(question);
    cout<<answerText<<endl;
    cout<<endl;
    student_Answer.get(studentAnswer);
    question.seekg(0);
    question.get(que);
    while(question.good())
    {
        while(que!=')')
        {
            cout<<que;
            question.get(que);
        }
        question.get(que);
        cout<<"\nYour Answer :"<<studentAnswer<<endl;
        cout<<"Correct Answer :"<<adminAnswer<<endl;
        cout<<endl;
        student_Answer.get(studentAnswer);
        admin_Answer.get(adminAnswer);
    }

}

void QuestionPaper::result()
{
    char studentAnswer,adminAnswer;
    int choice = 2;
    int mark = 0,totalMark=5;
    ifstream student_Answer("Answer.txt");
    ifstream admin_Answer("Answer Key.txt");
    student_Answer.seekg(0);
    admin_Answer.seekg(0);
    student_Answer.get(studentAnswer);
    admin_Answer.get(adminAnswer);
    while(adminAnswer!=studentAnswer)
    {
        admin_Answer.get(adminAnswer);
    }
    admin_Answer.get(adminAnswer);
    cout<<resultText<<endl;
    student_Answer.get(studentAnswer);
    while(student_Answer.good())
    {
        if(studentAnswer==adminAnswer)
        {
            mark++;
        }
        student_Answer.get(studentAnswer);
        admin_Answer.get(adminAnswer);
    }
    student_Answer.close();
    admin_Answer.close();
    cout<<"Total Marks :"<<totalMark<<endl;
    cout<<"Marks obtain :"<<mark<<endl;
    cout<<endl;
    cout<<"1.Answer Sheet  2.End :";
    cin>>choice;
    if(choice==1)
    {
        cout<<"\n*-*-*Answer Sheet*-*-*\n\n";
        displayAnswer();
    }
}

int main()
{
    login student_1;
    student_1.userLogin(student_1);
    student_1.select();
    student_1.result();
    return 0;
}
