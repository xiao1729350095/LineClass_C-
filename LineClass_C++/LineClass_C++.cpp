// LineClass_C++.cpp : �������̨Ӧ�ó������ڵ㡣
//
/*******************************************************************************************/
/************************      ��������LineClass_C++           *****************************/
/*************     ����˵�������Ա���࣬�������������ջ�࣬����ʾ���ݵĶ�̬����    *******/
/**********    ����ʵ��˼·������ģ���Ĭ�ϲ���ʵ����Բ�ͬ�������ݵĶ�̬����  *************/
/**********                  ͨ������Ԥ���ı�����Ա�е��ⲿ�ӿ�ʵ�������������Ĳ���   ****/
/*******************************************************************************************/
#include "stdafx.h"
#include "iostream"
using namespace std;
#define MAXNUM 10
#define False  0
#define True 1

#define Version 1
/*����汾��˵����version��1.1*/
template<class T, class M = char> class LINE
{
private:                 //˽�г�Ա���ڱ�������
	T Data_r[MAXNUM];    //ʵ��
	M Data_i[MAXNUM];    //�鲿���鲿���Ͳ�����Ϊchar�ͣ�Ĭ���鲿����Ϊchar���Ա����ָ���
	int length;
public:                  //���г�Ա�����ⲿ����
/***************���캯�����ڳ�ʼ�����ݱ������char NULL=�� ����int NULL=0��***********/	
	LINE() {     
		int i;
		length = 0;
		for (i = 0; i < MAXNUM; i++) {
			Data_r[i] = NULL;
			Data_i[i] = NULL;
		}
	}
/***************************�����������ݵ����Ա���*****************************/
	void CREATE() {
		T temp_r;
		if (typeid(M) != typeid(char))           //������
		{
			M temp_i;
			cout << "���������ĸ���(������ʵ���������鲿):(/end:0 0)" << endl;
			cin >> temp_r >> temp_i;
			while ((temp_r != 0 || temp_i != 0)&&length<MAXNUM) {
				Data_r[length] = temp_r;
				Data_i[length++] = temp_i;
				if (length >= MAXNUM)
					break;
				cin >> temp_r >> temp_i;
			}
		}
		else if (typeid(T) == typeid(char))
		{
			cout << "�����������ַ�:(/end:#)" << endl;
			cin >> temp_r;
			while (temp_r != '#' && length<MAXNUM) {
				Data_r[length++] = temp_r;
				if (length >= MAXNUM)
					break;
				cin >> temp_r;
			}
		}
		else                                    //����������ʵ���ͷ���
		{
			cout << "��������������:(/end:0)" << endl;
			cin >> temp_r;
			while (temp_r != 0&&length<MAXNUM) {
				Data_r[length++] = temp_r;
				if (length >= MAXNUM)
					break;
				cin >> temp_r;
			}
		}
	}
/***************************�������ݵ����Ա�bitλ��*************************/
	int INSERT(int bit, T i, M j = NULL)
	{
		if (length >= MAXNUM)
			return False;
		if (bit < 1)
			bit = 1;
		else if (bit > length+1)
			bit = length+1;
		bit--;                     //ת�����±괦��
		for (int m = length - 1; m >= bit; m--)
		{
			Data_r[m + 1] = Data_r[m];
			Data_i[m + 1] = Data_i[m];
		}
			Data_r[bit] = i;
			Data_i[bit] = j;
			length++;
	}
/***************************ɾ�����Ա�bitλ�е�����*************************/
	int DELETE_L(int bit)
	{
		if (length >= MAXNUM)
			return False;
		if (bit < 1)
			bit = 1;
		else if (bit > length)
			bit = length;
		bit--;          //ת�����±괦��
		for (int m = bit; m < length-1; m++)
		{
			Data_r[m] = Data_r[m+1];
			Data_i[m] = Data_i[m+1];
		}
		Data_r[length-1] = NULL;
		Data_i[length-1] = NULL;
		length--;
	}

/*************************��ʾ���Ա�����*******************************/
	int SHOW() {
		int i;
		cout << "**************���Ա�***************" << endl;
		cout << "length=" << length << endl;
		if (length == 0)                   //�п�
		{
			cout << "���Ա�Ϊ��" << endl;
			return False;
		}
		cout << "���Ա����ݣ�" << endl;
		for (i = 0; i < length; i++)      
		{
			if (typeid(M) != typeid(char)) //��ʾ����   
				cout << Data_r[i] << "+i" << Data_i[i] << '\t';
			else                           //��ʾ������ʵ���ͷ���
				cout << Data_r[i] << '\t';
		}
		cout << endl;
		return True;
	}
protected:          //������Ա��������̳�ʹ��
/*******************�ⲿ�ӿ�����������ݣ�i��j�����±�Ϊbitλ*********************/
		int ADD(int bit, T i, M j) {         
			if (bit < 0 || bit >= MAXNUM) return False;
			else
			{
				Data_r[bit] = i;
				Data_i[bit] = j;
			}
			return True;
		}
/*******************�ⲿ�ӿ�����ɾ���±�Ϊbitλ������*********************/
		int DELETE(int bit) {
			if (bit < 0 || bit >= MAXNUM) return False;
			else
			{
				Data_r[bit] = NULL;
				Data_i[bit] = NULL;
			}
			return True;
		}
/*******************�ⲿ�ӿ�������ʾ�±�Ϊbitλ������*********************/
		int DISPLAY(int bit) {
			if (bit < 0 || bit >= MAXNUM)
				return False;
			if (typeid(M) != typeid(char))
				cout << Data_r[bit] << "+i" << Data_i[bit] << '\t';
			else
				cout << Data_r[bit] << '\t';
			return True;
		}

};
template<class T, class M = char>class QUEUE :private LINE<T, M> {
private:
	int  front, rear;
public:
	QUEUE() {
		front = 0;
		rear = 0;
	}
/***************************ѭ��������ʾ����******************************/
	int SHOW() {
		int x = front, y = rear;
		cout << "**************����****************" << endl;
		cout << "front=" << x << ",rear=" << y << endl;
		if (x == y)                   //�п�
		{
			cout << "���б�Ϊ��" << endl;
			return False;
		}
		cout << "���б����ݣ�" << endl;
		x = (x + 1) % MAXNUM;         //��һ��Ԫ��λ��
		while (x != y)
		{
			DISPLAY(x++);
			x = x%MAXNUM;
		}
		DISPLAY(y);
		cout << endl;
		return True;
	}
/************************ѭ����Ӻ���**********************************/
	int PUSH(T i, M j = NULL)
	{
		if ((rear + 1) % MAXNUM == front)   //�ж϶����Ƿ�����
			return False;
		rear = (rear + 1) % MAXNUM;
		ADD(rear, i, j);
		return True;
	}
/**************************ѭ�����Ӻ���****************************/
	int POP()
	{
		if (front == rear)                //�ж϶����Ƿ�Ϊ��
			return False;
		front = (front + 1) % MAXNUM;
		DELETE(front);
		return True;
	}
};
template<class T, class M = char>class STACK :private LINE<T, M> {
private:
	int top;
public:
	STACK() {
		top = -1;
	}
	/***************************��ջ����***************************/
	int PUSH(T i, M j = NULL) {
		if (top >= MAXNUM - 1)
			return False;
		ADD(++top, i, j);
		return True;
	}
	/***************************��ջ����***************************/
	int POP() {
		if (top < 0)
			return False;
		DELETE(top--);
		return True;
	}
	/***************************ջ��ʾ����***************************/
	int SHOW() {
		cout << "**************ջ��***************" << endl;
		cout << "top=" << top << endl;
		if (top < 0)
		{
			cout << "ջ��Ϊ��" << endl;
			return False;
		}
		cout << "ջ�����ݣ�" << endl;
		for (int i = 0; i <= top; i++)
			DISPLAY(i);
		cout << endl;
		return True;
	}
};


int main() {
	LINE<float,int> a;
	a.CREATE();
	a.SHOW();
	a.INSERT(2,1.1,2);
	a.SHOW();
	a.DELETE_L(2);
	a.SHOW();
	QUEUE<float,int> b;
	b.PUSH(1.1,1);
	b.SHOW();
	b.PUSH(2,1.1);
	b.SHOW();
	b.POP();
	b.SHOW();
	STACK<float, int> c;
	c.SHOW();
	c.PUSH(1.1);
	c.SHOW();
	c.PUSH(2,1);
	c.SHOW();
	c.POP();
	c.SHOW();
	LINE<char> d;
	d.CREATE();
	d.SHOW();
	d.INSERT(2,'Z');
	d.SHOW();
	d.DELETE_L(2);
	d.SHOW();
	return 0;
}