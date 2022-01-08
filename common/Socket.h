//
// Created by stefan on 08.01.2022.
//

#ifndef READSPROFILER_SOCKET_H
#define READSPROFILER_SOCKET_H
#include "include.h"

class Socket {
private:

    ReturnOf < decltype ( socket ) > sock;

    bool _connected  {false};
    uint16 _port;
    uint64 _packageSize = 1024u;

public:

    constexpr static StringLiteral LOCALHOST = "127.0.0.1";

    __CDS_NoDiscard constexpr auto isOpen() const noexcept -> bool {
        return this->sock != -1;
    }

    __CDS_NoDiscard constexpr auto connected() const noexcept -> bool {
        return this->_connected;
    }

    auto open() noexcept (false) -> Socket & {
        if( this -> isOpen() )
            return * this;

        this->sock = :: socket (AF_INET, SOCK_STREAM, 0);

        if( this->sock != -1 )
            return * this;

        throw Exception ("Socket error");

    }

    auto close () noexcept (false) -> Socket & {

        if (! this->isOpen() )
            return * this;

        this->_connected = false;

        auto retVal = ::close (exchange( this->sock, -1 ) );
        if( retVal == -1 )
            throw Exception ("Socket close exception");

        this->sock = -1;

        return * this;
    }

    constexpr explicit Socket(int  s = -1) noexcept : sock (s) {} ;

    explicit  Socket( String const & address, uint16 port ) noexcept ( false ) : _port ( port ) {
        (void) this->open().connect( address, port );
    }


    Socket (Socket const & socket) noexcept :
        sock(dup(socket.sock)),
        _port(socket._port),
        _packageSize(socket._packageSize),
        _connected(socket._connected) {

    }


    Socket( Socket && socket ) noexcept :
            sock(exchange(socket.sock, -1)),
            _port(exchange(socket._port, 8080u)),
            _packageSize(exchange(socket._packageSize, 0)),
            _connected(exchange(socket._connected, false)) { }

    ~Socket () noexcept  {
        (void) this->close();
    }

    auto connect (const String& addr, uint16_t port) noexcept ( false ) -> void {
        if (-1 == sock) open();

        sockaddr_in address{};
        address.sin_addr.s_addr = inet_addr( addr.cStr() );
        address.sin_port = htons( port );
        address.sin_family = AF_INET;

        auto result = ::connect( sock, ( sockaddr * ) & address, sizeof ( sockaddr_in ) );

        if ( -1 == result )
            throw Exception ( "connect error" );
    }

    auto bind ( uint16_t port )  noexcept (false) -> Socket & {
        int opt = 1;
        auto result = ::setsockopt( sock, SOL_SOCKET, SO_REUSEADDR, & opt, sizeof ( opt ) );

        if ( -1 == result )
            throw Exception ( "Reuse address error" );

        sockaddr_in addressStructure;
        addressStructure.sin_addr.s_addr = htonl ( INADDR_ANY );
        addressStructure.sin_port = htons ( port );
        addressStructure.sin_family = AF_INET;

        result = ::bind ( sock, ( sockaddr * ) & addressStructure , sizeof ( sockaddr_in ) );

        if( -1 == result )
            throw Exception ( "Bind error" );

        return * this;
    }

    auto listen ( int queueSize ) const noexcept ( false ) -> void {
        auto result = ::listen (sock, queueSize);

        if( -1 == result )
            throw Exception ( "Listen error" );
    }

    __CDS_NoDiscard auto accept() const noexcept (false) -> Socket{

        sockaddr_in clientAddr;
        socklen_t size = sizeof(clientAddr);

        int retVal = ::accept(this->sock, ( sockaddr *) & clientAddr, & size );

        if( retVal == -1 )
            throw Exception ("Accept error");

        auto clientSocket = Socket(retVal);

        return std::move(clientSocket);

    }


    auto writeBytes (uint8 const * pBuffer, uint64 count) noexcept ( false ) -> Socket & {

        auto written = ::write( this->sock, pBuffer, count );

        if (written == -1)
            throw Exception ("Socket writeBytes error");

        if( static_cast < Size > ( written ) != count)
            throw Exception( String::f(
                    "Unable to completely write message : intended : %d, sent : %d",
                    static_cast < int > ( count ),
                    static_cast < int > ( written )
            ));

        return * this;
    }

    __CDS_NoDiscard auto readBytes ( uint8 * pBuffer, uint64 count ) noexcept (false) -> Socket & {

        auto read = ::read (this->sock, pBuffer, count );

        if( read == -1 )
            throw Exception("Socket readBytes Exception");

        if(read == 0)
            throw Exception("Connection lost");

        if ( static_cast < Size > ( read ) != count )
            throw Exception("Read Bytes count Different from Intended Count");

        return * this;
    }

    auto writeInt ( int value ) noexcept (false) -> Socket & {
        return this->writeBytes( reinterpret_cast < Byte const * > ( & value ), sizeof (value) );
    }

    __CDS_NoDiscard auto readInt () noexcept(false) -> int {
        int value;
        (void) this->readBytes(reinterpret_cast < Byte * > ( &value ), sizeof(value));
        return value;
    }

    auto writeString ( String const & string ) noexcept ( false ) -> Socket & {
        auto packageCount = string.size() / this->_packageSize;
        if( string.size() % this->_packageSize != 0u )
            ++packageCount;

        (void) this->writeInt( (int) string.size() );

        uint64 offset = 0u;

        for(uint64 i = 0; i < packageCount; ++i) {

            (void) this->writeBytes(
                    reinterpret_cast < Byte const * > ( string.cStr() ) + offset,
                    std::min ( this->_packageSize, string.size() - offset)
            );

            offset += this->_packageSize;
        }

        return * this;
    }

    __CDS_NoDiscard auto readString () noexcept (false) -> String {
        uint64 originalSize = this->readInt();
        uint64 offset = 0u;
        uint64 packetCount = originalSize / this->_packageSize;

        if ( originalSize % this->_packageSize != 0u)
            ++packetCount;

        String buffer;
        buffer.resize(originalSize);


        for(uint64 i = 0u; i < packetCount; i++){
            (void) this->readBytes(
                    reinterpret_cast < Byte * > (buffer.data()) + offset,
                    std::min(this->_packageSize, originalSize - offset)
            );
        }

        offset  += this->_packageSize;

        return { buffer.cStr(), originalSize };

    }
    auto operator= (Socket && socket) noexcept -> Socket & {
        if( & socket == this )
            return * this;

        (void) this->close();

        this->sock = exchange(socket.sock, -1);
        this->_port = exchange(socket._port, 8080);
        this->_packageSize = exchange(socket._packageSize, 0);
        this->_connected = exchange(socket._connected, false);

        return * this;

    }

};

#endif //READSPROFILER_SOCKET_H
