#pragma once

#include <iostream>
#include <string>

using std::string;

class Exception
{
public:
    Exception();
    Exception(string message);
    string getMessage() const;
protected:
    string m_errorMessage;
};

std::ostream & operator << (std::ostream & ostr, const Exception & exception);
