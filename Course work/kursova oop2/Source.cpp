#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <numeric>



using namespace std;

class CStudentEmploy {
private:
	string m_strName;
	string m_strFacNum;
	int m_iMinutes;
public:

	//1.1 default constructor
	CStudentEmploy() {
		m_strName = "Empty";
		m_strFacNum = "Empty";
		m_iMinutes = 0;
	}

	//1.2 explicit constructor
	CStudentEmploy(string m_strName, string m_strFacNum, int m_iMinutes) {
		this->m_strName = m_strName;
		this->m_strFacNum = m_strFacNum;
		this->m_iMinutes = m_iMinutes;
	}

	//1.3 copy constructor
	CStudentEmploy(const CStudentEmploy& obj) {
		m_strName = obj.m_strName;
		m_strFacNum = obj.m_strFacNum;
		m_iMinutes = obj.m_iMinutes;
	}

	//1.4 read minutes 
	int Get_Minutes() {
		return m_iMinutes;
	}

	//1.5 operator =
	CStudentEmploy operator =(CStudentEmploy& obj) {
		this->m_strName = obj.m_strName;
		this->m_strFacNum = obj.m_strFacNum;
		this->m_iMinutes = obj.m_iMinutes;
		return *this;
	}

	//1.6 operator <
	bool operator <(const CStudentEmploy& obj) const {
		return(m_iMinutes < obj.m_iMinutes);
	}

	//1.7 operator +
	CStudentEmploy operator +(CStudentEmploy& obj) {
		this->m_iMinutes += obj.m_iMinutes;
		return *this;
	}

	//1.8 operator <<
	friend ostream& operator << (ostream& toStream, const CStudentEmploy &obj)
	{
		toStream << "\nName: " << obj.m_strName << "\nFaculty number: " << obj.m_strFacNum << "\nMinutes:" << obj.m_iMinutes << endl;
		return toStream;
	}

	//1.9 operator >>
	friend istream& operator >> (istream& fromStream, CStudentEmploy* &obj)
	{
		obj = new CStudentEmploy();
		fromStream >> obj->m_strName >> obj->m_strFacNum >> obj->m_iMinutes;
		return fromStream;
	}
};

//
class StudentComparer {
public:
	bool operator() (CStudentEmploy *left, CStudentEmploy *right) {
		return *left < *right;
	}
};

class CAnalizeData {
private:
	vector<CStudentEmploy*>m_vData;
public:
	CAnalizeData(const string &strFileName) {
		ifstream ifile(strFileName);
		copy(istream_iterator<CStudentEmploy*>(ifile), istream_iterator<CStudentEmploy*>(), back_inserter(m_vData));
	}

	void Sort() {
		sort(m_vData.begin(), m_vData.end(), StudentComparer());
	}

	double calcMean() {
		double avg = 0;
		vector<CStudentEmploy*>::iterator it = m_vData.begin();
		for (it = m_vData.begin(); it != m_vData.end(); it++) {
			avg += (*it)->Get_Minutes();
		}
		return avg / m_vData.size();
	}

	vector<int>calcNums(int iR1, int iR2, int iR3, int iR4, int iR5, int iR6) {
		int m_ibr1 = 0, m_ibr2 = 0, m_ibr3 = 0, m_ibr4 = 0, m_ibr5 = 0;
		vector<CStudentEmploy*>::iterator it = m_vData.begin();
		for (it = m_vData.begin(); it != m_vData.end(); it++) {
			if ((*it)->Get_Minutes() > iR1 && (*it)->Get_Minutes() <= iR2) { m_ibr1++; }
			else if ((*it)->Get_Minutes() > iR2 && (*it)->Get_Minutes() <= iR3) { m_ibr2++; }
			else if ((*it)->Get_Minutes() > iR3 && (*it)->Get_Minutes() <= iR4) { m_ibr3++; }
			else if ((*it)->Get_Minutes() > iR4 && (*it)->Get_Minutes() <= iR5) { m_ibr4++; }
			else if ((*it)->Get_Minutes() > iR5 && (*it)->Get_Minutes() <= iR6) { m_ibr5++; }
		}
		vector<int> calc{ m_ibr1,m_ibr2,m_ibr3,m_ibr4,m_ibr5,iR1,iR2,iR3,iR4,iR5,iR6 };
		return calc;
	}

	vector < vector<CStudentEmploy*>>calcNums2(int iR1, int iR2, int iR3, int iR4, int iR5, int iR6) {
		vector<CStudentEmploy*>a, b, c, d, e;
		vector<CStudentEmploy*>::iterator it = m_vData.begin();
		for (int i = 0; i < m_vData.size(); i++) {
			CStudentEmploy* A = new CStudentEmploy();
			if (m_vData[i]->Get_Minutes() > iR1 && m_vData[i]->Get_Minutes() <= iR2) { a.push_back(m_vData[i]); }
			else if (m_vData[i]->Get_Minutes() > iR2 && m_vData[i]->Get_Minutes() <= iR3) { b.push_back(m_vData[i]); }
			else if (m_vData[i]->Get_Minutes() > iR3 && m_vData[i]->Get_Minutes() <= iR4) { c.push_back(m_vData[i]); }
			else if (m_vData[i]->Get_Minutes() > iR4 && m_vData[i]->Get_Minutes() <= iR5) { d.push_back(m_vData[i]); }
			else if (m_vData[i]->Get_Minutes() > iR5 && m_vData[i]->Get_Minutes() <= iR6) { e.push_back(m_vData[i]); }
		}
		vector<vector<CStudentEmploy*>>AA{ a,b,c,d,e };
		return AA;
	}

	friend ostream& operator << (ostream& toStream, CAnalizeData &obj)
	{
		for (int i = 0; i < obj.m_vData.size(); i++)
		{
			CStudentEmploy* emp = obj.m_vData[i];
			toStream << *emp << endl;
		}
		return toStream;
	}


};
int main() {
	try {
		CAnalizeData AB("Test.txt");
		cout << AB << endl;
		AB.Sort();
		cout << "Average minutes is:" << AB.calcMean() << endl;
		cout << AB << endl;


		vector<int>vect = AB.calcNums(20, 35, 50, 65, 80, 120);
		vector<int>::iterator it2 = vect.begin() + 5;
		for (vector<int>::iterator it = vect.begin(); it != vect.end() - 6; it++)
		{

			cout << "[" << *it << "]" << "[" << *it2 << "-";
			it2++;
			cout << *it2 << "]" << endl;

		}
		cout << endl;


		vector<vector<CStudentEmploy*>>AAA = AB.calcNums2(20, 35, 50, 65, 80, 120);
		for (int i = 0; i < AAA.size(); i++)
		{
			for (vector<CStudentEmploy*>::iterator it = AAA[i].begin(); it != AAA[i].end(); ++it) {
				cout << **it << endl;
			}
			cout << "__________________" << endl;
		}
	}


	catch (exception &e)
	{
		cout << e.what() << endl;
	}
	cout << endl << endl;
	system("pause");
	return 0;
}