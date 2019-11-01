#include "penclip.h"

#include <limits.h>
#include <stdint.h>

#if(Fold_(Static Assertions))
MemC_Type_Declare_(struct,penc_sn,PENC_SN);
struct _penc_sn { penc_sn *Link[2];penc_sc Data; };

static_assert((sizeof(text_08)==1),"sizeof(text_08) != 1");
static_assert((sizeof(text_16)==2),"sizeof(text_16) != 2");
static_assert((sizeof(integer)<=sizeof(address)),"sizeof(integer) > sizeof(address)");
static_assert(+(LONG_MIN)<-(LONG_MAX),"|LONG_MIN| < |LONG_MAX|");
static_assert((sizeof(penc_sn)==sizeof(penc_sl)),"sizeof(penc_sn) != sizeof(penc_sl)");
static_assert((sizeof(penc_sn)==(sizeof(address)<<2)),"sizeof(penc_sn) != 4*sizeof(address)");
#endif

#if(Fold_(Definition:PenClip Macros))
#define _PENC_ static
#define _PENC_SC_MAX_ ((address)(((address)(1))<<(sizeof(address)<<2)))
#endif

#if(Fold_(Definition:Internal Constants))
_PENC_ BYTE_08 IdiomVersion[16]="Date:2019.11.01";
_PENC_ TEXT_08 IdiomHello08[16]="Hello, world!\r\n";
_PENC_ TEXT_16 IdiomHello16[16]=L"Hello, world!\r\n";
static TEXT_08 IdiomOpen08[16]={'r','b','\0','\0','w','b','\0','\0','r','t','\0','\0','w','t','\0','\0'};
static TEXT_16 IdiomOpen16[16]={L'r',L'b',L'\0',L'\0',L'w',L'b',L'\0',L'\0',L'r',L't',L'\0',L'\0',L'w',L't',L'\0',L'\0'};
#endif

