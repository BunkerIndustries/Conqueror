#include "_Game.h"
#include "node.h"
#include "required\stands.h"

Node::Node(std::vector<GameObject*>* stand)
	:stand(stand)
{

}

void Node::OnStart() {
	is_occupied = false;
}

void Node::OnStop() {
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

void Node::OnUpdate() {

}

