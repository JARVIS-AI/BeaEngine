#include "unittest/regression/zip_archive.hpp"

#include <stdexcept>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <fcntl.h>

#ifdef unix
# include <unistd.h>
# include <utime.h>
# include <sys/types.h>
# include <sys/stat.h>
#else
# include <direct.h>
# include <io.h>
#endif

#include "unittest/thirdparty/microzip/zip.h"
#include "unittest/thirdparty/microzip/unzip.h"
#ifdef WIN32
#define USEWIN32IOAPI
#include "unittest/thirdparty/microzip/iowin32.h"
#endif



#define WRITEBUFFERSIZE (16384)
#define MAXFILENAME (256)

#ifdef WIN32
#define CASESENSITIVITY (0) 
#else 
#define CASESENSITIVITY (1) 
#endif



#ifdef WIN32
static uLong filetime(
		      const char *f,                /* name of file to get info on */
		      tm_zip *tmzip,             /* return value: access, modific. and creation times */
		      uLong *dt             /* dostime */
		      )
{
  int ret = 0;
  {
      FILETIME ftLocal;
      HANDLE hFind;
      WIN32_FIND_DATA  ff32;

      hFind = FindFirstFile(f,&ff32);
      if (hFind != INVALID_HANDLE_VALUE)
      {
        FileTimeToLocalFileTime(&(ff32.ftLastWriteTime),&ftLocal);
        FileTimeToDosDateTime(&ftLocal,((LPWORD)dt)+1,((LPWORD)dt)+0);
        FindClose(hFind);
        ret = 1;
      }
  }
  return ret;
}
#else
#ifdef unix
static uLong filetime(
		      const char *f,               /* name of file to get info on */
		      tm_zip *tmzip,         /* return value: access, modific. and creation times */
		      uLong *dt             /* dostime */
		      )
{
  int ret=0;
  struct stat s;        /* results of stat() */
  struct tm* filedate;
  time_t tm_t=0;

  if (strcmp(f,"-")!=0)
  {
    char name[MAXFILENAME+1];
    int len = strlen(f);
    if (len > MAXFILENAME)
      len = MAXFILENAME;

    strncpy(name, f,MAXFILENAME-1);
    /* strncpy doesnt append the trailing NULL, of the string is too long. */
    name[ MAXFILENAME ] = '\0';

    if (name[len - 1] == '/')
      name[len - 1] = '\0';
    /* not all systems allow stat'ing a file with / appended */
    if (stat(name,&s)==0)
    {
      tm_t = s.st_mtime;
      ret = 1;
    }
  }
  filedate = localtime(&tm_t);

  tmzip->tm_sec  = filedate->tm_sec;
  tmzip->tm_min  = filedate->tm_min;
  tmzip->tm_hour = filedate->tm_hour;
  tmzip->tm_mday = filedate->tm_mday;
  tmzip->tm_mon  = filedate->tm_mon ;
  tmzip->tm_year = filedate->tm_year;

  return ret;
}
#else
uLong filetime(
	       const char *f,                /* name of file to get info on */
	       tm_zip *tmzip,             /* return value: access, modific. and creation times */
	       uLong *dt             /* dostime */
	       )
{
    return 0;
}
#endif
#endif

static int check_exist_file (const char* filename)
{
    FILE* ftestexist;
    int ret = 1;
    ftestexist = fopen(filename,"rb");
    if (ftestexist==NULL)
        ret = 0;
    else
        fclose(ftestexist);
    return ret;
} 

// ================================================================
struct zip_oarchive_impl_s
{
  zipFile m_zf; 
};
// ================================================================

