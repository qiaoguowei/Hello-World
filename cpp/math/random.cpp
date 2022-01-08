#include <iostream>
#include <cstdlib>
#include <vector>
#include <sys/types.h> 
#include <unistd.h>

template <int32_t max, typename T, class = typename std::enable_if<std::is_integral<T>::value>::type>
static std::vector<T> random(int32_t extract_count = max)                                                          
{
	std::vector<T> results;

	if (max <= 0 || extract_count <= 0 || extract_count > max)
	{
		return results;
	}

	results.resize(max);
	auto t = time(nullptr);
	srand(t*rand()%5+1);
	//srand(getpid());

	for (int32_t i = 1; i < max; ++i)
	{
		results[i] = i;
		int32_t randv = rand()%i;
		std::swap(results[i], results[randv%i]);
	}

	if (extract_count != max)
	{
		results.erase(results.begin() + extract_count, results.end());
	}
	return std::move(results);
}

int main()
{
	//while(1)
	{
		auto offsets = random<3, unsigned char>();
		for(int i = 0; i < 3; i++)
		{
			std::cout << (int)offsets[i] << ", ";
		}
		std::cout << std::endl;
//		sleep(1);
	}
}
