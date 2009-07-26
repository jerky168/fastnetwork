// echo_client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

sockaddr_in init_addr( const string & host, unsigned short port )
{
	WSADATA wsaData;
	::WSAStartup(MAKEWORD(2,2), &wsaData);

	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons( port );
	addr.sin_addr.s_addr = inet_addr( host.c_str() );

	return addr;
}


void read_send( const string & host, unsigned short port )
{
	sockaddr_in to_addr = init_addr( host, port );

	SOCKET s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	while( true )
	{
		string read;
		cin >> read;
		if( read == "quit" )
		{
			break;
		}
		cout << "[SYS:send]" << read << endl;
		char send_buf[1024] = {0};
		unsigned short message_len = static_cast<unsigned short>( read.length() );
		::memcpy( send_buf, &message_len, sizeof(message_len) );
		::memcpy( send_buf + sizeof(message_len), read.c_str(), message_len );
		::sendto( s, send_buf, message_len + sizeof(message_len), 0, (SOCKADDR*)&to_addr, sizeof(to_addr) );

		sockaddr_in server_addr;
		int addr_size = sizeof(server_addr);
		char buf[1024] = {0};

		int size = ::recvfrom( s, buf, sizeof(buf), 0, (SOCKADDR*)&server_addr, &addr_size );
		if( size == -1 ) {
			cout << "[SYS]can not read response." << endl;
			continue ;
		}

		::memcpy( &message_len, buf, sizeof(message_len) );
		assert( size >= message_len + 2 );
		string received( buf + sizeof( message_len ), message_len );
		cout << received << endl;
	}
}

void show_usage( _TCHAR* app_name )
{
	cout << app_name << " ip port" << endl;
}
int _tmain(int argc, _TCHAR* argv[])
{
	if( argc < 3 )
	{
		show_usage( argv[0] );
		return 0;
	}

	string host( argv[1] );
	unsigned short port = static_cast<unsigned short>( atoi( argv[2] ) );

	read_send( host, port );

	return 0;
}

