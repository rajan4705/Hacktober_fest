// Anurag Deshmane
// 2001CS08

#include <bits/stdc++.h>
using namespace std;

// SYMBOLS AND LABELS explanation after pass 1
struct Mnemonic
{
	string opcode; // type = 0 means no operand
	int type;	   // type = 1 means argument is given
	// type = 2 means offset to be given
};
struct symb
{
	int address; // type = 0 means varicable or data is declared here
	int type;	 // type = 1 means Label name or block name
};

struct threepc
{
	string label_name;
	string ins;
	string op;
	threepc(string &a, string &b, string &c)
	{
		label_name = a;
		ins = b;
		op = c;
	}
	friend ostream &operator<<(ostream &os, const threepc &H)
	{
		os << H.label_name << " " << H.ins << " " << H.op << " ";
		return os;
	}
};

vector<string> MachineCode;			// final machine code generated ;
vector<string> ListingFile;			// final Listing file in strings ;
vector<pair<int, threepc>> p1Inst;	// cleaned Instructions for pass1
vector<pair<int, threepc>> Inst;	// Processed Instructions for pass2
map<string, Mnemonic> Optab;		// Opcode Table
map<string, symb> declared;			// Declared Labels
map<string, symb> used;				// Used Labels
vector<pair<int, string>> Warning;	// All the warnings
vector<pair<int, string>> Errors;	// All The errors ;
int pc = 0;							// Program counter
set<string> datadeclared;			// labels declared with data
set<string> setdeclared;			// labels declared with set instruction
vector<pair<int, threepc>> dataseg; // Data Segment
bool isHaltPresent = false;

// Parsing functions
// Removing Comments and unnecessary space from beginning from a line
string ProcessRawInput(string s)
{
	string ans;
	int i = 0;
	while (i < s.size() && s[i] == ' ')
		i++;
	for (; i < s.size(); i++)
	{
		char c = s[i];
		if (c == ';')
			break;
		if (c >= 'A' && c <= 'Z')
			c = tolower(c);
		ans.push_back(c);
	}
	return ans;
}
bool CheckifNum(char x)
{
	return (x >= '0' && x <= '9');
}
bool isOctal(string s)
{
	if (s.size() < 2)
		return false;
	bool ok = true;
	ok &= (s[0] == '0');
	for (int i = 1; i < s.size(); i++)
	{
		ok &= (s[i] >= '0' && s[i] <= '7');
	}
	return ok;
}
bool isHexadecimal(string s)
{
	bool ok = true;
	if (s.size() < 3)
		return false;
	ok &= (s[0] == '0');
	ok &= (s[1] == 'x');
	for (int i = 2; i < s.size(); i++)
	{
		bool check = (s[i] >= '0' && s[i] <= '9');
		check |= (s[i] >= 'a' && s[i] <= 'f');
		ok &= check;
	}
	return ok;
}
int Octal2Dec(string s)
{
	int ans = 0, x = 1;
	for (int i = s.size() - 1; i > 0; i--)
	{
		ans += (s[i] - '0') * x;
		x *= 8;
	}
	return ans;
}
int Hex2Dec(string s)
{
	int ans = 0, x = 1;
	for (int i = s.size() - 1; i > 1; i--)
	{
		if (CheckifNum(s[i]))
		{
			ans += (s[i] - '0') * x;
		}
		else
		{
			ans += ((s[i] - 'a') + 10) * x;
		}
		x *= 16;
	}
	return ans;
}
bool isValidName(string name)
{
	if (name.empty())
		return false;
	char x = name[0];
	return ((x >= 'A' && x <= 'Z') || (x >= 'a' && x <= 'z')); //check if char
	bool ans = true;
	for (int i = 0; i < name.size(); i++)
	{
		ans &= ( ((name[i] >= 'A' && name[i] <= 'Z') || (name[i] >= 'a' && name[i] <= 'z')) || CheckifNum(name[i]) || name[i] == '_');
	}
	return ans;
}

