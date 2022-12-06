#include "my_lib.h"
Node* Create_Node(BOOK b)
{
	Node* node = new Node;
	node->book = b;
	return node;
}
void Add_Tail(Library& lib, BOOK temp)
{
	Node* node = Create_Node(temp);
	if (lib.pHead == NULL)
		lib.pHead = lib.pTail = node;
	else
	{
		lib.pTail->pNext = node;
		lib.pTail = node;
	}
}
BOOK Pop_Head(Library& lib)
{
	Node* temp = lib.pHead;
	lib.pHead = lib.pHead->pNext;
	BOOK bhead = temp->book;
	delete temp;
	return bhead;
}
ostream& operator << (ostream& os, BOOK b)
{
	// Id, Title, Price, User_id, profileName, review / helpfulness, review / score, review / time, review / summary, review / text
	os << "Id: " << b.id << endl;
	os << "Title: " << b.title << endl;
	os << "Price: " << b.price << endl;
	os << "User_id: " << b.user_id << endl;
	os << "Profile_name: " << b.profile_name << endl;
	os << "Review/helpfulness: " << b.r_help << endl;
	os << "Review/score: " << b.r_score << endl;
	os << "Review/time: " << b.r_time << endl;
	os << "Review/summary: " << b.r_sum << endl;
	os << "Review/text: " << b.r_text;
	return os;
}
void Get_Book(string Input_File,  string& str, vector<BOOK>& lib)
{
	ifstream fi;
	BOOK b;
	fi.open(Input_File, ios::in);
	if (!fi.is_open())
	{
		cout << "Mo File Khong Thanh Cong" << endl;
		return;
	}
	getline(fi, str);
	while (!fi.eof())
	{
		string temp = "";
		getline(fi, str, ','); // read up to the first comma to save str in id
		b.id = str;
		getline(fi, str, ','); // to second comma get title
		b.title = str;
		getline(fi, str, ','); // to 3rd comma get price
		if (str == "")
			b.price = 0;
		else
			b.price = stof(str);
		getline(fi, str, ','); // to the 4th comma get user_id
		b.user_id = str;
		getline(fi, str, ','); // to the 5th comma get profileName
		b.profile_name = str;
		getline(fi, str, ','); // to the 6th comma to get review helpfulness
		b.r_help = str;
		getline(fi, str, ','); // to the 7th comma to get review score
		b.r_score = stof(str);
		getline(fi, str, ','); // to the 8th comma to get review time
		b.r_time = str;
		getline(fi, str, ','); // to the 9th comma to get the review summary
		b.r_sum = str;
		getline(fi, str, '\n');
		b.r_text = str;
		lib.push_back(b);
	}
	fi.close();	
}
void Export_Excel(string Output_File, vector <BOOK>& lib, string str)
{
	ofstream fo;
	fo.open(Output_File, ios::out);
	fo << str << endl; // cai nay la cai header ne
	for (int i = 0; i < lib.size(); ++i)
	{
		fo << lib[i] << endl;
	}
}
void Merge(vector <BOOK>& lib, int l, int m, int r)
{
	int first1 = l, last1 = m;
	int first2 = m + 1, last2 = r;
	int idx = first1;
	while (first1 < last1 && first2 < last2) {
		if (lib[first1].id < lib[first2].id)
		{
			lib[idx] = lib[first1];
			++idx; ++first1;
		}
		else
		{
			lib[idx] = lib[first2];
			++idx; ++first2;
		}
	}
	while (first1 < last1)
	{
		lib[idx] = lib[first1];
		++idx; ++first1;
	}
	while (first2 < last2)
	{
		lib[idx] = lib[first2];
		++idx; ++first2;
	}
}
void Merge_Sort(vector<BOOK> &lib, int l, int r)
{
	if (l >= r) return;
	int mid = (l + r) / 2;
	Merge_Sort(lib, l, mid);
	Merge_Sort(lib, mid + 1, r);
	Merge(lib, l, mid, r);

}