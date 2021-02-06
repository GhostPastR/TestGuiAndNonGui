#ifndef LISTSTRUCTSYSTEM_H
#define LISTSTRUCTSYSTEM_H

#include "convertbyte.h"

struct ItemShared
{
    std::string value1_;
    std::string value2_;
    std::string value3_;

    auto structSharedMemory() const {
        return StructShareMemory<std::string, std::string, std::string>( value1_, value2_, value3_ );
    }
};

template<> size_t idStruct<ItemShared>() {
    return 1;
}

#endif // LISTSTRUCTSYSTEM_H
