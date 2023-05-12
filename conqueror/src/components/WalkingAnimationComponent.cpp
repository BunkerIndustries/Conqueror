#include "_Game.h"
#include "WalkingAnimationComponent.h"

#include <corecrt_math_defines.h>

#include "required/functions.h"
#include "required/constants.h"

WalkingAnimation::WalkingAnimation(){}
WalkingAnimation::WalkingAnimation(glm::ivec2 indexStartUp, glm::ivec2 indexEndUp, glm::ivec2 indexStartDown, glm::ivec2 indexEndDown, glm::ivec2 indexStartRight, glm::ivec2 indexEndRight, glm::ivec2 indexStartLeft, glm::ivec2 indexEndLeft, int animationSpeed, int spriteSheetLength)
    : indexStartUp(indexStartUp), indexEndUp(indexEndUp), indexStartDown(indexStartDown), indexEndDown(indexEndDown), indexStartRight(indexStartRight), indexEndRight(indexEndRight), indexStartLeft(indexStartLeft), indexEndLeft(indexEndLeft), animationSpeed(animationSpeed), spriteSheetLength(spriteSheetLength) {}

std::string WalkingAnimation::CalculateDirection() {
    glm::ivec2 direction = gameObject->GetComponent<Movement>()->GetDirection(); // Example direction vector

    float angle = std::atan2(direction.y, direction.x); // Calculate the angle in radians

    // Convert the angle to degrees and shift it to the positive range [0, 360)
    float degrees = std::fmod((std::fmod(angle, 2 * glm::pi<float>()) + 2 * glm::pi<float>()), (2 * glm::pi<float>())) * (180.0f / glm::pi<float>());

    std::string directionString;

    // Determine the direction based on the angle
    if (degrees > 45 && degrees <= 135)
        Start(indexStartUp, indexEndUp);
    else if (degrees > 135 && degrees <= 225)
        Start(indexStartLeft, indexEndLeft);
    else if (degrees > 225 && degrees <= 315)
        Start(indexStartDown, indexEndDown);
    else
        Start(indexStartRight, indexEndRight);

    return directionString;
}


void WalkingAnimation::OnUpdate() {
    if (gameObject->GetComponent<Movement>()->IsArrived() == false)
    {
        CalculateDirection();
    }
    else
    {

    }
}


void WalkingAnimation::Start(glm::ivec2 indexStart, glm::ivec2 indexEnd) {
    static int animationLength = indexEnd.x - indexStart.x + 1;
    static int tex = 0;
    static float x = 0.01f;
    x += Application::GetDT() / animationSpeed;

    tex = (int)(x * 100);

    if (tex % (animationLength + 1) == 0)
    {
        x = 0.01f;
        tex = (int)(x * 100);
    }
    LOG_DEBUG(indexStart.y);
    gameObject->GetComponent<SpriteSheet>()->ChangeSprite(glm::ivec2(tex + indexStart.x, indexStart.y));
}
