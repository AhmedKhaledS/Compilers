//
// Created by ahmed on 4/24/18.
//
#include <iostream>
#include "ParserStack.h"
#include "../lexical_analyzer/LexicalController.h"

//void ParserStack::ParserStack(ParserTable table ,
//                              std::string initial_state)
//{
//    this->predictive_parse_table = table ;
//    this->input_parsing_stack.push("$");
//    this->input_parsing_stack.push(initial_state);
//}
//
//void ParserStack::run_string_matcher()
//{
//    Lexical_controller z ;
//    std::string temp = z.next_token();
//    while(input_parsing_stack.top() != "$" && temp != ""){
//        match_next(temp);
//        temp = z.next_token();
//    }
//    if(input_parsing_stack.top() != "$" &&  temp == ""){
//        error_logger(Reject);
//    }
//}
//
//void ParserStack::match_next(std::string st)
//{
//    if(st == input_parsing_stack.top()){
//        input_parsing_stack.pop();
//        return ;
//    } else {
//        std::string temp = predictive_parse_table.fetch_from_parse_table(input_parsing_stack.pop(),st);
//        if(temp == "Synch"){
//            error_logger(Synch);
//        } else if (temp == NULL) {
//            error_logger(Panic);
//        } else {
//            input_parsing_stack.push(temp);
//        }
//    }
//}
//
//void ParserStack::error_logger(ERROR_ROUTINE err)
//{
//    switch (err){
//        case Synch :
//            //Synch routine
//            std::cout << "Performing Synchronised recovery" << endl;
//            break;
//        case Panic :
//            //Panic routine
//            std::cout << "Performing Panicked recovery" << endl;
//            break;
//        case Correct :
//            //Correct routine
//            std::cout << "Missing Token :" << endl;
//            break;
//        case Reject :
//            //Reject routine
//            std::cout << "Aborting Program" << endl;
//            break;
//        default:
//            std::cout << "Un-identified Error" << endl;
//
//    }
//}

