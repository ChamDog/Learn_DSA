#include <string> 
#include <sstream> 
using namespace std; 
class CStu {
private:
	int _studentID;
	string _name; 
	float _age; 
	double _score;
public:
	CStu() :_studentID(-1), _name("Unknown"), _age(-1.0), _score(-1.0) {}
	CStu(int id, const string& name, float age, double score)  
	{
		_name = name; _studentID = id; _age = age; _score = score;
	}
	CStu(int id, const char* name, float age, double score)  
	{
		_name = name; _studentID = id; _age = age; _score = score;
	}
	// 拷贝构造
	CStu(const CStu& s) :_name(s._name) 
	{
		_studentID = s._studentID;_age = s._age; _score = s._score;
	}
	// 移动构造
	CStu(CStu&& s) 
	{
		*this = move(s); 
	}
   // 拷贝赋值
	const CStu& operator =(const CStu& rhs) 
	{
		if (this != &rhs) 
		{
			_studentID = rhs._studentID;_age = rhs._age; _score = rhs._score; _name = rhs._name;
		}
		return *this;
	}
	// 移动赋值
	CStu& operator=(CStu&& rhs) 
	{
		if (this != &rhs) 
		{
			_studentID = rhs._studentID;_age = rhs._age; _score = rhs._score; _name = rhs._name;
		}
		return *this;
	}
	// 重载小于
	bool operator<(const CStu& y) const
	{
		return this->_studentID < y._studentID;
	}
	//Get and set
	int id() const { return _studentID; }
	int& id() { return _studentID; }
	    
	string name() const { return _name; }
	string& name() { return _name; } 
	
	float age() const { return _age; }
	float& age() { return _age; }

	double score() const { return _score; }
	double& score() { return _score; }
	 
	//获取stu()
	string str() const {
		ostringstream ss;
		ss << _studentID << '-' << _name << '-' << _age << '-' << _score; 
		return ss.str();
	}

	~CStu() {}
};
ostream& operator<<(ostream& os, const CStu& stu) {
	os << stu.name() << '(' << stu.id() << ')';
	return os;
}

