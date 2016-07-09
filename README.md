# SampFavorites
C++ class for working with SA-MP favorites list (USERDATA.DAT).

# Usage
The example of usage this class:
```Pawn
#include <iostream>
#include "SampFavorites.hpp"

int main()
{
	SampFavorites data;
	data.open("USERDATA.DAT");

	if (!data.isOpen()) {
		std::cout << "Error reading file" << std::endl;
		return 1;
	}

	SampFavorites::Header header;
	SampFavorites::Server server;

	header = data.getHeader();

	std::cout << header.fileTag << "\n"
	          << header.fileVersion << "\n"
	          << header.serversCount << "\n";

	for (int i = 0; i < header.serversCount; i++) {
		server = data.getServer(i);

		std::cout << server.address << " | "
		          << server.port << " | "
		          << server.hostname << " | "
		          << server.password << " | "
		          << server.rcon << std::endl;
	}

	server.address = (char *)"999.000.111.32";
	server.port = 4322;
	server.hostname = (char *)"test host";
	server.password = (char *)"pass22";
	server.rcon = (char *)"rcon1";
	data.addServer(server);

	data.save("test.dat");
	return 0;
}
```
