//
// Created by CIJhn on 11/19/2016.
//

#include <assert.h>
#include "ByteBuffer.h"

void test() {
    //first the server should be start
    //in server
    //TCPServerChannel* server = TCPServerChannel.createServer(address,handler,10);
    //std::async([server](){server->start();});
    //notice that the start function is blocking! it's a inf while loop, unless other thread
    //call the function server->terminate();




    //in client
    //TCPConnection *connection = TCPConnection.connect(address); declare the connection and connect
    ByteBuffer byteBuffer(512);
    assert(byteBuffer.capacity() == 512);
    assert(byteBuffer.size() == 0);
    assert(byteBuffer.remain() == 0);
    //suppose we want to write a message that | message id(byte) | payload length(int) | payload
    std::string msg("whatever message");
    byteBuffer.writeByte(0x04); //assume the id for sending this message is 4
    byteBuffer.writeInt(msg.length());//write the length
    byteBuffer.writeBytes(msg.c_str(), msg.length());//write the payload

    //send bytebuffer
    //connection.write(byteBuffer);


    //in server
    //The session handler inside TCPServerChannel will get the message;
    //
    //
    //void handle(TCPConnection* connection){
    // ByteBuffer serverBuffer(512);
    // connection->read(serverBuffer);
    // serverBuffer.flip(); //you have to flip to reset the read/write pointer to 0
    // then read the message
    // }
    //

    //now suppose the byteBuffer is the serverBuffer:
    Byte id = byteBuffer.readByte();
    if (id == 0x04) {
        // this is just a hard code if statement,
        // there should be a message dispatch framework to call different message handler to handle
        int length = byteBuffer.readInt();
        Byte container[length];
        byteBuffer.readBytes(container, length);

        std::string string(container);
        assert(id == 0x04);
        assert(length == msg.length());
        assert(msg == string);

        //do something for the string
    }
}
