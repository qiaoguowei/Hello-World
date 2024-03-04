#include <iostream>
#include <stack>
#include <string>

using namespace std;

int main()
{
    std::stack<std::pair<int, string>> mStack;
    mStack.push(make_pair(1, "aaa"));
    cout << mStack.top().first << ", " << mStack.top().second << endl;
    mStack.push(make_pair(2, "bbb"));
    cout << mStack.top().first << ", " << mStack.top().second << endl;
    mStack.push(make_pair(3, "ccc"));
    cout << mStack.top().first << ", " << mStack.top().second << endl;
    mStack.push(make_pair(4, "ddd"));
    cout << mStack.top().first << ", " << mStack.top().second << endl;
    mStack.push(make_pair(5, "eee"));
    cout << mStack.top().first << ", " << mStack.top().second << endl;
    mStack.push(make_pair(6, "fff"));
    cout << mStack.top().first << ", " << mStack.top().second << endl;
    mStack.push(make_pair(7, "ggg"));
    cout << mStack.top().first << ", " << mStack.top().second << endl;

}
