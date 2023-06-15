#include "_Game.h"
#include "node.h"
#include "required\stands.h"

Node::Node(std::vector<GameObject*>* stand)
	:stand(stand)
{
	is_occupied = false;
	contains_soldier = false;
}

Node::~Node()
{
	if (stand == trench_stand.stand) {
		for (size_t i = 0; i < trench_nodes.size(); i++) {
			if (trench_nodes.at(i) == gameObject) {
				trench_nodes.erase(trench_nodes.begin() + i);
				break;
			}
		}
	}
	else if (stand == hiding_stand.stand) {
		for (size_t i = 0; i < hiding_nodes.size(); i++) {
			if (hiding_nodes.at(i) == gameObject) {
				hiding_nodes.erase(hiding_nodes.begin() + i);
				break;
			}
		}
	}
}

void Node::OnStart() {
	
}

void Node::OnStop() {
	
}

void Node::OnUpdate() {

}

