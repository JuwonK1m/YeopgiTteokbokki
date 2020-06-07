#pragma once

#include <iostream>
#include <vector>
#include <utility>

using namespace std;

class Order {
private:
	vector<pair<string, int>> orderedMenuList;
	int amount;

public:
	Order() : amount(0) {}

	void add(pair<string, int> orderedMenu) {
		orderedMenuList.push_back(orderedMenu);

		amount += orderedMenu.second;
	}

	int getAmount() {
		return amount;
	}

	bool isEmpty() {
		return orderedMenuList.empty() ? true : false;
	}

	void printOrderedMenuList() {
		if (orderedMenuList.empty()) {
			cout << "현재 주문 내역이 없습니다." << '\n';
			return;
		}

		cout << "<현재까지의 주문 내역>\n";
		cout << "'+'는 메뉴에 대한 옵션을 나타냅니다.\n";
		for (int i = orderedMenuList.size() - 1; i >= 0; i--) {
			string menuInformation = orderedMenuList[i].first;
			int price = orderedMenuList[i].second;

			cout << menuInformation << " --> " << price << "원\n";
		}

		cout << "-------------------------------------------------------\n";

		cout << "총 금액: " << amount << "원\n\n";
	}

	void order() {
		cout << "<결제 내역>\n";

		while (!orderedMenuList.empty()) {
			string menuInformation = orderedMenuList[orderedMenuList.size() - 1].first;
			int price = orderedMenuList[orderedMenuList.size() - 1].second;

			orderedMenuList.erase(orderedMenuList.end() - 1);

			cout << menuInformation << " --> " << price << "원\n";
		}

		cout << "-------------------------------------------------------\n";

		cout << "총 금액: " << amount << "원\n\n";
		amount = 0;
	}
};