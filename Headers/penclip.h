/*------------------------------------------------------------------*/
/*	PenClip is a file I/O header.									*/
/*																	*/
/*	Written by Ranny Clover								Date		*/
/*	http://github.com/dlOuOlb/Clips						2018.02.12	*/
/*------------------------------------------------------------------*/
/*	OpenCL Support													*/
/*	http://www.khronos.org/opencl/									*/
/*------------------------------------------------------------------*/
/*	Opener : File Open												*/
/*	Closer : File Close												*/
/*																	*/
/*	Writer : File Write												*/
/*	Reader : File Read												*/
/*------------------------------------------------------------------*/

#ifndef _INC_PENCLIP
#define _INC_PENCLIP	//PenClip : Header Declaration

#include <stdio.h>
#include <time.h>
#ifdef _CL
#include <CL\opencl.h>
#endif
#include <memclip.h>

typedef char name_08;			//PenClip : 8-bit Name Variable
typedef const name_08 NAME_08;	//PenClip : 8-bit Name Constant

#ifdef __OPENCL_H
struct _penc_cl						//PenC_CL : OpenCL Supported Program Resource Structure
{
	cl_device_id const Device;		//PenC_CL : Device ID
	cl_context const Context;		//PenC_CL : Context
	cl_command_queue const Queue;	//PenC_CL : Command Queue
	cl_program const Program;		//PenC_CL : Internal Program
	cl_kernel _PL_ SetKernel;		//PenC_CL : Internal Kernel Set
	const size_t _PL_ SizeWorker;	//PenC_CL : Maximum Number of Work Items that can be specified in each Dimension of the Work Group 
	const size_t Workers;			//PenC_CL : Maximum Number of Work Items in a Work Group
	const cl_ulong SizeLocal;		//PenC_CL : Size of Local Memory Arena in Bytes
	const cl_uint Cores;			//PenC_CL : The Number of Parallel Compute Cores
	const cl_uint Dimensions;		//PenC_CL : Maximum Dimensions of Global and Local Work Items
	const cl_uint Kernels;			//PenC_CL : The Number of Kernels
};
typedef struct _penc_cl penc_cl;		//PenC_CL : Program Resource Variable
typedef const struct _penc_cl PENC_CL;	//PenC_CL : Program Resource Constant
#endif

#define File_Opener_(FilePointer,FileName,Mode) fopen_s(&(FilePointer),FileName,Mode)												//PenClip : File Open
#define File_Closer_(FilePointer) if(!fclose(FilePointer)){(FilePointer)=NULL;}														//PenClip : File Close
#define File_Remove_(FileName) remove(FileName)																						//PenClip : File Delete
#define File_Rename_(FileNameOld,FileNameNew) rename(FileNameOld,FileNameNew)														//PenClip : File Rename

#define File_Writer_(FilePointer,Buffer,Elements,type) fwrite(Buffer,sizeof(type),Elements,FilePointer)								//PenClip : File Write
#define File_Reader_(FilePointer,Buffer,Elements,type) fread_s(Buffer,(Elements)*sizeof(type),sizeof(type),Elements,FilePointer)	//PenClip : File Read
#define File_Jumper_(FilePointer,Elements,type) fseek(FilePointer,(Elements)*sizeof(type),SEEK_CUR)									//PenClip : Step Forward from Current Location
#define File_Backer_(FilePointer,Elements,type) fseek(FilePointer,0-((Elements)*sizeof(type)),SEEK_CUR)								//PenClip : Step Backward from Current Location

#define File_Rewind_(FilePointer) rewind(FilePointer)																				//PenClip : Pointer Restart
#define File_Teller_(FilePointer) ftell(FilePointer)																				//PenClip : Current Location from Start
#define File_Washer_(FilePointer) fflush(FilePointer)																				//PenClip : Stream Flush
#define File_Finish_(FilePointer) feof(FilePointer)																					//PenClip : End of File

#define Byte_Setter_(Buffer,Value,Length) (name_08*)memset(Buffer,Value,Length)														//PenClip : Buffer Byte Set
#define Byte_Finder_(Buffer,Value,Length) (name_08*)memchr(Buffer,Value,Length)														//PenClip : Buffer Byte Find
#define Word_Finder_(Sentence,Word) (name_08*)strstr(Sentence,Word)																	//PenClip : Sentence Word Find

