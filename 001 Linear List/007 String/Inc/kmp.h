/*******************************************************************************
 * @file kmp.h
 * @author sheer.rey
 * @date Aug. 30, 2022
 *
 * @note
 * This pair of files, or, these series of file piars is my personal realization
 * of Data Structure in corresponding learning progress.
 *
 * Tip.1 I hope you know is there may be some slapdash mistake.
 *
 * Another thing is, the reason why I choose to use full english comment is I
 * want to improve my english level by this way.
 *
 * Tip.2 is if you find some grammatical error or others and tell me that
 * I will be very greatful to you! The style of these pair of files may be
 * variable, cause it's also in my C++ learning process, so the programme
 * style may transform C to C++ gradually.
 * ****************************************************************************/

#ifndef _KMP_H_
#define _KMP_H_

#include <string>
#include <vector>

/* my (sheer.rey) namespace */
namespace libofsheerrey {
  int Search(std::string source, std::string pattern);
}  // namespace libofsheerrey

#endif