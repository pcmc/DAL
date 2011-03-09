/***************************************************************************
 *   Copyright (C) 2010                                                    *
 *   Lars B"ahren <bahren@astron.nl>                                       *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef ACCESSPROPERTIES_H
#define ACCESSPROPERTIES_H

#include <dal_config.h>
#include <core/HDF5Object.h>

namespace DAL { // Namespace DAL -- begin
  
  /*!
    \class AccessProperties
    
    \ingroup DAL
    \ingroup core
    
    \brief Book-keeping of access properties
    
    \author Lars B&auml;hren

    \date 2010/10/19

    \test tAccessProperties.cc
    
    <h3>Prerequisite</h3>
    
    <ul type="square">
      <li>[start filling in your text here]
    </ul>
    
    <h3>Synopsis</h3>

    Available file access property flags:

    <ul>
      <li>\b HDF5 <br>
      These are the bits that can be passed to the `flags' argument of
      \c H5Fcreate() and \c H5Fopen(). Use the bit-wise OR operator (|) to combine
      them as needed.  As a side effect, they call H5check_version() to make sure
      that the application is compiled with a version of the hdf5 header files
      which are compatible with the library to which the application is linked.
      We're assuming that these constants are used rather early in the hdf5
      session.
      \code
      //____________________________________________________
      // H5Fpublic.h

      #define H5F_ACC_RDONLY  (H5CHECK 0x0000u)     //  absence of rdwr => rd-only
      #define H5F_ACC_RDWR    (H5CHECK 0x0001u)     //  open for read and write
      #define H5F_ACC_TRUNC   (H5CHECK 0x0002u)     //  overwrite existing files
      #define H5F_ACC_EXCL    (H5CHECK 0x0004u)     //  fail if file already exists
      #define H5F_ACC_DEBUG   (H5CHECK 0x0008u)     //  print debug info
      #define H5F_ACC_CREAT   (H5CHECK 0x0010u)     //  create non-existing files
      \endcode
      Four access modes address these concerns, with H5Fcreate and H5Fopen each
      accepting two of them:
      <ul>
        <li>\c H5Fcreate accepts \c H5F_ACC_TRUNC or \c H5F_ACC_EXCL.
	<li>\c H5Fopen accepts \c H5F_ACC_RDONLY or \c H5F_ACC_RDWR.
      </ul>
      For more detailed information see chapter 3 ("The HDF5 File") of the
      <i>HDF5 User's Guide</i>.
      
      <li>\b CFITSIO <br>
      The iomode parameter defines the read/write access allowed in the file and can
      have values of:
      \code
      #define READONLY 0
      #define READWRITE 1
      \endcode

      <li>\b casacore

      <li>\b mirlib

      \code
      //____________________________________________________
      // dio.c
      
      if     (!strcmp(status,"read"))    flags = O_RDONLY;
      else if(!strcmp(status,"write"))   flags = O_CREAT|O_TRUNC|O_RDWR;
      else if(!strcmp(status,"append"))  flags = O_CREAT|O_RDWR;

      //____________________________________________________
      // hio.c
      
      #define ITEM_READ     0x1
      #define ITEM_WRITE    0x2
      #define ITEM_SCRATCH  0x4
      #define ITEM_APPEND   0x8
      #define ACCESS_MODE (ITEM_READ|ITEM_WRITE|ITEM_SCRATCH|ITEM_APPEND)
      
      #define RDWR_UNKNOWN 0
      #define RDWR_RDONLY  1
      #define RDWR_RDWR    
      \endcode
    </ul>
    
    <h3>Example(s)</h3>
    
  */  
  class AccessProperties {

    hid_t itsAccessProperties;
    
  public:
    
    // === Construction =========================================================
    
    //! Default constructor
    AccessProperties ();
    
    //! Copy constructor
    AccessProperties (AccessProperties const &other);
    
    // === Destruction ==========================================================

    //! Destructor
    ~AccessProperties ();
    
    // === Operators ============================================================
    
    /*!
      \brief Overloading of the copy operator
      
      \param other -- Another AccessProperties object from which to make a copy.
    */
    AccessProperties& operator= (AccessProperties const &other); 
    
    // === Parameter access =====================================================
    
    /*!
      \brief Get the name of the class
      
      \return className -- The name of the class, AccessProperties.
    */
    inline std::string className () const {
      return "AccessProperties";
    }

    //! Provide a summary of the object's internal parameters and status
    inline void summary () {
      summary (std::cout);
    }

    //! Provide a summary of the object's internal parameters and status
    void summary (std::ostream &os);    

    // === Methods ==============================================================
    
    
    
  private:
    
    //! Unconditional copying
    void copy (AccessProperties const &other);
    
    //! Unconditional deletion 
    void destroy(void);
    
  }; // Class AccessProperties -- end
  
} // Namespace DAL -- end

#endif /* ACCESSPROPERTIES_H */
  