/*
 * AutoBuf.h
 *
 *  Created on: September 14th, 2017
 *      Author: Alin Tomescu <alinush@mit.edu>
 */

#pragma once

#include <cstring>
#include <algorithm>

#include <xutils/Log.h>

template<class T>
class AutoBuf {
private:
    T * buf;
    long len;

public:
    AutoBuf() : len(0), buf(nullptr) {}

    AutoBuf(size_t len)
        : buf(new T[len]), len(static_cast<long>(len))
    {}

    AutoBuf(long len)
        : buf(new T[static_cast<unsigned long>(len)]), len(len)
    {}

    AutoBuf(int len)
        : buf(new T[static_cast<unsigned long>(len)]), len(len)
    {}

    AutoBuf(const AutoBuf<T>& ab)
        : AutoBuf(ab.len)
    {
        std::copy(ab.buf, ab.buf + ab.len, buf);
    }
 
    AutoBuf(AutoBuf&& other)
        : buf(other.buf), len(other.len)
    {
        //logdbg << "Move constructor called: this = " << this << ", other = " << &other << std::endl;

        other.buf = nullptr;
        other.len = 0;
    }

    // Move assignment
    AutoBuf& operator=(AutoBuf&& other) noexcept {
        //logdbg << "Move assignment called: this = " << this << ", other = " << &other << std::endl;

        if (this == &other)
            return *this;

        delete [] buf;

        buf = other.buf;
        len = other.len;

        other.buf = nullptr;
        other.len = 0;

        return *this;
    }

    ~AutoBuf() {
        delete [] buf;
    }

public:
    operator T* () { return buf; }
    operator const T* () const { return buf; }

public:
    T * getBuf() { return buf; }
    const T * getBuf() const { return buf; }

    long size() const { return len; }

    void zeroize() {
        memset(buf, 0, static_cast<size_t>(len));
    }
};

typedef AutoBuf<char> AutoCharBuf;
typedef AutoBuf<unsigned char> AutoByteBuf;
