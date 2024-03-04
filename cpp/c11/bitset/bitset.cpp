#include <iostream>
#include <string>
#include <bitset>

using namespace std;

int main()
{
    enum Color
    {
        red,
        yellow,
        green,
        blue,
        white,
        black,
        numColors
    };

    bitset<numColors> usedColors;
    usedColors.set(red);
    usedColors.set(blue);

    cout << "bitfield of used colors: " << usedColors << endl;
    cout << "number   of used colors: " << usedColors.count() << endl;
    cout << "bitfield of unused colors: " << ~usedColors << endl;

    //if any color is used
    if (usedColors.any())
    {
        for (int c = 0; c < numColors; ++c)
        {
            if (usedColors[c])
            {
                cout << c << " is used." << endl;
            }
        }
    }
}
