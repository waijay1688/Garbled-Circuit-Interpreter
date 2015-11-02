#include "stdafx.h"
#include <iostream>
#include <vector>
#include <assert.h>
#include "CodeGenerator.h"
using namespace CodeWriterNameSpace;

/******************************************************************************************
global variable
*******************************************************************************************/
namespace CodeGeneratorNameSpace
{
	unordered_map<string, vector<string> > aliasList;
	Range* getRange(string str)
	{
		if(-1 == str.find(':'))
			return new SingleRange(str);
		else
			return new MultipleRange(str);
	}
	//seperate by ','
	vector<Range* > getComboRange(string str)
	{
		vector<Range* > comboRange;
		str.push_back(',');
		int lastI = 0;
		int curI = str.find(',', lastI);
		while(-1 != curI)
		{
			comboRange.push_back(getRange(str.substr(lastI, curI-lastI)));
			lastI = curI+1;
			curI = str.find(',', lastI);
		}
		return comboRange;
	}

	bool checkSingleRange(string str)
	{
		if(str.empty())
			return false;
		for(int i=0; i<str.length(); i++)
		{
			char c = str[i];
			if(' ' == c)
				return false;
		}
		return true;
	}

	bool checkMultipleRange(string str)
	{
		int counter = 0;
		for(int i=0; i<str.length(); i++)
		{
			if(':'==str[i])
				counter++;
			if(counter > 2)
				return false;
		}
		return 2 == counter;
	}
}

/******************************************************************************************
CodeGenerator
*******************************************************************************************/
namespace CodeGeneratorNameSpace
{

CodeGenerator::~CodeGenerator()
{
}


//set the description
void CodeGenerator::setDescription(string description)
{
	this->description = description;
}
string CodeGenerator::printCode(int n)
{
	//get description comment first.
	string result = showDescription(n);
	Statement *s = getStatement();
	result += s->toString(n);
	delete s;
	return result;
}
string CodeGenerator::showDescription(int n)
{
	if(description.empty())
		return "";
	description.push_back(' ');
	string indent(n, '\t');
	int maxLen = 40;
	string result = indent+"//";
	string word = "";
	int lineLen = 0;

	for(int i=0; i<description.length(); i++)
	{
		if(' ' == description[i])
		{
			if(word.empty())
				continue;
			if(lineLen+word.length()<maxLen)
			{
				result += word+" ";
				lineLen += word.length()+1;
			}
			else
			{
				result += "\n"+indent+"//"+word;
				lineLen = word.length();
			}
			word = "";
		}
		else
			word.push_back(description[i]);
	}
	result += "\n";
	return result;
}
}

/******************************************************************************************
Range
*******************************************************************************************/

namespace CodeGeneratorNameSpace
{
	bool Range::isMultiple()
	{
		return this->multiple;
	}

	string Range::getVariableID()
	{
		return "";
	}

	string Range::printDefineAlias(string alias)
	{
		return "";
	}

	string Range::getAliasID(string alias)
	{
		return "";
	}
	string Range::getNum()
	{
		return "1";
	}

}

/******************************************************************************************
SingleRange
*******************************************************************************************/
namespace CodeGeneratorNameSpace
{
	SingleRange::SingleRange(string str)
	{
		//assert(checkSingleRange(str));
		this->index = str;
		this->multiple = false;
	}

	string SingleRange::getVariableID()
	{
		return index;
	}

	string SingleRange::printDefineAlias(string alias)
	{
		string result = "private final static int "+alias + " = " + this->getVariableID()+";\n";
		aliasList[alias].push_back(result);
		return result;
	}

	string SingleRange::getAliasID(string alias)
	{
		return alias;
	}
}

/******************************************************************************************
MultipleRange
*******************************************************************************************/
namespace CodeGeneratorNameSpace
{

	MultipleRange::MultipleRange(string str)
	{
		//assert(checkMultipleRange(str));
		int index1 = str.find_first_of(':');
		int index2 = str.find_last_of(':');
		this->startIndex = str.substr(0, index1);
		this->num = str.substr(index2+1);
		this->step = str.substr(index1+1, index2-index1-1);
		this->multiple = true;
		//set variable "i" as default
		this->variable = "i";
	}

	string MultipleRange::getVariableID()
	{
		return this->startIndex+"+"+this->variable+"*"+this->step;
	}

