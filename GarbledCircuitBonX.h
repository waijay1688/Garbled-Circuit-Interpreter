#ifndef GARBLEDCIRCUITBONX_H
#define GARBLEDCIRCUITBONX_H

#include "BON.h"
#include "BONImpl.h"
#include "CodeGenerator.h"
#include "Extensions.h"

///BUP
// add your include files/class definitions here
///EUP

namespace GarbledCircuit_BON {             DECLARE_BONEXTENSION( BON::Model, GarbledCircuitImpl, GarbledCircuit ); }
namespace GarbledCircuit_BON {             DECLARE_BONEXTENSION( BON::Model, LibraryImpl, Library ); }
namespace GarbledCircuit_BON {             DECLARE_ABSTRACT_BONEXTENSION( BON::FCO, CircuitImpl, Circuit ); }
namespace GarbledCircuit_BON {             DECLARE_ABSTRACT_BONEXTENSION( BON::FCO, SplitPortImpl, SplitPort ); }
namespace GarbledCircuit_BON {             DECLARE_ABSTRACT_BONEXTENSION( BON::Atom, InOutPutImpl, InOutPut ); }
namespace GarbledCircuit_BON {             DECLARE_ABSTRACT_BONEXTENSION( BON::Reference, CircuitlRefImpl, CircuitlRef ); }
namespace GarbledCircuit_BON {             DECLARE_BONEXTENSION2( SplitPort, InOutPut, InputImpl, Input ); }
namespace GarbledCircuit_BON {             DECLARE_BONEXTENSION2( SplitPort, InOutPut, OutputImpl, Output ); }
namespace GarbledCircuit_BON {             DECLARE_ABSTRACT_BONEXTENSION( CircuitlRef, ConnectionRefImpl, ConnectionRef ); }
namespace GarbledCircuit_BON {             DECLARE_BONEXTENSION2( SplitPort, CircuitlRef, FixedWireRefImpl, FixedWireRef ); }
namespace GarbledCircuit_BON {             DECLARE_BONEXTENSION( CircuitlRef, InitialtorRefImpl, InitialtorRef ); }
namespace GarbledCircuit_BON {             DECLARE_BONEXTENSION( ConnectionRef, ReplicateRefImpl, ReplicateRef ); }
namespace GarbledCircuit_BON {             DECLARE_BONEXTENSION2( SplitPort, ConnectionRef, SingleRefImpl, SingleRef ); }
namespace GarbledCircuit_BON {             DECLARE_ABSTRACT_BONEXTENSION( BON::Atom, LogicalGateImpl, LogicalGate ); }
namespace GarbledCircuit_BON {             DECLARE_BONEXTENSION( LogicalGate, ANDImpl, AND ); }
namespace GarbledCircuit_BON {             DECLARE_BONEXTENSION( LogicalGate, ORImpl, OR ); }
namespace GarbledCircuit_BON {             DECLARE_BONEXTENSION( LogicalGate, XORImpl, XOR ); }
namespace GarbledCircuit_BON {             DECLARE_ABSTRACT_BONEXTENSION( BON::Connection, WireImpl, Wire ); }
namespace GarbledCircuit_BON {             DECLARE_BONEXTENSION( Wire, DefineInOutPutImpl, DefineInOutPut ); }
namespace GarbledCircuit_BON {             DECLARE_BONEXTENSION( Wire, InternalWireImpl, InternalWire ); }


