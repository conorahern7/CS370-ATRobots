#include <iostream>
//#include <string>
#include <fstream>
#include <ctime>
#include <cstring>

using namespace std;

#define lock_type 3

int write_line(string, string, ofstream &, int, char []);
bool file_exists(string);
bool endsWith(string, string);
string replaceExt(string, string);
string ucase(string);
string prepare(string, string);
string encode(string, char [], int);

int lock_dat, lock_pos;

int main(int argc, char *argv[]) {
    string fn1, fn2, s, s1, s2;
    int i, k, lock_pos, this_dat;
    ifstream f1;
    ofstream f2;
    time_t now = time(0);
    tm *ltm = localtime(&now);

    lock_pos = 0;
    lock_dat = 0;

    //Only 1-2 arguments allowed, otherwise print usage and exit.
    if((argc < 2) || (argc > 3)) {
        cout << "Usage: ATRLOCK <robot[.at2]> [locked[.atl]]";
        exit(0);
    }

    //Set fn1 to arg1, btrim removes spaces & other chars from "left" and "right" of file names,
    //but this probably isn't necessary in C++. Added ucase function for compatibility.
    //fn1:=btrim(ucase(paramstr(1)));
    fn1 = ucase(argv[1]);

    //Add file extension to argument(s) if not already there
    if (!(endsWith(fn1, ".AT2"))) {
        fn1 = fn1 + ".AT2";
    }
    if (argc == 3) {
        //fn2:=btrim(ucase(paramstr(2)));
        fn2 = ucase(argv[2]);
        if (!(endsWith(fn2, ".ATL"))) {
            fn2 = fn2 + ".ATL";
        }
    } else {
        fn2 = replaceExt(fn1, ".ATL");
    }

    //Check here to see if file 1/input file exists
    if (!file_exists(fn1)) {
        cout<<"Input robot file \"" + fn1 + "\" does not exist.";
        exit(0);
    }

    //Check to see if file 2's name is valid ?
    //For now, instead check to see if file creation was successful after opening stream, later on

    //Check to make sure input and output filenames are not the same
    if( fn1.compare(fn2) == 0 ) {
        cout<<"Filenames can not be the same!";
        exit(0);
    }

    //Filenames have been fully checked, open files.
    f1.open(fn1);
    f2.open(fn2);

    //Check here to see if output file creation was successful
    if (!file_exists(fn2)) {
        cout<<"Output robot file \"" + fn2 + "\" could not be created.";
        exit(0);
    }

    //Copy comment header
    f2 << ";------------------------------------------------------------------------------\n";
    s = "";
    while (s.compare("") == 0) {
        //Read line of f1 to s
        getline(f1, s);

        //Run "btrim(s)"
        //If first character of s is ;, then write s to f2, and set s to ""
        if ( s[0] == ';' ) {
            f2 << s + "\n";
            s = "";
        }
    }

    //Randomize = rand.time null
    srand (time(NULL));

    //LOCK HEADER
    //f2 << endl;
    f2 <<";------------------------------------------------------------------------------\n";
    //Try to remove .AT2 ext in the future
    f2 << "; " << fn1 << " Locked on " << (1900 + ltm->tm_year) << "/" << (1 + ltm->tm_mon) <<
       "/" << (ltm->tm_mday) << endl;
    f2 <<";------------------------------------------------------------------------------\n";

    //k:=random(21)+20;
    k = rand() % 21 + 20;
    char *lock_code = new char[k];

    //cout << "k is " << k << endl;

    //Generate lock code to char array
    for (i = 0; i < k; i++) {
        lock_code[i] = (char)(rand() % 32 + 65);
    }

    //Print lock code info
    f2 << "#LOCK" << lock_type << " ";
    for (i = 0; i < k; i++) {
        f2 << lock_code[i];
    }
    f2 << endl;

    //DECODE lock_code
    for (i = 0; i < k; i++){
        lock_code[i] = (char)((int)(lock_code[i]) - 65);
    }

    cout << "Encoding " << fn1 << "..." << endl;

    //ENCODE ROBOT
    //s = //btrim(s);

    //if length(s)>0 then
    if (s.length() > 0) {
        write_line("", ucase(s), f2, k, lock_code);
    }

    // while not eof(f1) do
    //readln(f1,s1); s:='';
    //s1:=btrim(ucase(s1));

    while (getline(f1, s1)) {
        //Read line of f1 to s1, done in while cond. When it reaches EOF, while loop ends.

        s = "";
        s1 = ucase(s1);

        write_line(s, s1, f2, k, lock_code);
    }

    cout << "Done. Used LOCK Format #" << lock_type << "." << endl;
    cout << "Only ATR2 v2.08 or later can decode." << endl;
    cout << "LOCKed robot saved as " << fn2 << "." << endl;

    f1.close();
    f2.close();
}