	string MultipleRange::getNum()
	{
		return this->num;
	}

	void MultipleRange::setVariable(string str)
	{
		this->variable = str;
	}

	string MultipleRange::printDefineAlias(string alias)
	{
		string result1 = "private int " + alias+"(int "+variable+") {\n";
		aliasList[alias].push_back(result1);
		string result2 = "\treturn "+this->getVariableID()+";\n";
		aliasList[alias].push_back(result2);
		string result3 = "}\n";
		aliasList[alias].push_back(result3);
		return result1+result2+result3;
	}
	string MultipleRange::getAliasID(string alias)
	{
		return alias+"("+variable+")";
	}
}

/**********************************************************************************
*Initialtor
**********************************************************************************/
namespace CodeGeneratorNameSpace
{
Initialtor::Initialtor()
{
}
Initialtor::~Initialtor()
{
}
Initialtor::Initialtor(string ci, string arg, string cn)
{
	this->circuitIndexes = ci;
	this->arguments = arg;
	this->className = cn;
}
void Initialtor::setIndexAlias(string alias)
{
	this->indexAlias = alias;
}
Statement* Initialtor::getStatement()
{
	Range *cir = getRange(circuitIndexes);
	vector<Range*>  pir = getComboRange(arguments);
	ForLoopStatement *fls = 0;
	//need for loop
	if(cir->isMultiple())
	{
		((MultipleRange*) cir)->setVariable("i");
		//it should be a multiple range
		
		for(int i=0; i<pir.size(); i++)
		{
			if(pir[i]->isMultiple())
				((MultipleRange*)pir[i])->setVariable("i");
		}
		
		//may set forloop variable here
		//to match the range
		fls = new ForLoopStatement(cir->getNum(), "i");
		
	}
	//show the alias
	if(!this->indexAlias.empty())
		cir->printDefineAlias(indexAlias);
	//get the circuitID
	string circuitId = cir->getVariableID();
	if(!this->indexAlias.empty())
		circuitId = cir->getAliasID(indexAlias);
	delete cir;
	//get the id of the parameters
	vector<string> parameters;
	for(int i=0; i<pir.size(); i++)
	{
		parameters.push_back(pir[i]->getVariableID());
		delete pir[i];
	}
	
	Statement* is = 0;
	/*
	**  special case, AND and OR gate, not initialized by new, but by static function
	*/
	if("AND" != className && "OR" != className)
	{
		if("XOR" == className)
			className += "_2_1";
		is = new InitialtorStatement(circuitId, parameters, this->className);
	}
	else
		is = new GateStatement(circuitId, className+"_2_1");
	
	//for loop or just single initialization
	if(0 != fls)
	{
		fls->insertToForLoop(is);
		return fls;
	}
	else
		return is;	
}

}

/******************************************************************************************
FixedWire
*******************************************************************************************/
namespace CodeGeneratorNameSpace
{

	FixedWire::FixedWire(string ci, string psi, string pi, string v):circuitIndexes(ci), portStartIndex(psi), portIndexes(pi), value(v)
	{
	};
	Statement* FixedWire::getStatement()
	{
		Statement* s = 0;
		//first loop the circuitIndex, variable "i"
		Range* rCircuit = getRange(circuitIndexes);
		ForLoopStatement *f1 = 0;
		if(rCircuit->isMultiple())
		{
			((MultipleRange*)rCircuit)->setVariable("i");
			f1 = new ForLoopStatement(rCircuit->getNum(), "i");
		}
		//second loop index start, set variable j
		Range *rStart = getRange(portStartIndex);
		ForLoopStatement *f2 = 0;
		if(rStart->isMultiple())
		{
			((MultipleRange*)rStart)->setVariable("j");
			f2 = new ForLoopStatement(rStart->getNum(), "j");
		}
		
		//third loop, port index, set variable k
		Range *rPort = getRange(portIndexes);
		ForLoopStatement *f3 = 0;
		if(rPort->isMultiple())
		{
			((MultipleRange*)rPort)->setVariable("k");
			f3 = new ForLoopStatement(rPort->getNum(), "k");
		}
		//circuit alias
		string circuitID = rCircuit->getVariableID();
		if(!this->indexAlias.empty())
		{
			rCircuit->printDefineAlias(indexAlias);
			circuitID = rCircuit->getAliasID(indexAlias);
		}

		Statement *fw = new FixedWireStatement(circuitID,rStart->getVariableID()+"+"+rPort->getVariableID(), value);
		
		if(0 != f1)
		{
			f1->insertToForLoop(f2);
			f1->insertToForLoop(f3);
			f1->insertToForLoop(fw);
			s = f1;
		}
		else
		if(0 != f2)
		{
			f2->insertToForLoop(f3);
			f2->insertToForLoop(fw);
			s = f2;
		}
		else
		if(0 != f3)
		{
			f3->insertToForLoop(fw);
			s = f3;
		}
		else
			s = fw;
		
		delete rCircuit;
		delete rStart;
		delete rPort;
		return s;
	}
}
/******************************************************************************************
Connection
*******************************************************************************************/

