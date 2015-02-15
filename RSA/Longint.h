//
//  Longint.h
//  RSA
//
//  Created by Андрей Рычков on 08.04.13.
//  Copyright (c) 2013 Андрей Рычков. All rights reserved.
//

#ifndef __RSA__Longint__
#define __RSA__Longint__

#include <iostream>
#include "string.h"
#include "List.h"

const int BASE = 10;

class Longint
{
    char*   _digits;
    long    _len;
    bool    _positive;
    
    // Private operations
    void removeLeadingZeros ();
    void removeLastSymbol ();
    void addSymbol (const char s);
    void shift ();
    bool isEven ();
public:
    // Constructors
    Longint (unsigned long ul = 0);
    Longint (unsigned int ui = 0);
    Longint (signed long sl = 0);
    Longint (signed int si = 0);
    Longint (const char* s = "");
    Longint (const Longint&);
    ~Longint();
    // Output
    void print() const;
    // Comparison operators
    bool operator == (const Longint&);
    bool operator != (const Longint&);
    bool operator < (const Longint&);
    bool operator <= (const Longint&);
    bool operator > (const Longint&);
    bool operator >= (const Longint&);
    // Unary operator
    const Longint operator - () const;
    // Binary operators
    friend const Longint operator + (Longint, const Longint&);
    friend const Longint operator - (Longint, const Longint&);
    friend const Longint operator * (const Longint&, const Longint&);
    friend const Longint operator / (const Longint&, const Longint&);
    friend const Longint operator % (const Longint&, const Longint&);
    // Assignment operator
    Longint& operator = (const Longint&);
    // Increment and decrement operators
    Longint& operator ++ ();
    Longint operator ++ (int);
    Longint& operator -- ();
    Longint operator -- (int);
    // Compound assignment operators
    const Longint& operator += (const Longint&);
    const Longint& operator -= (const Longint&);
    const Longint& operator *= (const Longint&);
    const Longint& operator /= (const Longint&);
    const Longint& operator %= (const Longint&);
    // Math functions
    Longint abs (Longint&); // Absolute value;
    Longint pow (Longint&); // Power
    Longint factorial (); // Factorial *this!
    Longint powMod (); // a^d(mod m)
    // Miller-Rabin primarity test
    bool prime ();
    // Convert to binary
    char* toBin ();
};

// Output stream
std::ostream& operator << (std::ostream& out, const Longint&);
std::istream& operator >> (std::istream& in, Longint&);

#endif /* defined(__RSA__Longint__) */