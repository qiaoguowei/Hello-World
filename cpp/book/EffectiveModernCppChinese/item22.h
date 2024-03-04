#ifndef _QGW_WIDGET_H
#define _QGW_WIDGET_H

#include <memory>

class Widget
{
public:
    Widget();

private:
    struct Impl;
    std::unique_ptr<Impl> pImpl;
};


#endif //_QGW_WIDGET_H
