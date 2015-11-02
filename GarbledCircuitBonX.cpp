#include "stdafx.h"
#include "GarbledCircuitBonX.h"


namespace BON
{

IMPLEMENT_BONEXTENSION( GarbledCircuit_BON::GarbledCircuit, "GarbledCircuit" );
IMPLEMENT_BONEXTENSION( GarbledCircuit_BON::Library, "Library" );
IMPLEMENT_ABSTRACT_BONEXTENSION( GarbledCircuit_BON::Circuit );
IMPLEMENT_ABSTRACT_BONEXTENSION( GarbledCircuit_BON::SplitPort );
IMPLEMENT_ABSTRACT_BONEXTENSION( GarbledCircuit_BON::InOutPut );
IMPLEMENT_ABSTRACT_BONEXTENSION( GarbledCircuit_BON::CircuitlRef );
IMPLEMENT_BONEXTENSION( GarbledCircuit_BON::Input, "Input" );
IMPLEMENT_BONEXTENSION( GarbledCircuit_BON::Output, "Output" );
IMPLEMENT_ABSTRACT_BONEXTENSION( GarbledCircuit_BON::ConnectionRef );
IMPLEMENT_BONEXTENSION( GarbledCircuit_BON::FixedWireRef, "FixedWireRef" );
IMPLEMENT_BONEXTENSION( GarbledCircuit_BON::InitialtorRef, "InitialtorRef" );
IMPLEMENT_BONEXTENSION( GarbledCircuit_BON::ReplicateRef, "ReplicateRef" );
IMPLEMENT_BONEXTENSION( GarbledCircuit_BON::SingleRef, "SingleRef" );
IMPLEMENT_ABSTRACT_BONEXTENSION( GarbledCircuit_BON::LogicalGate );
IMPLEMENT_BONEXTENSION( GarbledCircuit_BON::AND, "AND" );
IMPLEMENT_BONEXTENSION( GarbledCircuit_BON::OR, "OR" );
IMPLEMENT_BONEXTENSION( GarbledCircuit_BON::XOR, "XOR" );
IMPLEMENT_ABSTRACT_BONEXTENSION( GarbledCircuit_BON::Wire );
IMPLEMENT_BONEXTENSION( GarbledCircuit_BON::DefineInOutPut, "DefineInOutPut" );
IMPLEMENT_BONEXTENSION( GarbledCircuit_BON::InternalWire, "InternalWire" );


} // namespace BON

//********************************************************************************
// 
//********************************************************************************
void GarbledCircuit_BON::GarbledCircuitImpl::accept( BON::Visitor *pVisitor)
{
	// visit the Model
	pVisitor->visitModel( BON::Model( this));

}


//********************************************************************************
// 
//********************************************************************************
std::string GarbledCircuit_BON::GarbledCircuitImpl::getCircuitClassName() 
{
	return FCOImpl::getAttribute("CircuitClassName")->getStringValue();
}


//********************************************************************************
// 
//********************************************************************************
std::string GarbledCircuit_BON::GarbledCircuitImpl::getComponentNumber() 
{
	return FCOImpl::getAttribute("ComponentNumber")->getStringValue();
}


//********************************************************************************
// 
//********************************************************************************
std::string GarbledCircuit_BON::GarbledCircuitImpl::getDescription() 
{
	return FCOImpl::getAttribute("Description")->getStringValue();
}


//********************************************************************************
// 
//********************************************************************************
std::string GarbledCircuit_BON::GarbledCircuitImpl::getInDegree() 
{
	return FCOImpl::getAttribute("InDegree")->getStringValue();
}


//********************************************************************************
// 
//********************************************************************************
std::string GarbledCircuit_BON::GarbledCircuitImpl::getOutDegree() 
{
	return FCOImpl::getAttribute("OutDegree")->getStringValue();
}


//********************************************************************************
// 
//********************************************************************************
std::string GarbledCircuit_BON::GarbledCircuitImpl::getVariable() 
{
	return FCOImpl::getAttribute("Variable")->getStringValue();
}


//********************************************************************************
// 
//********************************************************************************
bool GarbledCircuit_BON::GarbledCircuitImpl::isClassAlreadyDefined() 
{
	return FCOImpl::getAttribute("ClassAlreadyDefined")->getBooleanValue();
}


//********************************************************************************
// 
//********************************************************************************
void GarbledCircuit_BON::GarbledCircuitImpl::setCircuitClassName( const std::string& val)
{
	FCOImpl::getAttribute("CircuitClassName")->setStringValue( val);
}


//********************************************************************************
// 
//********************************************************************************
void GarbledCircuit_BON::GarbledCircuitImpl::setClassAlreadyDefined( bool val)
{
	FCOImpl::getAttribute("ClassAlreadyDefined")->setBooleanValue( val);
}


