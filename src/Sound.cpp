#include "Sound.h"

using namespace Aftr;
using namespace std;

SoundManager* SoundManager::init() {
	SoundManager* SM = new SoundManager();
	SM->engine = irrklang::createIrrKlangDevice();
	return SM;
}

void SoundManager::play2DSound(const char* soundFile, bool looped, bool paused, bool track) {
	this->sound2D.push_back(this->engine->play2D(soundFile, looped, paused, track));
}

void SoundManager::play3DSound(const char* soundFile, Aftr::Vector position, bool playLooped, bool paused, bool track) {
	this->sound3D.push_back(this->engine->play3D(soundFile, this->convertFromVector(position), playLooped, paused, track));
}

void SoundManager::pauseAll2DSounds() {
	if (sound2D.empty()) {
		return;
	}
	else {
		for (int i = 0; i < sound2D.size(); i++) {
			sound2D.at(i)->setIsPaused(true);
		}
	}
}

void SoundManager::pauseAll3DSounds() {
	if (sound3D.empty()) {
		return;
	}
	else {
		for (int i = 0; i < sound3D.size(); i++) {
			sound3D.at(i)->setIsPaused(true);
		}
	}
}

void SoundManager::resumeAll2DSounds() {
	if (sound2D.empty()) {
		return;
	}
	else {
		for (int i = 0; i < sound2D.size(); i++) {
			sound2D.at(i)->setIsPaused(false);
		}
	}
}

void SoundManager::resumeAll3DSounds() {
	if (sound3D.empty()) {
		return;
	}
	else {
		for (int i = 0; i < sound3D.size(); i++) {
			sound3D.at(i)->setIsPaused(false);
		}
	}
}

void SoundManager::stopAll2DSounds() {
	if (sound2D.empty()) {
		return;
	}
	else {
		for (int i = 0; i < sound2D.size(); i++) {
			sound2D.at(i)->stop();
		}
	}
}

void SoundManager::stopAll3DSounds() {
	if (sound3D.empty()) {
		return;
	}
	else {
		for (int i = 0; i < sound3D.size(); i++) {
			sound3D.at(i)->stop();
		}
	}
}

irrklang::vec3df SoundManager::convertFromVector(Vector position) {
	return irrklang::vec3df(position.x, position.y, position.z);
}

irrklang::ISoundEngine* SoundManager::getSoundEngine() {
	return this->engine;
}

std::vector<irrklang::ISound*> SoundManager::get2DSound() {
	return this->sound2D;
}

std::vector<irrklang::ISound*> SoundManager::get3DSound() {
	return this->sound3D;
}