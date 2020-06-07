#pragma once

#include <string>

using namespace std;

class Taste {
private:
	int id;
	string taste;

public:
	void init(int id, string taste) {
		this->id = id;
		this->taste = taste;
	}

	int getId() {
		return id;
	}

	string getTaste() {
		return taste;
	}
};