//********************************************************************************
// 
//********************************************************************************
void GarbledCircuit_BON::GarbledCircuitImpl::setComponentNumber( const std::string& val)
{
	FCOImpl::getAttribute("ComponentNumber")->setStringValue( val);
}


//********************************************************************************
// 
//********************************************************************************
void GarbledCircuit_BON::GarbledCircuitImpl::setDescription( const std::string& val)
{
	FCOImpl::getAttribute("Description")->setStringValue( val);
}


//********************************************************************************
// 
//********************************************************************************
void GarbledCircuit_BON::GarbledCircuitImpl::setInDegree( const std::string& val)
{
	FCOImpl::getAttribute("InDegree")->setStringValue( val);
}


//********************************************************************************
// 
//********************************************************************************
void GarbledCircuit_BON::GarbledCircuitImpl::setOutDegree( const std::string& val)
{
	FCOImpl::getAttribute("OutDegree")->setStringValue( val);
}


//********************************************************************************
// 
//********************************************************************************
void GarbledCircuit_BON::GarbledCircuitImpl::setVariable( const std::string& val)
{
	FCOImpl::getAttribute("Variable")->setStringValue( val);
}


//********************************************************************************
// getter for role "AND" among "LogicalGate"s and its descendants
//********************************************************************************
std::set<GarbledCircuit_BON::AND> GarbledCircuit_BON::GarbledCircuitImpl::getAND()
{
	std::set<GarbledCircuit_BON::AND> res;
	std::set<BON::FCO> roles = ModelImpl::getChildFCOsAs("AND");
	for( std::set<BON::FCO>::iterator i = roles.begin(); i != roles.end(); ++i)
	{
		GarbledCircuit_BON::AND elem(*i);
		ASSERT(elem);
		res.insert(elem);
	}
	return res;
}


//********************************************************************************
// aggregated getter for role "GarbledCircuit_BON::" among "GarbledCircuit_BON::CircuitlRef"s and its descendants
//********************************************************************************
std::set<GarbledCircuit_BON::CircuitlRef> GarbledCircuit_BON::GarbledCircuitImpl::getCircuitlRef()
{
	std::set<GarbledCircuit_BON::CircuitlRef> res;
	const int len = 4;
	std::set<BON::FCO> roles_vec[ len];
	roles_vec[0] = ModelImpl::getChildFCOsAs("FixedWireRef");
	roles_vec[1] = ModelImpl::getChildFCOsAs("InitialtorRef");
	roles_vec[2] = ModelImpl::getChildFCOsAs("ReplicateRef");
	roles_vec[3] = ModelImpl::getChildFCOsAs("SingleRef");
	for( int k = 0; k < len; ++k)
		for( std::set<BON::FCO>::iterator i = roles_vec[k].begin(); i != roles_vec[k].end(); ++i)
		{
			GarbledCircuit_BON::CircuitlRef elem(*i);
			ASSERT(elem);
			res.insert(elem);
		}
	return res;
}


//********************************************************************************
// getter for role "DefineInOutPut" among "Wire"s and its descendants
//********************************************************************************
std::set<GarbledCircuit_BON::DefineInOutPut> GarbledCircuit_BON::GarbledCircuitImpl::getDefineInOutPut()
{
	std::set<GarbledCircuit_BON::DefineInOutPut> res;
	std::set<BON::FCO> roles = ModelImpl::getChildFCOsAs("DefineInOutPut");
	for( std::set<BON::FCO>::iterator i = roles.begin(); i != roles.end(); ++i)
	{
		GarbledCircuit_BON::DefineInOutPut elem(*i);
		ASSERT(elem);
		res.insert(elem);
	}
	return res;
}


//********************************************************************************
// getter for role "FixedWireRef" among "CircuitlRef"s and its descendants
//********************************************************************************
std::set<GarbledCircuit_BON::FixedWireRef> GarbledCircuit_BON::GarbledCircuitImpl::getFixedWireRef()
{
	std::set<GarbledCircuit_BON::FixedWireRef> res;
	std::set<BON::FCO> roles = ModelImpl::getChildFCOsAs("FixedWireRef");
	for( std::set<BON::FCO>::iterator i = roles.begin(); i != roles.end(); ++i)
	{
		GarbledCircuit_BON::FixedWireRef elem(*i);
		ASSERT(elem);
		res.insert(elem);
	}
	return res;
}


