#include "EnemyMillBehavior.h"
#include <iostream>

void EnemyMillBehavior::ReachedEndOfMill()
{
	if (taggedEnd) return; 

	std::cout << "Enemy has reached the end of the mill!" << std::endl;
	taggedEnd = true;
}
