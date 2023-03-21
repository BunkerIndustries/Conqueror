#include "_Game.h"
#include "node.h"

Node::Node(std::vector<GameObject*>* stand)
	:stand(stand)
{

}

void Node::OnStart() {
	is_occupied = false;
}

void Node::OnStop() {

}

void Node::OnUpdate() {

}

