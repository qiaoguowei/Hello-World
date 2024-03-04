//我们将从一个简单的情况开始，没有任何令人惊讶的情况。相比模板类型推导和auto类型推导（参见Item1和Item2），decltype只是简单的返回名字或者表达式的类型：
const int i = 0;                //decltype(i)是const int

bool f(const Widget& w);        //decltype(w)是const Widget&
                                //decltype(f)是bool(const Widget&)

struct Point
{
    int x,y;                    //decltype(Point::x)是int
};                              //decltype(Point::y)是int

Widget w;                       //decltype(w)是Widget

if (f(w))…                      //decltype(f(w))是bool

template<typename T>            //std::vector的简化版本
class vector
{
public:
    …
    T& operator[](std::size_t index);
    …
};

vector<int> v;                  //decltype(v)是vector<int>
…
if (v[0] == 0)…                 //decltype(v[0])是int&

/*=================================================================================================*/
//对一个T类型的容器使用operator[] 通常会返回一个T&对象
//使用decltype使得我们很容易去实现它，这是我们写的第一个版本，使用decltype计算返回类型，这个模板需要改良，我们把这个推迟到后面：

template<typename Container, typename Index>    //可以工作，
auto authAndAccess(Container& c, Index i)       //但是需要改良
    ->decltype(c[i])
{
    authenticateUser();
    return c[i];
}
//函数名称前面的auto不会做任何的类型推导工作。相反的，他只是暗示使用了C++11的尾置返回类型语法，即在函数形参列表后面使用一个”->“符号指出函数的返回类型，尾置返回类型的好处是我们可以在函数返回类型中使用函数形参相关的信息。在authAndAccess函数中，我们使用c和i指定返回类型。如果我们按照传统语法把函数返回类型放在函数名称之前，c和i就未被声明所以不能使用。

//C++11允许自动推导单一语句的lambda表达式的返回类型， C++14扩展到允许自动推导所有的lambda表达式和函数，甚至它们内含多条语句。对于authAndAccess来说这意味着在C++14标准下我们可以忽略尾置返回类型，只留下一个auto。使用这种声明形式，auto标示这里会发生类型推导。更准确的说，编译器将会从函数实现中推导出函数的返回类型。

template<typename Container, typename Index>    //C++14版本，
auto authAndAccess(Container& c, Index i)       //不那么正确
{
    authenticateUser();
    return c[i];                                //从c[i]中推导返回类型
}
//Item2解释了函数返回类型中使用auto，编译器实际上是使用的模板类型推导的那套规则。如果那样的话这里就会有一些问题。正如我们之前讨论的，operator[]对于大多数T类型的容器会返回一个T&，但是Item1解释了在模板类型推导期间，表达式的引用性（reference-ness）会被忽略

//要想让authAndAccess像我们期待的那样工作，我们需要使用decltype类型推导来推导它的返回值，即指定authAndAccess应该返回一个和c[i]表达式类型一样的类型。C++期望在某些情况下当类型被暗示时需要使用decltype类型推导的规则，C++14通过使用decltype(auto)说明符使得这成为可能。我们第一次看见decltype(auto)可能觉得非常的矛盾（到底是decltype还是auto？），实际上我们可以这样解释它的意义：auto说明符表示这个类型将会被推导，decltype说明decltype的规则将会被用到这个推导过程中。因此我们可以这样写authAndAccess：

template<typename Container, typename Index>    //C++14版本，
decltype(auto)                                  //可以工作，
authAndAccess(Container& c, Index i)            //但是还需要
{                                               //改良
    authenticateUser();
    return c[i];
}

//现在authAndAccess将会真正的返回c[i]的类型。现在事情解决了，一般情况下c[i]返回T&，authAndAccess也会返回T&，特殊情况下c[i]返回一个对象，authAndAccess也会返回一个对象。


//decltype(auto)的使用不仅仅局限于函数返回类型，当你想对初始化表达式使用decltype推导的规则，你也可以使用：

Widget w;

const Widget& cw = w;

