#include "SampFavorites.hpp"

bool SampFavorites::open(const char *fileName)
{
	std::ifstream fileStream;
	fileStream.open(fileName, std::ifstream::binary);

	isOpened = fileStream.is_open();
	if (!isOpened) {
		return false;
	}

	fileStream.read(fileHeader.fileTag, 4);
	fileHeader.fileTag[4] = 0;

	fileStream.read(reinterpret_cast<char*>(&fileHeader.fileVersion), 4);
	fileStream.read(reinterpret_cast<char*>(&fileHeader.serversCount), 4);

	Server fileServer;
	int length;

	for (int i = 0; i < fileHeader.serversCount; i++) {
		// ip address
		fileStream.read(reinterpret_cast<char*>(&length), 4);

		fileServer.address = new char [length + 1];
		fileStream.read(fileServer.address, length);
		fileServer.address[length] = 0;

		// port
		fileStream.read(reinterpret_cast<char*>(&fileServer.port), 4);

		// hostname
		fileStream.read(reinterpret_cast<char*>(&length), 4);

		fileServer.hostname = new char [length + 1];
		fileStream.read(fileServer.hostname, length);
		fileServer.hostname[length] = 0;

		// password
		fileStream.read(reinterpret_cast<char*>(&length), 4);

		fileServer.password = new char [length + 1];
		fileStream.read(fileServer.password, length);
		fileServer.password[length] = 0;

		// rcon
		fileStream.read(reinterpret_cast<char*>(&length), 4);

		fileServer.rcon = new char [length + 1];
		fileStream.read(fileServer.rcon, length);
		fileServer.rcon[length] = 0;

		// add to vector
		addServer(fileServer);
	}

	fileStream.close();
	return true;
}

bool SampFavorites::isOpen()
{
	return isOpened;
}

bool SampFavorites::save(const char *fileName)
{
	std::ofstream fileStream;
	fileStream.open(fileName, std::ifstream::binary);

	isOpened = fileStream.is_open();
	if (!isOpened) {
		return false;
	}

	strncpy(fileHeader.fileTag, "SAMP", sizeof(fileHeader.fileTag) - 1);
	fileStream.write(fileHeader.fileTag, 4);

	fileHeader.fileVersion = 1;
	fileStream.write(reinterpret_cast<char*>(&fileHeader.fileVersion), 4);

	fileHeader.serversCount = getServersCount();
	fileStream.write(reinterpret_cast<char*>(&fileHeader.serversCount), 4);

	Server fileServer;
	int length;

	for (int i = 0; i < fileHeader.serversCount; i++) {
		fileServer = getServer(i);

		// ip address
		length = strlen(fileServer.address);
		fileStream.write(reinterpret_cast<char*>(&length), 4);
		fileStream.write(fileServer.address, length);

		// port
		fileStream.write(reinterpret_cast<char*>(&fileServer.port), 4);

		// hostname
		length = strlen(fileServer.hostname);
		fileStream.write(reinterpret_cast<char*>(&length), 4);
		fileStream.write(fileServer.hostname, length);

		// password
		length = strlen(fileServer.password);
		fileStream.write(reinterpret_cast<char*>(&length), 4);
		fileStream.write(fileServer.password, length);

		// rcon
		length = strlen(fileServer.rcon);
		fileStream.write(reinterpret_cast<char*>(&length), 4);
		fileStream.write(fileServer.rcon, length);
	}

	fileStream.close();
	return true;
}

SampFavorites::Header SampFavorites::getHeader()
{
	return fileHeader;
}

void SampFavorites::setHeader(const SampFavorites::Header header)
{
	fileHeader = header;
}

SampFavorites::Server SampFavorites::getServer(const int id)
{
	return fileServers[id];
}

void SampFavorites::setServer(const int id, const SampFavorites::Server server)
{
	fileServers[id] = server;
}

void SampFavorites::addServer(const SampFavorites::Server server)
{
	fileServers.push_back(server);
}

int SampFavorites::getServersCount()
{
	return fileServers.size();
}
