
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <limits>

using namespace cv;
using namespace std;
int npoints =0;
string imgname = "frontalface/3.jpg";
const char*outputtxt = "Points01.txt";

void DrawPoint (int x, int y)
{
	Point center(x,y);
	Mat src = imread (imgname,1);
	
	circle( src,
         center,
         2.0,
         Scalar( 0, 0, 255 ),
         -1,
         8);
	vector<int> compression_params;
  	compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
  	compression_params.push_back(100);
  	imwrite(imgname,src,compression_params);  
}

std::fstream& GotoLine(std::fstream& file, unsigned int num){
    file.seekg(std::ios::beg);
    for(int i=0; i < num - 1; ++i){
       file.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
    return file;
}

void ReadfromFile ()
{
	int avgx,avgy,stddev,somax,somay;
	int x1,y1,x2,y2,x3,y3;
	std::fstream infile("buffer.txt");
	std::string line;
	int a,b;
	for (int i = 0; i<31 ; i++)
	{
		somax = 0;
		somay = 0;
		GotoLine(infile,(i+1));
		getline(infile, line);
   		std::istringstream iss(line);
    	
    	if (!(iss >> x1 >> y1)) { break; } // error

    	//cout<<"valor 1: "<<x1<< " e valor 2: "<<y1<<endl;// process pair (a,b)
    	somax+=x1;
    	somay+=y1;
    	GotoLine(infile,(i+32));
		getline(infile, line);
   		std::istringstream iss2(line);
    	
    	if (!(iss2 >> x2>> y2)) {break; } // error

    	//cout<<"valor 1: "<<x2<< " e valor 2: "<<y2<<endl;// process pair (a,b)
    	somax+=x2;
    	somay+=y2;
    	GotoLine(infile,(i+63));
		getline(infile, line);
   		std::istringstream iss3(line);
    	
    	if (!(iss3 >> x3 >> y3)) { break; } // error

    	//cout<<"valor 1: "<<x3<< " e valor 2: "<<y3<<endl;// process pair (a,b)
    	somax+=x3;
    	somay+=y3;
    	avgx=(somax/3);
    	avgy=(somay/3);

    	//cout <<"A média em X "<<avgx<<" em Y é: "<<avgy<<endl;

    	float somadesviox=0.0;
    	float somadesvioy=0.0;
    	somadesviox+= (x1-avgx)*(x1-avgx);
    	somadesvioy+= (y1-avgy)*(y1-avgy);

    	somadesviox+= (x2-avgx)*(x2-avgx);
    	somadesvioy+= (y2-avgy)*(y2-avgy);

    	somadesviox+= (x3-avgx)*(x3-avgx);
    	somadesvioy+= (y3-avgy)*(y3-avgy);

    	float desviox,desvioy;
    	desviox = sqrt(somadesviox/3);
    	desvioy = sqrt(somadesvioy/3);

    	//cout <<"O desvio em X "<<desviox<<" em Y é: "<<desvioy<<endl;
    	ofstream outfile;
		outfile.open(outputtxt , ios::app);
		outfile<<avgx<<" "<<avgy<< " "<<desviox <<" "<<desvioy<<endl;
		DrawPoint(avgx,avgy);
	}


}

void WriteinFile(Point pt)
{
	ofstream outfile;
	outfile.open("buffer.txt" , ios::app);
	outfile<<pt.x<<" "<<pt.y<<endl;
	npoints++;
	if (npoints<32)
	{
		cout<<"Ponto salvo: "<<npoints<<endl;
	}
	
	else if ((npoints>=32)&&(npoints<63))
	{
		cout<<"Ponto salvo: "<<(npoints-31)<<endl;
	}
	else if ((npoints>=63))
	{
		cout<<"Ponto salvo: "<<(npoints-62)<<endl;	
	}

	//cout <<"Ponto salvo no arquivo: "<< (*pt) <<endl;
}

void CallBackFunc(int e, int x, int y, int d, void *ptr )
{
	
	if (e == EVENT_LBUTTONDOWN)
	{
		
		Point*p = (Point*)ptr;
    	p->x = x;
   		p->y = y;
   		WriteinFile(*p);
   		//cout <<"Ponto salvo: "<< (*p) <<endl;
	}

	else if (e == EVENT_RBUTTONDOWN)
	{
		
		Point*p = (Point*)ptr;
    	p->x = -1;
   		p->y = -1;
   		//cout <<"Ponto não pode ser definido para o ground truth: "<< (*p) <<endl;
   		WriteinFile(*p);
	}
	
	
}

int main (){

	Mat src = imread (imgname,1);
	cvNamedWindow ("Imagem", WINDOW_AUTOSIZE | CV_GUI_NORMAL);
	if (!src.data)
	{
		cout<<"Não pode carregar a imagem!"<<endl;
		return 0;
	}
	imshow("Imagem",src);
	ofstream outfile;
	outfile.open("buffer.txt");
	outfile.close();
	outfile.open(outputtxt);
	outfile.close();
	
	while (npoints!=93)
	{
		imshow("Imagem",src);
		Point pt1;
		
		setMouseCallback("Imagem", CallBackFunc, (&pt1));
		//cout<<"Na main: "<<pt1<<endl;
		char key = (char) cv::waitKey(30);   // explicit cast
		if (key == 27) break;  
		
	}
	ReadfromFile();

	//cout<<"saiu do loop"<<endl;

	return 0;
}