auto myWidget1 = cw;                    //auto类型推导
                                        //myWidget1的类型为Widget
decltype(auto) myWidget2 = cw;          //decltype类型推导
                                        //myWidget2的类型是const Widget&

//但是这里有两个问题困惑着你。一个是我之前提到的authAndAccess的改良至今都没有描述。让我们现在加上它。

//再看看C++14版本的authAndAccess声明：
template<typename Container, typename Index>
decltype(auto) authAndAccess(Container& c, Index i);

//我们还需要更新一下模板的实现，让它能听从Item25的告诫应用std::forward实现通用引用：
template<typename Container, typename Index>    //最终的C++14版本
decltype(auto)
    authAndAccess(Container&& c, Index i)
{
    authenticateUser();
    return std::forward<Container>(c)[i];
}

//这样就能对我们的期望交上一份满意的答卷，但是这要求编译器支持C++14。如果你没有这样的编译器，你还需要使用C++11版本的模板，它看起来和C++14版本的极为相似，除了你不得不指定函数返回类型之外：
template<typename Container, typename Index>    //最终的C++11版本
auto
authAndAccess(Container&& c, Index i)
    ->decltype(std::forward<Container>(c)[i])
{
    authenticateUser();
    return std::forward<Container>(c)[i];
}



//另一个问题是就像我在条款的开始唠叨的那样，decltype通常会产生你期望的结果，但并不总是这样。在极少数情况下它产生的结果可能让你很惊讶。老实说如果你不是一个大型库的实现者你不太可能会遇到这些异常情况。

//将decltype应用于变量名会产生该变量名的声明类型。虽然变量名都是左值表达式，但这不会影响decltype的行为。（译者注：这里是说对于单纯的变量名，decltype只会返回变量的声明类型）然而，对于比单纯的变量名更复杂的左值表达式，decltype可以确保报告的类型始终是左值引用。也就是说，如果一个不是单纯变量名的左值表达式的类型是T，那么decltype会把这个表达式的类型报告为T&。这几乎没有什么太大影响，因为大多数左值表达式的类型天生具备一个左值引用修饰符。例如，返回左值的函数总是返回左值引用。

//这个行为暗含的意义值得我们注意，在：
int x = 0;
//中，x是一个变量的名字，所以decltype(x)是int。但是如果用一个小括号包覆这个名字，比如这样(x) ，就会产生一个比名字更复杂的表达式。对于名字来说，x是一个左值，C++11定义了表达式(x)也是一个左值。因此decltype((x))是int&。用小括号覆盖一个名字可以改变decltype对于名字产生的结果。


//在C++11中这稍微有点奇怪，但是由于C++14允许了decltype(auto)的使用，这意味着你在函数返回语句中细微的改变就可以影响类型的推导：
decltype(auto) f1()
{
    int x = 0;
    …
    return x;                            //decltype(x）是int，所以f1返回int
}

decltype(auto) f2()
{
    int x = 0;
    return (x);                          //decltype((x))是int&，所以f2返回int&
}

//注意不仅f2的返回类型不同于f1，而且它还引用了一个局部变量！这样的代码将会把你送上未定义行为的特快列车，一辆你绝对不想上第二次的车。
//当使用decltype(auto)的时候一定要加倍的小心，在表达式中看起来无足轻重的细节将会影响到decltype(auto)的推导结果。为了确认类型推导是否产出了你想要的结果，请参见Item4描述的那些技术。

//同时你也不应该忽略decltype这块大蛋糕。没错，decltype（单独使用或者与auto一起用）可能会偶尔产生一些令人惊讶的结果，但那毕竟是少数情况。通常，decltype都会产生你想要的结果，尤其是当你对一个变量使用decltype时，因为在这种情况下，decltype只是做一件本分之事：它产出变量的声明类型。


请记住：

decltype总是不加修改的产生变量或者表达式的类型。
对于T类型的不是单纯的变量名的左值表达式，decltype总是产出T的引用即T&。
C++14支持decltype(auto)，就像auto一样，推导出类型，但是它使用decltype的规则进行推导。
