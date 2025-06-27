#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <iostream>
#include <sstream>

std::stringstream ss;

class person
{
public:
    person()
    {
    }

    person(int age)
        : age_(age)
    {
    }

    int age() const
    {
        return age_;
    }

private:
    friend class boost::serialization::access;

/*
    为了序列化用户定义类型的对话， serialize() 函数必须定义，它在对象序列化或从字节流中恢复是被调用
    由于 serialize () 函数既用来序列化又用来恢复数据， Boost.Serialization 除了 << 和 >> 之外还提供了 & 操作符
    如果使用这个操作符，就不再需要在 serialize() 函数中区分是序列化和恢复了。

    serialize () 在对象序列化或恢复时自动调用
    它应从来不被明确地调用，所以应声明为私有的
    这样的话， boost::serialization::access 类必须被声明为友元，以允许 Boost.Serialization 能够访问到这个函数
    有些情况下需要添加 serialize() 函数却不能修改现有的类。 比如，对于来自 C++ 标准库或其他库的类就是这样的。
 */
    template <typename Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & age_;
    }

private:
    int age_;
};

void save()
{
    boost::archive::text_oarchive oa(ss);
    person p(31);
    oa << p;
}

void load()
{
    boost::archive::text_iarchive ia(ss);
    person p;
    ia >> p;
    std::cout << p.age() << std::endl;
}

int main()
{
    save();
    load();
}




