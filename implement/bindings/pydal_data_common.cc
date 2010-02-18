
// DAL headers
#include "dal.h"
#include "dalCommon.h"
#include "CommonAttributes.h"
#include "Filename.h"
#include "Timestamp.h"
#include "SAS_Settings.h"
#include "HDF5Hyperslab.h"

// Boost.Python headers
#include <boost/python.hpp>

// Namespace usage
using namespace DAL;

//_____________________________________________________________________________
//                                                             CommonAttributes

void export_CommonAttributes () 
{
  bpl::class_<CommonAttributes>("CommonAttributes")
    .def( bpl::init<>())
    .def( bpl::init<Filename,string,string>())
    .def( "groupType", &CommonAttributes::groupType,
	  "Get the LOFAR group type.")
    .def( "filename", &CommonAttributes::filename,
	  "Get the name of the file.")
    .def( "setFilename", &CommonAttributes::setFilename,
	  "Set the name of the file.")
    .def( "filetype", &CommonAttributes::filetype,
	  "Get the type of the file.")
    .def( "setFiletype", &CommonAttributes::setFiletype,
	  "Set the type of the file.")
    .def( "filedate", &CommonAttributes::filedate,
	  "Get the file creation date.")
    .def( "setFiledate", &CommonAttributes::setFiledate,
	  "Set the file creation date.")
    .def( "telescope", &CommonAttributes::telescope,
	  "Get the name of the telescope.")
    .def( "setTelescope", &CommonAttributes::setTelescope,
	  "Set the name of the telescope.")
    .def( "projectID", &CommonAttributes::projectID,
	  "Get the unique identifier for the project.")
    .def( "setProjectID", &CommonAttributes::setProjectID,
	  "Set the unique identifier for the project.")
    .def( "projectTitle", &CommonAttributes::projectTitle,
	  "Get the name of the project.")
    .def( "setProjectTitle", &CommonAttributes::setProjectTitle,
	  "Set the name of the project.")
    .def( "projectPI", &CommonAttributes::projectPI,
	  "Get the name of the project's principal investigator.")
    .def( "setProjectPI", &CommonAttributes::setProjectPI,
	  "Set the name of the project's principal investigator.")
    ;
}

//_______________________________________________________________________________
//                                                                       Filename

void export_Filename ()
{
  /* Enumeration: File type */
  bpl::enum_<Filename::FileType>("FileType")
    .value("uv",Filename::uv)
    .value("sky",Filename::sky)
    .value("rm",Filename::rm)
    .value("nfi",Filename::nfi)
    .value("dynspec",Filename::dynspec)
    .value("bf",Filename::bf)
    .value("tbb",Filename::tbb)
    ;
  
  /* Enumeration: File extension */
  bpl::enum_<Filename::FileExtension>("FileExtension")
    .value("MS",Filename::MS)
    .value("h5",Filename::h5)
    .value("fits",Filename::fits)
    .value("log",Filename::log)
    .value("parset",Filename::parset)
    .value("lsm",Filename::lsm)
    .value("IM",Filename::IM)
    .value("PD",Filename::PD)
    .value("vds",Filename::vds)
    .value("gds",Filename::gds)
    .value("conf",Filename::conf)
    ;
  
  bpl::class_<Filename>("Filename")
    .def( bpl::init<>())
    .def( bpl::init<string,string,Filename::FileType,Filename::FileExtension>())
    .def( "observationID", &Filename::observationID,
	  "Get the unique observation ID.")
    .def( "setObservationID", &Filename::setObservationID,
	  "Set the unique observation ID.")
    .def( "optionalDescription", &Filename::optionalDescription,
	  "Get optional descriptors.")
    .def( "setOptionalDescription", &Filename::setOptionalDescription,
	  "Set optional descriptors.")
    .def( "filetype", &Filename::filetype,
	  "Get the file type.")
    .def( "filetypeName", &Filename::filetypeName,
	  "Get the file type name.")
    .def( "setFiletype", &Filename::setFiletype,
	  "Set the file type.")
    .def( "extension", &Filename::extension,
	  "Get the file extension type.")
    .def( "extensionName", &Filename::extensionName,
	  "Get the file extension name.")
    .def( "setExtension", &Filename::setExtension,
	  "Set the file extension type.")
    .def( "filename", &Filename::filename,
	  "Get the name of the file.")
    ;
}

  //_____________________________________________________________________________
  //                                                                    Timestamp
  