//********************************************************************************
// getter for role "GarbledCircuit" among "GarbledCircuit_BON::GarbledCircuit"s
//********************************************************************************
std::set<GarbledCircuit_BON::GarbledCircuit> GarbledCircuit_BON::GarbledCircuitImpl::getGarbledCircuit()
{
	std::set<GarbledCircuit_BON::GarbledCircuit> res;
	std::set<BON::FCO> roles = ModelImpl::getChildFCOsAs("GarbledCircuit");
	for( std::set<BON::FCO>::iterator i = roles.begin(); i != roles.end(); ++i)
	{
		GarbledCircuit_BON::GarbledCircuit elem(*i);
		ASSERT(elem);
		res.insert(elem);
	}
	return res;
}


//********************************************************************************
// aggregated getter for role "GarbledCircuit_BON::" among "GarbledCircuit_BON::InOutPut"s and its descendants
//********************************************************************************
std::set<GarbledCircuit_BON::InOutPut> GarbledCircuit_BON::GarbledCircuitImpl::getInOutPut()
{
	std::set<GarbledCircuit_BON::InOutPut> res;
	const int len = 2;
	std::set<BON::FCO> roles_vec[ len];
	roles_vec[0] = ModelImpl::getChildFCOsAs("Input");
	roles_vec[1] = ModelImpl::getChildFCOsAs("Output");
	for( int k = 0; k < len; ++k)
		for( std::set<BON::FCO>::iterator i = roles_vec[k].begin(); i != roles_vec[k].end(); ++i)
		{
			GarbledCircuit_BON::InOutPut elem(*i);
			ASSERT(elem);
			res.insert(elem);
		}
	return res;
}


//********************************************************************************
// getter for role "InitialtorRef" among "CircuitlRef"s and its descendants
//********************************************************************************
std::set<GarbledCircuit_BON::InitialtorRef> GarbledCircuit_BON::GarbledCircuitImpl::getInitialtorRef()
{
	std::set<GarbledCircuit_BON::InitialtorRef> res;
	std::set<BON::FCO> roles = ModelImpl::getChildFCOsAs("InitialtorRef");
	for( std::set<BON::FCO>::iterator i = roles.begin(); i != roles.end(); ++i)
	{
		GarbledCircuit_BON::InitialtorRef elem(*i);
		ASSERT(elem);
		res.insert(elem);
	}
	return res;
}


//********************************************************************************
// getter for role "Input" among "InOutPut"s and its descendants
//********************************************************************************
std::set<GarbledCircuit_BON::Input> GarbledCircuit_BON::GarbledCircuitImpl::getInput()
{
	std::set<GarbledCircuit_BON::Input> res;
	std::set<BON::FCO> roles = ModelImpl::getChildFCOsAs("Input");
	for( std::set<BON::FCO>::iterator i = roles.begin(); i != roles.end(); ++i)
	{
		GarbledCircuit_BON::Input elem(*i);
		ASSERT(elem);
		res.insert(elem);
	}
	return res;
}


//********************************************************************************
// getter for role "InternalWire" among "Wire"s and its descendants
//********************************************************************************
std::set<GarbledCircuit_BON::InternalWire> GarbledCircuit_BON::GarbledCircuitImpl::getInternalWire()
{
	std::set<GarbledCircuit_BON::InternalWire> res;
	std::set<BON::FCO> roles = ModelImpl::getChildFCOsAs("InternalWire");
	for( std::set<BON::FCO>::iterator i = roles.begin(); i != roles.end(); ++i)
	{
		GarbledCircuit_BON::InternalWire elem(*i);
		ASSERT(elem);
		res.insert(elem);
	}
	return res;
}


//********************************************************************************
// aggregated getter for role "GarbledCircuit_BON::" among "GarbledCircuit_BON::LogicalGate"s and its descendants
//********************************************************************************
std::set<GarbledCircuit_BON::LogicalGate> GarbledCircuit_BON::GarbledCircuitImpl::getLogicalGate()
{
	std::set<GarbledCircuit_BON::LogicalGate> res;
	const int len = 3;
	std::set<BON::FCO> roles_vec[ len];
	roles_vec[0] = ModelImpl::getChildFCOsAs("AND");
	roles_vec[1] = ModelImpl::getChildFCOsAs("OR");
	roles_vec[2] = ModelImpl::getChildFCOsAs("XOR");
	for( int k = 0; k < len; ++k)
		for( std::set<BON::FCO>::iterator i = roles_vec[k].begin(); i != roles_vec[k].end(); ++i)
		{
			GarbledCircuit_BON::LogicalGate elem(*i);
			ASSERT(elem);
			res.insert(elem);
		}
	return res;
}


//********************************************************************************
// getter for role "OR" among "LogicalGate"s and its descendants
//********************************************************************************
std::set<GarbledCircuit_BON::OR> GarbledCircuit_BON::GarbledCircuitImpl::getOR()
{
	std::set<GarbledCircuit_BON::OR> res;
	std::set<BON::FCO> roles = ModelImpl::getChildFCOsAs("OR");
	for( std::set<BON::FCO>::iterator i = roles.begin(); i != roles.end(); ++i)
	{
		GarbledCircuit_BON::OR elem(*i);
		ASSERT(elem);
		res.insert(elem);
	}
	return res;
}


