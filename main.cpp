#include <fstream>
#include <iostream>
#include <stdio.h>
#include <vector>

namespace ext {
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
            while (std::getline(file, line))
            {
              if(line.contains(param)){
                  line.erase(0,param.size()+1);
                //  std::cout<<line<<std::endl;
                  return std::stoi(line);
              }
            }
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
            return 0;
        }
    public:
        explicit FileInterpeter(const std::string &pathToFile,int type=NO_FORMAT) : path(pathToFile),type(type) {
            this->saved_size=0;
            this->opened=false;
            file.open(pathToFile);
            if (!file.is_open()) {
                std::cerr << "File is not opened!\n";
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
    ext::FileInterpeter test("1.txt",ext::SINGLE_LINE);
  //  cout<<test.size();
   // cout<<test.size();
    cout<<test.findParamInt("qw");
    cout<<test.findParamString("tr");
}
