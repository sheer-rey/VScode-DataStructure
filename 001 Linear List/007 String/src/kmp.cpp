/*******************************************************************************
 * @file kmp.cpp
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

#include "kmp.h"

/* my (sheer.rey) namespace */
namespace libofsheerrey {
  /*****************************************************************************
   * @name Search
   * @param source The source string used to match
   * @param pattern The pattern string used to match
   * @retval Indicate the first position in source that pattern matched, if not
   *         matched, return -1
   * @brief Check if the pattern is the substring of source and return the first
   *        position in source that pattern matched, if not matched, return -1
   * @attention The elements in next array (e.g. next[j]) indicates the index j
   *            need rool back to while pattern[j] do not match source[i]
   * **************************************************************************/
  int Search(std::string source, std::string pattern) {
    using std::vector, std::size_t, std::string;

    size_t source_size = source.size();
    size_t pattern_size = pattern.size();

    // calculate the next array
    vector<size_t> next(pattern_size, 0);
    size_t slow = 0;
    size_t fast = 1;
    while (fast < pattern_size) {
      if (pattern[fast] == pattern[slow]) {
        ++slow;
        if (++fast >= pattern_size) { break; }

        // optimized next array
        if (pattern[fast] == pattern[slow]) {
          next[fast] = next[slow];
        } else {
          next[fast] = slow;
        }
      } else if (slow) {
        slow = next[slow];
      } else {
        ++fast;
      }
    }

    // search the pattern
    slow = fast = 0;
    while (fast < source_size && slow < pattern_size) {
      if (source[fast] == pattern[slow]) {
        ++slow;
        ++fast;
      } else if (slow) {
        slow = next[slow];
      } else {
        ++fast;
      }
    }

    // return the result
    return slow < pattern_size ? -1 : fast - pattern_size;
  }

}  // namespace libofsheerrey