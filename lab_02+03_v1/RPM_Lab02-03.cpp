#include <iostream>
#include <stack>
#include <stdexcept>
#include <string>
#include <sstream>

using namespace std;

stack<string> split(const string &s, char delim) {
  stringstream ss(s);
  string item;
  stack<string> elems;
  while (getline(ss, item, delim)) {
    elems.push(move(item));
  }
  return elems;
}

double eval_num(string str) {
  //std::cout << "[DEBUG] Evaluating: " << str << std::endl;
  double num = 0;
  for(auto c : str) {
    num = num*10 + c - '0';
  }
  return num;
}

double eval_expr(stack <string> &expr) {
  string top = expr.top();
  expr.pop();
  if (isdigit(top[0])) return eval_num(top);
  else {
    double a = eval_expr(expr);
    double b = eval_expr(expr);
    //std::cout << "[DEBUG] Evaluating: " << b << top[0] << a << std::endl;
    switch(top[0]) {
      case '+':
        return a + b;
      break;
      case '-':
        return b - a;
      break;
      case '*':        
        return a * b;
      break;
      case '/':
        if (a == 0) throw invalid_argument("Division by zero");
        return b / a;
      break;
      default:
        throw invalid_argument("Unable to process the expression: " + top);
    }
  }
  return 0;
}

double evaluate(string str) {
  stack<string> lexems = split(str, ' ');
  return eval_expr(lexems);  
}

int main() {
  string input = "";
  getline(cin, input);
  
  double ans = 0;
  try {
    ans = evaluate(input);
    cout << "Result: " << ans << endl;
  } catch (invalid_argument) {
    cout << "The entered expression contains an error." << endl;
  }
  return 0;
}