// only one sentence
namespace CodeGeneratorNameSpace
{
	
	Connection::Connection(Component* sc, Component* dc):sourceCircuit(sc), destinationCircuit(dc)
	{
	}
	Connection::~Connection()
	{
		//delete this->sourceCircuit;
		//delete this->destinationCircuit;
	}
	Statement* Connection::getStatement()
	{
		//may include for loop?
		//Statement *cs = sourceCircuit->generateStatement();
		//cs->setDesCircuitID(this->destinationCircuit->getCircuitVariable());
		//cs->setDesInportID(this->destinationCircuit->getPortVariable());
		//s = cs;
		//return cs;
		ForLoopStatement *fs = sourceCircuit->generateForLoopStatement();
		ConnectionStatement *cs = sourceCircuit->getConnectionStatement();
		cs->setDesCircuitID(destinationCircuit->getCircuitID());
		cs->setDesInportID(destinationCircuit->getPortID());
		if(0 == fs)
			return cs;
		fs->insertToForLoop(cs);
		return fs;
	}
}
/******************************************************************************************
Component
*******************************************************************************************/
namespace CodeGeneratorNameSpace
{
	Component::Component(string pi):portIndex(pi)
	{}

	ForLoopStatement* Component::generateForLoopStatement()
	{
		//first for loop, set variable i
		ForLoopStatement *f1 = getFirstForLoopStatement("i");
		//second loop
		Range *rPort = getRange(this->portIndex);
		ForLoopStatement *f2 = 0;
		if(rPort->isMultiple())
			f2 = new ForLoopStatement(rPort->getNum(), "j");
		delete rPort;
		if(0 != f1)
		{
			f1->insertToForLoop(f2);
			return f1;
		}
		else
			return f2;
	}
}

/******************************************************************************************
SingleComponent
*******************************************************************************************/
namespace CodeGeneratorNameSpace
{

	SingleComponent::SingleComponent(string ci, string si, string port): Component(port), startIndexRange(si), circuitIndex(ci)
	{
	}

	string SingleComponent::getCircuitID()
	{
		//should be single
		Range * rCircuit = getRange(this->circuitIndex);
		string circuitID = rCircuit->getVariableID();
		if(!this->indexAlias.empty())
		{
			rCircuit->printDefineAlias(indexAlias);
			circuitID = rCircuit->getAliasID(indexAlias);
		}
		if(rCircuit->isMultiple())
			cout<<"multiple range in single component\n";
		delete rCircuit;
		return circuitID;
	}
	string SingleComponent::getPortID()
	{
		string result = "";
		if(!startIndexRange.empty())
		{
			Range *rStart = getRange(this->startIndexRange);
			if(rStart->isMultiple())
				((MultipleRange*)rStart)->setVariable("i");
			result += rStart->getVariableID();
			delete rStart;
		}
		Range *rPort = getRange(this->portIndex);
		if(!rPort->isMultiple())
			if(result.empty())
				result = rPort->getVariableID();
			else
				result += "+"+rPort->getVariableID();
		else
		{
			((MultipleRange*)rPort)->setVariable("j");
			if(result.empty())
				result = rPort->getVariableID();
			else
				result += "+"+rPort->getVariableID();
		}
		delete rPort;
		return result;
	}
	ConnectionStatement* SingleComponent::getConnectionStatement()
	{
		InterConnectionStatement *ic = new InterConnectionStatement(getCircuitID(), getPortID());
		return ic;
	};
	ForLoopStatement* SingleComponent::getFirstForLoopStatement(string variable)
	{
		if(startIndexRange.empty())
			return 0;
		Range *rStart = getRange(startIndexRange);
		ForLoopStatement *f1 = 0;
		if(rStart->isMultiple())
		{
			((MultipleRange*)rStart)->setVariable(variable);
			f1 = new ForLoopStatement(rStart->getNum(), variable);
		}
		delete rStart;
		return f1;
	}
}

