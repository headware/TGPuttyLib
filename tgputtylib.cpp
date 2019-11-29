#pragma hdrstop

#include <stdio.h>
#include <windows.h>
#include "tgputtylib.hpp"

#pragma package(smart_init)

HINSTANCE hPuttyLib = NULL;

int (*psftp_main)(int argc, char *argv[]);
int (*tggetlibrarycontextsize)();

int (*tgputty_initwithcmdline)(int argc, char *argv[], TTGLibraryContext *libctx);





int (*tgsftp_cd)(const char *adir,TTGLibraryContext *libctx);















                                                          const struct fxp_attrs *attrs,
                                                          TTGLibraryContext *libctx);
int (*tgputty_closefile)(struct fxp_handle **fh,TTGLibraryContext *libctx);









bool GetProc(const LPCSTR lpProcName,void *p)
{
  *(FARPROC*)p = GetProcAddress(hPuttyLib,lpProcName);
  bool res = ((*(void**)p)!=NULL);
  if (!res)
     printf("Function missing in DLL: %s\n",lpProcName);
  return res;
}

bool LoadTGPuttyLib()
{
  if (hPuttyLib)
     return true;

  hPuttyLib = LoadLibrary("tgputtylib.dll");

  if (!hPuttyLib)
     return false;

  bool res=true;

  res &= GetProc("psftp_main",&psftp_main);
  res &= GetProc("tggetlibrarycontextsize",&tggetlibrarycontextsize);
  res &= GetProc("tgputty_initcontext",&tgputty_initcontext);
  res &= GetProc("tgputty_initwithcmdline",&tgputty_initwithcmdline);
  res &= GetProc("tgputtyrunpsftp",&tgputtyrunpsftp);
  res &= GetProc("tgputtysetappname",&tgputtysetappname);
  res &= GetProc("tgputtysftpcommand",&tgputtysftpcommand);
  res &= GetProc("tgsftp_connect",&tgsftp_connect);
  res &= GetProc("tgsftp_cd",&tgsftp_cd);
  res &= GetProc("tgsftp_rm",&tgsftp_rm);
  res &= GetProc("tgsftp_rmdir",&tgsftp_rmdir);
  res &= GetProc("tgsftp_ls",&tgsftp_ls);
  res &= GetProc("tgsftp_mkdir",&tgsftp_mkdir);
  res &= GetProc("tgsftp_mv",&tgsftp_mv);
  res &= GetProc("tgsftp_mvex",&tgsftp_mvex);
  res &= GetProc("tgsftp_getstat",&tgsftp_getstat);
  res &= GetProc("tgsftp_setstat",&tgsftp_setstat);
  res &= GetProc("tgsftp_putfile",&tgsftp_putfile);
  res &= GetProc("tgsftp_getfile",&tgsftp_getfile);
  res &= GetProc("tgsftp_close",&tgsftp_close);
  res &= GetProc("tgputty_setverbose",&tgputty_setverbose);
  res &= GetProc("tgputty_setkeyfile",&tgputty_setkeyfile);
  res &= GetProc("tgputty_openfile",&tgputty_openfile);
  res &= GetProc("tgputty_closefile",&tgputty_closefile);
  res &= GetProc("tgputty_xfer_upload_init",&tgputty_xfer_upload_init);
  res &= GetProc("tgputty_xfer_upload_ready",&tgputty_xfer_upload_ready);
  res &= GetProc("tgputty_xfer_upload_data",&tgputty_xfer_upload_data);
  res &= GetProc("tgputty_xfer_ensuredone",&tgputty_xfer_ensuredone);
  res &= GetProc("tgputty_xfer_done",&tgputty_xfer_done);
  res &= GetProc("tgputty_xfer_cleanup",&tgputty_xfer_cleanup);
  res &= GetProc("tgputtygetversions",&tgputtygetversions);
  res &= GetProc("tgputtyfree",&tgputtyfree);

  if (!res)
  {
     FreeLibrary(hPuttyLib);
     hPuttyLib = NULL;
  }
  return res;
}

