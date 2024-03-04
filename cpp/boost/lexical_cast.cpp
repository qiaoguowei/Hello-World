#include <iostream>
#include <boost/lexical_cast.hpp>

using namespace std;

int main()
{
    int port = 9001;
    uint16_t m_port = boost::lexical_cast<uint16_t>(port);
    cout << m_port << endl;
}
