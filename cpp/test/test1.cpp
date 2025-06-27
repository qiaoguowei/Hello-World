#include <iostream>
#include <string>

using namespace std;

<<<<<<< HEAD
void test1()
{
    std::string client_id = "7a6ed187-920a-430c-8dfd-9b36be225613";
    std::string client_secret = "VrZ8Q~jVb0Sstct7_vi1Qz5pSx2-TFiNzKasbcp_";

    std::string m_postdata = "client_id=" + client_id + "&scope=https%3A%2F%2Foutlook.office365.com%2F.default&client_secret=" + client_secret + "&grant_type=client_credentials";

    cout << m_postdata << endl;
}

void test2()
{
    std::cout << MAX_NUMBER_OF_BYTES << std::endl;
}

int main()
{
    test2();
=======
int main()
{
    string str = ";matched policy uuid: []";

    cout << str << endl;
>>>>>>> 4adb3f20a968faa466b0157e6da162535c178879
}
