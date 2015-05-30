#include "client.hpp"

int main(int argc, char* argv[])
{
    client client_("localhost", argv[1]);
    client_();
}