//********************************************************************************
// getter for role "Output" among "InOutPut"s and its descendants
//********************************************************************************
std::set<GarbledCircuit_BON::Output> GarbledCircuit_BON::GarbledCircuitImpl::getOutput()
{
	std::set<GarbledCircuit_BON::Output> res;
	std::set<BON::FCO> roles = ModelImpl::getChildFCOsAs("Output");
	for( std::set<BON::FCO>::iterator i = roles.begin(); i != roles.end(); ++i)
	{
		GarbledCircuit_BON::Output elem(*i);
		ASSERT(elem);
		res.insert(elem);
	}
	return res;
}


//********************************************************************************
// getter for role "ReplicateRef" among "CircuitlRef"s and its descendants
//********************************************************************************
std::set<GarbledCircuit_BON::ReplicateRef> GarbledCircuit_BON::GarbledCircuitImpl::getReplicateRef()
{
	std::set<GarbledCircuit_BON::ReplicateRef> res;
	std::set<BON::FCO> roles = ModelImpl::getChildFCOsAs("ReplicateRef");
	for( std::set<BON::FCO>::iterator i = roles.begin(); i != roles.end(); ++i)
	{
		GarbledCircuit_BON::ReplicateRef elem(*i);
		ASSERT(elem);
		res.insert(elem);
	}
	return res;
}


//********************************************************************************
// getter for role "SingleRef" among "CircuitlRef"s and its descendants
//********************************************************************************
std::set<GarbledCircuit_BON::SingleRef> GarbledCircuit_BON::GarbledCircuitImpl::getSingleRef()
{
	std::set<GarbledCircuit_BON::SingleRef> res;
	std::set<BON::FCO> roles = ModelImpl::getChildFCOsAs("SingleRef");
	for( std::set<BON::FCO>::iterator i = roles.begin(); i != roles.end(); ++i)
	{
		GarbledCircuit_BON::SingleRef elem(*i);
		ASSERT(elem);
		res.insert(elem);
	}
	return res;
}


//********************************************************************************
// aggregated getter for role "GarbledCircuit_BON::" among "GarbledCircuit_BON::Wire"s and its descendants
//********************************************************************************
std::set<GarbledCircuit_BON::Wire> GarbledCircuit_BON::GarbledCircuitImpl::getWire()
{
	std::set<GarbledCircuit_BON::Wire> res;
	const int len = 2;
	std::set<BON::FCO> roles_vec[ len];
	roles_vec[0] = ModelImpl::getChildFCOsAs("DefineInOutPut");
	roles_vec[1] = ModelImpl::getChildFCOsAs("InternalWire");
	for( int k = 0; k < len; ++k)
		for( std::set<BON::FCO>::iterator i = roles_vec[k].begin(); i != roles_vec[k].end(); ++i)
		{
			GarbledCircuit_BON::Wire elem(*i);
			ASSERT(elem);
			res.insert(elem);
		}
	return res;
}


//********************************************************************************
// getter for role "XOR" among "LogicalGate"s and its descendants
//********************************************************************************
std::set<GarbledCircuit_BON::XOR> GarbledCircuit_BON::GarbledCircuitImpl::getXOR()
{
	std::set<GarbledCircuit_BON::XOR> res;
	std::set<BON::FCO> roles = ModelImpl::getChildFCOsAs("XOR");
	for( std::set<BON::FCO>::iterator i = roles.begin(); i != roles.end(); ++i)
	{
		GarbledCircuit_BON::XOR elem(*i);
		ASSERT(elem);
		res.insert(elem);
	}
	return res;
}


//********************************************************************************
// 
//********************************************************************************
void GarbledCircuit_BON::LibraryImpl::accept( BON::Visitor *pVisitor)
{
	// visit the Model
	pVisitor->visitModel( BON::Model( this));

}


//********************************************************************************
// getter for role "GarbledCircuit" among "GarbledCircuit_BON::GarbledCircuit"s
//********************************************************************************
std::set<GarbledCircuit_BON::GarbledCircuit> GarbledCircuit_BON::LibraryImpl::getGarbledCircuit()
{
	std::set<GarbledCircuit_BON::GarbledCircuit> res;
	std::set<BON::FCO> roles = ModelImpl::getChildFCOsAs("GarbledCircuit");
	for( std::set<BON::FCO>::iterator i = roles.begin(); i != roles.end(); ++i)
	{
		GarbledCircuit_BON::GarbledCircuit elem(*i);
		ASSERT(elem);
		res.insert(elem);
	}
	return res;
}


