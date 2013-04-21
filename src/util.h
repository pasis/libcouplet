/* util.h
** strophe XMPP client library -- various utility functions
**
** Copyright (C) 2005-2009 Collecta, Inc.
**
**  This software is provided AS-IS with no warranty, either express
**  or implied.
**
**  This software is distributed under license and may not be copied,
**  modified or distributed except as expressly authorized under the
**  terms of the license contained in the file LICENSE.txt in this
**  distribution.
*/

/** @file
 *  Internally used utility functions.
 */

#ifndef __LIBSTROPHE_UTIL_H__
#define __LIBSTROPHE_UTIL_H__

#ifndef _WIN32
#include <stdint.h>
#else
#include "ostypes.h"
#endif

/* timing functions */
uint64_t time_stamp(void);

/* inline functions */

/** Get the time elapsed between two time stamps.
 *  This function returns the time elapsed between t1 and t2 by subtracting
 *  t1 from t2.  If t2 happened before t1, the result will be negative.  This
 *  function is used internally by the event loop and timed handlers.
 *
 *  @param t1 first time stamp
 *  @param t2 second time stamp
 *
 *  @return number of milliseconds between the stamps
 */
inline static uint64_t time_elapsed(uint64_t t1, uint64_t t2)
{
    return (uint64_t)(t2 - t1);
}

#endif /* __LIBSTROPHE_UTIL_H__ */
