#ifndef TREE_VALIDATION_POLICIES_H
#define TREE_VALIDATION_POLICIES_H

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
        return implies(node->isLeaf(),!node->getName().empty());
    }
};

#endif
