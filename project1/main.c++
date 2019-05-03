// main.c++
// Hamza Hameed
// KUID: 2796053

#include "GLFWController.h"
#include "ModelView.h"

#include <fstream>

void createScene(GLFWController& c, ShaderIF* sIF, std::string fileName)
{
	//Open file that was passed in as a command line arg
	std::ifstream in;
	in.open(fileName);
	if(!in){
		std::cerr << "\nError: File does not exist or is invalid.\n";
		exit(1);
	}

	//Grab the number of points and attributes, now respectively called rows and cols
	int rows;
	int cols;
	in >> rows;
	in >> cols;

	//Parser
	float a[rows][cols];
	std::string str;
	std::string temp = "";
	int x = 0;
	int y = 0;
	std::getline(in, str); //skip past the first line because its no longer useful
	while(std::getline(in, str)){ //grab a line
		y = 0;
		int length = str.length();
		for(int i = 0; i < length; i++){
			//while char being read is not a space/tab
			while(isdigit(str[i]) || str[i] == '-' || str[i] == '.'){
				temp += str[i];
				i++;
			}
			a[x][y] = stof(temp); //put value into 2d array
			temp = ""; //reset
			y++;
		}
		x++;
	}

	//Call addModel for each line
	for(int i = 0; i < rows; i++){
		c.addModel(new ModelView(sIF, a[i], cols));
	}
}

int main(int argc, char* argv[])
{
	GLFWController c(argv[0]);
	c.reportVersions(std::cout);

	ShaderIF* sIF = new ShaderIF("shaders/project1.vsh", "shaders/project1.fsh");

	createScene(c, sIF, argv[1]);

	// initialize 2D viewing information:
	// Get the overall scene bounding box in Model Coordinates:
	double xyz[6]; // xyz limits, even though this is 2D
	c.getOverallMCBoundingBox(xyz);
	std::cout << "Bounding box: " << xyz[0] << " <= x <= " << xyz[1] << '\n';
	std::cout << "              " << xyz[2] << " <= y <= " << xyz[3] << '\n';
	std::cout << "              " << xyz[4] << " <= z <= " << xyz[5] << "\n\n";
	// Tell class ModelView we initially want to see the whole scene:
	ModelView::setMCRegionOfInterest(xyz);

	c.run();

	delete sIF;

	return 0;
}
