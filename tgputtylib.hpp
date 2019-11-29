#ifndef tgputtylibH
#define tgputtylibH

#define tgputtydll_filename "tgputtylib.dll"

#define SSH_FILEXFER_ATTR_SIZE                    0x00000001
#define SSH_FILEXFER_ATTR_UIDGID                  0x00000002
#define SSH_FILEXFER_ATTR_PERMISSIONS             0x00000004
#define SSH_FILEXFER_ATTR_ACMODTIME               0x00000008
#define SSH_FILEXFER_ATTR_EXTENDED                0x80000000

#define SSH_FXF_READ                              0x00000001
#define SSH_FXF_WRITE                             0x00000002
#define SSH_FXF_APPEND                            0x00000004
#define SSH_FXF_CREAT                             0x00000008
#define SSH_FXF_TRUNC                             0x00000010
#define SSH_FXF_EXCL                              0x00000020


typedef unsigned __int64 uint64_t;

struct fxp_attrs {
    unsigned long flags;
    uint64_t size;
    unsigned long uid;
    unsigned long gid;
    unsigned long permissions;
    unsigned long atime;
    unsigned long mtime;
};

struct fxp_name {
    char *filename, *longname;
    struct fxp_attrs attrs;
};

struct fxp_names {
    int nnames;
    struct fxp_name *names;
};

typedef struct fxp_names Tfxp_names;

typedef void *TSFTPFileHandle;
typedef TSFTPFileHandle *PSFTPFileHandle;
typedef void *TSFTPTransfer;

typedef struct
{
  // PUBLISHED PART OF STRUCT
  int structsize;
  __int64 tag;

  bool (*ls_callback)(const struct fxp_names *names,const void *libctx);
  char* (*getpassword_callback)(const char *prompt, const bool echo, const bool *cancel, const void *libctx);
  void (*printmessage_callback)(const char *msg, const bool isstderr, const void *libctx);
  bool (*progress_callback)(const uint64_t bytescopied, const bool isupload, const void *libctx);
  int (*read_from_stream)(const uint64_t offset,void *buffer,const int bufsize, const void *libctx);
  int (*write_to_stream)(const uint64_t offset,void *buffer,const int bufsize, const void *libctx);
  bool (*get_input_callback)(char *linebuf,const int maxchars, const void *libctx);
  bool (*verify_host_key_callback)(const char *host,const int port,const char *keytype,
                                   const char *keystr,const char *fingerprint,
                                   const int verificationstatus,
                                   bool *storehostkey, const void *libctx);
  void (*raise_exception_callback)(const char *msg,const char *srcfile,const int line,const void *libctx);
  void (*entercriticalsection_callback)(const int Num); // not currently used because they wouldn't work cross-process
  void (*leavecriticalsection_callback)(const int Num); // not currently used because they wouldn't work cross-process

  // these aren't really good for much ...
  int mode;
  int modeflags;
  char *batchfile;

  // sftp client state from psftp.c
  char *pwd, *homedir; // accessed by host application too

  // static items from sftp.c
  const char *fxp_error_message; // accessed by host application too
  int fxp_errtype; // accessed by host application too

  // STRICTLY LIBRARY PRIVATE FIELDS FOLLOW
  char reservedbytes[301];

} TTGLibraryContext;











extern int (*tgsftp_cd)(const char *adir,TTGLibraryContext *libctx);















                                                          const struct fxp_attrs *attrs,
                                                          TTGLibraryContext *libctx);
extern int (*tgputty_closefile)(struct fxp_handle **fh,TTGLibraryContext *libctx);












#endif