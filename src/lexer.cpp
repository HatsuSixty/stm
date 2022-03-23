#include "lexer.hpp"

std::vector <Token> tokenize_file(std::string path)
{
    std::fstream fs;
    fs.open("input.systack", std::ios::in);

    std::vector <std::string> words;
    
    if (fs.is_open())
    {
        std::string file_line;

	std::string word = "";
	std::vector <std::string> words;
	
        while(getline(fs, file_line))
	{
	    for (size_t i = 0; i < file_line.size(); ++i)
	    {
		if ((file_line[i] == ' ') || (file_line[i] == '\n') || (file_line[i] == '\r') || (file_line[i] == '\t'))
		{
		    if (!word.empty())
		    {
		    	words.push_back(word);
		    	word = "";
		    }
		}
		else
		{
		    word += file_line[i];
		}
	    }
        }

	for (std::string i : words)
	{
	    std::cout << i << '\n';
	}
	
	fs.close();
    }
    else
    {
	std::cerr << "ERROR: could not open file " << path << ": " << std::strerror(errno) << '\n';
	exit(3);
    }

    std::vector <Token> temp = {};
    
    return temp;
}
