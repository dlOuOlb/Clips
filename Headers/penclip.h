/*------------------------------------------------------------------*/
/*	PenClip is a simple stream I/O library.							*/
/*																	*/
/*	Written by Ranny Clover								Date		*/
/*	http://github.com/dlOuOlb/Clips/					2019.11.08	*/
/*------------------------------------------------------------------*/
/*	Dependency:														*/
/*																	*/
/*	MSVClip ─ MemClip ─ PenClip									*/
/*------------------------------------------------------------------*/
/*	Non-Prefixed Macros:											*/
/*																	*/
/*	_INC_PENCLIP													*/
/*------------------------------------------------------------------*/
/*	Non-Prefixed Types:												*/
/*																	*/
/*	text_08	text_16													*/
/*	TEXT_08	TEXT_16													*/
/*------------------------------------------------------------------*/

#ifndef _INC_PENCLIP
#define _INC_PENCLIP

#include <memclip.h>

#include <stdio.h>
#include <wchar.h>

#if(Fold_(Definition:Primal Types))
MemC_Type_Rename_(char,text_08,TEXT_08);		//PenClip : 8-bit Character
MemC_Type_Rename_(wchar_t,text_16,TEXT_16);		//PenClip : 16-bit Character
#endif

#if(Fold_(Definition:Advanced Types))
//PenClip : String Pointer Union
union _penclip
{
	text_08 *T08;	//PenClip : 8-bit Access
	text_16 *T16;	//PenClip : 16-bit Access
	general *X;		//PenClip : General Access
	address A;		//PenClip : Address Value
};
MemC_Type_Declare_(union,penclip,PENCLIP);	//PenClip : String Pointer Union

//PenClip : String Container Structure
struct _penc_sc
{
	ADDRESS Capacity;	//PenClip : Allowed Size in Bytes
	PENCLIP String;		//PenClip : String Data
};
MemC_Type_Declare_(struct,penc_sc,PENC_SC);	//PenClip : String Container Structure

//PenClip : String Container Lender Structure
struct _penc_sl
{
	GENERAL _PL_ Node;	//PenClip : Internal Node Set
	ADDRESS Chunks;		//PenClip : Total Number of Internal Memory Chunks
	ADDRESS Nodes;		//PenClip : Current Number of Internal Nodes
	ADDRESS Capable;	//PenClip : Current Lendable String Size in Bytes
};
MemC_Type_Declare_(struct,penc_sl,PENC_SL);	//PenClip : String Container Lender Structure
#endif

#if(Fold_(Library Casing))
//PenClip : Library Case Structure
struct _pencase
{
	//PenClip : Library Version
	BYTE_08 _PL_ Version;

	//PenClip : Hello, world!
	const struct
	{
		TEXT_08 _PL_ T08;	//PenClip : "Hello, world!\r\n"
		TEXT_16 _PL_ T16;	//PenClip : L"Hello, world!\r\n"
	}
	Hello;

	//PenClip : Stream I/O Options
	const struct
	{
		//PenClip : Stream Read Options
		const struct
		{
			//PenClip : Stream Read Binary Options
			const struct
			{
				TEXT_08 _PL_ T08;	//PenClip : "rb"
				TEXT_16 _PL_ T16;	//PenClip : L"rb"
			}
			Binary;

			//PenClip : Stream Read Text Options
			const struct
			{
				TEXT_08 _PL_ T08;	//PenClip : "rt"
				TEXT_16 _PL_ T16;	//PenClip : L"rt"
			}
			Text;
		}
		Read;

		//PenClip : Stream Write Options
		const struct
		{
			//PenClip : Stream Write Binary Options
			const struct
			{
				TEXT_08 _PL_ T08;	//PenClip : "wb"
				TEXT_16 _PL_ T16;	//PenClip : L"wb"
			}
			Binary;

			//PenClip : Stream Write Text Options
			const struct
			{
				TEXT_08 _PL_ T08;	//PenClip : "wt"
				TEXT_16 _PL_ T16;	//PenClip : L"wt"
			}
			Text;
		}
		Write;
	}
	Option;

