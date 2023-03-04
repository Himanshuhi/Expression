#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_EXPR_LENGTH 256

double evaluate(char *expr) {
    char *p;
    double left_operand, right_operand;
    char operator;
    
    // Evaluate expressions with parentheses first
    while ((p = strchr(expr, '(')) != NULL) {
        char *q = p + 1;
        int paren_count = 1;
        while (*q != '\0') {
            if (*q == '(') {
                paren_count++;
            } else if (*q == ')') {
                paren_count--;
                if (paren_count == 0) {
                    *q = '\0';
                    double result = evaluate(p + 1);
                    sprintf(p, "%.3f%s", result, q + 1);
                    break;
                }
            }
            q++;
        }
    }
    
    // Evaluate expressions with exponentiation next
    p = expr;
    while (*p != '\0') {
        if (*p == '^') {
            operator = *p;
            *p = '\0';
            left_operand = evaluate(expr);
            right_operand = evaluate(p + 1);
            return pow(left_operand, right_operand);
        }
        p++;
    }
    
    // Evaluate expressions with multiplication and division next
    p = expr;
    while (*p != '\0') {
        if (*p == '*' || *p == '/') {
            operator = *p;
            *p = '\0';
            left_operand = evaluate(expr);
            right_operand = evaluate(p + 1);
            switch (operator) {
                case '*':
                    return left_operand * right_operand;
                case '/':
                    return left_operand / right_operand;
            }
        }
        p++;
    }
    
    p = expr;
    while (*p != '\0') {
        if (*p == '+' || *p == '-') {
            operator = *p;
            *p = '\0';
            left_operand = evaluate(expr);
            right_operand = evaluate(p + 1);
            switch (operator) {
                case '+':
                    return left_operand + right_operand;
                case '-':
                    return left_operand - right_operand;
            }
        }
        p++;
    }
    
    return atof(expr);
}

int main() {
    char expr[MAX_EXPR_LENGTH];
    printf("Enter a math expression: ");
    fgets(expr, MAX_EXPR_LENGTH, stdin);
    expr[strcspn(expr, "\n")] = '\0'; // himanshu
    printf("Result: %.3f\n", evaluate(expr));
    return 0;
}
