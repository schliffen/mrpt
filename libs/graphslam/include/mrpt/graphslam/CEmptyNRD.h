/* +---------------------------------------------------------------------------+
	 |                     Mobile Robot Programming Toolkit (MRPT)               |
	 |                          http://www.mrpt.org/                             |
	 |                                                                           |
	 | Copyright (c) 2005-2016, Individual contributors, see AUTHORS file        |
	 | See: http://www.mrpt.org/Authors - All rights reserved.                   |
	 | Released under BSD License. See details in http://www.mrpt.org/License    |
	 +---------------------------------------------------------------------------+ */

#ifndef CEMPTYNRD_H
#define CEMPTYNRD_H

#include <mrpt/obs/CActionCollection.h>
#include <mrpt/obs/CSensoryFrame.h>
#include <mrpt/obs/CRawlog.h>

#include "CNodeRegistrationDecider.h"

namespace mrpt { namespace graphslam { namespace deciders {

/**\brief Empty Node Registration Decider
 *
 * Handy when you are testing other parts of the application but not the
 * specific registration procedure
 */
template<class GRAPH_t=typename mrpt::graphs::CNetworkOfPoses2DInf>
class CEmptyNRD:
	public mrpt::graphslam::deciders::CNodeRegistrationDecider<GRAPH_t>
{
	public:
		CEmptyNRD();
		~CEmptyNRD();

		bool updateState( mrpt::obs::CActionCollectionPtr action,
				mrpt::obs::CSensoryFramePtr observations,
				mrpt::obs::CObservationPtr observation );

	private:
		void registerNewNode();

};

//////////////////////////////////////////////////////////////////////////////

template<class GRAPH_t>
CEmptyNRD<GRAPH_t>::CEmptyNRD() { }
template<class GRAPH_t>
CEmptyNRD<GRAPH_t>::~CEmptyNRD() { }

template<class GRAPH_t>
bool CEmptyNRD<GRAPH_t>::updateState(
		mrpt::obs::CActionCollectionPtr action,
		mrpt::obs::CSensoryFramePtr observations,
		mrpt::obs::CObservationPtr observation )  {return false;}

template<class GRAPH_t>
void CEmptyNRD<GRAPH_t>::registerNewNode() { }

} } } // end of namespaces

#endif /* end of include guard: CEMPTYNRD_H */
