
auto x = 27;                    //情景三（x既不是指针也不是引用）
const auto cx = x;              //情景三（cx也一样）
const auto & rx=cx;             //情景一（rx是非通用引用）

/*================================================================================================*/
auto&& uref1 = x;               //x是int左值，
                                //所以uref1类型为int&
auto&& uref2 = cx;              //cx是const int左值，
                                //所以uref2类型为const int&
auto&& uref3 = 27;              //27是int右值，
                                //所以uref3类型为int&&

/*================================================================================================*/
const char name[] =             //name的类型是const char[13]
 "R. N. Briggs";

auto arr1 = name;               //arr1的类型是const char*
auto& arr2 = name;              //arr2的类型是const char (&)[13]

void someFunc(int, double);     //someFunc是一个函数，
                                //类型为void(int, double)

auto func1 = someFunc;          //func1的类型是void (*)(int, double)
auto& func2 = someFunc;         //func2的类型是void (&)(int, double)


/*================================================================================================*/
//如果你想声明一个带有初始值27的int，C++98提供两种语法选择
int x1 = 27;
int x2(27);
//C++11由于也添加了用于支持统一初始化（uniform initialization）的语法：
int x3 = { 27 };
int x4{ 27 };
//总之，这四种不同的语法只会产生一个相同的结果：变量类型为int值为27

auto x1 = 27;                   //类型是int，值是27
auto x2(27);                    //同上
auto x3 = { 27 };               //类型是std::initializer_list<int>，
                                //值是{ 27 }
auto x4{ 27 };                  //同上
//这些声明都能通过编译，但是他们不像替换之前那样有相同的意义。前面两个语句确实声明了一个类型为int值为27的变量，但是后面两个声明了一个存储一个元素27的 std::initializer_list<int>类型的变量。


//对于花括号的处理是auto类型推导和模板类型推导唯一不同的地方。当使用auto声明的变量使用花括号的语法进行初始化的时候，会推导出std::initializer_list<T>的实例化，但是对于模板类型推导这样就行不通：
auto x = { 11, 23, 9 };         //x的类型是std::initializer_list<int>

template<typename T>            //带有与x的声明等价的
void f(T param);                //形参声明的模板

f({ 11, 23, 9 });               //错误！不能推导出T

//然而如果在模板中指定T是std::initializer_list<T>而留下未知T,模板类型推导就能正常工作：
template<typename T>
void f(std::initializer_list<T> initList);

f({ 11, 23, 9 });               //T被推导为int，initList的类型为
                                //std::initializer_list<int>

//C++14允许auto用于函数返回值并会被推导，而且C++14的lambda函数也允许在形参声明中使用auto。但是在这些情况下auto实际上使用模板类型推导的那一套规则在工作，而不是auto类型推导，所以说下面这样的代码不会通过编译：
auto createInitList()
{
    return { 1, 2, 3 };         //错误！不能推导{ 1, 2, 3 }的类型
}

//同样在C++14的lambda函数中这样使用auto也不能通过编译：
std::vector<int> v;
…
auto resetV = [&v](const auto& newValue){ v = newValue; };        //C++14
…
resetV({ 1, 2, 3 });            //错误！不能推导{ 1, 2, 3 }的类型
/*================================================================================================*/

请记住：

* auto类型推导通常和模板类型推导相同，但是auto类型推导假定花括号初始化代表std::initializer_list，而模板类型推导不这样做
* 在C++14中auto允许出现在函数返回值或者lambda函数形参中，但是它的工作机制是模板类型推导那一套方案，而不是auto类型推导