// Split the single line into 3 components label - ins - operand
void Split(string &label_name, string &ins, string &op, string &Line, int line_num)
{
	int i = 0;
	bool label = false;
	for (; i < Line.size(); i++)
	{
		if (Line[i] == ':')
		{
			label = true;
			for (int j = 0; j < i; j++)
			{
				label_name.push_back(Line[j]);
			}
			i++;
			break;
		}
	}
	if (!label)
		i = 0;
	while (i < Line.size() && (Line[i] == ' ' || Line[i] == '\t'))
		i++;
	while (i < Line.size() && !(Line[i] == ' ' || Line[i] == '\t'))
	{
		ins.push_back(Line[i]);
		i++;
	}
	while (i < Line.size() && (Line[i] == ' ' || Line[i] == '\t'))
		i++;
	while (i < Line.size() && !(Line[i] == ' ' || Line[i] == '\t'))
	{
		op.push_back(Line[i]);
		i++;
	}
	while (i < Line.size() && (Line[i] == ' ' || Line[i] == '\t'))
		i++;
	if (i < Line.size() && !(Line[i] == ' ' || Line[i] == '\t'))
	{
		string t = "Extra operand on end of line ";
		Errors.push_back({line_num, t});
	}
}

string Process_Operand(string s, int *err, int line_num)
{
	if (isValidName(s))
	{
		used[s] = {line_num, 5};
		return s;
	}
	int sign = 1;
	if (s[0] == '-')
		sign = -1;
	if (s[0] == '+' || s[0] == '-')
		s = s.substr(1);
	if (isOctal(s))
		return to_string(sign * Octal2Dec(s));
	if (isHexadecimal(s))
		return to_string(sign * Hex2Dec(s));
	bool ok = true;
	for (int i = 0; i < s.size(); i++)
	{
		ok &= CheckifNum(s[i]);
	}
	if (ok)
		return to_string(sign * stoi(s));
	*err = 1;
	return s;
}

// Fill declared by data and declared by set labels
void Declaredbywho()
{
	for (auto &Line : p1Inst)
	{
		if (Line.second.ins == "set")
		{
			setdeclared.insert(Line.second.label_name);
		}
	}
	for (auto &Line : dataseg)
	{
		datadeclared.insert(Line.second.label_name);
	}
	vector<pair<int, threepc>> temper;
	for (auto Line : p1Inst)
	{
		bool flag = false;
		if (Line.second.ins == "set")
		{
			if (datadeclared.count(Line.second.label_name) == 0)
			{
				datadeclared.insert(Line.second.label_name);
				Line.second.ins = "data";
				dataseg.push_back(Line);
				flag = true;
			}
		}
		if (!flag)
		{
			temper.push_back(Line);
		}
	}
	p1Inst.clear();
	for (auto Line : temper)
	{
		p1Inst.push_back(Line);
	}
	for (auto Line : dataseg)
	{
		p1Inst.push_back(Line);
	}
	temper.clear();
	dataseg.clear();
}

// Function to Implement SET Instruction
bool SETinstruction(string &label_name, string &val, int lnum, int toadd)
{
	int A = 0;
	if (label_name.empty())
	{
		string t = "Missing Label name for set Instruction";
		Errors.push_back({lnum, t});
		return false;
	}
	if (val.empty())
	{
		string t = "Missing operand";
		Errors.push_back({lnum, t});
		return false;
	}
	string nop = Process_Operand(val, &A, lnum);
	if (((val[0] >= 'A' && val[0] <= 'Z') || (val[0] >= 'a' && val[0] <= 'z')) || A == 1)
	{
		string t = "Not a Number for SET Instruction";
		Errors.push_back({lnum, t});
		return false;
	}
	string ins;
	if (datadeclared.count(label_name) == 0 && declared.count(label_name) == 0)
	{
		return true;
	}
	else
	{
		string op;
		string label;
		ins = "adj";
		op = "2"; // increase the stack size
		nop = Process_Operand(op, &A, lnum);
		Inst.push_back({pc, threepc(label, ins, nop)});
		pc++;

		ins = "stl";
		op = "-1"; // push A
		nop = Process_Operand(op, &A, lnum);
		Inst.push_back({pc, threepc(label, ins, nop)});
		pc++;

		ins = "stl";
		op = "0"; // push B
		nop = Process_Operand(op, &A, lnum);
		Inst.push_back({pc, threepc(label, ins, nop)});
		pc++;

		ins = "ldc";
		op = val; // load the value to set
		nop = Process_Operand(op, &A, lnum);
		Inst.push_back({pc, threepc(label, ins, nop)});
		pc++;

		ins = "ldc";
		op = label_name; // load location of var
		nop = Process_Operand(op, &A, lnum);
		Inst.push_back({pc, threepc(label, ins, nop)});
		pc++;

		ins = "adc";
		op = to_string(toadd);
		nop = Process_Operand(op, &A, lnum);
		Inst.push_back({pc, threepc(label, ins, nop)});
		pc++; // for setting value in array

		ins = "stnl";
		op = "0"; // store value to set
		nop = Process_Operand(op, &A, lnum);
		Inst.push_back({pc, threepc(label, ins, nop)});
		pc++;

		ins = "ldl";
		op = "0"; // load back B
		nop = Process_Operand(op, &A, lnum);
		Inst.push_back({pc, threepc(label, ins, nop)});
		pc++;

		ins = "ldl";
		op = "-1"; // load back A
		nop = Process_Operand(op, &A, lnum);
		Inst.push_back({pc, threepc(label, ins, nop)});
		pc++;

		ins = "adj";
		op = "-2"; // decrease the stack size
		nop = Process_Operand(op, &A, lnum);
		Inst.push_back({pc, threepc(label, ins, nop)});
		pc++;
	}
	return false;
}