#define Line_Reader_(Line,FileName,Elements,type) _Line_Reader_(Line,FileName,sizeof(type),Elements)								//PenClip : 1D Array Data Read
#define Line_Writer_(Line,FileName,Elements,type) _Line_Writer_(Line,FileName,sizeof(type),Elements)								//PenClip : 1D Array Data Write

#define Program_Opener_(ProgramPointer,Command,Mode) {(ProgramPointer)=_popen(Command,Mode);}										//PenClip : Program Open
#define Program_Closer_(ProgramPointer,Return) if(ProgramPointer){(Return)=_pclose(ProgramPointer);(ProgramPointer)=NULL;}			//PenClip : Program Close

#define PenC_Clocks_ clock()																										//PenClip : Current Clocks
#define PenC_Elapse_(Start) (PenC_Clocks_-(Start))																					//PenClip : Clock Measure from Start

#define Printer_Console_ printf_s																									//PenClip : Console Stream Print
#define Scanner_Console_ scanf_s																									//PenClip : Console Stream Scan

#define Printer_File_ fprintf_s																										//PenClip : File Stream Print
#define Scanner_File_ fscanf_s																										//PenClip : File Stream Scan

#define Printer_Text_ fputs																											//PenClip : File Stream Print in Text
#define Scanner_Text_ fgets																											//PenClip : File Stream Scan in Text

#define Printer_Buffer_ sprintf_s																									//PenClip : Buffer Stream Print
#define Scanner_Buffer_ sscanf_s																									//PenClip : Buffer Stream Scan

//PenClip : Library Version
extern NAME_08 _PL_ PenClip;

//PenClip : File I/O Option
//＊[0] : "rb" (Read Binary)
//　[1] : "wb" (Write Binary)
//　[2] : "rt" (Read Text)
//　[3] : "wt" (Write Text)
extern NAME_08 _PL_ _PL_ PenCOpen;

//PenClip : 1KB Buffer
extern name_08 _PL_ PenCBuffer;

//PenClip : File Byte Size
size_t File_Length_(NAME_08 _PL_ FileName);

//PenClip : Execute a command.
int PenC_Command_(NAME_08 _PL_ Command);

//PenClip : Print an integer in decimal form.
//＊Required buffer size is count bytes.
void PenC_Deci_(name_08 _PL_ Buffer,const size_t Number,const size_t Count);
//PenClip : Print an integer in hexadecimal form.
//＊Required buffer size is count bytes.
void PenC_Hexa_(name_08 _PL_ Buffer,const size_t Number,const size_t Count);

//PenClip : Print current date.
//＊Required buffer size is 10 bytes.
void PenC_Date_(name_08 _PL_ Buffer);
//PenClip : Print current time.
//＊Requried buffer size is 8 bytes.
void PenC_Time_(name_08 _PL_ Buffer);

//PenClip : Find the last dot character.
//＊Return value is offset.
size_t PenC_Extend_(NAME_08 _PL_ Buffer,const size_t Length);

#ifdef __OPENCL_H
//PenC_CL : Select Platform and Device with Console Interface
cl_int PenC_Identify_CL_(cl_uint _PL_ PlatformSelect,cl_uint _PL_ DeviceSelect);

//PenC_CL : Program Resource Memory Allocation - Deallocate with "PenC_Delete_CL_"
penc_cl *PenC_Create_CL_(cl_command_queue const,NAME_08 _PL_ _PL_ FileNameSet,NAME_08 _PL_ _PL_ IndicatorSet,NAME_08 _PL_ BuildOption,const size_t FilesNumber,const cl_uint KernelsNumber,cl_int _PL_ Error);
//PenC_CL : Program Resource Memory Deallocation
void PenC_Delete_CL_(penc_cl*_PL_);
#endif

int _Line_Reader_(void _PL_,NAME_08 _PL_,const size_t,const size_t);
int _Line_Writer_(const void _PL_,NAME_08 _PL_,const size_t,const size_t);
#endif
