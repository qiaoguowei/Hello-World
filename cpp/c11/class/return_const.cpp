#include <iostream>

class A
{
public:
    void setLoggingLevel(const std::string& logging_level)
    {
        m_logging_level = logging_level;
    }

    std::string getLoggingLevel() const
    {
        return m_logging_level;
    }

private:
    std::string m_logging_level;
};

class B
{
public:
    void setA(const A& a)
    {
        m_a = a;
    }

    const A& getA() const
    {
        return m_a;
    }

private:
    A m_a;
};

int main()
{
    A a;
    a.setLoggingLevel("INFO");
    B b;
    b.setA(a);

    std::cout << b.getA().getLoggingLevel() << std::endl;

    A& aa = const_cast<A&>(b.getA());
    aa.setLoggingLevel("DEBUG");
    std::cout << b.getA().getLoggingLevel() << std::endl;
}










