/*
Name: Zoe Debyl
ID: 1186610
Date: November 4th 2022
Assignment: Assignment 3
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//struct for converting
struct Operands {
	char value;
	struct Operands *next;
};

//struct for calculating
struct EquationValue {
	double value;
	struct EquationValue *next;
};

//push function
void push(struct Operands** top, char value) {
	//create new node
	struct Operands* newValue = (struct Operands*)malloc(sizeof(struct Operands));
	newValue->value = value;
	newValue->next = NULL;

	//push on stack
	newValue->next = *top;
	*top = newValue;
}

//pop function
char pop(struct Operands** top) {
	struct Operands* temp = *top;

	//remove item
	*top=(*top)->next;

	//return removed item
	char value = temp->value;

	return value;
}

//is empty function
int isEmpty(struct Operands* top) {
	//returns 1 if empty, else returns 0
	if (top==NULL) {
		return 1;
	}
	else {
		return 0;
	}
}

//peek function
int peek(struct Operands* top) {
	return top->value;
}

//push function for doubles
void pushDouble(struct EquationValue** top, double value) {
	//create new node
	struct EquationValue* newValue = (struct EquationValue*)malloc(sizeof(struct EquationValue));
	newValue->value = value;
	newValue->next = NULL;

	//push on stack
	newValue->next = *top;
	*top = newValue;
}

//pop function for doubles
double popDouble(struct EquationValue** top) {
	struct EquationValue* temp = *top;

	//remove item
	*top=(*top)->next;

	//return removed item
	double value = temp->value;

	return value;
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
		if (operand2==0) {
			answer=-9999;
		} else {
			answer = operand1 / operand2;
		}
	}

	return answer;
}

//display tree
void convertToTree(char expression[]) {
	char left[100];
	char right[100];
	int i;
	int l;
	int numParanthesis=0;
	int check=0;
	char operator;

	//find middle operator
	if (expression[1]!='(') {
		i=1;

		while (expression[i]!='+' && expression[i]!='-' && expression[i]!='*' && expression[i]!='/') {
			i++;
		}
	}
	else {
		i=1;

		while (check==0) {
		if (expression[i]=='(') {
			numParanthesis++;
		}
		else if (expression[i]==')') {
			numParanthesis--;
		}

		if (numParanthesis==0) {
			check = 1;
		}
		i++;
		}
	}
	
	//get operator
	operator=expression[i];

	//TEST
	printf("operator: %c\n", operator);

	//get left and right side of expression
	l=0;
	for (int j=1; j<i; j++) {
		left[l] = expression[j];
		l++;
	}
	left[l]='\0';

	l=0;
	for (int k=i+1; k<strlen(expression)-1; k++) {
		right[l] = expression[k];
		l++;
	}
	right[l]='\0';
	
	//TEST
	printf("left: %s\n", left);
	printf("right: %s\n", right);

	//check if it still needs to be split and call function if it does
	if (left[0] == '(') {
		convertToTree(left);
	}

	if (right[0] == '(') {
		convertToTree(right);
	}

}

int main(int argc, char* argv[]) {
	char expression[200];
	char inorder[200];
	char postorder[200];
	char preorder[200];
	char temp[200];
	int l;
	int position;
	int userChoice=0;
	double x[50];
	int varNum=0;
	char varUpdate[3];
	double numUpdate;
	char strNum[5];
	double num;
	double operand1;
	double operand2;
	char *endptr;
	double answer;

	//get expression
	strcpy(expression, argv[1]);

	//get variables
	for (int i=0; i<strlen(expression);i++) {
		if (expression[i]=='x') {
			varNum=expression[i+1]-48;
			x[varNum] = 0.00;
		}
	}

	//print menu
	while (userChoice!=7) {
		do {
			printf("1. Display\n");
			printf("2. Preorder\n");
			printf("3. Inorder\n");
			printf("4. Postorder\n");
			printf("5. Update\n");
			printf("6. Calculate\n");
			printf("7. Exit\n");
			printf("\nEnter what you would like to do: ");
			scanf("%d",&userChoice);

			//check for valid input
			if (userChoice<1 || userChoice>7) {
				printf("Invalid choice. Please try again.\n");
			}
		}
		while (userChoice<1 || userChoice>7);

		//create stack
		struct Operands *top = (struct Operands*)malloc(sizeof(struct Operands));
		top->value = 'd';
		top->next = NULL;
		
		//perform users choice
		switch(userChoice) {
			//display
			case 1:
				convertToTree(expression);

				printf("\nVariable Values: \n");
				for (int i=1;i<=varNum;i++) {
					printf("x%d = %.2lf\n", i, x[i]);
				}
				break;

			//preorder
			case 2:
				//get rid of outermost brackets
				l=0;
				for (int i=1; i<strlen(expression)-1;i++) {
					inorder[l]=expression[i];
					l++;
				}
				inorder[l]='\0';

				//reverse expression
				l=strlen(inorder)-1;
				temp[strlen(inorder)]='\0';

				for (int i=0; i<strlen(inorder);i++) {
					//change direction of paranthesis
					if (inorder[i]=='(') {
						temp[l]=')';
						l--;
					}
					else if (inorder[i]==')') {
						temp[l]='(';
						l--;
					}
					//if variable
					else if (inorder[i]=='x') {
						temp[l-1]=inorder[i];
						i++;
						temp[l]=inorder[i];
						l=l-2;
					}
					//if number
					else if(inorder[i]>='0' && inorder[i]<='9') {
						temp[l-3]=inorder[i];
						i++;
						temp[l-2]=inorder[i];
						i++;
						temp[l-1]=inorder[i];
						i++;
						temp[l]=inorder[i];
						l=l-4;
					}
					else {
						temp[l]=inorder[i];
						l--;
					}
				}
				
				strcpy(inorder,temp);

				//initialize variable to keep track of position in postorder expression
				position=0;

				//convert to postorder
				for (int i=0; i<strlen(inorder); i++) {
					//if variable
					if (inorder[i]=='x') {
						postorder[position] = inorder[i];
						position++;
						i++;
						postorder[position] = inorder[i];
						position++;
					}
					//if number
					else if ((inorder[i]>='0' && inorder[i]<='9') || inorder[i]=='.') {
						postorder[position] = inorder[i];
						position++;
					}
					//if operator
					else if (inorder[i]=='+' || inorder[i]=='-' || inorder[i]=='*' || inorder[i]=='/') {
						while(peek(top)!='d' && peek(top)!='(') {
							postorder[position] = pop(&top);
							position++;
						}
						push(&top,inorder[i]);
					}
					//if opening paranthesis
					else if (inorder[i]=='(') {
						push(&top,inorder[i]);
					}
					//closing paranthesis
					else if (inorder[i]==')') {
						while(peek(top)!='d' && peek(top)!='(') {
							postorder[position] = pop(&top);
							position++;
						}
						pop(&top);
					}
				}
				
				//get everything left from stack
				while(peek(top)!='d') {
					postorder[position] = pop(&top);
					position++;
				}

				//set end of string to null
				postorder[position] = '\0';

				//reverse expression
				l=strlen(postorder)-1;
				preorder[strlen(postorder)]='\0';

				for (int i=0; i<strlen(postorder);i++) {
					//if variable
					if (postorder[i]=='x') {
						preorder[l-1]=postorder[i];
						i++;
						preorder[l]=postorder[i];
						l=l-2;
					} 
					//if number
					else if(postorder[i]>='0' && postorder[i]<='9') {
						preorder[l-3]=postorder[i];
						i++;
						preorder[l-2]=postorder[i];
						i++;
						preorder[l-1]=postorder[i];
						i++;
						preorder[l]=postorder[i];
						l=l-4;
					} else {
						preorder[l]=postorder[i];
						l--;
					}	
				}

				printf("Preorder expression: %s\n\n",preorder);
				

				break;

			//inorder
			case 3:
				//print inorder expression
				printf("Inorder expression: %s\n\n",expression);
				
				break;

			//postorder
			case 4:
				//get rid of outermost brackets
				l=0;
				for (int i=1; i<strlen(expression)-1;i++) {
					inorder[l]=expression[i];
					l++;
				}
				inorder[l]='\0';

				//initialize variable to keep track of position in postorder expression
				position=0;

				//convert to postorder
				for (int i=0; i<strlen(inorder); i++) {
					//if variable
					if (inorder[i]=='x') {
						postorder[position] = inorder[i];
						position++;
						i++;
						postorder[position] = inorder[i];
						position++;
					}
					//if number
					else if ((inorder[i]>='0' && inorder[i]<='9') || inorder[i]=='.') {
						postorder[position] = inorder[i];
						position++;
					}
					//if operator
					else if (inorder[i]=='+' || inorder[i]=='-' || inorder[i]=='*' || inorder[i]=='/') {
						while(peek(top)!='d' && peek(top)!='(') {
							postorder[position] = pop(&top);
							position++;
						}
						push(&top,inorder[i]);
					}
					//if opening paranthesis
					else if (inorder[i]=='(') {
						push(&top,inorder[i]);
					}
					//closing paranthesis
					else if (inorder[i]==')') {
						while(peek(top)!='d' && peek(top)!='(') {
							postorder[position] = pop(&top);
							position++;
						}
						pop(&top);
					}
				}
				
				//get everything left from stack
				while(peek(top)!='d') {
					postorder[position] = pop(&top);
					position++;
				}

				//set end of string to null
				postorder[position] = '\0';

				//print postorder
				printf("Postorder expression: %s\n\n",postorder);

				break;

			//update
			case 5:
				printf("Enter variable to update: ");
				scanf("%s",varUpdate);
				printf("Enter updated value: ");
				scanf("%lf", &numUpdate);
				printf("\n");

				x[varUpdate[1]-48] = numUpdate;

				break;

			//calculate
			case 6:
				//convert to postfix
				//get rid of outermost brackets
				l=0;
				for (int i=1; i<strlen(expression)-1;i++) {
					inorder[l]=expression[i];
					l++;
				}
				inorder[l]='\0';

				//initialize variable to keep track of position in postorder expression
				position=0;

				//convert to postorder
				for (int i=0; i<strlen(inorder); i++) {
					//if variable
					if (inorder[i]=='x') {
						postorder[position] = inorder[i];
						position++;
						i++;
						postorder[position] = inorder[i];
						position++;
					}
					//if number
					else if ((inorder[i]>='0' && inorder[i]<='9') || inorder[i]=='.') {
						postorder[position] = inorder[i];
						position++;
					}
					//if operator
					else if (inorder[i]=='+' || inorder[i]=='-' || inorder[i]=='*' || inorder[i]=='/') {
						while(peek(top)!='d' && peek(top)!='(') {
							postorder[position] = pop(&top);
							position++;
						}
						push(&top,inorder[i]);
					}
					//if opening paranthesis
					else if (inorder[i]=='(') {
						push(&top,inorder[i]);
					}
					//closing paranthesis
					else if (inorder[i]==')') {
						while(peek(top)!='d' && peek(top)!='(') {
							postorder[position] = pop(&top);
							position++;
						}
						pop(&top);
					}
				}
				
				//get everything left from stack
				while(peek(top)!='d') {
					postorder[position] = pop(&top);
					position++;
				}

				//set end of string to null
				postorder[position] = '\0';

				//calculate expression
				//create top
				struct EquationValue *top2 = (struct EquationValue*)malloc(sizeof(struct EquationValue));
				top2->next = NULL;

				//go through expression
				for (int i=0; i<strlen(postorder); i++) {
					//if its a variable, get value and push on stack
					if (postorder[i]=='x') {
						varNum = postorder[i+1]-48;
						num = x[varNum];
						pushDouble(&top2,num);

						i++;
					}
					//if its an operand push on stack
					else if ((postorder[i]>='0' && postorder[i]<='9')) {
						for (int j=0;j<4;j++) {
							strNum[j] = postorder[i+j];
						}
						num = strtod(strNum,&endptr);
						pushDouble(&top2,num);

						i=i+3;

					}
					//if its an operator, pop previous 2 operands and do operation
					else if (postorder[i]=='+' || postorder[i]=='-' || postorder[i]=='*' || postorder[i]=='/') {
						operand2 = popDouble(&top2);
						operand1 = popDouble(&top2);
						answer = doOperation(postorder[i], operand1, operand2);
						//check for division by 0
						if (answer == -9999) {
							printf("Invalid. Division by 0.\n\n");
						}
						pushDouble(&top2,answer);
					}
				}

				//pop answer from stack and print to user
				if (answer != -9999) {
					answer = popDouble(&top2);
					printf("The answer is: %.2lf\n\n", answer);
				}

				break;

			//exit
			case 7:
				break;

			default:
				break;
			
		}
	}
	

	return 0;
}