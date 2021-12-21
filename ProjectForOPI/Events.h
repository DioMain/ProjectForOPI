#pragma once
#include <iostream>
#include "DefaultMath.h"
#include "GraphicEngine.h"
#include "Physics.h"
#include "Vars.h"

using namespace CE;
using namespace std;

namespace Game {
	
	void testEvent() {
		system("cls");

		cout << "Event is work!!!" << endl;
		cout << "AYE" << endl;

		system("pause");
	}
	
	void EventF() {
		system("cls");

		cout << "Let's go fight!!!" << endl;

		system("pause");
	}

	void EventUnit() {
		GameObject* object = Collision::Overlap(&MainMap, &Player);

		if ((*object).type == ObjectType::action) {
			if ((*object).tag == "test") testEvent();
			else if ((*object).tag == "F") EventF();

			MainMap.deleteGameObject(object);
		}
	}
}