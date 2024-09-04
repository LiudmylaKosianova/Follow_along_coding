#include <iostream>

#include "../headers/olc_net.h"

enum class CustomMsgTypes : uint32_t
{
    FireBullet,
    MovePlayer
};

class CustomClient : olc::net::client_interface<CustomMsgTypes>
{
public:
    bool FireBullet(float x, float y){
        olc::net::message<CustomMsgTypes> msg;
        msg.header.id = CustomMsgTypes::FireBullet;
        msg << x << y;
        //Send(msg);
    }
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

