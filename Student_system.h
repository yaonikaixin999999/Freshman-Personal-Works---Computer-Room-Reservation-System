#pragma once
#include"computer_reservation_system.h"
#include<iostream>
#define STUDENT_FILE "student.txt"
using namespace std;

class Student:public userID{
public:
	Student();

	string m_Name;

	//ѧ���Ѿ���¼
	bool student_log_in;

	//��ʼ��
	void student_start_process();

	//��¼����
	void student_login_screen();

	//�����˺�ϵͳ����
	userID UID;

	//ѧ���˵�
	void Student_Menu();

	//����ԤԼ
	void Apply_reservation();

	//���û�������
	computer_reservation_system crs;

	//�鿴�ҵ�ԤԼ
	void View_my_reservation();

	//�鿴����ԤԼ
	void Sut_View_all_reservation();

	//ȡ��ԤԼ
	void Cancel_reservation();

	//ѧ����¼����
	void student_system_process();

	//��¼��ʱ���������
	int temp_computer_num[3] = {0,0,0};

	//��������
	~Student();
};
