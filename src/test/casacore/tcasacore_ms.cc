/***************************************************************************
 *   Copyright (C) 2007-2011                                               *
 *   Lars Baehren (lbaehren@gmail.com)                                     *
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

#include <iostream>
#include <iomanip>
#include <string>

#include <casa/OS/File.h>
#include <casa/OS/SymLink.h>
#include <ms/MeasurementSets.h>
#include <ms/MeasurementSets/MeasurementSet.h>
#include <tables/Tables/TableDesc.h>
#include <tables/Tables/SetupNewTab.h>

/*!
  \file tMeasurementSets.cc

  \ingroup DAL

  \brief Test building against the "ms" modules of casacore

  \author Lars B&auml;hren

  \date 2007/08/13

  This test program contains a number of routines which make use of various
  modules and classes of the casacore libraries; rather than providing a full
  test and demonstration of all the available functionality, this program collects
  a number of very simple test such creating some basic objects and using their
  APIs.
*/

/* Namespace usage */
using std::cout;
using std::endl;

//_______________________________________________________________________________
//                                                                           main

/*!
  \brief Test working with the classes in the CASA "ms" module
  
  \return nofFaildTests -- The number of failed tests within this function
*/
int test_open_create (std::string const &filename="tcasacore_ms.ms")
{
  cout << "\n[tcasacore_ms::test_open_create]\n" << endl;
  
  int nofFailedTests = 0;
  bool fileExists    = false;
  std::string absoluteName;
  casa::File msfile (filename);
  casa::MeasurementSet ms;

  fileExists = msfile.exists();
  
  if (fileExists) {
    
    /*____________________________________________
      Open existing MeasurementSet
    */
    
    if (msfile.isSymLink()) {
      casa::SymLink link (msfile);
      casa::Path realFileName = link.followSymLink();
      absoluteName = realFileName.absoluteName();
    } else {
      absoluteName = filename;
    }
    
    ms = casa::MeasurementSet (absoluteName);
    
  } else {

    /*____________________________________________
      Create new MeasurementSet
    */
    
    unsigned int nofColumns (10);
    // create table descriptor
    casa::TableDesc simpleDesc (casa::MS::requiredTableDesc());
    // set up a new table
    casa::SetupNewTable newTab (filename,
				simpleDesc,
				casa::Table::New);
    // create the new MeasurementSet
    ms = casa::MeasurementSet (newTab, nofColumns);
    // create the required sub-tables
    ms.createDefaultSubtables(casa::Table::New);
    ms.flush();
    
  }
  
    /*____________________________________________
      Summary of created MeasurementSet
    */
    
  cout << "-- Filename            = " << filename                   << endl;
  cout << "-- File exists         = " << fileExists                 << endl;
  cout << "-- Absolute filename   = " << absoluteName               << endl;
  cout << "-- Feed table          = " << ms.feedTableName()         << endl;
  cout << "-- Field table         = " << ms.fieldTableName()        << endl;
  cout << "-- Polarization table  = " << ms.polarizationTableName() << endl;
  
  return nofFailedTests;
}

//_______________________________________________________________________________
//                                                                      test_open

