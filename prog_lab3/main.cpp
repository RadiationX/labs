#include <iostream>
#include <fstream>

using namespace std;
struct data {
    string fio;
    int points[5];
    string phone;
};

void one();

int main() {
    locale::global(locale(""));
    locale loc("");
    cout.imbue(loc);
    one();
    return 0;
}

void one() {
    ifstream fin("/home/radiationx/ClionProjects.git/prog_lab3/text.txt", ios::in);
    ofstream fout("/home/radiationx/ClionProjects.git/prog_lab3/out.txt", ios::out);
    string text, outText, temp;
    char buff;
    int dataSize = 0, colon = 0;
    data *datas;
    string::size_type sz;
    string line;
    while (fin.get(buff)) {
        text += buff;
        if (buff=='\n')
            dataSize++;
    }

    datas = new data[dataSize+1];
    dataSize = 0;

    for (int i = 0; i < text.size(); i++) {
        if (text[i] == ':') {
            colon++;
            temp = "";
            continue;
        }
        if (text[i] == '\n') {
            dataSize++;
            colon = 0;
            continue;
        }

        if (colon == 0) {
            datas[dataSize].fio += text[i];
        } else if (colon > 0 && colon < 6) {
            temp += text[i];
            datas[dataSize].points[colon - 1] = stoi(temp, &sz);
        } else {
            datas[dataSize].phone += text[i];
        }
    }

    int middle = 0;
    for(int i=0; i<dataSize+1;i++){
        for(int j = 0; j<5;j++){
            middle+=datas[i].points[j];
        }
        middle/=5;
        cout<<middle<<endl;
        if(middle<20){
            if(i!=0)
                outText.append("\n");
            outText.append(datas[i].fio).append(":");
            for(int j = 0; j<5;j++)
                outText.append(to_string(datas[i].points[j])).append(":");
            outText.append(datas[i].phone);

        }
        middle=0;
    }
    cout<<endl<<outText;

    fout<<outText;
    fout.close();
    fin.close();
}