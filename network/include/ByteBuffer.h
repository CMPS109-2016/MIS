//
// Created by CIJhn on 11/15/2016.
//

#ifndef MIS_SOCKET_BYTEBUFFER_H
#define MIS_SOCKET_BYTEBUFFER_H

#include <cstdlib>
#include <string>

typedef char Byte;

//this class is not tested yet.
class ByteBuffer {
    Byte *payload;
    size_t cap;
    int pt, _size;

    template<size_t>
    void ensure_capacity(int size);

public:
    ByteBuffer(int initSize);

    virtual ~ByteBuffer();

    /**
     * Write a byte array into this buffer.
     */
    ByteBuffer &writeBytes(const Byte *v, int size);

    /**
    * Write a byte into this buffer.
    */
    ByteBuffer &writeByte(Byte v);

    /**
    * Write a int into this buffer.
    */
    ByteBuffer &writeInt(int v);

    /**
     * Reset the pointer into the 0.
     * */
    void flip();

    /**
     * The capacity of the buffer, might grow if we keep putting bytes into it.
     * */
    size_t capacity();

    /**
     * The size of the bytes already been buffered.
     * */
    int size();

    int remain();

    int readInt();

    Byte readByte();

    ByteBuffer &readBytes(Byte *bytes, int size);//dont really know if this will work

    const Byte *data();
};


#endif //MIS_SOCKET_BYTEBUFFER_H
