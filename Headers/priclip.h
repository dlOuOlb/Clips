/*------------------------------------------------------------------*/
/*	PriClip provides some small prime number tables.				*/
/*																	*/
/*	Written by Ranny Clover								Date		*/
/*	http://github.com/dlOuOlb/Clips/					2019.10.10	*/
/*------------------------------------------------------------------*/

#ifndef _INC_PRICLIP
#define _INC_PRICLIP

#if(1)
#include <penclip.h>
#include <bitclip.h>
#endif

#if(Fold_(Definition:Types))
//PriClip : 8-bit Prime Table Structure
struct _pric_08
{
	DATA_08 Count;		//PriClip : The Number of Primes
	DATA_08 Prime[];	//PriClip : The Table of The First (Count) Primes
};
MemC_Type_Declare_(struct,pric_08,PRIC_08);	//PriClip : 8-bit Prime Table Structure

//PriClip : 16-bit Prime Table Structure
struct _pric_16
{
	DATA_16 Count;		//PriClip : The Number of Primes
	DATA_16 Prime[];	//PriClip : The Table of The First (Count) Primes
};
MemC_Type_Declare_(struct,pric_16,PRIC_16);	//PriClip : 16-bit Prime Table Structure

//PriClip : 32-bit Prime Table Structure
struct _pric_32
{
	DATA_32 Count;		//PriClip : The Number of Primes
	DATA_32 Prime[];	//PriClip : The Table of The First (Count) Primes
};
MemC_Type_Declare_(struct,pric_32,PRIC_32);	//PriClip : 32-bit Prime Table Structure

//PriClip : 64-bit Prime Table Structure
struct _pric_64
{
	DATA_64 Count;		//PriClip : The Number of Primes
	DATA_64 Prime[];	//PriClip : The Table of The First (Count) Primes
};
MemC_Type_Declare_(struct,pric_64,PRIC_64);	//PriClip : 64-bit Prime Table Structure
#endif

#if(Fold_(Library Casing))
//PriClip : Library Case Structure
struct _pricase
{
	//PriClip : Library Version
	BYTE_08 _PL_ Version;