namespace GarbledCircuit_BON
{
//*******************************************************************
//   C  L  A  S  S   GarbledCircuitImpl
//*******************************************************************
class GarbledCircuitImpl :
	  virtual public BON::ModelImpl
{
public:
	virtual void        accept( BON::Visitor *pVisitor);

	//
	// attribute getters and setters
	virtual std::string getCircuitClassName() ;
	virtual std::string getComponentNumber() ;
	virtual std::string getDescription() ;
	virtual std::string getInDegree() ;
	virtual std::string getOutDegree() ;
	virtual std::string getVariable() ;
	virtual bool        isClassAlreadyDefined() ;
	virtual void        setCircuitClassName( const std::string& val);
	virtual void        setClassAlreadyDefined( bool val);
	virtual void        setComponentNumber( const std::string& val);
	virtual void        setDescription( const std::string& val);
	virtual void        setInDegree( const std::string& val);
	virtual void        setOutDegree( const std::string& val);
	virtual void        setVariable( const std::string& val);
	//
	// kind and role getters
	virtual std::set<GarbledCircuit_BON::AND>         getAND();
	virtual std::set<GarbledCircuit_BON::CircuitlRef> getCircuitlRef();
	virtual std::set<GarbledCircuit_BON::DefineInOutPut> getDefineInOutPut();
	virtual std::set<GarbledCircuit_BON::FixedWireRef> getFixedWireRef();
	virtual std::set<GarbledCircuit_BON::GarbledCircuit> getGarbledCircuit();
	virtual std::set<GarbledCircuit_BON::InOutPut>    getInOutPut();
	virtual std::set<GarbledCircuit_BON::InitialtorRef> getInitialtorRef();
	virtual std::set<GarbledCircuit_BON::Input>       getInput();
	virtual std::set<GarbledCircuit_BON::InternalWire> getInternalWire();
	virtual std::set<GarbledCircuit_BON::LogicalGate> getLogicalGate();
	virtual std::set<GarbledCircuit_BON::OR>          getOR();
	virtual std::set<GarbledCircuit_BON::Output>      getOutput();
	virtual std::set<GarbledCircuit_BON::ReplicateRef> getReplicateRef();
	virtual std::set<GarbledCircuit_BON::SingleRef>   getSingleRef();
	virtual std::set<GarbledCircuit_BON::Wire>        getWire();
	virtual std::set<GarbledCircuit_BON::XOR>         getXOR();

	///BUP
	// add your own members here
	///EUP
}; // class
}  // namespace


namespace GarbledCircuit_BON
{
//*******************************************************************
//   C  L  A  S  S   LibraryImpl
//*******************************************************************
class LibraryImpl :
	  virtual public BON::ModelImpl
{
public:
	virtual void        accept( BON::Visitor *pVisitor);

	//
	// kind and role getters
	virtual std::set<GarbledCircuit_BON::GarbledCircuit> getGarbledCircuit();

	///BUP
	// add your own members here
	///EUP
}; // class
}  // namespace


namespace GarbledCircuit_BON
{
//*******************************************************************
//   C  L  A  S  S   CircuitImpl
//*******************************************************************
class CircuitImpl :
	  virtual public BON::FCOImpl
{
public:


	///BUP
	// add your own members here
	///EUP
}; // class
}  // namespace


namespace GarbledCircuit_BON
{
//*******************************************************************
//   C  L  A  S  S   SplitPortImpl
//*******************************************************************
class SplitPortImpl :
	  virtual public BON::FCOImpl
{
public:

	//
	// attribute getters and setters
	virtual std::string getPortStartIndex() ;
	virtual void        setPortStartIndex( const std::string& val);

	///BUP
	// add your own members here
	///EUP
}; // class
}  // namespace


namespace GarbledCircuit_BON
{
//*******************************************************************
//   C  L  A  S  S   InOutPutImpl
//*******************************************************************
class InOutPutImpl :
	  virtual public BON::AtomImpl
{
public:
	virtual void        accept( BON::Visitor *pVisitor);

	//
	// connectionEnd getters
	virtual std::multiset<GarbledCircuit_BON::ConnectionRef> getDefineInOutPutDsts();
	virtual std::set<GarbledCircuit_BON::DefineInOutPut> getOutDefineInOutPutLinks();

	///BUP
	// add your own members here
	///EUP
}; // class
}  // namespace


namespace GarbledCircuit_BON
{
//*******************************************************************
//   C  L  A  S  S   CircuitlRefImpl
//*******************************************************************
class CircuitlRefImpl :
	  virtual public BON::ReferenceImpl
{
public:
	virtual void        accept( BON::Visitor *pVisitor);

	//
	// attribute getters and setters
	virtual std::string getCircuitIndexAlias() ;
	virtual std::string getCircuitIndexRange() ;
	virtual void        setCircuitIndexAlias( const std::string& val);
	virtual void        setCircuitIndexRange( const std::string& val);
	//
	// ref getters
	virtual BON::FCO    getReferred();

	///BUP
	// add your own members here
	///EUP
}; // class
}  // namespace