	//PenClip : Character Setting Functions
	const struct
	{
		//PenClip : 8-bit Character Setting
		general(_PL_ T08_)(text_08 _PL_ Buffer,TEXT_08 Value,ADDRESS Count);
		//PenClip : 16-bit Character Setting
		general(_PL_ T16_)(text_16 _PL_ Buffer,TEXT_16 Value,ADDRESS Count);
#define PenC_Set_(Buffer,Value,Count) __dl{switch(sizeof(Value)){case 1:PenC.Set.T08_((text_08*)(Buffer),(text_08)(Value),Count);break;case 2:PenC.Set.T16_((text_16*)(Buffer),(text_16)(Value),Count);break;default:{MemC_Assert_(sizeof(*(Buffer))==sizeof(Value));MemC_Assert_((sizeof(Value)==1)|(sizeof(Value)==2));}}}lb__
	}
	Set;

	//PenClip : Character Finding Functions
	const struct
	{
		//PenClip : 8-bit Character Finding
		text_08*(_PL_ T08_)(text_08 _PL_ Buffer,TEXT_08 Value,ADDRESS Count);
		//PenClip : 16-bit Character Finding
		text_16*(_PL_ T16_)(text_16 _PL_ Buffer,TEXT_16 Value,ADDRESS Count);
	}
	Find;

	//PenClip : String Handling Functions
	const struct
	{
		//PenClip : String Conversion Functions
		//＊Return value is 1 for success, 0 for failure.
		const struct
		{
			//PenClip : Convert from a narrow multi-byte string.
			const struct
			{
				//PenClip : Convert into a wide string.
				logical(_PL_ T16_)(TEXT_08 _PL_ SourceString,text_16 _PL_ TargetString,ADDRESS SourceCapacity,ADDRESS TargetCapacity);
			}
			T08;

			//PenClip : Convert from a wide string.
			const struct
			{
				//PenClip : Convert into a narrow multi-byte string.
				logical(_PL_ T08_)(TEXT_16 _PL_ SourceString,text_08 _PL_ TargetString,ADDRESS SourceCapacity,ADDRESS TargetCapacity);
			}
			T16;
		}
		Conv;

		//PenClip : String Length Functions
		const struct
		{
			//PenClip : 8-bit String Length
			address(_PL_ T08_)(TEXT_08 _PL_ String,ADDRESS Capacity);
			//PenClip : 16-bit String Length
			address(_PL_ T16_)(TEXT_16 _PL_ String,ADDRESS Capacity);
		}
		Length;

		//PenClip : Sub-String Finding Functions
		const struct
		{
			//PenClip : 8-bit Sub-String Finding
			text_08*(_PL_ T08_)(TEXT_08 _PL_ String,TEXT_08 _PL_ SubString);
			//PenClip : 16-bit Sub-String Finding
			text_16*(_PL_ T16_)(TEXT_16 _PL_ String,TEXT_16 _PL_ SubString);
		}
		Find;

		//PenClip : String Copy Functions
		//＊Return value is 1 for success, 0 for failure.
		const struct
		{
			//PenClip : 8-bit String Copy
			logical(_PL_ T08_)(text_08 _PL_ Buffer,TEXT_08 _PL_ Source,ADDRESS Capacity);
			//PenClip : 16-bit String Copy
			logical(_PL_ T16_)(text_16 _PL_ Buffer,TEXT_16 _PL_ Source,ADDRESS Capacity);
		}
		Copy;

		//PenClip : String Concatenation Functions
		//＊Return value is 1 for success, 0 for failure.
		const struct
		{
			//PenClip : 8-bit String Concatenation
			logical(_PL_ T08_)(text_08 _PL_ Buffer,TEXT_08 _PL_ Source,ADDRESS Capacity);
			//PenClip : 16-bit String Concatenation
			logical(_PL_ T16_)(text_16 _PL_ Buffer,TEXT_16 _PL_ Source,ADDRESS Capacity);
		}
		Conc;

		//PenClip : String Comparison Functions
		const struct
		{
			//PenClip : 8-bit String Comparison
			integer(_PL_ T08_)(TEXT_08 _PL_ StringA,TEXT_08 _PL_ StringB);
			//PenClip : 16-bit String Comparison
			integer(_PL_ T16_)(TEXT_16 _PL_ StringA,TEXT_16 _PL_ StringB);
		}
		Comp;
	}
	String;
	