/******************************************************************************************
MultipleComponent
*******************************************************************************************/
namespace CodeGeneratorNameSpace
{
	string MultipleComponent:: getCircuitID()
	{
		Range *rCircuit = getRange(circuitIndexes);
		string circuitID = rCircuit->getVariableID();
		
		if(rCircuit->isMultiple())
			((MultipleRange*)rCircuit)->setVariable("i");
		else
			cout<<"single range in multiple componnet\n";
		if(!this->indexAlias.empty())
		{
			rCircuit->printDefineAlias(indexAlias);
			circuitID = rCircuit->getAliasID(indexAlias);
		}
		delete rCircuit;
		return circuitID;
	}

	string MultipleComponent::getPortID()
	{
		Range *rPort = getRange(this->portIndex);	
		if(rPort->isMultiple())
			((MultipleRange*)rPort)->setVariable("j");
		string portID = rPort->getVariableID();
		delete rPort;
		return portID;
	}
	MultipleComponent::MultipleComponent(string ci, string port):Component(port), circuitIndexes(ci)
	{
	}
	ForLoopStatement* MultipleComponent::getFirstForLoopStatement(string variable)
	{
		Range *rCircuit = getRange(circuitIndexes);
		ForLoopStatement *f1 = 0;
		if(rCircuit->isMultiple())
		{
			((MultipleRange*)rCircuit)->setVariable(variable);
			f1 = new ForLoopStatement(rCircuit->getNum(), variable);
		}
		else
			cout<<"single range in multiple componnet\n";
		delete rCircuit;
		return f1;
	}

	ConnectionStatement* MultipleComponent::getConnectionStatement()
	{
		InterConnectionStatement *ic = new InterConnectionStatement(getCircuitID(), getPortID());
		return ic;
	};
}
/******************************************************************************************
Input
*******************************************************************************************/
namespace CodeGeneratorNameSpace
{
	Input::Input(string ip, string port):SingleComponent("",ip, port)
	{
	};
	ConnectionStatement* Input::getConnectionStatement()
	{
		return new InputConnectionStatement(getPortID());
	}

}

/******************************************************************************************
Output
*******************************************************************************************/
namespace CodeGeneratorNameSpace
{
	Output::Output(string ip, string port):SingleComponent("", ip, port)
	{
	};
	ConnectionStatement* Output::getConnectionStatement()
	{
		return new OutputConnectionStatement(getPortID());
	}

}

/******************************************************************************************
InputConnection
*******************************************************************************************/
namespace CodeGeneratorNameSpace
{
	InputConnection::InputConnection(string inputStartIndex, string sc, Component* endpoint):Connection(new Input(inputStartIndex, sc), endpoint)
	{
	}

	InputConnection::~InputConnection()
	{}
	
}

/******************************************************************************************
OutputConnection
*******************************************************************************************/
namespace CodeGeneratorNameSpace
{
	OutputConnection::OutputConnection(string inputStartIndex, string sc, Component* endpoint):Connection(new Output(inputStartIndex, sc), endpoint)
	{
	}
	OutputConnection::~OutputConnection()
	{}
}

/******************************************************************************************
GarbledClass
*******************************************************************************************/
namespace CodeGeneratorNameSpace
{
	GarbledClass::GarbledClass(string cn, string as, string in, string out, string component)
		:className(cn), arguments(as), inDegree(in), outDegree(out), componentNum(component)
	{
	}
	GarbledClass::GarbledClass(const GarbledClass& gc)
	{
		this->className = gc.className;
		this->arguments = gc.arguments;
		this->inDegree = gc.inDegree;
		this->outDegree = gc.outDegree;
		this->componentNum = gc.componentNum;
	}
	GarbledClass::GarbledClass()
	{}
	Statement* GarbledClass::getStatement()
	{
		Statement *s;
		string str = "";
		vector<string> para;
		int length = arguments.length();
		for(int i=0; i<=length; i++)
		{
			char tmp = arguments[i];
			if(','==tmp||';'==tmp||'\0'==tmp)
			{
				if(!str.empty())
					para.push_back(str);
				str = "";
			}
			else
				str.push_back(tmp);
		}
		s = new GarbledClassConstructor(className, para, inDegree, outDegree, componentNum);
		return s;
	}

