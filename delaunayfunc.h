#pragma once
#include <opencv2/legacy/legacy.hpp>  
#include<opencv2\opencv.hpp>
#include <opencv2/features2d/features2d.hpp>
#include<opencv2/nonfree/nonfree.hpp>
#include<iostream> 
using namespace std;
using namespace cv;

CvSubdiv2D* init_delaunay(CvMemStorage* storage, CvRect rect);
inline void draw_edge(IplImage* img, CvSubdiv2DEdge edge, CvScalar color);
void draw_delaunay(IplImage* img, CvSubdiv2D* subdiv, CvScalar delaunay_color);
void draw_voronoi(CvSubdiv2D* subdiv, IplImage* img);
void draw_facet(IplImage* img, CvSubdiv2DEdge edge);
inline void draw_point(IplImage* img, CvPoint2D32f fp, CvScalar color);
void locate_pointInDelaunay(CvSubdiv2D* subdiv, CvPoint2D32f fp, IplImage* img, CvScalar active_color);
void locate_pointInVoronoi(CvSubdiv2D* subdiv, CvPoint2D32f fp, IplImage* img, CvScalar color);