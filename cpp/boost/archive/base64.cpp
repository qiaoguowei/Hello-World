#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <cstring>

using namespace std;

bool base64Encode(const std::string& input, std::string *output)
{
    if (input.empty() || nullptr == output)
    {
        return true;
    }

    typedef boost::archive::iterators::base64_from_binary<boost::archive::iterators::transform_width<std::string::const_iterator, 6, 8>> Base64EncodeIterator;
    std::stringstream result;

    std::copy(Base64EncodeIterator(input.begin()), Base64EncodeIterator(input.end()), std::ostream_iterator<char>(result));
    size_t equal_count = (3 - input.size()%3) % 3;
    for (size_t i = 0; i < equal_count; ++i)
    {
        result.put('=');
    }

    *output = result.str();

    return !output->empty();
}

bool base64Decode(const std::string& input, std::string *output)
{
    if (input.empty() || nullptr == output)
        return true;

    if (input.size() < 4)
        return false;

    size_t pos = input.size();
    for (size_t i = 2; i > 0; --i)
    {
        if (input[input.size() - i] == '=')
        {
            pos -= i;
            break;
        }
    }

    typedef boost::archive::iterators::transform_width<boost::archive::iterators::binary_from_base64<std::string::const_iterator>, 8, 6> Base64DecodeIterator;
    std::stringstream result;

    try
    {
        std::copy(Base64DecodeIterator(input.begin()), Base64DecodeIterator(input.begin()+pos), std::ostream_iterator<char>(result));
    }
    catch (std::exception& e)
    {
        cout << e.what() << endl;
        return false;
    }

    *output = result.str();

    return !output->empty();
}

int main(int argc, char *argv[])
{
    string inputFileName = argv[1];
    ifstream fin(inputFileName, ios::in | ios::binary);
    if (!fin.is_open())
    {
        cout << "open file failed." << endl;
        return -1; 
    }

    fin.seekg(0, std::ios_base::end);
    unsigned int inputLength = fin.tellg();
    fin.seekg(0, std::ios_base::beg);
    unsigned char *inputBuf = new unsigned char[inputLength];

        unsigned int readBytes = 0;
    while (!fin.eof() && readBytes < inputLength)
    {
        fin.read((char *)inputBuf + readBytes, inputLength - readBytes);
        if (fin.fail())
        {
            cout << "failed to read data from file stream." << endl;
            delete [] inputBuf;
        }
        readBytes += fin.gcount();
    }
    fin.close();

    string input(reinterpret_cast<char *>(inputBuf), inputLength);
    string output;

    if (!strncmp(argv[2], "0", 1))
        base64Decode(input, &output);
    else if (!strncmp(argv[2], "1", 1))
        base64Encode(input, &output);

    cout << output << endl;
}
