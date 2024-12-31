// functions are repeatable reusable pieces of useful code
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
void InitXX();
void OpenLog();
void OpenLogn();
void CloseLog();
void OpenErr();
void OpenErrn();
void CloseErr();
void OpenStat();
void OpenStatn();
void CloseStat();

// f-key actions and or primary command actions
void Report();
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
void ChangeIt();
void ChangeOver();
void ChangeOverShort();
void ChangeOverLong();
void eXclude();
void Reset();
void WipeCommand();
void Create();
void CreateFile();
void CreateTable();
void TrimFile();
void GetEndl();
void SetEndl();
void PageofPage();

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
void LookForLC();
void LCReasonability();
void Capture();
void Ranges();
void ApplyCommands();

void LCReasonabilityBlock();
void LCReasonabilityBlockMM();
void LCReasonabilityLine();
void LCReasonabilityOverall();
void Continue();

void LookForLCCC();
void LookForLCDD();
void LookForLCMM();
void LookForLCOO();
void LookForLCRR();
void LookForLCSR();
void LookForLCSL();
void LookForLCXX();
void LookForFF();
void CaptureFF();
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
void MoveOverOver();
void MoveBlockOver();
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
std::string ToString(int);  /*  annoying that you can assign a char array to a string
                                but not a string to a char array
                                something about pointers and lvalues and rvalues - C++ is funny */
// functions related to processing a file - command line actions
void CopyFile();
void OpenFile();
void SaveFile();
void SaveAsFile();
void Exit();

void CLEditCFmsg();
// functions related to database processing
void FromStage();
void ToStage();
// functions related to SORT processing
void SortSM();
void SortArea();
int BiSearch();
