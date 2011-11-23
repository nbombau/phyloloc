#ifndef VECTOR_HELPER_H
#define VECTOR_HELPER_H

#include <vector>
#include <algorithm>
#include <functional>

namespace Propagation
{
    //TODO: add more specific methods that use this general methods
    class VectorHelper
    {
    public:
        template <typename T, typename Operation>
        static void vectorialOperation(const std::vector<T>& a, 
                                       const std::vector<T>& b, 
                                       std::vector<T>& result)
        {
            assert(a.size() == b.size());
            
            result.reserve(a.size());
            
            std::transform(a.begin(), a.end(), b.begin(),
                           result.begin(), Operation());
        }
        
        template <typename T, typename Operation>
        static void scalarOperation(std::vector<T>& a, 
                                    T scalar)
        {
            std::transform(a.begin(), a.end(), a.begin(),
                           std::bind1st(Operation(), scalar));
        }
        
    };
}

#endif