// Clean the Lines of the code ;
string InputName = "input.asm";
void clean()
{
	ifstream infile;
	infile.open(InputName);
	if (infile.fail())
	{
		cout << "Error in Opening Input file";
		exit(0);
	}
	string s;
	int lnum = 0;
	while (getline(infile, s))
	{
		string Line = ProcessRawInput(s);
		lnum++;
		if (Line.empty())
			continue;
		string ins, op, label_name;
		Split(label_name, ins, op, Line, lnum);
		if (!ins.empty() && ins == "data")
		{
			if (p1Inst.size() > 0)
			{
				auto temp = p1Inst.back();
				if (label_name.empty() && temp.second.ins.empty())
				{
					dataseg.push_back(temp);
					p1Inst.pop_back();
				}
			}
			dataseg.push_back({lnum, threepc(label_name, ins, op)});
		}
		else
		{
			p1Inst.push_back({lnum, threepc(label_name, ins, op)});
		}
	}
}
// PASS 1
void pass1()
{
	clean();
	Declaredbywho();
	int cnt = 0;
	string prev;
	for (auto &Line : p1Inst)
	{
		int lnum;
		string ins, op, label_name;
		lnum = Line.first;
		label_name = Line.second.label_name;
		ins = Line.second.ins;
		op = Line.second.op;

		bool wanttodeclare = false;
		if (!label_name.empty())
		{
			bool checker = isValidName(label_name);
			if (!checker)
			{
				string t = "Bogus Label Name ";
				Errors.push_back({lnum, t});
			}
			else
			{
				// declare the valid Label .
				wanttodeclare = true;
				prev = label_name;
				cnt = 0;
			}
		}
		else
			cnt++;
		int use = 0;
		int minus = 1, toincrease = 0;
		bool needsoperand = false;
		bool flag = false;
		if (!ins.empty())
		{
			bool checker = (Optab.count(ins) > 0);
			if (!checker)
			{
				string t = "Bogus Mnemonic";
				Errors.push_back({lnum, t});
			}
			else
			{
				needsoperand |= (Optab[ins].type > 0);
				if (ins == "set")
					flag = SETinstruction(prev, op, lnum, cnt);
				if (flag)
					ins = "data";
				toincrease++;
				if (wanttodeclare && ins == "data")
					use = 1;
				/*special care for data  and set instructions */
			}
		}
		if (!flag && (ins == "set"))
		{
			continue;
		}
		if (wanttodeclare)
		{
			if (declared.count(label_name) > 0)
			{
				string t = "Duplicate label definition of \"" + label_name + "\"";
				Errors.push_back({lnum, t});
			}
			else
			{
				declared[label_name] = {pc, use};
			}
		}
		string nop;
		if (!op.empty())
		{
			if (!needsoperand)
			{
				string t = "Unexpected Operand";
				Errors.push_back({lnum, t});
			}
			else
			{
				// check if it is valid label or valid number
				int A = 0;
				nop = Process_Operand(op, &A, lnum);
				if (A == 1)
				{
					string t = "Not a number or a valid Label";
					Errors.push_back({lnum, t});
				}
			}
		}
		else
		{
			if (needsoperand)
			{
				string t = "Missing Operand";
				Errors.push_back({lnum, t});
			}
		}
		Inst.push_back({pc, threepc(label_name, ins, nop)});
		pc += toincrease;
	}
	map<string, symb>::iterator it;
	for (it = used.begin(); it != used.end(); it++)
	{
		string name = it->first;
		symb temp = it->second;
		int add = temp.address;
		if (declared.count(name) == 0)
		{
			string t = "No such label as \"" + name + "\" has been declared";
			Errors.push_back({add, t});
		}
	}
	for (it = declared.begin(); it != declared.end(); it++)
	{
		string name = it->first;
		if (used.count(name) == 0)
		{
			string t = "Label with name \"" + name + "\" not used but declared";
			Warning.push_back({it->second.address, t});
		}
	}
}
string hexstr(int n, bool is24)
{
	string ans = "00000000";
	int idx = 7;
	if (n < 0)
	{
		unsigned int x = n;
		ans = "";
		while (x != 0)
		{
			int temp = x % 16;
			if (temp < 10)
			{
				ans = (char)(temp + 48) + ans;
			}
			else
			{
				ans = (char)(temp + 55) + ans;
			}
			x /= 16;
			idx--;
		}
		string res = "00000000";
		int j = 7;
		for (int i = ans.size() - 1; i >= 0 && j >= 0; i--, j--)
		{
			res[j] = ans[i];
		}
		ans = res;
	}
	else
	{
		while (n != 0)
		{
			int temp = n % 16;
			if (temp < 10)
			{
				ans[idx] = (char)(temp + 48);
			}
			else
			{
				ans[idx] = (char)(temp + 55);
			}
			n /= 16;
			idx--;
		}
	}
	if (is24)
		return ans.substr(2);
	return ans;
}
// PASS 2
void pass2()
{
	for (auto &Line : Inst)
	{
		// cout << Line.second <<endl ;
		int loc = Line.first;
		string label_name = Line.second.label_name;
		string ins = Line.second.ins;
		string op = Line.second.op;
		int operand_val;
		string ins_val;
		bool needsoffset = false;
		bool isthisdataval = false;
		if (!ins.empty())
		{
			ins_val = Optab[ins].opcode;
			if (Optab[ins].type == 2)
				needsoffset = true;
			/*
			if instruction is data special care needed
			*/
			if (ins == "data")
				isthisdataval = true;
			if (ins == "halt")
				isHaltPresent = true;
		}
		string final;
		if (!op.empty())
		{
			if (declared.count(op) == 0)
				operand_val = stoi(op);
			else
				operand_val = declared[op].address;

			if (needsoffset && declared.count(op) != 0)
			{
				operand_val -= loc + 1;
				/* Take care when operand should be 0 but it comes to be -1*/
			}
			/*
			operand value should be changed if you want offset ;
			convert the integer to 24 bit or 6 len string hexadecimal
			*/
			if (isthisdataval)
			{
				/* convert to 32 bit */
				final = hexstr(operand_val, false);
			}
			else
			{
				/* convert to 24 bit */
				final = hexstr(operand_val, true) + ins_val;
			}
		}
		else
			final = "000000" + ins_val;
		string program_counter = hexstr(loc, false);
		string mcode, lcode;
		lcode = program_counter;
		if (!ins.empty())
		{
			mcode = final;
			lcode += " " + final;
		}
		else
		{
			lcode += "         ";
		}
		if (!label_name.empty())
		{
			lcode += " " + label_name + ":";
		}
		if (!ins.empty())
		{
			lcode += " " + ins;
		}
		if (!op.empty())
		{
			lcode += " " + op;
		}
		if (!mcode.empty())
			MachineCode.push_back(mcode);
		if (!lcode.empty())
			ListingFile.push_back(lcode);
	}
	if (!isHaltPresent)
	{
		string t = "HALT instruction not found .";
		Warning.push_back({12, t});
	}
}
// optable is initialised with the opcodes and type
void Optable_initialisation()
{

	// type = 0 means no operand
	Optab["add"] = {"06", 0};
	Optab["sub"] = {"07", 0};
	Optab["shl"] = {"08", 0};
	Optab["shr"] = {"09", 0};
	Optab["a2sp"] = {"0B", 0};
	Optab["sp2a"] = {"0C", 0};
	Optab["return"] = {"0E", 0};
	Optab["halt"] = {"12", 0};

	// type = 1 means argument is given
	Optab["data"] = {"", 1};
	Optab["ldc"] = {"00", 1};
	Optab["adc"] = {"01", 1};
	Optab["set"] = {"", 1};
	Optab["adj"] = {"0A", 1};

	// type = 2 means offset to be given
	Optab["ldl"] = {"02", 2};
	Optab["stl"] = {"03", 2};
	Optab["ldnl"] = {"04", 2};
	Optab["stnl"] = {"05", 2};
	Optab["call"] = {"0D", 2};
	Optab["brz"] = {"0F", 2};
	Optab["brlz"] = {"10", 2};
	Optab["br"] = {"11", 2};
}

