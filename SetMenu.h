#pragma once

#include "Menu.h"

class SetMenu : public Menu {
private:
	string description;

public:
	void init(int id, string name, string description, int price) {
		this->id = id;
		this->name = name;
		this->description = description;
		this->price = price;
	}

	string getDesctiption() {
		return description;
	}
};