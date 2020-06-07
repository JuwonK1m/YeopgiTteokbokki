#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <cctype>
#include <conio.h>
#include "YeopgiMenu.h"
#include "Topping.h"
#include "SideAndDrink.h"
#include "SetMenu.h"
#include "Taste.h"
#include "Order.h"
#define YEOPGIMENU_SIZE 10
#define SIDEANDDRINK_SIZE 16
#define TOPPING_SIZE 13
#define SETMENU_SIZE 5
#define TASTE_SIZE 6

using namespace std;

vector<YeopgiMenu> yeopgiMenu;
vector<SideAndDrink> sideAndDrink;
vector<Topping> topping;
vector<SetMenu> setMenu;
vector<Taste> taste;
Order order;
string tempInfo = "";
int tempPrice;
int tempId;

void initAllMenu(); // �޴����� �Ӽ� �ʱ�ȭ
int printMainScreen(); // ���� ȭ�� ���
bool isCorrectChoiceNum(const string& choice); // ����(�Է�) ���ڰ� ���� ���ڷ� �ԷµǾ����� Ȯ�� 
void printYeopgiMenu(); // ����޴� ���
void printTaste(); // �� ���
void printTopping(); // ���� ���
void printSideAndDrink(); // ���̵�/���� ���
void printSetMenu(); // ��Ʈ�޴� ���
void printSetMenuDetailChoice(); // ������ ��Ʈ�޴��� ���� ���λ��� ����
bool printChoiceOrder();  // �ֹ������� Ȯ���ϰ�, ������ �Ұ����� ����
void printOrder(); // ����

int main(void) {

	initAllMenu();

	// ���α׷� ����
	while (true) {
		int menuNum = printMainScreen();

		if (menuNum == 1) {
			printYeopgiMenu();
			printTaste();
			printTopping();
		}
		else if (menuNum == 2) {
			printSetMenu();
			printSetMenuDetailChoice();
		}
		else if (menuNum == 3)
			printSideAndDrink();
		else if (menuNum == 4) {}
		else
			break;

		if (printChoiceOrder())
			printOrder();
	}

	cout << "���α׷��� ����Ǿ����ϴ�.\n";

	return 0;
}

