#include "HandGesture.h"

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/video/background_segm.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

HandGesture::HandGesture() {

}


double HandGesture::getAngle(Point s, Point e, Point f) {

    double v1[2],v2[2];
    v1[0] = s.x - f.x;
    v1[1] = s.y - f.y;

    v2[0] = e.x - f.x;
    v2[1] = e.y - f.y;

    double ang1 = atan2(v1[1],v1[0]);
    double ang2 = atan2(v2[1],v2[0]);

    double angle = ang1 - ang2;
    if (angle > CV_PI) angle -= 2 * CV_PI;
    if (angle < -CV_PI) angle += 2 * CV_PI;
    return (angle * 180.0/CV_PI);
}
void HandGesture::FeaturesDetection(Mat mask, Mat output_img, Mat &draw_img) {

    vector<vector<Point> > contours;
    Mat temp_mask;
    mask.copyTo(temp_mask);
    int index = -1;
    // CODIGO 3.1
    // detección del contorno de la mano y selección del contorno más largo
    //...
    findContours(temp_mask,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_SIMPLE);
    int max=0;
    for (int i=0;i<contours.size();i++){
        if(max<contours[i].size()){
            max=contours[i].size();
            index=i;
        }
    }

    // pintar el contorno
    //...
    if (index!=-1){
        drawContours(output_img,contours,index,cv::Scalar(255,0,0),2,8,vector<Vec4i>(),0,Point());

        //obtener el convex hull
        vector<int> hull;
        convexHull(contours[index],hull);

        // pintar el convex hull
        Point pt0 = contours[index][hull[hull.size()-1]];
        for (int i = 0; i < hull.size(); i++)
        {
            Point pt = contours[index][hull[i]];
            line(output_img, pt0, pt, Scalar(0, 0, 255), 2, CV_AA);
            pt0 = pt;
        }

        //obtener los defectos de convexidad
        vector<Vec4i> defects;
        convexityDefects(contours[index], hull, defects);

        Point aux;
        int x = 0;
        int y = 0;
        int cont = 0;
        for (int i = 0; i < defects.size(); i++) {
            Point s = contours[index][defects[i][0]];
            Point e = contours[index][defects[i][1]];
            Point f = contours[index][defects[i][2]];
            float depth = (float)defects[i][3] / 256.0;
            double angle = getAngle(s, e, f);

            // CODIGO 3.2
            // filtrar y mostrar los defectos de convexidad
            //...
            if (angle < 90.0 && angle > 20.0){
               convexityDefects(contours[index], hull, defects);
               circle(output_img, f, 5, Scalar(0, 255, 0),5, 0);
               aux = f;
               cont++;
            }
            //opcional punto medio hull
            Point p1 = contours[index].at(defects[i].val[2]);
            x += p1.x;
            y += p1.y;

        }
       // Contar dedos de la mano ## opcional 1
        Point p(100,70);
        string contt = "Dedos: " + to_string(cont);
        putText(output_img, contt, p, FONT_HERSHEY_SCRIPT_SIMPLEX, 2,  Scalar(255, 0, 0));

        // Pintar punto medio ConxexHUll  ## opcional 2
        circle(output_img, Point(x/defects.size(), y/defects.size()), 3, Scalar( 0, 0, 255), 3);

        // Dibujar segun dedos ## opcional 3
          switch(cont){
              case 1:
                  circle(draw_img, aux, 40, Scalar(50, 50, 50),-5, 0);
              break;
              case 2:
                  circle(draw_img, aux, 40, Scalar(255, 0, 0),-5, 0);
              break;
              case 3:
                  circle(draw_img, aux, 40, Scalar(0, 255, 0),-5, 0);
              break;
              case 4:
                  circle(draw_img, aux, 40, Scalar(0, 0, 255),-5, 0);
              break;
              default:
                  Point p(100,70);
                  string mess = "Dibujar algo...";
                  putText(draw_img, mess, p, FONT_HERSHEY_SCRIPT_SIMPLEX, 2,  Scalar(255, 0, 0));
                  /*  //borrar con puño cerrado o dedos juntos
                    Scalar color = Scalar(0, 0, 0);       //define desired color
                    Mat draw_d = Mat(500, 500, CV_8UC3, color);
                    draw_d.copyTo(draw_img);*/
              break;
            }

    }
}
