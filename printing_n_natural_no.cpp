// recursive function to print n natural numbers

#include<iostream>
using namespace std;

void fun1(int n)
{
    if(n>0)
    {
        fun1(n-1);
        cout<<n<<endl;
    }
}

// in reverse order
void fun2(int n)
{
    if(n>0)
    {
        cout<<n<<endl;
        fun2(n-1);
    }
}

int main()
{
    fun1(5);
    return 0;
}