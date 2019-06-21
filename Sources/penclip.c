#include "penclip.h"

#if(Fold_(Definition:PenClip Macros))
#define _PENC_ static
#define _PENC_SC_MAX_ ((address)(((address)1)<<(sizeof(address)<<2)))
#endif

#if(Fold_(Definition:Internal Constants))
static BYTE_08 IdiomVersion[16]="Date:2019.06.21";
static TEXT_08 IdiomHello08[16]="Hello, world!\r\n";
static TEXT_16 IdiomHello16[16]=L"Hello, world!\r\n";
static TEXT_08 IdiomOpen08[16]={'r','b','\0','\0','w','b','\0','\0','r','t','\0','\0','w','t','\0','\0'};
static TEXT_16 IdiomOpen16[16]={L'r',L'b',L'\0',L'\0',L'w',L'b',L'\0',L'\0',L'r',L't',L'\0',L'\0',L'w',L't',L'\0',L'\0'};
#endif

#if(Fold_(Definition:Pipe Functions))
_PENC_ FILE *PenC_Pipe_Opener_T08_(TEXT_08 _PL_ Command,TEXT_08 _PL_ Mode)
{
	return _popen(Command,Mode);
}
_PENC_ FILE *PenC_Pipe_Opener_T16_(TEXT_16 _PL_ Command,TEXT_16 _PL_ Mode)
{
	return _wpopen(Command,Mode);
}
_PENC_ integer PenC_Pipe_Closer_(FILE *_PL_ Pipe)
{
	integer Return;
	
	if(*Pipe)
	{
		Return=_pclose(*Pipe);
		*Pipe=NULL;
	}
	else
		Return=EOF;

	return Return;
}
_PENC_ integer PenC_Pipe_Action_T08_(TEXT_08 _PL_ Command,FILE _PL_ Stream)
{
	text_08 Buffer[1024];
	PENC_SC SC=PenC_SC_Assign_(Buffer);
	integer Return=EOF;

	PenC_Pipe_Using_(Pipe,Command,PenC.Option.Read.Binary.T08,Return)
		while(PenC.SC.Stream.T08_(1,&SC,Pipe))
		{
			Return=PenC_Stream_Format_T08_(0,Stream,Buffer);
			if(Return<0)
				break;

			Return=PenC.File.Washer_(Pipe);
			if(Return)
				break;
		}

	return Return;
}
_PENC_ integer PenC_Pipe_Action_T16_(TEXT_16 _PL_ Command,FILE _PL_ Stream)
{
	text_16 Buffer[1024];
	PENC_SC SC=PenC_SC_Assign_(Buffer);
	integer Return=EOF;
	
	PenC_Pipe_Using_(Pipe,Command,PenC.Option.Read.Binary.T16,Return)
		while(PenC.SC.Stream.T16_(1,&SC,Pipe))
		{
			Return=PenC_Stream_Format_T16_(0,Stream,Buffer);
			if(Return<0)
				break;

			Return=PenC.File.Washer_(Pipe);
			if(Return)
				break;
		}

	return Return;
}
#endif

#if(Fold_(Definition:File Functions))
static integer _PenC_Reader_1D_T08_(general _PL_ Line,TEXT_08 _PL_ Name,ADDRESS Size,ADDRESS Count)
{
	integer Success=0;

	if(Line)
	{
		integer Error=EOF;

		PenC_File_Using_(File,Name,PenC.Option.Read.Binary.T08,Error)
		{
			ADDRESS Bytes=Count*Size;

			if(Bytes==PenC_File_Reader_(File,(byte_08*)Line,Bytes))
				Success=1;
		}
		if(Error)
			Success=0;
	}

	return Success;
}
static integer _PenC_Reader_1D_T16_(general _PL_ Line,TEXT_16 _PL_ Name,ADDRESS Size,ADDRESS Count)
{
	integer Success=0;

	if(Line)
	{
		integer Error=EOF;

		PenC_File_Using_(File,Name,PenC.Option.Read.Binary.T16,Error)
		{
			ADDRESS Bytes=Count*Size;

			if(Bytes==PenC_File_Reader_(File,(byte_08*)Line,Bytes))
				Success=1;
		}
		if(Error)
			Success=0;
	}

	return Success;
}
static integer _PenC_Writer_1D_T08_(GENERAL _PL_ Line,TEXT_08 _PL_ Name,ADDRESS Size,ADDRESS Count)
{
	integer Success=0;

	if(Line)
	{
		integer Error=EOF;

		PenC_File_Using_(File,Name,PenC.Option.Write.Binary.T08,Error)
		{
			ADDRESS Bytes=Count*Size;

			if(Bytes==PenC_File_Writer_(File,(byte_08*)Line,Bytes))
				Success=1;
		}
		if(Error)
			Success=0;
	}

	return Success;
}
static integer _PenC_Writer_1D_T16_(GENERAL _PL_ Line,TEXT_16 _PL_ Name,ADDRESS Size,ADDRESS Count)
{
	integer Success=0;

	if(Line)
	{
		integer Error=EOF;

		PenC_File_Using_(File,Name,PenC.Option.Write.Binary.T16,Error)
		{
			ADDRESS Bytes=Count*Size;

			if(Bytes==PenC_File_Writer_(File,(byte_08*)Line,Bytes))
				Success=1;
		}
		if(Error)
			Success=0;
	}

	return Success;
}

