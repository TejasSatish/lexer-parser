#include<iostream>
#include<string>
#include<string_view>
#include<optional>
using namespace std;

class Tokenizer{
public: 
    Tokenizer(std::string &input)
    : m_input { input }{ }  
    
    /**
     * optional makes it so that if there is no program then no string view will be created
    */
    std::optional<std::string_view> next(){
        auto view= std::string_view(m_input);
        while(m_index<m_input.length()){
            char c=m_input.at(m_index);
            switch(c){
                case ' ': 
                case '\n': //new line
                case '\t': // tab
                case '\r': //carriage return
                case ',':
                    ++m_index;
                    break;
                case '~':{
                    ++m_index;
                    if(m_index+1<m_input.length() && m_input.at(m_index+1)=='@'){ //checks if new string 
                    ++m_index;
                        return view.substr(m_index-2, 2);
                    }
                    return view.substr(m_index-1, 1);
                }   
                case '[':  
                case ']':
                case '(':
                case ')':
                case '{':
                case '}':
                case '\'': 
                case '`':
                case '^':
                case '@':{
                    return view.substr(m_index++,1);
                }
                case '"':{
                    size_t start=m_index;  //start index of string
                    ++m_index;
                    while(m_index<m_input.length()){
                        c=m_input.at(m_index);
                        switch(c){
                            case '"':
                                ++m_index;
                                return view.substr(start, m_index - start); //appends character to token
                            case '\\':
                                ++m_index; //goes next index
                                break;
                        }
                        ++m_index;  //goes next index
                    }
                    std::cout << "EOF\n";
                    return view.substr(start,m_index - start);
                }
                case ';':{
                    size_t start=m_index;
                    while(m_index < m_input.length()){
                        c=m_input.at(m_index);
                        if(c=='\n'){
                            break;
                        }
                        ++m_index;
                    }
                    return view.substr(start, m_index - start);
                }
                
                
                default:{    // used to escape blank characters
                    size_t start=m_index;
                    bool done = false;
                    while(!done && m_index<m_input.length()){
                        c=m_input.at(m_index);
                        switch(c){
                            case ' ':
                            case '\t':
                            case '\n':
                            case '[':
                            case ']':
                            case '(':
                            case ')':
                            case '{':
                            case '}':
                            case '\'':
                            case '"':
                            case '`':
                            case ',':
                            case ';':{
                                done = true;
                                break;
                            }
                            default:
                            ++m_index;
                        }
                    }
                    return view.substr(start,m_index - start);
                }
            }
        }
        return { };
    }

private:
    std::string m_input;
    size_t m_index { 0 };
    //zero zero webhost

};

class Reader{

};
