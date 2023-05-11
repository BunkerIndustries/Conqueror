#include "_Game.h"
#include "WalkingAnimationComponent.h"

#include <corecrt_math_defines.h>

#include "required/functions.h"
#include "required/constants.h"

WalkingAnimation::WalkingAnimation(){}
WalkingAnimation::WalkingAnimation(glm::vec2 indexStartUp, glm::vec2 indexEndUp, glm::vec2 indexStartDown, glm::vec2 indexEndDown, glm::vec2 indexStartRight, glm::vec2 indexEndRight, glm::vec2 indexStartLeft, glm::vec2 indexEndLeft, int animationSpeed, int spriteSheetLength)
    : indexStartUp(indexStartUp), indexEndUp(indexEndUp), indexStartDown(indexStartDown), indexEndDown(indexEndDown), indexStartRight(indexStartRight), indexEndRight(indexEndRight), indexStartLeft(indexStartLeft), indexEndLeft(indexEndLeft), animationSpeed(animationSpeed), spriteSheetLength(spriteSheetLength) {}

std::string WalkingAnimation::CalculateDirection() {
    glm::vec2 direction = gameObject->GetComponent<Movement>()->GetDirection(); // Example direction vector

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

        std::cout << "arrived";
    }
}


void WalkingAnimation::Start(glm::vec2 indexStart, glm::vec2 indexEnd) {
    static int animationLength = indexEnd[0] - indexStart[0];
    std::cout << animationLength;
    static int tex = 0;
    static float x = 0.0f;
    x += Application::GetDT() / animationLength;

    tex = (int)(x * 100);

    if (tex % animationLength == 0)
    {
        x = 0.01f;
    }

    gameObject->GetComponent<SpriteSheet>()->ChangeSprite(glm::vec2(tex + indexStart[0], indexStart[1]));
}
