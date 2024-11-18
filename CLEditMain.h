// the purpose of this program is to Edit a file in manner similar to IBM TSO Edit with some twists taken from B.I. Moyle
#include "CLEditCF.h"
#include "CLEditDB.h"
#include <wx/wx.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <algorithm>
#include <ctype.h>
using namespace std;
class CLEditFrame : public wxFrame
{

    public:

// logging and error messages
        std::fstream LogFile;
        std::fstream ErrFile;

// a frame is a window

        CLEditFrame(const wxString & title);

//controls
        wxPanel      * Panel;
        wxTextCtrl   * Command;
        wxButton     * Apply;

        struct Screen
        {
            wxTextCtrl * Line;  // line command action
            wxTextCtrl * Code;  // text
        };
        Screen CL[50];


// variables
// Command

        std::string CurrentFile;    // the name of the file currently being edited
        char        Byte;           // do nothing - like a continue *here
        int         ypos;           // Y position
        int         pos;            // search position
        int         strpos;         // start position
        int         Mstrl;          // length of Move string
        int         Ostrl;          // length of Overlay string
        int         posp1;          // search position plus 1 - next byte
        std::string str;            // common string
        int         i;              // index into string
        int         wi;             // index into work string
        int         l;              // index other

        std::string FindStr;        // find string
        int         res;            // result of STD::STRING::FIND
        int         FindCnt;        // number of times string found
        int         MinusOne;       // a constant easier to understand than STD::STRING::NPOS
        int         f;              // index into found string locations
        bool        OnOne;          // trigger for first time
        int         prevf;          // previously found string location

        std::string ChangeFrom;     // change from string
        int         ChangeFroml;    // change from string length
        std::string ChangeLineT;    // change line to string
        int         ChangeLineTl;   // change line to string length
        std::string ChangeLineF;    // change line from string
        int         ChangeLineFl;   // change line from string length
        int         ChngCnt;        // number of times change from string found
        int         tf;             // index into change from found string locations
        bool        OnOnetf;        // trigger for first time
        int         prevtf;         // previously found string location
        std::string ChangeTo;       // change to string
        int         ChangeTol;      // change to string length
//
        int         Commandl;           // the length of the command line string
        wxString    Commandstr;         // the command string
        wxString    PrimaryCommand;     // the Primary command
        wxString    FirstParameter;     // the first parameter
        wxString    SecondParameter;    // the second parameter
        wxString    ThirdParameter;     // the third parameter

// this is the "screen"
// Line
// Code
        int u;
        struct Userinput
        {
            int Linel;          // line command string length
            wxString Linestr;   // line command string
            int Codel;          // Code string length
            wxString Codestr;   // Code string
        };
        Userinput Input[50];    // 50 lines on the screen
        Userinput uInput;       // a single line

        int         UserLinel;      // line command string length
        wxString    UserLinestr;    // line command string
        int         UserCodel;      // Code string length
        wxString    UserCodestr;    // Code string

// frstl is the index to the file in process - it is where we start the display
        int         frstl;
        int         lastl;

// to make the line command area pretty "000010"
//      ostringstream os;     defined local scope because otherwise it concatenates
        int         prettyint;  // STD::OSTRINGSTREAM::SETW number to output
        std::string prettystr;  // result string from STD::OSTRINGSTREAM::SETW

// error / logging
        bool        Return;     // return code

        std::string ReturnFunction;     // the name of the function running
        std::string ReturnCode;         // a return code
        std::string ReturnMessage;      // a meaningful return message

// the file being processed
        bool FileSizeError;     // file size error - exceeds 25000 lines
        bool haveaFile;         // are we starting with blank screen or did we open or stage a file
        struct InputFile
        {
            std::string IFlc;       // line command
            std::string IFCode;     // the line of code
        };
        InputFile inputfile[25000];  // 23,000 line is the biggest single block of code I've ever seen aka "203"

// the work file being processed
        int wfilecnt;
        int oldwfilecnt;
        struct wInputFile
        {
            std::string wIFlc;      // line command string
            std::string wIFCode; // the line of code
        };
        wInputFile winputfile[25000];  // 23,000 line is the biggest single block of code I've ever seen aka "203"


// a line to be Copied
        int haveaC;
        struct cInputFile
        {
            std::string cIFCode;    // Code string
        };
        cInputFile cinputfile;
// a block of lines to be Copied
        bool haveaCC;
        cInputFile ccinputfile[2000];  // a reasonable block copy would be what you can see on the current screen -


// a line to be Moved
        int haveaM;
        struct mInputFile
        {
            std::string mIFCode;    // Code string
        };
        mInputFile minputfile;
// a block of lines to be Moved
        bool haveaMM;
        mInputFile mminputfile[2000]; // a reasonable block move would be what you can see on the current screen


// a line to be Overlaid
        int haveaO;
        struct oInputFile
        {
            std::string oIFCode;    // Code string
        };
        oInputFile oinputfile;
// a block of lines to be Overlaid
        bool haveaOO;
        oInputFile ooinputfile[2000]; // a reasonable block overlay would be what you can see on the current screen

// a line to be Repeated
        int haveaR;
        struct rInputFile
        {
            std::string rIFCode; // the line of code
        };
// a block of lines to be Repeated
        bool haveaRR;
        rInputFile rrinputfile[2000]; // a reasonable block overlay would be what you can see on the current screen

// index to found strings - find
        struct FindFile
        {
            int index;
            int pos;
        };
        FindFile FF[25000];  // not at all likely

// index to found strings - change from
        struct ChngFile
        {
            int index;
            int pos;
        };
        ChngFile TF[25000];  // not at all likely

// line command trackers
//      bool singleA;  // single After
        int  afters;   // single or multiple Afters
//      bool singleB;  // single Before
        int  befores;  // single or multiple Before
        int  LCcnt;

