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

#ifndef INCLUDED_OFDM_AUTOCORRELATOR0_H
#define INCLUDED_OFDM_AUTOCORRELATOR0_H

#include <ofdm/api.h>
#include <gnuradio/hier_block2.h>

namespace gr {
  namespace ofdm {

    /*!
     * \brief <+description of block+>
     * \ingroup ofdm
     *
     */
    class OFDM_API autocorrelator0 : virtual public gr::hier_block2
    {
     public:
      typedef boost::shared_ptr<autocorrelator0> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of ofdm::autocorrelator0.
       *
       * To avoid accidental use of raw pointers, ofdm::autocorrelator0's
       * constructor is in a private implementation
       * class. ofdm::autocorrelator0::make is the public interface for
       * creating new instances.
       */
      static sptr make(int lag, int n_samples);
    };

  } // namespace ofdm
} // namespace gr

#endif /* INCLUDED_OFDM_AUTOCORRELATOR0_H */

