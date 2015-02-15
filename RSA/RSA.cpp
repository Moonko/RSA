//
//  RSA.cpp
//  RSA
//
//  Created by Андрей Рычков on 08.04.13.
//  Copyright (c) 2013 Андрей Рычков. All rights reserved.
//

#include "RSA.h"

const unsigned int KEYLENGTH = 80;

void RSA::genkeys(cryptkey& pbkey, cryptkey& prkey)
{
    Longint p(KEYLENGTH / 2);
    Longint q(KEYLENGTH / 2);
    Longint d(KEYLENGTH - 3);
    Longint n("0"), eiler("0"), diviser("0"), e("0");
    
}

void RSA::extEuclid(Longint a, Longint b, Longint& y)
{
    Longint a11(1), a12(0), a21(0), a22(1);
    Longint remainder("0"), quotient("0");
    Longint A11("0"), A12("0"), A21("0"), A22("0");
    
    while (b > Longint("0"))
    {
        remainder = a % b;
        quotient = a / b;
        if (remainder == Longint("0"))
        {
            break;
        }
        A11 = a12;
        A12 = a11 + a12 * (-quotient);
        A21 = a22;
        A22 = a21 + a22 * (-quotient);
        
        a11 = A11;
        a12 = A12;
        a21 = A21;
        a22 = A22;
        
        a = b;
        b = remainder;
    }
    y = a22;
}












