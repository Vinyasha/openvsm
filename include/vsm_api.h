/**
 *
 * @file   vsm_api.h
 * @author Lavrentiy Ivanov (ookami@mail.ru)
 * @date   22.09.2014
 * @copyright Copyright 2014 Lavrentiy Ivanov. All rights reserved
 * @license This project is released under the BSD 2-Clause license.
 *
 */

#ifndef VSMAPI_H
#define VSMAPI_H

#include <windows.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#include <defines.h>
#include <enums.h>
#include <vsm_classes.h>
#include <device.h>
#include <c_bind.h>
#include <lua_bind.h>
#include <pin.h>
 #include <vsmobj.h>
#include <uthash.h>

#undef _WIN32_WINNT
#define _WIN32_WINNT 0x0500
#define VSM_API_VERSION  110
#define model_key 0x00000000

#ifndef MAX_PIN_NUMBER
#define MAX_PIN_NUMBER 32
#endif

#define LOGIC_HI (model->logic_high)
#define LOGIC_LO (model->logic_low)

#define LSTRING (&lua_isstring)
#define LINT (&lua_isnumber)
#define LUSER (&lua_islightuserdata)
#define LTABLE (&lua_istable)

typedef struct calltrace
{
	void *func_addr;
	UT_hash_handle hh;
} calltrace;

int32_t vasprintf ( char** sptr, char* fmt, va_list argv );
int32_t asprintf ( char** sptr, char* fmt, ... );

int32_t __attribute__ ( ( fastcall ) )
vsm_isdigital ( IDSIMMODEL* this, uint32_t edx, char* pinname );
void __attribute__ ( ( fastcall ) )
vsm_setup ( IDSIMMODEL* this, uint32_t edx, IINSTANCE* instance, IDSIMCKT* dsim );
void __attribute__ ( ( fastcall ) )
vsm_runctrl (  IDSIMMODEL* this, uint32_t edx, RUNMODES mode );
void __attribute__ ( ( fastcall ) )
vsm_actuate  (  IDSIMMODEL* this, uint32_t edx, REALTIME atime, ACTIVESTATE newstate );
bool __attribute__ ( ( fastcall ) )
vsm_indicate (  IDSIMMODEL* this, uint32_t edx, REALTIME atime, ACTIVEDATA* newstate );
void __attribute__ ( ( fastcall ) )
vsm_simulate (  IDSIMMODEL* this, uint32_t edx, ABSTIME atime, DSIMMODES mode );
void __attribute__ ( ( fastcall ) )
vsm_timer_callback (  IDSIMMODEL* this, uint32_t edx, ABSTIME atime, EVENTID eventid );

LRESULT __attribute__ ( ( fastcall ) )
icpu_vdmhlr (  ICPU* this, uint32_t edx, VDM_COMMAND* cmd, uint8_t* data );
void __attribute__ ( ( fastcall ) )
icpu_loaddata ( ICPU* this, EDX, int32_t format, int32_t seg, ADDRESS address, uint8_t* data, int32_t numbytes );
void __attribute__ ( ( fastcall ) )
icpu_disassemble ( ICPU* this, EDX, ADDRESS address, int32_t numbytes );
bool __attribute__ ( ( fastcall ) )
icpu_getvardata ( ICPU* this, EDX, VARITEM* vip, VARDATA* vdp );

struct SPICEDATA
{
	uint32_t numtimepoints;
	uint32_t numpins;
	REALTIME* timepoints;
	double* nodedata;
};

struct DSIMDATA
{
	uint32_t numtimepoints;
	uint32_t numpins;
	ABSTIME* timepoints;
	STATE* nodedata;
};

struct CREATEPOPUPSTRUCT
{
	POPUPID id;
	POPUPTYPES type;
	char* caption;
	int32_t width, height;
	uint32_t flags;
};

struct ACTIVEDATA
{
	ACTIVEDATATYPES type;
	union
	{
		int32_t intval;
		double realval;
		STATE stateval;
		double wireinfo[2]; // Voltage and current
		SPICEDATA spicedata;
		DSIMDATA dsimdata;
		void* userinfo; // Pointer to user data
	};
};

struct VARITEM
{
	char name[WATCHITEM_NAME_SIZE];
	uint32_t loader, seg;
	ADDRESS address;
	DATATYPES type;
	DISPFORMATS format;
	uint32_t size;
	ADDRESS scope_begin;
	ADDRESS scope_end;
};

// Variable Data structure
struct VARDATA
{
	char addr[WATCHITEM_ADDR_SIZE];
	DATATYPES type;
	uint8_t* memory;
	uint32_t memsize;
	uint32_t offset; // from start of memory block.
};

struct ILICENCESERVER
{

	ILICENCESERVER_vtable* vtable;
	
};

struct EVENT
{
	EVENT_vtable* vtable;
};

struct ICPU
{
	ICPU_vtable* vtable;
	
};

struct IDSIMPIN2
{
	IDSIMPIN2_vtable* vtable;
};

struct IDSIMPIN1
{

	IDSIMPIN1_vtable* vtable;
	
};

struct IDSIMMODEL
{

	IDSIMMODEL_vtable* vtable;
	
	/* Custom objects */
	
	IINSTANCE* model_instance;
	IDSIMCKT* model_dsim;
	lua_State* luactx;
	VSM_PIN device_pins[MAX_PIN_NUMBER];
	calltrace *trace;
	/* Emulated logic type */
	LOGIC_TYPE ltype;
	int logic_high;
	int logic_low;
	/* simulation flags */
	bool safe_mode;
	bool timer_callback_declared;
	bool device_init_declared;
	bool device_simulate_declared;
	/**/
	int popup_id; ///< Popup identificator. Should be unique per model
	
};

struct IBUSPIN
{

	ICPU_vtable* vtable;
	
};

struct IINSTANCE
{

	IINSTANCE_vtable* vtable;
	
};

struct IDSIMCKT
{

	IDSIMCKT_vtable* vtable;
	
};

struct IUSERPOPUP
{

	IUSERPOPUP_vtable* vtable;
	
};

struct IDEBUGPOPUP
{

	IDEBUGPOPUP_vtable* vtable;
	
};

struct IMEMORYPOPUP
{

	IMEMORYPOPUP_vtable* vtable;
	
};

struct ISTATUSPOPUP
{

	ISTATUSPOPUP_vtable* vtable;
	
};

struct ISOURCEPOPUP
{

	ISOURCEPOPUP_vtable* vtable;
	
};

struct IMSGHLR
{
	IMSGHLR_vtable* vtable;
};

ICPU ICPU_DEVICE;

#endif

