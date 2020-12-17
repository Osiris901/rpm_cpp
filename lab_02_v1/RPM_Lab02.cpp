#include <iostream>
#include <string>
#include <stack>
#include <queue>

using namespace std;

bool in_between(int n, int a, int b) {
  return (n>=a) && (n<=b); 
}

int get_priority(std::string op) {
  switch (op[0]) {
    case '+': return 0; break;
    case '-': return 1; break;
    case '*': return 2; break;
    case '/': return 3; break;
    default: return -1;
  }
}

auto parse (const string& str) {
  queue <string> output;
  stack <string> operation;
  string number = "";
  for(auto c : str) {
    string op = "";
    if(in_between(c-'0', 0, 9)) number += c;
    else if(!number.empty()) {
      output.push(number);
      number = "";
    }
    if (c == ' ') continue;    
    op += c;    
    if (c == '+' || c == '-' || c == '*' || c == '/') {
      while(!operation.empty() && (operation.top() != "(") && (get_priority(op) <=    get_priority(operation.top()))) {
        output.push(operation.top());
        operation.pop();
      }
      operation.push(op);
    } else if (c == '(') {
      operation.push(op);
    } else if (c == ')') {
      while (operation.top() != "(") {
        output.push(operation.top());
        operation.pop();
      }
      operation.pop();
    }
  }
  if (!number.empty()) output.push(number);
  while(!operation.empty()) {
    output.push(operation.top());
    operation.pop();
  }
  return output;
}

int main() {
  string input = "";
  string output = "";
  getline(cin, input);
  auto result = parse(input);
  while(!result.empty()) {
    std::cout << result.front() << " ";
    result.pop();
  }
  std::cout << '\n';
  return 0;
}
