#ifndef CIRCUITVISITOR_h
#define CIRCUITVISITOR_h

#include "Utils.h"
#include "BON.h"
#include "GarbledCircuitBonX.h"
#include "JavaClass.h"
#include <queue>
using namespace BON;
using namespace GarbledCircuit_BON;
namespace CircuitVisitor
{
//###############################################################################################################################################
//
// 	C L A S S : CircuitVisitor::CircuitVisitor
//
//###############################################################################################################################################

	class CircuitVisitor 
	{
	public:
		//get all the root folder to get all the garabled cicuit.
		static void visitProject(Project &p);
	
		static std::queue<GarbledCircuit> gcQueue;
		//static JavaClassNameSpace::JavaClass jc; 
		//static std::vector<JavaClassNameSpace::JavaClass> jcs;
	private:
		static void traversalGarbledCircuit(const GarbledCircuit& gc);

	};
}
#endif
