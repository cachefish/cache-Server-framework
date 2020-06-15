#ifndef _NONCOPYABLE_H
#define _NONCOPYABLE_H

namespace cf
{
    
class NonCopyable
{
    public:
        NonCopyable(){}
        ~NonCopyable(){}
    private:
        NonCopyable(const NonCopyable&);
        NonCopyable &operator=(const NonCopyable&);
};

}
#endif