#include "_Core.h"

#include "renderer/Mesh.h"

namespace core {

    Mesh::Mesh(Transform transform, int zIndex) {
        this->zIndex = zIndex;
        this->transform = transform;
        lastTransform = transform.copy();
    }

    void Mesh::addGameObject(GameObject* gameObject, int x, int y) {
        if (x < 0 && -x > coord.ZERO_OFFSET_X) {
            int dx = -(coord.ZERO_OFFSET_X + x);
            coord.ZERO_OFFSET_X = -x;
            coord.width += dx;
            std::reverse(coord.map.begin(), coord.map.end());
            coord.map.resize(coord.width, std::vector<GameObject*>());
            std::reverse(coord.map.begin(), coord.map.end());

            for (int i = 0; i < coord.map.size(); i++) {
                coord.map[i].resize(coord.height, nullptr);
            }
        }
        else if (x + 1 > coord.width - coord.ZERO_OFFSET_X) {
            std::cout << "x: " << x << std::endl;

            coord.width = coord.ZERO_OFFSET_X + x + 1;
            coord.map.resize(coord.width, std::vector<GameObject*>());

            std::cout << coord.width << std::endl;

            for (int i = 0; i < coord.map.size(); i++) {
                coord.map[i].resize(coord.height, nullptr);
            }
        }
        if (y < 0 && -y > coord.ZERO_OFFSET_Y) {
            int dy = -(coord.ZERO_OFFSET_Y + y);
            coord.ZERO_OFFSET_Y = -y;
            coord.height += dy;
            for (int i = 0; i < coord.map.size(); i++) {
                std::reverse(coord.map[i].begin(), coord.map[i].end());
                coord.map[i].resize(coord.height, nullptr);
                std::reverse(coord.map[i].begin(), coord.map[i].end());
            }
        }
        else if (y + 1 > coord.height - coord.ZERO_OFFSET_Y) {
            coord.height = coord.ZERO_OFFSET_Y + y;
            for (int i = 0; i < coord.map.size(); i++) {
                coord.map[i].resize(coord.height, nullptr);
            }
        }

        std::cout << x << "/" << coord.map.size() << " | " << y << "/" << coord.map[0].size() << std::endl;

        if (!gameObject) return;

        //change the objects transform, so it maches the transform from the mesh
        gameObject->transform.position = glm::vec2(this->transform.position.x + x * 1.1f, this->transform.position.y + y * 1.1f);
        gameObject->transform.scale = this->transform.scale;
        gameObject->SetZIndex(this->zIndex);


        coord.getMap()[coord.ZERO_OFFSET_X + x][coord.ZERO_OFFSET_Y + y] = gameObject; //ERROR TODO: HERE IS ERROR MAYBE BECAUSE OF COPYING INSTEAD OF REFERENCE
        //std::cout << "GameObject: " << gameObject << std::endl;
        //std::cout << coord.ZERO_OFFSET_X + x << " | " << coord.ZERO_OFFSET_Y + y << " <|> " << coord.getMap()[0][0] << std::endl;
        return;
        /*
        //resize "map"
        if (x >= 0 && mapCol <= x) {
            gameObjectMap.resize(x + 1 + indexRep0_X, std::vector<GameObject*>());
            mapCol = x + 1;
            for (std::vector<GameObject*>& rowVec : gameObjectMap) {
                rowVec.resize(mapRow, nullptr);
            }
        } else if (x < 0) {
            //  0  1  2 3 4 5 6 7 8 9 10
            // -3 -2 -1 0 1 2 3 4 5 6 7

            if (-x > indexRep0_X) {
                indexRep0_X = -x;
                x = x + indexRep0_X;
                printf("%p\n", &gameObjectMap[0]);
                std::reverse(gameObjectMap.begin(), gameObjectMap.end());
                gameObjectMap.resize(indexRep0_X, std::vector<GameObject*>());
                std::reverse(gameObjectMap.begin(), gameObjectMap.end());
                printf("%p\n", &gameObjectMap[0]);
            }

        }

        if (mapRow <= y) {
            for (std::vector<GameObject*>& rowVec : gameObjectMap) {
                rowVec.resize(y + 1, nullptr);
                mapRow = y + 1;
            }
        }



        //add gameobject to "map"
        gameObjectMap[x][y] = gameObject;

        std::cout << gameObjectMap.size() << " | " << indexRep0_X << std::endl;
        */
    }

    void Mesh::update(float dt) {
        if (!(this->transform.equals(*lastTransform)))
        {
            // if it is not equal, save it to the local transform and
            // set the dirty bit (variable that is being checked in order to display changes)
            this->transform.copy(*this->lastTransform);
            for (int x = 0; x < coord.width; x++) {
                for (int y = 0; y < coord.height; y++) {
                    coord.map[x][y]->transform.position = glm::vec2(this->transform.position.x + x * 1.1f, this->transform.position.y + y * 1.1f);
                    coord.map[x][y]->transform.scale = this->transform.scale;
                }
            }
        }
    }

    void GameObjectMap::resize(int x, int y) {
        map.resize(x + 1, std::vector<GameObject*>());
        for (std::vector<GameObject*>& rowVec : map) {
            rowVec.resize(y + 1, nullptr);
        }
        width = map.size();
        height = map[0].size();
    }

    std::vector<std::vector<GameObject*>>& GameObjectMap::getMap() {
        return this->map;
    }

}