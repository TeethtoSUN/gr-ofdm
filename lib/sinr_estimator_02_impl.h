/* -*- c++ -*- */
/* 
 * Copyright 2014 Institute for Theoretical Information Technology,
 *                RWTH Aachen University
 *                www.ti.rwth-aachen.de
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef INCLUDED_OFDM_SINR_ESTIMATOR_02_IMPL_H
#define INCLUDED_OFDM_SINR_ESTIMATOR_02_IMPL_H

#include <ofdm/sinr_estimator_02.h>

#include <boost/shared_array.hpp>

/*!
  Implementation of Milan's SNR estimation,
  taking the 1st and 2nd preamble as input and giving
   per subcarrier SINR estimate at the 1st output and average SNR at the 2nd output
 */

namespace gr {
  namespace ofdm {

    class sinr_estimator_02_impl : public sinr_estimator_02
    {
     private:
    	  int   d_vlen;
    	  int	d_skip;
    	  //std::vector<int>   d_load_index;
    	  boost::shared_array<float> d_taps;
    	  boost::shared_array<float> d_taps1;
     public:
      sinr_estimator_02_impl(int vlen, int skip);
      ~sinr_estimator_02_impl();

      // Where all the action really happens
      int work(int noutput_items,
	       gr_vector_const_void_star &input_items,
	       gr_vector_void_star &output_items);
    };

  } // namespace ofdm
} // namespace gr

#endif /* INCLUDED_OFDM_SINR_ESTIMATOR_02_IMPL_H */

