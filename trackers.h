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