_PENC_ FILE *PenC_File_Opener_T08_(TEXT_08 _PL_ Name,TEXT_08 _PL_ Mode)
{
	FILE *File=NULL;
	
	fopen_s(&File,Name,Mode);
	
	return File;
}
_PENC_ FILE *PenC_File_Opener_T16_(TEXT_16 _PL_ Name,TEXT_16 _PL_ Mode)
{
	FILE *File=NULL;

	_wfopen_s(&File,Name,Mode);

	return File;
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

static address _PenC_File_Writer_(FILE _PL_ File,GENERAL _PL_ Buffer,ADDRESS Elements,ADDRESS TypeSize)
{
	return fwrite(Buffer,TypeSize,Elements,File);
}
static address _PenC_File_Reader_(FILE _PL_ File,general _PL_ Buffer,ADDRESS Elements,ADDRESS TypeSize)
{
	return fread_s(Buffer,Elements*TypeSize,TypeSize,Elements,File);
}

static integer _PenC_File_Jumper_(FILE _PL_ File,long Size,ADDRESS TypeSize)
{
	Size*=(long)TypeSize;

	return fseek(File,Size,SEEK_CUR);
}
static integer _PenC_File_Backer_(FILE _PL_ File,long Size,ADDRESS TypeSize)
{
	Size*=(long)TypeSize;
	Size=-Size;

	return fseek(File,Size,SEEK_CUR);
}

static general _PenC_File_Rewind_(FILE _PL_ File)
{
	rewind(File);
}
static long _PenC_File_Teller_(FILE _PL_ File)
{
	return ftell(File);
}

static integer _PenC_File_Washer_(FILE _PL_ File)
{
	return (fflush(File)==0);
}
static integer _PenC_File_Finish_(FILE _PL_ File)
{
	return feof(File);
}

static integer _PenC_File_Remove_T08_(TEXT_08 _PL_ FileName)
{
	return (remove(FileName)==0);
}
static integer _PenC_File_Remove_T16_(TEXT_16 _PL_ FileName)
{
	return (_wremove(FileName)==0);
}
static integer _PenC_File_Rename_T08_(TEXT_08 _PL_ OldName,TEXT_08 _PL_ NewName)
{
	return (rename(OldName,NewName)==0);
}
static integer _PenC_File_Rename_T16_(TEXT_16 _PL_ OldName,TEXT_16 _PL_ NewName)
{
	return (_wrename(OldName,NewName)==0);
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

_PENC_ address PenC_Stream_Buffer_T08_(INTEGER Mode,FILE _PL_ Stream,text_08 _PL_ Buffer,ADDRESS Capacity)
{
	return ((Mode)?((Stream)?((address)fgets(Buffer,(integer)(Capacity),Stream)):((address)gets_s(Buffer,(rsize_t)(Capacity)))):((Stream)?((address)fputs(Buffer,Stream)):((address)puts(Buffer))));
}
_PENC_ address PenC_Stream_Buffer_T16_(INTEGER Mode,FILE _PL_ Stream,text_16 _PL_ Buffer,ADDRESS Capacity)
{
	return ((Mode)?((Stream)?((address)fgetws(Buffer,(integer)(Capacity),Stream)):((address)_getws_s(Buffer,Capacity))):((Stream)?((address)fputws(Buffer,Stream)):((address)_putws(Buffer))));
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

_PENC_ text_08 *PenC_Finder_T08_(TEXT_08 _PL_ Buffer,TEXT_08 Value,ADDRESS Count)
{
	return memchr(Buffer,Value,Count);
}
_PENC_ text_16 *PenC_Finder_T16_(TEXT_16 _PL_ Buffer,TEXT_16 Value,ADDRESS Count)
{
	return wmemchr(Buffer,Value,Count);
}
#endif

#if(Fold_(Definition:String Functions))
_PENC_ errno_t PenC_String_Caster_T08_T16_(TEXT_08 *StringS,text_16 _PL_ StringT,ADDRESS CapacityS,ADDRESS CapacityT)
{
	mbstate_t State={._Wchar=0,._Byte=0,._State=0};
	size_t Length;

	return mbsrtowcs_s(&Length,StringT,CapacityT,&StringS,CapacityS,&State);
}
_PENC_ errno_t PenC_String_Caster_T16_T08_(TEXT_16 *StringS,text_08 _PL_ StringT,ADDRESS CapacityS,ADDRESS CapacityT)
{
	mbstate_t State={._Wchar=0,._Byte=0,._State=0};
	size_t Length;

	return wcsrtombs_s(&Length,StringT,CapacityT,&StringS,CapacityS,&State);
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

_PENC_ errno_t PenC_String_Concat_T08_(text_08 _PL_ Buffer,TEXT_08 _PL_ Source,ADDRESS Capacity)
{
	return strcat_s(Buffer,Capacity,Source);
}
_PENC_ errno_t PenC_String_Concat_T16_(text_16 _PL_ Buffer,TEXT_16 _PL_ Source,ADDRESS Capacity)
{
	return wcscat_s(Buffer,Capacity,Source);
}

_PENC_ errno_t PenC_String_Copier_T08_(text_08 _PL_ Buffer,TEXT_08 _PL_ Source,ADDRESS Capacity)
{
	return strcpy_s(Buffer,Capacity,Source);
}
_PENC_ errno_t PenC_String_Copier_T16_(text_16 _PL_ Buffer,TEXT_16 _PL_ Source,ADDRESS Capacity)
{
	return wcscpy_s(Buffer,Capacity,Source);
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
#if(Fold_(Part:PenC_SC))
_PENC_ penc_sc _PenC_SC_Assign_(GENERAL _PL_ String,ADDRESS Capacity)
{
	penc_sc SC;

	Acs_(address,SC.Capacity)=Capacity;
	Acs_(GENERAL*,SC.String.X)=String;

	return SC;
}

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
			Temp>>=1;

			if(Temp)
			{
				SC->String.T32[0]=0x00000000;
				SC->String.T32[Temp-1]=0x00000000;
			}
		}
	}
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
		}
		else
		{
			SC=MemC_Alloc_Unit_(penc_sc);
			if(SC)
				MemC_Clear_Unit_(SC);
		}
	else
		SC=NULL;

	return SC;
}
_PENC_ general PenC_SC_Delete_(penc_sc *_PL_ SC)
{
	MemC_Deloc_(*SC);
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
_PENC_ general PenC_SC_Shut_T32_(PENC_SC _PL_ SC)
{
	SC->String.T32[(SC->Capacity>>2)-1]=0;
}

_PENC_ errno_t PenC_SC_Caster_T08_T16_(PENC_SC _PL_ Source,PENC_SC _PL_ Target)
{
	return PenC_String_Caster_T08_T16_(Source->String.T08,Target->String.T16,Source->Capacity,Target->Capacity>>1);
}
_PENC_ errno_t PenC_SC_Caster_T16_T08_(PENC_SC _PL_ Source,PENC_SC _PL_ Target)
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

_PENC_ errno_t PenC_SC_Copier_T08_(PENC_SC _PL_ Source,PENC_SC _PL_ Target)
{
	return PenC_String_Copier_T08_(Target->String.T08,Source->String.T08,Target->Capacity);
}
_PENC_ errno_t PenC_SC_Copier_T16_(PENC_SC _PL_ Source,PENC_SC _PL_ Target)
{
	return PenC_String_Copier_T16_(Target->String.T16,Source->String.T16,Target->Capacity>>1);
}

_PENC_ errno_t PenC_SC_Concat_T08_(PENC_SC _PL_ Source,PENC_SC _PL_ Target)
{
	return PenC_String_Concat_T08_(Target->String.T08,Source->String.T08,Target->Capacity);
}
_PENC_ errno_t PenC_SC_Concat_T16_(PENC_SC _PL_ Source,PENC_SC _PL_ Target)
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

_PENC_ address PenC_SC_Stream_T08_(INTEGER Mode,PENC_SC _PL_ SC,FILE _PL_ Stream)
{
	return PenC_Stream_Buffer_T08_(Mode,Stream,SC->String.T08,SC->Capacity);
}
_PENC_ address PenC_SC_Stream_T16_(INTEGER Mode,PENC_SC _PL_ SC,FILE _PL_ Stream)
{
	return PenC_Stream_Buffer_T16_(Mode,Stream,SC->String.T16,SC->Capacity>>1);
}
#endif

#if(Fold_(Part:PenC_SL))
MemC_Type_Declare_(struct,penc_sn,PENC_SN);
struct _penc_sn { penc_sn *Link[2];penc_sc Data; };
static_assert((sizeof(penc_sn)==sizeof(penc_sl)),"sizeof(penc_sn) != sizeof(penc_sl)");

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

	return SL;
}
_PENC_ general PenC_SL_Delete_(penc_sl *_PL_ SL)
{
	if(*SL)
		MemC_Deloc_(*SL);
}
_PENC_ address PenC_SL_Size_(PENC_SL _PL_ SL)
{
	return ((SL)?(MemC_Size_(penc_sn,SL->Chunks+1)):(0));
}
_PENC_ integer PenC_SL_Reset_(penc_sl _PL_ SL)
{
	integer Return;

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

		Return=1;
	}
	else
		Return=0;

	return Return;
}

