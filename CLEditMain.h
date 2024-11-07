// the purpose of this program is to Edit a file in manner similar to IBM TSO Edit with some twists taken from B.I. Moyle
#include "CLEditCF.h"
#include "CLEditDB.h"
#include <wx/wx.h>
#include <iostream>
#include <iomanip>
#include <sstream>
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

        std::string CurrentFile;
        char        Byte;
        int         ypos;
        int         strpos;
        int         i;
        int         posp1;
        int         Commandl;
        wxString    Commandstr;
        wxString    PrimaryCommand;
        wxString    FirstParameter;
        wxString    SecondParameter;
        wxString    ThirdParameter;

// this is the "screen"
// Line
// Code
        int u;
        struct Userinput
        {
            int Linel;
            wxString Linestr;
            int Codel;
            wxString Codestr;
        };
        Userinput Input[50];
        Userinput uInput;

        int         UserLinel;
        wxString    UserLinestr;   // action
        int         UserCodel;
        wxString    UserCodestr;   // text

// frstl is the index to the file in process - it is where we start the display
        int         frstl;
        int         lastl;

// to make the line command area pretty "000010"
//      ostringstream os;     defined local because otherwise it concatenates
        int         prettyint;
        std::string prettystr;

// error / logging
        bool        Return;

        std::string ReturnFunction;
        std::string ReturnCode;
        std::string ReturnMessage;

// the file being processed
        bool haveaFile;
        struct InputFile
        {
            std::string IFlc;   // exclude process!
            std::string IFCode; // the line of code
        };
        InputFile inputfile[25000];  // 23,000 line is the biggest single block of code I've ever seen aka "203"

// the work file being processed
        int wfilecnt;
        struct wInputFile
        {
            std::string wIFlc;   // line command action
            std::string wIFCode; // the line of code
        };
        wInputFile winputfile[25000];  // 23,000 line is the biggest single block of code I've ever seen aka "203"


// a line to be Copied
        bool haveaC;
        struct cInputFile
        {
            std::string cIFCode; // the line of code
        };
        cInputFile cinputfile;
// a block of lines to be Copied
        bool haveaCC;
        cInputFile ccinputfile[2000];  // a reasonable block copy would be what you can see on the current screen -


// a line to be Moved
        bool haveaM;
        struct mInputFile
        {
            std::string mIFCode; // the line of code
        };
        mInputFile minputfile;
// a block of lines to be Moved
        bool haveaMM;
        mInputFile mminputfile[2000]; // a reasonable block move would be what you can see on the current screen


// a line to be Overlaid
        bool haveaO;
        struct oInputFile
        {
            std::string oIFCode; // the line of code
        };
        oInputFile oinputfile;
// a block of lines to be Overlaid
        bool haveaOO;
        oInputFile ooinputfile[2000]; // a reasonable block overlay would be what you can see on the current screen


// a line to be Repeated
        bool haveaR;
        struct rInputFile
        {
            std::string rIFCode; // the line of code
        };
        rInputFile rinputfile;
// a block of lines to be Repeated
        bool haveaRR;
        rInputFile rrinputfile[2000]; // a reasonable block overlay would be what you can see on the current screen

// line command trackers
/*        bool singleA;  // single After
        int  afters;   // multiple Afters
        bool singleB;  // single Before
        int  befores;  // multiple Before */
        int  CCcnt;
        bool singleC;  // Copy a line - need Before(s) or After(s)
        bool blockCC;  // Copy a block - need Before(s) or After(s) - can be used in a Create

        int  DDcnt;
        bool singleD;  // Delete a line
        bool blockDD;  // Delete a block of lines

        bool singleI;  // insert a single line - can have a count
        int  Ii;       // number of lines to insert

        int  MMcnt;
        bool singleM;  // Move a line - need Before(s) or After(s)
        bool blockMM;  // Move a block of lines - need Before(s) or After(s)

        int  OOcnt;
        bool singleO;  // Overlay a line - needs single Move
        bool blockOO;  // Overlay a block of lines - needs a block Move

        int  RRcnt;
        bool singleR;  // Repeat a line
        bool blockRR;  // Repeat a block of lines

        int  SRcnt;
        bool singleSR; // right shift a line ">" - needs a number of characters (default is one space)
        int  SRi;      // number of characters to shift right
        bool blockSR;  // right shift a block of lines ">>" - needs a number of characters (default is one space)

        int  SLcnt;
        bool singleSL; // left shift a line "<" - needs a number of characters (default is one space)
        int  SLi;      // number of characters to shift left
        bool blockSL;  // left shift a block of lines - needs a number of characters (default is one space)

        int  XXcnt;
        bool singleX;  // exclude (hide) a line
        bool blockXX;  // exclude (hide) a block of lines

        bool changesapplied;

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

// f-key actions and or command actions
        void Find();
        void Bottom();
        void Home();
        void Up();
        void Down();
        void Help();
        void Change();

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
        void ApplyChanges();
        void LookForCC();
        void ApplyCC();
        void LookForDD();
        void ApplyDD();
        void LookForMM();
        void ApplyMM();
        void LookForOO();
        void ApplyOO();
        void LookForSR();
        void ApplySR();
        void LookForSL();
        void ApplySL();
        void LookForXX();
        void ApplyXX();
        void LoopLine();
        void LoopCode();
        void LoadScreen();
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
