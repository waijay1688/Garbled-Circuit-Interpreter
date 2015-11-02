/*
 * BinaryLinearEquation.h
 *
 *  Created on: Jan 29, 2015
 *      Author: yuw1 
 */

#ifndef CODEWRITER_H_
#define CODEWRITER_H_
#include <string>
#include<vector>

using namespace std;

namespace CodeWriterNameSpace {
class Statement;
class ForLoopStatement;
class ConnectionStatement;
class InitialtorStatement;
class GateStatement;
class InterConnectionStatement;
class OutputConnectionStatement;
class InputConnectionStatement;
class FixedWireStatement;
class GarbledClassConstructor;
}
#include "CodeGenerator.h"

/******************************************************************************************
Variable
*******************************************************************************************/
namespace CodeWriterNameSpace
{
	const string SUBCIRCUITS = "subCircuits";
	const string CONNECTTO = "connectTo";
	const string INPUTWIRES = "inputWires";
	const string OUTPUTWIRES = "outputWires";
	const string FIXWIRE = "fixWire";
};
/******************************************************************************************
*class Statement
*******************************************************************************************/
namespace CodeWriterNameSpace 
{
class Statement {
public:
	//Statement();
	//virtual ~Statement();
	virtual string toString(int n = 0) = 0;
};

} /* namespace CodeWriterNameSpace */

/******************************************************************************************
*class ConnectionStatement
*******************************************************************************************/
namespace CodeWriterNameSpace {

class ConnectionStatement: public Statement {
public:
	//ConnectionStatement();
	//virtual ~ConnectionStatement();
	virtual string toString(int n = 0)=0;
	void setDesCircuitID(string str);
	void setDesInportID(string str);
protected:
	string destinationCircuitId;
	string destinationPortId;
};

} /* namespace CodeWriterNameSpace */




/******************************************************************************************
*class ForLoopStatement
*******************************************************************************************/
namespace CodeWriterNameSpace 
{
class ForLoopStatement: public Statement 
{
public:
	ForLoopStatement();
	ForLoopStatement(string num, string variable);
	virtual ~ForLoopStatement();
	void insertToForLoop(Statement* s);
	string toString(int n = 0);
private:
	string startIndex;
	string endIndex;
	string step;
	string variable;
	Statement*  statement;
};

} /* namespace CodeWriterNameSpace */

/******************************************************************************************
*class FixedWireStatement
*******************************************************************************************/
namespace CodeWriterNameSpace {
class FixedWireStatement: public Statement {
public:
	FixedWireStatement(string ic, string ip, string v);
	//virtual ~FixedWireStatement();
	virtual string toString(int n = 0);
private:
	string inputCircuitId;
	string inputPortId;
	string value;
};

} /* namespace CodeWriterNameSpace */

/******************************************************************************************
*class InitialtorStatement
*******************************************************************************************/
namespace CodeWriterNameSpace {

class InitialtorStatement: public Statement {
public:
	InitialtorStatement(string index, vector<string> arg, string cn);
	virtual ~InitialtorStatement();
	virtual string toString(int n = 0);
private:
	string index;
	vector<string> arguments;
	string className;
};
}

/******************************************************************************************
*class GateStatement
*******************************************************************************************/
namespace CodeWriterNameSpace {

class GateStatement: public Statement {
public:
	GateStatement(string i, string cn);
	virtual ~GateStatement();
	virtual string toString(int n = 0);
private:
	string index;
	string className;
};


} /* namespace CodeWriterNameSpace */

/******************************************************************************************
*class InterConnectionStatement
*******************************************************************************************/
namespace CodeWriterNameSpace {

class InterConnectionStatement: public ConnectionStatement {
public:
	InterConnectionStatement(string sc, string sp);
	virtual ~InterConnectionStatement();
	virtual string toString(int n = 0);
private:
	string sourceCircuitId;
	string sourcePortId;
};

} /* namespace CodeWriterNameSpace */


/******************************************************************************************
*class OutputConnectionStatement
*******************************************************************************************/
namespace CodeWriterNameSpace {

class OutputConnectionStatement: public ConnectionStatement {
public:
	OutputConnectionStatement(string op);
	//virtual ~OutputConnectionStatement();
	virtual string toString(int n = 0);
private:
	string outputPortId;
};
}

/******************************************************************************************
*class InputConnectionStatement
*******************************************************************************************/
namespace CodeWriterNameSpace {

class InputConnectionStatement: public ConnectionStatement {
public:
	InputConnectionStatement(string ip);
	virtual ~InputConnectionStatement();
	virtual string toString(int n = 0);
private:
	string inputPortId;
};

} /* namespace CodeWriterNameSpace */

/******************************************************************************************
*class GarbledClassConstructor
*******************************************************************************************/
namespace CodeWriterNameSpace {

class GarbledClassConstructor: public Statement {
public:
	virtual string toString(int n = 0);
	GarbledClassConstructor(string cn, vector<string> as, string in, string out, string component);
private:
	string className;
	vector<string> arguments;
	string indegree;
	string outdegree;
	string componentNum;
private:
	string declareVariable(int n = 0);
	string declareConstruction(int n =0);
};

} /* namespace CodeWriterNameSpace */


#endif 