#if(Fold_(Definition:File Functions))
_PENC_ logical _PenC_Reader_1D_T08_(general _PL_ Line,TEXT_08 _PL_ Name,ADDRESS Size,ADDRESS Count)
{
	if(Line)
	{
		integer Error=EOF;
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
_PENC_ logical _PenC_Reader_1D_T16_(general _PL_ Line,TEXT_16 _PL_ Name,ADDRESS Size,ADDRESS Count)
{
	if(Line)
	{
		integer Error=EOF;
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
_PENC_ logical _PenC_Writer_1D_T08_(GENERAL _PL_ Line,TEXT_08 _PL_ Name,ADDRESS Size,ADDRESS Count)
{
	if(Line)
	{
		integer Error=EOF;
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
_PENC_ logical _PenC_Writer_1D_T16_(GENERAL _PL_ Line,TEXT_16 _PL_ Name,ADDRESS Size,ADDRESS Count)
{
	if(Line)
	{
		integer Error=EOF;
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

_PENC_ FILE *PenC_File_Opener_T08_(TEXT_08 _PL_ Name,TEXT_08 _PL_ Mode)
{
	FILE *File;
	
	return ((fopen_s(&File,Name,Mode))?(NULL):(File));
}
_PENC_ FILE *PenC_File_Opener_T16_(TEXT_16 _PL_ Name,TEXT_16 _PL_ Mode)
{
#if defined(_MSC_BUILD)||defined(__POCC__)
	FILE *File;

	return ((_wfopen_s(&File,Name,Mode))?(NULL):(File));
#else
	text_08 NameCast[FILENAME_MAX];

	if(PenC.String.Caster.T16_T08_(Name,NameCast,FILENAME_MAX,FILENAME_MAX))
	{
		text_08 ModeCast[4];

		if(PenC.String.Caster.T16_T08_(Mode,ModeCast,4,4))
			return PenC_File_Opener_T08_(NameCast,ModeCast);
		else;
	}
	else;

	return NULL;
#endif
}
_PENC_ integer PenC_File_Closer_(FILE *_PL_ File)
{
	integer Return;
	
	if(*File)
	{
		Return=fclose(*File);
		*File=NULL;
	}
	else
		Return=EOF;

	return Return;
}

_PENC_ address _PenC_File_Writer_(FILE _PL_ File,GENERAL _PL_ Buffer,ADDRESS Elements,ADDRESS TypeSize)
{
	return fwrite(Buffer,TypeSize,Elements,File);
}
_PENC_ address _PenC_File_Reader_(FILE _PL_ File,general _PL_ Buffer,ADDRESS Elements,ADDRESS TypeSize)
{
	return fread(Buffer,TypeSize,Elements,File);
}

_PENC_ integer _PenC_File_Jumper_(FILE _PL_ File,ADDRESS Nums,ADDRESS Size)
{
	fpos_t Back;
	integer Flag=fgetpos(File,&Back);

	if(Flag);
	else if(Nums&&Size)
	{
		address Rest=MemC.Size.Mul_(Nums,Size);

		if(Rest)
			for(ADDRESS Limit=(address)(((SIZE_MAX)<(LONG_MAX))?(SIZE_MAX):(LONG_MAX));1;)
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
_PENC_ integer _PenC_File_Backer_(FILE _PL_ File,ADDRESS Nums,ADDRESS Size)
{
	fpos_t Back;
	integer Flag=fgetpos(File,&Back);

	if(Flag);
	else if(Nums&&Size)
	{
		address Rest=MemC.Size.Mul_(Nums,Size);

		if(Rest)
			for(ADDRESS Limit=(address)(((SIZE_MAX)<(LONG_MAX))?(SIZE_MAX):(LONG_MAX));1;)
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

_PENC_ general _PenC_File_Rewind_(FILE _PL_ File)
{
	rewind(File);
}
_PENC_ long _PenC_File_Teller_(FILE _PL_ File)
{
	return ftell(File);
}

_PENC_ integer _PenC_File_Washer_(FILE _PL_ File)
{
	return fflush(File);
}
_PENC_ integer _PenC_File_Finish_(FILE _PL_ File)
{
	return feof(File);
}

_PENC_ integer _PenC_File_Pose_Get_(FILE _PL_ File,fpos_t _PL_ Pose)
{
	return fgetpos(File,Pose);
}
_PENC_ integer _PenC_File_Pose_Set_(FILE _PL_ File,const fpos_t Pose)
{
	return fsetpos(File,&Pose);
}

_PENC_ integer _PenC_File_Remove_T08_(TEXT_08 _PL_ FileName)
{
	return remove(FileName);
}
_PENC_ integer _PenC_File_Remove_T16_(TEXT_16 _PL_ FileName)
{
	return _wremove(FileName);
}
_PENC_ integer _PenC_File_Rename_T08_(TEXT_08 _PL_ OldName,TEXT_08 _PL_ NewName)
{
	return rename(OldName,NewName);
}
_PENC_ integer _PenC_File_Rename_T16_(TEXT_16 _PL_ OldName,TEXT_16 _PL_ NewName)
{
	return _wrename(OldName,NewName);
}

_PENC_ address PenC_File_Length_T08_(TEXT_08 _PL_ Name)
{
	address Length=0;
	integer Error=EOF;

	PenC_File_Using_(File,Name,PenC.Option.Read.Binary.T08,Error)
		if(!fseek(File,0,SEEK_END))
			Length=(address)ftell(File);

	if(Error)
		Length=0;

	return Length;
}
_PENC_ address PenC_File_Length_T16_(TEXT_16 _PL_ Name)
{
	address Length=0;
	integer Error=EOF;

	PenC_File_Using_(File,Name,PenC.Option.Read.Binary.T16,Error)
		if(!fseek(File,0,SEEK_END))
			Length=(address)ftell(File);

	if(Error)
		Length=0;

	return Length;
}

_PENC_ address PenC_Stream_Buffer_T08_(LOGICAL Mode,FILE _PL_ Stream,text_08 _PL_ Buffer,ADDRESS Capacity)
{
	return ((Mode)?((address)fgets(Buffer,(Capacity<INT_MAX)?((INTEGER)(Capacity)):(INT_MAX),(Stream)?(Stream):(stdin))):((address)fputs(Buffer,(Stream)?(Stream):(stdout))));
}
_PENC_ address PenC_Stream_Buffer_T16_(LOGICAL Mode,FILE _PL_ Stream,text_16 _PL_ Buffer,ADDRESS Capacity)
{
	return ((Mode)?((address)fgetws(Buffer,(Capacity<INT_MAX)?((INTEGER)(Capacity)):(INT_MAX),(Stream)?(Stream):(stdin))):((address)fputws(Buffer,(Stream)?(Stream):(stdout))));
}

_PENC_ logical PenC_Object_Save_T08_(TEXT_08 _PL_ Name,logical(_PL_ Save_)(FILE _PL_,GENERAL _PL_ _R_),GENERAL _PL_ _R_ Object,LOGICAL Mode)
{
	if(Save_)
	{
		TEXT_08 _PL_ Format=(Mode)?(PenC.Option.Write.Text.T08):(PenC.Option.Write.Binary.T08);
		integer Error=EOF;
		logical Flag=0;

		PenC_File_Using_(File,Name,Format,Error)
			Flag=Save_(File,Object);

		return Flag;
	}
	else;

	return 0;
}
_PENC_ logical PenC_Object_Save_T16_(TEXT_16 _PL_ Name,logical(_PL_ Save_)(FILE _PL_,GENERAL _PL_ _R_),GENERAL _PL_ _R_ Object,LOGICAL Mode)
{
	if(Save_)
	{
		TEXT_16 _PL_ Format=(Mode)?(PenC.Option.Write.Text.T16):(PenC.Option.Write.Binary.T16);
		integer Error=EOF;
		logical Flag=0;

		PenC_File_Using_(File,Name,Format,Error)
			Flag=Save_(File,Object);

		return Flag;
	}
	else;

	return 0;
}
_PENC_ general *PenC_Object_Load_T08_(TEXT_08 _PL_ Name,general*(_PL_ Load_)(FILE _PL_,general _PL_ _R_),general _PL_ _R_ Option,LOGICAL Mode)
{
	if(Load_)
	{
		TEXT_08 _PL_ Format=(Mode)?(PenC.Option.Read.Text.T08):(PenC.Option.Read.Binary.T08);
		integer Error=EOF;
		general *Object=NULL;

		PenC_File_Using_(File,Name,Format,Error)
			Object=Load_(File,Option);

		return Object;
	}
	else;

	return NULL;
}
_PENC_ general *PenC_Object_Load_T16_(TEXT_16 _PL_ Name,general*(_PL_ Load_)(FILE _PL_,general _PL_ _R_),general _PL_ _R_ Option,LOGICAL Mode)
{
	if(Load_)
	{
		TEXT_16 _PL_ Format=(Mode)?(PenC.Option.Read.Text.T16):(PenC.Option.Read.Binary.T16);
		integer Error=EOF;
		general *Object=NULL;

		PenC_File_Using_(File,Name,Format,Error)
			Object=Load_(File,Option);

		return Object;
	}
	else;

	return NULL;
}
#endif

#if(Fold_(Definition:Character Functions))
_PENC_ general PenC_Setter_T08_(text_08 _PL_ Buffer,TEXT_08 Value,ADDRESS Count)
{
	memset(Buffer,Value,Count);
}
_PENC_ general PenC_Setter_T16_(text_16 _PL_ Buffer,TEXT_16 Value,ADDRESS Count)
{
	wmemset(Buffer,Value,Count);
}

_PENC_ text_08 *PenC_Finder_T08_(text_08 _PL_ Buffer,TEXT_08 Value,ADDRESS Count)
{
	return memchr(Buffer,Value,Count);
}
_PENC_ text_16 *PenC_Finder_T16_(text_16 _PL_ Buffer,TEXT_16 Value,ADDRESS Count)
{
	return wmemchr(Buffer,Value,Count);
}
#endif

#if(Fold_(Definition:String Functions))
_PENC_ logical PenC_String_Caster_T08_T16_(TEXT_08 _PL_ StringS,text_16 _PL_ StringT,ADDRESS CapacityS,ADDRESS CapacityT)
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
_PENC_ logical PenC_String_Caster_T16_T08_(TEXT_16 _PL_ StringS,text_08 _PL_ StringT,ADDRESS CapacityS,ADDRESS CapacityT)
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

_PENC_ address PenC_String_Length_T08_(TEXT_08 _PL_ String,ADDRESS Capacity)
{
	return strnlen_s(String,Capacity);
}
_PENC_ address PenC_String_Length_T16_(TEXT_16 _PL_ String,ADDRESS Capacity)
{
	return wcsnlen_s(String,Capacity);
}

_PENC_ text_08 *PenC_String_Finder_T08_(TEXT_08 _PL_ String,TEXT_08 _PL_ SubString)
{
	return strstr(String,SubString);
}
_PENC_ text_16 *PenC_String_Finder_T16_(TEXT_16 _PL_ String,TEXT_16 _PL_ SubString)
{
	return wcsstr(String,SubString);
}

_PENC_ logical PenC_String_Concat_T08_(text_08 _PL_ Buffer,TEXT_08 _PL_ Source,ADDRESS Capacity)
{
	return (strcat_s(Buffer,Capacity,Source)==0);
}
_PENC_ logical PenC_String_Concat_T16_(text_16 _PL_ Buffer,TEXT_16 _PL_ Source,ADDRESS Capacity)
{
	return (wcscat_s(Buffer,Capacity,Source)==0);
}

_PENC_ logical PenC_String_Copier_T08_(text_08 _PL_ Buffer,TEXT_08 _PL_ Source,ADDRESS Capacity)
{
	return (strcpy_s(Buffer,Capacity,Source)==0);
}
_PENC_ logical PenC_String_Copier_T16_(text_16 _PL_ Buffer,TEXT_16 _PL_ Source,ADDRESS Capacity)
{
	return (wcscpy_s(Buffer,Capacity,Source)==0);
}

_PENC_ integer PenC_String_Compar_T08_(TEXT_08 _PL_ A,TEXT_08 _PL_ B)
{
	return strcmp(A,B);
}
_PENC_ integer PenC_String_Compar_T16_(TEXT_16 _PL_ A,TEXT_16 _PL_ B)
{
	return wcscmp(A,B);
}
#endif

#if(Fold_(Definition:PenClip Managed Functions))
_PENC_ general PenC_Delete_(general *_PL_ Object) { MemC_Deloc_(*Object); }

#if(Fold_(Part:PenC_SC))
static general _PenC_SC_Bound_(PENC_SC _PL_ SC)
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
}
_PENC_ penc_sc *PenC_SC_Create_(ADDRESS Capacity)
{
	penc_sc *SC;
	
	if(Capacity<_PENC_SC_MAX_)
		if(Capacity)
		{
			SC=MemC.Alloc.Byte_(MemC.Size.Add_(Capacity,sizeof(penc_sc)));
			if(SC)
			{
				Acs_(address,SC->Capacity)=Capacity;
				Acs_(text_08*,SC->String.T08)=(text_08*)(SC+1);
				_PenC_SC_Bound_(SC);
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

_PENC_ general PenC_SC_Init_(PENC_SC _PL_ SC)
{
	MemC_Clear_1D_(SC->String.T08,SC->Capacity);
}
_PENC_ general PenC_SC_Shut_T08_(PENC_SC _PL_ SC)
{
	SC->String.T08[SC->Capacity-1]=0;
}
_PENC_ general PenC_SC_Shut_T16_(PENC_SC _PL_ SC)
{
	SC->String.T16[(SC->Capacity>>1)-1]=0;
}

_PENC_ logical PenC_SC_Caster_T08_T16_(PENC_SC _PL_ Source,PENC_SC _PL_ Target)
{
	return PenC_String_Caster_T08_T16_(Source->String.T08,Target->String.T16,Source->Capacity,Target->Capacity>>1);
}
_PENC_ logical PenC_SC_Caster_T16_T08_(PENC_SC _PL_ Source,PENC_SC _PL_ Target)
{
	return PenC_String_Caster_T16_T08_(Source->String.T16,Target->String.T08,Source->Capacity>>1,Target->Capacity);
}

_PENC_ address PenC_SC_Length_T08_(PENC_SC _PL_ SC)
{
	return PenC.String.Length.T08_(SC->String.T08,SC->Capacity);
}
_PENC_ address PenC_SC_Length_T16_(PENC_SC _PL_ SC)
{
	return PenC.String.Length.T16_(SC->String.T16,SC->Capacity>>1);
}

_PENC_ logical PenC_SC_Copier_T08_(PENC_SC _PL_ Source,PENC_SC _PL_ Target)
{
	return PenC_String_Copier_T08_(Target->String.T08,Source->String.T08,Target->Capacity);
}
_PENC_ logical PenC_SC_Copier_T16_(PENC_SC _PL_ Source,PENC_SC _PL_ Target)
{
	return PenC_String_Copier_T16_(Target->String.T16,Source->String.T16,Target->Capacity>>1);
}

_PENC_ logical PenC_SC_Concat_T08_(PENC_SC _PL_ Source,PENC_SC _PL_ Target)
{
	return PenC_String_Concat_T08_(Target->String.T08,Source->String.T08,Target->Capacity);
}
_PENC_ logical PenC_SC_Concat_T16_(PENC_SC _PL_ Source,PENC_SC _PL_ Target)
{
	return PenC_String_Concat_T16_(Target->String.T16,Source->String.T16,Target->Capacity>>1);
}

_PENC_ integer PenC_SC_Compar_T08_(PENC_SC _PL_ A,PENC_SC _PL_ B)
{
	return PenC_String_Compar_T08_(A->String.T08,B->String.T08);
}
_PENC_ integer PenC_SC_Compar_T16_(PENC_SC _PL_ A,PENC_SC _PL_ B)
{
	return PenC_String_Compar_T16_(A->String.T16,B->String.T16);
}

_PENC_ address PenC_SC_Stream_T08_(LOGICAL Mode,PENC_SC _PL_ SC,FILE _PL_ Stream)
{
	return PenC_Stream_Buffer_T08_(Mode,Stream,SC->String.T08,SC->Capacity);
}
_PENC_ address PenC_SC_Stream_T16_(LOGICAL Mode,PENC_SC _PL_ SC,FILE _PL_ Stream)
{
	return PenC_Stream_Buffer_T16_(Mode,Stream,SC->String.T16,SC->Capacity>>1);
}
#endif

#if(Fold_(Part:PenC_SL))
_PENC_ penc_sl *PenC_SL_Create_(ADDRESS Chunks)
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

_PENC_ address PenC_SL_Size_(PENC_SL _PL_ SL)
{
	return ((SL)?(MemC_Size_(penc_sn,SL->Chunks+1)):(0));
}
_PENC_ logical PenC_SL_Reset_(penc_sl _PL_ SL)
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

static address _PenC_SN_Margin_(volatile address Number)
{
	Number--;
	Number+=sizeof(penc_sn);
	Number/=sizeof(penc_sn);
	Number*=sizeof(penc_sn);

	return Number;
}
static penc_sn *_PenC_SN_Search_Space_(penc_sn *_R_ Ptr,ADDRESS Demand)
{
	penc_sn *Mark=NULL;

	for(address Temp=SIZE_MAX;Ptr;Ptr=Ptr->Link[1])
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
static address _PenC_SN_Search_Size_(penc_sn *_R_ Ptr)
{
	address Temp;

	for(Temp=0;Ptr;Ptr=Ptr->Link[1])
		if(Ptr->Data.String.X);
		else if(Temp<Ptr->Data.Capacity)
			Temp=Ptr->Data.Capacity;
		else;

	return Temp;
}
static penc_sn *_PenC_SN_Search_Node_(penc_sn *_R_ Ptr,PENC_SC _PL_ SC)
{
	while(Ptr)
		if(&(Ptr->Data)==SC)
			break;
		else
			Ptr=Ptr->Link[1];

	return Ptr;
}
static address _PenC_SN_Borrow_(penc_sn _PL_ Node,ADDRESS Demand)
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
		((address*)(Node->Data.String.X))[(Node->Data.Capacity/sizeof(size_t))-1]=0;
	}
	else
		Acs_(general*,Node->Data.String.X)=FULL;

	return Return;
}
static general _PenC_SN_Attach_(penc_sn _PL_ Node)
{
	Acs_(address,Node->Data.Capacity)+=sizeof(penc_sn);
	Acs_(address,Node->Data.Capacity)+=Node->Link[1]->Data.Capacity;

	Node->Link[1]=Node->Link[1]->Link[1];
	if(Node->Link[1])
		Node->Link[1]->Link[0]=Node;
	else;
}
static address _PenC_SN_Return_(penc_sn *_PL_ Node)
{
	address Return=0;

	if((*Node)->Link[0])
		if((*Node)->Link[0]->Data.String.X);
		else
		{
			*Node=(*Node)->Link[0];
			_PenC_SN_Attach_(*Node);
			Return+=1;
		}
	else;

	if((*Node)->Link[1])
		if((*Node)->Link[1]->Data.String.X);
		else
		{
			_PenC_SN_Attach_(*Node);
			Return+=1;
		}
	else;

	Acs_(general*,(*Node)->Data.String.X)=NULL;

	return Return;
}
_PENC_ penc_sc *PenC_SL_Borrow_(penc_sl _PL_ SL,ADDRESS Demand)
{
	if(SL)
		if(Demand<_PENC_SC_MAX_)
		{
			penc_sn _PL_ Node=(penc_sn*)(SL->Node);
			ADDRESS Margin=_PenC_SN_Margin_(Demand);

			if(Margin>SL->Capable);
			else
			{
				penc_sn _PL_ This=_PenC_SN_Search_Space_(Node,Margin);

				if(This)
				{
					if(This->Data.Capacity==SL->Capable)
					{
						Acs_(address,SL->Nodes)+=_PenC_SN_Borrow_(This,Margin);
						Acs_(address,SL->Capable)=_PenC_SN_Search_Size_(Node);
					}
					else
						Acs_(address,SL->Nodes)+=_PenC_SN_Borrow_(This,Margin);

					return &(This->Data);
				}
				else;
			}
		}
		else;
	else;

	return NULL;
}
_PENC_ logical PenC_SL_Return_(penc_sl _PL_ SL,penc_sc *_PL_ SC)
{
	if(SL)
		if(*SC)
		{
			penc_sn *Node=_PenC_SN_Search_Node_((penc_sn*)(SL->Node),*SC);

			if(Node)
			{
				Acs_(address,SL->Nodes)-=_PenC_SN_Return_(&Node);
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

_PENC_ penc_sc *PenC_SL_Borrow_Copier_T08_(penc_sl _PL_ SL,PENC_SC _PL_ Source)
{
	penc_sc *Target=PenC_SL_Borrow_(SL,PenC_SC_Length_T08_(Source)+1);

	if(Target)
		if(PenC_SC_Copier_T08_(Source,Target));
		else
			PenC_SL_Return_(SL,&Target);
	else;

	return Target;
}
_PENC_ penc_sc *PenC_SL_Borrow_Copier_T16_(penc_sl _PL_ SL,PENC_SC _PL_ Source)
{
	penc_sc *Target=PenC_SL_Borrow_(SL,(PenC_SC_Length_T16_(Source)+1)<<1);

	if(Target)
		if(PenC_SC_Copier_T16_(Source,Target));
		else
			PenC_SL_Return_(SL,&Target);
	else;

	return Target;
}
_PENC_ penc_sc *PenC_SL_Borrow_Concat_T08_(penc_sl _PL_ SL,PENC_SC _PL_ Former,PENC_SC _PL_ Latter)
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
_PENC_ penc_sc *PenC_SL_Borrow_Concat_T16_(penc_sl _PL_ SL,PENC_SC _PL_ Former,PENC_SC _PL_ Latter)
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

#if(Fold_(Undefinition:PenClip Macros))
#undef _PENC_SC_MAX_
#undef _PENC_
#endif

#if(Fold_(Library Casing))
PENCASE PenC=
{
	.Version=IdiomVersion,
	.Hello=
	{
		.T08=IdiomHello08,
		.T16=IdiomHello16
	},
	.Option=
	{
		.Read=
		{
			.Binary=
			{
				.T08=IdiomOpen08+0,
				.T16=IdiomOpen16+0
			},
			.Text=
			{
				.T08=IdiomOpen08+8,
				.T16=IdiomOpen16+8
			}
		},
		.Write=
		{
			.Binary=
			{
				.T08=IdiomOpen08+4,
				.T16=IdiomOpen16+4
			},
			.Text=
			{
				.T08=IdiomOpen08+12,
				.T16=IdiomOpen16+12
			}
		}
	},
	.Setter=
	{
		.T08_=PenC_Setter_T08_,
		.T16_=PenC_Setter_T16_
	},
	.Finder=
	{
		.T08_=PenC_Finder_T08_,
		.T16_=PenC_Finder_T16_
	},
	.String=
	{
		.Caster=
		{
			.T08_T16_=PenC_String_Caster_T08_T16_,
			.T16_T08_=PenC_String_Caster_T16_T08_
		},
		.Length=
		{
			.T08_=PenC_String_Length_T08_,
			.T16_=PenC_String_Length_T16_
		},
		.Finder=
		{
			.T08_=PenC_String_Finder_T08_,
			.T16_=PenC_String_Finder_T16_
		},
		.Concat=
		{
			.T08_=PenC_String_Concat_T08_,
			.T16_=PenC_String_Concat_T16_
		},
		.Copier=
		{
			.T08_=PenC_String_Copier_T08_,
			.T16_=PenC_String_Copier_T16_
		},
		.Compar=
		{
			.T08_=PenC_String_Compar_T08_,
			.T16_=PenC_String_Compar_T16_
		}
	},
	.File=
	{
		.Opener=
		{
			.T08_=PenC_File_Opener_T08_,
			.T16_=PenC_File_Opener_T16_
		},
		.Closer_=PenC_File_Closer_,
		.Writer_=_PenC_File_Writer_,
		.Reader_=_PenC_File_Reader_,
		.Jumper_=_PenC_File_Jumper_,
		.Backer_=_PenC_File_Backer_,
		.Rewind_=_PenC_File_Rewind_,
		.Teller_=_PenC_File_Teller_,
		.Washer_=_PenC_File_Washer_,
		.Finish_=_PenC_File_Finish_,
		.Pose=
		{
			.Get_=_PenC_File_Pose_Get_,
			.Set_=_PenC_File_Pose_Set_
		},
		.Remove=
		{
			.T08_=_PenC_File_Remove_T08_,
			.T16_=_PenC_File_Remove_T16_
		},
		.Rename=
		{
			.T08_=_PenC_File_Rename_T08_,
			.T16_=_PenC_File_Rename_T16_
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
			.T08_=_PenC_Reader_1D_T08_,
			.T16_=_PenC_Reader_1D_T16_
		},
		.Writer=
		{
			.T08_=_PenC_Writer_1D_T08_,
			.T16_=_PenC_Writer_1D_T16_
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
		.Create_=PenC_SC_Create_,
		.Delete_=MemC_Func_Casting_(general,PenC_Delete_,penc_sc*_PL_),
		.Init_=PenC_SC_Init_,
		.Shut=
		{
			.T08_=PenC_SC_Shut_T08_,
			.T16_=PenC_SC_Shut_T16_
		},
		.Caster=
		{
			.T08_T16_=PenC_SC_Caster_T08_T16_,
			.T16_T08_=PenC_SC_Caster_T16_T08_
		},
		.Length=
		{
			.T08_=PenC_SC_Length_T08_,
			.T16_=PenC_SC_Length_T16_
		},
		.Copier=
		{
			.T08_=PenC_SC_Copier_T08_,
			.T16_=PenC_SC_Copier_T16_
		},
		.Concat=
		{
			.T08_=PenC_SC_Concat_T08_,
			.T16_=PenC_SC_Concat_T16_
		},
		.Compar=
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
		.Create_=PenC_SL_Create_,
		.Delete_=MemC_Func_Casting_(general,PenC_Delete_,penc_sl*_PL_),
		.Size_=PenC_SL_Size_,
		.Reset_=PenC_SL_Reset_,
		.Borrow_=PenC_SL_Borrow_,
		.Borrow=
		{
			.Copier=
			{
				.T08_=PenC_SL_Borrow_Copier_T08_,
				.T16_=PenC_SL_Borrow_Copier_T16_
			},
			.Concat=
			{
				.T08_=PenC_SL_Borrow_Concat_T08_,
				.T16_=PenC_SL_Borrow_Concat_T16_
			}
		},
		.Return_=PenC_SL_Return_
	}
};
PENCASE *PenC_(general) { return &PenC; }
#endif
