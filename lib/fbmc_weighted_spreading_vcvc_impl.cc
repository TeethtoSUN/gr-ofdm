/* -*- c++ -*- */
/* 
 * Copyright 2014 <+YOU OR YOUR COMPANY+>.
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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "fbmc_weighted_spreading_vcvc_impl.h"

namespace gr {
  namespace ofdm {

    fbmc_weighted_spreading_vcvc::sptr
    fbmc_weighted_spreading_vcvc::make(unsigned int M, unsigned int K)
    {
      return gnuradio::get_initial_sptr
        (new fbmc_weighted_spreading_vcvc_impl(M, K));
    }

    /*
     * The private constructor
     */
    fbmc_weighted_spreading_vcvc_impl::fbmc_weighted_spreading_vcvc_impl(unsigned int M, unsigned int K)
      : gr::sync_block("fbmc_weighted_spreading_vcvc",
        gr::io_signature::make(1, 1, sizeof(gr_complex)*M),
        gr::io_signature::make(1, 1, sizeof(gr_complex)*K*M)),
    d_M(M),
    d_K(K),
    d_h(new gr_complex[K])
  {
    assert(K==2 || K==3 || K==4);
    assert(M>0 && log(M)/log(2) = (int)(log(M)/log(2)));
    initialize_vector(d_h,K);
    // std::cout<<"before";
    // for(int i=0;i<d_K;i++) std::cout<<d_h[i]<<std::endl;
    // std::cout<<"after";
  }

    /*
     * Our virtual destructor.
     */
    fbmc_weighted_spreading_vcvc_impl::~fbmc_weighted_spreading_vcvc_impl()
    {
    }

    void
    fbmc_weighted_spreading_vcvc_impl::initialize_vector(gr_complex* v, unsigned int K)
    {
      // v = new gr_complex[K];
      if(K==2){
        v[0] = 1;
        v[1] = sqrt(2)/2;
      }else if(K==3){
        v[0] = 1;
        v[1] = 0.911438;
        v[2] = 0.411438;
      }else if(K==4){
        v[0] = 1;
        v[1] = 0.97195983;
        v[2] = sqrt(2)/2;
        v[3] = 0.23514695;
      }
    }

    int
    fbmc_weighted_spreading_vcvc_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items)
    {
        const gr_complex *in = (const gr_complex *) input_items[0];
    gr_complex *out = (gr_complex *) output_items[0];

    // Do <+signal processing+>
    for(int i=0;i<noutput_items*d_K*d_M;i++){
      int ii= (int)(i/d_K); //input index
      if(i%d_K==0){
        out[i] = d_h[0]*in[ii]; //secret multiplier h[0] = 1
      }else{
        for(int j=1;j<d_K;j++){
          if(ii%d_M!=d_M-1){
            out[i] = d_h[j]*in[ii]+d_h[d_K-j]*in[ii+1];
            // std::cout<<in[ii]<<"\t"<<in[ii+1]<<"\t"<<std::endl;
          }else{
            out[i] = d_h[j]*in[ii]+d_h[d_K-j]*in[ii+1-d_M];
            // std::cout<<in[ii]<<"\t"<<in[ii+1-d_M]<<"\t"<<std::endl;
          }
          i++;
        } 
        i--; //decrease i because it will be also incremented by main loop
      }
    }
    // Tell runtime system how many output items we produced.
    return noutput_items;
    }

  } /* namespace ofdm */
} /* namespace gr */

