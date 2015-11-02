#include "stdafx.h"
#include "CodeWriter.h"

/******************************************************************************************
*class Statement
*******************************************************************************************/
namespace CodeWriterNameSpace {

}

/******************************************************************************************
*class InitialtorStatement
*******************************************************************************************/
namespace CodeWriterNameSpace {

	string InitialtorStatement:: toString(int n)
	{
		string indent(n, '\t');
		string output = indent+SUBCIRCUITS+"["+index+"] = new "+className+"(";
		int size = arguments.size();
		for(int i=0; i<size; i++)
		{
			output += arguments[i];
			if(size-1 != i)
				output += ", ";
		}
		output += ");\n";
		return output;
	}

	InitialtorStatement::InitialtorStatement(string i, vector<string> a, string cn):index(i), arguments(a), className(cn)
	{
	}

	InitialtorStatement:: ~InitialtorStatement()
	{
	}

} /* namespace CodeWriter */


/******************************************************************************************
*class GateStatement
*******************************************************************************************/
namespace CodeWriterNameSpace {

	string GateStatement:: toString(int n)
	{
		string indent(n, '\t');
		string output = indent+"subCircuits["+index+"] = "+className+".newInstance();\n";
		return output;
	}

	GateStatement::GateStatement(string i,  string cn):index(i), className(cn)
	{
	}

	GateStatement:: ~GateStatement()
	{
	}

} /* namespace CodeWriter */


/******************************************************************************************
*class ConnectionStatement
*******************************************************************************************/
namespace CodeWriterNameSpace {

	void ConnectionStatement::setDesCircuitID(string str)
	{
		this->destinationCircuitId = str;
	}
	void ConnectionStatement::setDesInportID(string str)
	{
		destinationPortId = str;
	}
}

/******************************************************************************************
*class InterConnectionStatement
*******************************************************************************************/
namespace CodeWriterNameSpace {
	string InterConnectionStatement:: toString(int n)
	{
		string indent(n, '\t');
		string output = indent+SUBCIRCUITS+"[";
		output += sourceCircuitId;
		output += "]."+OUTPUTWIRES+"[";
		output += sourcePortId;
		output += "]."+CONNECTTO+"("+SUBCIRCUITS+"[";
		output += destinationCircuitId;
		output += "]."+INPUTWIRES+", ";
		output += destinationPortId;
		output += ");\n";
		return output;
	}
	InterConnectionStatement:: InterConnectionStatement(string sc, string sp):sourceCircuitId(sc), sourcePortId(sp)
	{
	}

	InterConnectionStatement:: ~InterConnectionStatement()
	{
	}
}; /* namespace CodeWriter */



/******************************************************************************************
*class OutputConnectionStatement
*******************************************************************************************/
namespace CodeWriterNameSpace {

	string OutputConnectionStatement:: toString(int n)
	{
		string indent(n, '\t');
		string output = indent+OUTPUTWIRES+"[";
		output += outputPortId;
		output += "] = "+SUBCIRCUITS+"[";
		output += destinationCircuitId;
		output += "]."+OUTPUTWIRES+"[";
		output += destinationPortId;
		output += "];\n";
		return output;
	}
	OutputConnectionStatement::OutputConnectionStatement(string op):outputPortId(op)
	{
	}
}

/******************************************************************************************
*class InputConnectionStatement
*******************************************************************************************/
namespace CodeWriterNameSpace {

	string InputConnectionStatement:: toString(int n)
	{
		string indent(n, '\t');
		string output = indent+INPUTWIRES+"[";
		output += inputPortId;
		output += "]."+CONNECTTO+"("+SUBCIRCUITS+"[";
		output += destinationCircuitId;
		output += "]."+INPUTWIRES+", ";
		output += destinationPortId;
		output += ");\n";
		return output;
	};
	InputConnectionStatement::InputConnectionStatement(string ip):inputPortId(ip)
	{
	}

	InputConnectionStatement::~InputConnectionStatement()
	{
	}

} /* namespace CodeWriter */


/******************************************************************************************
*class FixedWireStatement
*******************************************************************************************/
namespace CodeWriterNameSpace {
	string FixedWireStatement:: toString(int n)
	{
		string indent(n, '\t');
		string output = indent+SUBCIRCUITS+"[";
		output += inputCircuitId;
		output += "]."+INPUTWIRES+"[";
		output += inputPortId;
		output += "]."+FIXWIRE+"(";
		output += value;
		output += ");\n";
		return output;
	}

	FixedWireStatement::FixedWireStatement(string ic, string ip, string v):inputCircuitId(ic), inputPortId(ip), value(v)
	{
	}
};


/******************************************************************************************
*class ForLoopStatement
*******************************************************************************************/
namespace CodeWriterNameSpace {
	string ForLoopStatement:: toString(int n) 
	{
		string indent(n, '\t');
		string output = indent+"for( int ";
		output += variable;
		output += "=";
		output += startIndex;
		output += "; ";
		output += variable;
		output += "<";
		output += endIndex;
		output += "; ";
		output += variable+"="+variable+"+"+step;
		output +=")\n"+indent+"{\n";
		output += statement->toString(n+1);
		output += indent+"}\n";
		return output;
	}

	ForLoopStatement::~ForLoopStatement()
	{
		if(0 != statement)
			delete statement;
	}

	void ForLoopStatement:: insertToForLoop(Statement* s)
	{
		if(0 == statement)
			statement = s;
		else
			((ForLoopStatement*)statement)->insertToForLoop(s);
	}

	ForLoopStatement::ForLoopStatement()
	{
	}

	ForLoopStatement::ForLoopStatement(string num, string variable)
	{
		this->startIndex = "0";
		this->endIndex = num;
		this->step = "1";
		this->variable = variable;
		this->statement = 0;
	}

	
};


/******************************************************************************************
*class GarbledClassFunction
*******************************************************************************************/
namespace CodeWriterNameSpace {

	GarbledClassConstructor::GarbledClassConstructor(string cn, vector<string> as, string in, string out, string component)
		:className(cn), arguments(as), indegree(in), outdegree(out), componentNum(component)
	{}
	string GarbledClassConstructor:: toString(int n)
	{
		string output = "";
		output += declareVariable(n);
		output += declareConstruction(n);
		return output;
	}

	string GarbledClassConstructor::declareVariable(int n)
	{
		string indent(n, '\t');
		string output = "";
		for(auto it=arguments.begin(); it!=arguments.end(); it++)
			output += indent+"private final int "+(*it)+";\n";
		return output;
	}

	string GarbledClassConstructor::declareConstruction(int n)
	{
		string indent(n, '\t');
		string output = "";
		//header
		output += indent+"public "+className+"_Weijie"+"(";
		int size = arguments.size();
		for(int i=0; i<size; i++)
		{
			output += "int "+arguments[i];
			if(size-1 != i)
				output += ", ";
		}
		output += ")\n";
		output += indent+"{\n";
		//call the father construction
		output += indent+"\tsuper("+indegree+", "+outdegree+", "+componentNum+", \""+className+"_"+indegree+"\");\n";

		for(int i=0; i<size; i++)
			output += indent+"\tthis."+arguments[i]+" = "+arguments[i]+";\n";
		output += indent+"}\n";
		return output;
	}

} /* namespace CodeWriter */