int test_open (std::string const &filename)
{
  cout << "\n[tcasacore_ms::test_open]" << endl;
  
  int nofFailedTests = 0;
  std::string absoluteName;
  casa::File msfile (filename);
  
  /*________________________________________________________
    Check if the file exists; if not, then exit function.
  */
  
  if (!msfile.exists()) {
    std::cerr << "ERROR: MeasurementSet " << filename << " does not exist!" << endl;
    return 1;
  }
  
  /*________________________________________________________
    Check if the filename is a symbolic link; of this is the
    case, then resolve the link before opening the dataset.
  */
  
  if (msfile.isSymLink()) {
    casa::SymLink link (msfile);
    casa::Path realFileName = link.followSymLink();
    absoluteName = realFileName.absoluteName();
  } else {
    absoluteName = filename;
  }
  
  /*______________________________________________________
    Use MS-specific classes to access data
  */

  std::cout << "\n[1] Use MS-specific classes to access data ..." << std::endl;

  try {
    // Create the MeasurementSet from an existing Table on disk
    casa::MeasurementSet ms (absoluteName); 
    // Create a columns object that accesses the data in the specified Table. 
    casa::ROMSMainColumns mainColumns (ms);
    // Create object to hold 'TIME' column
    casa::ROScalarColumn<casa::Double> timeColumn = mainColumns.time ();
    // Create object to hold 'UVW' column
    casa::ROArrayColumn<casa::Double> uvwColumn = mainColumns.uvw ();
    // Create object to hold 'DATA' column
    casa::ROArrayColumn<casa::Complex> dataColumn = mainColumns.data ();
    
    cout << "-- Filename            = " << filename                   << endl;
    cout << "-- Absolute filename   = " << absoluteName               << endl;
    cout << "-- Feed table          = " << ms.feedTableName()         << endl;
    cout << "-- Field table         = " << ms.fieldTableName()        << endl;
    cout << "-- Polarization table  = " << ms.polarizationTableName() << endl;
    cout << "-- 'TIME' : nof. rows  = " << timeColumn.nrow()          << endl;
    cout << "-- 'UVW'  : nof. rows  = " << uvwColumn.nrow()           << endl;
    cout << "-- 'UVW'  : cell shape = " << uvwColumn.shape(0)         << endl;
    cout << "-- 'DATA' : nof. rows  = " << dataColumn.nrow()          << endl;
    cout << "-- 'DATA' : cell shape = " << dataColumn.shape(0)        << endl;
    
  } catch (casa::AipsError x) {
    std::cerr << "ERROR: " << x.getMesg() << endl;
    ++nofFailedTests;
  }
  
  /*________________________________________________________
    Use generic Table classes to access data
  */

  std::cout << "\n[2] Use generic Table classes to access data ..." << std::endl;

  try {
    casa::Vector<casa::Double> tmp;

    // Open table
    casa::Table table (absoluteName);
    // Retrieve table description
    casa::TableDesc tableDesc = table.tableDesc ();
    // Retrieve the names of the table columns
    casa::Vector<casa::String> columnNames = tableDesc.columnNames();

    // Provide basic overview of table properties
    cout << "-- Name of the table   = " << table.tableName()  << endl;
    cout << "-- nof. table rows     = " << table.nrow()       << endl;
    cout << "-- Column descriptions : " << std::endl;
    // Loop through the columns and get their properties
    for (unsigned int n=0; n<columnNames.nelements(); ++n) {
      // Get column description
      casa::ColumnDesc columnDesc = tableDesc.columnDesc(columnNames(n));
      // Display column properties
      std::cout << std::setw(5)  << n 
		<< std::setw(25) << columnDesc.name()
		<< std::setw(5)  << columnDesc.ndim()
		<< std::setw(10) << columnDesc.dataType()
		<< std::setw(10) << columnDesc.isScalar()
		<< std::setw(10) << columnDesc.isArray()
		<< std::setw(10) << columnDesc.isTable()
		<< std::setw(10) << columnDesc.shape()
		<< std::endl;
    }

    // Access contents of the 'TIME' column
    casa::ROScalarColumn<casa::Double> timeColumn (table , "TIME");
    // Get the times for the entire column
    casa::Vector<casa::Double> timeColumnData = timeColumn.getColumn();

    std::cout << "-- Column 'TIME' : " << std::endl;
    std::cout << "   nof. elements = " << timeColumnData.nelements() << std::endl;
    std::cout << "   Minimum value = " << min(timeColumnData) << std::endl;
    std::cout << "   Maximum value = " << max(timeColumnData) << std::endl;

    // Access contents of the 'UVW' column
    casa::ROArrayColumn<casa::Double> uvwColumn (table , "UVW");
    // Get the times for the entire column
    casa::Array<casa::Double> uvwColumnData = uvwColumn.getColumn();

    std::cout << "-- Column 'UVW' : " << std::endl;
    std::cout << "   nof. elements = " << uvwColumnData.nelements() << std::endl;
    std::cout << "   shape(data)   = " << uvwColumnData.shape()     << std::endl;

    for (int col=0; col<10; ++col) {

      tmp = uvwColumnData(casa::Slicer(casa::IPosition(2,0,col),
				       casa::IPosition(2,casa::Slicer::MimicSource,1)));
	
      std::cout << "   uvw(," << col << ")       = " << tmp << std::endl;
    }
    
  } catch (casa::AipsError x) {
    std::cerr << "ERROR: " << x.getMesg() << endl;
    ++nofFailedTests;
  }

  return nofFailedTests;
}

//_______________________________________________________________________________
//                                                                           main

/*!
  \brief Main routine of the test program

  \return nofFailedTests -- The number of failed tests encountered within and
          identified by this test program.
*/
int main (int argc, char *argv[])
{
  int nofFailedTests   = 0;
  bool haveDataset     = false;
  std::string filename = "tcasacore_ms.ms";

  //________________________________________________________
  // Process parameters from the command line
  
  if (argc > 1) {
    filename    = std::string(argv[1]);
    haveDataset = true;
  }

  //________________________________________________________
  // Run the tests

  if (haveDataset) {
    nofFailedTests += test_open (filename);
  }

  nofFailedTests += test_open_create ();
  
  return nofFailedTests;
}