	//PenClip : File Handling Functions
	const struct
	{
		//PenClip : File Open Functions
		const struct
		{
			//PenClip : File Open with 8-bit String - Close with "PenC.File.Closer_"
			FILE*(_PL_ T08_)(TEXT_08 _PL_ FileName,TEXT_08 _PL_ OpeningMode);
			//PenClip : File Open with 16-bit String - Close with "PenC.File.Closer_"
			FILE*(_PL_ T16_)(TEXT_16 _PL_ FileName,TEXT_16 _PL_ OpeningMode);
#define PenC_File_Opener_(Name,Mode) ((sizeof(*(Name))==sizeof(*(Mode)))?((sizeof(*(Name))==1)?(PenC.File.Opener.T08_((text_08*)(Name),(text_08*)(Mode))):((sizeof(*(Name))==2)?(PenC.File.Opener.T16_((text_16*)(Name),(text_16*)(Mode))):(NULL))):(NULL))
		}
		Opener;

		//PenClip : File Close
		//＊Return value is 0 for success, or an error code for failure.
		integer(_PL_ Closer_)(FILE *_PL_ FilePointer);
		//PenClip : File Pointer Usage in Local Scope - Handle with "PenC_Catch_"
#define PenC_File_Using_(Stream,Name,Mode,Error) for(FILE*(_##Stream)[sizeof(*(Name))==sizeof(*(Mode))]={FULL},_PL_(Stream)=PenC_File_Opener_(Name,Mode);(_##Stream)[0];(_##Stream)[0]=NULL,(Error)=PenC.File.Closer_((FILE**)&(Stream)))if(!(Stream)){(Error)=EOF;break;}else
		//PenClip : File Write
		address(_PL_ Writer_)(FILE _PL_ FilePointer,GENERAL _PL_ Buffer,ADDRESS Elements,ADDRESS TypeSize);
#define PenC_File_Writer_(FilePointer,Buffer,Elements) PenC.File.Writer_(FilePointer,Buffer,Elements,sizeof(*(Buffer)))
		//PenClip : File Read
		address(_PL_ Reader_)(FILE _PL_ FilePointer,general _PL_ Buffer,ADDRESS Elements,ADDRESS TypeSize);
#define PenC_File_Reader_(FilePointer,Buffer,Elements) PenC.File.Reader_(FilePointer,Buffer,Elements,sizeof(*(Buffer)))
		//PenClip : Step Forward from Current Location
		//＊Return value is 0 for success, or an error code for failure.
		integer(_PL_ Jumper_)(FILE _PL_ FilePointer,ADDRESS Elements,ADDRESS TypeSize);
#define PenC_File_Jumper_(FilePointer,Elements,type) PenC.File.Jumper_(FilePointer,Elements,sizeof(type))
		//PenClip : Step Backward from Current Location
		//＊Return value is 0 for success, or an error code for failure.
		integer(_PL_ Backer_)(FILE _PL_ FilePointer,ADDRESS Elements,ADDRESS TypeSize);
#define PenC_File_Backer_(FilePointer,Elements,type) PenC.File.Backer_(FilePointer,Elements,sizeof(type))
		//PenClip : Pointer Restart
		general(_PL_ Rewind_)(FILE _PL_ FilePointer);
		//PenClip : Current Location from Start
		long(_PL_ Teller_)(FILE _PL_ FilePointer);
		//PenClip : Stream Flush
		//＊Return value is 0 for success, or an error code for failure.
		integer(_PL_ Washer_)(FILE _PL_ FilePointer);
		//PenClip : End of File
		//＊Return value is 0 if the end has not been reached.
		integer(_PL_ Finish_)(FILE _PL_ FilePointer);

		//PenClip : File Pointer Position
		//＊Return value is 0 for success, or an error code for failure.
		const struct
		{
			//PenClip : Get the position.
			integer(_PL_ Get_)(FILE _PL_ FilePointer,fpos_t _PL_ Position);
			//PenClip : Set the position.
			integer(_PL_ Set_)(FILE _PL_ FilePointer,const fpos_t Position);
		}
		Pose;

		//PenClip : File Remove Functions
		//＊Return value is 0 for success, or an error code for failure.
		const struct
		{
			//PenClip : File Remove with 8-bit String
			integer(_PL_ T08_)(TEXT_08 _PL_ FileName);
			//PenClip : File Remove with 16-bit String
			integer(_PL_ T16_)(TEXT_16 _PL_ FileName);
#define PenC_File_Remove_(Name) ((sizeof(*(Name))==1)?(PenC.File.Remove.T08_((text_08*)(Name))):((sizeof(*(Name))==2)?(PenC.File.Remove.T16_((text_16*)(Name))):(0)))
		}
		Remove;

		//PenClip : File Rename Functions
		//＊Return value is 0 for success, or an error code for failure.
		const struct
		{
			//PenClip : File Rename with 8-bit String
			integer(_PL_ T08_)(TEXT_08 _PL_ OldName,TEXT_08 _PL_ NewName);
			//PenClip : File Rename with 16-bit String
			integer(_PL_ T16_)(TEXT_16 _PL_ OldName,TEXT_16 _PL_ NewName);
#define PenC_File_Rename_(Old,New) (MemC_Assert_(sizeof(*(Old))==sizeof(*(New))),((sizeof(*(Old))==1)?(PenC.File.Rename.T08_((text_08*)(Old),(text_08*)(New))):((sizeof(*(Old))==2)?(PenC.File.Rename.T16_((text_16*)(Old),(text_16*)(New))):(0))))
		}
		Rename;

		//PenClip : File's Byte Size Functions
		const struct
		{
			//PenClip : File's Byte Size with 8-bit String
			address(_PL_ T08_)(TEXT_08 _PL_ FileName);
			//PenClip : File's Byte Size with 16-bit String
			address(_PL_ T16_)(TEXT_16 _PL_ FileName);
#define PenC_File_Length_(Name) ((sizeof(*(Name))==1)?(PenC.File.Length.T08_((text_08*)(Name))):((sizeof(*(Name))==2)?(PenC.File.Length.T16_((text_16*)(Name))):(0)))
		}
		Length;
	}
	File;

