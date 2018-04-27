//
// Created by ahmed on 27/04/18.
//

#include <iostream>
#include "MainController.h"
#include "parser/ParserController.h"


MainController::MainController()
{

}
void MainController::run()
{
    Lexical_controller l;
    l.run_("./lexical_tests/test.txt", "./lexical_tests/test_1.txt");
    ParserController p;
    p.set_lexical_controller(&l);
    p.run_parser("./test_cases/main_grammar.txt");
}
