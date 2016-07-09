#ifndef SAMPFAVORITES_H
#define SAMPFAVORITES_H

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

class SampFavorites
{
	public:
		typedef struct {
			char fileTag[5];
			int fileVersion;
			int serversCount;
		} Header;

		typedef struct {
			char *address;
			int port;
			char *hostname;
			char *password;
			char *rcon;
		} Server;

		bool open(const char *fileName);
		bool isOpen();
		bool save(const char *fileName);

		Header getHeader();
		void setHeader(const Header header);

		Server getServer(const int id);
		void setServer(const int id, const Server server);
		void addServer(const Server server);
		int getServersCount();

	private:
		bool isOpened;
		Header fileHeader;
		std::vector<Server> fileServers;
};

#endif // SAMPFAVORITES_H
