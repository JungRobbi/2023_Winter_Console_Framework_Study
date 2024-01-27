#include "stdafx.h"
#include "Exception.h"

Exception::Exception(const std::string& str) : text(str)
{
}

Exception::~Exception()
{
}
