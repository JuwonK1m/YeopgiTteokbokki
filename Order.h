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
			cout << "���� �ֹ� ������ �����ϴ�." << '\n';
			return;
		}

		cout << "<��������� �ֹ� ����>\n";
		cout << "'+'�� �޴��� ���� �ɼ��� ��Ÿ���ϴ�.\n";
		for (int i = orderedMenuList.size() - 1; i >= 0; i--) {
			string menuInformation = orderedMenuList[i].first;
			int price = orderedMenuList[i].second;

			cout << menuInformation << " --> " << price << "��\n";
		}

		cout << "-------------------------------------------------------\n";

		cout << "�� �ݾ�: " << amount << "��\n\n";
	}

	void order() {
		cout << "<���� ����>\n";

		while (!orderedMenuList.empty()) {
			string menuInformation = orderedMenuList[orderedMenuList.size() - 1].first;
			int price = orderedMenuList[orderedMenuList.size() - 1].second;

			orderedMenuList.erase(orderedMenuList.end() - 1);

			cout << menuInformation << " --> " << price << "��\n";
		}

		cout << "-------------------------------------------------------\n";

		cout << "�� �ݾ�: " << amount << "��\n\n";
		amount = 0;
	}
};