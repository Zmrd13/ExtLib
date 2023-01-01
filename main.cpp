#include <fstream>
#include <iostream>
#include <stdio.h>
#include <utility>
#include <vector>

namespace ext {
    class Exception:public std::exception{
    public:
        explicit Exception(const char* message)
            : msg_(message) {}
        explicit Exception(std::string  message)
            : msg_(std::move(message)) {}
        virtual const char* what() const noexcept {
            return msg_.c_str();
        }
        virtual ~Exception() noexcept {}
        const std::string msg_;
    };
    enum{
        SINGLE_LINE [[maybe_unused]] =0x01,
        MULTILINE [[maybe_unused]]=0x02,
        NO_FORMAT [[maybe_unused]]=0x03
    };
    class FileInterpeter {
    private:
        std::streampos position;
        bool opened=false;
        std::string path;
        uint32_t saved_size = 0;
        uint16_t sections = 0;
        std::ifstream file;
        int type=0;
        int processSingleLineInt(const std::string &param){
            std::string line;
            position=file.tellg();
            file.seekg(file.beg);
            while (std::getline(file, line))
            {
              if(line.contains(param)){
                  line.erase(0,param.size()+1);
                //  std::cout<<line<<std::endl;
                  file.seekg(position);
                  return std::stoi(line);
              }
            }
            file.seekg(position);
            return 0;
        }
        std::string processSingleLineString(const std::string &param){
            std::string line;
            while (std::getline(file, line))
            {
              if(line.contains(param)){
                  line.erase(0,param.size()+1);

                  return line;
              }
            }
            return {};
        }
    public:
        explicit FileInterpeter(const std::string &pathToFile,int type=NO_FORMAT) : path(pathToFile),type(type) {
            if(!pathToFile.ends_with(".inf")){
              throw Exception("Wrong extension of file");

            }
            this->saved_size=0;
            this->opened=false;
            file.open(pathToFile);
            if (!file.is_open()) {
              throw Exception("File is not opened");
                return;
            }
            else{
                opened=true;
            }
        }
        uint32_t size(){
            if(!opened){
                return 0;
            }
            if(saved_size!=0){
                std::cout<<"Saved\n";
                return saved_size;
            }
            else{
                std::cout<<"New\n";
                position=file.tellg();
               file.seekg(0,std::ios::end);
               saved_size=file.tellg();
               file.seekg(position);
               return saved_size;
            }
        }
        int findParamInt(const std::string &param){
            switch(type){
               case NO_FORMAT:
                   std::cerr<<"NO FORMAT\n";break;
            case MULTILINE:
               std::cerr<<"MULTLINE\n";break;
            case SINGLE_LINE:
                return processSingleLineInt(param);

        }}
        std::string findParamString(const std::string &param){
            switch(type){
                case NO_FORMAT:
                    std::cerr<<"NO FORMAT\n";break;
                case MULTILINE:
                    std::cerr<<"MULTLINE\n";break;
                case SINGLE_LINE:
                    return processSingleLineString(param);

            }
        }

    };
} // namespace ext
using namespace std;

int main() {
    ext::FileInterpeter test("1.inf",ext::SINGLE_LINE);
  //  cout<<test.size();
   // cout<<test.size();
    cout<<test.findParamInt("qw")<<endl;
    cout<<test.findParamInt("qw")<<endl;
    cout<<test.findParamString("tr")<<endl;
    int tempVar=test.findParamInt("qw");
    cout<<"\n"<<tempVar;
}
