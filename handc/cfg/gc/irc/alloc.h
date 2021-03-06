/*-----------------------------------------------------------------*-C-*---
 * File:    %p%
 *
 *          Copyright (C)1997 Donovan Kolbly <d.kolbly@rscheme.org>
 *          as part of the RScheme project, licensed for free use.
 *          See <http://www.rscheme.org/> for the latest information.
 *
 * File version:     %I%
 * File mod date:    %E% %U%
 * System build:     %b%
 *
 *------------------------------------------------------------------------*/

#ifndef _H_ALLOC
#define _H_ALLOC

#include <stdio.h>

#ifdef NDEBUG
#define atracef ((FILE *)0)
#else
extern FILE *atracef;
#endif

IRC_Header *IRC_growSizeClass( IRC_Heap *heap,
			       IRC_SizeClass *sc,
			       UINT_32 size );
/* aix: -Q+IRC_getBlock */

#ifdef __GNUC__
inline
#endif
static void *IRC_getBlock( IRC_Heap *heap, IRC_SizeClass *sc, UINT_32 size )
{
IRC_Header *p = sc->free;

    if (p == &sc->marker)
    {
	p = IRC_growSizeClass( heap, sc, size );
    }
    p->sizeClass = sc;	/* may have died from an older size class */

    if (WATCH_IT(p))
      printf( "IRC_getBlock: %p\n", p );
#if FREE_HAS_DEADBEEF
    assert( p->flagBits == 0xDEADBEEF );
#endif

    sc->free = p->next;
    p->flagBits = sc->initFlagBits;
    return p+1;
}

#endif
