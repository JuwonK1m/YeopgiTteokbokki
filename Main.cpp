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

void initAllMenu(); // 메뉴들의 속성 초기화
int printMainScreen(); // 메인 화면 출력
bool isCorrectChoiceNum(const string& choice); // 선택(입력) 숫자가 순수 숫자로 입력되었는지 확인 
void printYeopgiMenu(); // 엽기메뉴 출력
void printTaste(); // 맛 출력
void printTopping(); // 토핑 출력
void printSideAndDrink(); // 사이드/음료 출력
void printSetMenu(); // 세트메뉴 출력
void printSetMenuDetailChoice(); // 선택한 세트메뉴에 대한 세부사항 선택
bool printChoiceOrder();  // 주문내역을 확인하고, 결제를 할것인지 결정
void printOrder(); // 결제

int main(void) {

	initAllMenu();

	// 프로그램 루프
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

	cout << "프로그램이 종료되었습니다.\n";

	return 0;
}

void initAllMenu() {
	// 엽기메뉴 속성값 초기화
	// 인자 순서: id, 이름, 가격, 맛 선택 가능 여부, 토핑 선택 가능 여부
	yeopgiMenu.resize(YEOPGIMENU_SIZE);
	yeopgiMenu[0].init(1, "엽기떡볶이", 14000, true, true);
	yeopgiMenu[1].init(2, "엽기오뎅", 14000, true, true);
	yeopgiMenu[2].init(3, "엽기반반", 14000, true, true);
	yeopgiMenu[3].init(4, "엽기닭볶음탕", 24000, true, false);
	yeopgiMenu[4].init(5, "2인 엽기떡볶이", 9000, true, true);
	yeopgiMenu[5].init(6, "참숯 뼈없는 닭발", 15000, false, false);
	yeopgiMenu[6].init(7, "국물닭발", 15000, false, false);
	yeopgiMenu[7].init(8, "참숯 통닭발", 14000, false, false);
	yeopgiMenu[8].init(9, "오돌뼈", 14000, false, false);
	yeopgiMenu[9].init(10, "참숯닭날개", 14000, false, false);

	// 사이드/음료 속성값 초기화
	// 인자 순서: id, 이름, 가격
	sideAndDrink.resize(SIDEANDDRINK_SIZE);
	sideAndDrink[0].init(1, "모듬튀김", 2000);
	sideAndDrink[1].init(2, "김말이", 2000);
	sideAndDrink[2].init(3, "야채튀김", 1000);
	sideAndDrink[3].init(4, "튀김만두", 2000);
	sideAndDrink[4].init(5, "엽도그", 2000);
	sideAndDrink[5].init(6, "순살치킨", 2000);
	sideAndDrink[6].init(7, "치즈스틱", 2000);
	sideAndDrink[7].init(8, "바삭치즈만두", 2000);
	sideAndDrink[8].init(9, "순대", 3000);
	sideAndDrink[9].init(10, "주먹김밥(인기메뉴)", 2000);
	sideAndDrink[10].init(11, "계란찜", 2000);
	sideAndDrink[11].init(12, "계란야채죽", 5000);
	sideAndDrink[12].init(13, "오뎅탕", 10000);
	sideAndDrink[13].init(14, "누룽지탕", 5000);
	sideAndDrink[14].init(15, "공기밥", 1000);
	sideAndDrink[15].init(16, "음료(유산균)", 1000);

	// 토핑 속성값 초기화
	// 인자 순서: id, 이름, 가격
	topping.resize(TOPPING_SIZE);
	topping[0].init(1, "치즈", 3000);
	topping[1].init(2, "햄", 1000);
	topping[2].init(3, "베이컨", 3000);
	topping[3].init(4, "떡추가", 1000);
	topping[4].init(5, "오뎅추가", 1000);
	topping[5].init(6, "퐁당치즈만두", 2000);
	topping[6].init(7, "계란", 1500);
	topping[7].init(8, "메추리알", 1000);
	topping[8].init(9, "중국당면", 2500);
	topping[9].init(10, "라면사리", 1000);
	topping[10].init(11, "우동사리", 2000);
	topping[11].init(12, "당면사리", 2000);
	topping[12].init(13, "토핑 선택 안함", 0);

	// 세트메뉴 초기화
	// 인자 순서: id, 이름, 설명, 가격
	setMenu.resize(SETMENU_SIZE);
	setMenu[0].init(1, "A SET", "엽떡 OR 엽오 OR 반반 중 택 1 + 모듬튀김 + 계란 2알 OR 메추리알 5알 중 택 1", 17000);
	setMenu[1].init(2, "B SET", "엽떡 OR 엽오 OR 반반 중 택 1 + 모듬튀김 + 계란 2알 OR 메추리알 5알 중 택 1 + 주먹김밥", 19000);
	setMenu[2].init(3, "C SET", "엽떡 OR 엽오 OR 반반 중 택 1 + 모듬튀김 + 계란 2알 OR 메추리알 5알 중 택 1 + 주먹김밥 + 당면", 21000);
	setMenu[3].init(4, "FAMILY SET", "엽떡 OR 엽오 OR 반반 중 택 1 + 참숯메뉴 중 택 1 + 주먹김밥", 28000);
	setMenu[4].init(5, "참숯 SET", "참숯메뉴 중 택 1 + 주먹김밥", 16000);

	// 맛 초기화
	// 인자 순서: id, 맛
	taste.resize(TASTE_SIZE);
	taste[0].init(1, "매운맛");
	taste[1].init(2, "오리지널맛");
	taste[2].init(3, "덜매운맛");
	taste[3].init(4, "엽떡초보맛");
	taste[4].init(5, "짜장맛");
	taste[5].init(6, "착한맛");
}

