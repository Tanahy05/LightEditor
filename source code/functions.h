#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <vector>
#include<cmath>
#include "Image_Class.h"
#include <QDebug>
using namespace std;

//implemented
void grayscale(Image& image){
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned  int avg = 0; // Initialize average value
            for (int x = 0; x < 3; ++x) {
                avg += image(i, j, x); // Accumulate pixel values
            }
            avg/=3;
            image(i, j, 0) = avg;
            image(i, j, 1) = avg;
            image(i, j, 2) = avg;
        }
    }
}

//implemented
void rotate90(Image& image){
    image.saveImage("temp.jpg");
    image.loadNewImage("temp.jpg");
    Image temp(image.height,image.width);
    for(long long i=0;i<temp.width;++i){
        for(long long j=0;j<temp.height;++j){
            for(long long k=0;k<3;++k){
                long long start=image.height-1-i;
                temp(i,j,k)=image(j,start,k);
            }

        }

    }
    temp.saveImage("temp.jpg");
    image.loadNewImage("temp.jpg");
}
//implemented
void rotate90Left(Image& image){
    image.saveImage("temp.jpg");
    image.loadNewImage("temp.jpg");
    Image temp(image.height, image.width);
    for (long long i = 0; i < temp.width; ++i) {
        for (long long j = 0; j < temp.height; ++j) {
            for (long long k = 0; k < 3; ++k) {
                long long start = i;
                long long end = image.width - 1 - j;
                temp(i, j, k) = image(end, start, k);
            }
        }
    }
    temp.saveImage("temp.jpg");
    image.loadNewImage("temp.jpg");
}


//implemented
void rotate_img(Image& image, int degree){
    switch(degree){
    case 1:
        rotate90(image);
        break;
    case 2:
        rotate90Left(image);
        break;
    }


}


//implemented
void flip(Image& image,int direction){
    image.saveImage("temp.jpg");
    image.loadNewImage("temp.jpg");
    Image temp(image.width,image.height);
    if(direction==1){
        for(long long i=0;i<temp.width;++i){
            for(long long j=0;j<temp.height;++j){
                for(long long k=0;k<3;++k){
                    long long start=temp.width-1-i;
                    temp(i,j,k)=image(start,j,k);
                }

            }

        }

    }
    else{
        for(long long i=0;i<temp.width;++i){
            for(long long j=0;j<temp.height;++j){
                for(long long k=0;k<3;++k){
                    long long start=temp.height-1-j;
                    temp(i,j,k)=image(i,start,k);
                }

            }

        }

    }

    temp.saveImage("temp.jpg");
    image.loadNewImage("temp.jpg");
}


//implemented
void bw(Image& image){

    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            int avg = 0;

            for (int k = 0; k < 3; ++k) {
                avg += image(i, j, k);
            }

            avg /= 3;

            if(avg>127){
                image(i, j, 0) = 255;
                image(i, j, 1) = 255;
                image(i, j, 2) = 255;

            }
            else{
                image(i, j, 0) = 0;
                image(i, j, 1) = 0;
                image(i, j, 2) = 0;
            }

        }
    }
}

//implemented
void DarkenLighten(Image &image ,double scale) {
    scale*=0.1;
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                for (int k = 0; k < 3; ++k) {
                    int newValue = image(i, j, k) * scale;
                    if (newValue > 255) {
                        image(i, j, k) = 255;
                    }
                    else {
                        image(i, j, k) = newValue;
                    }
                }
            }
        }
    }


//implemented
void invert(Image& image){
    for(int i=0;i<image.width;++i){
        for(int j=0;j<image.height;++j){
            for(int k=0; k<3;++k){
                image(i,j,k)=255-image(i,j,k);

            }

        }
    }
}

//implemented
void crop(Image& image,int X,int Y,int W,int H){
    image.saveImage("temp.jpg");
    image.loadNewImage("temp.jpg");
    Image temp(W,H);
    for(long long i=X;i<X+W;++i){
        for(long long j=Y;j<Y+H;++j){
            for(long long k=0;k<3;++k){

                temp(i-X,j-Y,k)=image(i,j,k);
            }

        }

    }

    temp.saveImage("temp.jpg");
    image.loadNewImage("temp.jpg");
}

