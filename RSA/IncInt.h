//
//  IncInt.h
//  RSA
//
//  Created by Андрей Рычков on 28.03.13.
//  Copyright (c) 2013 Андрей Рычков. All rights reserved.
//

#ifndef RSA_IncInt_h
#define RSA_IncInt_h

#include "List.h"

class IncInt
{
    List<int> digits_;
    bool positive_;
public:
    IncInt();
    IncInt(int);
    IncInt(unsigned long);
    IncInt(const char*);
    
};

IncInt::IncInt()
{
    positive_ = false;
    digits_.push_back(0);
}
IncInt::IncInt(int)
{
    
}
IncInt::IncInt(unsigned long)
{
    
}
IncInt::IncInt(const char* s)
{
    
}

#endif
