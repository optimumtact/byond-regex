/*
	This file is part of bygex.

    bygex is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as
	published by the Free Software Foundation, either version 3 of
	the License, or (at your option) any later version.

    bygex is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with bygex.  If not, see <http://www.gnu.org/licenses/>

    Based on code by Zac Stringham -  Copyright 2009.
    Rewritten 6-Oct-2013 - carnie (elly1989@rocketmail.com), accreditation appreciated but not required.
    Please do not remove this comment.
*/

#include <cstdlib>
#include <iostream>
#include <string>
#include <boost/regex.hpp>
#include <sstream>
#include "main.h"

#define REGEX_FLAVOUR boost::regex::perl

static char *result = 0;

void free_statics(){
    if(result){
        delete[] result;
        result = 0;
    }
}

char *return_result(std::string const& str){
    free_statics();
    result = new char[str.size()+1];
    if(result){
        memcpy(result, str.c_str(), str.size());
        result[str.size()] = '\0';
    }
    return result;
}

char *smatches2params(boost::smatch const& results, unsigned int from){
	free_statics();

	std::stringstream ss;
    if(ss){
        for(unsigned int i=0; i<results.size(); ++i){
            ss << '0' << '=' << results.position(i)+1+from << ';';   //+1 corrects for the fact byond starting index is 1, not 0.
            ss << '0' << '=' << results.length(i) << ';';
        }
        if(ss.good()){return return_result(ss.str());}
    }
    return return_result("Err: smatches2params failed.");
}

const char *err2msg(boost::regex_error *err){
    switch(err->code()){
        case boost::regex_constants::error_collate:
            return "Err: The expression contained an invalid collating element name.";
        case boost::regex_constants::error_ctype:
            return "Err: The expression contained an invalid character class name.";
        case boost::regex_constants::error_escape:
            return "Err: The expression contained an invalid escaped character, or a trailing escape.";
        case boost::regex_constants::error_backref:
            return "Err: The expression contained an invalid back reference.";
        case boost::regex_constants::error_brack:
            return "Err: The expression contained mismatched brackets ([ and ]).";
        case boost::regex_constants::error_paren:
            return "Err: The expression contained mismatched parentheses (( and )).";
        case boost::regex_constants::error_brace:
            return "Err: The expression contained mismatched braces ({ and }).";
        case boost::regex_constants::error_badbrace:
            return "Err: The expression contained an invalid range between braces ({ and }).";
        case boost::regex_constants::error_range:
            return "Err: The expression contained an invalid character range.";
        case boost::regex_constants::error_space:
            return "Err: There was insufficient memory to convert the expression into a finite state machine.";
        case boost::regex_constants::error_badrepeat:
            return "Err: The expression contained a repeat specifier (one of *?+{) that was not preceded by a valid regular expression.";
        case boost::regex_constants::error_complexity:
            return "Err: The complexity of an attempted match against a regular expression exceeded a pre-set level.";
        case boost::regex_constants::error_stack:
            return "Err: There was insufficient memory to determine whether the regular expression could match the specified character sequence.";
        default:
            return "Err: Unknown Error.";
    }
}

char *regex_compare_backend(int argc, char *argv[], boost::regex::flag_type match_options=0){
    if(argc < 2){return return_result("Err: Not enough arguments.");}

    std::string subject = argv[0];
    std::string::const_iterator from = subject.begin();
    std::string::const_iterator to = subject.end();

    unsigned int offset = 0;
    if(argc >= 3){
        int temp = atoi(argv[2]) - 1;
        if(temp > 0){
            offset = (unsigned)temp;
            unsigned int len = subject.length();
            if(offset > len){
                offset = len;
            }
            from += offset;
        }
    }

    boost::smatch matches;
    try{
        boost::regex expression(argv[1], match_options);
        if(boost::regex_match(from, to, matches, expression)){
            return smatches2params(matches, offset);
        } else{
            return 0;
        }
    }
    catch(boost::regex_error &err){return return_result(err2msg(&err));}
    catch(...){return return_result("Err: Unknown Error.");}
}

// (str, expr, from, to)
char *regEx_compare(int argc, char *argv[]){
	return regex_compare_backend(argc, argv, REGEX_FLAVOUR);
}

// (str, expr, from, to)
char *regex_compare(int argc, char *argv[]){
	return regex_compare_backend(argc, argv, boost::regex::icase|REGEX_FLAVOUR);
}

