#include <iostream>
#include <string>
#include <iterator>
#include <map>
#include <conio.h>

using namespace std;

map<string,int> product;
map<string,string> user;

void display(map<string,int> p)
{
    map<string,int>::iterator itr;
    cout<<"\n\tList of available products\n";
    cout<<"\tProduct\tPrice\n";
    for(itr=p.begin();itr!=p.end();itr++)
    {
        cout<<"\t"<<itr->first<<"\tRs."<<itr->second<<"\n";
    }
}

int displayc(map<string,map<int,int>> p)
{
    map<string,map<int,int>>::iterator itr;
    map<int,int>::iterator ptr;
    int cost=0;
    cout<<"\nProduct\tQuantity\tPrice\n";
    for(itr=p.begin();itr!=p.end();itr++)
    {
        ptr=itr->second.begin();
        {
            cout<<itr->first<<"\t   "<<ptr->first<<"\t\t Rs."<<ptr->second;
            cout<<"\n";
            cost+=ptr->second;
        }

    }
    return cost;
}

class amazon
{
    string name;
    string id;
    string password;
    string addr;
    string acno;
    string pin;
    map<string,map<int,int>>cart;
    int bal;
public:
    void create()
    {
        cout<<"\n\t********Enter Account Details*********\n";
        cout<<"\n\tName: ";cin>>name;
        cout<<"\n\tID: ";cin>>id;
        pass:
        cout<<"\n\tPassword: ";cin>>password;
        if(password.length()<8){cout<<"\nPassword cannot be less than 8 characters!!!";goto pass;}
        cout<<"\n\tAddress: ";cin>>addr;
        cout<<"\n\tAccount No: ";cin>>acno;
        p:
        cout<<"\n\tPin: ";cin>>pin;
        if(pin.length()!=4){cout<<"\nPin should be 4 characters long";goto p;}
        bal=1000;
        user.insert(pair<string,string>(id,password));
        cout<<"\n\n\tYour account has been created!!!";
    }
    void operator+(map<string,int> p)
    {
        string prod;int flag=-1,n;char ch;
        display(p);
        add:
        cout<<"\nEnter the product: ";cin>>prod;
        map<string,int>::iterator itr;
        for(itr=p.begin();itr!=p.end();itr++)
        {
            if(itr->first==prod)
            {
                flag=0;
                cout<<"\nNo of product: ";cin>>n;
                cart[prod][n]=itr->second*n;
                break;
            }
        }
        if(flag==-1){cout<<"\n\tNo such product found!!!";}
        cout<<"\nDo you like to add more(y/n): ";cin>>ch;
        if(ch=='y')goto add;
        cout<<"\n\tProducts Added to cart!!!";cout<<"\nYour cart";displayc(cart);
    }
    void operator-()
    {
        string prod;int flag=-1,n;char ch;
        int cost=displayc(cart);
        remove:
        cout<<"\nEnter the product: ";cin>>prod;
        map<string,map<int,int>>::iterator itr;
        for(itr=cart.begin();itr!=cart.end();itr++)
        {
            if(itr->first==prod)
            {
                flag=0;
                cart.erase(prod);
                break;
            }
        }
        if(flag==-1){cout<<"\n\tNo such product found!!!";}
        cout<<"\nDo you like to remove more(y/n): ";cin>>ch;
        if(ch=='y')goto remove;
        cout<<"\nYour cart";displayc(cart);
    }
    void operator++()
    {
        int amt;string p;
        cout<<"\nEnter Amount to be added to wallet: ";cin>>amt;
        pi:
        cout<<"\nEnter your pin: ";cin>>p;
        if(p==pin)
        {
            bal+=amt;
            cout<<"\n\tAmount added successfully";
            cout<<"\nCurrent Balance: Rs."<<bal;
        }
        else{cout<<"\n\tInvalid pin!!!";goto pi;}
    }
    void operator--()
    {
        char ch;string id,pass;int flag=-1;
        uid:
        cout<<"\nUser ID: ";cin>>id;
        map<string,string>::iterator itr;
        for(itr=user.begin();itr!=user.end();itr++)
        {
            if(itr->first==id)
            {
                flag=0;
                p:
                cout<<"\nPassword: ";cin>>pass;
                if(itr->second==pass){flag=1;break;}
                cout<<"\n\tInvalid password!!!";
                goto p;
            }
        }
        if(flag==1)
        {
            string pi;int cost;
            if(cart.empty()){cout<<"\n\tYour cart is empty!!!";return;}
            cout<<"\n\tYour Order";
            cost=displayc(cart);
            cout<<"\nTotal cost: Rs."<<cost;
            cout<<"\n\n\tProceeding to pay";
            epi:
            cout<<"\nEnter your wallet pin: ";cin>>pi;
            try
            {
                if(pi==pin){int res=place(pi,cost);if(!res) throw bal;}
                else goto epi;
            }
            catch(int b)
            {
                char ch;
                cout<<"\nDo you like to add money to your wallet(y/n): ";cin>>ch;
                if(ch=='y'){add();cout<<"\n\tPlacing your order";place(pi,cost);}
                else{cout<<"\n\tSorry order is dropped due to insufficient balance!!!";}
            }
        }
        else if(flag!=0){cout<<"\n\tInvalid User ID!!!";goto uid;}
    }

