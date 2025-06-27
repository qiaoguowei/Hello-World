#include <iostream>
#include <thrift/transport/TBufferTransports.h>
#include <memory>

using namespace std;
using namespace apache::thrift::transport;

int main()
{
	string str1 = "abcdefghijklmn";
	std::shared_ptr<TMemoryBuffer> rbuf(new TMemoryBuffer((uint8_t*)str1.c_str(), str1.size()));
	//uint8_t *buf = nullptr;
	//uint32_t buf_size;

	//rbuf->getBuffer(&buf, &buf_size);

	//cout << buf_size << endl;
	//cout << (char*)buf << endl;
	//
	string str2 = rbuf->getBufferAsString();
	cout << str2 << endl;

	rbuf->appendBufferToString(str2);
	cout << str2 << endl;

	cout << rbuf->getBufferSize() << endl;

	str1[0] = 'z';
	cout << rbuf->getBufferAsString() << endl;
}