namespace GarbledCircuit_BON
{
//*******************************************************************
//   C  L  A  S  S   InputImpl
//*******************************************************************
class InputImpl :
	  public SplitPortImpl
	, public InOutPutImpl
{
public:
	virtual void        accept( BON::Visitor *pVisitor);


	///BUP
	// add your own members here
	///EUP
}; // class
}  // namespace


namespace GarbledCircuit_BON
{
//*******************************************************************
//   C  L  A  S  S   OutputImpl
//*******************************************************************
class OutputImpl :
	  public SplitPortImpl
	, public InOutPutImpl
{
public:
	virtual void        accept( BON::Visitor *pVisitor);


	///BUP
	// add your own members here
	///EUP
}; // class
}  // namespace


namespace GarbledCircuit_BON
{
//*******************************************************************
//   C  L  A  S  S   ConnectionRefImpl
//*******************************************************************
class ConnectionRefImpl :
	  public CircuitlRefImpl
{
public:
	virtual void        accept( BON::Visitor *pVisitor);

	//
	// connectionEnd getters
	virtual std::multiset<GarbledCircuit_BON::InOutPut> getDefineInOutPutSrcs();
	virtual std::set<GarbledCircuit_BON::DefineInOutPut> getInDefineInOutPutLinks();
	virtual std::set<GarbledCircuit_BON::InternalWire> getInInternalWireLinks();
	virtual std::multiset<GarbledCircuit_BON::ConnectionRef> getInternalWireDsts();
	virtual std::set<GarbledCircuit_BON::InternalWire> getInternalWireLinks();
	virtual std::multiset<GarbledCircuit_BON::ConnectionRef> getInternalWireSrcs();
	virtual std::set<GarbledCircuit_BON::InternalWire> getOutInternalWireLinks();

	///BUP
	// add your own members here
	virtual CodeGeneratorNameSpace::Component * getComponent(string port) = 0;
	///EUP
}; // class
}  // namespace


namespace GarbledCircuit_BON
{
//*******************************************************************
//   C  L  A  S  S   FixedWireRefImpl
//*******************************************************************
class FixedWireRefImpl :
	  public SplitPortImpl
	, public CircuitlRefImpl
{
public:
	virtual void        accept( BON::Visitor *pVisitor);
	typedef enum
	{
		_0_FixedValue_Type,
		_1_FixedValue_Type
	} FixedValue_Type;

	//
	// attribute getters and setters
	virtual std::string getDescription() ;
	virtual GarbledCircuit_BON::FixedWireRefImpl::FixedValue_Type getFixedValue();
	virtual std::string getPortIndex() ;
	virtual void        setDescription( const std::string& val);
	virtual void        setFixedValue( FixedWireRefImpl::FixedValue_Type val);
	virtual void        setPortIndex( const std::string& val);

	///BUP
	// add your own members here
	///EUP
}; // class
}  // namespace


namespace GarbledCircuit_BON
{
//*******************************************************************
//   C  L  A  S  S   InitialtorRefImpl
//*******************************************************************
class InitialtorRefImpl :
	  public CircuitlRefImpl
{
public:
	virtual void        accept( BON::Visitor *pVisitor);

	//
	// attribute getters and setters
	virtual std::string getCircuitArgument() ;
	virtual std::string getDescription() ;
	virtual void        setCircuitArgument( const std::string& val);
	virtual void        setDescription( const std::string& val);

	///BUP
	// add your own members here
	///EUP
}; // class
}  // namespace


namespace GarbledCircuit_BON
{
//*******************************************************************
//   C  L  A  S  S   ReplicateRefImpl
//*******************************************************************
class ReplicateRefImpl :
	  public ConnectionRefImpl
{
public:
	virtual void        accept( BON::Visitor *pVisitor);


	///BUP
	// add your own members here
	virtual CodeGeneratorNameSpace::Component * getComponent(string port);
	///EUP
}; // class
}  // namespace


