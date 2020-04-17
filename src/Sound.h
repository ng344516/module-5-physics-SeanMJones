#pragma once
#include "irrKlang.h"
#include "ik_ISoundEngine.h"
#include "Vector.h"

namespace Aftr {
	class SoundManager {

	protected:
		irrklang::ISoundEngine* engine = nullptr;
		std::vector<irrklang::ISound*> sound2D;
		std::vector<irrklang::ISound*> sound3D;

	public:
		static SoundManager* init();
		virtual void play2DSound(const char* soundFile, bool looped, bool paused, bool track);
		virtual void play3DSound(const char* soundFile, Aftr::Vector position, bool playLooped, bool paused, bool track);
		virtual void pauseAll2DSounds();
		virtual void pauseAll3DSounds();
		virtual void resumeAll2DSounds();
		virtual void resumeAll3DSounds();
		virtual void stopAll2DSounds();
		virtual void stopAll3DSounds();
		virtual irrklang::vec3df convertFromVector(Vector position);
		virtual irrklang::ISoundEngine* getSoundEngine();
		virtual std::vector<irrklang::ISound*> get2DSound();
		virtual std::vector<irrklang::ISound*> get3DSound();
	};
}