int write_line(string s, string s1, ofstream &f2, int k, char lock_code[]) {
    //cout << "write_line: " << s1 << endl;

    s = prepare(s, s1);

    //cout << "write_line s: " << s << endl;

    //write line
    if (s1.length() > 0) {
        s = encode(s, lock_code, k);
        f2 << s << endl;
    }
}

bool file_exists(string filename)
{
    ifstream testopen(filename);
    return testopen.good();
}

bool endsWith(string one, string two) {
    //Compare end of first string with the second string.
    int str_i, endlen;

    endlen = two.length();
    str_i = one.length() - endlen;

    if( one.compare(str_i, endlen, two) == 0 ) {
        return true;
    } else {
        return false;
    }

}

string replaceExt(string one, string two) {
    //Replace ending of string one with string two.
    int str_i, extlen;
    string three;

    extlen = two.length();
    str_i = one.length() - extlen;

    three = one.replace(str_i, extlen, two);

    return three;
}

string ucase(string str) {
    int i;
    for (i = 0; i < str.length(); i++) {
        str[i] = toupper(str[i]);
    }
    return str;
}

string prepare(string s, string s1){

    int i,j;

    //int n = s1.length();
    //char c[n + 1];

    //cout << "c is initially " << c << endl;

    //for(i = 0; i < (n); i++) {
    //    c[i] = ' ';
    //}
    //strcpy(c, s1.c_str());


    //{--remove comments--}
    /*if ((s1.length() == 0) || (s1[0]=';')){
        s1 = "";
    } else {
        k = 0;
        for (i = 0; i < s1.length(); i++)
        {
            if (s1[i]==';'){
                k = i;
            }
            if (k > 0){
                //Figure out how lstr works
                //s1=lstr(s1,k-1);
            }
        }
    }*/

//    {--remove excess spaces--}
    //j = 0;
    for (i = 0; i < s1.length(); i++) {

        if ( (s1.compare(i, 1, "\b") == 0) || (s1.compare(i, 1, "\t") == 0) ||
                (s1.compare(i, 1, "\n") == 0) || (s1.compare(i, 1, ",") == 0) ) {
            s1.erase(i, 1);
            //c[j] = s1[i];
            //j++;
        }
        //cout << s1[i] << " " << (s1.compare(i, 1, " ") != 0) << " " << (s1.compare(i, 1, "\b") != 0) << " " << (s1.compare(i, 1, "\t") != 0) << " " << (s1.compare(i, 1, "\n") != 0) << " " << (s1.compare(i, 1, ",") != 0) << endl;
        /*else if (s2!= ""){
            s = s + s2 + " ";
            s2 = "";
        }*/

    }
    /*if (s2!=""){
        s = s+s2;
    }*/
    //c[n] = ' ';
    //cout << s1 << "; " << c << endl;
    //s1 = c;
    //cout << s1 << endl;
    return s1;
}

string encode(string s, char lock_code[], int k) {
    int i, this_dat;

    int n = s.length();
    char c[n+1];
    strcpy(c, s.c_str());
    //unsigned char c_temp = ' ';

    //cout << "encode: " << s << endl;

    //char lock_code2[21];
    //strcpy(lock_code2, "AAAAAAAAAAAAAAAAAAAA");

    //cout << "strlen(lock_code) is " << strlen(lock_code) << endl;

    if(strlen(lock_code) != 0) {
        for (i = 0; i < s.length(); i++) {

            if (lock_pos > (k - 1)) {
                lock_pos = 0;
            }

            //If character is outside normal alphabet/symbols in ASCII range, change it to a space
            if (((int)(c[i]) <= 31) || ((int)(c[i]) >= 128)) {
                c[i] = ' ';
            }

            this_dat = (int)(c[i]) & 15;
            //Debug:
            //cout << c[i] << ", " << (int)(c[i]) << ", & 15 = " << this_dat << endl;
            //cout << ((((long)(c[i]) ^ (long)(lock_code[lock_pos])) ^ lock_dat) + 1) << ", ";
            c[i] = (char)((((int)(c[i]) ^ (int)(lock_code[lock_pos])) ^ lock_dat) + 1);
            //cout << c[i] << ", lock_dat = " << lock_dat << ", lock_code = " << (int)lock_code[lock_pos] << ", lock_pos = " << lock_pos << endl;
            lock_dat = this_dat;
            lock_pos++;
        }
        //cout << c << endl;
        s = c;
        return s;
    }
}