#define __STDC_WANT_LIB_EXT1__ (1)
#include "penclip.h"

#include <limits.h>

#if(Fold_(Static Assertions))
static_assert(sizeof(text_08)==1,"sizeof(text_08) != 1");
static_assert(sizeof(text_16)==2,"sizeof(text_16) != 2");
static_assert(sizeof(address)>=sizeof(int),"sizeof(address) < sizeof(int)");
static_assert(sizeof(address)>=sizeof(long),"sizeof(address) < sizeof(long)");
static_assert(+(LONG_MIN)<-(LONG_MAX),"|LONG_MIN| < |LONG_MAX|");
#endif

#if(Fold_(PenClip Macros))
#define xPENC_SC_MAX_ ((address)(((address)(1))<<(sizeof(address)<<2)))
#if(defined(_MSC_BUILD)||defined(__POCC__))
#define xPENC_WIDE_
#endif
#endif

#if(Fold_(Internal Constants))
static const struct
{
	const struct { TEXT_16 Hello[16],Open[16]; }T16;
	const struct { TEXT_08 Hello[16],Open[16]; }T08;
	BYTE_08 Version[16],UTF8[4];
}
Idiom=
{
	.Version=oPENCLIP_INC_,
	.T08=
	{
		.Hello="Hello, world!\r\n",
		.Open={'r','b','\0','\0','w','b','\0','\0','r','t','\0','\0','w','t','\0','\0'}
	},
	.T16=
	{
		.Hello=L"Hello, world!\r\n",
		.Open={L'r',L'b',L'\0',L'\0',L'w',L'b',L'\0',L'\0',L'r',L't',L'\0',L'\0',L'w',L't',L'\0',L'\0'}
	},
	.UTF8={0xEF,0xBB,0xBF,0x00}
};
#endif

#if(Fold_(Function Declarations))
static logical PenC_String_Caster_T16_T08_(ADDRESS,text_16 _PL_ _R_,ADDRESS,TEXT_08 _PL_ _R_);
static logical PenC_String_Caster_T08_T16_(ADDRESS,text_08 _PL_ _R_,ADDRESS,TEXT_16 _PL_ _R_);
#endif

#if(Fold_(File Functions))
static logical xPenC_Reader_1D_T08_(general _PL_ Line,TEXT_08 _PL_ Name,ADDRESS Size,ADDRESS Count)
{
	if(Line)
	{
		integer Error=0;
		logical Success=0;

		PenC_File_Using_(File,Name,PenC.Option.Read.Binary.T08,Error)
		{
			ADDRESS Bytes=Count*Size;

			Success=(Bytes==PenC_File_Reader_(File,(byte_08*)Line,Bytes));
		}

		if(Error);
		else
			return Success;
	}
	else;

	return 0;
}
static logical xPenC_Reader_1D_T16_(general _PL_ Line,TEXT_16 _PL_ Name,ADDRESS Size,ADDRESS Count)
{
	if(Line)
	{
		integer Error=0;
		logical Success=0;

		PenC_File_Using_(File,Name,PenC.Option.Read.Binary.T16,Error)
		{
			ADDRESS Bytes=Count*Size;

			Success=(Bytes==PenC_File_Reader_(File,(byte_08*)Line,Bytes));
		}

		if(Error);
		else
			return Success;
	}
	else;

	return 0;
}
static logical xPenC_Writer_1D_T08_(GENERAL _PL_ Line,TEXT_08 _PL_ Name,ADDRESS Size,ADDRESS Count)
{
	if(Line)
	{
		integer Error=0;
		logical Success=0;

		PenC_File_Using_(File,Name,PenC.Option.Write.Binary.T08,Error)
		{
			ADDRESS Bytes=Count*Size;

			Success=(Bytes==PenC_File_Writer_(File,(byte_08*)Line,Bytes));
		}

		if(Error);
		else
			return Success;
	}
	else;

	return 0;
}
static logical xPenC_Writer_1D_T16_(GENERAL _PL_ Line,TEXT_16 _PL_ Name,ADDRESS Size,ADDRESS Count)
{
	if(Line)
	{
		integer Error=0;
		logical Success=0;

		PenC_File_Using_(File,Name,PenC.Option.Write.Binary.T16,Error)
		{
			ADDRESS Bytes=Count*Size;

			Success=(Bytes==PenC_File_Writer_(File,(byte_08*)Line,Bytes));
		}

		if(Error);
		else
			return Success;
	}
	else;

	return 0;
}

