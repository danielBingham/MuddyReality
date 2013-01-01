#ifndef _BEING_H_
#define _BEING_H_

class Model;
class Race;
class Subrace;
class Skill;
class BeingSkill;
class Object;

#define ABILITY_STR	0
#define ABILITY_DEX	1
#define ABILITY_CON	2
#define ABILITY_INT	3
#define ABILITY_WIS	4
#define ABILITY_WIL	5
#define ABILITY_PER	6
#define ABILITY_CHA	7
#define NUMBER_OF_ABILITIES	8

#define STAT_CURRENT	0
#define STAT_MAXIMUM	1

#define EQUIPMENT_RIGHT_HAND		0
#define EQUIPMENT_LEFT_HAND			1
#define EQUIPMENT_TORSO				2
#define EQUIPMENT_LEGS				3
#define EQUIPMENT_ARMS				4
#define EQUIPMENT_GLOVES			5
#define EQUIPMENT_BOOTS				6
#define EQUIPMENT_BELT				7
#define EQUIPMENT_BACKPACK			8
#define EQUIPMENT_HEAD				9
#define EQUIPMENT_RING_START		10
#define EQUIPMENT_RING_END			20
#define EQUIPMENT_NECKLACE_START	21
#define EQUIPMENT_NECKLACE_END		30
#define EQUIPMENT_CAPE				31
#define EQUIPMENT_MAX				32

class BeingSkill {
	Skill *skill;
	int knowledge;
}

class Being: public Model {
	public:
		String name;
		String description;
		
		Race *race;
		Subrace *subrace;

		// Stats
		int abilities[NUMBER_OF_ABILITIES];
		int baseAbilities[NUMBER_OF_ABILITIES];

		int health[2], mana[2], movement[2];

		Object *equipment[EQUIPMENT_MAX];
		BeingSkill **skills;
}

class Race: public Model {
	public:
		String name;
		String description;

		Subrace **subraces;
}

class Subrace: public Model {
	public:
		int baseAbilities[NUMBER_OF_ABILITIES];
}

class Skill: public Model {
	public:
		String name;
		String description;	
}

#endif // _BEING_H_
