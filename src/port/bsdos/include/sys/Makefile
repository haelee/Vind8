# $Id: Makefile,v 1.4 1997/06/19 03:22:22 halley Exp $

# ++Copyright++
# -
# Copyright (c)  Regents of the University of California.
# All rights reserved.
# 
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
# 3. All advertising materials mentioning features or use of this software
#    must display the following acknowledgement:
# 	This product includes software developed by the University of
# 	California, Berkeley and its contributors.
# 4. Neither the name of the University nor the names of its contributors
#    may be used to endorse or promote products derived from this software
#    without specific prior written permission.
# 
# THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
# OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
# OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
# SUCH DAMAGE.
# -
# Portions Copyright (c) 1993 by Digital Equipment Corporation.
# 
# Permission to use, copy, modify, and distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies, and that
# the name of Digital Equipment Corporation not be used in advertising or
# publicity pertaining to distribution of the document or software without
# specific, written prior permission.
# 
# THE SOFTWARE IS PROVIDED "AS IS" AND DIGITAL EQUIPMENT CORP. DISCLAIMS ALL
# WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES
# OF MERCHANTABILITY AND FITNESS.   IN NO EVENT SHALL DIGITAL EQUIPMENT
# CORPORATION BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
# DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
# PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS
# ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
# SOFTWARE.
# -
# --Copyright--

HFILES= bitypes.h cdefs.h

DESTDIR=
DESTINC= /usr/local/bind/include

SED=/usr/bin/sed
SEDFLAGS=-e 's/ts_sec/tv_sec/g' -e 's/ts_nsec/tv_nsec/g'
SYSINCLUDE=/usr/include/sys

all depend:
	@../../maybe_fix_includes

fix_includes: time.h stat.h

time.h: ${SYSINCLUDE}/time.h
	${SED} ${SEDFLAGS} ${SYSINCLUDE}/time.h > time.h

stat.h: ${SYSINCLUDE}/stat.h
	${SED} ${SEDFLAGS} ${SYSINCLUDE}/stat.h > stat.h

distclean: clean

clean:
	rm -f *~ *.BAK *.CKP *.orig time.h stat.h

links:
	@set -e; ln -s SRC/*.h .

install: ${DESTDIR}${DESTINC}/sys
	for x in ${HFILES}; do \
		if [ -f $$x ]; then \
			${INSTALL} -c -m 444 $$x ${DESTDIR}${DESTINC}/sys/$$x;\
		fi; \
	done

${DESTDIR}${DESTINC}/sys:
	mkdir -p ${DESTDIR}${DESTINC}/sys