	//PenClip : Stream Functions
	const struct
	{
		//PenClip : 8-bit Stream Print (Mode 0) or Scan (Mode 1)
#define PenC_Stream_Format_T08_(Mode,Stream,...) _PenC_Stream_Format_##Mode##_T08_(Stream,__VA_ARGS__)
#define _PenC_Stream_Format_0_T08_(Stream,...) ((Stream)?(fprintf_s(Stream,__VA_ARGS__)):(printf_s(__VA_ARGS__)))
#define _PenC_Stream_Format_1_T08_(Stream,...) ((Stream)?(fscanf_s(Stream,__VA_ARGS__)):(scanf_s(__VA_ARGS__)))
		//PenClip : 16-bit Stream Print (Mode 0) or Scan (Mode 1)
#define PenC_Stream_Format_T16_(Mode,Stream,...) _PenC_Stream_Format_##Mode##_T16_(Stream,__VA_ARGS__)
#define _PenC_Stream_Format_0_T16_(Stream,...) ((Stream)?(fwprintf_s(Stream,__VA_ARGS__)):(wprintf_s(__VA_ARGS__)))
#define _PenC_Stream_Format_1_T16_(Stream,...) ((Stream)?(fwscanf_s(Stream,__VA_ARGS__)):(wscanf_s(__VA_ARGS__)))

		//PenClip : Stream-Buffer I/O Functions
		const struct
		{
			//PenClip : 8-bit Buffer to Stream Print (Mode 0) or Stream to Buffer Scan (Mode 1)
			address(_PL_ T08_)(LOGICAL Mode,FILE _PL_ Stream,text_08 _PL_ Buffer,ADDRESS Capacity);
			//PenClip : 16-bit Buffer to Stream Print (Mode 0) or Stream to Buffer Scan (Mode 1)
			address(_PL_ T16_)(LOGICAL Mode,FILE _PL_ Stream,text_16 _PL_ Buffer,ADDRESS Capacity);
		}
		Buffer;

		//PenClip : Stream-String Container I/O Functions
		const struct
		{
			//PenClip : 8-bit String Container to Stream Print (Mode 0) or Stream to String Container Scan (Mode 1)
			address(_PL_ T08_)(LOGICAL Mode,PENC_SC _PL_ SC,FILE _PL_ Stream);
			//PenClip : 16-bit String Container to Stream Print (Mode 0) or Stream to String Container Scan (Mode 1)
			address(_PL_ T16_)(LOGICAL Mode,PENC_SC _PL_ SC,FILE _PL_ Stream);
		}
		SC;
	}
	Stream;

