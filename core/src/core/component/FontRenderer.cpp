#include "_Core.h"

#include "component/FontRenderer.h"

namespace core {

    //FONTRENDERER
    FontRenderer::FontRenderer()
	    : Component("font_renderer")
	{
        // pascal you are funny
        LOG_CORE_DEBUG("FOUND FONT RENDERER");
    }

    FontRenderer::~FontRenderer() {

    }

    void FontRenderer::start() {

    }

    void FontRenderer::update(float dt) {

    }

}