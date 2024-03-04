#include <iostream>
#include <string>
#include <initializer_list>
#include <vector>

using namespace std;

enum class jsonType
{
    jsonTypeNull,
    jsonTypeInt,
    jsonTypeLong,
    jsonTypeDouble,
    jsonTypeBool,
    jsonTypeString,
    jsonTypeArray,
    jsonTypeObject
};

struct jsonNode
{
    jsonNode(const char *key, const char *value)
        : m_type(jsonType::jsonTypeString),
          m_key(key),
          m_value(value)
    {
        cout << "jsonNode constructor1 called." << endl;
    }

    jsonNode(const char *key, double value)
        : m_type(jsonType::jsonTypeDouble),
          m_key(key),
          m_value(std::to_string(value))
    {
        cout << "jsonNode constructor2 called." << endl;
    }

    jsonType        m_type;
    std::string     m_key;
    std::string     m_value;
};

class json
{
public:
    static json& array(std::initializer_list<jsonNode> nodes)
    {
        m_json.m_nodes.clear();
        m_json.m_nodes.insert(m_json.m_nodes.end(), nodes.begin(), nodes.end());

        cout << "json::array() called." << endl;

        return m_json;
    }

    json()
    {
    }

    ~json()
    {
    }

    std::string toString()
    {
        size_t size = m_nodes.size();
        for (size_t i = 0; i < size; ++i)
        {
            switch (m_nodes[i].m_type)
            {
                //根据类型组成一个json字符串
                case jsonType::jsonTypeDouble:
                    break;
            }
        }
        return std::string();
    }

    void print()
    {
        for (auto& x : m_nodes)
        {
            cout << x.m_key << " : " << x.m_value << endl;
        }
    }

private:
    std::vector<jsonNode>   m_nodes;
    static json             m_json;
};

json json::m_json;

int main()
{
    json array_not_object = json::array({{"currency", "USD"}, {"value", 42.99}});
    array_not_object.print();

    return 0;
}













