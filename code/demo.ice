module Demo
{

sequence<byte> ByteSeq;
const int ByteSeqSize = 128000;

sequence<string> StringSeq;
const int StringSeqSize = 128000;

struct StringDouble
{
string s;
double d;
};
sequence<StringDouble> StringDoubleSeq;
const int StringDoubleSeqSize = 128000;

struct Fixed
{
int i;
int j;
double d;
};
sequence<Fixed> FixedSeq;

};