static FILE *PenC_File_Opener_T08_(TEXT_08 _PL_ Name,TEXT_08 _PL_ Mode) { FILE *File;return ((fopen_s(&File,Name,Mode))?(NULL):(File)); }
static FILE *PenC_File_Opener_T16_(TEXT_16 _PL_ Name,TEXT_16 _PL_ Mode)
{
#ifdef xPENC_WIDE_
	FILE *File;

	return ((_wfopen_s(&File,Name,Mode))?(NULL):(File));
#else
	text_08 NameCast[FILENAME_MAX];

	if(PenC_String_Caster_T08_T16_(FILENAME_MAX,NameCast,FILENAME_MAX,Name))
	{
		text_08 ModeCast[4];

		if(PenC_String_Caster_T08_T16_(4,ModeCast,4,Mode))
			return PenC_File_Opener_T08_(NameCast,ModeCast);
		else;
	}
	else;

	return NULL;
#endif
}
static integer PenC_File_Closer_(FILE *_PL_ _R_ File)
{
	if(*File)
	{
		INTEGER Return=fclose(*File);

		*File=NULL;

		return Return;
	}
	else
		return EOF;
}
static integer PenC_File_Verify_(FILE _PL_ _R_ File) { return ferror(File); }

static address xPenC_File_Writer_(FILE _PL_ _R_ File,GENERAL _PL_ _R_ Buffer,ADDRESS Elements,ADDRESS TypeSize) { return fwrite(Buffer,TypeSize,Elements,File); }
static address xPenC_File_Reader_(FILE _PL_ _R_ File,general _PL_ _R_ Buffer,ADDRESS Elements,ADDRESS TypeSize) { return fread(Buffer,TypeSize,Elements,File); }

static integer xPenC_File_Jumper_(FILE _PL_ _R_ File,ADDRESS Nums,ADDRESS Size)
{
	fpos_t Back;
	integer Flag=fgetpos(File,&Back);

	if(Flag);
	else if(Nums&&Size)
	{
		address Rest=MemC.Size.Mul_(Nums,Size);

		if(Rest)
			for(ADDRESS Limit=(address)(((UINTPTR_MAX)<(LONG_MAX))?(UINTPTR_MAX):(LONG_MAX));1;)
				if(Rest>Limit)
				{
					const long Cast=(long)Limit;

					Flag=fseek(File,+Cast,SEEK_CUR);
					if(Flag)
						break;
					else
						Rest-=Limit;
				}
				else
				{
					const long Cast=(long)Rest;

					Flag=fseek(File,+Cast,SEEK_CUR);
					if(Flag)
						break;
					else
						return Flag;
				}
		else
			Flag=EOF;

		fsetpos(File,&Back);
	}
	else;

	return Flag;
}
static integer xPenC_File_Backer_(FILE _PL_ _R_ File,ADDRESS Nums,ADDRESS Size)
{
	fpos_t Back;
	integer Flag=fgetpos(File,&Back);

	if(Flag);
	else if(Nums&&Size)
	{
		address Rest=MemC.Size.Mul_(Nums,Size);

		if(Rest)
			for(ADDRESS Limit=(address)(((UINTPTR_MAX)<(LONG_MAX))?(UINTPTR_MAX):(LONG_MAX));1;)
				if(Rest>Limit)
				{
					const long Cast=(long)Limit;

					Flag=fseek(File,-Cast,SEEK_CUR);
					if(Flag)
						break;
					else
						Rest-=Limit;
				}
				else
				{
					const long Cast=(long)Rest;

					Flag=fseek(File,-Cast,SEEK_CUR);
					if(Flag)
						break;
					else
						return Flag;
				}
		else
			Flag=EOF;

		fsetpos(File,&Back);
	}
	else;

	return Flag;
}

static general xPenC_File_Rewind_(FILE _PL_ _R_ File) { rewind(File);return; }
static long xPenC_File_Teller_(FILE _PL_ _R_ File) { return ftell(File); }

static integer xPenC_File_Washer_(FILE _PL_ _R_ File) { return fflush(File); }
static integer xPenC_File_Finish_(FILE _PL_ _R_ File) { return feof(File); }

static integer xPenC_File_Pose_Get_(FILE _PL_ _R_ File,fpos_t _PL_ _R_ Pose) { return fgetpos(File,Pose); }
static integer xPenC_File_Pose_Set_(FILE _PL_ _R_ File,const fpos_t Pose) { return fsetpos(File,&Pose); }

static integer xPenC_File_Remove_T08_(TEXT_08 _PL_ FileName) { return remove(FileName); }
static integer xPenC_File_Remove_T16_(TEXT_16 _PL_ FileName)
{
#ifdef xPENC_WIDE_
	return _wremove(FileName);
#else
	text_08 NameCast[FILENAME_MAX];

	return ((PenC_String_Caster_T08_T16_(FILENAME_MAX,NameCast,FILENAME_MAX,FileName))?(remove(NameCast)):(EOF));
#endif
}
static integer xPenC_File_Rename_T08_(TEXT_08 _PL_ OldName,TEXT_08 _PL_ NewName) { return rename(OldName,NewName); }
static integer xPenC_File_Rename_T16_(TEXT_16 _PL_ OldName,TEXT_16 _PL_ NewName)
{
#ifdef xPENC_WIDE_
	return _wrename(OldName,NewName);
#else
	text_08 OldCast[FILENAME_MAX];

	if(PenC_String_Caster_T08_T16_(FILENAME_MAX,OldCast,FILENAME_MAX,OldName))
	{
		text_08 NewCast[FILENAME_MAX];

		if(PenC_String_Caster_T08_T16_(FILENAME_MAX,NewCast,FILENAME_MAX,NewName))
			return rename(OldCast,NewCast);
		else;
	}
	else;

	return EOF;
#endif
}