static address _PenC_SN_Margin_(address Number)
{
	Number+=sizeof(penc_sn);
	Number--;
	Number/=sizeof(penc_sn);
	Number*=sizeof(penc_sn);

	return Number;
}
static penc_sn *_PenC_SN_Search_Space_(penc_sn *_R_ Ptr,ADDRESS Demand)
{
	penc_sn *Mark;
	address Temp;

	for(Mark=NULL,Temp=(address)FULL;Ptr;Ptr=Ptr->Link[1])
		if(!(Ptr->Data.String.X))
			if(Demand<=Ptr->Data.Capacity)
				if(Temp>Ptr->Data.Capacity)
				{
					Temp=Ptr->Data.Capacity;
					Mark=Ptr;
				}

	return Mark;
}
static address _PenC_SN_Search_Size_(penc_sn *_R_ Ptr)
{
	address Temp;

	for(Temp=0;Ptr;Ptr=Ptr->Link[1])
		if(!(Ptr->Data.String.X))
			if(Temp<Ptr->Data.Capacity)
				Temp=Ptr->Data.Capacity;

	return Temp;
}
static penc_sn *_PenC_SN_Search_Node_(penc_sn *_R_ Ptr,PENC_SC _PL_ SC)
{
	for(;Ptr;Ptr=Ptr->Link[1])
		if(&(Ptr->Data)==SC)
			break;

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
}
static address _PenC_SN_Return_(penc_sn *_PL_ Node)
{
	address Return=0;

	if((*Node)->Link[0])
		if(!((*Node)->Link[0]->Data.String.X))
		{
			*Node=(*Node)->Link[0];
			_PenC_SN_Attach_(*Node);
			Return+=1;
		}
	if((*Node)->Link[1])
		if(!((*Node)->Link[1]->Data.String.X))
		{
			_PenC_SN_Attach_(*Node);
			Return+=1;
		}
	Acs_(general*,(*Node)->Data.String.X)=NULL;

	return Return;
}
_PENC_ penc_sc *PenC_SL_Borrow_(PENC_SL _PL_ SL,ADDRESS Demand)
{
	penc_sc *SC;

	if(SL)
		if(Demand<_PENC_SC_MAX_)
		{
			penc_sn _PL_ Node=(penc_sn*)(SL->Node);
			ADDRESS Margin=_PenC_SN_Margin_(Demand);

			if(Margin>SL->Capable)
				SC=NULL;
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

					SC=&(This->Data);
				}
				else
					SC=NULL;
			}
		}
		else
			SC=NULL;
	else
		SC=NULL;

	return SC;
}
_PENC_ integer PenC_SL_Return_(PENC_SL _PL_ SL,PENC_SC *_PL_ SC)
{
	integer Return;

	if(SL)
		if(*SC)
		{
			penc_sn *Node=_PenC_SN_Search_Node_((penc_sn*)(SL->Node),*SC);

			if(Node)
			{
				Acs_(address,SL->Nodes)-=_PenC_SN_Return_(&Node);
				if(Node->Data.Capacity>SL->Capable)
					Acs_(address,SL->Capable)=Node->Data.Capacity;

				*SC=NULL;
				Return=1;
			}
			else
				Return=0;
		}
		else
			Return=0;
	else
		Return=0;

	return Return;
}