void initAllMenu() {
	// ����޴� �Ӽ��� �ʱ�ȭ
	// ���� ����: id, �̸�, ����, �� ���� ���� ����, ���� ���� ���� ����
	yeopgiMenu.resize(YEOPGIMENU_SIZE);
	yeopgiMenu[0].init(1, "���ⶱ����", 14000, true, true);
	yeopgiMenu[1].init(2, "�������", 14000, true, true);
	yeopgiMenu[2].init(3, "����ݹ�", 14000, true, true);
	yeopgiMenu[3].init(4, "����ߺ�����", 24000, true, false);
	yeopgiMenu[4].init(5, "2�� ���ⶱ����", 9000, true, true);
	yeopgiMenu[5].init(6, "���� ������ �߹�", 15000, false, false);
	yeopgiMenu[6].init(7, "�����߹�", 15000, false, false);
	yeopgiMenu[7].init(8, "���� ��߹�", 14000, false, false);
	yeopgiMenu[8].init(9, "������", 14000, false, false);
	yeopgiMenu[9].init(10, "�����߳���", 14000, false, false);

	// ���̵�/���� �Ӽ��� �ʱ�ȭ
	// ���� ����: id, �̸�, ����
	sideAndDrink.resize(SIDEANDDRINK_SIZE);
	sideAndDrink[0].init(1, "���Ƣ��", 2000);
	sideAndDrink[1].init(2, "�踻��", 2000);
	sideAndDrink[2].init(3, "��äƢ��", 1000);
	sideAndDrink[3].init(4, "Ƣ�踸��", 2000);
	sideAndDrink[4].init(5, "������", 2000);
	sideAndDrink[5].init(6, "����ġŲ", 2000);
	sideAndDrink[6].init(7, "ġ�ƽ", 2000);
	sideAndDrink[7].init(8, "�ٻ�ġ���", 2000);
	sideAndDrink[8].init(9, "����", 3000);
	sideAndDrink[9].init(10, "�ָԱ��(�α�޴�)", 2000);
	sideAndDrink[10].init(11, "�����", 2000);
	sideAndDrink[11].init(12, "�����ä��", 5000);
	sideAndDrink[12].init(13, "������", 10000);
	sideAndDrink[13].init(14, "��������", 5000);
	sideAndDrink[14].init(15, "�����", 1000);
	sideAndDrink[15].init(16, "����(�����)", 1000);

	// ���� �Ӽ��� �ʱ�ȭ
	// ���� ����: id, �̸�, ����
	topping.resize(TOPPING_SIZE);
	topping[0].init(1, "ġ��", 3000);
	topping[1].init(2, "��", 1000);
	topping[2].init(3, "������", 3000);
	topping[3].init(4, "���߰�", 1000);
	topping[4].init(5, "�����߰�", 1000);
	topping[5].init(6, "����ġ���", 2000);
	topping[6].init(7, "���", 1500);
	topping[7].init(8, "���߸���", 1000);
	topping[8].init(9, "�߱����", 2500);
	topping[9].init(10, "���縮", 1000);
	topping[10].init(11, "�쵿�縮", 2000);
	topping[11].init(12, "���縮", 2000);
	topping[12].init(13, "���� ���� ����", 0);

	// ��Ʈ�޴� �ʱ�ȭ
	// ���� ����: id, �̸�, ����, ����
	setMenu.resize(SETMENU_SIZE);
	setMenu[0].init(1, "A SET", "���� OR ���� OR �ݹ� �� �� 1 + ���Ƣ�� + ��� 2�� OR ���߸��� 5�� �� �� 1", 17000);
	setMenu[1].init(2, "B SET", "���� OR ���� OR �ݹ� �� �� 1 + ���Ƣ�� + ��� 2�� OR ���߸��� 5�� �� �� 1 + �ָԱ��", 19000);
	setMenu[2].init(3, "C SET", "���� OR ���� OR �ݹ� �� �� 1 + ���Ƣ�� + ��� 2�� OR ���߸��� 5�� �� �� 1 + �ָԱ�� + ���", 21000);
	setMenu[3].init(4, "FAMILY SET", "���� OR ���� OR �ݹ� �� �� 1 + �����޴� �� �� 1 + �ָԱ��", 28000);
	setMenu[4].init(5, "���� SET", "�����޴� �� �� 1 + �ָԱ��", 16000);

	// �� �ʱ�ȭ
	// ���� ����: id, ��
	taste.resize(TASTE_SIZE);
	taste[0].init(1, "�ſ��");
	taste[1].init(2, "�������θ�");
	taste[2].init(3, "���ſ��");
	taste[3].init(4, "�����ʺ���");
	taste[4].init(5, "¥���");
	taste[5].init(6, "���Ѹ�");
}

int printMainScreen() {
	string choice;

	do {
		cout << "<���빮 ���ⶱ����>" << '\n';
		cout << "1. ����޴�" << '\n';
		cout << "2. ��Ʈ�޴�" << '\n';
		cout << "3. ���̵�/����" << '\n';
		cout << "4. �ֹ����� ����" << '\n';
		cout << "5. ����" << '\n';
		cout << "�����Ͻÿ� >> ";
		cin >> choice;

		cout << '\n';
	} while ((choice != "1") && (choice != "2") && (choice != "3") && (choice != "4")); // ��ȿ�� ��ȣ���� �˻�

	return atoi(choice.c_str());
}

bool isCorrectChoiceNum(const string& choice) {
	if ((atoi(choice.c_str()) == 0) || (choice.empty()))
		return false;

	if (choice[0] == '0')
		return false;

	for (int i = 0; i < choice.size(); i++) {
		if (!isdigit(choice[i]))
			return false;
	}

	return true;
}

void printYeopgiMenu() {
	string choiceId;
	int choiceId_;

	do {
		cout << "<����޴�>\n";
		for (YeopgiMenu ym : yeopgiMenu)
			printf("%d. %s - %d��\n", ym.getId(), ym.getName().c_str(), ym.getPrice());

		cout << "�����Ͻÿ� >> ";
		cin >> choiceId;

		choiceId_ = atoi(choiceId.c_str());

		cout << '\n';
	} while ((!isCorrectChoiceNum(choiceId)) || (choiceId_ > YEOPGIMENU_SIZE) || (choiceId_ < 1)); // ��ȿ�� id���� �˻�

	tempInfo += yeopgiMenu[choiceId_ - 1].getName();
	tempId = choiceId_;
	tempPrice += yeopgiMenu[choiceId_ - 1].getPrice();

	cout << yeopgiMenu[choiceId_ - 1].getName() << "��(��) �����ϼ̽��ϴ�. ����Ϸ��� �ƹ�Ű�� �����ʽÿ�.\n";
	_getch();
	cout << '\n';
}