zip_oarchive_c::zip_oarchive_c (const char* zipname, zip_mode_t mode)
{
  int zipmode;
  if (mode == eCREATE)
    {
      if (check_exist_file (zipname) == 1)
	{
	  throw std::runtime_error ("Failed to create new zip archive");
	}
      zipmode = APPEND_STATUS_CREATE;
    }
  else
    {
      if (check_exist_file (zipname) == 0)
	{
	  throw std::runtime_error ("Failed to append to existing zip archive");
	}
      zipmode = APPEND_STATUS_ADDINZIP;
    }
  zipFile zf = zipOpen (zipname, zipmode);
  if (zf == NULL)
    {
      throw std::runtime_error ("microzip failure");
    }
  m_pimpl = new zip_oarchive_impl_s;
  m_pimpl->m_zf = zf;
}
// -----------------------------------------------------------------
zip_oarchive_c::~zip_oarchive_c ()
{
  if (m_pimpl->m_zf)
    {
      zipClose (m_pimpl->m_zf, "BeaEngine Regression tests");
    }
  delete m_pimpl;
}
// -----------------------------------------------------------------
void zip_oarchive_c::put (const std::string& file, const std::string& comment)
{
  const char* filenameinzip = file.c_str ();
  zip_fileinfo zi;
  unsigned long crcFile=0;
  
  zi.tmz_date.tm_sec = zi.tmz_date.tm_min = zi.tmz_date.tm_hour =
    zi.tmz_date.tm_mday = zi.tmz_date.tm_mon = zi.tmz_date.tm_year = 0;
  zi.dosDate = 0;
  zi.internal_fa = 0;
  zi.external_fa = 0;
  if (filetime(filenameinzip,&zi.tmz_date,&zi.dosDate) == 0)
    {
      throw std::runtime_error ("Failed to obtain filetime");
    }
  const int opt_compress_level = 9;
  const char* password = 0;
  
  int err = zipOpenNewFileInZip3(m_pimpl->m_zf,
				 filenameinzip,
				 &zi,
				 NULL,
				 0,
				 NULL,
				 0,
				 comment.c_str (),
				 (opt_compress_level != 0) ? Z_DEFLATED : 0,
				 opt_compress_level,
				 0,
				 -MAX_WBITS, 
				 DEF_MEM_LEVEL, 
				 Z_DEFAULT_STRATEGY,
				 password,
				 crcFile);

   if (err != ZIP_OK)
     {
       throw std::runtime_error ("Failed to open file in zip");
     }
   FILE* fin = NULL;
   fin = fopen(filenameinzip,"rb");
   if (fin==NULL)
     {
       throw std::runtime_error ("Failed to open source file for reading");
     }
   int size_buf = WRITEBUFFERSIZE;
   char* buf = new char [size_buf];
   int size_read = 0;
   do
     {
       err = ZIP_OK;
       
       size_read = (int)fread(buf,1,size_buf,fin);
       
       if (size_read < size_buf)
	 if (feof(fin)==0)
	   {
	     delete [] buf;
	     throw std::runtime_error ("Error in source file read");
	   }
       
       if (size_read>0)
	 {
	   err = zipWriteInFileInZip (m_pimpl->m_zf, buf, size_read);
	   if (err<0)
	     {
	       delete [] buf;
	       throw std::runtime_error ("error in writing to zip file");
	     }
	   
	 }
     } while ((err == ZIP_OK) && (size_read>0));
   
   if (fin)
     {
       fclose(fin);
     }
   delete [] buf;
   err = zipCloseFileInZip(m_pimpl->m_zf);
   if (err!=ZIP_OK)
     {
       throw std::runtime_error ("Failed to close file in zipfile");
     }
}
// =================================================================================
struct zip_entry_impl_s 
{
  zip_entry_impl_s (size_t length, int method, double ratio, UInt32 crc, 
		    const char* name, const char* comment,int index,
		    zip_iarchive_c* owner);

  size_t          m_length;
  int             m_method;
  double          m_ratio;
  UInt32          m_crc;
  std::string     m_name;
  std::string     m_comment;
  int             m_index;
  zip_iarchive_c* m_owner; 
};