	string GarbledClass::getClassName()
	{
		return this->className;
	}
}

/******************************************************************************************
GarbledClass
*******************************************************************************************/
namespace CodeGeneratorNameSpace
{
	JavaClass::JavaClass(GarbledClass _gc, 
						vector<Initialtor> _init,
						vector<Connection> _inter, 
						vector<InputConnection> _input,
						vector<OutputConnection> _output,
						vector<FixedWire> _fw):gc(_gc), init(_init),inter(_inter), input(_input), 
												output(_output), fw(_fw)
	{};
	void JavaClass::clear()
	{
		gc = GarbledClass();
		init.clear();
		inter.clear();
		input.clear();
		output.clear();
		fw.clear();
	}
	JavaClass::JavaClass()
	{}
	string JavaClass::getFileContent()
	{
		string output = "";
		//file header
		output += getHeader();
		output += "{\n";
		output += getConstructor();
		output += getCreateSubCircuit(1);
		output += getConnectWires(1);
		output += getDefineOutput(1);
		output += getFixedWire(1);
		for(auto it=aliasList.begin(); it!=aliasList.end(); it++)
		{
			vector<string> a = it->second;
			for(int i=0; i<a.size(); i++)
				output += "\t"+a[i];
		}
		aliasList.clear();
		output += "}\n";
		return output;
	}

	string JavaClass::getHeader(int n)
	{
		string indent(n, '\t');
		string output = "";
		output += indent+"package YaoGC;\n";
		output += indent+"public class "+gc.getClassName()+"_Weijie"+" extends CompositeCircuit\n";
		return output;
	}

	string JavaClass::getConstructor(int n)
	{
		Statement *s = gc.getStatement();
		string output = s->toString(n+1);
		delete s;
		return output;
	}

	string JavaClass::getCreateSubCircuit(int n)
	{
		string indent(n, '\t');
		string output = indent+"protected void createSubCircuits() throws Exception \n"+indent+"{\n";
		for(auto it=init.begin(); it!=init.end(); it++)
			output += it->printCode(n+1);

		output += indent+"\tsuper.createSubCircuits();\n";
		output += indent+"}\n";
		
		return output;
	}

	string JavaClass::getConnectWires(int n)
	{
		string indent(n, '\t');
		string output = indent+"protected void connectWires() \n"+indent+"{\n";
		for(auto it=input.begin(); it!=input.end(); it++)
			output += it->printCode(n+1);

		for(auto it=inter.begin(); it!=inter.end(); it++)
			output += it->printCode(n+1);
		output += indent+"}\n";
		return output;
	}

	string JavaClass::getDefineOutput(int n)
	{
		string indent(n, '\t');
		string output = indent+"protected void defineOutputWires() \n"+indent+"{\n";
		for(auto it=this->output.begin(); it!=this->output.end(); it++)
			output += it->printCode(n+1);
		output += indent+"}\n";
		return output;
	}

	string JavaClass::getFixedWire(int n)
	{
		string indent(n, '\t');
		string output = indent+"protected void fixInternalWires() \n"+indent+"{\n";
		for(auto it=this->fw.begin(); it!=this->fw.end(); it++)
			output += it->printCode(n+1);

		output += indent+"}\n";
		return output;
	}


	void JavaClass::insert(Initialtor i)
	{
		this->init.push_back(i);
	}
	void JavaClass::insert(Connection c)
	{
		this->inter.push_back(c);
	}
	void JavaClass::insert(InputConnection ic)
	{
		this->input.push_back(ic);
	}
	void JavaClass::insert(OutputConnection oc)
	{
		this->output.push_back(oc);
	}
	void JavaClass::insert(FixedWire f)
	{
		this->fw.push_back(f);
	}
	void JavaClass::insert(CodeGeneratorNameSpace::GarbledClass gc)
	{
		this->gc = gc;
	}
	JavaClass::JavaClass(GarbledClass _gc):gc(_gc)
	{}
}