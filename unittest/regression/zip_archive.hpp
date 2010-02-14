#ifndef __ZIP_ARCHIVE_HPP__
#define __ZIP_ARCHIVE_HPP__

#include <string>

enum zip_mode_t
  {
    eCREATE,
    eAPPEND
  };

struct zip_oarchive_impl_s;

class zip_oarchive_c
{
public:
  zip_oarchive_c (const char* zipname, zip_mode_t mode);
  ~zip_oarchive_c ();
  void put (const std::string& file, const std::string& comment);
private:
  zip_oarchive_impl_s* m_pimpl;
};


#endif
