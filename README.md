# 🖥️ TINY42 Compiler

## 📖 **Description**  
TINY42 Compiler is a C++-based compiler that compiles a dialect of the Tiny Programming language.Tiny42 programming language is a simple, procedural language designed for learning compiler design. Basically
it translates TINY42 source code into executable c++ code, supporting variables, input/output, loops. arithmetic/string operations. This project demonstrates lexical analysis, parsing, and code generation.

## 💻 **Features**  
- **Simple Syntax**: Write programs with intuitive commands like `PRINT`, `INPUT`, `LET`, and `WHILE`.  
- **Variable Support**: Handles numeric (`NUM`) and string (`STR`) variables (e.g., `LET NUM a = 0`).  
- **Input/Output**: Reads user input (`INPUT`) and displays output (`PRINT`) with newline support (`NL`).  
- **Control Flow**: Iterates with `WHILE` loops (e.g., `WHILE nums > 0 REPEAT ... ENDWHILE`).  
- **Operations**: Supports arithmetic (e.g., `a + b`) and string concatenation (e.g., `greet + name`).  
- **Code Generation**: Outputs clean C++ code that can be compiled and run.
  
---

### Example Program  
Calculates Fibonacci numbers and greets the user:  
```tiny42
PRINT "How many Fibonacci numbers do you want? "
INPUT NUM nums

PRINT "What's your name? "
INPUT STR name

LET NUM a = 0
LET NUM b = 1
LET NUM c = 0
WHILE nums > 0 REPEAT
    PRINT a
    LET c = a + b
    LET a = b
    LET b = c
    LET nums = nums - 1
ENDWHILE

PRINT NL
LET STR greet = "Hello "
PRINT greet + name NL
```

**Output** (for input `3` and `Alice`):  
```
How many Fibonacci numbers do you want? 3
What's your name? Alice
0
1
1

Hello Alice
```

## 🚀 **How to Build and Run**  

📄 **Prerequisites**  
- C++11-compatible compiler (e.g., `g++`, Clang).  
- Make (optional, for build automation).  

🦵 **Steps**  
1. Clone this repository:  
   ```bash
   git clone https://github.com/thom151/tiny42
   cd tiny42
   ```
2. Build the compiler:  
   ```bash
   g++ -o tiny42 tiny42.cpp
   ```
3. Write a TINY42 program in a `.tiny` file (e.g., `fibonacci.tiny`).  
4. Compile the program:  
   ```bash
   ./tiny42 fibonacci.tiny
   ```
5. Compile and run the generated C++ code:  
   ```bash
   g++ -o out out.cpp
   ./out
   ```

🎮 **Usage**  
- Create a TINY42 program in a `.tiny` file.  
- Run the compiler to generate `out.cpp`.  
- Compile and execute the generated C++ code as shown above.  

🎥 **Example Output**  
Input file (`fibonacci.tiny`) generates `out.cpp`, producing the Fibonacci sequence and a greeting (see example above).

---

## ✍️ **Contributing**  
- **Bug Reports**: Found an issue? Open an issue with steps to reproduce it.  
- **Feature Requests**: Suggest new language features or compiler improvements via issues.  
- **Code Contributions**:  
  1. Fork the repository.  
  2. Create a branch (`git checkout -b feature-name`).  
  3. Commit changes (`git commit -m "Add feature"`).  
  4. Push and open a pull request to the `main` branch.  
- **Documentation**: Improve this README or add example programs.  
- **Feedback**: Share ideas to enhance the compiler or language.  

## 🤝 **Need Help?**  
- Open an issue in the repository.  
- Contact me at [thomassantos2003@gmail.com](mailto:thomassantos2003@gmail.com).  

## 🙏 **Acknowledgments**  
- Inspired by Austin Henley's [Teeny Tiny Compiler tutorial](https://austinhenley.com/blog/teenytinycompiler1.html).  
- Thanks to the C++ community for robust tools and libraries.  
- Special nod to the open-source community for sharing knowledge on lexical analysis and code generation.  

## 📜 **License**  
This project is licensed under the MIT License. Feel free to use, modify, and distribute it as you wish.

Enjoy compiling with TINY42! 🎉
