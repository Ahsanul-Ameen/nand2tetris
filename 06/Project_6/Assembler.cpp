#include "Parser.hpp"
#include "Code.hpp"
#include "SymbolTable.hpp"

using std::ofstream;



int main(int argc, char** argv) {
	using namespace std;
	
	

	for (int i = 1; i < argc; ++i) {
		string path_string(argv[i]);
		string output_file = path_string.substr(0, path_string.find_last_of('.')) + ".hack";
		ofstream out(output_file);
		auto Log = [&](const string& message) {
			out << message << endl;
		};
		
		SymbolTable symbol_table;
		Parser pass_one(path_string);
		int pc = 0;
		
		// perfrom first pass
		while(pass_one.hasMoreCommands()) {
			pass_one.advance();
			//std::cout << pass_one.getCurrentToken() << std::endl;
			if(pass_one.commandType() == L_COMMAND) {
				symbol_table.addEntry(pass_one.symbol(), pc);
				//std::cout << "hello" << std::endl;
			} else ++pc;
		}
		
		pc = 0;
		Parser pass_two(path_string);
		
		// perform second pass
		while(pass_two.hasMoreCommands()) {
			pass_two.advance();
			if(pass_two.commandType() == A_COMMAND) {
				//std::cout << "A" << std::endl;
				string address = pass_two.symbol();
				if(!symbol_table.contains(address)) {
					static int local_variable = 16;
					symbol_table.addEntry(address, local_variable++);
				}
				string instruction = "0" + Code::addr(symbol_table.GetAddress(address));
				Log(instruction);
				++pc;
			} else if(pass_two.commandType() == C_COMMAND) {
				//std::cout << "C" << std::endl;
				string instruction = "111";
				instruction += Code::comp(pass_two.comp());
				instruction += Code::dest(pass_two.dest());
				instruction += Code::jump(pass_two.jump());
				Log(instruction);
				++pc;	
			} else {
				//std::cout << "L" << std::endl;
			}
		}
		
		// Colses output file
		out.close();
	}

	return 0;
}