void printTaste() {
	if (!yeopgiMenu[tempId - 1].getCanChoiceTaste()) {
		order.add(make_pair(tempInfo, tempPrice));
		tempInfo = "";
		tempPrice = 0;
		return;
	}

	string choiceId;
	int choiceId_;

	cout << yeopgiMenu[tempId - 1].getName() << "�� ���� �����Ͻʽÿ�.\n";
	do {
		for (Taste t : taste) {
			// 2�� ���ⶱ���̸� �����ʺ���/¥����� �����Ƿ� �ǳʶ�
			if (((t.getTaste() == "�����ʺ���") || (t.getTaste() == "¥���")) && (yeopgiMenu[tempId - 1].getName() == "2�� ���ⶱ����"))
				continue;

			printf("%d. %s\n", t.getId(), t.getTaste().c_str());
		}

		cout << "�����Ͻÿ� >> ";
		cin >> choiceId;

		choiceId_ = atoi(choiceId.c_str());

		cout << '\n';
	} while ((!isCorrectChoiceNum(choiceId)) || (choiceId_ > TASTE_SIZE) || (choiceId_ < 1)
		|| ((yeopgiMenu[tempId - 1].getName() == "2�� ���ⶱ����") && ((taste[choiceId_ - 1].getTaste() == "�����ʺ���") || (taste[choiceId_ - 1].getTaste() == "¥���")))); // ��ȿ�� id���� �˻�

	tempInfo += (" + " + taste[choiceId_ - 1].getTaste());

	cout << taste[choiceId_ - 1].getTaste() << "��(��) �����ϼ̽��ϴ�. ����Ϸ��� �ƹ�Ű�� �����ʽÿ�.\n";
	_getch();
	cout << '\n';
}

void printTopping() {
	if (!yeopgiMenu[tempId - 1].getCanChoiceTopping()) {
		if (!yeopgiMenu[tempId - 1].getCanChoiceTaste())
			return;

		order.add(make_pair(tempInfo, tempPrice));
		tempInfo = "";
		tempPrice = 0;
		return;
	}

	string choiceId;
	int choiceId_;
	string continueChoiceToppingAnswer;
	bool continueChoiceTopping = true; // ������ ����ؼ� �ֹ��� �������� ���� ����

	cout << yeopgiMenu[tempId - 1].getName() << "�� ���� ������ �����Ͻʽÿ�.\n";
	while (continueChoiceTopping) {
		do {
			for (Topping t : topping)
				printf("%d. %s - %d��\n", t.getId(), t.getName().c_str(), t.getPrice());

			cout << "�����Ͻÿ� >> ";
			cin >> choiceId;

			choiceId_ = atoi(choiceId.c_str());

			cout << '\n';
		} while ((!isCorrectChoiceNum(choiceId)) || (choiceId_ > TOPPING_SIZE) || (choiceId_ < 1));

		if (topping[choiceId_ - 1].getName() != "���� ���� ����") {
			tempInfo += (" + " + topping[choiceId_ - 1].getName());
			tempPrice += topping[choiceId_ - 1].getPrice();
		}

		do {
			cout << "������ �� �ֹ��Ͻðڽ��ϱ�?(y �Ǵ� n) >> ";
			cin >> continueChoiceToppingAnswer;

			cout << '\n';
		} while ((continueChoiceToppingAnswer != "y") && (continueChoiceToppingAnswer != "n"));

		if (continueChoiceToppingAnswer == "n")
			continueChoiceTopping = false;
	}

	order.add(make_pair(tempInfo, tempPrice));
	tempInfo = "";
	tempPrice = 0;
}

