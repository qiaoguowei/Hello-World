#include <iostream>
using namespace std;

void testA(int *p)
{
    int b = 11;
    p= &b;
    cout << "aaaaaaa"<<*p;
}

class persion
{
    public:
        persion()
        {
            cout << "1111111"<<endl;
        }       

        persion(persion & a) = delete;

        virtual ~persion()
        {
            cout<<"222222222"<<endl;
        }
};

class student :public persion
{
    public:
        student()
        {
            cout << "333333333"<<endl;
        }       
        virtual ~student()
        {
            cout<<"44444444444"<<endl;
        }
};

bool isvalid(student& s)
{
    return true;    
}
int main()
{
    student s;
    isvalid(s);
    return 0;
}


