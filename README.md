# TaskFlow
Name: Mst Nayma 
Uni: mzn2002

TaskFlow is a programming language I’m designing to help automate tasks and workflows with simple, easy-to-read code. It’s built for users who need to set up things like task scheduling, data processing, or file management. The goal is to make it straightforward to manage these tasks by focusing on clear flow control and showing how different tasks depend on each other.

1. Token Types

Keywords:
Description: Words used for TaskFlow’s structures.
Tokens: task, run, every, if, fails, send, to
Pattern: Exact matches of the keywords.

Identifiers:
Description: Names for tasks and variables.
Pattern: [a-zA-Z_][a-zA-Z_0-9]*
Examples: backup_files, daily_backup

String Literals:
Description: Used to define file paths, messages, and email addresses.
Pattern: "[^"]*" (Matches any characters inside double quotes)
Examples: "/documents", "Backup failed!"

Operators:
Description: Symbols used for assignment and comparisons.
Tokens: :=, +, -, *, /, =, !=, >, <
Pattern: Exact matches of these symbols.

Delimiters:
Description: Braces, parentheses, colons, and commas for structuring the program.
Tokens: {, }, (, ), :, ,
Pattern: Exact matches of these symbols.

2. Developing a Scanning Algorithm
a. Pseudocode: 
state = START
while not end of input:
    current_char = get_next_char()
    if state == START:
        if current_char is a letter:
            state = IN_IDENTIFIER
            while current_char is a letter or digit:
                accumulate to form identifier
            output <IDENTIFIER, identifier>
            state = START
        elif current_char is a digit:
            state = IN_NUMBER
            while current_char is a digit:
                accumulate to form number
            output <INTLITERAL, number>
            state = START
        elif current_char is '"':
            state = IN_STRING
            while current_char is not '"':
                accumulate to form string
            output <STRINGLITERAL, string>
            state = START
        elif current_char is a keyword or operator:
            recognize and output <KEYWORD/OPERATOR, value>
            state = START
        elif current_char is invalid:
            raise lexical error: "Unexpected character!"

b. Finite automata
START: Initial state. If a character is a letter, transition to IN_IDENTIFIER. If it's a number, transition to IN_NUMBER. If it’s a " symbol, transition to IN_STRING.
IN_IDENTIFIER: Continue reading until encountering a non-alphabetic character. Output the identifier and return to START.
IN_NUMBER: Continue reading digits to form an integer literal. Output the integer and return to START.
IN_STRING: Continue reading until the closing " is found. Output the string literal and return to START.

c. Lexical Errors
If the scanner encounters an invalid character (e.g., an unexpected symbol), throw an error with details like the character and its position in the file. 
For example: "Unexpected character '!' at line 3, column 12."

3. 5 sample input programs 

Sample Input 1:  
task backup_files {
    source: "/documents"
    destination: "/backup"
}

<KEYWORD, task>
<IDENTIFIER, backup_files>
<OPERATOR, {>
<IDENTIFIER, source>
<OPERATOR, :>
<STRINGLITERAL, "/documents">
<IDENTIFIER, destination>
<OPERATOR, :>
<STRINGLITERAL, "/backup">
<OPERATOR, }>

Sample Input 2: 
if backup_files fails {
    send "Backup failed!" to email("admin@example.com")
}
<KEYWORD, if>
<IDENTIFIER, backup_files>
<KEYWORD, fails>
<OPERATOR, {>
<KEYWORD, send>
<STRINGLITERAL, "Backup failed!">
<KEYWORD, to>
<IDENTIFIER, email>
<OPERATOR, (>
<STRINGLITERAL, "admin@example.com">
<OPERATOR, )>
<OPERATOR, }>

Sample Input 3:
task incomplete_task {
    source: "/files"

Expected Error: Error: Missing closing '}' for task definition 'incomplete_task' at line 3.

Sample Input 4: 
task 123task {
    source: "/data"
}
Expected Error: Error: Invalid identifier '123task' at line 1. Identifiers must start with a letter.

Sample Input 5:
task math_task {
    result := 5 + 3
}
<KEYWORD, task>
<IDENTIFIER, math_task>
<OPERATOR, {>
<IDENTIFIER, result>
<OPERATOR, :=>
<INTLITERAL, 5>
<OPERATOR, +>
<INTLITERAL, 3>
<OPERATOR, }>

4. Shell Script
To run the Shell Script: 

Compile: 
g++ -std=c++11 -o taskflow_scanner scanner.cpp

Run the scanner again with your input file:
./taskflow_scanner input_program.tfl

OR 

To run shell script (run_scanner.sh): 
Open your terminal.
Navigate to where run_scanner.sh is located.
Make sure the script is executable. If you haven’t done this yet, run:
chmod +x run_scanner.sh
Run the script with input file. For example:
./run_scanner.sh input_program.tfl


Test for Error handling capabilities:
input file with unmatched quotes called invalid_program.tfl:

task quote_test {
    string_value = "This is a string
}

Run the script:
./run_scanner.sh unmatched_quotes.tfl
You should see an error message about unmatched quotes:
Error: Unmatched quote in string literal at line 2












