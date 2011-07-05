#ifndef VALIDATION_POLICIES_H
#define VALIDATION_POLICIES_H

class DefaultValidationPolicy
{
public:
    template <class T>
    bool validate(T* /*leaf*/)
    {
        return true;
    }
};

class ForbidMissinbgDataPolicy
{
public:
    template <class T>
    bool validate(T* leaf)
    {
        return leaf->getName() != "";
    }
};

#endif
