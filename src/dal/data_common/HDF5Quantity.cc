/***************************************************************************
 *   Copyright (C) 2011                                                    *
 *   Lars B"ahren (lbaehren@gmail.com)                                     *
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

#include "HDF5Quantity.h"

namespace DAL { // Namespace DAL -- begin
  
  // ============================================================================
  //
  //  Construction
  //
  // ============================================================================
  
  HDF5Quantity::HDF5Quantity ()
  {
    init ();
  }
  
  HDF5Quantity::HDF5Quantity (double const &value,
			      std::string const &unit)
  {
    setQuantity (value, unit);
  }
  
  HDF5Quantity::HDF5Quantity (std::vector<double> const &values,
			      std::string const &unit)
  {
    setQuantity (values, unit);
  }
  
  HDF5Quantity::HDF5Quantity (std::vector<double> const &values,
			      std::vector<std::string> const &units)
  {
    setQuantity (values, units);
  }
  
  /*!
    \param other -- Another HDF5Property object from which to create this new
           one.
  */
  HDF5Quantity::HDF5Quantity (HDF5Quantity const &other)
  {
    copy (other);
  }
  
  // ============================================================================
  //
  //  Destruction
  //
  // ============================================================================
  
  HDF5Quantity::~HDF5Quantity ()
  {
    destroy();
  }
  
  void HDF5Quantity::destroy ()
  {;}
  
  // ============================================================================
  //
  //  Operators
  //
  // ============================================================================
  
  //_____________________________________________________________________________
  //                                                                    operator=
  
  /*!
    \param other -- Another HDF5Quantity object from which to make a copy.
  */
  HDF5Quantity& HDF5Quantity::operator= (HDF5Quantity const &other)
  {
    if (this != &other) {
      destroy ();
      copy (other);
    }
    return *this;
  }
  
  //_____________________________________________________________________________
  //                                                                         copy
  
  void HDF5Quantity::copy (HDF5Quantity const &other)
  {
    itsValues.resize(other.itsValues.size());
    itsValues = other.itsValues;

    itsUnits.resize(other.itsUnits.size());
    itsUnits = other.itsUnits;

    itsName        = other.itsName;
    itsValueSuffix = other.itsValueSuffix;
    itsUnitSuffix  = other.itsUnitSuffix;
    itsSeparator   = other.itsSeparator;
  }

  // ============================================================================
  //
  //  Parameter access
  //
  // ============================================================================
  
  bool HDF5Quantity::setQuantity (double const &value,
				  std::string const &unit)
  {
    itsValues.resize(1);
    itsValues[0] = value;

    itsUnits.resize(1);
    itsUnits[0] = unit;

    return true;
  }
  
  bool HDF5Quantity::setQuantity (std::vector<double> const &values,
				  std::string const &unit)
  {
    std::vector<std::string> units (values.size(),unit);
    return setQuantity (values,units);
  }
  
  bool HDF5Quantity::setQuantity (std::vector<double> const &values,
				  std::vector<std::string> const &units)
  {
    if (values.size() == units.size()) {
      // Value(s)
      itsValues.resize(values.size());
      itsValues = values;
      // Unit(s)
      itsUnits.resize(units.size());
      itsUnits = units;
      // return
      return true;
    } else {
      return false;
    }
  }
  
  //_____________________________________________________________________________
  //                                                                      summary
  
  /*!
    \param os -- Output stream to which the summary is written.
  */
  void HDF5Quantity::summary (std::ostream &os)
  {
    os << "[HDF5Quantity] Summary of internal parameters." << std::endl;
  }
  
  // ============================================================================
  //
  //  Public methods
  //
  // ============================================================================
  
  void HDF5Quantity::init ()
  {
    itsValues.clear();
    itsUnits.clear();
    
    itsName        = "";
    itsValueSuffix = "VALUE";
    itsUnitSuffix  = "UNITS";
    itsSeparator   = "_";
  }

  // ============================================================================
  //
  //  Static methods
  //
  // ============================================================================
  
  

} // Namespace DAL -- end
