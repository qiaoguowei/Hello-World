#include <boost/system/error_code.hpp>

//using namespace boost::system;

class my_category : public boost::system::error_category
{
public:
	virtual const char *name() const BOOST_SYSTEM_NOEXCEPT
	{
		return "myapp_category";
	}

	virtual std::string message(int ev) const
	{
		std::string msg;
		switch(ev)
		{
			case 0 :
				msg = "OK";
				break;
			default :
				msg = "some error";
				break;
		}

		return msg;
	}
};
