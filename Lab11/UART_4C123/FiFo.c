// FiFo.c
// Runs on LM4F120/TM4C123
// Provide functions that implement the Software FiFo Buffer


#include <stdint.h>
// Declare state variables for FiFo
//        size, buffer, put and get indexes
#define Size 8
#define Fail 0
#define Success 1
char Buffer[Size+1] = {0};
uint32_t PutPt, GetPt, BufCt;

// *********** FiFo_Init**********
// Initializes a software FIFO of a
// fixed size and sets up indexes for
// put and get operations
void FiFo_Init(){
	PutPt = GetPt = BufCt = 0;
}

// *********** FiFo_Put**********
// Adds an element to the FIFO
// Input: Character to be inserted
// Output: 1 for success and 0 for failure
//         failure is when the buffer is full
uint32_t FiFo_Put(char data){
	if(BufCt==Size){
		return Fail;
	}
	Buffer[PutPt] = data;
	PutPt++;
	PutPt = PutPt%Size;
	BufCt++;
	return Success;
}

// *********** FiFo_Get**********
// Gets an element from the FIFO
// Input: Pointer to a character that will get the character read from the buffer
// Output: 1 for success and 0 for failure
//         failure is when the buffer is empty
uint32_t FiFo_Get(char *datapt){
	if(BufCt==0){
		return Fail;
	}
	*datapt = Buffer[GetPt];
	GetPt++;
	GetPt = GetPt%Size;
	BufCt--;
	return Success;
}



