#include "WOPxActor.h"

#ifdef AFTR_CONFIG_USE_BOOST

using namespace Aftr;
using namespace physx;

WOPxActor* WOPxActor::New(physx::PxRigidActor* actor, const std::string& path, Vector scale, MESH_SHADING_TYPE shadingType) {
	WOPxActor* wo = new WOPxActor(actor);
	wo->onCreate(path, scale, shadingType);
	return wo;
}

WOPxActor::WOPxActor(physx::PxRigidActor* actor) : IFace(this), WO() {
	this->pxActor = actor;
}

void WOPxActor::onCreate(const std::string& path, Vector scale, MESH_SHADING_TYPE shadingType) {
	WO::onCreate(path, scale, shadingType);
}

#endif