//implemented
void rsize(Image& image,int x,int y){
    Image image2(x,y);
    float r=static_cast<float>(image.width)/x;
    float c=static_cast<float>(image.height)/y;
    for (int i = 0; i < image2.width ; i++) {
        for (int j = 0; j < image2.height ; j++) {
            for (int k = 0; k < 3; k++) {
                int oi=static_cast<int>(i*r);
                int oj=static_cast<int>(j*c);
                image2(i,j,k)=image(oi,oj,k);
            }
        }
    }
    image2.saveImage("temp.jpg");
    image.loadNewImage("temp.jpg");
}

//implemented
void merge(Image &image1, Image &image2) {
    int imgwdth= max(image1.width,image2.width);
    int imghght= max(image1.height,image2.height);
    rsize(image1,imgwdth,imghght);
    rsize(image2,imgwdth,imghght);
    for (int i = 0; i < image1.width; ++i) {
        for (int j = 0; j < image1.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                // Accumulate pixel values
                image1(i, j, k) = (image1(i, j, k) + image2(i, j, k)) / 2;
            }
        }
    }
}
//overload for custom placement
void merge(Image &image1, Image &image2,int X,int Y) {
    for (int i = X; i < image1.width; ++i) {
        for (int j = Y; j < image1.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                // Accumulate pixel values
                if(((i-X)<image2.width) && ((j-Y)<image2.height))
                image1(i, j, k) = (image1(i, j, k) + image2(i-X, j-Y, k)) / 2;
            }
        }
    }
}

//implemented (dynamic)
void frame(Image& image,int red,int green, int blue, bool isfancy=false){
    int thickness = min(image.width,image.height)*0.04;
    int fancy_thickness=thickness*0.2;
    int space=thickness*0.5;
    for(int i=0; i<image.width;++i){
        for (int j=0; j<thickness;++j){
            image(i,j,0)=red;
            image(i,j,1)=green;
            image(i,j,2)=blue;
        }

    }

    for(int i=0; i<image.width;++i){
        for (int j=image.height-1; j>=image.height-1-thickness;--j){
            image(i,j,0)=red;
            image(i,j,1)=green;
            image(i,j,2)=blue;
        }

    }

    for(int i=0; i<thickness;++i){
        for (int j=0; j<image.height;++j){
            image(i,j,0)=red;
            image(i,j,1)=green;
            image(i,j,2)=blue;
        }

    }
    for(int i=image.width-1;i>=image.width-1-thickness;--i){
        for (int j=0; j<image.height;++j){
            image(i,j,0)=red;
            image(i,j,1)=green;
            image(i,j,2)=blue;
        }

    }
    if(isfancy){
        for(int i=thickness; i<image.width-thickness;++i){
            for (int j=thickness; j<thickness+fancy_thickness;++j){
                image(i,j,0)=255;
                image(i,j,1)=255;
                image(i,j,2)=255;

            }

        }

        for(int i=thickness; i<image.width-thickness;++i){
            for (int j=image.height-thickness-1; j>=image.height-1-thickness-fancy_thickness;--j){
                image(i,j,0)=255;
                image(i,j,1)=255;
                image(i,j,2)=255;

            }

        }

        for(int i=thickness; i<thickness+fancy_thickness;++i){
            for (int j=thickness; j<image.height-thickness;++j){
                image(i,j,0)=255;
                image(i,j,1)=255;
                image(i,j,2)=255;

            }

        }

        for(int i=image.width-thickness-1;i>=image.width-1-thickness-fancy_thickness;--i){
            for (int j=thickness; j<image.height-thickness;++j){
                image(i,j,0)=255;
                image(i,j,1)=255;
                image(i,j,2)=255;

            }

        }
        int start=thickness+fancy_thickness+space;
        for(int i=start; i<image.width-start;++i){
            for (int j=start; j<start+fancy_thickness;++j){
                image(i,j,0)=255;
                image(i,j,1)=255;
                image(i,j,2)=255;

            }

        }

        for(int i=start; i<image.width-start;++i){
            for (int j=image.height-1-start; j>=image.height-1-start-fancy_thickness;--j){
                image(i,j,0)=255;
                image(i,j,1)=255;
                image(i,j,2)=255;

            }

        }

        for(int i=start; i<start+fancy_thickness;++i){
            for (int j=start; j<image.height-start;++j){
                image(i,j,0)=255;
                image(i,j,1)=255;
                image(i,j,2)=255;

            }

        }

        for(int i=image.width-1-start;i>=image.width-1-start-fancy_thickness;--i){
            for (int j=start; j<image.height-start;++j){
                image(i,j,0)=255;
                image(i,j,1)=255;
                image(i,j,2)=255;

            }

        }

    }
}


