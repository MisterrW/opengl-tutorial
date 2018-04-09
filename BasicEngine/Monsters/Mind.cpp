#include "Mind.h"
using namespace BasicEngine::Monsters;

Mind::Mind()
{

}

Mind::Mind(std::vector<Behaviour> behaviours)
{
	this->behaviours = behaviours;
	// set default active behaviour
};

void Mind::setActiveBehaviour(models, monsters, player, health)
{
	// this will select an active behaviour by querying the available behaviours to get a suitability score based on the gamestate, and picking the behaviour with the best score
};

// the function which takes in all the gamestate and decides what to do
// it will call setActiveBehaviour(), and then behave()
void Mind::think(models, monsters, player, health)
{
	this->setActiveBehaviour(models, monsters, player, health);
	this->activeBehaviour->behave(models, monsters, player, health);
};

// passes this query through to the active behaviour
// will probably end up with modifiers like desired speed (enum)
glm::vec3 Mind::getDesiredPosition()
{
	return this->activeBehaviour->getDesiredPosition();
};

// passes this query through to the active behaviour
// do this for now, assuming that monsters always attack directly in front of them. The specifics of who is being attacked / targeted should be internal to the mind anyway, but we will probably need to share details like which weapon / attack type.
// we will do something similar for sounds as well, ultimately both will probably be enums.
bool Mind::checkIfAttacking()
{
	return this->activeBehaviour->checkIfAttacking();
};

			// think about how this is going to be set. Unique ids a thought. Or using a map to behaviour names?
			//void setActiveBehaviour(all required state);
