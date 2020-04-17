#pragma once

#include "PxPhysicsAPI.h"
#include <map>
#include "NetMessengerClient.h"

namespace Aftr {
    class ModelDataSharedID;
    class WOPxActor;

    class PxEngine {
    public:
        PxEngine();
        ~PxEngine();
        static PxEngine* New() { return new PxEngine(); };        

        void simulate(NetMessengerClient* client, std::map<WOPxActor*, int> boxes);

        physx::PxPhysics* phys;
        physx::PxScene* scene;

    private:
        physx::PxFoundation* found;
        physx::PxPvd* pvd;
        physx::PxU32 version = PX_PHYSICS_VERSION;
        physx::PxCooking* cook;
        physx::PxDefaultCpuDispatcher* dispatch;
        physx::PxMaterial* mat;
        physx::PxDefaultAllocator all;
        physx::PxDefaultErrorCallback err;
        physx::PxPvdSceneClient* client;
    };
}