static address PenC_File_Length_T08_(TEXT_08 _PL_ Name)
{
	address Length=0;
	integer Error=0;

	PenC_File_Using_(File,Name,PenC.Option.Read.Binary.T08,Error)
		if(fseek(File,0,SEEK_END));
		else
			Length=(address)ftell(File);

	if(Error)
		Length=0;
	else;

	return Length;
}
static address PenC_File_Length_T16_(TEXT_16 _PL_ Name)
{
	address Length=0;
	integer Error=0;

	PenC_File_Using_(File,Name,PenC.Option.Read.Binary.T16,Error)
		if(fseek(File,0,SEEK_END));
		else
			Length=(address)ftell(File);

	if(Error)
		Length=0;
	else;

	return Length;
}

static logical PenC_Stream_Buffer_T08_(LOGICAL Mode,FILE _PL_ _R_ Stream,ADDRESS Capacity,text_08 _PL_ _R_ Buffer)
{
	if(Mode)
		return (fgets(Buffer,(Capacity<INT_MAX)?((INTEGER)(Capacity)):(INT_MAX),(Stream)?(Stream):(stdin))!=NULL);
	else
		return (fputs(Buffer,(Stream)?(Stream):(stdout))>=0);
}
static logical PenC_Stream_Buffer_T16_(LOGICAL Mode,FILE _PL_ _R_ Stream,ADDRESS Capacity,text_16 _PL_ _R_ Buffer)
{
	if(Mode)
		return (fgetws(Buffer,(Capacity<INT_MAX)?((INTEGER)(Capacity)):(INT_MAX),(Stream)?(Stream):(stdin))!=NULL);
	else
		return (fputws(Buffer,(Stream)?(Stream):(stdout))>=0);
}

static logical PenC_Object_Save_T08_(TEXT_08 _PL_ Name,logical(_PL_ Save_)(FILE _PL_ _R_,GENERAL _PL_ _R_),GENERAL _PL_ _R_ Object,LOGICAL Mode)
{
	if(Save_)
	{
		TEXT_08 _PL_ Format=(Mode)?(PenC.Option.Write.Text.T08):(PenC.Option.Write.Binary.T08);
		integer Error=0;
		logical Flag=0;

		PenC_File_Using_(File,Name,Format,Error)
			Flag=Save_(File,Object);

		return Flag;
	}
	else;

	return 0;
}
static logical PenC_Object_Save_T16_(TEXT_16 _PL_ Name,logical(_PL_ Save_)(FILE _PL_ _R_,GENERAL _PL_ _R_),GENERAL _PL_ _R_ Object,LOGICAL Mode)
{
	if(Save_)
	{
		TEXT_16 _PL_ Format=(Mode)?(PenC.Option.Write.Text.T16):(PenC.Option.Write.Binary.T16);
		integer Error=0;
		logical Flag=0;

		PenC_File_Using_(File,Name,Format,Error)
			Flag=Save_(File,Object);

		return Flag;
	}
	else;

	return 0;
}
static general *PenC_Object_Load_T08_(TEXT_08 _PL_ Name,general*(_PL_ Load_)(FILE _PL_ _R_,general _PL_ _R_),general _PL_ _R_ Option,LOGICAL Mode)
{
	if(Load_)
	{
		TEXT_08 _PL_ Format=(Mode)?(PenC.Option.Read.Text.T08):(PenC.Option.Read.Binary.T08);
		integer Error=0;
		general *Object=NULL;

		PenC_File_Using_(File,Name,Format,Error)
			Object=Load_(File,Option);

		return Object;
	}
	else;

	return NULL;
}
static general *PenC_Object_Load_T16_(TEXT_16 _PL_ Name,general*(_PL_ Load_)(FILE _PL_ _R_,general _PL_ _R_),general _PL_ _R_ Option,LOGICAL Mode)
{
	if(Load_)
	{
		TEXT_16 _PL_ Format=(Mode)?(PenC.Option.Read.Text.T16):(PenC.Option.Read.Binary.T16);
		integer Error=0;
		general *Object=NULL;

		PenC_File_Using_(File,Name,Format,Error)
			Object=Load_(File,Option);

		return Object;
	}
	else;

	return NULL;
}
#endif

#if(Fold_(Character Functions))
static general PenC_Setter_T08_(text_08 _PL_ _R_ Buffer,TEXT_08 Value,ADDRESS Count) { memset(Buffer,Value,Count);return; }
static general PenC_Setter_T16_(text_16 _PL_ _R_ Buffer,TEXT_16 Value,ADDRESS Count) { wmemset(Buffer,Value,Count);return; }