	//PenClip : Buffer Functions
	const struct
	{
		//PenClip : 8-bit Format String Length Expectation
#define PenC_Format_Length_T08_(...) snprintf(NULL,0,__VA_ARGS__)
		//PenClip : 16-bit Format String Length Expectation
#define PenC_Format_Length_T16_(...) swprintf(NULL,0,__VA_ARGS__)
		//PenClip : 8-bit Buffer Print (Mode 0) or Scan (Mode 1)
#define PenC_Buffer_Format_T08_(Mode,Buffer,Capacity,...) _PenC_Buffer_Format_##Mode##_T08_(Buffer,Capacity,__VA_ARGS__)
#define _PenC_Buffer_Format_0_T08_(Buffer,Capacity,...) (sprintf_s(Buffer,Capacity,__VA_ARGS__))
#define _PenC_Buffer_Format_1_T08_(Buffer,Capacity,...) (sscanf_s(Buffer,__VA_ARGS__))
		//PenClip : 16-bit Buffer Print (Mode 0) or Scan (Mode 1)
#define PenC_Buffer_Format_T16_(Mode,Buffer,Capacity,...) _PenC_Buffer_Format_##Mode##_T16_(Buffer,Capacity,__VA_ARGS__)
#define _PenC_Buffer_Format_0_T16_(Buffer,Capacity,...) (swprintf_s(Buffer,Capacity,__VA_ARGS__))
#define _PenC_Buffer_Format_1_T16_(Buffer,Capacity,...) (swscanf_s(Buffer,__VA_ARGS__))

		//PenClip : Buffer-Stream I/O Functions
		const struct
		{
			//PenClip : 8-bit Buffer to Stream Print (Mode 0) or Stream to Buffer Scan (Mode 1)
			address(_PL_ T08_)(LOGICAL Mode,FILE _PL_ Stream,text_08 _PL_ Buffer,ADDRESS Capacity);
			//PenClip : 16-bit Buffer to Stream Print (Mode 0) or Stream to Buffer Scan (Mode 1)
			address(_PL_ T16_)(LOGICAL Mode,FILE _PL_ Stream,text_16 _PL_ Buffer,ADDRESS Capacity);
		}
		Stream;

		//PenClip : 1D Array Data Read Functions
		const struct
		{
			//PenClip : 1D Array Data Read with 8-bit String
			//＊Return value is 1 for success, or 0 for failure.
			logical(_PL_ T08_)(general _PL_ Line,TEXT_08 _PL_ FileName,ADDRESS TypeSize,ADDRESS Count);
			//PenClip : 1D Array Data Read with 16-bit String
			//＊Return value is 1 for success, or 0 for failure.
			logical(_PL_ T16_)(general _PL_ Line,TEXT_16 _PL_ FileName,ADDRESS TypeSize,ADDRESS Count);
#define PenC_Buffer_Reader_(Line,FileName,Elements) ((sizeof(*(FileName))==1)?(PenC.Buffer.Reader.T08_(Line,(text_08*)(FileName),sizeof(*(Line)),Elements)):((sizeof(*(FileName))==2)?(PenC.Buffer.Reader.T16_(Line,(text_16*)(FileName),sizeof(*(Line)),Elements)):(0)))
		}
		Reader;

		//PenClip : 1D Array Data Write Functions
		const struct
		{
			//PenClip : 1D Array Data Write with 8-bit String
			//＊Return value is 1 for success, or 0 for failure.
			logical(_PL_ T08_)(GENERAL _PL_ Line,TEXT_08 _PL_ FileName,ADDRESS TypeSize,ADDRESS Count);
			//PenClip : 1D Array Data Write with 16-bit String
			//＊Return value is 1 for success, or 0 for failure.
			logical(_PL_ T16_)(GENERAL _PL_ Line,TEXT_16 _PL_ FileName,ADDRESS TypeSize,ADDRESS Count);
#define PenC_Buffer_Writer_(Line,FileName,Elements) ((sizeof(*(FileName))==1)?(PenC.Buffer.Writer.T08_(Line,(text_08*)(FileName),sizeof(*(Line)),Elements)):((sizeof(*(FileName))==2)?(PenC.Buffer.Writer.T16_(Line,(text_16*)(FileName),sizeof(*(Line)),Elements)):(0)))
		}
		Writer;
	}
	Buffer;

