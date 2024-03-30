#include<iostream>
using namespace std;
#include"computer_reservation_system.h"
#include"Student_system.h"
#include"Teacher_system.h"
#include"Administrator_system.h"

int main() {
	int temp_choice;
	computer_reservation_system crs;
	while (1) {
		crs.Main_Menu();
		cin >> temp_choice;
		if (temp_choice != 1 && temp_choice != 2 && temp_choice != 3 && temp_choice != 0) {
			cout << "输入错误，请重新输入" << endl;
			system("pause");
			system("cls");
		}
		else {
			if (temp_choice == 0) {
				cout << "欢迎下次使用" << endl;
				break;
			}
			else if (temp_choice == 1) {
				Student Stu;
				Stu.student_system_process();
			}
			else if (temp_choice == 2) {
				Teacher Tea;
				Tea.teacher_system_process();
			}
			else if (temp_choice == 3) {
				Administrator Adm;
				Adm.Administrator_system_process();
			}
		}
	}

	return 0;
}