#ifndef __ZIP_ARCHIVE_HPP__
#define __ZIP_ARCHIVE_HPP__

#include <string>
#include <list>
#include <beaengine/basic_types.h>

#include "unittest/regression/shared_ptr.hpp"

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
  zip_oarchive_c (const zip_oarchive_c&);
  zip_oarchive_c& operator = (const zip_oarchive_c&);
private:
  zip_oarchive_impl_s* m_pimpl;
};

struct zip_entry_impl_s;
class zip_iarchive_c;

class zip_entry_c
{
  friend class zip_iarchive_c;
public:
  zip_entry_c ();
public:
  size_t length    () const;
  int    method    () const;
  double ratio     () const;
  UInt32 crc       () const;
  std::string name () const;
  std::string comment () const;

  void explode ();
private:
  zip_entry_c (size_t length_, int method_, 
	       double ratio_ , UInt32 crc_, 
	       const char* name_, 
	       const char* comment_,
	       int index, zip_iarchive_c* owner);
private:
  shared_ptr_c <zip_entry_impl_s> m_pimpl;
};


struct zip_iarchive_impl_s;
class zip_iarchive_c
{
  friend class zip_entry_c;
public:
  typedef std::list <zip_entry_c>      entry_list_t;
  typedef entry_list_t::const_iterator iterator_t;
public:
  zip_iarchive_c (const char* path);
  ~zip_iarchive_c ();
  
  size_t size  () const;
  bool   empty () const;
  
  iterator_t begin () const;
  iterator_t end   () const;
private:
  void _explode (int index);
private:
  zip_iarchive_c (const zip_iarchive_c&);
  zip_iarchive_c& operator = (const zip_iarchive_c&);
private:
  zip_iarchive_impl_s* m_pimpl;
};


#endif
