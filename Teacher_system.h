#pragma once
#include"computer_reservation_system.h"
#include<iostream>
#define TEACHER_FILE "teacher.txt"
using namespace std;

class Teacher:public userID {
public:
	Teacher();

	string m_Name;

	//��ʦ�Ѿ���¼
	bool teacher_log_in;

	//��ʼ��
	void teacher_start_process();

	//��¼����
	void teacher_login_screen();

	//��ʦ�˵�
	void Teacher_Menu();

	//�����˺�ϵͳ����
	userID UID;

	//���û�������
	computer_reservation_system CRS;

	//�鿴����ԤԼ
	void Tea_View_all_reservation();

	//���ԤԼ
	void Audit_reservation();

	//��ʦ��¼����
	void teacher_system_process();

	~Teacher();
};
