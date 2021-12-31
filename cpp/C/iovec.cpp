#include <iostream>
#include <cstring>
#include <cstdio>
#include <sys/uio.h>
#include <vector>

void set_iovec(struct iovec& iov, void *part, unsigned long len)
{
	iov.iov_base = part;
	iov.iov_len = (size_t)len;
}

int main()
{
	std::vector<struct iovec> vc;

	char part1[] = "[";
	char part2[] = "This is from writev";
	int part3 = 65;

	struct iovec io_tmp;
	set_iovec(io_tmp, (void *)part1, (unsigned long)strlen(part1));
	vc.push_back(io_tmp);
	set_iovec(io_tmp, (void *)part2, (unsigned long)strlen(part2));
	vc.push_back(io_tmp);
	set_iovec(io_tmp, (void *)&part3, (unsigned long)sizeof(int));
	vc.push_back(io_tmp);

	int result = writev(1, &vc[0], vc.size());
	std::cout << std::endl;
	std::cout << "result : " << result << std::endl;
}
