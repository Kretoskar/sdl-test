#include "HCCore/Core/HString.h"

namespace HC
{
    char HString::hashTable[hashTableSize][hashTableMaxStringLength] = { {'\0'} };
    HString HString::None = HString();
    std::mutex HString::hashTableMutex;
}