void export_Timestamp () 
{
  /* Enumeration: Month of the year */
  bpl::enum_<Timestamp::Month>("Month")
    .value("Jan",Timestamp::Jan)
    .value("Feb",Timestamp::Feb)
    .value("Mar",Timestamp::Mar)
    .value("Apr",Timestamp::Apr)
    .value("May",Timestamp::May)
    .value("Jun",Timestamp::Jun)
    .value("Jul",Timestamp::Jul)
    .value("Aug",Timestamp::Aug)
    .value("Sep",Timestamp::Sep)
    .value("Oct",Timestamp::Oct)
    .value("Nov",Timestamp::Nov)
    .value("Dec",Timestamp::Dec)
    ;
  
  bpl::class_<Timestamp>("Timestamp")
    .def( bpl::init<>())
    .def( bpl::init<int,int,int,int,int,double>())
    .def( "year", &Timestamp::year,
	  "Get the numerical value of the year.")
    .def( "setYear", &Timestamp::setYear,
	  "Set the numerical value of the year.")
    .def( "month", &Timestamp::month,
	  "Get the numerical value of the month.")
    .def( "setMonth", &Timestamp::setMonth1,
	  "Set the numerical value of the month.")
    .def( "setMonth", &Timestamp::setMonth2,
	  "Set the numerical value of the month.")
    .def( "day", &Timestamp::day,
	  "Get the numerical value of the day.")
    .def( "setDay", &Timestamp::setDay,
	  "Set the numerical value of the day.")
    .def( "hour", &Timestamp::hour,
	  "Get the numerical value of the hour.")
    .def( "setHour", &Timestamp::setHour,
	  "Set the numerical value of the hour.")
    .def( "minute", &Timestamp::minute,
	  "Get the numerical value of the minute.")
    .def( "setMinute", &Timestamp::setMinute,
	  "Set the numerical value of the minute.")
    .def( "second", &Timestamp::second,
	  "Get the numerical value of the second.")
    .def( "setSecond", &Timestamp::setSecond,
	  "Set the numerical value of the second.")
    .def( "fractionOfSecond", &Timestamp::fractionOfSecond,
	  "Get the fraction of the second.")
    .def( "dayOfWeek", &Timestamp::dayOfWeek,
	  "Get the name of the day of the week.")
    .def( "ymd", &Timestamp::ymd,
	  "Get string combining year, month and day.")
    .def( "hms", &Timestamp::hms,
	  "Get the time of day.")
    .def( "iso8601", &Timestamp::iso8601,
	  "Retrieve ISO 8601 conform version of the timestamp string.")
    .def( "rfc2822", &Timestamp::rfc2822,
	  "Retrieve RCF 2822 conform version of the timestamp string.")
    ;
}

  //_____________________________________________________________________________
  //                                                                 SAS_Settings

void export_SAS_Settings () 
{
  bpl::class_<SAS_Settings>("SAS_Settings")
    .def( bpl::init<>())
    .def( "className", &SAS_Settings::className,
	  "Get the name of the class.")
    .def( "antennaSet", &SAS_Settings::antennaSet,
	  "Get the values for the AntennaSet field in SAS.")
    .def( "antennaSet", &SAS_Settings::antennaSet,
	  "Get the values for the AntennaSet field in SAS.")
    .def( "haveAntennaSet", &SAS_Settings::haveAntennaSet,
	  "Is name a valid value for the AntennaSet field in SAS?")
    .def( "filterSelection", &SAS_Settings::filterSelection,
	  "Get the values for the FilterSelection field in SAS.")
    .def( "haveFilterSelection", &SAS_Settings::haveFilterSelection,
	  "Is name a valid value for the AntennaSet field in SAS?")
    ;  
}
  
  //_____________________________________________________________________________
  //                                                                HDF5Hyperslab

void export_HDF5Hyperslab ()
{
  bpl::class_<HDF5Hyperslab>("HDF5Hyperslab")
    .def( bpl::init<>())
    .def( "className", &HDF5Hyperslab::className,
	  "Get the name of the class.")
    .def( "shape", &HDF5Hyperslab::shape,
	  "Get the shape of the array to which the hyperslab is applied.")
    .def( "start", &HDF5Hyperslab::start,
	  "Get the offset of the starting element of the specified hyperslab.")
    .def( "setStart", &HDF5Hyperslab::setStart,
	  "Set the offset of the starting element of the specified hyperslab.")
    .def( "stride", &HDF5Hyperslab::stride,
	  "Get the number of elements to separate each element or block.")
    .def( "setStride", &HDF5Hyperslab::setStride,
	  "Set the number of elements to separate each element or block.")
    .def( "count", &HDF5Hyperslab::count,
	  "Get the number of elements or blocks to select along each dimension.")
    .def( "setCount", &HDF5Hyperslab::setCount,
	  "Set the number of elements or blocks to select along each dimension.")
    .def( "block", &HDF5Hyperslab::block,
	  "Get the size of the element block selected from the dataspace.")
    .def( "setBlock", &HDF5Hyperslab::setBlock,
	  "Set the size of the element block selected from the dataspace.")
    ; 
}
