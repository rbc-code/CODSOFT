#include<iostream>
using namespace std;
int main()
{
    int n1,n2,press;
    cout<<"Press 1 ='+'\n Press 2='-'\n Press 3='X'\n Press 4='/'\n ";
    cin>>press;
    cout<<"Enter 1st Number :";
    cin>>n1;
    cout<<"Enter 2nd Number :";
    cin>>n2;
    switch(press)
    {
        case 1:
        cout<<"Addition :"<<n1+n2;
        break;
        case 2:
        cout<<"Subtraction :"<<n1-n2;
        break;
        case 3:
        cout<<"Multiplication :"<<n1*n2;
        break;
        case 4:
        cout<<"Division :"<<n1/n2;
    }
    return 888;

    
}