void printSideAndDrink() {
	if (order.isEmpty()) {
		cout << "����޴� �Ǵ� ��Ʈ�޴��� �ֹ��ϼž߸� ���̵�/���Ḧ �ֹ��Ͻ� �� �ֽ��ϴ�.\n";
		return;
	}

	string choiceId;
	int choiceId_;
	string continueChoiceSideAndDrinkAnswer;
	bool continueChoiceSideAndDrink = true; // ���̵�/���Ḧ ����ؼ� �ֹ��� �������� ���� ����

	cout << "<���̵�/����>\n";
	while (continueChoiceSideAndDrink) {
		do {
			for (SideAndDrink sd : sideAndDrink)
				printf("%d. %s - %d��\n", sd.getId(), sd.getName().c_str(), sd.getPrice());

			cout << "�����Ͻÿ� >> ";
			cin >> choiceId;

			choiceId_ = atoi(choiceId.c_str());

			cout << '\n';
		} while ((!isCorrectChoiceNum(choiceId)) || (choiceId_ > SIDEANDDRINK_SIZE) || (choiceId_ < 1));

		order.add(make_pair(sideAndDrink[choiceId_ - 1].getName(), sideAndDrink[choiceId_ - 1].getPrice()));
		cout << sideAndDrink[choiceId_ - 1].getName() << "��(��) �����ϼ̽��ϴ�.\n\n";

		do {
			cout << "���̵�/���Ḧ �� �ֹ��Ͻðڽ��ϱ�?(y �Ǵ� n) >> ";
			cin >> continueChoiceSideAndDrinkAnswer;

			cout << '\n';
		} while ((continueChoiceSideAndDrinkAnswer != "y") && (continueChoiceSideAndDrinkAnswer != "n"));

		if (continueChoiceSideAndDrinkAnswer == "n")
			continueChoiceSideAndDrink = false;
	}
}

void printSetMenu() {
	string choiceId;
	int choiceId_;

	do {
		cout << "<��Ʈ�޴�>\n";
		for (SetMenu sm : setMenu)
			printf("%d. %s (%s) - %d��\n", sm.getId(), sm.getName().c_str(), sm.getDesctiption().c_str(), sm.getPrice());

		cout << "�����Ͻÿ� >> ";
		cin >> choiceId;

		choiceId_ = atoi(choiceId.c_str());

		cout << '\n';
	} while ((!isCorrectChoiceNum(choiceId)) || (choiceId_ > SETMENU_SIZE) || (choiceId_ < 1));

	tempInfo += setMenu[choiceId_ - 1].getName();
	tempId = choiceId_;
	tempPrice += setMenu[choiceId_ - 1].getPrice();
}