//implemented
void EdgeDetection(Image &image) {
    grayscale(image);
    Image edgeImage(image.width,image.height);
    for (int i = 1; i < image.width - 1; ++i) {

        for (int j = 1; j < image.height - 1; ++j) {
            // Apply Sobel operator on grayscale image
            int gx = (image(i+1, j-1, 0) + 2*image(i+1, j, 0) + image(i+1, j+1, 0)) - (image(i-1, j-1, 0) + 2*image(i-1, j, 0) + image(i-1, j+1, 0));
            int gy = (image(i-1, j+1, 0) + 2*image(i, j+1, 0) + image(i+1, j+1, 0)) - (image(i-1, j-1, 0) + 2*image(i, j-1, 0) + image(i+1, j-1, 0));
            int magnitude = sqrt(gx*gx + gy*gy);

            // Edge thresholding
            if (magnitude > 128) {
                // Set edge pixel to gray
                for (int k = 0; k < 3; ++k) {
                    edgeImage(i, j, k) = 128; // Gray
                }
            } else {
                // Set non-edge pixel to black
                for (int k = 0; k < 3; ++k) {
                    edgeImage(i, j, k) = 0; // Black
                }
            }
        }
    }
    invert(edgeImage);
    edgeImage.saveImage("temp.jpg");
    image.loadNewImage("temp.jpg");
}


void blur(Image &image,int strength) {
    // Larger kernel size for more blur
    const int kernelSize = strength; // Increase the kernel size
    float kernel[kernelSize][kernelSize];
    float kernelSum = 0.0;

    // Generate the kernel
    for(int i = 0; i < kernelSize; ++i) {
        for(int j = 0; j < kernelSize; ++j) {
            // Assign higher weights towards the center for more blur
            kernel[i][j] = 1.0 / (kernelSize * kernelSize);
            kernelSum += kernel[i][j];
        }
    }

    // Create a temporary vector to hold the filtered pixel values
    vector<vector<vector<double>>> filteredPixels(image.width, vector<vector<double>>(image.height, vector<double>(3)));

    // Apply the mean filter to the image
    for(int y = 0; y < image.height; ++y) {
        for(int x = 0; x < image.width; ++x) {
            for(int c = 0; c < 3; ++c) { // Assuming RGB channels
                float sum = 0.0;

                // Apply the kernel to the current pixel and its neighbors
                for(int ky = -kernelSize/2; ky <= kernelSize/2; ++ky) {
                    for(int kx = -kernelSize/2; kx <= kernelSize/2; ++kx) {
                        int pixelX = x + kx;
                        int pixelY = y + ky;
                        // Ensure pixel coordinates are within bounds
                        if (pixelX >= 0 && pixelX < image.width && pixelY >= 0 && pixelY < image.height) {
                            sum += image(pixelX, pixelY, c) * kernel[ky + kernelSize/2][kx + kernelSize/2];
                        }
                    }
                }

                // Set the filtered pixel value
                filteredPixels[x][y][c] = sum / kernelSum;
            }
        }
    }

    // Update the image with the filtered pixel values
    for(int y = 0; y < image.height; ++y) {
        for(int x = 0; x < image.width; ++x) {
            for(int c = 0; c < 3; ++c) { // Assuming RGB channels
                image(x, y, c) = filteredPixels[x][y][c];
            }
        }
    }
}


//implemented
void samurai(Image& image){
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned  int avg = 0; // Initialize average value
            for (int x = 0; x < 3; ++x) {
                avg += image(i, j, x); // Accumulate pixel values
            }
            avg/=3;
            avg=255-avg;
            image(i, j, 0) = 255;
            image(i, j, 1) = avg;
            image(i, j, 2) = avg;


        }
    }
}


//implemented
void skew(Image& image,double theta){
    theta=(theta*22/7)/180;
    double skewness= tan(theta)*image.height;
    Image temp(image.width+skewness,image.height);
    double counter=skewness;
    double interval= skewness/image.height;
    for(int j=0;j<image.height;++j){
        for(int i=counter;i<counter+image.width;++i){
            for(int k=0;k<3;++k){
                temp(i,j,k)=image(i-counter,j,k);
            }
        }
        counter = counter- interval;
    }
    temp.saveImage("temp.jpg");
    image.loadNewImage("temp.jpg");
}