static text_08 *PenC_Finder_T08_(text_08 _PL_ _R_ Buffer,TEXT_08 Value,ADDRESS Count) { return memchr(Buffer,Value,Count); }
static text_16 *PenC_Finder_T16_(text_16 _PL_ _R_ Buffer,TEXT_16 Value,ADDRESS Count) { return wmemchr(Buffer,Value,Count); }
#endif

#if(Fold_(String Functions))
static logical PenC_String_Caster_T16_T08_(ADDRESS CapacityT,text_16 _PL_ _R_ StringT,ADDRESS CapacityS,TEXT_08 _PL_ _R_ StringS)
{
	address Lng;

	{
		TEXT_08 *PinS=StringS;
		mbstate_t State={0};

		if(mbsrtowcs_s(&Lng,NULL,0,&PinS,0,&State))
			return 0;
		else if(Lng<CapacityS)
			Lng++;
		else
			return 0;
	}
	{
		TEXT_08 *PinS=StringS;
		mbstate_t State={0};

		return (mbsrtowcs_s(&Lng,StringT,CapacityT,&PinS,Lng,&State)==0);
	}
}
static logical PenC_String_Caster_T08_T16_(ADDRESS CapacityT,text_08 _PL_ _R_ StringT,ADDRESS CapacityS,TEXT_16 _PL_ _R_ StringS)
{
	address Lng;

	{
		TEXT_16 *PinS=StringS;
		mbstate_t State={0};

		if(wcsrtombs_s(&Lng,NULL,0,&PinS,0,&State))
			return 0;
		else if(Lng<CapacityS)
			Lng++;
		else
			return 0;
	}
	{
		TEXT_16 *PinS=StringS;
		mbstate_t State={0};

		return (wcsrtombs_s(&Lng,StringT,CapacityT,&PinS,Lng,&State)==0);
	}
}

static address PenC_String_Length_T08_(ADDRESS Capacity,TEXT_08 _PL_ _R_ String) { return strnlen_s(String,Capacity); }
static address PenC_String_Length_T16_(ADDRESS Capacity,TEXT_16 _PL_ _R_ String) { return wcsnlen_s(String,Capacity); }

static text_08 *PenC_String_Finder_T08_(text_08 _PL_ _R_ String,TEXT_08 _PL_ _R_ SubString) { return strstr(String,SubString); }
static text_16 *PenC_String_Finder_T16_(text_16 _PL_ _R_ String,TEXT_16 _PL_ _R_ SubString) { return wcsstr(String,SubString); }

static logical PenC_String_Concat_T08_(ADDRESS Capacity,text_08 _PL_ _R_ Buffer,TEXT_08 _PL_ _R_ Source) { return (strcat_s(Buffer,Capacity,Source)==0); }
static logical PenC_String_Concat_T16_(ADDRESS Capacity,text_16 _PL_ _R_ Buffer,TEXT_16 _PL_ _R_ Source) { return (wcscat_s(Buffer,Capacity,Source)==0); }

static logical PenC_String_Copier_T08_(ADDRESS Capacity,text_08 _PL_ _R_ Buffer,TEXT_08 _PL_ _R_ Source) { return (strcpy_s(Buffer,Capacity,Source)==0); }
static logical PenC_String_Copier_T16_(ADDRESS Capacity,text_16 _PL_ _R_ Buffer,TEXT_16 _PL_ _R_ Source) { return (wcscpy_s(Buffer,Capacity,Source)==0); }

static integer PenC_String_Compar_T08_(TEXT_08 _PL_ A,TEXT_08 _PL_ B) { return strcmp(A,B); }
static integer PenC_String_Compar_T16_(TEXT_16 _PL_ A,TEXT_16 _PL_ B) { return wcscmp(A,B); }
#endif

#if(Fold_(Advanced Object Functions))
static general PenC_Delete_(general *_PL_ _R_ Object) { MemC_Deloc_(*Object);return; }

#if(Fold_(PenC_SC))
static general xPenC_SC_Bound_(PENC_SC _PL_ _R_ SC)
{
	address Temp=SC->Capacity;

	if(Temp)
	{
		SC->String.T08[0]=0x00;
		SC->String.T08[Temp-1]=0x00;
		Temp>>=1;

		if(Temp)
		{
			SC->String.T16[0]=0x0000;
			SC->String.T16[Temp-1]=0x0000;
		}
		else;
	}
	else;

	return;
}
static penc_sc *PenC_SC_Create_(ADDRESS Capacity)
{
	penc_sc *SC;
	
	if(Capacity<xPENC_SC_MAX_)
		if(Capacity)
		{
			SC=MemC.Alloc.Byte_(MemC.Size.Add_(Capacity,sizeof(penc_sc)));
			if(SC)
			{
				Acs_(address,SC->Capacity)=Capacity;
				Acs_(text_08*,SC->String.T08)=(text_08*)(SC+1);
				xPenC_SC_Bound_(SC);
			}
			else;
		}
		else
		{
			SC=MemC_Alloc_Unit_(penc_sc);
			if(SC)
				MemC_Clear_Unit_(SC);
			else;
		}
	else
		SC=NULL;

	return SC;
}
static address PenC_SC_Size_(PENC_SC _PL_ _R_ SC) { return ((SC)?(sizeof(penc_sc)+(SC->Capacity)):(0)); }

