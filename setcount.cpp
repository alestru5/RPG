#include "setcount.h"

int SetCount::createCount(type_bunch T){
    if (T == type_bunch::big){
        return 3;
    } else if (T == type_bunch::medium){
        return 2;
    } else if (T == type_bunch::small){
        return 1;
    } else {
        throw std::invalid_argument("Its not bunch");
    }
}
