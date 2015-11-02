namespace CodeGeneratorNameSpace
{
class CodeGenerator;
class Initialtor;
class FixedWire;
class Component;
class SingleComponent;
class Input;
class Output;
class MultipleComponent;
class Connection;
class InterConnection;
class InputConnection;
class OutputConnection;
class Range;
class GarbledClass;
class JavaClass;
}
#ifndef CodeGeneratorNameSpace_H_
#define CodeGeneratorNameSpace_H_
#include <string>
#include <vector>
#include <unordered_map>
#include "CodeWriter.h"
using namespace std;
//using namespace CodeWriterNameSpace;

/******************************************************************************************
CodeGeneratorNameSpace
*******************************************************************************************/
namespace CodeGeneratorNameSpace
{
	class CodeGenerator
	{
	public:
		virtual CodeWriterNameSpace::Statement* getStatement() = 0;
		//friend Range* getRange(string range);
		virtual ~CodeGenerator();
		void setDescription(string description);
		//show the description
		string showDescription(int n);
		string printCode(int n);
	private:
		string description;
	};
}
/******************************************************************************************
Initialtor
*******************************************************************************************/
namespace CodeGeneratorNameSpace
{
	class Initialtor : public CodeGenerator
	{
	private:
		string className;
		string circuitIndexes;
		string arguments;
		string indexAlias;
		bool single;
	public:
		Initialtor();
		~Initialtor();
		Initialtor(string ci, string arg, string className);
		CodeWriterNameSpace::Statement *getStatement();
		void setIndexAlias(string alias);
	};
}

/******************************************************************************************
FixedWire
*******************************************************************************************/
namespace CodeGeneratorNameSpace
{
	class FixedWire : public CodeGenerator
	{
	private:
		string circuitIndexes;
		string indexAlias;
		string portStartIndex;
		string portIndexes;
		string value;
	public:
		FixedWire(string ci, string psi, string pi, string v);
		virtual CodeWriterNameSpace::Statement* getStatement();

	};
}

/******************************************************************************************
Component
*******************************************************************************************/
namespace CodeGeneratorNameSpace
{
	class Component
	{
	protected:
		string portIndex;
	public:
		//the connection type is determined by the src end
		virtual CodeWriterNameSpace::ConnectionStatement* getConnectionStatement() = 0;
		virtual string getCircuitID() = 0;
		virtual string getPortID() = 0;
		Component(string pi);
		CodeWriterNameSpace::ForLoopStatement* generateForLoopStatement();
	private:
		virtual CodeWriterNameSpace::ForLoopStatement* getFirstForLoopStatement(string variable) = 0;
	};
}

/******************************************************************************************
SingleComponent
*******************************************************************************************/
namespace CodeGeneratorNameSpace
{
	class SingleComponent : public Component
	{
	protected:
		string startIndexRange;
	private:
		string circuitIndex;
		string indexAlias;
	public:
		virtual CodeWriterNameSpace::ConnectionStatement* getConnectionStatement();
		SingleComponent(string ci, string si, string port);
		string getCircuitID();
		string getPortID();
	private:
		virtual CodeWriterNameSpace::ForLoopStatement* getFirstForLoopStatement(string variable);
	};
}

/******************************************************************************************
MultipleComponent
*******************************************************************************************/
namespace CodeGeneratorNameSpace
{
	class MultipleComponent : public Component
	{
	private:
		string circuitIndexes;
		string indexAlias;
	public:
		virtual CodeWriterNameSpace::ConnectionStatement* getConnectionStatement();
		string getCircuitID();
		string getPortID();
		MultipleComponent(string ci, string port);
	private:
		virtual CodeWriterNameSpace::ForLoopStatement* getFirstForLoopStatement(string variable);
	};
}


/******************************************************************************************
Input
*******************************************************************************************/
namespace CodeGeneratorNameSpace
{
	class Input : public SingleComponent
	{
	public:
		Input(string ip, string port);
		virtual CodeWriterNameSpace::ConnectionStatement* getConnectionStatement();
	};
}
/******************************************************************************************
Output
*******************************************************************************************/
namespace CodeGeneratorNameSpace
{
	class Output : public SingleComponent
	{
	public:
		Output(string ip, string port);
		virtual CodeWriterNameSpace::ConnectionStatement* getConnectionStatement();
	};
}