zip_entry_impl_s::zip_entry_impl_s (size_t length, int method, double ratio, UInt32 crc, 
				    const char* name, const char* comment, int index,
				    zip_iarchive_c* owner)
  : m_length  (length),
    m_method  (method),
    m_ratio   (ratio),
    m_crc     (crc),
    m_name    (name),
    m_comment (comment),
    m_index   (index),
    m_owner   (owner)
{
}
// =========================================================================
size_t zip_entry_c::length    () const
{
  return m_pimpl->m_length;
}
// -------------------------------------------------------------------------
int zip_entry_c::method () const
{
  return m_pimpl->m_method;
}
// -------------------------------------------------------------------------
double zip_entry_c::ratio () const
{
  return m_pimpl->m_ratio;
}
// -------------------------------------------------------------------------
UInt32 zip_entry_c::crc () const
{
  return m_pimpl->m_crc;
}
// -------------------------------------------------------------------------
std::string zip_entry_c::name () const
{
  return m_pimpl->m_name;
}
// -------------------------------------------------------------------------
std::string zip_entry_c::comment () const
{
  return m_pimpl->m_comment;
}
// -------------------------------------------------------------------------
void zip_entry_c::explode ()
{
  m_pimpl->m_owner->_explode (m_pimpl->m_index);
}
// -------------------------------------------------------------------------
zip_entry_c::zip_entry_c ()
{
}
// -------------------------------------------------------------------------
zip_entry_c::zip_entry_c (size_t length_, int method_, double ratio_, UInt32 crc_, 
			  const char* name_, const char* comment_,
			  int index, zip_iarchive_c* owner)
  : m_pimpl (new zip_entry_impl_s (length_, method_, ratio_, crc_, name_, comment_, index, owner))
{
}
// =========================================================================
struct zip_iarchive_impl_s
{
  unzFile m_uzf;
  zip_iarchive_c::entry_list_t m_entries;
};
// -------------------------------------------------------------------------
zip_iarchive_c::zip_iarchive_c (const char* path)
{
  unzFile uzf = unzOpen (path);
  if (uzf == NULL)
    {
      throw std::runtime_error ("Cant open zip archive for reading");
    }
  m_pimpl = new zip_iarchive_impl_s;
  m_pimpl->m_uzf = uzf;
  uLong i;
  unz_global_info gi;
  int err;
  
  err = unzGetGlobalInfo (uzf ,&gi);
  if (err!=UNZ_OK)
    {
      throw std::runtime_error ("Zip file is corrupted");
    }
  for (i=0;i<gi.number_entry;i++)
    {
        char filename_inzip[256];
        unz_file_info file_info;
        double ratio=0;
	char comment [256];
        err = unzGetCurrentFileInfo(uzf,&file_info,filename_inzip,sizeof(filename_inzip),NULL,0,comment,sizeof (comment));
        if (err!=UNZ_OK)
        {
	  throw std::runtime_error ("Zip file is corrupted.");
        }
        if (file_info.uncompressed_size>0)
            ratio = (file_info.compressed_size*100)/file_info.uncompressed_size;
	zip_entry_c ze (file_info.uncompressed_size, file_info.compression_method, 
			ratio, file_info.crc, filename_inzip, comment, i, this);
	m_pimpl->m_entries.push_back (ze);
			
        if ((i+1)<gi.number_entry)
        {
            err = unzGoToNextFile(uzf);
            if (err!=UNZ_OK)
            {
	      throw std::runtime_error ("Zip file iteration failed");
            }
        }
    }
}
// -------------------------------------------------------------------------
zip_iarchive_c::~zip_iarchive_c ()
{
  unzClose (m_pimpl->m_uzf);
  delete m_pimpl;
}
// -------------------------------------------------------------------------
size_t zip_iarchive_c::size  () const
{
  return m_pimpl->m_entries.size ();
}
// -------------------------------------------------------------------------
bool zip_iarchive_c::empty () const
{
  return m_pimpl->m_entries.empty ();
}
// -------------------------------------------------------------------------
zip_iarchive_c::iterator_t zip_iarchive_c::begin () const
{
  return m_pimpl->m_entries.begin ();
}
// -------------------------------------------------------------------------
zip_iarchive_c::iterator_t zip_iarchive_c::end () const
{
  return m_pimpl->m_entries.end ();
}
// -------------------------------------------------------------------------
void zip_iarchive_c::_explode (int index)
{
  char filename_inzip[256];
  unz_file_info file_info;
  int err;
  err = unzGoToFirstFile (m_pimpl->m_uzf);
  if (err!=UNZ_OK)
    {
      throw std::runtime_error ("Zip file iteration failed");
    }

  for (int i=0;i <=index;i++)
    {
      err = unzGoToNextFile (m_pimpl->m_uzf);
      if (err!=UNZ_OK)
	{
	  throw std::runtime_error ("Zip file iteration failed");
	}
    }
  err = unzGetCurrentFileInfo(m_pimpl->m_uzf,
			      &file_info,
			      filename_inzip, sizeof(filename_inzip),
			      NULL, 0,
			      NULL, 0);
  if (err!=UNZ_OK)
    {
      throw std::runtime_error ("Zip file is corrupted.");
    }
  err = unzOpenCurrentFile (m_pimpl->m_uzf);
  if (err!=UNZ_OK)
    {
      throw std::runtime_error ("Zip file is corrupted.");
    }
  char buff [WRITEBUFFERSIZE];
  int remains = file_info.uncompressed_size;
  FILE* fout = fopen (filename_inzip, "wb");
  if (!fout)
    {
      unzCloseCurrentFile (m_pimpl->m_uzf);
      throw std::runtime_error ("Failed to open output file");
    }
  int exploded = 0;
  while (exploded < remains)
    {
      int n = unzReadCurrentFile (m_pimpl->m_uzf, buff, WRITEBUFFERSIZE);
      if (n < 0)
	{
	  unzCloseCurrentFile (m_pimpl->m_uzf);
	  fclose (fout);
	  throw std::runtime_error ("Failed to explode");
	}
      fwrite (buff, 1, n, fout);
      exploded += n;
    }
  fclose (fout);
  unzCloseCurrentFile (m_pimpl->m_uzf);
}