void printSetMenuDetailChoice() {
	string choiceId;
	int choiceId_;

	if ((setMenu[tempId - 1].getName() == "A SET") || (setMenu[tempId - 1].getName() == "B SET") || (setMenu[tempId - 1].getName() == "C SET")) {
		cout << setMenu[tempId - 1].getName() << "�� ���λ����� �����Ͻʽÿ�.\n";

		do {
			for (int i = 0; i < 3; i++)
				printf("%d. %s\n", yeopgiMenu[i].getId(), yeopgiMenu[i].getName().c_str());

			cout << "�����Ͻÿ� >> ";
			cin >> choiceId;

			choiceId_ = atoi(choiceId.c_str());

			cout << '\n';
		} while ((!isCorrectChoiceNum(choiceId)) || (choiceId_ > 3) || (choiceId_ < 1));

		tempInfo += (" + " + yeopgiMenu[choiceId_ - 1].getName());
		tempInfo += " + ���Ƣ��";

		cout << yeopgiMenu[choiceId_ - 1].getName() << "��(��) �����ϼ̽��ϴ�. ����Ϸ��� �ƹ�Ű�� �����ʽÿ�.\n\n";
		_getch();

		do {
			for (int i = 6; i < 8; i++)
				printf("%d. %s\n", topping[i].getId(), topping[i].getName().c_str());

			cout << "�����Ͻÿ� >> ";
			cin >> choiceId;

			choiceId_ = atoi(choiceId.c_str());

			cout << '\n';
		} while ((!isCorrectChoiceNum(choiceId)) || (choiceId_ > 8) || (choiceId_ < 7));

		tempInfo += (" + " + topping[choiceId_ - 1].getName());

		cout << topping[choiceId_ - 1].getName() << "��(��) �����ϼ̽��ϴ�. ����Ϸ��� �ƹ�Ű�� �����ʽÿ�.\n\n";

		if (setMenu[tempId - 1].getName() == "B SET")
			tempInfo += " + �ָԱ��";
		else if (setMenu[tempId - 1].getName() == "C SET")
			tempInfo += " + �ָԱ�� + ���";
	}
	else if (setMenu[tempId - 1].getName() == "FAMILY SET") {
		cout << setMenu[tempId - 1].getName() << "�� ���λ����� �����Ͻʽÿ�.\n";

		do {
			for (int i = 0; i < 3; i++)
				printf("%d. %s\n", yeopgiMenu[i].getId(), yeopgiMenu[i].getName().c_str());

			cout << "�����Ͻÿ� >> ";
			cin >> choiceId;

			choiceId_ = atoi(choiceId.c_str());

			cout << '\n';
		} while ((!isCorrectChoiceNum(choiceId)) || (choiceId_ > 3) || (choiceId_ < 1));

		tempInfo += (" + " + yeopgiMenu[choiceId_ - 1].getName());
		cout << yeopgiMenu[choiceId_ - 1].getName() << "��(��) �����ϼ̽��ϴ�. ����Ϸ��� �ƹ�Ű�� �����ʽÿ�.\n\n";

		do {
			printf("%d. %s\n", yeopgiMenu[5].getId(), yeopgiMenu[5].getName().c_str());
			printf("%d. %s\n", yeopgiMenu[7].getId(), yeopgiMenu[7].getName().c_str());
			printf("%d. %s\n", yeopgiMenu[9].getId(), yeopgiMenu[9].getName().c_str());

			cout << "�����Ͻÿ� >> ";
			cin >> choiceId;

			choiceId_ = atoi(choiceId.c_str());

			cout << '\n';
		} while ((!isCorrectChoiceNum(choiceId)) || ((choiceId_ != 6) && (choiceId_ != 8) && (choiceId_ != 10)));

		tempInfo += (" + " + yeopgiMenu[choiceId_ - 1].getName());
		tempInfo += " + �ָԱ��";

		cout << yeopgiMenu[choiceId_ - 1].getName() << "��(��) �����ϼ̽��ϴ�. ����Ϸ��� �ƹ�Ű�� �����ʽÿ�.\n\n";
		_getch();
	}
	else {
		cout << setMenu[tempId - 1].getName() << "�� ���λ����� �����Ͻʽÿ�.\n";

		do {
			printf("%d. %s\n", yeopgiMenu[5].getId(), yeopgiMenu[5].getName().c_str());
			printf("%d. %s\n", yeopgiMenu[7].getId(), yeopgiMenu[7].getName().c_str());
			printf("%d. %s\n", yeopgiMenu[9].getId(), yeopgiMenu[9].getName().c_str());

			cout << "�����Ͻÿ� >> ";
			cin >> choiceId;

			choiceId_ = atoi(choiceId.c_str());

			cout << '\n';
		} while ((!isCorrectChoiceNum(choiceId)) || ((choiceId_ != 6) && (choiceId_ != 8) && (choiceId_ != 10)));

		tempInfo += (" + " + yeopgiMenu[choiceId_ - 1].getName());
		tempInfo += " + �ָԱ��";

		cout << yeopgiMenu[choiceId_ - 1].getName() << "��(��) �����ϼ̽��ϴ�. ����Ϸ��� �ƹ�Ű�� �����ʽÿ�.\n\n";
		_getch();
	}

	order.add(make_pair(tempInfo, tempPrice));
	tempInfo = "";
	tempPrice = 0;
}

bool printChoiceOrder() {
	tempId = 0;
	string choice;

	order.printOrderedMenuList();
	if (order.isEmpty()) {
		cout << '\n';
		return false;
	}

	do {
		cout << "���ݱ����� �ֹ� ������ �����Ϸ��� y��, �ٸ� �޴��� �߰��Ϸ��� n�� �Է��Ͻʽÿ� >> ";
		cin >> choice;
	} while ((choice != "y") && (choice != "n"));

	cout << '\n';

	return (choice == "y") ? true : false;
}

void printOrder() {
	int amount = order.getAmount();

	order.order();

	cout << amount << "�� ������ �Ϸ�Ǿ����ϴ�. ����Ϸ��� �ƹ�Ű�� �����ʽÿ�.";
	_getch();
	cout << "\n\n";
}