char *regex_findall_backend(int argc, char *argv[], boost::regex::flag_type match_options=0){
    if(argc < 2){return return_result("Err: Not enough arguments.");}

    std::string subject = argv[0];
    std::string::const_iterator from = subject.begin();
    std::string::const_iterator to = subject.end();

    free_statics();
    std::stringstream ss;

    try{
        boost::regex expression(argv[1], match_options);

        boost::sregex_iterator m1(from, to, expression);
        boost::sregex_iterator m2;

        unsigned int j=0;
        for(; m1!=m2; ++m1){
            for(unsigned int i=0; i<(*m1).size(); ++i){
                ss << j << '=' << (*m1).position(i)+1 << ';';   //+1 corrects for the fact byond starting index is 1, not 0.
                ss << j << '=' << (*m1).length(i) << ';';
            }
            ++j;
        }

        if(ss.good()){return return_result(ss.str());}
        return return_result("Err: Bad stringstream.");
    }
    catch(boost::regex_error &err){return return_result(err2msg(&err));}
    catch(...){return return_result("Err: Unknown Error.");}

}

char *regex_find_backend(int argc, char *argv[], boost::regex::flag_type match_options=0){
    if(argc < 2){return return_result("Err: Not enough arguments.");}

    std::string subject = argv[0];
    std::string::const_iterator from = subject.begin();
    std::string::const_iterator to = subject.end();
    unsigned int offset = 0;
    if(argc >= 3){
        int temp = atoi(argv[2]) - 1;
        if(temp > 0){
            offset = (unsigned)temp;
            unsigned int len = subject.length();
            if(offset > len){
                offset = len;
            }
            from += offset;
        }
    }

    boost::smatch matches;
    try{
        boost::regex expression(argv[1], match_options);
        if(boost::regex_search(from, to, matches, expression)){
            return smatches2params(matches, offset);
        } else{
            return 0;
        }
    }
    catch(boost::regex_error &err){return return_result(err2msg(&err));}
    catch(...){return return_result("Err: Unknown Error.");}
}

// (str, expr, from, to)
char *regEx_find(int argc, char *argv[]){
    return regex_find_backend(argc, argv, REGEX_FLAVOUR);
}

// (str, expr, from, to)
char *regex_find(int argc, char *argv[]){
    return regex_find_backend(argc, argv, boost::regex::icase|REGEX_FLAVOUR);
}

char *regex_replace_backend(int argc, char *argv[], boost::regex::flag_type match_options=boost::match_default, boost::match_flag_type fmt_options=boost::format_default){
    if(argc < 3){return return_result("Err: Not enough arguments.");}

    std::string subject = argv[0];
    std::string fmt = argv[2];

    try{
        boost::regex expression(argv[1], match_options);
        std::string formatted = boost::regex_replace(subject, expression, fmt, fmt_options);
        return return_result(formatted);
    }
    catch(boost::regex_error &err){return return_result(err2msg(&err));}
    catch(...){return return_result("Err: Unknown Error.");}
}

// (str, expr, fmt, from, to)
char *regEx_replaceall(int argc, char *argv[]){
	return regex_replace_backend(argc, argv, REGEX_FLAVOUR);
}

// (str, expr, fmt, from, to)
char *regex_replaceall(int argc, char *argv[]){
	return regex_replace_backend(argc, argv, REGEX_FLAVOUR|boost::regex::icase);
}

char *regEx_replace(int argc, char *argv[]){
    return regex_replace_backend(argc, argv, REGEX_FLAVOUR, boost::format_first_only);
}

char *regex_replace(int argc, char *argv[]){
    return regex_replace_backend(argc, argv, REGEX_FLAVOUR|boost::regex::icase, boost::format_first_only);
}

char *regEx_findall(int argc, char *argv[]){
     return regex_findall_backend(argc, argv, REGEX_FLAVOUR);
}

char *regex_findall(int argc, char *argv[]){
    return regex_findall_backend(argc, argv, REGEX_FLAVOUR|boost::regex::icase);
}

char *regEx_replaceallliteral(int argc, char *argv[]){
    return regex_replace_backend(argc, argv, REGEX_FLAVOUR|boost::regex::literal);
}

char *regex_replaceallliteral(int argc, char *argv[]){
    return regex_replace_backend(argc, argv, REGEX_FLAVOUR|boost::regex::literal|boost::regex::icase);
}
