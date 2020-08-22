#include "Client.hpp"

int main()
{
	CloudClient client( LISTEN_DIR, STORE_FILE ,SERVER_IP, SERVER_PORT);
	client.Start();
	
    return 0;
}