void Errors_display(const string &lgfile)
{
	sort(Errors.begin(), Errors.end());
	cerr << "Failed to Assemble!!" << endl;
	ofstream coutLog(lgfile);
	coutLog << "Failed to assemble!" << endl;
	coutLog << "Errors :-" << endl;
	for (auto x : Errors)
	{
		cerr << "Error at Line " << x.first << " : " << x.second << endl;
		coutLog << "Error at Line " << x.first << " : " << x.second << endl;
	}

	coutLog.close();
	exit(0);
}
void Warning_display(const string &lgfile)
{
	sort(Warning.begin(), Warning.end());
	ofstream coutLog(lgfile);
	coutLog << "Warning :-" << endl;
	for (auto x : Warning)
	{
		cerr << "Warning at Line " << x.first << " : " << x.second << endl;
		coutLog << "Warning at Line " << x.first << " : " << x.second << endl;
	}
	coutLog.close();
}

void write_listing_file(const string &lsfile)
{
	ofstream outfile(lsfile);
	for (auto &x : ListingFile)
	{
		outfile << x << endl;
	}
	outfile.close();
}

void write_object_code_file(const string &mcfile)
{
	ofstream noutfile;
	noutfile.open(mcfile, ios::binary | ios::out);
	for (auto &x : MachineCode)
	{
		unsigned int y;
		std::stringstream ss;
		ss << std::hex << x;
		ss >> y;
		static_cast<int>(y);
		noutfile.write((const char *)&y, sizeof(unsigned));
	}
	noutfile.close();
}