static general PenC_SC_Init_(PENC_SC _PL_ _R_ SC) { MemC_Clear_1D_(SC->String.T08,SC->Capacity);return; }
static general PenC_SC_Shut_T08_(PENC_SC _PL_ _R_ SC) { SC->String.T08[SC->Capacity-1]=0;return; }
static general PenC_SC_Shut_T16_(PENC_SC _PL_ _R_ SC) { SC->String.T16[(SC->Capacity>>1)-1]=0;return; }

static logical PenC_SC_Caster_T08_T16_(PENC_SC _PL_ _R_ Target,PENC_SC _PL_ _R_ Source) { return PenC_String_Caster_T08_T16_(Target->Capacity,Target->String.T08,Source->Capacity>>1,Source->String.T16); }
static logical PenC_SC_Caster_T16_T08_(PENC_SC _PL_ _R_ Target,PENC_SC _PL_ _R_ Source) { return PenC_String_Caster_T16_T08_(Target->Capacity>>1,Target->String.T16,Source->Capacity,Source->String.T08); }

static address PenC_SC_Length_T08_(PENC_SC _PL_ _R_ SC) { return PenC_String_Length_T08_(SC->Capacity,SC->String.T08); }
static address PenC_SC_Length_T16_(PENC_SC _PL_ _R_ SC) { return PenC_String_Length_T16_(SC->Capacity>>1,SC->String.T16); }

static logical PenC_SC_Copier_T08_(PENC_SC _PL_ _R_ Target,PENC_SC _PL_ _R_ Source) { return PenC_String_Copier_T08_(Target->Capacity,Target->String.T08,Source->String.T08); }
static logical PenC_SC_Copier_T16_(PENC_SC _PL_ _R_ Target,PENC_SC _PL_ _R_ Source) { return PenC_String_Copier_T16_(Target->Capacity>>1,Target->String.T16,Source->String.T16); }

static logical PenC_SC_Concat_T08_(PENC_SC _PL_ _R_ Target,PENC_SC _PL_ _R_ Source) { return PenC_String_Concat_T08_(Target->Capacity,Target->String.T08,Source->String.T08); }
static logical PenC_SC_Concat_T16_(PENC_SC _PL_ _R_ Target,PENC_SC _PL_ _R_ Source) { return PenC_String_Concat_T16_(Target->Capacity>>1,Target->String.T16,Source->String.T16); }

static integer PenC_SC_Compar_T08_(PENC_SC _PL_ A,PENC_SC _PL_ B) { return PenC_String_Compar_T08_(A->String.T08,B->String.T08); }
static integer PenC_SC_Compar_T16_(PENC_SC _PL_ A,PENC_SC _PL_ B) { return PenC_String_Compar_T16_(A->String.T16,B->String.T16); }

static logical PenC_SC_Stream_T08_(LOGICAL Mode,FILE _PL_ _R_ Stream,PENC_SC _PL_ _R_ SC) { return PenC_Stream_Buffer_T08_(Mode,Stream,SC->Capacity,SC->String.T08); }
static logical PenC_SC_Stream_T16_(LOGICAL Mode,FILE _PL_ _R_ Stream,PENC_SC _PL_ _R_ SC) { return PenC_Stream_Buffer_T16_(Mode,Stream,SC->Capacity>>1,SC->String.T16); }
#endif

#if(Fold_(PenC_SL))
MemC_Type_Declare_(struct,penc_sn,PENC_SN);
struct _penc_sn { penc_sn *Link[2];penc_sc Data; };

static_assert((sizeof(penc_sn)==sizeof(penc_sl)),"sizeof(penc_sn) != sizeof(penc_sl)");
static_assert((sizeof(penc_sn)==(sizeof(address)<<2)),"sizeof(penc_sn) != 4*sizeof(address)");

static penc_sl *PenC_SL_Create_(ADDRESS Chunks)
{
	penc_sl _PL_ SL=MemC.Alloc.Byte_(MemC.Size.Mul_(Chunks+1,sizeof(penc_sn)));

	if(SL)
		if(Chunks)
		{
			penc_sn _PL_ Node=(penc_sn*)(SL+1);

			Acs_(penc_sn*,SL->Node)=Node;
			Acs_(address,SL->Chunks)=Chunks;
			Acs_(address,SL->Nodes)=1;
			Acs_(address,SL->Capable)=MemC_Size_(penc_sn,Chunks-1);

			Node->Link[0]=NULL;
			Node->Link[1]=NULL;
			Acs_(address,Node->Data.Capacity)=SL->Capable;
			Acs_(general*,Node->Data.String.X)=NULL;
		}
		else
			MemC_Clear_Unit_(SL);
	else;

	return SL;
}

