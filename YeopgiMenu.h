#pragma once

#include "Menu.h"

class YeopgiMenu : public Menu {
private:
	bool canChoiceTaste;
	bool canChoiceTopping;

public:
	void init(int id, string name, int price, bool canChoiceTaste, bool canChoiceTopping) {
		this->id = id;
		this->name = name;
		this->price = price;
		this->canChoiceTaste = canChoiceTaste;
		this->canChoiceTopping = canChoiceTopping;
	}

	bool getCanChoiceTaste() {
		return canChoiceTaste;
	}

	bool getCanChoiceTopping() {
		return canChoiceTopping;
	}
};