int printMainScreen() {
	string choice;

	do {
		cout << "<동대문 엽기떡볶이>" << '\n';
		cout << "1. 엽기메뉴" << '\n';
		cout << "2. 세트메뉴" << '\n';
		cout << "3. 사이드/음료" << '\n';
		cout << "4. 주문내역 결제" << '\n';
		cout << "5. 종료" << '\n';
		cout << "선택하시오 >> ";
		cin >> choice;

		cout << '\n';
	} while ((choice != "1") && (choice != "2") && (choice != "3") && (choice != "4")); // 유효한 번호인지 검사

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
		cout << "<엽기메뉴>\n";
		for (YeopgiMenu ym : yeopgiMenu)
			printf("%d. %s - %d원\n", ym.getId(), ym.getName().c_str(), ym.getPrice());

		cout << "선택하시오 >> ";
		cin >> choiceId;

		choiceId_ = atoi(choiceId.c_str());

		cout << '\n';
	} while ((!isCorrectChoiceNum(choiceId)) || (choiceId_ > YEOPGIMENU_SIZE) || (choiceId_ < 1)); // 유효한 id인지 검사

	tempInfo += yeopgiMenu[choiceId_ - 1].getName();
	tempId = choiceId_;
	tempPrice += yeopgiMenu[choiceId_ - 1].getPrice();

	cout << yeopgiMenu[choiceId_ - 1].getName() << "을(를) 선택하셨습니다. 계속하려면 아무키나 누르십시오.\n";
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

	cout << yeopgiMenu[tempId - 1].getName() << "의 맛을 선택하십시오.\n";
	do {
		for (Taste t : taste) {
			// 2인 엽기떡볶이면 엽떡초보맛/짜장맛이 없으므로 건너뜀
			if (((t.getTaste() == "엽떡초보맛") || (t.getTaste() == "짜장맛")) && (yeopgiMenu[tempId - 1].getName() == "2인 엽기떡볶이"))
				continue;

			printf("%d. %s\n", t.getId(), t.getTaste().c_str());
		}

		cout << "선택하시오 >> ";
		cin >> choiceId;

		choiceId_ = atoi(choiceId.c_str());

		cout << '\n';
	} while ((!isCorrectChoiceNum(choiceId)) || (choiceId_ > TASTE_SIZE) || (choiceId_ < 1)
		|| ((yeopgiMenu[tempId - 1].getName() == "2인 엽기떡볶이") && ((taste[choiceId_ - 1].getTaste() == "엽떡초보맛") || (taste[choiceId_ - 1].getTaste() == "짜장맛")))); // 유효한 id인지 검사

	tempInfo += (" + " + taste[choiceId_ - 1].getTaste());

	cout << taste[choiceId_ - 1].getTaste() << "을(를) 선택하셨습니다. 계속하려면 아무키나 누르십시오.\n";
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
	bool continueChoiceTopping = true; // 토핑을 계속해서 주문할 것인지에 대한 여부

	cout << yeopgiMenu[tempId - 1].getName() << "에 넣을 토핑을 선택하십시오.\n";
	while (continueChoiceTopping) {
		do {
			for (Topping t : topping)
				printf("%d. %s - %d원\n", t.getId(), t.getName().c_str(), t.getPrice());

			cout << "선택하시오 >> ";
			cin >> choiceId;

			choiceId_ = atoi(choiceId.c_str());

			cout << '\n';
		} while ((!isCorrectChoiceNum(choiceId)) || (choiceId_ > TOPPING_SIZE) || (choiceId_ < 1));

		if (topping[choiceId_ - 1].getName() != "토핑 선택 안함") {
			tempInfo += (" + " + topping[choiceId_ - 1].getName());
			tempPrice += topping[choiceId_ - 1].getPrice();
		}

		do {
			cout << "토핑을 더 주문하시겠습니까?(y 또는 n) >> ";
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
		cout << "엽기메뉴 또는 세트메뉴를 주문하셔야만 사이드/음료를 주문하실 수 있습니다.\n";
		return;
	}

	string choiceId;
	int choiceId_;
	string continueChoiceSideAndDrinkAnswer;
	bool continueChoiceSideAndDrink = true; // 사이드/음료를 계속해서 주문할 것인지에 대한 여부

	cout << "<사이드/음료>\n";
	while (continueChoiceSideAndDrink) {
		do {
			for (SideAndDrink sd : sideAndDrink)
				printf("%d. %s - %d원\n", sd.getId(), sd.getName().c_str(), sd.getPrice());

			cout << "선택하시오 >> ";
			cin >> choiceId;

			choiceId_ = atoi(choiceId.c_str());

			cout << '\n';
		} while ((!isCorrectChoiceNum(choiceId)) || (choiceId_ > SIDEANDDRINK_SIZE) || (choiceId_ < 1));

		order.add(make_pair(sideAndDrink[choiceId_ - 1].getName(), sideAndDrink[choiceId_ - 1].getPrice()));
		cout << sideAndDrink[choiceId_ - 1].getName() << "을(를) 선택하셨습니다.\n\n";

		do {
			cout << "사이드/음료를 더 주문하시겠습니까?(y 또는 n) >> ";
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
		cout << "<세트메뉴>\n";
		for (SetMenu sm : setMenu)
			printf("%d. %s (%s) - %d원\n", sm.getId(), sm.getName().c_str(), sm.getDesctiption().c_str(), sm.getPrice());

		cout << "선택하시오 >> ";
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
		cout << setMenu[tempId - 1].getName() << "의 세부사항을 선택하십시오.\n";

		do {
			for (int i = 0; i < 3; i++)
				printf("%d. %s\n", yeopgiMenu[i].getId(), yeopgiMenu[i].getName().c_str());

			cout << "선택하시오 >> ";
			cin >> choiceId;

			choiceId_ = atoi(choiceId.c_str());

			cout << '\n';
		} while ((!isCorrectChoiceNum(choiceId)) || (choiceId_ > 3) || (choiceId_ < 1));

		tempInfo += (" + " + yeopgiMenu[choiceId_ - 1].getName());
		tempInfo += " + 모듬튀김";

		cout << yeopgiMenu[choiceId_ - 1].getName() << "을(를) 선택하셨습니다. 계속하려면 아무키나 누르십시오.\n\n";
		_getch();

		do {
			for (int i = 6; i < 8; i++)
				printf("%d. %s\n", topping[i].getId(), topping[i].getName().c_str());

			cout << "선택하시오 >> ";
			cin >> choiceId;

			choiceId_ = atoi(choiceId.c_str());

			cout << '\n';
		} while ((!isCorrectChoiceNum(choiceId)) || (choiceId_ > 8) || (choiceId_ < 7));

		tempInfo += (" + " + topping[choiceId_ - 1].getName());

		cout << topping[choiceId_ - 1].getName() << "을(를) 선택하셨습니다. 계속하려면 아무키나 누르십시오.\n\n";

		if (setMenu[tempId - 1].getName() == "B SET")
			tempInfo += " + 주먹김밥";
		else if (setMenu[tempId - 1].getName() == "C SET")
			tempInfo += " + 주먹김밥 + 당면";
	}
	else if (setMenu[tempId - 1].getName() == "FAMILY SET") {
		cout << setMenu[tempId - 1].getName() << "의 세부사항을 선택하십시오.\n";

		do {
			for (int i = 0; i < 3; i++)
				printf("%d. %s\n", yeopgiMenu[i].getId(), yeopgiMenu[i].getName().c_str());

			cout << "선택하시오 >> ";
			cin >> choiceId;

			choiceId_ = atoi(choiceId.c_str());

			cout << '\n';
		} while ((!isCorrectChoiceNum(choiceId)) || (choiceId_ > 3) || (choiceId_ < 1));

		tempInfo += (" + " + yeopgiMenu[choiceId_ - 1].getName());
		cout << yeopgiMenu[choiceId_ - 1].getName() << "을(를) 선택하셨습니다. 계속하려면 아무키나 누르십시오.\n\n";

		do {
			printf("%d. %s\n", yeopgiMenu[5].getId(), yeopgiMenu[5].getName().c_str());
			printf("%d. %s\n", yeopgiMenu[7].getId(), yeopgiMenu[7].getName().c_str());
			printf("%d. %s\n", yeopgiMenu[9].getId(), yeopgiMenu[9].getName().c_str());

			cout << "선택하시오 >> ";
			cin >> choiceId;

			choiceId_ = atoi(choiceId.c_str());

			cout << '\n';
		} while ((!isCorrectChoiceNum(choiceId)) || ((choiceId_ != 6) && (choiceId_ != 8) && (choiceId_ != 10)));

		tempInfo += (" + " + yeopgiMenu[choiceId_ - 1].getName());
		tempInfo += " + 주먹김밥";

		cout << yeopgiMenu[choiceId_ - 1].getName() << "을(를) 선택하셨습니다. 계속하려면 아무키나 누르십시오.\n\n";
		_getch();
	}
	else {
		cout << setMenu[tempId - 1].getName() << "의 세부사항을 선택하십시오.\n";

		do {
			printf("%d. %s\n", yeopgiMenu[5].getId(), yeopgiMenu[5].getName().c_str());
			printf("%d. %s\n", yeopgiMenu[7].getId(), yeopgiMenu[7].getName().c_str());
			printf("%d. %s\n", yeopgiMenu[9].getId(), yeopgiMenu[9].getName().c_str());

			cout << "선택하시오 >> ";
			cin >> choiceId;

			choiceId_ = atoi(choiceId.c_str());

			cout << '\n';
		} while ((!isCorrectChoiceNum(choiceId)) || ((choiceId_ != 6) && (choiceId_ != 8) && (choiceId_ != 10)));

		tempInfo += (" + " + yeopgiMenu[choiceId_ - 1].getName());
		tempInfo += " + 주먹김밥";

		cout << yeopgiMenu[choiceId_ - 1].getName() << "을(를) 선택하셨습니다. 계속하려면 아무키나 누르십시오.\n\n";
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
		cout << "지금까지의 주문 내역을 결제하려면 y를, 다른 메뉴를 추가하려면 n을 입력하십시오 >> ";
		cin >> choice;
	} while ((choice != "y") && (choice != "n"));

	cout << '\n';

	return (choice == "y") ? true : false;
}

void printOrder() {
	int amount = order.getAmount();

	order.order();

	cout << amount << "원 결제가 완료되었습니다. 계속하려면 아무키나 누르십시오.";
	_getch();
	cout << "\n\n";
}