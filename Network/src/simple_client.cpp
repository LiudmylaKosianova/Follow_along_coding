#include <iostream>

#include "../headers/olc_net.h"

enum class CustomMsgTypes : uint32_t
{
    FireBullet,
    MovePlayer
};

int main()
{
    olc::net::message<CustomMsgTypes> msg;
    msg.header.id = CustomMsgTypes::FireBullet;

    //testing
    int a = 11;
    bool b = true;
    float c = 2.213f;

    msg << a << b << c;

    a = 99;
    b = false;
    c = 99.11f;
 

    return 0;

}

