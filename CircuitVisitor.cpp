#include "stdafx.h"
#include "CircuitVisitor.h"
#include <Console.h>
using namespace GMEConsole;

namespace CircuitVisitor
{
	void CircuitVisitor ::visitProject(Project &p)
	{
		BON::Folder folder = p->getRootFolder();
		std::set<BON::Model> models = folder->getChildModels();
		for(auto it=models.begin(); it!=models.end(); it++)
		{
			GarbledCircuit_BON::Library l(*it);
			std::set<GarbledCircuit_BON::GarbledCircuit> gc = l->getGarbledCircuit();
			for(auto i=gc.begin(); i!=gc.end(); i++)
			{
				Console::Out::WriteLine((*i)->getCircuitClassName().c_str());
				traversalGarbledCircuit(*i);
			}
		}
		
	}

	//every time enter in this function, get a gc
	void CircuitVisitor::traversalGarbledCircuit(const GarbledCircuit& gc)
	{
		using namespace std;
		//get the basic information of the current garbled circuit
		string className = gc->getCircuitClassName();
		std::string componentNum = gc->getComponentNumber();
		std::string inDegree = gc->getInDegree();
		std::string outDegree = gc->getOutDegree();
		std::string variable = gc->getVariable();
		//CodeGeneratorNameSpace::GarbledClass ;
		//JavaClassNameSpace::JavaClass jc(CodeGeneratorNameSpace::GarbledClass(className, variable, inDegree, outDegree, componentNum));
		CodeGeneratorNameSpace::GarbledClass garbledClass(className, variable, inDegree, outDegree, componentNum);
		JavaClassNameSpace::JavaClass jc;
//		jc.insert(garbledClass);
		//first get all the garbled gc
		std::set<GarbledCircuit_BON::GarbledCircuit> gcs = gc->getGarbledCircuit();
		//get initialtor
		std::set<InitialtorRef> crs = gc->getInitialtorRef();
		for(auto crsIt=crs.begin(); crsIt!=crs.end(); crsIt++)
		{
			std::string arguments = (*crsIt)->getCircuitArgument();
			std::string indexes = (*crsIt)->getCircuitIndexRange();
			string referedType = (*crsIt)->getReferred()->getObjectMeta().name();
			string className = "";
			if("GarbledCircuit" == referedType)
				className = GarbledCircuit(*crsIt)->getCircuitClassName();
			//Console::Out::WriteLine(output.c_str());
			CodeGeneratorNameSpace::Initialtor init(indexes, arguments, className);
			jc.insert(init);
		}

		//get fixed value?
		std::set<FixWireRef> fwr = gc->getFixWireRef();
		for(auto fwrIt=fwr.begin(); fwrIt!=fwr.end(); fwrIt++)
		{
			std::string indexes = (*fwrIt)->getCircuitIndexRange();
			std::string port = (*fwrIt)->getPortIndex();
			std::string portStart = (*fwrIt)->getPortStartIndex();
			FixWireRefImpl::FixedValue_Type value = (*fwrIt)->getFixedValue();
			string fixvalue = "0";
			if(value == FixWireRefImpl::FixedValue_Type::_1_FixedValue_Type)
				fixvalue = "1";
			CodeGeneratorNameSpace::FixedWire fw(indexes, portStart, port, fixvalue);
			jc.insert(fw);
		}
		//generator?
		std::set<GeneratorToCircuit> gtc = gc->getGeneratorToCircuit();
		for(auto gtcIt=gtc.begin(); gtcIt!=gtc.end(); gtcIt++)
		{
			std::string srcPort = (*gtcIt)->getSourcePortIndex();
			std::string destPort = (*gtcIt)->getDestinationPortIndex();
			CodeGenerator cd = (*gtcIt)->getSrc();
			ConnectionCircuitRef ccr = (*gtcIt)->getDst();
			
			std::string inputname = cd->getObjectMeta().name();
			if("Input" == inputname)
			{
				CodeGeneratorNameSpace::InputConnection ic(((Input)cd)->getPortStartIndex(), srcPort, ccr->getComponent(destPort));
				jc.insert(ic);
			}
			//output
			else
			{
				CodeGeneratorNameSpace::OutputConnection ic(((Output)cd)->getPortStartIndex(), srcPort, ccr->getComponent(destPort));
				jc.insert(ic);
			}
		}
		//internal?
		std::set<InternalWire> iw = gc->getInternalWire();
		for(auto iwIt=iw.begin(); iwIt!=iw.end(); iwIt++)
		{
			std::string srcPort = (*iwIt)->getSourcePortIndex();
			std::string destPort = (*iwIt)->getDestinationPortIndex();
			ConnectionCircuitRef srcCCR = (*iwIt)->getSrc();
			ConnectionCircuitRef destCCR = (*iwIt)->getDst();
			CodeGeneratorNameSpace::Connection conn(srcCCR->getComponent(srcPort), destCCR->getComponent(destPort));
			jc.insert(conn);
		}

		//jcs.push_back(jc);
	}
}