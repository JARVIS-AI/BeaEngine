#include "unittest/regression/temp_path.hpp"

#if defined(WIN32)
#include <windows.h>
#else
#include <unistd.h> 
#endif

std::string get_temp_path ()
{
#if defined(WIN32)
 char buffer[1024];
 DWORD n = GetTempPathA(sizeof(buffer), buffer);
 if (n > 0 && n < sizeof(buffer))
   {
     std::string result (buffer, n);
     if (result[n - 1] != '\\')
       {
	 result.append("\\");
       }
     return result;
   } 
#else
 std::string path;
 char* tmp = getenv("TMPDIR");
 if (tmp)
   {
     path = tmp;
     std::string::size_type n = path.size();
     if (n > 0 && path[n - 1] != '/') path.append("/");
   }
 else
   {
     path = "/tmp/";
   }
 return path; 
#endif
}

std::string get_temp_path (const std::string& fname)
{
  return get_temp_path () + fname;
}