	//PenClip : Object Functions
	//＊Mode 0 : Binary
	//　Mode 1 : Text
	const struct
	{
		//PenClip : Object Save Functions
		const struct
		{
			//PenClip : 8-bit Object Save
			//＊Return value is that of (Save_) function for success, or 0 for failure.
			logical(_PL_ T08_)(TEXT_08 _PL_ FileName,logical(_PL_ Save_)(FILE _PL_ File,GENERAL _PL_ _R_ Object),GENERAL _PL_ _R_ Object,LOGICAL SaveMode);
			//PenClip : 16-bit Object Save
			//＊Return value is that of (Save_) function for success, or 0 for failure.
			logical(_PL_ T16_)(TEXT_16 _PL_ FileName,logical(_PL_ Save_)(FILE _PL_ File,GENERAL _PL_ _R_ Object),GENERAL _PL_ _R_ Object,LOGICAL SaveMode);
		}
		Save;

		//PenClip : Object Load Functions
		const struct
		{
			//PenClip : 8-bit Object Load
			//＊Return value is that of (Load_) function for success, or NULL for failure.
			general*(_PL_ T08_)(TEXT_08 _PL_ FileName,general*(_PL_ Load_)(FILE _PL_ File,general _PL_ _R_ Option),general _PL_ _R_ Option,LOGICAL LoadMode);
			//PenClip : 16-bit Object Load
			//＊Return value is that of (Load_) function for success, or NULL for failure.
			general*(_PL_ T16_)(TEXT_16 _PL_ FileName,general*(_PL_ Load_)(FILE _PL_ File,general _PL_ _R_ Option),general _PL_ _R_ Option,LOGICAL LoadMode);
		}
		Load;
	}
	Object;

