#include "_Core.h"

#include "generic/Camera.h"
#include "generic/Application.h"

namespace core {

    Camera::Camera() {
        // standard position of the camera
        position = glm::vec3(0.0f, 0.0f, 5.0f);
        // standard fov
        fov = 45.0f;
    }

    Camera::~Camera() {}


    void Camera::calcCameraVectors() {
        //set vectors
        // the camera has to look somewhere (just set it to 0 because we are making it absolute)

        this->target = glm::vec3(this->position.x, this->position.y, 0.0f);
        // move every gameObject that is orthographic before the camera moves
        for (auto& go : Application::GetCurrentScene()->getGameObjects()) {
            if (go->displayMode == DataPool::DISPLAYMODE::ORTHOGRAPHIC) {
                go->transform.position.x = target.x + 1;
                go->transform.position.y = target.y + 1;
            }
        }

        // this is being used for pointing upwards (y globally, e.g. in the world)
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        // declare z-axis
        cameraDirection = glm::normalize(position - target);
        // declare x-axis by the cross-product
        cameraRight = glm::normalize(glm::cross(up, cameraDirection));
        // declare y-axis by the cross-product of z and x
        cameraUp = glm::cross(cameraDirection, cameraRight);
        // make camera depend on position (who could have thought this)
        cameraViewMatrix = glm::lookAt(position, target, up);
    }

    glm::mat4 Camera::getViewMatrix() {
        // give camera an "eye"
        return cameraViewMatrix;
    }

    glm::mat4 Camera::getReverseViewMatrix() {
        return glm::inverse(Camera::getViewMatrix());
    }

    glm::mat4 Camera::getProjectionMatrix() {
        // get aspect ratio because we need it in order to project the camera correctly
        float aspect = (float)Application::GetWindow()->getWidth() / (float)Application::GetWindow()->getHeight();
        return glm::perspective(fov, aspect, 0.1f, 1000.0f);
    }

    glm::mat4 Camera::getOrthographicMatrix()
    {
        // ortograhpic camera is basically a custom coordinate system with one's own units
        // every gameobject has the option to be rendered relative to orthographic or to projection
        return glm::ortho(0.0f, 2.0f, 0.0f, 2.0f, 0.0f, 10000000.0f);
    }

    glm::mat4 Camera::getReverseProjectionMatrix() {
        return glm::inverse(Camera::getProjectionMatrix());
    }

}
