/**
 * CropFace: detect face, crop and save it.
 *
 * Parameters:
 * -----------
 * argv[1]: picture addess
 *
 * Returns:
 * --------
 *  face saved at "face_" + argv[1]
**/
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>

//using namespace std;
using namespace cv;

void detectAndSave( Mat frame, String output_path );

String face_cascade_name = "haarcascade_frontalface_alt.xml";
CascadeClassifier cascade;

int main(int argc, char** argv ){
    if ( argc != 2 ){
        printf("usage: CropFace <Image_Path>\n");
        return -1;
    }
    String output_path = argv[1];
    output_path += "_face.jpg";

    Mat image;
    image = imread( argv[1], 1 );

    if ( !image.data ){
        printf("No image data \n");
        return -1;
    }

    // load cascades
    if( !cascade.load( face_cascade_name ) ){ printf("--(!)Error loading face cascade\n"); return -1; };
    detectAndSave( image, output_path );

    return 0;
}


void detectAndSave( Mat frame, String output_path ){
    std::vector<Rect> faces;
    Mat frame_gray, main_face;

    cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );

    //-- Detect faces (input_image, output_vector, scale, min_neighbors, flags, min_size
    cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0, Size(80, 80) );

    //-- Enlarge rectangle around the face
    int size = MAX(faces[0].width, faces[0].height) + 100;
    int w_diff = size - faces[0].width;
    int h_diff = size - faces[0].height;
    faces[0].x = MAX(faces[0].x-w_diff/2., 0);
    faces[0].width = size; 
    faces[0].y = MAX(faces[0].y-h_diff/2., 0);
    faces[0].height = size;
    // std::cout << "[DEBUG] y: " << faces[0].y << "\n";
    // std::cout << "[DEBUG] x: " << faces[0].x << "\n";
    // std::cout << "[DEBUG] size: " << size << "\n";

    //-- Crop face and resize
    frame(faces[0]).copyTo(main_face); 
    resize(main_face, main_face, Size(64, 64));

    imwrite(output_path, main_face);
}
