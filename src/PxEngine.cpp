#include "PxEngine.h"
#include <iostream>
#include "Model.h"
#include "WOPxActor.h"
#include "PhysxNetMsg.h"

using namespace Aftr;
using namespace physx;

PxEngine::PxEngine()
{
    this->found = PxCreateFoundation(version,all, err);
    this->pvd = PxCreatePvd(*found);
    this->pvd->connect(*PxDefaultPvdSocketTransportCreate("127.0.0.1", 5555, 10), PxPvdInstrumentationFlag::eALL);
    this->phys = PxCreatePhysics(version, *found, PxTolerancesScale(), true, pvd);
    this->cook = PxCreateCooking(version, *found, PxCookingParams(PxTolerancesScale()));
    this->dispatch = PxDefaultCpuDispatcherCreate(4);
    this->mat = phys->createMaterial(0.5f, 0.5f, 0.6f);

    PxSceneDesc sDesc(this->phys->getTolerancesScale());
    sDesc.gravity = PxVec3(0.0f, 0.0f, -9.81f);
    sDesc.cpuDispatcher = this->dispatch;
    sDesc.flags = PxSceneFlag::eENABLE_ACTIVE_ACTORS;
    sDesc.filterShader = PxDefaultSimulationFilterShader;
    this->scene = this->phys->createScene(sDesc);
    this->client = scene->getScenePvdClient();

    if (this->client) {
        this->client->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
        this->client->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
        this->client->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
    }
}

PxEngine::~PxEngine()
{
    this->scene->release();
    this->found->release();
    this->phys->release();
}

void PxEngine::simulate(NetMessengerClient* client, std::map<WOPxActor*, int> boxes) {
    this->scene->simulate(ManagerSDLTime::getTimeSinceLastPhysicsIteration() / 1000.0f);
    this->scene->fetchResults(true);
    PxU32 numTrans = 0;
    PxActor** activeActors = this->scene->getActiveActors(numTrans);
    for (PxU32 i = 0; i < numTrans; i++) {
        WOPxActor* wo = static_cast<WOPxActor*>(activeActors[i]->userData);
        if (wo != nullptr && wo->pxActor != nullptr) {
            PxTransform trans = wo->pxActor->getGlobalPose();
            PxMat44 pose = PxMat44(trans);

            float convert[16] = { 
                pose(0, 0), pose(0, 1), pose(0, 2), pose(3, 0),
                pose(1, 0), pose(1, 1), pose(1, 2), pose(3, 1),
                pose(2, 0), pose(2, 1), pose(2, 2), pose(3, 2),
                pose(0, 3), pose(1, 3), pose(2, 3), pose(3, 3)
            };
            Mat4 mat(convert);
            if (client != nullptr && client->isTCPSocketOpen()) {
                PhysxNetMsg msg;
                msg.pos = Vector(mat[12], mat[13], mat[14]);
                msg.pose = mat;
                msg.index = boxes[wo];
                client->sendNetMsgSynchronousTCP(msg);
            }
            wo->setDisplayMatrix(mat);
            wo->setPosition(Vector(mat[12], mat[13], mat[14]));
        }
    }
}