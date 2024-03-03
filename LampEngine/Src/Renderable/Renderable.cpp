#include "Renderable.h"

namespace LampEngine {
	Renderable::Renderable() :
		cullMode(CULL_MODE::BACK_CULL),
		depthTest(true) 
	{
	}

	void Renderable::render() {
		// Depth test
		if (depthTest) {
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LESS);
		}
		else
			glDisable(GL_DEPTH_TEST);
		// Cull Mode
		switch (cullMode) {
		case LampEngine::CULL_MODE::NO_CULL:
			glDisable(GL_CULL_FACE);
			break;
		case LampEngine::CULL_MODE::FRONT_CULL:
			glEnable(GL_CULL_FACE);
			glCullFace(GL_FRONT);
			break;
		case LampEngine::CULL_MODE::BACK_CULL:
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
			break;
		}
	}
}