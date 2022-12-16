#include<iostream>
#include<string>
#include "Reader.hpp"
#include "linenoise.hpp"

std::string READ(std::string input){
    Tokenizer tokenizer { input };
    while(auto token = tokenizer.next()){
        std::cout << "[" << *token << "]\n";
    }
    return input;
}

std::string EVAL(std::string input){
    return input;
}

std::string PRINT(std::string input){
    return input;
}

std::string rep(std::string input){
    auto ast=READ(input);
    auto result=EVAL(ast);
    return PRINT(input);
}

int main(){
    const auto history_path= "history.txt";
    linenoise::LoadHistory(history_path);
    std::string input;
    for(;;){
        auto quit = linenoise::Readline("users> ", input);
        if(quit){
            break;
        }
        std::cout << rep(input) << std::endl;
        linenoise::AddHistory(input.c_str());
    }
    linenoise::SaveHistory(history_path);

    return 0;
}