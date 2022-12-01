#include "stat.h"

class statData : public QSharedData
{
public:

};

stat::stat() : data(new statData)
{

}

stat::stat(const stat &rhs) : data(rhs.data)
{

}

stat &stat::operator=(const stat &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

stat::~stat()
{

}
