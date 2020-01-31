#ifndef oPENCLIP_INC_
#define oPENCLIP_INC_ "PenC:2020.01.31"
/*------------------------------------------------------------------+
|	PenClip is a simple stream I/O library.							|
|																	|
|	Written by Ranny Clover											|
|	http://github.com/dlOuOlb/Clips/blob/master/Headers/penclip.h	|
+-------------------------------------------------------------------+
|	Dependency:														|
|																	|
|	MSVClip -- MemClip -- PenClip									|
+-------------------------------------------------------------------+
|	Non-Prefixed Types:												|
|																	|
|	text_08	text_16													|
|	TEXT_08	TEXT_16													|
+------------------------------------------------------------------*/

#include <memclip.h>

#include <stdio.h>
#include <wchar.h>

#if(Fold_(Primal Types))
MemC_Type_Rename_(char,text_08,TEXT_08);	//PenClip : 8-bit Character
MemC_Type_Rename_(wchar_t,text_16,TEXT_16);	//PenClip : 16-bit Character
#endif

#if(Fold_(Plain Types))
//PenClip : String Pointer Union
union _penclip
{
	general *X;		//PenClip : General Access
	text_08 *T08;	//PenClip : 8-bit Access
	text_16 *T16;	//PenClip : 16-bit Access
	address A;		//PenClip : Address Value
};
MemC_Type_Declare_(union,penclip,PENCLIP);	//PenClip : String Pointer Union
#endif

