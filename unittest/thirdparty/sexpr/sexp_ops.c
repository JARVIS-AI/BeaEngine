/**
@cond IGNORE

======================================================
 SFSEXP: Small, Fast S-Expression Library version 1.2
 Written by Matthew Sottile (matt@cs.uoregon.edu)
======================================================

Copyright (2003-2006). The Regents of the University of California. This
material was produced under U.S. Government contract W-7405-ENG-36 for Los
Alamos National Laboratory, which is operated by the University of
California for the U.S. Department of Energy. The U.S. Government has rights
to use, reproduce, and distribute this software. NEITHER THE GOVERNMENT NOR
THE UNIVERSITY MAKES ANY WARRANTY, EXPRESS OR IMPLIED, OR ASSUMES ANY
LIABILITY FOR THE USE OF THIS SOFTWARE. If software is modified to produce
derivative works, such modified software should be clearly marked, so as not
to confuse it with the version available from LANL.

Additionally, this library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License as
published by the Free Software Foundation; either version 2.1 of the
License, or (at your option) any later version.

This library is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License
for more details.

You should have received a copy of the GNU Lesser General Public License
along with this library; if not, write to the Free Software Foundation,
Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, U SA

LA-CC-04-094

@endcond
**/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sexp_ops.h"

/**
 * Given an s-expression, find the atom inside of it with the 
 * value matchine name, and return a reference to it.  If the atom
 * doesn't occur inside start, return NULL.
 */
sexp_t *
find_sexp (const char *name, sexp_t * start)
{
  sexp_t *temp;

  if (start == NULL)
    return NULL;

  if (start->ty == SEXP_LIST)
    {
      temp = find_sexp (name, start->list);
      if (temp == NULL)
	return find_sexp (name, start->next);
      else
	return temp;
    }
  else
    {
      if (start->val != NULL && strcmp (start->val, name) == 0)
	return start;
      else
	return find_sexp (name, start->next);
    }
#if !defined (__INTEL_COMPILER) /* Make compiler hapy */
  return NULL;			/* shouldn't get here */
#endif
}

/**
 * Breadth first search - look at ->next before ->list when seeing list
 * elements of an expression.
 */
sexp_t *bfs_find_sexp(const char *str, sexp_t *sx) {
  sexp_t *t = sx;
  sexp_t *rt;
  
  if (sx == NULL) return NULL;

  while (t != NULL) {
    if (t->ty == SEXP_VALUE) {
      if (t->val != NULL) {
	if (strcmp(t->val,str) == 0) {
	  return t;
	}
      }
    } 

    t = t->next;
  }

  t = sx;
  while (t != NULL) {
    if (t->ty == SEXP_LIST) {
      rt = bfs_find_sexp(str,t->list);
      if (rt != NULL) return rt;
    }
    
    t = t->next;
  }

  return NULL;
}

/**
 * Give the length of a s-expression list.
 */
int sexp_list_length(const sexp_t *sx) {
  int len = 0;
  const sexp_t *t;

  if (sx == NULL) return 0;

  if (sx->ty == SEXP_VALUE) return 1;

  t = sx->list;
  
  while (t != NULL) {
    len++;
    t = t->next;
  }
  return len;
}

/**
 * Copy an s-expression.
 */
sexp_t *copy_sexp(const sexp_t *s) {
  sexp_t *snew_exp;

  if (s == NULL) return NULL;

  snew_exp = sexp_t_allocate();
  if (snew_exp == NULL) {
    sexp_errno = SEXP_ERR_MEMORY;
    return NULL;
  }

  /* initialize fields to null and zero, and fill in only those necessary. */
  snew_exp->val_allocated = snew_exp->val_used = 0;
  snew_exp->val = NULL;
  snew_exp->list = snew_exp->next = NULL;
  snew_exp->bindata = NULL;
  snew_exp->binlength = 0;

  /* now start copying in data and setting appropriate fields. */
  snew_exp->ty = s->ty;

  /* values */
  if (snew_exp->ty == SEXP_VALUE) {
    snew_exp->aty = s->aty;

    /* binary */
    if (snew_exp->aty == SEXP_BINARY) {
      if (s->bindata == NULL && s->binlength > 0) {
	sexp_errno = SEXP_ERR_BADCONTENT;
	sexp_t_deallocate(snew_exp);
	return NULL;
      }
      
      snew_exp->binlength = s->binlength;
      
      if (s->bindata == NULL) {
	snew_exp->bindata = NULL;
      } else {
	/** allocate space **/
#ifdef __cplusplus
	snew_exp->bindata = (char *)sexp_malloc(sizeof(char)*s->binlength);
#else
	snew_exp->bindata = sexp_malloc(sizeof(char)*s->binlength);
#endif
      }

      if (snew_exp->bindata == NULL) {
	sexp_errno = SEXP_ERR_MEMORY;
	sexp_t_deallocate(snew_exp);
	return NULL;
      }

      memcpy(snew_exp->bindata,s->bindata,s->binlength*sizeof(char));

    /* non-binary */ 
    } else {
      if (s->val == NULL && (s->val_used > 0 || s->val_allocated > 0)) {
	sexp_errno = SEXP_ERR_BADCONTENT;
	sexp_t_deallocate(snew_exp);
	return NULL;
      }

      snew_exp->val_used = snew_exp->val_allocated = s->val_used;

      if (s->val == NULL) {
	snew_exp->val = NULL;
      } else {
	/** allocate space **/
#ifdef __cplusplus
	snew_exp->val = (char *)sexp_malloc(sizeof(char)*s->val_used);
#else
	snew_exp->val = sexp_malloc(sizeof(char)*s->val_used);
#endif

	if (snew_exp->val == NULL) {
	  sexp_errno = SEXP_ERR_MEMORY;
	  sexp_t_deallocate(snew_exp);
	  return NULL;
	}

	strcpy(snew_exp->val,s->val);
      }
    }
  } else {
    snew_exp->list = copy_sexp(s->list);
  }
  
  snew_exp->next = copy_sexp(s->next);

  return snew_exp;
}