/******************************************************************************************
Connection
*******************************************************************************************/
namespace CodeGeneratorNameSpace
{
	class Connection : public CodeGenerator
	{
	private:
		//a input [0:1:2L], startIndex[0:1:2]
		Component* sourceCircuit;
		//multiple 2
		Component* destinationCircuit;
	public:
		virtual ~Connection();
		Connection(Component* sc, Component* dc);
		virtual CodeWriterNameSpace::Statement* getStatement();
	};
}

/******************************************************************************************
InputConnection
*******************************************************************************************/
namespace CodeGeneratorNameSpace
{
	class InputConnection : public Connection
	{
	public:
		~InputConnection();
		InputConnection(string inputStartIndex, string sc, Component* endpoint);
	
	};
}

/******************************************************************************************
OutputConnection
*******************************************************************************************/
namespace CodeGeneratorNameSpace
{
	class OutputConnection : public Connection
	{
	public:
		~OutputConnection();
		OutputConnection(string inputStartIndex, string sc, Component* endpoint);
	};
}

/******************************************************************************************
Range
*******************************************************************************************/
//to seperate range use ;
//in a range, use , particularly within parameter list
namespace CodeGeneratorNameSpace
{
	class Range
	{
	protected:
		bool multiple;
	public:
		bool isMultiple();
		virtual string getVariableID();
		virtual string getNum();
		virtual string printDefineAlias(string alias);
		virtual string getAliasID(string alias);
	};
}
/******************************************************************************************
SingleRange
*******************************************************************************************/
namespace CodeGeneratorNameSpace
{
	class SingleRange : public Range
	{
	private:
		string index;
	public:
		SingleRange(string str);
		string getVariableID();
		string printDefineAlias(string alias);
		string getAliasID(string alias);
	};
}

/******************************************************************************************
MultipleRange
*******************************************************************************************/
namespace CodeGeneratorNameSpace
{
	class MultipleRange : public Range
	{
	private:
		string startIndex;
		string step;
		string num;
		string variable;
	public:
		MultipleRange(string str);
		void setVariable(string str);
		string getVariableID();
		string getNum();
		string printDefineAlias(string alias);
		string getAliasID(string alias);
	};
}

/******************************************************************************************
GarbledClass
*******************************************************************************************/
namespace CodeGeneratorNameSpace
{
	class GarbledClass : public CodeGenerator
	{
	private:
		string className;
		string arguments;
		string inDegree;
		string outDegree;
		string componentNum;
	public:
		GarbledClass(string cn, string as, string in, string out, string component);
		virtual CodeWriterNameSpace::Statement* getStatement();
		string getClassName();
		GarbledClass();
		GarbledClass(const GarbledClass& gc);
	};
}
/******************************************************************************************
JavaClass
*******************************************************************************************/
namespace CodeGeneratorNameSpace
{
class JavaClass
	{
	private:
		GarbledClass gc;
		vector<Initialtor> init;
		vector<Connection> inter;
		vector<InputConnection> input;
		vector<OutputConnection> output;
		vector<FixedWire> fw;
	public:
		JavaClass();
		JavaClass(GarbledClass _gc, 
						vector<Initialtor> _init,
						vector<Connection> _inter, 
						vector<InputConnection> _input,
						vector<OutputConnection> _output,
						vector<FixedWire> _fw);
		JavaClass(GarbledClass _gc);
		string getFileContent();
		void insert(Initialtor i);
		void insert(Connection c);
		void insert(InputConnection ic);
		void insert(OutputConnection);
		void insert(FixedWire f);
		void insert(GarbledClass gc);
		void clear();
	private:
		string getHeader(int n = 0);
		string getConstructor(int n = 0);
		string getCreateSubCircuit(int n = 0);
		string getConnectWires(int n = 0);
		string getDefineOutput(int n = 0);
		string getFixedWire(int n = 0);

	};
}

/******************************************************************************************
global variable
*******************************************************************************************/
namespace CodeGeneratorNameSpace
{
	extern unordered_map<string, vector<string> > aliasList;
	Range* getRange(string str);
	vector<Range* > getComboRange(string str);

	bool checkSingleRange(string str);
	bool checkMultipleRange(string str);
}
#endif  /*  end CodeGeneratorNameSpace.h file  */