//********************************************************************************
// 
//********************************************************************************
std::string GarbledCircuit_BON::SplitPortImpl::getPortStartIndex() 
{
	return FCOImpl::getAttribute("PortStartIndex")->getStringValue();
}


//********************************************************************************
// 
//********************************************************************************
void GarbledCircuit_BON::SplitPortImpl::setPortStartIndex( const std::string& val)
{
	FCOImpl::getAttribute("PortStartIndex")->setStringValue( val);
}


//********************************************************************************
// 
//********************************************************************************
void GarbledCircuit_BON::InOutPutImpl::accept( BON::Visitor *pVisitor)
{
	// visit the Atom
	pVisitor->visitAtom( BON::Atom( this));

}


//********************************************************************************
// returns dst GarbledCircuit_BON::ConnectionRefs
//********************************************************************************
std::multiset<GarbledCircuit_BON::ConnectionRef> GarbledCircuit_BON::InOutPutImpl::getDefineInOutPutDsts()
{
	std::multiset<GarbledCircuit_BON::ConnectionRef> res;
	{
		std::multiset<BON::ConnectionEnd> out_ends = BON::ConnectionEndImpl::getOutConnEnds("DefineInOutPut");
		for ( std::multiset<BON::ConnectionEnd>::iterator cit = out_ends.begin() ; cit != out_ends.end() ; ++cit )
		{
			GarbledCircuit_BON::ConnectionRef dst( *cit );
			ASSERT(dst);
			res.insert( dst);
		}
	}
	return res;
}


//********************************************************************************
// 
//********************************************************************************
std::set<GarbledCircuit_BON::DefineInOutPut> GarbledCircuit_BON::InOutPutImpl::getOutDefineInOutPutLinks()
{
	std::set<GarbledCircuit_BON::DefineInOutPut> result;
	std::set<BON::Connection> conns = ConnectionEndImpl::getOutConnLinks();
	std::set<BON::Connection>::iterator it = conns.begin();
	for( ; it != conns.end(); ++it)
	{
		GarbledCircuit_BON::DefineInOutPut c( *it);
		if (c)
			result.insert( c);
	}
	return result;
}


//********************************************************************************
// 
//********************************************************************************
void GarbledCircuit_BON::CircuitlRefImpl::accept( BON::Visitor *pVisitor)
{
	// visit the Reference
	pVisitor->visitReference( BON::Reference( this));

}


//********************************************************************************
// 
//********************************************************************************
std::string GarbledCircuit_BON::CircuitlRefImpl::getCircuitIndexAlias() 
{
	return FCOImpl::getAttribute("CircuitIndexAlias")->getStringValue();
}


//********************************************************************************
// 
//********************************************************************************
std::string GarbledCircuit_BON::CircuitlRefImpl::getCircuitIndexRange() 
{
	return FCOImpl::getAttribute("CircuitIndexRange")->getStringValue();
}


//********************************************************************************
// 
//********************************************************************************
void GarbledCircuit_BON::CircuitlRefImpl::setCircuitIndexAlias( const std::string& val)
{
	FCOImpl::getAttribute("CircuitIndexAlias")->setStringValue( val);
}


//********************************************************************************
// 
//********************************************************************************
void GarbledCircuit_BON::CircuitlRefImpl::setCircuitIndexRange( const std::string& val)
{
	FCOImpl::getAttribute("CircuitIndexRange")->setStringValue( val);
}


//********************************************************************************
// 
//********************************************************************************
BON::FCO GarbledCircuit_BON::CircuitlRefImpl::getReferred()
{
	BON::FCO r = BON::ReferenceImpl::getReferred();
	return BON::FCO(r);
}


//********************************************************************************
// 
//********************************************************************************
void GarbledCircuit_BON::InputImpl::accept( BON::Visitor *pVisitor)
{
	// visit the Atom
	pVisitor->visitAtom( BON::Atom( this));

}


//********************************************************************************
// 
//********************************************************************************
void GarbledCircuit_BON::OutputImpl::accept( BON::Visitor *pVisitor)
{
	// visit the Atom
	pVisitor->visitAtom( BON::Atom( this));

}


//********************************************************************************
// 
//********************************************************************************
void GarbledCircuit_BON::ConnectionRefImpl::accept( BON::Visitor *pVisitor)
{
	// visit the Reference
	pVisitor->visitReference( BON::Reference( this));

}