static address PenC_SL_Size_(PENC_SL _PL_ _R_ SL) { return ((SL)?(MemC_Size_(penc_sn,SL->Chunks+1)):(0)); }
static logical PenC_SL_Reset_(penc_sl _PL_ _R_ SL)
{
	if(SL)
	{
		if(SL->Chunks)
		{
			{
				Acs_(address,SL->Nodes)=1;
				Acs_(address,SL->Capable)=MemC_Size_(penc_sn,SL->Chunks-1);
			}
			{
				penc_sn _PL_ Node=(penc_sn*)(SL->Node);

				Node->Link[0]=NULL;
				Node->Link[1]=NULL;
				Acs_(address,Node->Data.Capacity)=SL->Capable;
				Acs_(general*,Node->Data.String.X)=NULL;
			}
		}
		else
			MemC_Clear_Unit_(SL);

		return 1;
	}
	else
		return 0;
}

static address xPenC_SN_Margin_(address Number)
{
	Number--;
	Number+=sizeof(penc_sn);
	Number/=sizeof(penc_sn);
	Number*=sizeof(penc_sn);

	return Number;
}
static penc_sn *xPenC_SN_Search_Space_(penc_sn *_R_ Ptr,ADDRESS Demand)
{
	penc_sn *Mark=NULL;

	for(address Temp=MemC.Full.V;Ptr;Ptr=Ptr->Link[1])
		if(Ptr->Data.String.X);
		else if(Demand>Ptr->Data.Capacity);
		else if(Temp>Ptr->Data.Capacity)
		{
			Temp=Ptr->Data.Capacity;
			Mark=Ptr;
		}
		else;

	return Mark;
}
static address xPenC_SN_Search_Size_(penc_sn *_R_ Ptr)
{
	address Temp;

	for(Temp=0;Ptr;Ptr=Ptr->Link[1])
		if(Ptr->Data.String.X);
		else if(Temp<Ptr->Data.Capacity)
			Temp=Ptr->Data.Capacity;
		else;

	return Temp;
}
static penc_sn *xPenC_SN_Search_Node_(penc_sn *_R_ Ptr,PENC_SC _PL_ SC)
{
	while(Ptr)
		if(&(Ptr->Data)==SC)
			break;
		else
			Ptr=Ptr->Link[1];

	return Ptr;
}
static address xPenC_SN_Borrow_(penc_sn _PL_ Node,ADDRESS Demand)
{
	address Return;
	
	if(Demand<Node->Data.Capacity)
	{
		if(Node->Link[1])
		{
			Node->Link[1]->Link[0]=(penc_sn*)((address)(Node+1)+Demand);
			Node->Link[1]->Link[0]->Link[1]=Node->Link[1];
			Node->Link[1]=Node->Link[1]->Link[0];
		}
		else
		{
			Node->Link[1]=(penc_sn*)((address)(Node+1)+Demand);
			Node->Link[1]->Link[1]=NULL;
		}
		{
			Node->Link[1]->Link[0]=Node;

			Acs_(address,Node->Link[1]->Data.Capacity)=Node->Data.Capacity-Demand-sizeof(penc_sn);
			Acs_(general*,Node->Link[1]->Data.String.X)=NULL;

			Acs_(address,Node->Data.Capacity)=Demand;
			Return=1;
		}
	}
	else
		Return=0;

	if(Node->Data.Capacity)
	{
		Acs_(general*,Node->Data.String.X)=Node+1;
		((address*)(Node->Data.String.X))[0]=0;
		((address*)(Node->Data.String.X))[(Node->Data.Capacity/sizeof(address))-1]=0;
	}
	else
		Acs_(general*,Node->Data.String.X)=FULL;

	return Return;
}
static general xPenC_SN_Attach_(penc_sn _PL_ Node)
{
	Acs_(address,Node->Data.Capacity)+=sizeof(penc_sn);
	Acs_(address,Node->Data.Capacity)+=Node->Link[1]->Data.Capacity;

	Node->Link[1]=Node->Link[1]->Link[1];
	if(Node->Link[1])
		Node->Link[1]->Link[0]=Node;
	else;

	return;
}
static address xPenC_SN_Return_(penc_sn *_PL_ _R_ Node)
{
	address Return=0;

	if((*Node)->Link[0])
		if((*Node)->Link[0]->Data.String.X);
		else
		{
			xPenC_SN_Attach_(*Node=(*Node)->Link[0]);
			Return++;
		}
	else;

	if((*Node)->Link[1])
		if((*Node)->Link[1]->Data.String.X);
		else
		{
			xPenC_SN_Attach_(*Node);
			Return++;
		}
	else;

	Acs_(general*,(*Node)->Data.String.X)=NULL;

	return Return;
}
static penc_sc *PenC_SL_Borrow_(penc_sl _PL_ _R_ SL,ADDRESS Demand)
{
	if(SL)
		if(Demand<xPENC_SC_MAX_)
		{
			penc_sn _PL_ Node=(penc_sn*)(SL->Node);
			ADDRESS Margin=xPenC_SN_Margin_(Demand);

			if(Margin>SL->Capable);
			else
			{
				penc_sn _PL_ This=xPenC_SN_Search_Space_(Node,Margin);

				if(This)
				{
					if(This->Data.Capacity==SL->Capable)
					{
						Acs_(address,SL->Nodes)+=xPenC_SN_Borrow_(This,Margin);
						Acs_(address,SL->Capable)=xPenC_SN_Search_Size_(Node);
					}
					else
						Acs_(address,SL->Nodes)+=xPenC_SN_Borrow_(This,Margin);

					return &(This->Data);
				}
				else;
			}
		}
		else;
	else;

	return NULL;
}
static logical PenC_SL_Return_(penc_sl _PL_ _R_ SL,penc_sc *_PL_ _R_ SC)
{
	if(SL)
		if(*SC)
		{
			penc_sn *Node=xPenC_SN_Search_Node_((penc_sn*)(SL->Node),*SC);

			if(Node)
			{
				Acs_(address,SL->Nodes)-=xPenC_SN_Return_(&Node);
				if(Node->Data.Capacity>SL->Capable)
					Acs_(address,SL->Capable)=Node->Data.Capacity;
				else;

				*SC=NULL;

				return 1;
			}
			else;
		}
		else;
	else;

	return 0;
}

