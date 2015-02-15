//
//  Longint.cpp
//  RSA
//
//  Created by Андрей Рычков on 08.04.13.
//  Copyright (c) 2013 Андрей Рычков. All rights reserved.
//

#include "Longint.h"

// Constructors
Longint::Longint (unsigned long ul): _len(1), _positive(true)
{
    _digits = new char[_len];
    _digits[0] = ul % BASE + '0';
    ul /= BASE;
    while (ul > 0)
    {
        addSymbol(ul % BASE + '0');
        ul /= BASE;
    }
}
Longint::Longint (unsigned int ui): _len(1), _positive(true)
{
    _digits = new char[_len];
    _digits[0] = ui % BASE + '0';
    ui /= BASE;
    while (ui > 0)
    {
        addSymbol(ui % BASE + '0');
        ui /= BASE;
    }
}
Longint::Longint (signed long sl): _len(1), _positive(true)
{
    if (sl < 0)
    {
        _positive = false;
        sl = -sl;
    }
    _digits = new char[_len];
    _digits[0] = sl % BASE + '0';
    sl /= BASE;
    while (sl > 0)
    {
        addSymbol(sl % BASE + '0');
        sl /= BASE;
    }
}
Longint::Longint (signed int si): _len(1), _positive(true)
{
    if (si < 0)
    {
        _positive = false;
        si = -si;
    }
    _digits = new char[_len];
    _digits[0] = si % BASE + '0';
    si /= BASE;
    while (si > 0)
    {
        addSymbol(si % BASE + '0');
        si /= BASE;
    }
}
Longint::Longint (const char* s): _len(1), _positive(true)
{
    if (strlen(s) == 0 || strcmp(s, "-0") == 0)
    {
        _digits = new char[_len];
        _digits[0] = '0';
    }
    else
    {
        if (s[0] == '-')
        {
            _positive = false;
            _len = strlen(s)-1;
            _digits = new char[_len];
            for (long i = _len, j = 0; i > 0; --i, ++j)
                _digits[j] = s[i];
        }
        else
        {
            _len = strlen(s);
            _digits = new char[_len];
            for (long i = _len - 1, j = 0; i >= 0; --i, ++j)
                _digits[j] = s[i];
        }
    }
    removeLeadingZeros();
    if (_digits[0] == '0' && _len == 1)
        _positive = true;
}
Longint::Longint (const Longint& x): _len(0), _positive(true)
{
    this->_positive = x._positive;
    this->_len = x._len;
    _digits = new char[_len];
    for (int i = 0; i < _len; ++i)
        _digits[i] = x._digits[i];
}
Longint::~Longint()
{
    if (_digits)
        delete[] _digits;
}
// Output
void Longint::print() const
{
    if (!(_positive))
        std::cout << '-';
    for (long i = _len-1; i >= 0; --i)
        std::cout << (_digits[i] - '0');
}
// Private operations
void Longint::removeLeadingZeros ()
{
    while (_len > 1 && _digits[_len-1] == '0')
        removeLastSymbol();
}
void Longint::removeLastSymbol()
{
    char* tmp = new char[_len - 1];
    for (int i = 0; i < _len - 1; ++i)
    {
        tmp[i] = _digits[i];
    }
    _digits[_len-1] = '\0';
    delete[] _digits;
    --_len;
    _digits = new char[_len];
    for (int i = 0; i < _len; ++i)
    {
        _digits[i] = tmp[i];
    }
    tmp[_len-1] = '\0';
    delete[] tmp;
}
void Longint::addSymbol (const char s)
{
    ++this->_len;
    if (_len == 1)
    {
        _digits = new char[_len];
        _digits[0] = '0';
    }
    char* tmp = new char[this->_len];
    for (int i = 0; i < this->_len; ++i)
        tmp[i] = this->_digits[i];
    tmp[_len-1] = s;
    delete[] _digits;
    _digits = new char[_len];
    for (int i = 0; i < this->_len; ++i)
        this->_digits[i] = tmp[i];
    delete[] tmp;
}
void Longint::shift()
{
    addSymbol(_digits[_len-1]);
    for (long i = _len - 2; i > 0; --i)
        _digits[i] = _digits[i-1];
    _digits[0] = '0';
}
bool Longint::isEven ()
{
    return !(_digits[0] & 1);
}
// Comparison operators
bool Longint::operator == (const Longint& other)
{
    if (other._positive != this->_positive)
        return false;
    if (other._len != this->_len)
        return false;
    for (int i = 0; i < _len; ++i)
        if (other._digits[i] != this->_digits[i])
            return false;
    return true;
}
bool Longint::operator != (const Longint& other)
{
    return !(*this == other);
}
bool Longint::operator < (const Longint& other)
{
    if (!other._positive && this->_positive)
        return false;
    else if (other._positive && !this->_positive)
        return true;
    if (other._len < this->_len)
        return false;
    else if (other._len > this->_len)
        return true;
    for (long i = _len - 1; i >= 0; --i)
        if (other._digits[i] > this->_digits[i])
            return true;
        else if (other._digits[i] < this->_digits[i])
            return false;
    return false;
}
bool Longint::operator <= (const Longint& other)
{
    if (*this < other || *this == other)
        return true;
    return false;
}
bool Longint::operator > (const Longint& other)
{
    if (!other._positive && this->_positive)
        return true;
    else if (other._positive && !this->_positive)
        return false;
    if (other._len > this->_len)
        return false;
    else if (other._len < this->_len)
        return true;
    for (long i = _len - 1; i >= 0; --i)
        if (other._digits[i] < this->_digits[i])
            return true;
        else if (other._digits[i] > this->_digits[i])
            return false;
    return false;
    
}
bool Longint::operator >= (const Longint& other)
{
    if (*this > other || *this == other)
        return true;
    return false;
}
// Unary operator
const Longint Longint::operator - () const
{
    Longint tmp(*this);
    tmp._positive = !this->_positive;
    return tmp;
}
// Binary operators
const Longint operator + (Longint left, const Longint& right)
{
    if (!left._positive)
    {
        if (!right._positive)
            return -(-left + (-right));
        else
            return right - (-left);
    }
    else if (!right._positive)
        return left - (-right);
    while (right._len > left._len)
        left.addSymbol('0');
    left.addSymbol('0');
    
    for (int i = 0;i < right._len; ++i)
    {
        left._digits[i] += right._digits[i] - '0';
        long k = i;
        while (left._digits[k] > '9' && k < left._len)
        {
            left._digits[k+1] += 1;
            left._digits[k] -= ('9' + 1 - '0');
            ++k;
        }
    }
    left.removeLeadingZeros();
    return left;
}
const Longint operator - (Longint left, const Longint& right)
{
    if (!left._positive)
        return -(-left + right);
    else if (!right._positive)
        return left + (-right);
    else if (left < right)
        return -(right - left);
    
    for (int i = 0; i < right._len; ++i)
    {
        left._digits[i] = left._digits[i] - right._digits[i] + '0';
        long k = i;
        while  (left._digits[k] < '0')
        {
            left._digits[k] += BASE;
            left._digits[k+1] -= 1;
            ++k;
        }
    }
    left.removeLeadingZeros();
    return left;
}
const Longint operator * (const Longint& left, const Longint& right)
{
    Longint result("0");
    while (result._len < left._len + right._len)
    {
        result.addSymbol('0');
    }
    for (long i = 0; i < left._len; ++i)
    {
        for (long j = 0; j < right._len; ++j)
        {
            result._digits[i+j] = result._digits[i+j] - '0' + ((left._digits[i] - '0') * (right._digits[j] - '0'));
            if (result._digits[i+j] > ('9' - '0'))
            {
                result._digits[i+j+1] = result._digits[i+j+1] + (result._digits[i+j] / BASE);
                result._digits[i+j] = (static_cast<int>(result._digits[i+j]) % BASE) + '0';
            }
            else
            {
                result._digits[i+j] += '0';
            }
        }
    }
    result._positive = left._positive == right._positive;
    result.removeLeadingZeros();
    return result;
}
const Longint operator / (const Longint& left, const Longint& right)
{
    if (right._digits[0] == '0' && right._len == 1)
        throw "Divide by zero!";
    Longint R = right;
    R._positive = true; // if !right._positive it needs to initialize new Longint – R
    Longint L = left;
    L._positive = true;
    if (R > L)
    {
        return Longint('0');
    }
    Longint quotient("0");
    while (quotient._len < left._len)
    {
        quotient.addSymbol('0');
    }
    Longint current("0");
    for (long i = left._len - 1; i >= 0; --i)
    {
        current.shift();
        current._digits[0] = left._digits[i];
        current.removeLeadingZeros();
        int x = 0, l = 0, r = BASE;
        while (l <= r)
        {
            int middle = ((l + r) / 2);
            Longint tmp(middle);
            Longint t = R * tmp;
            if (t <= current)
            {
                x = middle;
                l = middle + 1;
            }
            else
                r = middle - 1;
        }
        quotient._digits[i] = x + '0';
        current = current - R * Longint(x);
    }
    quotient._positive = left._positive == right._positive;
    quotient.removeLeadingZeros();
    return quotient;
}
const Longint operator % (const Longint& left, const Longint& right)
{
    if (right._digits[0] == '0' && right._len == 1)
        throw "Divide by zero!";
    Longint remainder = (left - (left / right) * right);
    if (!remainder._positive)
    {
        remainder += right;
    }
    return remainder;
}
// Assignment operator
Longint& Longint::operator = (const Longint& x)
{
    if (this != &x)
    {
        if (_digits)
            delete [] _digits;
        _digits = new char[x._len];
        for(int i = 0; i < x._len; ++i)
            _digits[i] = x._digits[i];
        _len = x._len;
        _positive = x._positive;
    }
    return *this;
}
// Increment and decrement operators
Longint& Longint::operator ++ ()
{
    *this += Longint("1");
    return *this;
}
Longint Longint::operator ++ (int)
{
    Longint tmp(*this);
    ++*this;
    return tmp;
}
Longint& Longint::operator -- ()
{
    *this -= Longint("1");
    return *this;
}
Longint Longint::operator -- (int)
{
    Longint tmp(*this);
    --*this;
    return *this;
}
// Compound assignment operators
const Longint& Longint::operator += (const Longint& x)
{
    return *this = (*this + x);
}
const Longint& Longint::operator -= (const Longint& x)
{
    return *this = (*this - x);
}
const Longint& Longint::operator *= (const Longint& x)
{
    return *this = (*this * x);
}
const Longint& Longint::operator /= (const Longint& x)
{
    return *this = (*this / x);
}
const Longint& Longint::operator %= (const Longint& x)
{
    return *this = (*this % x);
}
// Absolute value
Longint Longint::abs (Longint& x)
{
    if (!x._positive)
        return -x;
    return x;
}
Longint Longint::pow(Longint& x)
{
    Longint tmp(*this);
    Longint result(1);
    Longint a(2);
    Longint b(0);
    while (x != b)
    {
        if (!x.isEven())
            result *= tmp;
        tmp *= tmp;
        x /= a;
    }
    return result;
}
Longint Longint::factorial()
{
    Longint result(1);
    for (Longint i(1); i <= *this; ++i)
    {
        result *= i;
    }
    return result;
}
// Output stream
std::ostream& operator << (std::ostream& out, const Longint& x)
{
    x.print();
    return out;
}
std::istream& operator >> (std::istream& in, Longint& x)
{
    char* s = new char[1024];
    std::cout << "Enter number: ";
    std::cin.getline(s, 1024);
    x = Longint(s);
    return in;
}
