#ifndef CONSENSOR_ASPECT_H
#define CONSENSOR_ASPECT_H

#include <vector>

#include "Phylopp/Consensor/bitset.h"

namespace Consensus
{

template <class T>
class ConsensorAspect : public T
{
public:
    bitset cluster;

};
}

#endif