namespace GarbledCircuit_BON
{
//*******************************************************************
//   C  L  A  S  S   SingleRefImpl
//*******************************************************************
class SingleRefImpl :
	  public SplitPortImpl
	, public ConnectionRefImpl
{
public:
	virtual void        accept( BON::Visitor *pVisitor);


	///BUP
	// add your own members here
	virtual CodeGeneratorNameSpace::Component * getComponent(string port);
	///EUP
}; // class
}  // namespace


namespace GarbledCircuit_BON
{
//*******************************************************************
//   C  L  A  S  S   LogicalGateImpl
//*******************************************************************
class LogicalGateImpl :
	  virtual public BON::AtomImpl
{
public:
	virtual void        accept( BON::Visitor *pVisitor);

	//
	// attribute getters and setters
	virtual long        getMultiplicity() ;
	virtual void        setMultiplicity( const long val);

	///BUP
	// add your own members here
	///EUP
}; // class
}  // namespace


namespace GarbledCircuit_BON
{
//*******************************************************************
//   C  L  A  S  S   ANDImpl
//*******************************************************************
class ANDImpl :
	  public LogicalGateImpl
{
public:
	virtual void        accept( BON::Visitor *pVisitor);


	///BUP
	// add your own members here
	///EUP
}; // class
}  // namespace


namespace GarbledCircuit_BON
{
//*******************************************************************
//   C  L  A  S  S   ORImpl
//*******************************************************************
class ORImpl :
	  public LogicalGateImpl
{
public:
	virtual void        accept( BON::Visitor *pVisitor);


	///BUP
	// add your own members here
	///EUP
}; // class
}  // namespace


namespace GarbledCircuit_BON
{
//*******************************************************************
//   C  L  A  S  S   XORImpl
//*******************************************************************
class XORImpl :
	  public LogicalGateImpl
{
public:
	virtual void        accept( BON::Visitor *pVisitor);


	///BUP
	// add your own members here
	///EUP
}; // class
}  // namespace


namespace GarbledCircuit_BON
{
//*******************************************************************
//   C  L  A  S  S   WireImpl
//*******************************************************************
class WireImpl :
	  virtual public BON::ConnectionImpl
{
public:
	virtual void        accept( BON::Visitor *pVisitor);

	//
	// attribute getters and setters
	virtual std::string getDescription() ;
	virtual std::string getDestinationPortIndex() ;
	virtual std::string getSourcePortIndex() ;
	virtual void        setDescription( const std::string& val);
	virtual void        setDestinationPortIndex( const std::string& val);
	virtual void        setSourcePortIndex( const std::string& val);

	///BUP
	// add your own members here
	///EUP
}; // class
}  // namespace


namespace GarbledCircuit_BON
{
//*******************************************************************
//   C  L  A  S  S   DefineInOutPutImpl
//*******************************************************************
class DefineInOutPutImpl :
	  public WireImpl
{
public:
	virtual void        accept( BON::Visitor *pVisitor);

	//
	// connectionEnd getters
	virtual GarbledCircuit_BON::ConnectionRef         getDst();
	virtual GarbledCircuit_BON::InOutPut    getSrc();

	///BUP
	// add your own members here
	///EUP
}; // class
}  // namespace


namespace GarbledCircuit_BON
{
//*******************************************************************
//   C  L  A  S  S   InternalWireImpl
//*******************************************************************
class InternalWireImpl :
	  public WireImpl
{
public:
	virtual void        accept( BON::Visitor *pVisitor);

	//
	// connectionEnd getters
	virtual GarbledCircuit_BON::ConnectionRef         getDst();
	virtual GarbledCircuit_BON::ConnectionRef         getSrc();

	///BUP
	// add your own members here
	///EUP
}; // class
}  // namespace


///BUP
// add your additional class definitions here
///EUP

#endif // GARBLEDCIRCUITBONX_H
