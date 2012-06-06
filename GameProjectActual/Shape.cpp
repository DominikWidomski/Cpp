#include "GameUtil.h"
#include "Shape.h"

using namespace std;

Shape::Shape()
{
}

Shape::Shape(const string& shape_filename)
{
	LoadShape(shape_filename);
}

Shape::~Shape()
{
}

void Shape::Render(void)
{
	// Disable lighting for solid colour lines
	//glDisable(GL_LIGHTING);
	// Start drawing lines
	//if (mLoop) { glBegin(GL_LINE_LOOP); } else { glBegin(GL_LINE_STRIP); }
	glBegin(mMode);
		// Set rgb colour
		glColor4f(mRGBA[0], mRGBA[1], mRGBA[2], mRGBA[3]);
		// Add vertices to draw shape
		for (GLVector3fList::iterator it = mPoints.begin(); it != mPoints.end(); ++it) {
			SmartPtr<GLVector3f> vec = (*it);
			glVertex3f(vec->x, vec->y, vec->z);
		}
	// Finish drawing lines
	glEnd();
	// Enable lighting
	//glEnable(GL_LIGHTING);
}

void Shape::LoadShape(const string& shape_filename)
{
	string filename;
	filename = "..//..//ASSETS//";
	filename += shape_filename;

	ifstream shape_file(shape_filename.c_str(), ios::in | ios::binary);
	ifstream shape_file2(filename.c_str(), ios::in | ios::binary);


	if (!shape_file && !shape_file2)
	{
		cerr << "Error opening " << shape_filename; exit(1);
	}

	string s;
	if (shape_file)
		shape_file >> s;
	else
		shape_file2 >> s;

	//if (0 == s.compare("loop")) { mLoop = true; } else { mLoop = false; }

        if(0 == s.compare("GL_POINTS")){
            mMode = GLenum(GL_POINTS);
        } else if (0 == s.compare("GL_LINES")){
            mMode = GLenum(GL_LINES);
        } else if (0 == s.compare("GL_LINE_LOOP")){
            mMode = GLenum(GL_LINE_LOOP);
        } else if (0 == s.compare("GL_LINE_STRIP")){
            mMode = GLenum(GL_LINE_STRIP);
        } else if (0 == s.compare("GL_TRIANGLES")){
            mMode = GLenum(GL_TRIANGLES);
        } else if (0 == s.compare("GL_TRIANGLE_STRIP")){
            mMode = GLenum(GL_TRIANGLE_STRIP);
        } else if (0 == s.compare("GL_TRIANGLE_FAN")){
            mMode = GLenum(GL_TRIANGLE_FAN);
        } else if (0 == s.compare("GL_QUADS")){
            mMode = GLenum(GL_QUADS);
        } else if (0 == s.compare("GL_QUAD_STRIP")){
            mMode = GLenum(GL_QUAD_STRIP);
        } else if (0 == s.compare("GL_POLYGON")){
            mMode = GLenum(GL_POLYGON);
        }

	if (shape_file) {
		shape_file >> mRGBA;
		while (!shape_file.eof()) {
			float x, y, z;
			shape_file >> x >> y >> z;
			SmartPtr<GLVector3f> vec = new GLVector3f(x, y, z);
			mPoints.push_back(vec);
		}
	} else {
		shape_file2 >> mRGBA;
		while (!shape_file2.eof()) {
			float x, y, z;
			shape_file2 >> x >> y >> z;
			SmartPtr<GLVector3f> vec = new GLVector3f(x, y, z);
			mPoints.push_back(vec);
		}
	}
}
