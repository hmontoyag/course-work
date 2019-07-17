/* pipe.h: contains all the macros and definition for the pipe type in XINU */

#define MAXPIPES 10
#define PIPE_SIZE 1024

enum pipe_state_t {
	PIPE_FREE,
	PIPE_USED,
	PIPE_CONNECTED,
	PIPE_OTHER,

};

struct pipe_t {
	pipid32 pipid;			    // Pipe ID
	enum pipe_state_t state;	// Pipe state defined by the enum
    // LAB2: TODO: Fill the structure with the fields as required.
    /*789*/
    char buffer[PIPE_SIZE];
    int32 wpos;
    int32 rpos;
    sid32 wsem;
    sid32 rsem;
    int32 ispipereading;
    int32 killing;
    int32 removingwriter;
    
    /*maybe an id for reader and writer procs?*/
    
    /*or actually, a did32 to form the link between devpip and pipes here*/
    did32 bounddev;  //if -1 then no dev?
    pid32 ownerpid;  //if -1, no owner
    pid32 readerpid;  // -1, no reader
    pid32 writerpid;  // - 1, no writer
    /*789*/
};

extern struct pipe_t pipe_tables[MAXPIPES];	// Table for all pipes
