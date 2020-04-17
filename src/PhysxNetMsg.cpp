#include "PhysxNetMsg.h"

#include <iostream>
#include <sstream>
#include <string>
#include "GLViewPhysics.h"
#include "WOPxActor.h"
#include "WorldContainer.h"

#ifdef AFTR_CONFIG_USE_BOOST

using namespace Aftr;

NetMsgMacroDefinition(PhysxNetMsg);

PhysxNetMsg::PhysxNetMsg() {

}

PhysxNetMsg::~PhysxNetMsg() {

}

bool PhysxNetMsg::toStream(NetMessengerStreamBuffer& os) const {
    os << pos.x << pos.y << pos.z;
    os << pose[0] << pose[1] << pose[2] << pose[3];
    os << pose[4] << pose[5] << pose[6] << pose[7];
    os << pose[8] << pose[9] << pose[10] << pose[11];
    os << pose[12] << pose[13] << pose[14] << pose[15];
    os << index;
    return true;
}

bool PhysxNetMsg::fromStream(NetMessengerStreamBuffer& is) {
    float x, y, z;
    is >> x >> y >> z;
    pos = Vector(x, y, z);
    is >> pose[0] >> pose[1] >> pose[2] >> pose[3];
    is >> pose[4] >> pose[5] >> pose[6] >> pose[7];
    is >> pose[8] >> pose[9] >> pose[10] >> pose[11];
    is >> pose[12] >> pose[13] >> pose[14] >> pose[15];
    is >> index;
    return true;
}

void PhysxNetMsg::onMessageArrived() {
    for (auto& i : ((GLViewPhysics*)ManagerGLView::getGLView())->boxes) {
        if (i.second == this->index) {
            WOPxActor* wo = i.first;
            wo->setDisplayMatrix(this->pose);
            wo->setPosition(this->pos);
            std::cout << this->toString() << std::endl;
        }
    }
}

std::string PhysxNetMsg::toString() const
{
    std::stringstream ss;
    ss << NetMsg::toString();
    ss << "Message: " << std::endl;
    ss << "     " << "Position: " << this->pos << "    " << "Index: " << this->index << std::endl;
    return ss.str();
}

#endif