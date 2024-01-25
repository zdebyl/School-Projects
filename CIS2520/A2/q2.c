/*
Name: Zoe Debyl
Date: October 22nd 2022
Assignment: Assignment 2
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//struct
struct EquationValue {
	double value;
	struct EquationValue *next;
};

//push function
void push(struct EquationValue** top, double value) {
	//create new node
	struct EquationValue* newValue = (struct EquationValue*)malloc(sizeof(struct EquationValue));
	newValue->value = value;
	newValue->next = NULL;

	//push on stack
	newValue->next = *top;
	*top = newValue;
}

//pop function
double pop(struct EquationValue** top) {
	struct EquationValue* temp = *top;

	//remove item
	*top=(*top)->next;

	//return removed item
	double value = temp->value;

	return value;
}

//check if its operator
int checkOperator(char val) {
	if (val=='+' || val=='-' || val=='*' || val=='/') {
		return 1;
	} else {
		return 0;
	}
}

//check if its operand
int checkOperand(char val) {
	if (val>='0' && val<='9') {
		return 1;
	} else {
		return 0;
	}
}

//do operation
double doOperation(char operator, double operand1, double operand2) {
	double answer;

	if (operator == '+') {
		answer = operand1 + operand2;
	} else if (operator == '-') {
		answer = operand1 - operand2;
	} else if (operator == '*') {
		answer = operand1 * operand2;
	} else if (operator == '/') {
		answer = operand1 / operand2;
	}

	return answer;
}

int main(int argc, char* argv[]) {
	char postfix[100];
	int operator=0;
	int operand=0;
	double num;
	double operand1;
	double operand2;
	double answer;

	//create top
	struct EquationValue *top = (struct EquationValue*)malloc(sizeof(struct EquationValue));
	top->next = NULL;

	//get postfix equation**
	strcpy(postfix, argv[1]);

	//go through expression
	for (int i=0; i<strlen(postfix); i++) {
		operator = checkOperator(postfix[i]);
		operand = checkOperand(postfix[i]);

		//if its an operand push on stack
		if (operand==1) {
			num = postfix[i]-48;
			push(&top,num);

		//if its an operator, pop previous 2 operands and do operation
		} else if (operator==1) {
			operand2 = pop(&top);
			operand1 = pop(&top);
			answer = doOperation(postfix[i], operand1, operand2);
			push(&top,answer);
		}
	}

	//pop answer from stack and print to user
	answer = pop(&top);
	printf("The answer is %.2lf", answer);

	return 0;
}
