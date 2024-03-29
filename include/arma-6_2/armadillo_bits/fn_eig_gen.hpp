// Copyright (C) 2015 National ICT Australia (NICTA)
// 
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
// -------------------------------------------------------------------
// 
// Written by Conrad Sanderson - http://conradsanderson.id.au


//! \addtogroup fn_eig_gen
//! @{


template<typename T1>
inline
typename enable_if2< is_supported_blas_type<typename T1::pod_type>::value, Col< std::complex<typename T1::pod_type> > >::result
eig_gen
  (
  const Base<typename T1::elem_type, T1>& expr
  )
  {
  arma_extra_debug_sigprint();
  
  typedef typename T1::pod_type     T;
  typedef typename std::complex<T> eT;
  
  Col<eT> eigvals;
  Mat<eT> eigvecs;
  
  const bool status = auxlib::eig_gen(eigvals, eigvecs, uword(0), expr.get_ref());
  
  if(status == false)
    {
    eigvals.reset();
    arma_bad("eig_gen(): decomposition failed");
    }
  
  return eigvals;
  }



template<typename T1>
inline
typename enable_if2< is_supported_blas_type<typename T1::pod_type>::value, bool >::result
eig_gen
  (
         Col< std::complex<typename T1::pod_type> >& eigvals,
  const Base< typename T1::elem_type, T1>&           expr
  )
  {
  arma_extra_debug_sigprint();
  
  typedef typename T1::pod_type     T;
  typedef typename std::complex<T> eT;
  
  Mat<eT> eigvecs;
  
  const bool status = auxlib::eig_gen(eigvals, eigvecs, uword(0), expr.get_ref());
  
  if(status == false)
    {
    eigvals.reset();
    arma_debug_warn("eig_gen(): decomposition failed");
    }
  
  return status;
  }



template<typename T1>
inline
typename enable_if2< is_supported_blas_type<typename T1::pod_type>::value, bool >::result
eig_gen
  (
        Col< std::complex<typename T1::pod_type> >& eigvals,
        Mat< std::complex<typename T1::pod_type> >& eigvecs,
  const Base<typename T1::elem_type, T1>&           expr,
  const char                                        mode = 'r'
  )
  {
  arma_extra_debug_sigprint();
  
  arma_debug_check( (void_ptr(&eigvals) == void_ptr(&eigvecs)), "eig_gen(): parameter 'eigval' is an alias of parameter 'eigvec'" );
  
  arma_debug_check( ((mode != 'l') && (mode != 'r')), "eig_gen(): parameter 'mode' must be either 'l' or 'r'" );
  
  uword id = 0;
  
  if(mode == 'l')  { id = 1; }
  if(mode == 'r')  { id = 2; }
  
  const bool status = auxlib::eig_gen(eigvals, eigvecs, id, expr.get_ref());
  
  if(status == false)
    {
    eigvals.reset();
    eigvecs.reset();
    arma_debug_warn("eig_gen(): decomposition failed");
    }
  
  return status;
  }



//! NOTE: this form is deprecated -- don't use it
template<typename T1>
arma_deprecated
inline
typename enable_if2< is_supported_blas_type<typename T1::elem_type>::value, bool >::result
eig_gen
  (
         Col< std::complex<typename T1::pod_type> >& eigvals, 
         Mat<typename T1::elem_type>&                eigvecs_l,
         Mat<typename T1::elem_type>&                eigvecs_r,
  const Base<typename T1::elem_type,T1>&             expr
  )
  {
  arma_extra_debug_sigprint();
  
  arma_debug_check( (void_ptr(&eigvecs_l) == void_ptr(&eigvecs_r)), "eig_gen(): parameter 'eigvec_l' is an alias of parameter 'eigvec_r'" );
  arma_debug_check( (void_ptr(&eigvecs_l) == void_ptr(&eigvals)  ), "eig_gen(): parameter 'eigvec_l' is an alias of parameter 'eigval'"   );
  arma_debug_check( (void_ptr(&eigvecs_r) == void_ptr(&eigvals)  ), "eig_gen(): parameter 'eigvec_r' is an alias of parameter 'eigval'"   );
  
  const bool status = auxlib::eig_gen_dual(eigvals, eigvecs_l, eigvecs_r, expr.get_ref());
  
  if(status == false)
    {
    eigvals.reset();
    eigvecs_l.reset();
    eigvecs_r.reset();
    arma_debug_warn("eig_gen(): decomposition failed");
    }
  
  return status;
  }


//! @}