	//PriClip : Prime Table Functions
	const struct
	{
		//PriClip : Prime Table Deletion
		const union
		{
			//PriClip : 8-bit Prime Table Memory Deallocation
			general(_PL_ D08_)(pric_08 *_PL_ _R_ Table);
			//PriClip : 16-bit Prime Table Memory Deallocation
			general(_PL_ D16_)(pric_16 *_PL_ _R_ Table);
			//PriClip : 32-bit Prime Table Memory Deallocation
			general(_PL_ D32_)(pric_32 *_PL_ _R_ Table);
			//PriClip : 64-bit Prime Table Memory Deallocation
			general(_PL_ D64_)(pric_64 *_PL_ _R_ Table);
		}
		Delete;

		//PriClip : Prime Table Creation
		//£ªTable -> Prime = { 2, 3, 5, 7, ... }
		const struct
		{
			//PriClip : 8-bit Prime Table Memory Allocation - Deallocate with "PriC.Delete.D08_"
			pric_08*(_PL_ D08_)(DATA_08 Count);
			//PriClip : 16-bit Prime Table Memory Allocation - Deallocate with "PriC.Delete.D16_"
			pric_16*(_PL_ D16_)(DATA_16 Count);
			//PriClip : 32-bit Prime Table Memory Allocation - Deallocate with "PriC.Delete.D32_"
			pric_32*(_PL_ D32_)(DATA_32 Count);
			//PriClip : 64-bit Prime Table Memory Allocation - Deallocate with "PriC.Delete.D64_"
			pric_64*(_PL_ D64_)(DATA_64 Count);
		}
		Create;

		//PriClip : Prime Table Saving
		//£ªReturn value is 1 for success, 0 for failure.
		const struct
		{
			//PriClip : 8-bit Prime Table File Writing
			logical(_PL_ D08_)(FILE _PL_ File,PRIC_08 _PL_ _R_ Table);
			//PriClip : 16-bit Prime Table File Writing
			logical(_PL_ D16_)(FILE _PL_ File,PRIC_16 _PL_ _R_ Table);
			//PriClip : 32-bit Prime Table File Writing
			logical(_PL_ D32_)(FILE _PL_ File,PRIC_32 _PL_ _R_ Table);
			//PriClip : 64-bit Prime Table File Writing
			logical(_PL_ D64_)(FILE _PL_ File,PRIC_64 _PL_ _R_ Table);
		}
		Save;

		//PriClip : Prime Table Loading
		//£ªThe second parameter will be just ignored.
		//£ªNote that the returned table could be wrong if the file is not correct.
		const struct
		{
			//PriClip : 8-bit Prime Table File Reading - Deallocate with "PriC.Delete.D08_"
			pric_08*(_PL_ D08_)(FILE _PL_ File,general _PL_ _R_);
			//PriClip : 16-bit Prime Table File Reading - Deallocate with "PriC.Delete.D16_"
			pric_16*(_PL_ D16_)(FILE _PL_ File,general _PL_ _R_);
			//PriClip : 32-bit Prime Table File Reading - Deallocate with "PriC.Delete.D32_"
			pric_32*(_PL_ D32_)(FILE _PL_ File,general _PL_ _R_);
			//PriClip : 64-bit Prime Table File Reading - Deallocate with "PriC.Delete.D64_"
			pric_64*(_PL_ D64_)(FILE _PL_ File,general _PL_ _R_);
		}
		Load;

		//PriClip : Prime Index Search
		//£ªReturn value is the index of the prime in the table, or ~0.
		const struct
		{
			//PriClip : Find the index of the 8-bit prime.
			data_08(_PL_ D08_)(PRIC_08 _PL_ _R_ Table,DATA_08 Prime);
			//PriClip : Find the index of the 16-bit prime.
			data_16(_PL_ D16_)(PRIC_16 _PL_ _R_ Table,DATA_16 Prime);
			//PriClip : Find the index of the 32-bit prime.
			data_32(_PL_ D32_)(PRIC_32 _PL_ _R_ Table,DATA_32 Prime);
			//PriClip : Find the index of the 64-bit prime.
			data_64(_PL_ D64_)(PRIC_64 _PL_ _R_ Table,DATA_64 Prime);
		}
		Search;

		//PriClip : Prime Factor
		const struct
		{
			//PriClip : Smallest Prime Factor
			//£ªReturn value is the smallest prime factor found in the table, or the number itself.
			const struct
			{
				//PriClip : Get the smallest prime factor of the 8-bit number.
				data_08(_PL_ D08_)(PRIC_08 _PL_ _R_ Table,DATA_08 Number);
				//PriClip : Get the smallest prime factor of the 16-bit number.
				data_16(_PL_ D16_)(PRIC_16 _PL_ _R_ Table,DATA_16 Number);
				//PriClip : Get the smallest prime factor of the 32-bit number.
				data_32(_PL_ D32_)(PRIC_32 _PL_ _R_ Table,DATA_32 Number);
				//PriClip : Get the smallest prime factor of the 64-bit number.
				data_64(_PL_ D64_)(PRIC_64 _PL_ _R_ Table,DATA_64 Number);
			}
			First;

			//PriClip : Prime Factor Counting
			const struct
			{
				//PriClip : Count the prime factors of the 8-bit number.
				address(_PL_ D08_)(PRIC_08 _PL_ _R_ Table,DATA_08 Number,LOGICAL Multiplicity);
				//PriClip : Count the prime factors of the 16-bit number.
				address(_PL_ D16_)(PRIC_16 _PL_ _R_ Table,DATA_16 Number,LOGICAL Multiplicity);
				//PriClip : Count the prime factors of the 32-bit number.
				address(_PL_ D32_)(PRIC_32 _PL_ _R_ Table,DATA_32 Number,LOGICAL Multiplicity);
				//PriClip : Count the prime factors of the 64-bit number.
				address(_PL_ D64_)(PRIC_64 _PL_ _R_ Table,DATA_64 Number,LOGICAL Multiplicity);
			}
			Count;
		}
		Factor;
	}
	PT;

	//PriClip : Theoretical Maximum Count of Primes
	const struct
	{
		DATA_64 D64;	//PriClip : 0x05E83C229654F94F
		DATA_32 D32;	//PriClip : 0x0C1DCF5D
		DATA_16 D16;	//PriClip : 0x198E
		DATA_08 D08;	//PriClip : 0x36
	}
	Count;
};
MemC_Type_Declare_(struct,pricase,PRICASE);	//PriClip : Library Case Structure

//PriClip : Library Case Object
extern PRICASE PriC;
//PriClip : Indirect access to the library case object.
extern PRICASE *PriC_(general);
#endif
#endif
