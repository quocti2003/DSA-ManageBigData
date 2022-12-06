#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;
struct BOOK
{
	string id, title, user_id, profile_name, r_help, r_time, r_sum, r_text;
	float price, r_score;
};
struct Node
{
	BOOK book;
	Node* pNext = NULL;
};
struct Library
{
	Node* pHead = NULL;
	Node* pTail = NULL;
};
Node* Create_Node(BOOK);
void Add_Tail(Library&, BOOK);
BOOK Pop_Head(Library&);
ostream& operator << (ostream&, BOOK);
void Get_Book(string, string&, vector<BOOK>&);
void Export_Excel(string, string&, vector<BOOK>);
void Merge(vector<BOOK>& lib, int l, int m, int r);
void Merge_Sort(vector<BOOK>& lib, int l, int r);


