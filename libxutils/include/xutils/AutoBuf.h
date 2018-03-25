/*
 * AutoBuf.h
 *
 *  Created on: September 14th, 2017
 *      Author: Alin Tomescu <alinush@mit.edu>
 */

#pragma once

#include <algorithm>

template<class T>
class AutoBuf {
private:
    T * buf;
    int len;

public:
    AutoBuf(int len)
        : buf(new T[len]), len(len)
    {}

    AutoBuf(const AutoBuf<T>& ab)
        : AutoBuf(ab.len)
    {
        std::copy(ab.buf, ab.buf + ab.len, buf);
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

    int size() const { return len; }
};

typedef AutoBuf<char> AutoCharBuf;
typedef AutoBuf<unsigned char> AutoByteBuf;