static penc_sc *PenC_SL_Borrow_Copier_T08_(penc_sl _PL_ _R_ SL,PENC_SC _PL_ _R_ Source)
{
	penc_sc *Target=PenC_SL_Borrow_(SL,PenC_SC_Length_T08_(Source)+1);

	if(Target)
		if(PenC_SC_Copier_T08_(Target,Source));
		else
			PenC_SL_Return_(SL,&Target);
	else;

	return Target;
}
static penc_sc *PenC_SL_Borrow_Copier_T16_(penc_sl _PL_ _R_ SL,PENC_SC _PL_ _R_ Source)
{
	penc_sc *Target=PenC_SL_Borrow_(SL,(PenC_SC_Length_T16_(Source)+1)<<1);

	if(Target)
		if(PenC_SC_Copier_T16_(Target,Source));
		else
			PenC_SL_Return_(SL,&Target);
	else;

	return Target;
}
static penc_sc *PenC_SL_Borrow_Concat_T08_(penc_sl _PL_ _R_ SL,PENC_SC _PL_ Former,PENC_SC _PL_ Latter)
{
	penc_sc *Concat=PenC_SL_Borrow_(SL,PenC_SC_Length_T08_(Former)+PenC_SC_Length_T08_(Latter)+1);

	if(Concat)
		if(PenC_SC_Copier_T08_(Concat,Former))
			if(PenC_SC_Concat_T08_(Concat,Latter));
			else
				PenC_SL_Return_(SL,&Concat);
		else
			PenC_SL_Return_(SL,&Concat);
	else;

	return Concat;
}
static penc_sc *PenC_SL_Borrow_Concat_T16_(penc_sl _PL_ _R_ SL,PENC_SC _PL_ Former,PENC_SC _PL_ Latter)
{
	penc_sc *Concat=PenC_SL_Borrow_(SL,(PenC_SC_Length_T16_(Former)+PenC_SC_Length_T16_(Latter)+1)<<1);

	if(Concat)
		if(PenC_SC_Copier_T16_(Concat,Former))
			if(PenC_SC_Concat_T16_(Concat,Latter));
			else
				PenC_SL_Return_(SL,&Concat);
		else
			PenC_SL_Return_(SL,&Concat);
	else;

	return Concat;
}
#endif
#endif

