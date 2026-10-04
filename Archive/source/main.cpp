#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>
#include <variant>
#include <vector>

using namespace std;

struct Argument {
        string                                     name;
        variant<std::monostate, bool, int, string> value;
        string                                     type;

        Argument(const string& name, const variant<std::monostate, bool, int, string>& value, const string& type) : name(name), value(value), type(type) {}
};

class ArgumentParser {
    public:
        void parse(int argc, char* argv[]) {
            unordered_set<string> seen;
            for(int i = 1; i < argc; ++i) {
                string arg = argv[ i ];

                if(arg.size() < 2 || arg[ 0 ] != '-') {
                    cerr << "Error: Invalid argument '" << arg << "'." << endl;
                    continue;
                }
                if(!seen.insert(arg).second) {
                    cerr << "Error: Duplicate argument '" << arg << "'." << endl;
                    continue;
                }

                string val;
                if(i + 1 < argc && string(argv[ i + 1 ]).rfind("-", 0) != 0) { val = argv[ ++i ]; }

                arguments.emplace_back(createArgument(arg, val));
            }
        }

        void printArguments() const {
            cout << "Stored Arguments:" << endl;
            for(const auto& a : arguments) {
                cout << a.name << " : ";
                if(holds_alternative<std::monostate>(a.value)) {
                    cout << "null";
                } else if(holds_alternative<bool>(a.value)) {
                    cout << (get<bool>(a.value) ? "true" : "false");
                } else if(holds_alternative<int>(a.value)) {
                    cout << get<int>(a.value);
                } else /* string */ {
                    cout << get<string>(a.value);
                }
                cout << "    (type: " << a.type << ")" << endl;
            }
        }

    private:
        vector<Argument> arguments;

        Argument createArgument(const string& name, const string& val) {
            if(val.empty() || val == "null") { return {name, std::monostate{}, "Null"}; }
            if(val == "true" || val == "false") { return {name, (val == "true"), "Boolean"}; }
            if(all_of(val.begin(), val.end(), ::isdigit)) { return {name, stoi(val), "Integer"}; }
            return {name, val, "String"};
        }
};

int main(int argc, char* argv[]) {
    ArgumentParser parser;
    parser.parse(argc, argv);
    parser.printArguments();
    return 0;
}
