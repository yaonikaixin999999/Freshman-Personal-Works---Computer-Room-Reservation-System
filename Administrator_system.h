#pragma once
#include"computer_reservation_system.h"
#include<iostream>
#define ADMINISTRATOR_FILE "adimistrator.txt"
#define STUDENT_FILE "student.txt"
#define TEACHER_FILE "teacher.txt"

using namespace std;

class Administrator:public userID {
public:
	Administrator();

	//����Ա�Ѿ���¼
	bool Administrator_log_in;

	//��ʼ��
	void administrator_start_process();

	//����Ա�˵�
	void Administrator_menu();

	//����Ա��¼����
	void administrator_login_screen();

	//����˺�
	void Add_username();

	//�鿴�˺�
	void View_username();

	//���û�������
	computer_reservation_system CRS;

	//�����˺�ϵͳ����
	userID UID;

	//�鿴����
	void View_computer_room();

	//���ԤԼ
	void clear_reservation();

	//����Ա��¼����
	void Administrator_system_process();

	~Administrator(){}
};
