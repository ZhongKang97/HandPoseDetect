#include<iostream>
#include<boost/lexical_cast.hpp>
using namespace std;
int main(int argc,char** argv)
{
    string s="1000";
    int a=boost::lexical_cast<int>(s);
    int b=1;
    cout<<"a+b="<<a+b<<endl;
    return 0;
}