#if(Fold_(Advanced Types))
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
typedef const struct
{
	//PenClip : Some Constants
	const struct
	{
		//PenClip : Library Version - "PenC:yyyy.mm.dd"
		BYTE_08 _PL_ _R_ Version;
		//PenClip : UTF-8 Signature - { 0xEF, 0xBB, 0xBF, 0x00 }
		BYTE_08 _PL_ _R_ Signature;

		//PenClip : Hello, world!
		const struct
		{
			TEXT_08 _PL_ _R_ T08;	//PenClip : "Hello, world!\r\n"
			TEXT_16 _PL_ _R_ T16;	//PenClip : L"Hello, world!\r\n"
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
					TEXT_08 _PL_ _R_ T08;	//PenClip : "rb"
					TEXT_16 _PL_ _R_ T16;	//PenClip : L"rb"
				}
				Binary;

				//PenClip : Stream Read Text Options
				const struct
				{
					TEXT_08 _PL_ _R_ T08;	//PenClip : "rt"
					TEXT_16 _PL_ _R_ T16;	//PenClip : L"rt"
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
					TEXT_08 _PL_ _R_ T08;	//PenClip : "wb"
					TEXT_16 _PL_ _R_ T16;	//PenClip : L"wb"
				}
				Binary;

				//PenClip : Stream Write Text Options
				const struct
				{
					TEXT_08 _PL_ _R_ T08;	//PenClip : "wt"
					TEXT_16 _PL_ _R_ T16;	//PenClip : L"wt"
				}
				Text;
			}
			Write;
		}
		Option;
	};

	//PenClip : Character Setting Functions
	const struct
	{
		//PenClip : Set narrow characters
		general(_PL_ T08_)(text_08 _PL_ _R_ Buffer,TEXT_08 Value,ADDRESS Count);
		//PenClip : Set wide characters.
		general(_PL_ T16_)(text_16 _PL_ _R_ Buffer,TEXT_16 Value,ADDRESS Count);

#if(Fold_(Set))
#define PenC_Set_(Buffer,Value,Count)\
		(\
			MemC_Assert_((sizeof(*(Buffer))==sizeof(Value))&&((sizeof(Value)==1)||(sizeof(Value)==2))),\
			(\
				(sizeof(Value)==1)?\
				(PenC.Set.T08_((text_08*)(Buffer),(TEXT_08)(Value),Count)):\
				(PenC.Set.T16_((text_16*)(Buffer),(TEXT_16)(Value),Count))\
			)\
		)
#endif
	}
	Set;

	//PenClip : Character Finding Functions
	const struct
	{
		//PenClip : Find a narrow character.
		text_08*(_PL_ T08_)(text_08 _PL_ _R_ Buffer,TEXT_08 Value,ADDRESS Count);
		//PenClip : Find a wide character.
		text_16*(_PL_ T16_)(text_16 _PL_ _R_ Buffer,TEXT_16 Value,ADDRESS Count);

#if(Fold_(Find))
#define PenC_Find_(Buffer,Value,Count)\
		(\
			MemC_Assert_((sizeof(*(Buffer))==sizeof(Value))&&((sizeof(Value)==1)||(sizeof(Value)==2))),\
			(\
				(sizeof(Value)==1)?\
				((general*)PenC.Find.T08_((text_08*)(Buffer),(TEXT_08)(Value),Count)):\
				((general*)PenC.Find.T16_((text_16*)(Buffer),(TEXT_16)(Value),Count))\
			)\
		)
#endif
	}
	Find;

	//PenClip : String Handling Functions
	const struct
	{
		//PenClip : String Conversion Functions
		//＊Return value is 1 for success, 0 for failure.
		const struct
		{
			//PenClip : Convert into a narrow string.
			const struct
			{
				//PenClip : Convert from a wide string.
				//＊Required (TargetText) size is (TargetRoom)×1 bytes.
				//　Required (SourceText) size is (SourceRoom)×2 bytes.
				logical(_PL_ T16_)(ADDRESS TargetRoom,text_08 _PL_ _R_ TargetText,ADDRESS SourceRoom,TEXT_16 _PL_ _R_ SourceText);
			}
			T08;

			//PenClip : Convert into a wide string.
			const struct
			{
				//PenClip : Convert from a narrow string.
				//＊Required (TargetText) size is (TargetRoom)×2 bytes.
				//　Required (SourceText) size is (SourceRoom)×1 bytes.
				logical(_PL_ T08_)(ADDRESS TargetRoom,text_16 _PL_ _R_ TargetText,ADDRESS SourceRoom,TEXT_08 _PL_ _R_ SourceText);
			}
			T16;

#if(Fold_(Conv))
#define PenC_String_Conv_(TRoom,TText,SRoom,SText)\
			(\
				MemC_Assert_(((sizeof(*(TText))==1)||(sizeof(*(TText))==2))&&((sizeof(*(SText))==1)||(sizeof(*(SText))==2))),\
				(\
					(sizeof(*(TText))==1)?\
					(\
						(sizeof(*(SText))==1)?\
						(PenC.String.Copy.T08_(TRoom,(text_08*)(TText),(TEXT_08*)(SText))):\
						(PenC.String.Conv.T08.T16_(TRoom,(text_08*)(TText),SRoom,(TEXT_16*)(SText)))\
					):\
					(\
						(sizeof(*(SText))==1)?\
						(PenC.String.Conv.T16.T08_(TRoom,(text_16*)(TText),SRoom,(TEXT_08*)(SText))):\
						(PenC.String.Copy.T16_(TRoom,(text_16*)(TText),(TEXT_16*)(SText)))\
					)\
				)\
			)
#endif
		}
		Conv;

		//PenClip : String Length Functions
		const struct
		{
			//PenClip : 8-bit String Length
			//＊Required (Text) size is (Room)×1 bytes.
			address(_PL_ T08_)(ADDRESS Room,TEXT_08 _PL_ _R_ Text);
			//PenClip : 16-bit String Length
			//＊Required (Text) size is (Room)×2 bytes.
			address(_PL_ T16_)(ADDRESS Room,TEXT_16 _PL_ _R_ Text);

#if(Fold_(Length))
#define PenC_String_Length_(Room,Text)\
			(\
				MemC_Assert_((sizeof(*(Text))==1)||(sizeof(*(Text))==2)),\
				(\
					(sizeof(*(Text))==1)?\
					(PenC.String.Length.T08_(Room,(TEXT_08*)(Text))):\
					(PenC.String.Length.T16_(Room,(TEXT_16*)(Text)))\
				)\
			)
#endif
		}
		Length;

		//PenClip : Sub-String Finding Functions
		const struct
		{
			//PenClip : 8-bit Sub-String Finding
			text_08*(_PL_ T08_)(text_08 _PL_ _R_ Text,TEXT_08 _PL_ _R_ Word);
			//PenClip : 16-bit Sub-String Finding
			text_16*(_PL_ T16_)(text_16 _PL_ _R_ Text,TEXT_16 _PL_ _R_ Word);

#if(Fold_(Find))
#define PenC_String_Find_(Text,Word)\
			(\
				MemC_Assert_((sizeof(*(Text))==sizeof(*(Word)))&&((sizeof(*(Text))==1)||(sizeof(*(Text))==2))),\
				(\
					(sizeof(*(Text))==1)?\
					((general*)PenC.String.Find.T08_((text_08*)(Text),(TEXT_08*)(Word))):\
					((general*)PenC.String.Find.T16_((text_16*)(Text),(TEXT_16*)(Word)))\
				)\
			)
#endif
		}
		Find;

		//PenClip : String Copy Functions
		//＊Return value is 1 for success, 0 for failure.
		const struct
		{
			//PenClip : 8-bit String Copy
			//＊Required (Target) size is (Room)×1 bytes.
			logical(_PL_ T08_)(ADDRESS Room,text_08 _PL_ _R_ Target,TEXT_08 _PL_ _R_ Source);
			//PenClip : 16-bit String Copy
			//＊Required (Target) size is (Room)×2 bytes.
			logical(_PL_ T16_)(ADDRESS Room,text_16 _PL_ _R_ Target,TEXT_16 _PL_ _R_ Source);

#if(Fold_(Copy))
#define PenC_String_Copy_(Room,Target,Source)\
			(\
				MemC_Assert_((sizeof(*(Target))==sizeof(*(Source)))&&((sizeof(*(Target))==1)||(sizeof(*(Target))==2))),\
				(\
					(sizeof(*(Target))==1)?\
					(PenC.String.Copy.T08_(Room,(text_08*)(Target),(TEXT_08*)(Source))):\
					(PenC.String.Copy.T16_(Room,(text_16*)(Target),(TEXT_16*)(Source)))\
				)\
			)
#endif
		}
		Copy;

		//PenClip : String Concatenation Functions
		//＊Return value is 1 for success, 0 for failure.
		const struct
		{
			//PenClip : 8-bit String Concatenation
			//＊Required (Target) size is (Room)×1 bytes.
			logical(_PL_ T08_)(ADDRESS Room,text_08 _PL_ _R_ Target,TEXT_08 _PL_ _R_ Source);
			//PenClip : 16-bit String Concatenation
			//＊Required (Target) size is (Room)×2 bytes.
			logical(_PL_ T16_)(ADDRESS Room,text_16 _PL_ _R_ Target,TEXT_16 _PL_ _R_ Source);

#if(Fold_(Conc))
#define PenC_String_Conc_(Room,Target,Source)\
			(\
				MemC_Assert_((sizeof(*(Target))==sizeof(*(Source)))&&((sizeof(*(Target))==1)||(sizeof(*(Target))==2))),\
				(\
					(sizeof(*(Target))==1)?\
					(PenC.String.Conc.T08_(Room,(text_08*)(Target),(TEXT_08*)(Source))):\
					(PenC.String.Conc.T16_(Room,(text_16*)(Target),(TEXT_16*)(Source)))\
				)\
			)
#endif
		}
		Conc;

		//PenClip : String Comparison Functions
		const struct
		{
			//PenClip : 8-bit String Comparison
			integer(_PL_ T08_)(TEXT_08 _PL_ StringA,TEXT_08 _PL_ StringB);
			//PenClip : 16-bit String Comparison
			integer(_PL_ T16_)(TEXT_16 _PL_ StringA,TEXT_16 _PL_ StringB);

#if(Fold_(Comp))
#define PenC_String_Comp_(A,B)\
			(\
				MemC_Assert_((sizeof(*(A))==sizeof(*(B)))&&((sizeof(*(A))==1)||(sizeof(*(A))==2))),\
				(\
					(sizeof(*(A))==1)?\
					(PenC.String.Comp.T08_((TEXT_08*)(A),(TEXT_08*)(B))):\
					(PenC.String.Comp.T16_((TEXT_16*)(A),(TEXT_16*)(B)))\
				)\
			)
#endif
		}
		Comp;
	}
	String;
	
	//PenClip : File Handling Functions
	const struct
	{
		//PenClip : File Opening and Closing
		const struct
		{
			//PenClip : File Open Functions - Close with "PenC.File.Closer_"
			//＊Return address is NULL for failure.
			const struct
			{
				//PenClip : Open a file with the narrow string path.
				FILE*(_PL_ T08_)(TEXT_08 _PL_ FilePath,TEXT_08 _PL_ OpeningMode);
				//PenClip : Open a file with the wide string path.
				FILE*(_PL_ T16_)(TEXT_16 _PL_ FilePath,TEXT_16 _PL_ OpeningMode);

#if(Fold_(Opener))
#define PenC_File_Opener_(Path,Mode)\
				(\
					MemC_Assert_((sizeof(*(Path))==sizeof(*(Mode)))&&((sizeof(*(Path))==1)||(sizeof(*(Path))==2))),\
					(\
						(sizeof(*(Path))==1)?\
						(PenC.File.Opener.T08_((TEXT_08*)(Path),(TEXT_08*)(Mode))):\
						(PenC.File.Opener.T16_((TEXT_16*)(Path),(TEXT_16*)(Mode)))\
					)\
				)
#endif
			}
			Opener;

			//PenClip : Close the file.
			//＊Return value is 0 for success, or an error code for failure.
			integer(_PL_ Closer_)(FILE *_PL_ _R_);
			//PenClip: Check the file.
			//＊Return value is 0 for success, or an error code for failure.
			integer(_PL_ Verify_)(FILE _PL_ _R_ File);

#if(Fold_(Using))
			//PenClip : File Pointer Usage in Local Scope
#define PenC_File_Using_(Stream,Path,Mode,Error)\
			if(Error);else MemC_Temp_(FILE,*Conc_(xPenCFile,__LINE__)=PenC_File_Opener_(Path,Mode))\
			if(!Conc_(xPenCFile,__LINE__)){(Error)=EOF;}else for\
			(\
				FILE _PL_(Stream)=Conc_(xPenCFile,__LINE__);\
				Conc_(xPenCFile,__LINE__);\
				(Error)=PenC.File.Closer_(&Conc_(xPenCFile,__LINE__))\
			)
#endif
		};

		//PenClip : File Writing and Reading
		const struct
		{
			//PenClip : Write into the file.
			//＊Return value is the number of written elements.
			address(_PL_ Writer_)(FILE _PL_ _R_ File,GENERAL _PL_ _R_ Buffer,ADDRESS Elements,ADDRESS TypeSize);
#define PenC_File_Writer_(File,Buffer,Elements) PenC.File.Writer_(File,Buffer,Elements,sizeof(*(Buffer)))

			//PenClip : Read from the file.
			//＊Return value is the number of read elements.
			address(_PL_ Reader_)(FILE _PL_ _R_ File,general _PL_ _R_ Buffer,ADDRESS Elements,ADDRESS TypeSize);
#define PenC_File_Reader_(File,Buffer,Elements) PenC.File.Reader_(File,Buffer,Elements,sizeof(*(Buffer)))

			//PenClip : Step forward from the current location.
			//＊Return value is 0 for success, or an error code for failure.
			integer(_PL_ Jumper_)(FILE _PL_ _R_ File,ADDRESS Elements,ADDRESS TypeSize);
#define PenC_File_Jumper_(File,Elements,type) PenC.File.Jumper_(File,Elements,sizeof(type))

			//PenClip : Step backward from the current location.
			//＊Return value is 0 for success, or an error code for failure.
			integer(_PL_ Backer_)(FILE _PL_ _R_ File,ADDRESS Elements,ADDRESS TypeSize);
#define PenC_File_Backer_(File,Elements,type) PenC.File.Backer_(File,Elements,sizeof(type))
		};

		//PenClip : File Handling
		const struct
		{
			//PenClip : Reset the file pointer.
			general(_PL_ Rewind_)(FILE _PL_ _R_ File);

			//PenClip : Get the file pointer offset from the start.
			long(_PL_ Teller_)(FILE _PL_ _R_ File);

			//PenClip : Flush the file.
			//＊Return value is 0 for success, or an error code for failure.
			integer(_PL_ Washer_)(FILE _PL_ _R_ File);

			//PenClip : Check the end of the file.
			//＊Return value is 0 if the end has not been reached.
			integer(_PL_ Finish_)(FILE _PL_ _R_ File);
		};

		//PenClip : File Pointer Position Functions
		//＊Return value is 0 for success, or an error code for failure.
		const struct
		{
			//PenClip : Get the file pointer position.
			integer(_PL_ Get_)(FILE _PL_ _R_ File,fpos_t _PL_ _R_ Position);
			//PenClip : Set the file pointer position.
			integer(_PL_ Set_)(FILE _PL_ _R_ File,const fpos_t Position);
		}
		Pose;

		//PenClip : File Remove Functions
		//＊Return value is 0 for success, or an error code for failure.
		const struct
		{
			//PenClip : Remove a file with the narrow string path.
			integer(_PL_ T08_)(TEXT_08 _PL_ Path);
			//PenClip : Remove a file with the wide string path.
			integer(_PL_ T16_)(TEXT_16 _PL_ Path);

#if(Fold_(Remove))
#define PenC_File_Remove_(Path)\
			(\
				MemC_Assert_((sizeof(*(Path))==1)||(sizeof(*(Path))==2)),\
				(\
					(sizeof(*(Path))==1)?\
					(PenC.File.Remove.T08_((TEXT_08*)(Path))):\
					(PenC.File.Remove.T16_((TEXT_16*)(Path)))\
				)\
			)
#endif
		}
		Remove;

		//PenClip : File Rename Functions
		//＊Return value is 0 for success, or an error code for failure.
		const struct
		{
			//PenClip : Rename a file with the narrow string path.
			integer(_PL_ T08_)(TEXT_08 _PL_ OldPath,TEXT_08 _PL_ NewPath);
			//PenClip : Rename a file with the wide string path.
			integer(_PL_ T16_)(TEXT_16 _PL_ OldPath,TEXT_16 _PL_ NewPath);

#if(Fold_(Rename))
#define PenC_File_Rename_(Old,New)\
			(\
				MemC_Assert_((sizeof(*(Old))==sizeof(*(New)))&&((sizeof(*(Old))==1)||(sizeof(*(Old))==2))),\
				(\
					(sizeof(*(Old))==1)?\
					(PenC.File.Rename.T08_((TEXT_08*)(Old),(TEXT_08*)(New))):\
					(PenC.File.Rename.T16_((TEXT_16*)(Old),(TEXT_16*)(New)))\
				)\
			)
#endif
		}
		Rename;

		//PenClip : File's Byte Size Functions
		const struct
		{
			//PenClip : Get a file's byte size with the narrow string path.
			address(_PL_ T08_)(TEXT_08 _PL_ Path);
			//PenClip : Get a file's byte size with the wide string path.
			address(_PL_ T16_)(TEXT_16 _PL_ Path);

#if(Fold_(Length))
#define PenC_File_Length_(Path)\
			(\
				MemC_Assert_((sizeof(*(Path))==1)||(sizeof(*(Path))==2)),\
				(\
					(sizeof(*(Path))==1)?\
					(PenC.File.Length.T08_((TEXT_08*)(Path))):\
					(PenC.File.Length.T16_((TEXT_16*)(Path)))\
				)\
			)
#endif
		}
		Length;
	}
	File;

	//PenClip : Stream Functions
	const struct
	{
#if(defined(__STDC_WANT_LIB_EXT1__)&&(__STDC_WANT_LIB_EXT1__))
		//PenClip : Narrow String Stream Print (Mode O) or Scan (Mode I)
#define PenC_Stream_Format_T08_(Mode,Stream,...) (xPenC_Stream_Format_##Mode##_T08_(Stream,__VA_ARGS__)>=0)
#define xPenC_Stream_Format_O_T08_(Stream,...) ((Stream)?(fprintf_s(Stream,__VA_ARGS__)):(printf_s(__VA_ARGS__)))
#define xPenC_Stream_Format_I_T08_(Stream,...) ((Stream)?(fscanf_s(Stream,__VA_ARGS__)):(scanf_s(__VA_ARGS__)))
		//PenClip : Wide String Stream Print (Mode O) or Scan (Mode I)
#define PenC_Stream_Format_T16_(Mode,Stream,...) (xPenC_Stream_Format_##Mode##_T16_(Stream,__VA_ARGS__)>=0)
#define xPenC_Stream_Format_O_T16_(Stream,...) ((Stream)?(fwprintf_s(Stream,__VA_ARGS__)):(wprintf_s(__VA_ARGS__)))
#define xPenC_Stream_Format_I_T16_(Stream,...) ((Stream)?(fwscanf_s(Stream,__VA_ARGS__)):(wscanf_s(__VA_ARGS__)))
#else
#define PenC_Stream_Format_T08_(...) xPenC_Stream_Format_Error_
#define PenC_Stream_Format_T16_(...) xPenC_Stream_Format_Error_
#define xPenC_Stream_Format_Error_ static_assert(0,"#define __STDC_WANT_LIB_EXT1__ (1) before #include <penclip.h>")
#endif

		//PenClip : Stream-Buffer I/O Functions
		//＊Mode 0 : Print - Buffer to Stream
		//　Mode 1 : Scan - Stream to Buffer
		//＊Return value is 1 for success, 0 for failure.
		const struct
		{
			//PenClip : Narrow String I/O
			//＊Required (Buffer) size is (Room)×1 bytes.
			logical(_PL_ T08_)(LOGICAL Mode,FILE _PL_ _R_ Stream,ADDRESS Room,text_08 _PL_ _R_ Buffer);
			//PenClip : Wide String I/O
			//＊Required (Buffer) size is (Room)×2 bytes.
			logical(_PL_ T16_)(LOGICAL Mode,FILE _PL_ _R_ Stream,ADDRESS Room,text_16 _PL_ _R_ Buffer);

#if(Fold_(Buffer))
#define PenC_Stream_Buffer_(Mode,Port,Room,Bf)\
			(\
				MemC_Assert_((sizeof(*(Bf))==1)||(sizeof(*(Bf))==2)),\
				(\
					(sizeof(*(Bf))==1)?\
					(PenC.Stream.Buffer.T08_(Mode,Port,Room,(text_08*)(Bf))):\
					(PenC.Stream.Buffer.T16_(Mode,Port,Room,(text_16*)(Bf)))\
				)\
			)
#endif
		}
		Buffer;

		//PenClip : Stream-String Container I/O Functions
		//＊Mode 0 : Print - String Container to Stream
		//　Mode 1 : Scan - Stream to String Container
		//＊Return value is 1 for success, 0 for failure.
		const struct
		{
			//PenClip : Narrow String I/O
			logical(_PL_ T08_)(LOGICAL Mode,FILE _PL_ _R_ Stream,PENC_SC _PL_ _R_ SC);
			//PenClip : Wide String I/O
			logical(_PL_ T16_)(LOGICAL Mode,FILE _PL_ _R_ Stream,PENC_SC _PL_ _R_ SC);
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
#if(defined(__STDC_WANT_LIB_EXT1__)&&(__STDC_WANT_LIB_EXT1__))
		//PenClip : 8-bit Buffer Print (Mode O) or Scan (Mode I)
#define PenC_Buffer_Format_T08_(Mode,Room,Buffer,...) xPenC_Buffer_Format_##Mode##_T08_(Room,Buffer,__VA_ARGS__)
#define xPenC_Buffer_Format_O_T08_(Room,Buffer,...) (sprintf_s(Buffer,Room,__VA_ARGS__)>0)
#define xPenC_Buffer_Format_I_T08_(Room,Buffer,...) (sscanf_s(Buffer,__VA_ARGS__)>=0)
		//PenClip : 16-bit Buffer Print (Mode O) or Scan (Mode I)
#define PenC_Buffer_Format_T16_(Mode,Room,Buffer,...) xPenC_Buffer_Format_##Mode##_T16_(Room,Buffer,__VA_ARGS__)
#define xPenC_Buffer_Format_O_T16_(Room,Buffer,...) (swprintf_s(Buffer,Room,__VA_ARGS__)>0)
#define xPenC_Buffer_Format_I_T16_(Room,Buffer,...) (swscanf_s(Buffer,__VA_ARGS__)>=0)
#else
#define PenC_Buffer_Format_T08_(...) xPenC_Buffer_Format_Error_
#define PenC_Buffer_Format_T16_(...) xPenC_Buffer_Format_Error_
#define xPenC_Buffer_Format_Error_ static_assert(0,"#define __STDC_WANT_LIB_EXT1__ (1) before #include <penclip.h>")
#endif

		//PenClip : Buffer-Stream I/O Functions
		//＊Mode 0 : Print - Buffer to Stream
		//　Mode 1 : Scan - Stream to Buffer
		//＊Return value is 1 for success, 0 for failure.
		const struct
		{
			//PenClip : Narrow String I/O
			//＊Required (Buffer) size is (Room)×1 bytes.
			logical(_PL_ T08_)(LOGICAL Mode,FILE _PL_ _R_ Stream,ADDRESS Room,text_08 _PL_ _R_ Buffer);
			//PenClip : Wide String I/O
			//＊Required (Buffer) size is (Room)×2 bytes.
			logical(_PL_ T16_)(LOGICAL Mode,FILE _PL_ _R_ Stream,ADDRESS Room,text_16 _PL_ _R_ Buffer);

#define PenC_Buffer_Stream_(Mode,Port,Room,Bf) PenC_Stream_Buffer_(Mode,Port,Room,Bf)
		}
		Stream;

		//PenClip : Preserved for Future Usage
		ADDRESS xPreserved[2];

		//PenClip : 1D Array Data Read Functions
		//＊Return value is 1 for success, or 0 for failure.
		const struct
		{
			//PenClip : Read 1D array data with the narrow string path.
			logical(_PL_ T08_)(general _PL_ Line,TEXT_08 _PL_ Path,ADDRESS TypeSize,ADDRESS Count);
			//PenClip : Read 1D array data with the wide string path.
			logical(_PL_ T16_)(general _PL_ Line,TEXT_16 _PL_ Path,ADDRESS TypeSize,ADDRESS Count);

#if(Fold_(Reader))
#define PenC_Buffer_Reader_(Line,Path,Elements)\
			(\
				MemC_Assert_((sizeof(*(Path))==1)||(sizeof(*(Path))==2)),\
				(\
					(sizeof(*(Path))==1)?\
					(PenC.Buffer.Reader.T08_(Line,(TEXT_08*)(Path),sizeof(*(Line)),Elements)):\
					(PenC.Buffer.Reader.T16_(Line,(TEXT_16*)(Path),sizeof(*(Line)),Elements))\
				)\
			)
#endif
		}
		Reader;

		//PenClip : 1D Array Data Write Functions
		//＊Return value is 1 for success, or 0 for failure.
		const struct
		{
			//PenClip : Write 1D array data with the narrow string path.
			logical(_PL_ T08_)(GENERAL _PL_ Line,TEXT_08 _PL_ Path,ADDRESS TypeSize,ADDRESS Count);
			//PenClip : Write 1D array data with the wide string path.
			logical(_PL_ T16_)(GENERAL _PL_ Line,TEXT_16 _PL_ Path,ADDRESS TypeSize,ADDRESS Count);

#if(Fold_(Writer))
#define PenC_Buffer_Writer_(Line,Path,Elements)\
			(\
				MemC_Assert_((sizeof(*(Path))==1)||(sizeof(*(Path))==2)),\
				(\
					(sizeof(*(Path))==1)?\
					(PenC.Buffer.Writer.T08_(Line,(TEXT_08*)(Path),sizeof(*(Line)),Elements)):\
					(PenC.Buffer.Writer.T16_(Line,(TEXT_16*)(Path),sizeof(*(Line)),Elements))\
				)\
			)
#endif
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
		//＊Return value is that of (Save_) function for success, or 0 for failure.
		const struct
		{
			//PenClip : Save an object with the narrow string path.
			logical(_PL_ T08_)(TEXT_08 _PL_ Path,logical(_PL_ Save_)(FILE _PL_ _R_ File,GENERAL _PL_ _R_ Object),GENERAL _PL_ _R_ Object,LOGICAL SaveMode);
			//PenClip : Save an object with the wide string path.
			logical(_PL_ T16_)(TEXT_16 _PL_ Path,logical(_PL_ Save_)(FILE _PL_ _R_ File,GENERAL _PL_ _R_ Object),GENERAL _PL_ _R_ Object,LOGICAL SaveMode);
		}
		Save;

		//PenClip : Object Load Functions
		//＊Return value is that of (Load_) function for success, or NULL for failure.
		const struct
		{
			//PenClip : Load an object with the narrow string path.
			general*(_PL_ T08_)(TEXT_08 _PL_ Path,general*(_PL_ Load_)(FILE _PL_ _R_ File,general _PL_ _R_ Option),general _PL_ _R_ Option,LOGICAL LoadMode);
			//PenClip : Load an object with the wide string path.
			general*(_PL_ T16_)(TEXT_16 _PL_ Path,general*(_PL_ Load_)(FILE _PL_ _R_ File,general _PL_ _R_ Option),general _PL_ _R_ Option,LOGICAL LoadMode);
		}
		Load;
	}
	Object;

	//PenClip : String Containter Functions
	const struct
	{
		//PenClip : Creation and Deletion
		const struct
		{
			//PenClip : String Container Memory Allocation - Deallocate with "PenC.SC.Delete_"
			penc_sc*(_PL_ Create_)(ADDRESS CapacityBytes);
			//PenClip : String Container Memory Deallocation
			general(_PL_ Delete_)(penc_sc *_PL_ _R_);
			//PenClip : String Container Memory Occupation
			address(_PL_ Size_)(PENC_SC _PL_ _R_);
			//PenClip : String Container Data Reset
			general(_PL_ Init_)(PENC_SC _PL_ _R_);

#if(Fold_(Auto))
#define PenC_SC_Auto_(Auto,CapacityBytes)\
			auto MemC_Unit_\
			(\
				penc_sc,Auto,\
					.Capacity=(CapacityBytes),\
					.String.X=(byte_08[CapacityBytes]){0}\
			)
#endif
		};

		//PenClip : Preserved for Future Usage
		ADDRESS xPreserved[2];

		//PenClip : Null End Functions
		const struct
		{
			//PenClip : Write a narrow null character at the end.
			general(_PL_ T08_)(PENC_SC _PL_ _R_);
			//PenClip : Write a wide null character at the end.
			general(_PL_ T16_)(PENC_SC _PL_ _R_);
		}
		Shut;

		//PenClip : String Container Conversion Functions
		//＊Return value is 1 for success, 0 for failure.
		const struct
		{
			//PenClip : Convert into a narrow string.
			const struct
			{
				//PenClip : Convert from a wide string.
				logical(_PL_ T16_)(PENC_SC _PL_ _R_ Target,PENC_SC _PL_ _R_ Source);
			}
			T08;

			//PenClip : Convert into a wide string.
			const struct
			{
				//PenClip : Convert from a narrow string.
				logical(_PL_ T08_)(PENC_SC _PL_ _R_ Target,PENC_SC _PL_ _R_ Source);
			}
			T16;
		}
		Conv;

		//PenClip : Length Functions
		const struct
		{
			//PenClip : Get the number of the narrow characters.
			address(_PL_ T08_)(PENC_SC _PL_ _R_);
			//PenClip : Get the number of the wide characters.
			address(_PL_ T16_)(PENC_SC _PL_ _R_);
		}
		Length;

		//PenClip : Copy Functions
		//＊Return value is 1 for success, 0 for failure.
		const struct
		{
			//PenClip : Copy the narrow string.
			logical(_PL_ T08_)(PENC_SC _PL_ _R_ Target,PENC_SC _PL_ _R_ Source);
			//PenClip : Copy the wide string.
			logical(_PL_ T16_)(PENC_SC _PL_ _R_ Target,PENC_SC _PL_ _R_ Source);
		}
		Copy;

		//PenClip : Concatenation Functions
		//＊Return value is 1 for success, 0 for failure.
		const struct
		{
			//PenClip : Concatenate the narrow strings.
			logical(_PL_ T08_)(PENC_SC _PL_ _R_ Target,PENC_SC _PL_ _R_ Source);
			//PenClip : Concatenate the wide strings.
			logical(_PL_ T16_)(PENC_SC _PL_ _R_ Target,PENC_SC _PL_ _R_ Source);
		}
		Conc;

		//PenClip : Comparison Functions
		const struct
		{
			//PenClip : Compare the narrow strings.
			integer(_PL_ T08_)(PENC_SC _PL_ SCA,PENC_SC _PL_ SCB);
			//PenClip : Compare the wide strings.
			integer(_PL_ T16_)(PENC_SC _PL_ SCA,PENC_SC _PL_ SCB);
		}
		Comp;
		
#if(Fold_(Format))
		//PenClip : Narrow String Container Print (Mode O) or Scan (Mode I)
#define PenC_SC_Format_T08_(Mode,SC,...) PenC_Buffer_Format_T08_(Mode,(SC)->Capacity,(SC)->String.T08,__VA_ARGS__)
		//PenClip : Wide String Container Print (Mode O) or Scan (Mode I)
#define PenC_SC_Format_T16_(Mode,SC,...) PenC_Buffer_Format_T16_(Mode,(SC)->Capacity>>1,(SC)->String.T16,__VA_ARGS__)
#endif

		//PenClip : String Container-Stream I/O Functions
		//＊Mode 0 : Print - String Container to Stream
		//　Mode 1 : Scan - Stream to String Container
		//＊Return value is 1 for success, 0 for failure.
		const struct
		{
			//PenClip : Narrow String I/O
			logical(_PL_ T08_)(LOGICAL Mode,FILE _PL_ _R_ Stream,PENC_SC _PL_ _R_ SC);
			//PenClip : Wide String I/O
			logical(_PL_ T16_)(LOGICAL Mode,FILE _PL_ _R_ Stream,PENC_SC _PL_ _R_ SC);
		}
		Stream;
	}
	SC;

	//PenClip : String Container Lender Functions
	const struct
	{
		//PenClip : Creation and Deletion
		const struct
		{
			//PenClip : SC Lender Memory Allocation - Deallocate with "PenC.SL.Delete_"
			//＊1 chunk is equal to 4×sizeof(address) bytes.
			//＊Each SC node's head occupies 1 chunk.
			penc_sl*(_PL_ Create_)(ADDRESS ChunksNumber);
			//PenClip : SC Lender Memory Deallocation
			general(_PL_ Delete_)(penc_sl *_PL_ _R_);

			//PenClip : SC Lender Memory Occupation
			address(_PL_ Size_)(PENC_SL _PL_ _R_ SCLender);
			//PenClip : Kill all SCs in the SC lender.
			//＊Return value is 1 for success, or 0 for failure.
			logical(_PL_ Reset_)(penc_sl _PL_ _R_ SCLender);

#if(Fold_(Auto))
#define PenC_SL_Auto_(Auto,ChunksNumber)\
			auto MemC_Unit_\
			(\
				penc_sl,Auto,\
					.Node=&(penc_sl[ChunksNumber]){[0].Nodes=MemC_Size_(penc_sl,(ChunksNumber)-1)},\
					.Chunks=(ChunksNumber),\
					.Nodes=1,\
					.Capable=MemC_Size_(penc_sl,(ChunksNumber)-1)\
			)
#endif
		};

		//PenClip : Borrow and Return
		const struct
		{
			//PenClip : Return the SC to the SC lender.
			//＊Return value is 1 for success, or 0 for failure.
			logical(_PL_ Return_)(penc_sl _PL_ _R_ SCLender,penc_sc *_PL_ _R_);
			//PenClip : Borrow an SC from the SC lender. - Return it with "PenC.SL.Return_"
			penc_sc*(_PL_ Borrow_)(penc_sl _PL_ _R_ SCLender,ADDRESS DemandBytes);

			//PenClip : Preserved for Future Usage
			ADDRESS xPreserved[2];
		};

		//PenClip : Borrow Functions - Return it with "PenC.SL.Return_"
		const struct
		{
#if(Fold_(Format))
			//PenClip : Borrow an SC from the SC lender with the narrow string format.
#define PenC_SL_Borrow_Format_T08_(Lender,Container,...)\
			__dl{\
				PenC.SL.Return_(Lender,&(Container));\
				(Container)=PenC.SL.Borrow_(Lender,PenC_Format_Length_T08_(__VA_ARGS__)+1);\
				if(Container){PenC_SC_Format_T08_(O,Container,__VA_ARGS__);}else;\
			}lb__

			//PenClip : Borrow an SC from the SC lender with the wide string format.
#define PenC_SL_Borrow_Format_T16_(Lender,Container,...)\
			__dl{\
				PenC.SL.Return_(Lender,&(Container));\
				(Container)=PenC.SL.Borrow_(Lender,(PenC_Format_Length_T16_(__VA_ARGS__)+1)<<1);\
				if(Container){PenC_SC_Format_T16_(O,Container,__VA_ARGS__);}else;\
			}lb__
#endif

			//PenClip : Borrow an SC from the SC lender, copying the given SC.
			const struct
			{
				//PenClip : Copy the narrow string.
				penc_sc*(_PL_ T08_)(penc_sl _PL_ _R_ SCLender,PENC_SC _PL_ _R_ SCSource);
				//PenClip : Copy the wide string.
				penc_sc*(_PL_ T16_)(penc_sl _PL_ _R_ SCLender,PENC_SC _PL_ _R_ SCSource);
			}
			Copy;

			//PenClip : Borrow an SC from the SC lender, concatenating the given SCs.
			const struct
			{
				//PenClip : Concatenate the narrow strings.
				penc_sc*(_PL_ T08_)(penc_sl _PL_ _R_ SCLender,PENC_SC _PL_ SCFormer,PENC_SC _PL_ SCLatter);
				//PenClip : Concatenate the wide strings.
				penc_sc*(_PL_ T16_)(penc_sl _PL_ _R_ SCLender,PENC_SC _PL_ SCFormer,PENC_SC _PL_ SCLatter);
			}
			Conc;
		}
		Borrow;
	}
	SL;
}
PENCASE;

//PenClip : Library Case Object
extern PENCASE PenC,*PenC_(general);
#endif
#endif
