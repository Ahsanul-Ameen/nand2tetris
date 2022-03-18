#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>	//#include <io.h>
#include <dirent.h>
#include <iostream>
#include <vector>
#include "JackTokenizer.h"
#include "CompilationEngine.h"


inline char separator()
{
	#ifdef _WIN32
	return '\\';
	#else
	return '/';
	#endif
}

// check if the path represents a file 1 / 0
int is_regular_file(const std::string& path) {
	struct stat path_stat;
	stat(path.c_str(), &path_stat);
	return S_ISREG(path_stat.st_mode);
}

// change file path with desired extention (ex: .cpp)
std::string file_to_file(std::string path_string, const std::string& dot_ext) {
	return path_string.substr(0, path_string.find_last_of('.')) + dot_ext;
}

// return a list of .jack file paths in a directory
std::vector<std::string> files_in_dir(std::string path_string, const std::string& dot_ext) {
	using namespace std;

	if (!path_string.empty() && path_string.back() != separator()) path_string.push_back(separator());
	DIR* dir;
	struct dirent* entry;
	vector<string> v;

	if ((dir = opendir(path_string.c_str())) != nullptr) {
		// Scanning directory contents looking for .jack files...
		while ((entry = readdir(dir)) != NULL) {
			string entry_name = entry->d_name;
			if (entry_name.find(dot_ext) != string::npos) {
				string file_path = path_string;
				file_path.append(entry_name); // path/fileName.jack
				v.push_back(file_path);  // ... and adding them to jack_files.
			}
		}
		closedir(dir);
		return v;
	} else {
		cerr << "Error opening directory." << endl;
		exit(-1);
	}
}


// do whatever you wan't to do with this file
void tokenize(std::string const& in_path, std::string const& out_path) {
	using namespace std;
	//cout << in << " to " << out << endl;
	ofstream out(out_path);
	JackTokenizer jack(in_path);

	out << "<tokens>" << endl;
	while (jack.hasMoreTokens()) {
		jack.advance();
		Token token = jack.tokenType();

		if (token == KEYWORD) {
			Keyword keyword = jack.keyWord();
			string key;
			for (const auto& entry: keyword_map) {
				if (entry.second == keyword) {
					key = entry.first;
					break;
				}
			}
			out << "<keyword> " << key << " </keyword>" << endl;
		}
		else if (token == SYMBOL) {
			string sym;
			sym.push_back(jack.symbol());
			if (sym == "<") sym = "&lt;";
			else if (sym == ">") sym = "&gt;";
			else if (sym == "&") sym = "&amp;";
			out << "<symbol> " << sym << " </symbol>" << endl;
		}
		else if (token == IDENTIFIER) {
			out << "<identifier> " << jack.identifier() << " </identifier>" << endl;
		}
		else if (token == INT_CONST) {
			out << "<integerConstant> " << jack.intVal() << " </integerConstant>" << endl;
		}
		else if (token == STRING_CONST) {
			out << "<stringConstant> " << jack.stringVal() << " </stringConstant>" << endl;
		}
		else {
			cout << "###ERROR in generating T.xml file" << endl;
			system("pause");
		}
		//cout << jack.tokenType() << endl;
	}
	out << "</tokens>" << endl;
	//cin.get();
	out.close();
}

int main(int argc, char** argv) {
	using namespace std;

	for (int i = 1; i < argc; ++i) {
		string path_string(argv[i]);
		string output_file;
		if (!is_regular_file(path_string)) {
			auto jack_files = files_in_dir(path_string, ".jack");	 // list all .jack files
			for (const string& input_file : jack_files) {
				output_file = file_to_file(input_file, "T.xml");
				tokenize(input_file, output_file);
				output_file = file_to_file(input_file, ".xml");
				//	initialize a CompilationEngine
				CompilationEngine compiler(input_file, output_file);
				// call compileClass
				compiler.CompileClass();
			}

		} else if (is_regular_file(path_string) == 1) {
			output_file = file_to_file(path_string, "T.xml");
			tokenize(path_string, output_file);
			output_file = file_to_file(path_string, ".xml");
			//	initialize a CompilationEngine
			CompilationEngine compiler(path_string, output_file);
			// call compileClass
			compiler.CompileClass();
		}
	}

	return 0;
}