//********************************************************************************
// returns src GarbledCircuit_BON::InOutPuts
//********************************************************************************
std::multiset<GarbledCircuit_BON::InOutPut> GarbledCircuit_BON::ConnectionRefImpl::getDefineInOutPutSrcs()
{
	std::multiset<GarbledCircuit_BON::InOutPut> res;
	{
		std::multiset<BON::ConnectionEnd> in_ends = BON::ConnectionEndImpl::getInConnEnds("DefineInOutPut");
		for ( std::multiset<BON::ConnectionEnd>::iterator cit = in_ends.begin() ; cit != in_ends.end() ; ++cit )
		{
			GarbledCircuit_BON::InOutPut dst( *cit );
			ASSERT(dst);
			res.insert( dst);
		}
	}
	return res;
}


//********************************************************************************
// 
//********************************************************************************
std::set<GarbledCircuit_BON::DefineInOutPut> GarbledCircuit_BON::ConnectionRefImpl::getInDefineInOutPutLinks()
{
	std::set<GarbledCircuit_BON::DefineInOutPut> result;
	std::set<BON::Connection> conns = ConnectionEndImpl::getInConnLinks();
	std::set<BON::Connection>::iterator it = conns.begin();
	for( ; it != conns.end(); ++it)
	{
		GarbledCircuit_BON::DefineInOutPut c( *it);
		if (c)
			result.insert( c);
	}
	return result;
}


//********************************************************************************
// 
//********************************************************************************
std::set<GarbledCircuit_BON::InternalWire> GarbledCircuit_BON::ConnectionRefImpl::getInInternalWireLinks()
{
	std::set<GarbledCircuit_BON::InternalWire> result;
	std::set<BON::Connection> conns = ConnectionEndImpl::getInConnLinks();
	std::set<BON::Connection>::iterator it = conns.begin();
	for( ; it != conns.end(); ++it)
	{
		GarbledCircuit_BON::InternalWire c( *it);
		if (c)
			result.insert( c);
	}
	return result;
}


//********************************************************************************
// returns dst GarbledCircuit_BON::ConnectionRefs
//********************************************************************************
std::multiset<GarbledCircuit_BON::ConnectionRef> GarbledCircuit_BON::ConnectionRefImpl::getInternalWireDsts()
{
	std::multiset<GarbledCircuit_BON::ConnectionRef> res;
	{
		std::multiset<BON::ConnectionEnd> out_ends = BON::ConnectionEndImpl::getOutConnEnds("InternalWire");
		for ( std::multiset<BON::ConnectionEnd>::iterator cit = out_ends.begin() ; cit != out_ends.end() ; ++cit )
		{
			GarbledCircuit_BON::ConnectionRef dst( *cit );
			ASSERT(dst);
			res.insert( dst);
		}
	}
	return res;
}


//********************************************************************************
// 
//********************************************************************************
std::set<GarbledCircuit_BON::InternalWire> GarbledCircuit_BON::ConnectionRefImpl::getInternalWireLinks()
{
	std::set<GarbledCircuit_BON::InternalWire> result;
	std::set<BON::Connection> conns = ConnectionEndImpl::getConnLinks();
	std::set<BON::Connection>::iterator it = conns.begin();
	for( ; it != conns.end(); ++it)
	{
		GarbledCircuit_BON::InternalWire c( *it);
		if (c)
			result.insert( c);
	}
	return result;
}


//********************************************************************************
// returns src GarbledCircuit_BON::ConnectionRefs
//********************************************************************************
std::multiset<GarbledCircuit_BON::ConnectionRef> GarbledCircuit_BON::ConnectionRefImpl::getInternalWireSrcs()
{
	std::multiset<GarbledCircuit_BON::ConnectionRef> res;
	{
		std::multiset<BON::ConnectionEnd> in_ends = BON::ConnectionEndImpl::getInConnEnds("InternalWire");
		for ( std::multiset<BON::ConnectionEnd>::iterator cit = in_ends.begin() ; cit != in_ends.end() ; ++cit )
		{
			GarbledCircuit_BON::ConnectionRef dst( *cit );
			ASSERT(dst);
			res.insert( dst);
		}
	}
	return res;
}


//********************************************************************************
// 
//********************************************************************************
std::set<GarbledCircuit_BON::InternalWire> GarbledCircuit_BON::ConnectionRefImpl::getOutInternalWireLinks()
{
	std::set<GarbledCircuit_BON::InternalWire> result;
	std::set<BON::Connection> conns = ConnectionEndImpl::getOutConnLinks();
	std::set<BON::Connection>::iterator it = conns.begin();
	for( ; it != conns.end(); ++it)
	{
		GarbledCircuit_BON::InternalWire c( *it);
		if (c)
			result.insert( c);
	}
	return result;
}


//********************************************************************************
// 
//********************************************************************************
void GarbledCircuit_BON::FixedWireRefImpl::accept( BON::Visitor *pVisitor)
{
	// visit the Reference
	pVisitor->visitReference( BON::Reference( this));

}


