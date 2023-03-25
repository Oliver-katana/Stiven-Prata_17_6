#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <set>
#include <list>
#include <iomanip>

using namespace std;


enum Workers
{
	EMPLOY = 1,
	MANAG,
	FIN,
	HFIN
};


class A_emp
{
	string fname_, lname_, job_;
public:
	A_emp(const string& fn = "", const string& ln = "", const string& j = "")
	{
		fname_ = fn; lname_ = ln; job_ = j;
	}
	A_emp(const A_emp& a)
	{
		this->fname_ = a.fname_; this->lname_ = a.lname_; this->job_ = a.job_;
	}
	virtual void ShowAll()const
	{
		cout << "First name: " << this->fname_
			<< " last name: " << this->lname_
			<< " job: " << this->job_;
	}
	virtual void SetAll()
	{
		cout << "Enter first name: ";
		cin >> this->fname_;
		cout << "Enter last name: ";
		cin >> this->lname_;
		cout << "Enter job: ";
		cin >> this->job_;
	}
	virtual void WriteAll(ofstream& fout)
	{
		fout << this->fname_ << "\n" << this->lname_ << "\n" << this->job_ << "\n";
	}
	virtual void ReadAll(ifstream& fin)
	{
		fin >> this->fname_ >> this->lname_ >> this->job_;
	}
	friend ostream& operator<<(ostream& os, const A_emp& e)
	{
		os << "First name: " << e.fname_ << " last name: " << e.lname_ << endl;
		return os;
	}
	virtual ~A_emp() = 0
	{
	}
};
class Emploee :public A_emp
{
public:
	Emploee()
	{}
	Emploee(const string& fn, const string& ln, const string& j) :A_emp(fn, ln, j)
	{}
	virtual void ShowAll()const
	{
		cout << "\n\nEmployee:" << endl;
		A_emp::ShowAll();
	}
	virtual void SetAll()
	{
		A_emp::SetAll();
	}
	virtual void WriteAll(ofstream& fout)
	{
		fout << EMPLOY << endl;
		A_emp::WriteAll(fout);
	}
	virtual void ReadAll(ifstream& fin)
	{
		A_emp::ReadAll(fin);
	}
	~Emploee()
	{
	}
};
class Manager :virtual public A_emp
{
	int inchargeof;
protected:
	int InChargeOf()const
	{
		return inchargeof;
	}
	int& InChargeOf()
	{
		return inchargeof;
	}
public:
	Manager()
	{}
	Manager(const string& fn, const string& ln, const string& j, int ico = 0) :A_emp(fn, ln, j)
	{
		inchargeof = ico;
	}
	Manager(const A_emp& e, int ico) :A_emp(e)
	{
		inchargeof = ico;
	}
	Manager(const Manager& m) :A_emp(m)
	{
		this->inchargeof = m.inchargeof;
	}
	virtual void ShowAll()const
	{
		cout << "\n\nManager:" << endl;
		A_emp::ShowAll();
		cout << " Inchargeof: " << this->inchargeof;
	}
	virtual void SetAll()
	{
		A_emp::SetAll();
		cout << "Enter inchargeof: ";
		cin >> this->inchargeof;
	}
	virtual void WriteAll(ofstream& fout)
	{
		fout << MANAG << endl;
		A_emp::WriteAll(fout);
		fout << inchargeof << endl;
	}
	virtual void ReadAll(ifstream& fin)
	{
		A_emp::ReadAll(fin);
		fin >> this->inchargeof;
	}
	~Manager()
	{
	}
};
class Fink :virtual public A_emp
{
	string reportsto;
protected:
	const string ReportsTo()const
	{
		return reportsto;
	}
	string SetReportsTo()
	{
		cout << "Enter reportsTo: ";
		cin >> this->reportsto;
		return this->reportsto;
	}
	void ReadReportsTo(ifstream& fin)
	{
		fin >> this->reportsto;
	}
public:
	Fink()
	{}
	Fink(const string& fn, const string& ln, const string& j, const string& rpo) :A_emp(fn, ln, j)
	{
		this->reportsto = rpo;
	}
	Fink(const A_emp& e, const string& rpo) :A_emp(e)
	{
		this->reportsto = rpo;
	}
	Fink(const Fink& f) :A_emp(f)
	{
		this->reportsto = f.reportsto;
	}
	virtual void ShowAll()const
	{
		cout << "\n\nFink:" << endl;
		A_emp::ShowAll();
		cout << " ReportsTo: " << this->reportsto << endl;
	}
	virtual void SetAll()
	{
		A_emp::SetAll();
		SetReportsTo();
	}
	virtual void WriteAll(ofstream& fout)
	{
		fout << FIN << endl;
		A_emp::WriteAll(fout);
		fout << reportsto << endl;
	}
	virtual void ReadAll(ifstream& fin)
	{
		A_emp::ReadAll(fin);
		fin >> this->reportsto;
	}
	~Fink()
	{
	}
};
class Highfink :public Manager, public Fink
{
public:
	Highfink()
	{}
	Highfink(const string& fn, const string& ln, const string& j, int ico, const string& rpo)
		:A_emp(fn, ln, j), Manager(fn, ln, j, ico), Fink(fn, ln, j, rpo)
	{}
	Highfink(const A_emp& e, int ico, const string& rpo)
		:A_emp(e), Manager(e, ico), Fink(e, rpo)
	{}
	Highfink(const Fink& f, int ico) :A_emp(f), Manager(f, ico), Fink(f)
	{}
	Highfink(const Manager& m, const string& rpo) :A_emp(m), Manager(m), Fink(m, rpo)
	{}
	Highfink(const Highfink& h) :A_emp(h), Manager(h), Fink(h)
	{}
	virtual void ShowAll()const
	{
		cout << "\n\nHighfink:" << endl;
		A_emp::ShowAll();
		cout << " InchargeOf: " << Manager::InChargeOf();
		cout << " ReportsTo: " << Fink::ReportsTo();
	}
	virtual void SetAll()
	{
		Manager::SetAll();
		Fink::SetReportsTo();
	}
	virtual void WriteAll(ofstream& fout)
	{
		fout << HFIN << endl;
		A_emp::WriteAll(fout);
		fout << Manager::InChargeOf() << endl;
		fout << Fink::ReportsTo() << endl;
	}
	virtual void ReadAll(ifstream& fin)
	{
		Manager::ReadAll(fin);
		Fink::ReadReportsTo(fin);
	}
	~Highfink()
	{
	}
};