_PENC_ penc_sc *PenC_SL_Borrow_Copier_T08_(PENC_SL _PL_ SL,PENC_SC _PL_ Source)
{
	penc_sc *Target=PenC_SL_Borrow_(SL,PenC_SC_Length_T08_(Source)+1);

	if(Target)
		if(PenC_SC_Copier_T08_(Source,Target)==MemCErrZero);
		else
			PenC_SL_Return_(SL,&Target);

	return Target;
}
_PENC_ penc_sc *PenC_SL_Borrow_Copier_T16_(PENC_SL _PL_ SL,PENC_SC _PL_ Source)
{
	penc_sc *Target=PenC_SL_Borrow_(SL,(PenC_SC_Length_T16_(Source)+1)<<1);

	if(Target)
		if(PenC_SC_Copier_T16_(Source,Target)==MemCErrZero);
		else
			PenC_SL_Return_(SL,&Target);

	return Target;
}
_PENC_ penc_sc *PenC_SL_Borrow_Concat_T08_(PENC_SL _PL_ SL,PENC_SC _PL_ Former,PENC_SC _PL_ Latter)
{
	penc_sc *Concat=PenC_SL_Borrow_(SL,PenC_SC_Length_T08_(Former)+PenC_SC_Length_T08_(Latter)+1);

	if(Concat)
		if(PenC_SC_Copier_T08_(Concat,Former)==MemCErrZero)
			if(PenC_SC_Concat_T08_(Concat,Latter)==MemCErrZero);
			else
				PenC_SL_Return_(SL,&Concat);
		else
			PenC_SL_Return_(SL,&Concat);

	return Concat;
}
_PENC_ penc_sc *PenC_SL_Borrow_Concat_T16_(PENC_SL _PL_ SL,PENC_SC _PL_ Former,PENC_SC _PL_ Latter)
{
	penc_sc *Concat=PenC_SL_Borrow_(SL,(PenC_SC_Length_T16_(Former)+PenC_SC_Length_T16_(Latter)+1)<<1);

	if(Concat)
		if(PenC_SC_Copier_T16_(Concat,Former)==MemCErrZero)
			if(PenC_SC_Concat_T16_(Concat,Latter)==MemCErrZero);
			else
				PenC_SL_Return_(SL,&Concat);
		else
			PenC_SL_Return_(SL,&Concat);

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
	.Pipe=
	{
		.Opener=
		{
			.T08_=PenC_Pipe_Opener_T08_,
			.T16_=PenC_Pipe_Opener_T16_
		},
		.Closer_=PenC_Pipe_Closer_,
		.Action=
		{
			.T08_=PenC_Pipe_Action_T08_,
			.T16_=PenC_Pipe_Action_T16_
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
		.Jumper_=MemC_Func_Casting_(integer,_PenC_File_Jumper_,FILE _PL_,const long,ADDRESS),
		.Backer_=MemC_Func_Casting_(integer,_PenC_File_Backer_,FILE _PL_,const long,ADDRESS),
		.Rewind_=_PenC_File_Rewind_,
		.Teller_=_PenC_File_Teller_,
		.Washer_=_PenC_File_Washer_,
		.Finish_=_PenC_File_Finish_,
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
	.SC=
	{
		.Assign_=_PenC_SC_Assign_,
		.Create_=PenC_SC_Create_,
		.Delete_=PenC_SC_Delete_,
		.Init_=PenC_SC_Init_,
		.Shut=
		{
			.T08_=PenC_SC_Shut_T08_,
			.T16_=PenC_SC_Shut_T16_,
			.T32_=PenC_SC_Shut_T32_
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
		.Delete_=PenC_SL_Delete_,
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
