Name: Zoe Debyl
ID: 1186610
Assignment: Assignment 3 (original)


To run Q1:
make
./q1 'expression'

expression requirements:
- fully parenthesized
- numbers are in the format #.##
- variables are in the form x1,x2,...
- expression is placed within single quotation marks


Sample Output (Q1):
./q1 '(((x1+5.12)*(x2-7.68))/x3)'

1. Display  
2. Preorder 
3. Inorder  
4. Postorder
5. Update   
6. Calculate
7. Exit     

Enter what you would like to do: 1
operator: /
left: ((x1+5.12)*(x2-7.68))
right: x3
operator: *
left: (x1+5.12)
right: (x2-7.68)
operator: +
left: x1
right: 5.12
operator: -
left: x2
right: 7.68

Variable Values:
x1 = 0.00
x2 = 0.00
x3 = 0.00
1. Display
2. Preorder
3. Inorder
4. Postorder
5. Update
6. Calculate
7. Exit

Enter what you would like to do: 2
Preorder expression: /*+x15.12-x27.68x3

1. Display
2. Preorder
3. Inorder
4. Postorder
5. Update
6. Calculate
7. Exit

Enter what you would like to do: 3
Inorder expression: (((x1+5.12)*(x2-7.68))/x3)

1. Display
2. Preorder
3. Inorder
4. Postorder
5. Update
6. Calculate
7. Exit

Enter what you would like to do: 4
Postorder expression: x15.12+x27.68-*x3/

1. Display
2. Preorder
3. Inorder
4. Postorder
5. Update
6. Calculate
7. Exit

Enter what you would like to do: 5
Enter variable to update: x3
Enter updated value: 1

1. Display
2. Preorder
3. Inorder
4. Postorder
5. Update
6. Calculate
7. Exit

Enter what you would like to do: 6
The answer is: -39.32

1. Display
2. Preorder
3. Inorder
4. Postorder
5. Update
6. Calculate
7. Exit

Enter what you would like to do: 7