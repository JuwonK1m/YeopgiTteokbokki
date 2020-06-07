#pragma once

#include <string>

using namespace std;

class Menu {
protected:
	int id;
	string name;
	int price;

public:
	void init(int id, string name, int price) {
		this->id = id;
		this->name = name;
		this->price = price;
	}

	int getId() {
		return id;
	}

	string getName() {
		return name;
	}

	int getPrice() {
		return price;
	}
};