#if(Fold_(Library Casing))
static_assert(sizeof(PENCASE)==(sizeof(ADDRESS)*96),"sizeof(PENCASE) != 96*sizeof(ADDRESS)");
extern PENCASE PenC=
{
	{
		.Version=Idiom.Version,
		.Signature=Idiom.UTF8,
		.Hello=
		{
			.T08=Idiom.T08.Hello,
			.T16=Idiom.T16.Hello
		},
		.Option=
		{
			.Read=
			{
				.Binary=
				{
					.T08=Idiom.T08.Open+0,
					.T16=Idiom.T16.Open+0
				},
				.Text=
				{
					.T08=Idiom.T08.Open+8,
					.T16=Idiom.T16.Open+8
				}
			},
			.Write=
			{
				.Binary=
				{
					.T08=Idiom.T08.Open+4,
					.T16=Idiom.T16.Open+4
				},
				.Text=
				{
					.T08=Idiom.T08.Open+12,
					.T16=Idiom.T16.Open+12
				}
			}
		}
	},
	.Set=
	{
		.T08_=PenC_Setter_T08_,
		.T16_=PenC_Setter_T16_
	},
	.Find=
	{
		.T08_=PenC_Finder_T08_,
		.T16_=PenC_Finder_T16_
	},
	.String=
	{
		.Conv=
		{
			.T08.T16_=PenC_String_Caster_T08_T16_,
			.T16.T08_=PenC_String_Caster_T16_T08_
		},
		.Length=
		{
			.T08_=PenC_String_Length_T08_,
			.T16_=PenC_String_Length_T16_
		},
		.Find=
		{
			.T08_=PenC_String_Finder_T08_,
			.T16_=PenC_String_Finder_T16_
		},
		.Copy=
		{
			.T08_=PenC_String_Copier_T08_,
			.T16_=PenC_String_Copier_T16_
		},
		.Conc=
		{
			.T08_=PenC_String_Concat_T08_,
			.T16_=PenC_String_Concat_T16_
		},
		.Comp=
		{
			.T08_=PenC_String_Compar_T08_,
			.T16_=PenC_String_Compar_T16_
		}
	},
	.File=
	{
		{
			.Opener=
			{
				.T08_=PenC_File_Opener_T08_,
				.T16_=PenC_File_Opener_T16_
			},
			.Closer_=PenC_File_Closer_,
			.Verify_=PenC_File_Verify_
		},
		{
			.Writer_=xPenC_File_Writer_,
			.Reader_=xPenC_File_Reader_,
			.Jumper_=xPenC_File_Jumper_,
			.Backer_=xPenC_File_Backer_
		},
		{
			.Rewind_=xPenC_File_Rewind_,
			.Teller_=xPenC_File_Teller_,
			.Washer_=xPenC_File_Washer_,
			.Finish_=xPenC_File_Finish_
		},
		.Pose=
		{
			.Get_=xPenC_File_Pose_Get_,
			.Set_=xPenC_File_Pose_Set_
		},
		.Remove=
		{
			.T08_=xPenC_File_Remove_T08_,
			.T16_=xPenC_File_Remove_T16_
		},
		.Rename=
		{
			.T08_=xPenC_File_Rename_T08_,
			.T16_=xPenC_File_Rename_T16_
		},
		.Length=
		{
			.T08_=PenC_File_Length_T08_,
			.T16_=PenC_File_Length_T16_
		}
	},
	.Stream=
	{
		.Buffer=
		{
			.T08_=PenC_Stream_Buffer_T08_,
			.T16_=PenC_Stream_Buffer_T16_
		},
		.SC=
		{
			.T08_=PenC_SC_Stream_T08_,
			.T16_=PenC_SC_Stream_T16_
		}
	},
	.Buffer=
	{
		.Stream=
		{
			.T08_=PenC_Stream_Buffer_T08_,
			.T16_=PenC_Stream_Buffer_T16_
		},
		.Reader=
		{
			.T08_=xPenC_Reader_1D_T08_,
			.T16_=xPenC_Reader_1D_T16_
		},
		.Writer=
		{
			.T08_=xPenC_Writer_1D_T08_,
			.T16_=xPenC_Writer_1D_T16_
		}
	},
	.Object=
	{
		.Save=
		{
			.T08_=PenC_Object_Save_T08_,
			.T16_=PenC_Object_Save_T16_
		},
		.Load=
		{
			.T08_=PenC_Object_Load_T08_,
			.T16_=PenC_Object_Load_T16_
		}
	},
	.SC=
	{
		{
			.Create_=PenC_SC_Create_,
			.Delete_=MemC_Func_Casting_(general,PenC_Delete_,penc_sc *_PL_ _R_),
			.Size_=PenC_SC_Size_,
			.Init_=PenC_SC_Init_
		},
		.Shut=
		{
			.T08_=PenC_SC_Shut_T08_,
			.T16_=PenC_SC_Shut_T16_
		},
		.Conv=
		{
			.T08.T16_=PenC_SC_Caster_T08_T16_,
			.T16.T08_=PenC_SC_Caster_T16_T08_
		},
		.Length=
		{
			.T08_=PenC_SC_Length_T08_,
			.T16_=PenC_SC_Length_T16_
		},
		.Copy=
		{
			.T08_=PenC_SC_Copier_T08_,
			.T16_=PenC_SC_Copier_T16_
		},
		.Conc=
		{
			.T08_=PenC_SC_Concat_T08_,
			.T16_=PenC_SC_Concat_T16_
		},
		.Comp=
		{
			.T08_=PenC_SC_Compar_T08_,
			.T16_=PenC_SC_Compar_T16_
		},
		.Stream=
		{
			.T08_=PenC_SC_Stream_T08_,
			.T16_=PenC_SC_Stream_T16_
		}
	},
	.SL=
	{
		{
			.Create_=PenC_SL_Create_,
			.Delete_=MemC_Func_Casting_(general,PenC_Delete_,penc_sl *_PL_ _R_),
			.Size_=PenC_SL_Size_,
			.Reset_=PenC_SL_Reset_
		},
		{
			.Return_=PenC_SL_Return_,
			.Borrow_=PenC_SL_Borrow_
		},
		.Borrow=
		{
			.Copy=
			{
				.T08_=PenC_SL_Borrow_Copier_T08_,
				.T16_=PenC_SL_Borrow_Copier_T16_
			},
			.Conc=
			{
				.T08_=PenC_SL_Borrow_Concat_T08_,
				.T16_=PenC_SL_Borrow_Concat_T16_
			}
		}
	}
};
extern PENCASE *PenC_(general) { return &PenC; }
#endif
