// WordChecker.cpp
//
// ICS 46 Spring 2016
// Project #3: Set the Controls for the Heart of the Sun
//
// Replace and/or augment the implementations below as needed to meet
// the requirements.

#include "WordChecker.hpp"
#include <iostream>


WordChecker::WordChecker(const Set<std::string>& words)
    : words{words}
{
}


bool WordChecker::wordExists(const std::string& word) const
{
    return this->words.contains(word);
}

std::vector<std::string> WordChecker::findSuggestions(const std::string& word) const
{
	std::vector<std::string> suggestions;
	std::string alphabet ="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		//begin swap DONEEE
        for (int i = 0; i < word.size() - 1; i++)
        {
            std::string temp = word;
            std::swap(temp[i], temp[1+1]);
            if (wordExists(temp) && (std::find(suggestions.begin(), suggestions.end(), temp) == suggestions.end()))
                suggestions.push_back(temp);
        }
         //begin insert character DONE
        for (int i = 0; i <= word.size(); i++)
        {
            for (int x = 0; x < alphabet.size(); x++)
            {
                std::string second_temp = word;
                second_temp.insert(i, alphabet.substr(x,1));
                if (wordExists(second_temp) && (std::find(suggestions.begin(), suggestions.end(), second_temp) == suggestions.end()))
                    suggestions.push_back(second_temp);
            }
        }
        //begin delete DONE 
        for (int i = 0; i < word.size(); i++)
        {
            std::string temp = word;
            temp = temp.erase(i,1);
             if (wordExists(temp) && (std::find(suggestions.begin(), suggestions.end(), temp) == suggestions.end()))
                suggestions.push_back(temp);
        }
        //begin replace character DONEEEEE
        for (int i = 0; i < word.size(); i++) // every letter first
        {
            
            for (int y = 0; y < alphabet.size(); y++)// then swap in every alphabet character
            {
                std::string second_copy = word;
                second_copy[i] = alphabet[y]; // might have to use replace
                 if (wordExists(second_copy) && (std::find(suggestions.begin(), suggestions.end(), second_copy) == suggestions.end()))
                    suggestions.push_back(second_copy);
            }

        }
        //begin insert space for pairs DONE
        for (int i = 0; i < word.size() - 1; i++)
        {
            std::string temp = word;
            temp = temp.insert(i, " ");
            if (wordExists(temp) && (std::find(suggestions.begin(), suggestions.end(), temp) == suggestions.end()))
                suggestions.push_back(temp);
        }
        


    return suggestions;
}

