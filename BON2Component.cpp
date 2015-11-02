//###############################################################################################################################################
//
//	Meta and Builder Object Network V2.0 for GME
//	BON2Component.cpp
//
//###############################################################################################################################################

/*
	Copyright (c) Vanderbilt University, 2000-2004
	ALL RIGHTS RESERVED

	Vanderbilt University disclaims all warranties with regard to this
	software, including all implied warranties of merchantability
	and fitness.  In no event shall Vanderbilt University be liable for
	any special, indirect or consequential damages or any damages
	whatsoever resulting from loss of use, data or profits, whether
	in an action of contract, negligence or other tortious action,
	arising out of or in connection with the use or performance of
	this software.
*/

#include "stdafx.h"
#include <Console.h>
#include "BON2Component.h"
#include "CodeGenerator.h"
#include "GarbledCircuitBonX.h"
#include <fstream>
//#include "CircuitVisitor.h"
namespace BON
{

//###############################################################################################################################################
//
// 	C L A S S : BON::Component
//
//###############################################################################################################################################

Component::Component()
	: m_bIsInteractive( false )
{
}

Component::~Component()
{
	if ( m_project ) {
		m_project->finalizeObjects();
		finalize( m_project );
		m_project = NULL;
	}
}

// ====================================================
// This method is called after all the generic initialization is done
// This should be empty unless application-specific initialization is needed

void Component::initialize( Project& project )
{
	// ======================
	// Insert application specific code here
#ifdef GME_ADDON
	project->setAutoCommit( false);
#endif
}

// ====================================================
// This method is called before the whole BON2 project released and disposed
// This should be empty unless application-specific finalization is needed

void Component::finalize( Project& project )
{
	// ======================
	// Insert application specific code here
}

// ====================================================
// This is the obsolete component interface
// This present implementation either tries to call InvokeEx, or does nothing except of a notification

void Component::invoke( Project& project, const std::set<FCO>& setModels, long lParam )
{
	#ifdef SUPPORT_OLD_INVOKE
		Object focus;
		invokeEx( project, focus, setModels, lParam );
	#else
		if ( m_bIsInteractive )
			AfxMessageBox(_T("This BON2 Component does not support the obsolete invoke mechanism!"));
	#endif
}

// ====================================================
// This is the main component method for Interpereters and Plugins.
// May also be used in case of invokeable Add-Ons

void Component::invokeEx( Project& project, FCO& currentFCO, const std::set<FCO>& setSelectedFCOs, long lParam )
{
#ifdef GME_ADDON
	project->setAutoCommit( false);
#endif
	using namespace GMEConsole;
	//using namespace CircuitVisitor;
	Console::Out::WriteLine("Interpreter started...");
	// ======================
	// TODO: Insert application specific code here
	/*
	if (!currentFCO && setSelectedFCOs.empty())
      {
        AfxMessageBox ("Interpretation must start from a TopLevelPackage, "
                       "or an ImplementationArtifact, or a "
                       "ComponentInterface, or a ComponentPackage, "
                       "ComponentImplementation !");
        return;
      }
	  */
	

    traversalProject(project);
	Console::Out::WriteLine("Interpreter completed...");
}

// ====================================================
// GME currently does not use this function
// You only need to implement it if other invokation mechanisms are used

void Component::objectInvokeEx( Project& project, Object& currentObject, const std::set<Object>& setSelectedObjects, long lParam )
	{
		if ( m_bIsInteractive )
			AfxMessageBox(_T("This BON2 Component does not support objectInvokeEx method!"));
	}

// ====================================================
// Implement application specific parameter-mechanism in these functions

Util::Variant Component::getParameter( const std::string& strName )
{
	// ======================
	// Insert application specific code here

	return Util::Variant();
}

void Component::setParameter( const std::string& strName, const Util::Variant& varValue )
{
	// ======================
	// Insert application specific code here
}

void Component::traversalProject(Project& p)
{
	BON::Folder folder = p->getRootFolder();
		std::set<BON::Model> models = folder->getChildModels();
		for(auto it=models.begin(); it!=models.end(); it++)
		{
			GarbledCircuit_BON::Library l(*it);
			std::set<GarbledCircuit_BON::GarbledCircuit> gc = l->getGarbledCircuit();
			for(auto i=gc.begin(); i!=gc.end(); i++)
			{
				traversalGarbledCircuit(*i);
			}
		}
}

void Component::traversalGarbledCircuit(const GarbledCircuit_BON::GarbledCircuit& gc)
{
	
		
		//first get all the garbled gc
		std::set<GarbledCircuit_BON::GarbledCircuit> gcs = gc->getGarbledCircuit();
		for(auto it=gcs.begin(); it!=gcs.end(); it++)
		{
			if(!(*it)->isClassAlreadyDefined())
				traversalGarbledCircuit(*it);
		}
		setBasicInfo(gc);
		setInit(gc);
		setFixedValue(gc);
		setInputOutput(gc);
		setConnection(gc);

		string folderName = "codes\\";
		std::string outputFile = currentJC.getFileContent();
		ofstream outf(folderName+gc->getCircuitClassName()+"_Weijie"+".java");
		outf<<outputFile;
}


void Component::setBasicInfo(const GarbledCircuit_BON::GarbledCircuit& gc)
{
		//get the basic information of the current garbled circuit
		string className = gc->getCircuitClassName();
		std::string componentNum = gc->getComponentNumber();
		std::string inDegree = gc->getInDegree();
		std::string outDegree =gc->getOutDegree();
		std::string variable = gc->getVariable();
		//CodeGeneratorNameSpace::GarbledClass ;
		//JavaClassNameSpace::JavaClass jc(CodeGeneratorNameSpace::GarbledClass(className, variable, inDegree, outDegree, componentNum));
		CodeGeneratorNameSpace::GarbledClass garbledClass(className, variable, inDegree, outDegree, componentNum);
		currentJC.clear();
		currentJC.insert(garbledClass);
}

void Component::setInit(const GarbledCircuit_BON::GarbledCircuit& gc)
{
	//get initialtor
		std::set<InitialtorRef> crs = gc->getInitialtorRef();
		for(auto crsIt=crs.begin(); crsIt!=crs.end(); crsIt++)
		{
			std::string arguments = (*crsIt)->getCircuitArgument();
			std::string indexes = (*crsIt)->getCircuitIndexRange();
			string referedType = (*crsIt)->getReferred()->getObjectMeta().name();
			string className = "";
			if("GarbledCircuit" == referedType)
				className = GarbledCircuit((*crsIt)->getReferred())->getCircuitClassName();
			else
				className = referedType;
			//Console::Out::WriteLine(output.c_str());
			CodeGeneratorNameSpace::Initialtor init(indexes, arguments, className);
			init.setDescription((*crsIt)->getDescription());
			init.setIndexAlias((*crsIt)->getCircuitIndexAlias());
			currentJC.insert(init);
		}
}

void Component::setFixedValue(const GarbledCircuit_BON::GarbledCircuit& gc)
{
	//get fixed value?
		std::set<FixedWireRef> fwr = gc->getFixedWireRef();
		for(auto fwrIt=fwr.begin(); fwrIt!=fwr.end(); fwrIt++)
		{
			std::string indexes = (*fwrIt)->getCircuitIndexRange();
			std::string port = (*fwrIt)->getPortIndex();
			std::string portStart = (*fwrIt)->getPortStartIndex();
			FixedWireRefImpl::FixedValue_Type value = (*fwrIt)->getFixedValue();
			string fixvalue = "0";
			if(value == FixedWireRefImpl::FixedValue_Type::_1_FixedValue_Type)
				fixvalue = "1";
			CodeGeneratorNameSpace::FixedWire fw(indexes, portStart, port, fixvalue);
			fw.setDescription((*fwrIt)->getDescription());
			currentJC.insert(fw);
		}

}

void Component::setInputOutput(const GarbledCircuit_BON::GarbledCircuit& gc)
{
	//generator?
		std::set<DefineInOutPut> gtc = gc->getDefineInOutPut();
		for(auto gtcIt=gtc.begin(); gtcIt!=gtc.end(); gtcIt++)
		{
			std::string srcPort = (*gtcIt)->getSourcePortIndex();
			std::string destPort = (*gtcIt)->getDestinationPortIndex();
			GarbledCircuit_BON::InOutPut cd = (*gtcIt)->getSrc();
			ConnectionRef ccr = (*gtcIt)->getDst();
			
			std::string inputname = cd->getObjectMeta().name();
			if("Input" == inputname)
			{
				CodeGeneratorNameSpace::InputConnection ic(((GarbledCircuit_BON::Input)cd)->getPortStartIndex(), srcPort, ccr->getComponent(destPort));
				ic.setDescription((*gtcIt)->getDescription());
				currentJC.insert(ic);
			}
			//output
			else
			{
				CodeGeneratorNameSpace::OutputConnection ic(((GarbledCircuit_BON::Output)cd)->getPortStartIndex(), srcPort, ccr->getComponent(destPort));
				ic.setDescription((*gtcIt)->getDescription());
				currentJC.insert(ic);
			}
		}
}

void Component::setConnection(const GarbledCircuit_BON::GarbledCircuit& gc)
{
	//internal?
		std::set<InternalWire> iw = gc->getInternalWire();
		for(auto iwIt=iw.begin(); iwIt!=iw.end(); iwIt++)
		{
			std::string srcPort = (*iwIt)->getSourcePortIndex();
			std::string destPort = (*iwIt)->getDestinationPortIndex();
			ConnectionRef srcCCR = (*iwIt)->getSrc();
			ConnectionRef destCCR = (*iwIt)->getDst();
			CodeGeneratorNameSpace::Connection conn(srcCCR->getComponent(srcPort), destCCR->getComponent(destPort));
			conn.setDescription((*iwIt)->getDescription());
			currentJC.insert(conn);
		}
}
#ifdef GME_ADDON

// ====================================================
// If the component is an Add-On, then this method is called for every Global Event

void Component::globalEventPerformed( globalevent_enum event )
{
	// ======================
	// Insert application specific code here
}

// ====================================================
// If the component is an Add-On, then this method is called for every Object Event

void Component::objectEventPerformed( Object& object, unsigned long event, VARIANT v )
{
	// ======================
	// Insert application specific code here
}

#endif // GME_ADDON

}; // namespace BON