//********************************************************************************
// 
//********************************************************************************
std::string GarbledCircuit_BON::FixedWireRefImpl::getDescription() 
{
	return FCOImpl::getAttribute("Description")->getStringValue();
}


//********************************************************************************
// 
//********************************************************************************
GarbledCircuit_BON::FixedWireRefImpl::FixedValue_Type GarbledCircuit_BON::FixedWireRefImpl::getFixedValue()
{
	std::string val = FCOImpl::getAttribute("FixedValue")->getStringValue();

	if ( val == "0") return _0_FixedValue_Type;
	else if ( val == "1") return _1_FixedValue_Type;
	else throw("None of the possible items");
}


//********************************************************************************
// 
//********************************************************************************
std::string GarbledCircuit_BON::FixedWireRefImpl::getPortIndex() 
{
	return FCOImpl::getAttribute("PortIndex")->getStringValue();
}


//********************************************************************************
// 
//********************************************************************************
void GarbledCircuit_BON::FixedWireRefImpl::setDescription( const std::string& val)
{
	FCOImpl::getAttribute("Description")->setStringValue( val);
}


//********************************************************************************
// 
//********************************************************************************
void GarbledCircuit_BON::FixedWireRefImpl::setFixedValue( FixedWireRefImpl::FixedValue_Type val)
{
	std::string str_val = "";

	if ( val == _0_FixedValue_Type) str_val = "0";
	else if ( val == _1_FixedValue_Type) str_val = "1";
	else throw("None of the possible items");

	FCOImpl::getAttribute("FixedValue")->setStringValue( str_val);
}


//********************************************************************************
// 
//********************************************************************************
void GarbledCircuit_BON::FixedWireRefImpl::setPortIndex( const std::string& val)
{
	FCOImpl::getAttribute("PortIndex")->setStringValue( val);
}


//********************************************************************************
// 
//********************************************************************************
void GarbledCircuit_BON::InitialtorRefImpl::accept( BON::Visitor *pVisitor)
{
	// visit the Reference
	pVisitor->visitReference( BON::Reference( this));

}


//********************************************************************************
// 
//********************************************************************************
std::string GarbledCircuit_BON::InitialtorRefImpl::getCircuitArgument() 
{
	return FCOImpl::getAttribute("CircuitArgument")->getStringValue();
}


//********************************************************************************
// 
//********************************************************************************
std::string GarbledCircuit_BON::InitialtorRefImpl::getDescription() 
{
	return FCOImpl::getAttribute("Description")->getStringValue();
}


//********************************************************************************
// 
//********************************************************************************
void GarbledCircuit_BON::InitialtorRefImpl::setCircuitArgument( const std::string& val)
{
	FCOImpl::getAttribute("CircuitArgument")->setStringValue( val);
}


//********************************************************************************
// 
//********************************************************************************
void GarbledCircuit_BON::InitialtorRefImpl::setDescription( const std::string& val)
{
	FCOImpl::getAttribute("Description")->setStringValue( val);
}


//********************************************************************************
// 
//********************************************************************************
void GarbledCircuit_BON::ReplicateRefImpl::accept( BON::Visitor *pVisitor)
{
	// visit the Reference
	pVisitor->visitReference( BON::Reference( this));

}

CodeGeneratorNameSpace::Component * GarbledCircuit_BON::ReplicateRefImpl::getComponent(string port)
{
	return new CodeGeneratorNameSpace::MultipleComponent(this->getCircuitIndexRange(), port);
}


//********************************************************************************
// 
//********************************************************************************
void GarbledCircuit_BON::SingleRefImpl::accept( BON::Visitor *pVisitor)
{
	// visit the Reference
	pVisitor->visitReference( BON::Reference( this));

}

CodeGeneratorNameSpace::Component * GarbledCircuit_BON::SingleRefImpl::getComponent(string port)
{
	return new CodeGeneratorNameSpace::SingleComponent(this->getCircuitIndexRange(), this->getPortStartIndex(),port);
}
//********************************************************************************
// 
//********************************************************************************
void GarbledCircuit_BON::LogicalGateImpl::accept( BON::Visitor *pVisitor)
{
	// visit the Atom
	pVisitor->visitAtom( BON::Atom( this));

}


//********************************************************************************
// 
//********************************************************************************
long GarbledCircuit_BON::LogicalGateImpl::getMultiplicity() 
{
	return FCOImpl::getAttribute("Multiplicity")->getIntegerValue();
}


//********************************************************************************
// 
//********************************************************************************
void GarbledCircuit_BON::LogicalGateImpl::setMultiplicity( const long val)
{
	FCOImpl::getAttribute("Multiplicity")->setIntegerValue( val);
}


//********************************************************************************
// 
//********************************************************************************
void GarbledCircuit_BON::ANDImpl::accept( BON::Visitor *pVisitor)
{
	// visit the Atom
	pVisitor->visitAtom( BON::Atom( this));

}


