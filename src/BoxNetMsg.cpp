#include "BoxNetMsg.h"

#include <iostream>
#include <sstream>
#include <string>
#include "AftrManagers.h"
#include "Vector.h"
#include "GLView.h"
#include "GLViewPhysics.h"
#include "WOPxActor.h"
#include "WorldContainer.h"


#ifdef AFTR_CONFIG_USE_BOOST

using namespace Aftr;

NetMsgMacroDefinition(BoxNetMsg);

bool BoxNetMsg::toStream(NetMessengerStreamBuffer& os) const {
	os << pos.x << pos.y << pos.z;
	return true;
}

bool BoxNetMsg::fromStream(NetMessengerStreamBuffer& is) {
	float x, y, z;
	is >> x >> y >> z;
	this->pos = Vector(x, y, z);
	return true;
}

void BoxNetMsg::onMessageArrived() {
	((GLViewPhysics*)ManagerGLView::getGLView())->spawnItem(this->pos);
}

std::string BoxNetMsg::toString() const {
	std::stringstream ss;
	ss << NetMsg::toString();
	ss << "Position: " << this->pos << std::endl;

	return ss.str();
}

#endif