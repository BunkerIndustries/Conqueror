#include "node.h"

Node::Node(std::vector<GameObject*>* stand)
	:stand(stand)
{

}

void Node::start() {
	is_occupied = false;
	stand = nullptr;
}

void Node::stop() {

}

void Node::update(float dt) {

}

