#ifndef __SHARED_PTR_HPP__
#define __SHARED_PTR_HPP__


class shared_counter_base_c
{
public:
  virtual ~shared_counter_base_c () {};
  virtual bool release () = 0;
  virtual void inc () = 0;
  virtual unsigned int value () = 0;
};
// -------------------------------------------------------------------
template <class T>
class shared_counter_c : public shared_counter_base_c
{
public:
  typedef T    elem_t;
public:
  shared_counter_c ();
  shared_counter_c (elem_t* ptr);
        
  ~shared_counter_c ();

  void dispose ();
  virtual bool release ();
  virtual void inc ();
  virtual unsigned int value ();
        
        
private:
  typedef  unsigned int counter_t;
  counter_t m_counter;
  elem_t*   m_ptr;
};
// ------------------------------------------------------------------------------
template <class T>
class shared_ptr_c
{
public:
  typedef T                   elem_t;
  typedef shared_ptr_c<T>     self_t;
  typedef shared_counter_c<T> counter_t;
public:
  shared_ptr_c ();
  explicit shared_ptr_c (elem_t* ptr);
  shared_ptr_c (const shared_ptr_c& obj);
  shared_ptr_c (elem_t* ptr, shared_counter_base_c* counter);

  ~shared_ptr_c ();
        
  T* get ();
  const T* get () const;

  T* operator -> ();
  const T* operator -> () const;

  self_t* clone ();

  bool release ();
  shared_counter_base_c* counter () const;

  bool null () const;
private:
  shared_counter_base_c* m_counter;
  T* m_ptr;
};

template <class T, class T0>
inline
shared_ptr_c<T> shared_cast (shared_ptr_c<T0> sp)
{
  return shared_ptr_c<T> (dynamic_cast<T *>(sp.get ()), sp.counter ());
}

// =========================================================================
// Implementation
// =========================================================================

// =====================================================================
// shared_counter_c
// =====================================================================
template <class T>
inline
shared_counter_c<T>::shared_counter_c ()
  : m_counter (1),
    m_ptr (0)
{
        
}
// ---------------------------------------------------------------------
template <class T>
inline
shared_counter_c<T>::shared_counter_c (elem_t* ptr)
  : m_counter (1),
    m_ptr (ptr)
{
}
// ---------------------------------------------------------------------
template <class T>
inline
shared_counter_c<T>::~shared_counter_c ()
{
        
}
// ---------------------------------------------------------------------
template <class T>
inline
void shared_counter_c<T>::dispose ()
{
  delete m_ptr;
}
// ---------------------------------------------------------------------
template <class T>
bool shared_counter_c<T>::release ()
{
  if (m_ptr && (--m_counter == 0))
    {
      dispose ();
      return true;
    }
  return false;
}
// ---------------------------------------------------------------------
template <class T>
void shared_counter_c<T>::inc ()
{
  m_counter++;
}
// ---------------------------------------------------------------------
template <class T>
unsigned int shared_counter_c<T>::value ()
{
  return m_counter;
}
// =====================================================================
// shared_ptr_c
// =====================================================================
template <class T>
inline
shared_ptr_c<T>::shared_ptr_c ()
  : m_counter (0),
    m_ptr (0)
{
}
// ---------------------------------------------------------------------
template <class T>
inline
shared_ptr_c<T>::shared_ptr_c (elem_t* ptr)
  : m_counter (new counter_t (ptr)),
    m_ptr (ptr)
{
}
// ---------------------------------------------------------------------
template <class T>
inline
shared_ptr_c<T>::shared_ptr_c (elem_t* ptr, shared_counter_base_c* counter)
  : m_counter (counter),
    m_ptr (0)
{
  if (ptr)
    {
      m_counter->inc ();
    }
  m_ptr = ptr;
}
// ---------------------------------------------------------------------
template <class T>
inline
shared_ptr_c<T>::shared_ptr_c (const shared_ptr_c& obj)
  : m_counter (obj.counter ()),
    m_ptr (0)
{
  if (obj.m_ptr)
    {
      m_counter->inc ();
    }
  m_ptr = obj.m_ptr;
}
// ---------------------------------------------------------------------
template <class T>
inline
shared_ptr_c<T>::~shared_ptr_c ()
{
  this->release ();
}
// ---------------------------------------------------------------------
template <class T>
inline
T* shared_ptr_c<T>::get ()
{
  return m_ptr;
}
// ---------------------------------------------------------------------
template <class T>
inline
const T* shared_ptr_c<T>::get () const
{
  return m_ptr;
}
// ---------------------------------------------------------------------
template <class T>
inline
T* shared_ptr_c<T>::operator -> ()
{
  return m_ptr;
}
// ---------------------------------------------------------------------
template <class T>
inline
const T* shared_ptr_c<T>::operator -> () const
{
  return m_ptr;
}
// ---------------------------------------------------------------------
template <class T>
inline
typename shared_ptr_c<T>::self_t* shared_ptr_c<T>::clone ()
{
  return new shared_ptr_c<T>(*this);
}
// ---------------------------------------------------------------------
template <class T>
inline
bool shared_ptr_c<T>::release ()
{
  if (!m_counter)
    {
      return false;
    }
  if (m_counter->release ())
    {
      delete m_counter;
      m_counter = 0;
      m_ptr = 0;
      return true;
    }
  return false;
}
// ---------------------------------------------------------------------
template <class T>
inline
shared_counter_base_c* shared_ptr_c<T>::counter () const
{
  return m_counter;
}
// ---------------------------------------------------------------------
template <class T>
inline
bool shared_ptr_c<T>::null () const
{
  return (m_ptr == 0);
}


#endif