        int  CCcnt;     // number of block Copy lines requests
        int  CCstart;   // index to the first CC line in the block
        int  CCend;     // index to the last CC line in the block
        int  CCrows;    // how many rows in the Copy block
        int  singleC;   // Copy a line - need Before(s) or After(s)
        bool blockCC;   // Copy a block - need Before(s) or After(s) - can be used in a Create

        int  DDcnt;     // number of Block Delete lines requests
        int  DDstart;   // index to the first DD line in the block
        int  DDend;     // index to the last DD line in the block
//      int  DDrows;    // how many rows in the Delete block - no need to capture them, we just need to know where they are, they are being discarded
        int  singleD;   // Delete a line
        bool blockDD;   // Delete a block of lines

        int  singleI;   // Insert a blank line

        int  MMcnt;     // number of block Move lines requests
        int  MMstart;   // index to the first MM line in the block
        int  MMend;     // index to the last MM line in the block
        int  MMrows;    // how many rows in the Move block
        int  singleM;   // Move a line - need Before(s) or After(s)
        bool blockMM;   // Move a block of lines - need Before(s) or After(s)

        int  OOcnt;     // number of Overlay lines requests
        int  OOstart;   // index to the first OO line in the block
        int  OOend;     // index to the last OO line in the block
        int  OOrows;    // how many rows in the Overlay block - must match MMrows.
        int  singleO;   // Overlay a line - needs single Move
        bool blockOO;   // Overlay a block of lines - needs a Block Move

        int  RRcnt;     // number of Repeat lines requests
        int  RRstart;   // index to the first RR line in the block
        int  RRend;     // index to the last RR line in the block
        int  RRrows;    // how many rows in the Repeat block
        int  singleR;   // Repeat a line
        bool blockRR;   // Repeat a block of lines

        int  SRcnt;     // number of Shift Right lines requests
        int  SRstart;   // index to the first SR line in the block
        int  SRend;     // index to the last SR line in the block
//      int  SRrows;    // how many rows in the Shift Right block - no need to capture them, we just need to know where they are, they are being Shifted Right
        int  singleSR;  // Right Shift a line ">" - needs a number of characters (default is one space)
        int  SRi;       // number of characters to Shift Right
        bool blockSR;   // Rght Shift a block of lines ">>" - needs a number of characters (default is one space)
        int  SRl;       // length of the string to be Shifted Right

        int  SLcnt;     // number of Shift Left lines requests
        int  SLstart;   // index to the first SL line in the block
        int  SLend;     // index to the last SL line in the block
//      int  SLrows;    // how many rows in the Shift Left block - no need to capture them, we just need to know where they are, they are being Shifted Left
        int  singleSL;  // left shift a line "<" - needs a number of characters (default is one space)
        int  SLi;       // number of characters to shift left
        bool blockSL;   // left shift a block of lines - needs a number of characters (default is one space)
        int  SLl;       // length of the string to be Shifted Left

        int  XXcnt;     // number of Exclude line requests
        int  XXstart;   // index to the first XX line in the block
        int  XXend;     // index to the last XX line in the block
//      int  XXrows;    // how many rows in the Exclude block - no need to capture them, we just need to know where they are, they are being Excluded from view & changes
        int  singleX;   // Exclude a line
        bool blockXX;   // Exclude a block of lines

