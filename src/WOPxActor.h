#pragma once

#include "WO.h"
#include "Model.h"
#include "PxEngine.h"
#include "PxPhysicsAPI.h"

#ifdef AFTR_CONFIG_USE_BOOST

namespace Aftr {
	class NetMessengerClient;
	class IPhysicsManager;

	class WOPxActor : public WO {
	public:
		WOMacroDeclaration(WOPxActor, WO);
		physx::PxRigidActor* pxActor;

		static WOPxActor* New(
			physx::PxRigidActor* pxActor = nullptr,
			const std::string& path = ManagerEnvironmentConfiguration::getSMM() + "models/box/box.blend",
			Vector scale = Vector(1, 1, 1),
			MESH_SHADING_TYPE shadingType = MESH_SHADING_TYPE::mstAUTO
			);
		virtual void onCreate(const std::string& path, Vector scale = Vector(1, 1, 1), MESH_SHADING_TYPE shadingType = MESH_SHADING_TYPE::mstAUTO);

		void setDisplayMatrix(Mat4 matrix) { WO::getModel()->setDisplayMatrix(matrix); }

	protected:
		WOPxActor(physx::PxRigidActor* actor);
	};
}

#endif
