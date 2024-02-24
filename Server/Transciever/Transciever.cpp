#include "Transceiver.hpp"

namespace rnitta
{
    

Transceiver::Transceiver()
{

}

Transceiver::Transceiver( const Transceiver& other )
{

}

Transceiver::~Transceiver()
{

}

Transceiver&    Transceiver::operator=( const Transceiver& other )
{
    if (this == &other)
        return (*this);
    
    return (*this);
}

};  // namespace rnitta