	//PenClip : String Containter Functions
	const struct
	{
		//PenClip : Automatic String Container
#define PenC_SC_Auto_(Auto,CapacityBytes) MemC_Unit_(penc_sc,Auto,.Capacity=(CapacityBytes),.String.X=(byte_08[CapacityBytes]){0})

		//PenClip : String Container Memory Allocation - Deallocate with "PenC.SC.Delete_"
		penc_sc*(_PL_ Create_)(ADDRESS CapacityBytes);
		//PenClip : String Container Memory Deallocation
		general(_PL_ Delete_)(penc_sc *_PL_ StringContainer);

		//PenClip : String Container Data Reset
		general(_PL_ Init_)(PENC_SC _PL_);

		//PenClip : Null End Functions
		const struct
		{
			//PenClip : String Container 8-bit Null End
			general(_PL_ T08_)(PENC_SC _PL_);
			//PenClip : String Container 16-bit Null End
			general(_PL_ T16_)(PENC_SC _PL_);
		}
		Shut;

		//PenClip : String Container Conversion Functions
		//＊Return value is 1 for success, 0 for failure.
		const struct
		{
			//PenClip : Convert from a narrow multi-byte string.
			const struct
			{
				//PenClip : Convert into a wide string.
				logical(_PL_ T16_)(PENC_SC _PL_ Source,PENC_SC _PL_ Target);
			}
			T08;

			//PenClip : Convert from a wide string.
			const struct
			{
				//PenClip : Convert into a narrow multi-byte string.
				logical(_PL_ T08_)(PENC_SC _PL_ Source,PENC_SC _PL_ Target);
			}
			T16;
		}
		Conv;

		//PenClip : Length Functions
		const struct
		{
			//PenClip : String Container 8-bit Length
			address(_PL_ T08_)(PENC_SC _PL_);
			//PenClip : String Container 16-bit Length
			address(_PL_ T16_)(PENC_SC _PL_);
		}
		Length;

		//PenClip : Copy Functions
		//＊Return value is 1 for success, 0 for failure.
		const struct
		{
			//PenClip : String Container 8-bit Copy
			logical(_PL_ T08_)(PENC_SC _PL_ Target,PENC_SC _PL_ Source);
			//PenClip : String Container 16-bit Copy
			logical(_PL_ T16_)(PENC_SC _PL_ Target,PENC_SC _PL_ Source);
		}
		Copy;

		//PenClip : Concatenation Functions
		//＊Return value is 1 for success, 0 for failure.
		const struct
		{
			//PenClip : String Container 8-bit Concatenation
			logical(_PL_ T08_)(PENC_SC _PL_ Target,PENC_SC _PL_ Source);
			//PenClip : String Container 16-bit Concatenation
			logical(_PL_ T16_)(PENC_SC _PL_ Target,PENC_SC _PL_ Source);
		}
		Conc;

		//PenClip : Comparison Functions
		const struct
		{
			//PenClip : String Container 8-bit Comparison
			integer(_PL_ T08_)(PENC_SC _PL_,PENC_SC _PL_);
			//PenClip : String Container 16-bit Comparison
			integer(_PL_ T16_)(PENC_SC _PL_,PENC_SC _PL_);
		}
		Comp;
		
		//PenClip : 8-bit String Container Print (Mode 0) or Scan (Mode 1)
#define PenC_SC_Format_T08_(Mode,SC,...) PenC_Buffer_Format_T08_(Mode,(SC)->String.T08,(SC)->Capacity,__VA_ARGS__)
		//PenClip : 16-bit String Container Print (Mode 0) or Scan (Mode 1)
#define PenC_SC_Format_T16_(Mode,SC,...) PenC_Buffer_Format_T16_(Mode,(SC)->String.T16,(SC)->Capacity>>1,__VA_ARGS__)

		//PenClip : String Container-Stream I/O Functions
		const struct
		{
			//PenClip : 8-bit String Container to Stream Print (Mode 0) or Stream to String Container Scan (Mode 1)
			address(_PL_ T08_)(LOGICAL Mode,PENC_SC _PL_ SC,FILE _PL_ Stream);
			//PenClip : 16-bit String Container to Stream Print (Mode 0) or Stream to String Container Scan (Mode 1)
			address(_PL_ T16_)(LOGICAL Mode,PENC_SC _PL_ SC,FILE _PL_ Stream);
		}
		Stream;
	}
	SC;

