#include <memory>
#include <iostream>

//抽象接口
class ErasureConcept
{
public:
    virtual void execute() const = 0;
    virtual ~ErasureConcept() = default;
};

//模版派生类
template <typename T>
class ErasureModel : public ErasureConcept
{
public:
    ErasureModel(T obj) : impl_(std::move(obj)) {}
    void execute() const override { impl_(); }

private:
    T impl_;
};

//统一包装类
class ErasureWrapper
{
public:
    template <typename T>
    ErasureWrapper(T obj) : ptr_(std::make_unique<ErasureModel<T>>(std::move(obj))) {}

    void operator()() const
    {
        if (ptr_)
            ptr_->execute();
    }

private:
    std::unique_ptr<ErasureConcept> ptr_;
};


int main()
{
    ErasureWrapper f1([](){std::cout << "Lambda called\n"; });

    f1();
    return 0;
}










