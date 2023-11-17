#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
using namespace std;

class tag{
    public:
        tag();
        void setName(string n);
        void setAttributes(string a);
        void setValues(string v);
        void setTags(tag t);
        void setEnd();
        string getName();
        vector<string> getAttributes();
        string getAttribute(int i);
        string getValues(int i);
        vector<tag> getTags();
        bool getEnd();
        friend istream& operator>>(istream& input, tag& t);
        
    private:
        string name;
        vector<string> attributes;
        vector<string> values;
        vector<tag> tags;
        bool end;
};

tag::tag() {end = false;}
void tag::setName(string n) {name = n;}
void tag::setAttributes(string a) {attributes.push_back(a);}
void tag::setValues(string v) {values.push_back(v);}
void tag::setTags(tag t) {tags.push_back(t);}
void tag::setEnd() {end = true;}
string tag::getName() {return name;}
vector<string> tag::getAttributes() {return attributes;}
string tag::getAttribute(int i) {return attributes[i];}
string tag::getValues(int i) {return values[i];}
vector<tag> tag::getTags() {return tags;}
bool tag::getEnd() {return end;}
istream& operator>>(istream& input, tag& t) {
    string s;
    input >> s;
    if(s.substr(1,1) == "/") {
        t.setName(s.substr(2, s.size()-3));
        t.setEnd();
        return input;
    }
    else if(s.substr(0, 1) == "<" && s.substr(s.size()-1, 1) == ">") {
        t.setName(s.substr(1, s.size()-2));
        return input;
    }
    else {
        t.setName(s.substr(1));
        input.ignore();
        input >> s;
        while(s.substr(s.size()-1, 1) != ">") {
            if(s.substr(0, 1) != "\"" && s != "=") {
                t.setAttributes(s);
            }
            else if(s != "=") {
                t.setValues(s.substr(1, s.size()-2));
            }
            input.ignore();
            input >> s;
        }
        t.setValues(s.substr(1, s.size()-3));
    }
    return input;
}

int encontraValue(vector<string> a, string s) {
    int k = 0;
    vector<string>::iterator it;
        for(it = a.begin();it != a.end(); it++, k++) {
            if(*it == s) {
                return k;
            }
        }
    throw runtime_error("Not Found!");
}

int encontraTag(vector<tag> tags, string s) {
    int k = 0;
    vector<tag>::iterator it;
        for(it = tags.begin();it != tags.end(); it++, k++) {
            if(tags[k].getName() == s) {
                return k;
            }
        }
    return -1;
}

tag retornaTag(vector<tag> tags, string s) {
    if(tags.empty())
        throw runtime_error("Not Found!");
    vector<tag>::iterator it;
        for(it = tags.begin();it != tags.end(); it++) {
            if((*it).getName() == s) {
                return *it;
            }
        }
    throw runtime_error("Not Found!");
}

int main() {
    int N, Q, i, j, k, l = -1;
    string s, aux;
    tag T;
    vector<tag> tags, raiz;
    cin >> N >> Q;
    for(i=0;i<N;i++) {
        l++;
        tag t;
        cin >> t;
        if(encontraTag(tags, t.getName()) == -1) {
            tags.push_back(t);
            for(j=l-1;j>=0;j--) {
                if(tags[j].getEnd() == false) {
                    tags[j].setTags(t);
                    break;
                }
            }
            if(j == -1) {
                raiz.push_back(t);
            }
        }
        else if(t.getEnd()) {
            k = encontraTag(tags, t.getName());
            tags[k].setEnd();
            l--;
        }
    }
    
    for(i=0;i<Q;i++) {
        vector<string> nomes;
        k = 0;
        cin >> s;
        for(j=0;j<s.size();j++) {
            aux.push_back(s[j]);
            if(s.substr(j, 1) == ".") {
                aux.pop_back();
                nomes.push_back(aux);
                aux.erase(aux.begin(), aux.end());
            }
            else if(s.substr(j, 1) == "~") {
                aux.pop_back();
                nomes.push_back(aux);
                aux.erase(aux.begin(), aux.end());
            }
        }
        vector<string>::iterator it = nomes.begin();
        try {
            T = retornaTag(raiz, *it);
            T = retornaTag(tags, T.getName());
        }
        catch(const runtime_error& e) {
            k = -1;
            cout << e.what() << "\n";
        }

        if(k != -1) {
            for(it = nomes.begin()+1;it != nomes.end(); it++) {
                try {
                    T = retornaTag(T.getTags(), *it);
                    T = retornaTag(tags, T.getName());
                }
                catch(const runtime_error& e) {
                    k = -1;
                    cout << e.what() << "\n";
                    break;
                }
            }
        }

        if(k != -1) {
            try {
                k = encontraValue(T.getAttributes(), aux);
                cout << T.getValues(k) << "\n";
            }
            catch(const runtime_error& e) {
                cout << e.what() << "\n";
            }
        }
        aux.erase(aux.begin(), aux.end());
    }
    
    return 0;
    
}