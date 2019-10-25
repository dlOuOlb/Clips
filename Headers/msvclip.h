/*------------------------------------------------------------------*/
/*	MSVClip is a workaround to avoid wicked MSVC issues.			*/
/*											16.3.6					*/
/*	Written by Ranny Clover								Date		*/
/*	http://github.com/dlOuOlb/Clips/					2019.10.24	*/
/*------------------------------------------------------------------*/

#ifndef _INC_MSVCLIP
#define _INC_MSVCLIP

#ifdef _MSC_BUILD

#define restrict __restrict
/* 'restrict' is a standard C keyword... since C99! */

#pragma warning(disable:4001)
/* C4001 : nonstandard extension 'single line comment' was used
But the single line comment is a C99 feature! */

#pragma warning(disable:4200)
/* C4200 : nonstandard extension used : zero-sized array in struct/union
But the flexible array member is a C99 feature! */

#pragma warning(disable:4201)
/* C4201 : nonstandard extension used : nameless struct/union
But the anonymous unions and structures are a C11 feature! */

#pragma warning(disable:4204)
/* C4204 : nonstandard extension used : non-constant aggregate initializer
But a non-constant aggregate initializer for an automatic storage is a C99 feature! */

#pragma warning(disable:4221)
/* C4221 : nonstandard extension used : 'identifier' : cannot be initialized using address of automatic variable
But isn't it just another form of a non-constant aggregate initializer? */

#pragma warning(disable:4619)
/* C4619 : #pragma warning : there is no warning number 'number'
Of course there are some warnings not supported by each version! */

#pragma warning(disable:4668)
/* C4668 : 'symbol' is not defined as a preprocessor macro, replacing with '0' for 'directives'
This warning should have been enabled, but MSVC's libraries does not handle the undefined '__cplusplus' macro properly! */

#pragma warning(disable:4710)
/* C4710 : 'function' : function not inlined
As the compiler wants to do. */

#pragma warning(disable:4711)
/* C4711 : function 'function' selected for inline expansion
As the compiler wants to do. */

#pragma warning(disable:4820)
/* C4820 : 'bytes' bytes padding added after construct 'member_name'
This warning should have been enabled, but some OpenCL headers will complain it. */

#pragma warning(disable:5045)
/* C5045 : Compiler will insert Spectre mitigation for memory load if /Qspectre switch specified
Just what is this? */

#endif
#endif
