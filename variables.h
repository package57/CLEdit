// variables
// characters
char Byte;          // do nothing - like a continue *here
// integers
int u;              // index into user input
int ypos;           // Y position up/down
int xpos;            // X position left/right
int pos;            // search position
int strpos;         // start position
int Mstrl;          // length of Move string
int Ostrl;          // length of Overlay string
int posp1;          // search position plus 1 - next byte
int i;              // index into current file or string
int wi;             // index into work string
int l;              // index other
int left;           // lower bound of array
int right;          // upper bound of array
int mid;            // location of 'key' if found
int res;            // result of STD::STRING::FIND
int FindCnt;        // number of times string found
int MinusOne;       // a constant easier to understand than STD::STRING::NPOS
int f;              // index into found string locations
int prevf;          // previously found string location
int ChangeFroml;    // change from string length
int ChangeLineTl;   // change line to string length
int ChangeLineFl;   // change line from string length
int ChngCnt;        // number of times change from string found
int tf;             // index into change from found string locations
int prevtf;         // previously found string location
int ChangeTol;      // change to string length
int Commandl;       // the length of the command line string
int CLEditCFrc;     // return code from CF
int rowcnt;         // number of rows from stage
int CLEditDBrc;     // return code from DB
int UserLinel;      // line command string length
int UserCodel;      // Code string length
int frstl;          // the first line to the screen
int lastl;          // the last line to the screen
int wfilecnt;       // the number of records in the current file
int oldwfilecnt;    // temp file record count
int page;           // page number
int ofpage;         // number of pages
int pgs;            // whole number of pages
int FindStrl;       // length of a search string
int WorkStrl;       // length of the work string
float pgsf;         // fractional pages
float wfilecntf;
// to make the line command area pretty "000010"
//      ostringstream os;     defined local scope because otherwise it concatenates
int prettyint;  // STD::OSTRINGSTREAM::SETW number to output
int haveaC;
int haveaM;
int haveaO;
int haveaR;

// strings
std::string CurrentFile;    // the name of the file currently being edited
std::string str;            // common string
std::string key;            // key value to search for
std::string FindStr;        // find string
std::string ChangeFrom;     // change from string
std::string ChangeLineT;    // change line to string
std::string ChangeLineF;    // change line from string
std::string ChangeTo;       // change to string
std::string prettystr;      // result string from STD::OSTRINGSTREAM::SETW
std::string ReturnFunction; // the name of the function running
std::string ReturnCode;     // a return code
std::string ReturnMessage;  // a meaningful return message
std::string WorkStr;         // a work string

// boolian
bool FileSizeError;  // file size error - exceeds 25000 lines
bool haveaFile;      // are we starting with blank screen or did we open or stage a file
bool haveaCC;
bool haveaMM;
bool haveaOO;
bool haveaRR;
bool Return;         // return code
