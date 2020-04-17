#include "NetMsgCreateWO.h"
#ifdef AFTR_CONFIG_USE_BOOST

#include <iostream>
#include <sstream>
#include <string>
#include "AftrManagers.h"
#include "Vector.h"
#include "WO.h"
#include "GLView.h"
#include "WorldContainer.h"
#include "NetworkingNetMsg.h"
#include "GLViewPhysics.h"


using namespace Aftr;

NetMsgMacroDefinition(NetworkingNetMsg);

NetworkingNetMsg::NetworkingNetMsg()
{
}

NetworkingNetMsg::~NetworkingNetMsg()
{
    
}

bool NetworkingNetMsg::toStream(NetMessengerStreamBuffer& os) const
{
    os << this->id;
    os << this->pos.x;
    os << this->pos.y;
    os << this->pos.z;
    return true;
}

bool NetworkingNetMsg::fromStream(NetMessengerStreamBuffer& is)
{
    is >> this->id;
    is >> this->pos.x;
    is >> this->pos.y;
    is >> this->pos.z;
    return true;
}

void NetworkingNetMsg::onMessageArrived()
{
    
}

std::string NetworkingNetMsg::toString() const
{
    std::stringstream ss;

    ss << NetMsg::toString();
    ss << "ID = " << this->id << "\n";
    ss << "Postion: " << this->pos << "\n";
    return ss.str();
}

#endif