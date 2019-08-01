// LineClass_C++.cpp : 定义控制台应用程序的入口点。
//
/*******************************************************************************************/
/************************      程序名：LineClass_C++           *****************************/
/*************     程序说明：线性表基类，衍生出队列类和栈类，并显示数据的多态处理    *******/
/**********    基本实现思路：利用模板和默认参数实现类对不同类型数据的多态处理  *************/
/**********                  通过基类预留的保护成员中的外部接口实现派生类对数组的操作   ****/
/*******************************************************************************************/
#include "stdafx.h"
#include "iostream"
using namespace std;
#define MAXNUM 10
#define False  0
#define True 1

#define Version 1
/*代码版本号说明：version：1.1*/
template<class T, class M = char> class LINE
{
private:                 //私有成员用于保存数据
	T Data_r[MAXNUM];    //实部
	M Data_i[MAXNUM];    //虚部，虚部类型不可能为char型，默认虚部类型为char型以便区分复数
	int length;
public:                  //公有成员用于外部引用
/***************构造函数用于初始化数据避免出错（char NULL=‘ ’；int NULL=0）***********/	
	LINE() {     
		int i;
		length = 0;
		for (i = 0; i < MAXNUM; i++) {
			Data_r[i] = NULL;
			Data_i[i] = NULL;
		}
	}
/***************************连续输入数据到线性表中*****************************/
	void CREATE() {
		T temp_r;
		if (typeid(M) != typeid(char))           //处理复数
		{
			M temp_i;
			cout << "请输入存入的复数(先输入实部再输入虚部):(/end:0 0)" << endl;
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
			cout << "请输入存入的字符:(/end:#)" << endl;
			cin >> temp_r;
			while (temp_r != '#' && length<MAXNUM) {
				Data_r[length++] = temp_r;
				if (length >= MAXNUM)
					break;
				cin >> temp_r;
			}
		}
		else                                    //处理整数，实数和符号
		{
			cout << "请输入存入的数据:(/end:0)" << endl;
			cin >> temp_r;
			while (temp_r != 0&&length<MAXNUM) {
				Data_r[length++] = temp_r;
				if (length >= MAXNUM)
					break;
				cin >> temp_r;
			}
		}
	}
/***************************插入数据到线性表bit位中*************************/
	int INSERT(int bit, T i, M j = NULL)
	{
		if (length >= MAXNUM)
			return False;
		if (bit < 1)
			bit = 1;
		else if (bit > length+1)
			bit = length+1;
		bit--;                     //转化成下标处理
		for (int m = length - 1; m >= bit; m--)
		{
			Data_r[m + 1] = Data_r[m];
			Data_i[m + 1] = Data_i[m];
		}
			Data_r[bit] = i;
			Data_i[bit] = j;
			length++;
	}
/***************************删除线性表bit位中的数据*************************/
	int DELETE_L(int bit)
	{
		if (length >= MAXNUM)
			return False;
		if (bit < 1)
			bit = 1;
		else if (bit > length)
			bit = length;
		bit--;          //转化成下标处理
		for (int m = bit; m < length-1; m++)
		{
			Data_r[m] = Data_r[m+1];
			Data_i[m] = Data_i[m+1];
		}
		Data_r[length-1] = NULL;
		Data_i[length-1] = NULL;
		length--;
	}

/*************************显示线性表内容*******************************/
	int SHOW() {
		int i;
		cout << "**************线性表***************" << endl;
		cout << "length=" << length << endl;
		if (length == 0)                   //判空
		{
			cout << "线性表为空" << endl;
			return False;
		}
		cout << "线性表数据：" << endl;
		for (i = 0; i < length; i++)      
		{
			if (typeid(M) != typeid(char)) //显示复数   
				cout << Data_r[i] << "+i" << Data_i[i] << '\t';
			else                           //显示整数，实数和符号
				cout << Data_r[i] << '\t';
		}
		cout << endl;
		return True;
	}
protected:          //保护成员用于子类继承使用
/*******************外部接口用于添加数据（i，j）到下标为bit位*********************/
		int ADD(int bit, T i, M j) {         
			if (bit < 0 || bit >= MAXNUM) return False;
			else
			{
				Data_r[bit] = i;
				Data_i[bit] = j;
			}
			return True;
		}
/*******************外部接口用于删除下标为bit位的数据*********************/
		int DELETE(int bit) {
			if (bit < 0 || bit >= MAXNUM) return False;
			else
			{
				Data_r[bit] = NULL;
				Data_i[bit] = NULL;
			}
			return True;
		}
/*******************外部接口用于显示下标为bit位的数据*********************/
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
/***************************循环队列显示函数******************************/
	int SHOW() {
		int x = front, y = rear;
		cout << "**************队列****************" << endl;
		cout << "front=" << x << ",rear=" << y << endl;
		if (x == y)                   //判空
		{
			cout << "队列表为空" << endl;
			return False;
		}
		cout << "队列表数据：" << endl;
		x = (x + 1) % MAXNUM;         //第一个元素位置
		while (x != y)
		{
			DISPLAY(x++);
			x = x%MAXNUM;
		}
		DISPLAY(y);
		cout << endl;
		return True;
	}
/************************循环入队函数**********************************/
	int PUSH(T i, M j = NULL)
	{
		if ((rear + 1) % MAXNUM == front)   //判断队列是否已满
			return False;
		rear = (rear + 1) % MAXNUM;
		ADD(rear, i, j);
		return True;
	}
/**************************循环出队函数****************************/
	int POP()
	{
		if (front == rear)                //判断队列是否为空
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
	/***************************入栈函数***************************/
	int PUSH(T i, M j = NULL) {
		if (top >= MAXNUM - 1)
			return False;
		ADD(++top, i, j);
		return True;
	}
	/***************************出栈函数***************************/
	int POP() {
		if (top < 0)
			return False;
		DELETE(top--);
		return True;
	}
	/***************************栈显示函数***************************/
	int SHOW() {
		cout << "**************栈堆***************" << endl;
		cout << "top=" << top << endl;
		if (top < 0)
		{
			cout << "栈堆为空" << endl;
			return False;
		}
		cout << "栈堆数据：" << endl;
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