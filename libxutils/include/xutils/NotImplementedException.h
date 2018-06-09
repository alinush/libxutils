/*
 * NotImplementedException.h
 *
 *      Author: Alin Tomescu
 */

#pragma once

#include <exception>
#include <stdexcept>

// Some compilers have different #define's for C++11's noexcept
#ifdef _GLIBCXX_NOEXCEPT
# define _NOEXCEPT _GLIBCXX_USE_NOEXCEPT
#else
# ifndef _NOEXCEPT
#  error "_NOEXCEPT is not defined"
# endif
#endif

namespace libxutils {

class NotImplementedException: public std::exception {
public:
	NotImplementedException() {}

public:
	virtual const char * what() const _NOEXCEPT { return "Not implemented exception!"; }
};

}