int main(int argc, char *argv[])
{
	// file format check , name extraction & Intialization
	if (argc != 2)
	{
		cerr << "Error: Only pass the .asm file";
		return 0;
	}
	int fname_len = strlen(argv[1]);
	if (fname_len <= 3 or strcmp("asm", argv[1] + fname_len - 3))
	{
		cerr << "Error: Incorrect file type" << endl;
		cerr << "Enter a .asm file" << endl;
		return 0;
	}

	string filename(argv[1]);
	string namewithoutasm = "";
	int i = 0;
	while (argv[1][i] != '.')
	{
		namewithoutasm += argv[1][i];
		i++;
	}

	InputName = namewithoutasm + ".asm";
	string lgfile, lsfile, mcfile;
	lgfile = namewithoutasm + "log.txt";
	lsfile = namewithoutasm + ".l";
	mcfile = namewithoutasm + ".o";

	Optable_initialisation();

	/**************************************************************/
	/*Assembler Passes & Error and warning genration*/
	/*************************************************************/

	pass1();

	if (Errors.size() > 0)
		Errors_display(lgfile);

	pass2();

	Warning_display(lgfile);

	/**************************************************************/
	/*Listing and Object File generation*/
	/**************************************************************/

	write_listing_file(lsfile);
	write_object_code_file(mcfile);
	cerr << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cerr << "Compiled without errors!!!" << endl;
	cerr << "Logs generated in: " + namewithoutasm + "log.txt" << endl;
	cerr << "Machine code generated in: " + namewithoutasm + ".o" << endl;
	cerr << "Listing generated in: " + namewithoutasm + ".l" << endl;
	cerr << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

	return 0;
}
