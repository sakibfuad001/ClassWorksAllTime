#include <iostream>
#include <stdio.h>
#include <string>
#include <cstring>

using namespace std;

class Bank
{
public:
    char* Bname;
    /*
    Implement necessary constructors and destructor
    */
    Bank(char *p)
    {
        Bname= new char[strlen(p)+1];
        strcpy(Bname, p);
    }


    Bank(const Bank &ob1)
    {
        Bname= new char[strlen(ob1.Bname)+1];
        strcpy(Bname, ob1.Bname);
    }

    ~Bank()
    {
        delete []Bname;
        cout<<"Destructing Bank"<<endl;
    }
};

class Person
{
    int age;
    char* Pname;
public:
    /*
    Implement necessary constructors and destructor
    */
    Person(char *p, int age_p)
    {

        Pname=new char[strlen(p)+1];
        strcpy(Pname, p);

        age= age_p;
    }

    Person(const Person &ob)
    {
        cout<<"In constructor for "<<ob.Pname<<endl;
        Pname= new char[strlen(ob.Pname)+1];
        strcpy(Pname, ob.Pname);

        age=ob.age;
    }
    ~Person()
    {
        delete []Pname;
    }

    char * get_pname()
    {
        return Pname;
    }

    virtual void show()
    {
        cout<<"Person name: "<<Pname<<endl;
        cout<<"Age: "<<age<<endl;
    }
};

class Customer;

class Employee:public Bank, public Person
{
    /*
    Employee is derived from both of Bank and Person
    */
protected:
    double salary;
    double incr;
public:
    int emp_card;
    /*
    Implement necessary constructors
    */

    Employee(char *p, char *q, int age_p, double salary_emp, double increm, int id):Bank(p), Person(q, age_p)
    {
        salary=salary_emp;
        incr=increm;
        emp_card=id;
        cout<<"Constructing Employee "<<emp_card<<" of bank "<<p<<endl;
    }
    Employee (Bank &ob1, Person &ob2, double salary_per, double increm, int id):Bank(ob1), Person(ob2)
    {
        cout<<"In constructor for "<<ob2.get_pname()<<endl;
        salary=salary_per;
        incr=increm;
        emp_card=id;
    }
    void show()
    {
        cout<<"Employee card: "<<emp_card<<endl;
        cout<<"Salary: "<<salary<<endl;
        cout<<"Earned increment: "<<incr<<endl;
    }

    friend void operator+(Employee &ob1, Customer &ob2);

};

class Customer:public Bank, public Person
{
    /*
    Employee is derived from both of Bank and Person
    */
protected:
    int purchase;
    double discount;
public:
    int cust_card;
    /*
    Implement necessary constructors
    */
    Customer(char *p, char *q, int age_p, int p_purchase, double p_dis, int card):Bank(p), Person(q, age_p)
    {
        purchase=p_purchase;
        discount = p_dis;
        cust_card=card;
        cout<<"Constructing Customer "<<cust_card<<" of bank "<<p<<endl;
    }

    Customer(Bank &ob1, Person &ob3, int p_purchase, double p_dis, int card):Bank(ob1), Person(ob3)
    {
        cout<<"In constructor for "<<ob3.get_pname()<<endl;
        purchase=p_purchase;
        discount = p_dis;
        cust_card=card;
    }

    void show()
    {
        cout<<"Customer card: "<<cust_card<<endl;
        cout<<"No. of purchase: "<<purchase<<endl;
        cout<<"Earned discount: " <<discount<<endl;
    }
    friend void operator+(Employee &ob1, Customer &ob2);
};

/*
*
Implement a friend + operator function
where,
discount = discount +  incr * purchase
and
salary = salary - purchase * 100
*
*/
void operator+(Employee &ob1, Customer &ob2)
{
    ob2.discount=ob2.discount+ob1.incr*ob2.purchase;
    ob1.salary=ob1.salary-ob2.purchase*100;
}

void display(Employee &emp, Customer &cust)
{
    cout<< "--------------------------------------"<<endl;
    emp.show();
    cout<<endl;
    cust.show();
    cout<< "--------------------------------------\n"<<endl;
}

int main()
{
    Bank bank("World Bank");//done
    Person person("Mr. X", 35);//done

    /*
    <bank_name>, <person_name>, <person_age>, <salary>, <increment>, <card_no>
    */
    Employee emp1("Brac Bank", "Mr. Y", 30, 30000, 500.5, 1340);//done
    /*
    <bank_name>, <person_name>, <person_age>, <no_of_purchase>, <discount>, <card_no>
    */
    Customer cust1("Brac Bank", "Mr. Z", 31, 9, 850.5, 3015);//done
    cout<< "\nModifying emp1 and cust1:\n";
    display(emp1, cust1);
    emp1 + cust1;
    display(emp1, cust1);

    /*
    <bank>, <person>, <salary>, <increment>, <card_no>
    */
    Employee emp2(bank, person, 44000, 480, 2119);//done
    /*
    <bank>, <person>, <no_of_purchase>, <discount>, <card_no>
    */
    Customer cust2(bank, person, 12, 370, 2219);//done
    cout<< "\n\nModifying emp2 and cust2:\n";
    display(emp2, cust2);
    emp2 + cust2;
    display(emp2, cust2);

    Person *p;
    p = &person;
    cout<< "--------------------------------------"<<endl;
    /*
    Implement necessary show() functions
    */
    p->show();
    p = &cust1;
    cout<< "--------------------------------------"<<endl;
    p->show();
    cout<< "--------------------------------------"<<endl;

    return 0;
}
