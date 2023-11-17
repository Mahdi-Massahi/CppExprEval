#include <iostream>
#include "exprtk.hpp"

// Functions defined at global scope
double ADD(double a, double b) {
    return a + b;
}

double SUB(double a, double b) {
    return a - b;
}

int main() {
    typedef double T;
    typedef exprtk::symbol_table<T> symbol_table_t;
    typedef exprtk::expression<T> expression_t;
    typedef exprtk::parser<T> parser_t;

    // Variables must be double to match ExprTk's default real type
    T X = 12.0;
    T Y = 21.0;

    // Define the SMA and CROSS functions, and add them to a symbol_table
    symbol_table_t symbol_table;
    symbol_table.add_variable("X", X);
    symbol_table.add_variable("Y", Y);
    symbol_table.add_function("ADD", ADD);
    symbol_table.add_function("SUB", SUB);

    // Define the expression
    std::string expression_string = "ADD(X, SUB(Y, 5))";
    expression_t expression;
    expression.register_symbol_table(symbol_table);

    // Parse the expression
    parser_t parser;
    if (!parser.compile(expression_string, expression)) {
        std::cerr << "Compilation error:" << std::endl;
        for (std::size_t i = 0; i < parser.error_count(); ++i) {
            typedef exprtk::parser_error::type error_t;
            error_t error = parser.get_error(i);
            std::cerr << "Error: " << error.diagnostic << std::endl;
        }
        return 1;
    }

    // Evaluate the expression
    T result = expression.value();

    std::cout << "The result of the expression is: " << result << std::endl;

    return 0;
}