//implemented
void landOfWano(Image &image) {

    for (int i = 0; i < image.width ; i++) {
        for (int j = 0; j < image.height ; j++) {
            image(i,j,2)*=0.5;
            for (int k = 0; k < 3; k++) {
                image(i,j,k)=image(i,j,k);
            }
        }
    }

}

//implemented

void purple(Image &image) {
    for (int i = 0; i < image.width ; i++) {
        for (int j = 0; j < image.height ; j++) {
            image(i,j,1)*=0.6;
            for (int k = 0; k < 3; k++) {
                image(i,j,k)=image(i,j,k);
            }
        }
    }

}


//implemented
void TvEffect(Image &image1){
    for (int i = 0; i < image1.width; ++i) {
        for (int j = 0; j < image1.height; ++j) {
            unsigned  int avg = ((i*25)+(j*25)) % 255 ;
            for (int k = 0; k < 3; ++k) {
                avg = (avg + image1(i, j, k));

                image1(i, j, 0) = avg / 3;
                image1(i, j, 1) = avg / 3;
                image1(i, j, 2) = avg / 3;
            }
        }
    }
}
//implemented
void mirror(Image &image) {
    for (int i = image.width; i > 0 ; i--) {
        for (int j = 0; j < image.height ; j++) {
            for (int k = 0; k < 3; k++) {
                image(i,j,k)=image(image.width-i,j,k);
            }
        }
    }
}

//implemented
void Oil(Image &image) {
    int kernel=3;
    Image change(image.width-2*kernel,image.height-2*kernel);
    for(int i=kernel;i<image.width-kernel;++i){
        for(int j= kernel;j<image.height-kernel;++j){
            int strength;
            int strength_count[10]{0},sumr[10]{0},sumg[10]{0},sumb[10]{0};
            for(int k=-kernel;k<=kernel;++k){
                for(int l=-kernel;l<=kernel;++l){
                    strength=((image(i+k,j+l,0)+image(i+k,j+l,1)+image(i+k,j+l,2))/3*10)/255;
                    if(strength>9)
                        strength=9;

                    strength_count[strength]=strength_count[strength]+1;
                    sumr[strength]=sumr[strength]+image(i+k,j+l,0);
                    sumg[strength]=sumg[strength]+image(i+k,j+l,1);
                    sumb[strength]=sumb[strength]+image(i+k,j+l,2);
                }
            }
            int max_index=0;
            int max_intensity=0;
            for(int k=0;k<10;++k){
                if(strength_count[k]>max_intensity){
                    max_intensity=strength_count[k];
                    max_index=k;
                }
            }
            change(i-kernel,j-kernel,0)=sumr[max_index]/strength_count[max_index];
            change(i-kernel,j-kernel,1)=sumg[max_index]/strength_count[max_index];
            change(i-kernel,j-kernel,2)=sumb[max_index]/strength_count[max_index];
        }
    }
    change.saveImage("temp.jpg");
    image.loadNewImage("temp.jpg");
}

//implemented
void burn(Image &image) {
    Image edgeImage(image.width,image.height);
    for (int i = 1; i < image.width - 1; ++i) {
        for (int j = 1; j < image.height - 1; ++j) {
            // Apply Sobel operator on grayscale image
            int gx = (image(i+1, j-1, 0) + 2*image(i+1, j, 0) + image(i+1, j+1, 0)) - (image(i-1, j-1, 0) + 2*image(i-1, j, 0) + image(i-1, j+1, 0));
            int gy = (image(i-1, j+1, 0) + 2*image(i, j+1, 0) + image(i+1, j+1, 0)) - (image(i-1, j-1, 0) + 2*image(i, j-1, 0) + image(i+1, j-1, 0));
            int magnitude = sqrt(gx*gx + gy*gy);

            // Edge thresholding
            if (magnitude > 128)
                edgeImage(i, j, 0) = 255; // White
            else
                edgeImage(i, j, 0) = 0; // Black
        }
    }
    edgeImage.saveImage("temp.jpg");
    image.loadNewImage("temp.jpg");
}


#endif // FUNCTIONS_H
