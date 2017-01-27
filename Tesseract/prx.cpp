#include "stdafx.h"

#include <cellstatus.h>
#include <sys/prx.h>

SYS_MODULE_INFO( Tesseract, 0, 1, 1);
SYS_MODULE_START( _Tesseract_prx_entry );

SYS_LIB_DECLARE_WITH_STUB( LIBNAME, SYS_LIB_AUTO_EXPORT, STUBNAME );
SYS_LIB_EXPORT( _Tesseract_export_function, LIBNAME );

// An exported function is needed to generate the project's PRX stub export library
extern "C" int _Tesseract_export_function(void)
{
    return CELL_OK;
}

extern "C" int _Tesseract_prx_entry(void)
{
    return SYS_PRX_RESIDENT;
}