	//PenClip : String Container Lender Functions
	const struct
	{
		//PenClip : Automatic String Lender
#define PenC_SL_Auto_(Auto,ChunksNumber) MemC_Unit_(penc_sl,Auto,.Node=&(penc_sl[ChunksNumber]){[0].Nodes=MemC_Size_(penc_sl,(ChunksNumber)-1)},.Chunks=(ChunksNumber),.Nodes=1,.Capable=MemC_Size_(penc_sl,(ChunksNumber)-1))

		//PenClip : SC Lender Memory Allocation - Deallocate with "PenC.SL.Delete_"
		//＊1 chunk is equal to 4×sizeof(size_t) bytes.
		//＊Each SC node's head occupies 1 chunk.
		penc_sl*(_PL_ Create_)(ADDRESS ChunksNumber);
		//PenClip : SC Lender Memory Deallocation
		general(_PL_ Delete_)(penc_sl *_PL_ SCLender);

		//PenClip : SC Lender Memory Occupation
		address(_PL_ Size_)(PENC_SL _PL_ SCLender);
		//PenClip : Kill all SCs in the SC Lender
		//＊Return value is 1 for success, or 0 for failure.
		logical(_PL_ Reset_)(penc_sl _PL_ SCLender);

		//PenClip : Borrow an SC from the SC Lender - Return with "PenC.SL.Return_"
		penc_sc*(_PL_ Borrow_)(penc_sl _PL_ SCLender,ADDRESS DemandBytes);

		//PenClip : Borrow Functions
		const struct
		{
			//PenClip : Borrow an SC from the SC Lender with the Specified 8-bit Format - Return with "PenC.SL.Return_"
#define PenC_SL_Borrow_Format_T08_(Lender,Container,...) __dl{PenC.SL.Return_(Lender,&(Container));(Container)=PenC.SL.Borrow_(Lender,PenC_Format_Length_T08_(__VA_ARGS__)+1);if(Container){PenC_SC_Format_T08_(0,Container,__VA_ARGS__);}else;}lb__
			//PenClip : Borrow an SC from the SC Lender with the Specified 16-bit Format - Return with "PenC.SL.Return_"
#define PenC_SL_Borrow_Format_T16_(Lender,Container,...) __dl{PenC.SL.Return_(Lender,&(Container));(Container)=PenC.SL.Borrow_(Lender,(PenC_Format_Length_T16_(__VA_ARGS__)+1)<<1);if(Container){PenC_SC_Format_T16_(0,Container,__VA_ARGS__);}else;}lb__

			//PenClip : Borrow an SC from the SC Lender Copying another SC
			const struct
			{
				//PenClip : Borrow an SC from the SC Lender Copying another SC with 8-bit String - Return with "PenC.SL.Return_"
				penc_sc*(_PL_ T08_)(penc_sl _PL_ SCLender,PENC_SC _PL_ SCSource);
				//PenClip : Borrow an SC from the SC Lender Copying another SC with 8-bit String - Return with "PenC.SL.Return_"
				penc_sc*(_PL_ T16_)(penc_sl _PL_ SCLender,PENC_SC _PL_ SCSource);
			}
			Copy;

			//PenClip : Borrow an SC from the SC Lender Concatenating two other SCs
			const struct
			{
				//PenClip : Borrow an SC from the SC Lender Concatenating two other SCs - Return with "PenC.SL.Return_"
				penc_sc*(_PL_ T08_)(penc_sl _PL_ SCLender,PENC_SC _PL_ SCFormer,PENC_SC _PL_ SCLatter);
				//PenClip : Borrow an SC from the SC Lender Concatenating two other SCs - Return with "PenC.SL.Return_"
				penc_sc*(_PL_ T16_)(penc_sl _PL_ SCLender,PENC_SC _PL_ SCFormer,PENC_SC _PL_ SCLatter);
			}
			Conc;
		}
		Borrow;

		//PenClip : Return the SC to the SC Lender
		//＊Return value is 1 for success, or 0 for failure.
		logical(_PL_ Return_)(penc_sl _PL_ SCLender,penc_sc *_PL_ StringContainer);
	}
	SL;
};
MemC_Type_Declare_(struct,pencase,PENCASE);	//PenClip : Library Case Structure

//PenClip : Library Case Object
extern PENCASE PenC;
//PenClip : Indirect access to the library case object.
extern PENCASE *PenC_(general);
#endif
#endif
