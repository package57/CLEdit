// logging and error messages
std::fstream LogFile;
std::fstream ErrFile;
std::fstream StatFile;

// file processing
// this is an instance of a class to process a file
CLEditCF CF;

// database processing
// this is an instance of a class to access the database
CLEditDB DB;

// SORT
// this is an instance of a class to SORT the current file
CLEditSM SM;

// report
// this is an instance of a class to produce a report
CLEditRP RP;

// key value for reporting
// this is an instance of a class to get a key value
CLEditAR AR;

// gather log data
CLEditXETL ETL;
