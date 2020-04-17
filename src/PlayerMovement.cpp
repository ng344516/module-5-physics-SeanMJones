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
#include "PlayerMovement.h"
#include "GLViewPhysics.h"


using namespace Aftr;

NetMsgMacroDefinition(PlayerMovement);

PlayerMovement::PlayerMovement()
{
}

PlayerMovement::~PlayerMovement()
{

}

bool PlayerMovement::toStream(NetMessengerStreamBuffer& os) const
{
    os << ptranslation.x << ptranslation.y << ptranslation.z;
    os << protation.x << protation.y << protation.z;\
    os << ltranslation.x << ltranslation.y << ltranslation.z;
    os << lrotation.x << lrotation.y << lrotation.z;
    os << usermsg;
    return true;
}

bool PlayerMovement::fromStream(NetMessengerStreamBuffer& is)
{
    is >> ptranslation.x >> ptranslation.y >> ptranslation.z;
    is >> protation.x >> protation.y >> protation.z;
    is >> ltranslation.x >> ltranslation.y >> ltranslation.z;
    is >> lrotation.x >> lrotation.y >> lrotation.z;
    is >> usermsg;
    return true;
}

void PlayerMovement::onMessageArrived()
{
    ((GLViewPhysics*)ManagerGLView::getGLView())->movePlayer(ptranslation, protation, ltranslation, lrotation, false);
    ((GLViewPhysics*)ManagerGLView::getGLView())->setLabel(usermsg);

}

std::string PlayerMovement::toString() const
{
    std::stringstream ss;

    ss << NetMsg::toString();
    ss << "ID = " << this->id << "\n";
    return ss.str();
}

#endif