        bool changes;           // did anything on the screen change - effects scrolling
        bool changesapplied;    // did the changes get applied - might be incomplete request
        bool badchanges;        // requested changes didn't make sense
// Logic
// basics
        void Initialize();
        void InitScreen();
        void InitUser();
        void InitCTrackers();
        void InitIF();
        void InitWIF();
        void InitCC();
        void InitMM();
        void InitOO();
        void InitRR();
        void InitCF();
        void InitDB();
        void InitFF();
        void InitTF();

// f-key actions and or primary command actions
        void Find();
        void FindNext();
        void Bottom();
        void Home();
        void Up();
        void Down();
        void Help();
        void Change();
        void ChangeFind();
        void ChangeNext();
        void ChangeAll();
        void ChangeOver();
        void ChangeOverShort();
        void ChangeOverLong();
        void Reset();
        void WipeCommand();
        void Create();
        void CreateFile();
        void CreateTable();
        void TrimFile();
        void SetEndl();
        void GetEndl();

// event handlers
        void OnKeyDown(wxKeyEvent & event);
        void OnApplyClicked(wxCommandEvent & event);
// functions
        void OnTerminal();
        void CreateControls();

// process Command
        void FindPrimary();
        void FindFirst();
        void FindSecond();
        void FindThird();
// process screen
        void ProcessScreen();
        void ReadScreen();

        void WhatCommand();
        void WhatCommandA();    // after(s)
        void WhatCommandB();    // before(s)
        void WhatCommandCC();   // Copy a line or Block
        void WhatCommandDD();   // Delete a line or Block
        void WhatCommandMM();   // Move a line or Block
        void WhatCommandOO();   // Overlay a line or Block
        void WhatCommandRR();   // Repeat a line or Block
        void WhatCommandSR();   // Right Shift a line of Block (like a TAB right)
        void WhatCommandSL();   // Left Shift a line or Block (like TAB left)
        void WhatCommandXX();   // Exclude a line or Block from view
        void WhatCommandI();    // Insert a line

        void LookForChanges();
        void ApplyChanges();
        void ApplyBlockCommands();
        void LCReasonability();
        void LCReasonabilityBlock();
        void LCReasonabilityBlockMM();
        void LCReasonabilityLine();
        void LCReasonabilityOverall();
        void LookForLC();
        void LookForLCCC();
        void LookForLCDD();
        void LookForLCMM();
        void LookForLCOO();
        void LookForLCRR();
        void LookForLCSR();
        void LookForLCSL();
        void LookForLCXX();
        void LookForFF();
        void LookForTF();

        void CaptureLC();
// Copy
        void LookForCC();
        void CaptureCC();
        void ApplyCC();
        void LineCopy();
        void BlockCopy();
// Delete
        void LookForDD();
//      void CaptureDD(); - applied directly
        void ApplyDD();
        void LineDelete();
        void BlockDelete();
// Move
        void LookForMM();
        void CaptureMM();
        void ApplyMM();
        void LineMove();
        void BlockMove();
// Overlay
        void LookForOO();
        void CaptureOO();
        void ApplyOO();
        void LineOver();
        void BlockOver();
        void BlockMoveOver();
        void LinePushOver();
        void BlockPushOver();
// Repeat
        void LookForRR();
        void CaptureRR();
        void ApplyRR();
        void LineRepeat();
        void BlockRepeat();
// Shift Right
        void LookForSR();
//      void CaptureSR(); - applied directly
        void ApplySR();
        void LineSR();
        void BlockSR();
        void ShiftRight();
// Shift Left
        void LookForSL();
//      void CaptureSL(); - applied directly
        void ApplySL();
        void LineSL();
        void BlockSL();
        void ShiftLeft();
// Exclude
        void LookForXX();
//      void CaptureXX(); - applied to view
        void ApplyXX();
// Insert
        void ApplyI();
        void LineInsert();

        void RefreshInput(); // from work to input
        void CopyTheLine(); // the same 3 assignments used everywhere

        void LoadScreen();
        void FocusLine();
        std::string ToString(int);  //annoying that you can assign a char array to a string but not a string to a char array - something about pointers and lvalues and rvalues - C++ is dumb

// file processing
// this is an instance of a class to process a file
        CLEditCF CF;
        int CLEditCFrc;

// functions related to processing a file - command line actions
        void CopyFile();
        void OpenFile();
        void SaveFile();
        void SaveAsFile();
        void Exit();

        void CLEditCFmsg();

// database processing
// this is an instance of a class to access the database
        CLEditDB DB;
        int rowcnt;
        int CLEditDBrc;

// functions related to database processing
        void FromStage();
        void ToStage();

    protected:

    private:

        wxDECLARE_EVENT_TABLE();

};
