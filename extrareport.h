/*
  Kinesis ergonomic keyboard firmware replacement

  Copyright 2012 Chris Andreae (chris (at) andreae.gen.nz)

  Licensed under the GNU GPL v2 (see GPL2.txt).

  See Kinesis.h for keyboard hardware documentation.

  ==========================

  If built for V-USB, this program includes library and sample code from:
	 V-USB, (C) Objective Development Software GmbH
	 Licensed under the GNU GPL v2 (see GPL2.txt)

  ==========================

  If built for LUFA, this program includes library and sample code from:
			 LUFA Library
	 Copyright (C) Dean Camera, 2011.

  dean [at] fourwalledcubicle [dot] com
		   www.lufa-lib.org

  Copyright 2011  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaim all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

#ifndef __EXTRAREPORT_H
#define __EXTRAREPORT_H

#include "keystate.h"

#define EXTRA_REPORT_KEY_COUNT 6

typedef struct _ExtraKeyboardReport {
	uint8_t modifiers;
	hid_keycode keys[EXTRA_REPORT_KEY_COUNT]; // Keys are kept unsorted and unpacked
} ExtraKeyboardReport;

void ExtraKeyboardReport_clear(ExtraKeyboardReport* r);
void ExtraKeyboardReport_add(ExtraKeyboardReport* r, hid_keycode key);
void ExtraKeyboardReport_remove(ExtraKeyboardReport* r, hid_keycode key);
void ExtraKeyboardReport_toggle(ExtraKeyboardReport* r, hid_keycode key);
void ExtraKeyboardReport_append(ExtraKeyboardReport* extra, struct _KeyboardReport_Data_t* report);

#endif // __EXTRAREPORT_H
