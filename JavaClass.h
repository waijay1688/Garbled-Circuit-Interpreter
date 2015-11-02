#ifndef JAVACLASS_H_
#define JAVACLASS_H_
#include <string>
#include<vector>
#include "CodeGenerator.h"
using namespace std;
//using namespace CodeGeneratorNameSpace;
/*************************************************************************************
JavaClass
**************************************************************************************/
namespace JavaClassNameSpace
{
	class JavaClass
	{
	private:
		CodeGeneratorNameSpace::GarbledClass gc;
		vector<CodeGeneratorNameSpace::Initialtor> init;
		vector<CodeGeneratorNameSpace::Connection> inter;
		vector<CodeGeneratorNameSpace::InputConnection> input;
		vector<CodeGeneratorNameSpace::OutputConnection> output;
		vector<CodeGeneratorNameSpace::FixedWire> fw;
	public:
		JavaClass();
		JavaClass(CodeGeneratorNameSpace::GarbledClass _gc, 
						vector<CodeGeneratorNameSpace::Initialtor> _init,
						vector<CodeGeneratorNameSpace::Connection> _inter, 
						vector<CodeGeneratorNameSpace::InputConnection> _input,
						vector<CodeGeneratorNameSpace::OutputConnection> _output,
						vector<CodeGeneratorNameSpace::FixedWire> _fw);
		JavaClass(CodeGeneratorNameSpace::GarbledClass _gc);
		string getFileContent();
		void insert(CodeGeneratorNameSpace::Initialtor i);
		void insert(CodeGeneratorNameSpace::Connection c);
		void insert(CodeGeneratorNameSpace::InputConnection ic);
		void insert(CodeGeneratorNameSpace::OutputConnection);
		void insert(CodeGeneratorNameSpace::FixedWire f);
		void insert(CodeGeneratorNameSpace::GarbledClass gc);
	private:
		string getHeader(int n = 0);
		string getConstructor(int n = 0);
		string getCreateSubCircuit(int n = 0);
		string getConnectWires(int n = 0);
		string getDefineOutput(int n = 0);
		string getFixedWire(int n = 0);

	};
}

#endif