//********************************************************************************
// 
//********************************************************************************
void GarbledCircuit_BON::ORImpl::accept( BON::Visitor *pVisitor)
{
	// visit the Atom
	pVisitor->visitAtom( BON::Atom( this));

}


//********************************************************************************
// 
//********************************************************************************
void GarbledCircuit_BON::XORImpl::accept( BON::Visitor *pVisitor)
{
	// visit the Atom
	pVisitor->visitAtom( BON::Atom( this));

}


//********************************************************************************
// 
//********************************************************************************
void GarbledCircuit_BON::WireImpl::accept( BON::Visitor *pVisitor)
{
	// visit the Connection
	pVisitor->visitConnection( BON::Connection( this));

}


//********************************************************************************
// 
//********************************************************************************
std::string GarbledCircuit_BON::WireImpl::getDescription() 
{
	return FCOImpl::getAttribute("Description")->getStringValue();
}


//********************************************************************************
// 
//********************************************************************************
std::string GarbledCircuit_BON::WireImpl::getDestinationPortIndex() 
{
	return FCOImpl::getAttribute("DestinationPortIndex")->getStringValue();
}


//********************************************************************************
// 
//********************************************************************************
std::string GarbledCircuit_BON::WireImpl::getSourcePortIndex() 
{
	return FCOImpl::getAttribute("SourcePortIndex")->getStringValue();
}


//********************************************************************************
// 
//********************************************************************************
void GarbledCircuit_BON::WireImpl::setDescription( const std::string& val)
{
	FCOImpl::getAttribute("Description")->setStringValue( val);
}


//********************************************************************************
// 
//********************************************************************************
void GarbledCircuit_BON::WireImpl::setDestinationPortIndex( const std::string& val)
{
	FCOImpl::getAttribute("DestinationPortIndex")->setStringValue( val);
}


//********************************************************************************
// 
//********************************************************************************
void GarbledCircuit_BON::WireImpl::setSourcePortIndex( const std::string& val)
{
	FCOImpl::getAttribute("SourcePortIndex")->setStringValue( val);
}


//********************************************************************************
// 
//********************************************************************************
void GarbledCircuit_BON::DefineInOutPutImpl::accept( BON::Visitor *pVisitor)
{
	// visit the Connection
	pVisitor->visitConnection( BON::Connection( this));

}


//********************************************************************************
// getDst() return value is a ConnectionEnd casted to GarbledCircuit_BON::ConnectionRef
//********************************************************************************
GarbledCircuit_BON::ConnectionRef GarbledCircuit_BON::DefineInOutPutImpl::getDst()
{
	BON::ConnectionEnd ce = ConnectionImpl::getDst();
	GarbledCircuit_BON::ConnectionRef sp( ce);
	if ( sp)
		return sp;

	GarbledCircuit_BON::ConnectionRef empty;
	return empty;
}


//********************************************************************************
// getSrc() return value is a ConnectionEnd casted to GarbledCircuit_BON::InOutPut
//********************************************************************************
GarbledCircuit_BON::InOutPut GarbledCircuit_BON::DefineInOutPutImpl::getSrc()
{
	BON::ConnectionEnd ce = ConnectionImpl::getSrc();
	GarbledCircuit_BON::InOutPut sp( ce);
	if ( sp)
		return sp;

	GarbledCircuit_BON::InOutPut empty;
	return empty;
}


//********************************************************************************
// 
//********************************************************************************
void GarbledCircuit_BON::InternalWireImpl::accept( BON::Visitor *pVisitor)
{
	// visit the Connection
	pVisitor->visitConnection( BON::Connection( this));

}


//********************************************************************************
// getDst() return value is a ConnectionEnd casted to GarbledCircuit_BON::ConnectionRef
//********************************************************************************
GarbledCircuit_BON::ConnectionRef GarbledCircuit_BON::InternalWireImpl::getDst()
{
	BON::ConnectionEnd ce = ConnectionImpl::getDst();
	GarbledCircuit_BON::ConnectionRef sp( ce);
	if ( sp)
		return sp;

	GarbledCircuit_BON::ConnectionRef empty;
	return empty;
}


//********************************************************************************
// getSrc() return value is a ConnectionEnd casted to GarbledCircuit_BON::ConnectionRef
//********************************************************************************
GarbledCircuit_BON::ConnectionRef GarbledCircuit_BON::InternalWireImpl::getSrc()
{
	BON::ConnectionEnd ce = ConnectionImpl::getSrc();
	GarbledCircuit_BON::ConnectionRef sp( ce);
	if ( sp)
		return sp;

	GarbledCircuit_BON::ConnectionRef empty;
	return empty;
}



