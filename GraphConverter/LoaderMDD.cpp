#include "stadx.h"
#include "LoaderMDD.h"
using namespace std;

std::string filePrefix = ""; //TODO: add fileprefix

const std::vector<std::string> LoaderMDD::header = {"participant_id","sex","age","group"};

bool LoaderMDD::checkHeader(const std::string &line)
{
    int count = 0;
    for(size_t plast = 0,p = line.find('\t');p!=std::string::npos;){
        if(line.substr(plast,p-plast) != header[count]){
            return false;
        }
        plast = p+1;
        p = line.find('\t',plast);
        ++count;
    }
    return true;
}

std::vector<Subject> LoaderMDD::loadValidList(const std::string &fn)
{
 
    std::string filename(fn);
    vector<Subject> res;
    
    if(filename.find("participants")==std::string::npos){
        size_t pos_slash = filename.find_last_of("/\\");
        if(pos_slash==filename.length()-1){
            filename+="participants.tsv";
        }else{
            filename+="/participants.tsv";
        } //TODO: double check that this works and makes sense for file structure
    }
    
    ifstream fin(filename);
    
    if(!fin){
        cerr<<"Cannot open phenotype file with given parameter: "<<endl;
        throw invalid_argument("cannot open valid list with given parameter");
    }
    
    std::string line;
    getline(fin,line,'\n');
    if(!checkHeader(line)){
        cerr<<"Header of file'" <<fn << "' is not correct!" <<endl;
        throw invalid_argument("file header does not match that of the specific dataset");
    }
    
    size_t limit = nSubject > 0 ? nSubject : numeric_limits<size_t>::max();
    
    while(getline(fin,line,'\n'))
    {
        strins sid;
        int type;
        tie(sid,type) = parsePhenotypeLine(line);
        
        res.push_back(Subject{sid,type});
        
        if(res.size() >= limit){
            break;
        }
    }
    fin.close();
    return res;
}

std::pair<std::string,int> LoaderMDD::parsePhenotypeLine(const std::string &line, const int nSubject)
{
    static const int POS_ID = 0;
    static const int POS_DX = 3;
    
    std::string id;
    int dx;
    
    size_t plast = 0;
    size_t p = line.find('\t');
    
    int count = 0;
    while(p!=std::string::npos)
    {
        if(count == POS_ID){
            id = line.substr(plast,p-plast);
        }else if(count == POS_DX){
            std::string entry = line.substr(plast,p-plast);
            if(entry.find("control")==std::string::npos){ //diagnosis turned into int. 0==control 1==positive.
                dx = 1;
            }else{
                dx = 0;
            }
        }
        
        plast = p+1;
        p = line.find('\t',plast);
        ++count;
    }
    return make_pair(std::move(id),dx);//NOTE: Assumes quality control. Dataset gives no information.
}