int main()
{
	const int size = 10;
	A_emp* tri[size];
	ifstream fin("emp.txt");
	int i = 0;

	if (!fin.is_open())
	{
		cerr << "File not exist!" << endl;
	}
	else
	{
		while (!fin.eof())
		{
			int emp = 0;
			fin >> emp;
			fin.ignore();
			switch (emp)
			{
			case EMPLOY:
			{
				tri[i] = new (Emploee);
				tri[i]->ReadAll(fin);
				tri[i]->ShowAll();
				i++;
				break;
			}
			case MANAG:
			{
				tri[i] = new (Manager);
				tri[i]->ReadAll(fin);
				tri[i]->ShowAll();
				i++;
				break;
			}
			case FIN:
			{
				tri[i] = new (Fink);
				tri[i]->ReadAll(fin);
				tri[i]->ShowAll();
				i++;
				break;
			}
			case HFIN:
			{
				tri[i] = new (Highfink);
				tri[i]->ReadAll(fin);
				tri[i]->ShowAll();
				i++;
				break;
			}
			default:
				break;
			}
		}
	}
	fin.close();

	ofstream fout("emp.txt", ios_base::app);
	if (!fout.is_open())
	{
		cerr << "Couldn't open the file for write!" << endl;
		exit(EXIT_FAILURE);
	}
	int choise;
	cout << "\nChoose your worker(1-employee, 2-manager, 3-fink, 4-highfink)(q-quit): ";
	while (cin >> choise)
	{
		cin.ignore();
		switch (choise)
		{
		case EMPLOY:
		{
			tri[i] = new (Emploee);
			tri[i]->SetAll();
			tri[i]->WriteAll(fout);
			tri[i]->ShowAll();
			i++;
			break;
		}
		case MANAG:
		{
			tri[i] = new (Manager);
			tri[i]->SetAll();
			tri[i]->WriteAll(fout);
			tri[i]->ShowAll();
			i++;
			break;
		}
		case FIN:
		{
			tri[i] = new (Fink);
			tri[i]->SetAll();
			tri[i]->WriteAll(fout);
			tri[i]->ShowAll();
			i++;
			break;
		}
		case HFIN:
		{
			tri[i] = new (Highfink);
			tri[i]->SetAll();
			tri[i]->WriteAll(fout);
			tri[i]->ShowAll();
			i++;
			break;
		}
		}
		cout << "\nChoose your worker(1-employee, 2-manager, 3-fink, 4-highfink)(q-quit): ";
	}
	fout.close();
	for (size_t k = 0; k < i; k++)
	{
		delete tri[k];
	}
	return 0;
}




