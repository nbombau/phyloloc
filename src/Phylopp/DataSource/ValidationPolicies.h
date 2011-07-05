#ifndef VALIDATION_POLICIES_H
#define VALIDATION_POLICIES_H

class DefaultValidationPolicy
{
public:
    template <class T>
    bool validate(const T* /*node*/) const
    {
        return true;
    }
};

class ForbidMissinbgDataPolicy
{
public:
    template <class T>
    bool validate(const T* node) const
    {        
        return node->isLeaf() ? !node->getName().empty() : true;
    }
};

#endif
