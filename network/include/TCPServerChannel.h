//
// Created by CIJhn on 11/17/2016.
//

#ifndef MISVM_TCPSERVERCHANNEL_H
#define MISVM_TCPSERVERCHANNEL_H

#include "TCPConnection.h"
#include "TCPServerSocket.h"
#include <functional>
#include <atomic>

class TCPServerChannel {
private:
    TCPServerSocket *socket;
    std::atomic<bool> term;//using the c++ api for atomic, not test yet if it really work(hope so)
    int queueSize, t_sec, t_mil, rsize, wsize;
    TCPConnection::Address address;
    SessionHandler handler;

    TCPServerChannel(TCPServerSocket *socket, int queueSize, const TCPConnection::Address &address,
                     const SessionHandler &handler);

public:
    /**
     * The handler for each client connection.
     * */
    using SessionHandler =  std::function<void(TCPConnection *)>;

    /**
     * Create server by this method.
     * */
    static TCPServerChannel *createServer(TCPConnection::Address &address, SessionHandler handler, int queueSize);

    TCPServerChannel &setTimeout(int second, int mill);

    TCPServerChannel &setReadBufferSize(int size);

    TCPServerChannel &setWriteBufferSize(int size);

    int getTimoutSecond() const;

    int getTimeoutMillSecond() const;

    int getReadBufferSize() const;

    int getWriteBufferSize() const;

    /**
     * Start the server, notice that this is a blocking function, it's inf loop until someone call
     * @fn TCPServerChannel::terminated from other thread.
     * @return if the server start successfully. (false means fails and error.)
     * */
    bool start();

    /**
     * Check if this server is done, called from several threads. So this is atomic.
     * */
    bool isTerminated();

    /**
     * Terminate the server, called from several threads. So this is atomic.
     * */
    void terminate();
};


#endif //MISVM_TCPSERVERCHANNEL_H