    int place(string pi,int cost)
    {
        cout<<"\nBalance: Rs."<<bal;
        if(bal<cost) return 0;
        bal-=cost;
        cout<<"\n\tYour Order is placed!!";
        cout<<"\n\tCurrent Balance: Rs."<<bal;
        return 1;
    }
    void add()
    {
        int amt;string p;
        cout<<"\nEnter Amount to be added to wallet: ";cin>>amt;
        pi:
        cout<<"\nEnter your pin: ";cin>>p;
        if(p==this->pin){this->bal+=amt;cout<<"\n\tAmount added successfully";cout<<"\nCurrent Balance: Rs."<<bal;}
        else goto pi;
    }
    void print()
    {
        cout<<"\n\t*********Account Details*********";
        cout<<"\nName: "<<name;
        cout<<"\nID: "<<id;
        cout<<"\nAddress: "<<addr;
        cout<<"\nWallet Balance: Rs."<<bal;
    }
};
int menu()
{
    int n;
    cout<<"\n\t***********MENU***********";
    cout<<"\n\t1) Create account";
    cout<<"\n\t2) Add to cart";
    cout<<"\n\t3) Remove from cart";
    cout<<"\n\t4) Add to wallet";
    cout<<"\n\t5) Place order";
    cout<<"\n\t6) View account";
    cout<<"\n\t7) Exit";
    cout<<"\nEnter your choice(1-6): ";
    cin>>n;
    return n;
}


int main()
{
    product.insert(pair<string,int>("A",500));
    product.insert(pair<string,int>("B",300));
    product.insert(pair<string,int>("C",800));
    product.insert(pair<string,int>("D",1500));
    product.insert(pair<string,int>("E",1000));
    amazon a[10];int count=-1;int cr=0;
    int ch;
    do
    {
        //system("cls");
        ch=menu();
        //system("cls");
        switch(ch)
        {
            case 1:a[++count].create();cr=1;break;
            case 2:if(!cr){cout<<"\nPlease create account before you proceed!!\n";a[++count].create();cr=1;}a[count]+product;break;
            case 3:if(!cr){cout<<"\nPlease create account before you proceed!!\n";a[++count].create();cr=1;}-a[count];break;
            case 4:if(!cr){cout<<"\nPlease create account before you proceed!!\n";a[++count].create();cr=1;}++a[count];break;
            case 5:if(!cr){cout<<"\nPlease create account before you proceed!!\n";a[++count].create();cr=1;}--a[count];break;
            case 6:if(!cr){cout<<"\nPlease create account before you proceed!!\n";a[++count].create();cr=1;}a[count].print();break;
            case 7:exit(0);
            default:cout<<"\n\tInvalid choice!!!";break;
        }
        getch();
    }
    while(ch!=7);

    return 0;
}
