#include <iostream>
#include <opencv.hpp>
#include <io.h>
using namespace std;
using namespace cv;

//只读取某给定路径下的当前文件名
void getJustCurrentFile(string path, vector<string>& files) {
	//文件句柄
	long hFile = 0;
	//文件信息
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1) {
		do {
			if ((fileinfo.attrib & _A_SUBDIR)) {
				;
			}
			else {
				files.push_back(fileinfo.name);
				//files.push_back(p.assign(path).append("\\").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}

int main(int argc, char** argv)
{
	string pathName = "D:\\Ccode2013\\Images";
	vector<string> files;
	getJustCurrentFile(pathName, files);

	for (int i = 0; i < files.size();i++)
	{
		Mat img = imread(files[i]);
		//if (i==2)
		//{
		//	img = Mat::zeros(0, 3, 1);
		//	cout << files[i] << endl;
		//}
		if (img.empty())
		{
			string completePath = pathName +"\\"+ files[i];
			const char* temp = completePath.c_str();
			int ret=remove(temp);
			if (!ret)
			{
				cout << "remove "<< temp << endl;
			}
		}
	}
	return 0;
}