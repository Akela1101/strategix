/* 
 * File:   Nya.hpp
 * Author: Akela1101
 *
 * 11.09.2010
 *
 * v.1.0
 */

#ifndef _NYA_HPP
#define	_NYA_HPP

#include <boost/foreach.hpp>
#define foreach         BOOST_FOREACH
#define rforeach        BOOST_REVERSE_FOREACH

#include "boost/smart_ptr.hpp"
#define sc_p boost::scoped_ptr
#define sc_a boost::scoped_array
#define sh_p boost::shared_ptr
#define sh_a boost::shared_array
#define w_p boost::weak_ptr

#endif	/* _NYA_HPP */

