#ifndef ___PROJECT_3_CONVERT_HPP
#define ___PROJECT_3_CONVERT_HPP

#include <cstddef>
#include <istream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include "Wordset.hpp"

namespace shindler::ics46::project3 {

template <unsigned int H1, unsigned int H2, unsigned int EvictThreshold>
[[nodiscard]] std::vector<std::string> convert(const std::string& start,
                                               const std::string& end,
                                               const BaseWordSet<H1, H2, EvictThreshold>& words) {
    std::vector<std::string> resultpath;
    if(start==end)
    {
        resultpath.push_back(start);
        return resultpath;
    }
    std::queue<std::string> explore;
    std::unordered_map<std::string, std::string> predecessors;
    explore.push(start);
    while(!explore.empty())
    {
        std::string currentword = explore.front();
        explore.pop();
        if(currentword==end)
        {
            for (std::string at = end; at != start; at = predecessors[at]) {
                resultpath.push_back(at);
            }
            resultpath.push_back(start);
            std::reverse(resultpath.begin(), resultpath.end());
            return resultpath;
        }
        for(size_t i=0;i<currentword.size();++i)
        {
            std::string nextword = currentword;
            for(char alpa = 'a'; alpa <= 'z'; ++alpa)
            {
                nextword[i] = alpa;
                if(words.contains(nextword)&&predecessors.find(nextword)==predecessors.end())
                {
                    predecessors[nextword] = currentword;
                    explore.push(nextword);
                }
            }
        }
    }
    return resultpath;
}

// You should not need to change this function
template <unsigned int H1, unsigned int H2, unsigned int EvictThreshold>
void loadWordsIntoTable(std::istream& istream,
                        BaseWordSet<H1, H2, EvictThreshold>& words) {
    std::string word;

    while (istream >> word) {
        words.insert(word);
    }
}

}  // namespace shindler::ics46::project3

#endif
