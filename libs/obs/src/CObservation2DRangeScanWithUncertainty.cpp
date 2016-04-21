/* +---------------------------------------------------------------------------+
   |                     Mobile Robot Programming Toolkit (MRPT)               |
   |                          http://www.mrpt.org/                             |
   |                                                                           |
   | Copyright (c) 2005-2016, Individual contributors, see AUTHORS file        |
   | See: http://www.mrpt.org/Authors - All rights reserved.                   |
   | Released under BSD License. See details in http://www.mrpt.org/License    |
   +---------------------------------------------------------------------------+ */

#include "obs-precomp.h"   // Precompiled headers

#include <mrpt/obs/CObservation2DRangeScanWithUncertainty.h>

using namespace mrpt::obs;

CObservation2DRangeScanWithUncertainty::TEvalParams::TEvalParams() :
	prob_outliers(0.5),
	prob_lost_ray(0.3),
	max_prediction_std_dev(1.0)
{
}

double CObservation2DRangeScanWithUncertainty::evaluateScanLikelihood(const CObservation2DRangeScan& otherScan, const TEvalParams &params) const
{
	ASSERT_EQUAL_( otherScan.scan.size(),otherScan.validRange.size() );
	ASSERT_EQUAL_( otherScan.scan.size(), this->rangesMean.size() );
	ASSERT_EQUAL_( otherScan.scan.size(), this->rangesCovar.rows() );
	ASSERT_EQUAL_( otherScan.scan.size(), this->rangesCovar.cols() );
	ASSERT_(params.prob_outliers>=0.0 && params.prob_outliers<=1.0)
	ASSERT_(otherScan.maxRange>0.0)

	const double sensorRangeVar = mrpt::utils::square(otherScan.stdError);
	const size_t N = rangesMean.size();

	const double max_var = mrpt::utils::square(params.max_prediction_std_dev);
	double lik_sum = .0;
	size_t num_valid = 0;

	for (size_t i=0;i<N;i++)
	{
		const double prediction_total_var = rangesCovar(i,i)+sensorRangeVar;
		
		if (prediction_total_var>max_var)
			continue;

		num_valid++;
		const double otherScanRange = otherScan.validRange[i] ? otherScan.scan[i] : otherScan.maxRange;

		const double likGauss = exp(-0.5 * mrpt::utils::square( otherScanRange - rangesMean[i] )/ prediction_total_var );
		double pi;
		if (otherScan.scan[i] > rangesMean[i]) {
			if (otherScan.validRange[i])
			     pi = likGauss;
			else pi = std::max(likGauss, params.prob_lost_ray);
		}
		else {
			pi = std::max( likGauss, std::min(1.0, params.prob_outliers *otherScanRange/rangesMean[i] ) );
		}
		lik_sum+=pi;
	}
	if (num_valid) lik_sum/=num_valid;

	return lik_sum;
}

