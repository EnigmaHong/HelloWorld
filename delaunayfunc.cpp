/* delaunayfunc.cpp */
#include "delaunayfunc.h"

//初始化初始三角形
CvSubdiv2D* init_delaunay(CvMemStorage* storage, CvRect rect)
{
	CvSubdiv2D* subdiv;//三角剖分的数据单元  

	subdiv = cvCreateSubdiv2D(CV_SEQ_KIND_SUBDIV2D, sizeof(*subdiv),
		sizeof(CvSubdiv2DPoint),
		sizeof(CvQuadEdge2D),
		storage);
	cvInitSubdivDelaunay2D(subdiv, rect);

	return subdiv;
}

//画出三角剖分的某一条边
inline void draw_edge(IplImage* img, CvSubdiv2DEdge edge, CvScalar color)
{
	CvSubdiv2DPoint* org_pt;//源顶点  
	CvSubdiv2DPoint* dst_pt;//目地顶点  
	CvPoint2D32f org;
	CvPoint2D32f dst;
	CvPoint iorg, idst;

	org_pt = cvSubdiv2DEdgeOrg(edge);//通过边获取顶点  
	dst_pt = cvSubdiv2DEdgeDst(edge);

	if (org_pt && dst_pt)//如果两个端点不为空  
	{
		org = org_pt->pt;
		dst = dst_pt->pt;

		iorg = cvPoint(cvRound(org.x), cvRound(org.y));
		idst = cvPoint(cvRound(dst.x), cvRound(dst.y));

		cvLine(img, iorg, idst, color, 1, CV_AA, 0);
	}
}

//画出Deluanary细分
void draw_delaunay(IplImage* img, CvSubdiv2D* subdiv, CvScalar delaunay_color)
{
	CvSeqReader  reader;
	int i, total = subdiv->edges->total;//边的数量  
	int elem_size = subdiv->edges->elem_size;//边的大小  

	cvStartReadSeq((CvSeq*)(subdiv->edges), &reader, 0);//使用CvSeqReader遍历Delaunay或者Voronoi边  

	for (i = 0; i < total; i++)
	{
		CvQuadEdge2D* edge = (CvQuadEdge2D*)(reader.ptr);
		//CvSubdiv2DEdge edge1 = (CvSubdiv2DEdge)(reader.ptr);  //这样赋值也可以,其实edge1和edge指向的是同一片内存，因为edge的最低2位是00，可以使用下面的方式验证
		//size_t t = (size_t)edge;size_t t1 = (size_t)edge1;if (t == t1) printf("edge1 == edge\n");

		if (CV_IS_SET_ELEM(edge))
		{
			draw_edge(img, (CvSubdiv2DEdge)edge, delaunay_color);
		}

		CV_NEXT_SEQ_ELEM(elem_size, reader);
	}

}


//画出voronoi面  
void draw_voronoi(CvSubdiv2D* subdiv, IplImage* img)
{
	CvSeqReader  reader;
	int i, total = subdiv->edges->total;//边缘总数  
	int elem_size = subdiv->edges->elem_size;//边缘的大小 

	cvStartReadSeq((CvSeq*)(subdiv->edges), &reader, 0);

	for (i = 0; i < total; i++)
	{
		CvQuadEdge2D* edge = (CvQuadEdge2D*)(reader.ptr);//获取四方边缘  

		if (CV_IS_SET_ELEM(edge))//判断边缘是否在边缘集中  
		{
			CvSubdiv2DEdge e = (CvSubdiv2DEdge)edge;//edge是四方边缘的指针，而CvSubdiv2DEdge高位表示四方边缘的指针。  
													//cout<<(e&3)<<endl;//通过测试e低2位即索引值应该设置为0了，即输入边缘  
													// left  逆时针遍历小区域
			draw_facet(img, cvSubdiv2DRotateEdge(e, 1));//e为Delaunay边，获得Delaunay边对应的voronoi边，即e的旋转边缘  

														// right  顺时针遍历小区域
														//draw_facet( img, cvSubdiv2DRotateEdge( e, 3 ));//反向的旋转边缘  
		}

		CV_NEXT_SEQ_ELEM(elem_size, reader);//移动到下一个位置  
	}
}


//画出voronoi中某点占有的小区域 
void draw_facet(IplImage* img, CvSubdiv2DEdge edge)
{
	//cout<<edge<<endl;//edge低两位表示表示索引，高位表示四方边缘指针。  
	//cout<<(edge&3)<<endl;  
	CvSubdiv2DEdge t = edge;//当我们按上面的调用形式时，edge为eRot。  
	int i, count = 0;
	CvPoint* buf = 0;
	Point2d *buf1 = 0;

	// count number of edges in facet //面内边的计数  
	do
	{
		count++;
		t = cvSubdiv2DGetEdge(t, CV_NEXT_AROUND_LEFT);
	} while (t != edge);//我们绕着一个voronoi单元一周，遍历该vornonoi边缘所拥有的边缘数。  

	buf = (CvPoint*)malloc(count * sizeof(buf[0]));
	buf1 = (Point2d*)malloc(count * sizeof(buf1[0]));

	// gather points  
	t = edge;
	for (i = 0; i < count; i++)
	{
		CvSubdiv2DPoint* pt = cvSubdiv2DEdgeOrg(t);//第一次获取eRot边缘的起始点  
		if (!pt) break;//如果得不到该源点，则退出循环  
		buf[i] = cvPoint(cvRound(pt->pt.x), cvRound(pt->pt.y));//将该点转换为cvPoint类型点，存储在buf中  
		t = cvSubdiv2DGetEdge(t, CV_NEXT_AROUND_LEFT);//然后绕着vornonoi单元，左旋转。  
	}

	if (i == count)//如果所有的点都存储起来了。  
	{
		CvSubdiv2DPoint* pt = cvSubdiv2DEdgeDst(cvSubdiv2DRotateEdge(edge, 1));//这里eRot的旋转边缘应该是reversed e,那么目的点，就是e的源点。  
		cvFillConvexPoly(img, buf, count, CV_RGB(rand() & 255, rand() & 255, rand() & 255), CV_AA, 0);//颜色随机填充凸多边形  
		for (i = 0; i<count; i++)
		{
			buf1[i].x = buf[i].x;
			buf1[i].y = buf[i].y;
		}
		Mat mat_img(img);

		cvPolyLine(img, &buf, &count, 1, 1, CV_RGB(0, 200, 0), 1, CV_AA, 0);//画出线。   
		draw_point(img, pt->pt, CV_RGB(255, 0, 0));//用红色画出画出剖分顶点。  
	}
	free(buf);
}

//定位给定点所在Delaunary三角型的三边,关键在于确定给定点与定位边的位置关系
void locate_pointInDelaunay(CvSubdiv2D* subdiv, CvPoint2D32f fp, IplImage* img,
	CvScalar active_color)
{
	CvSubdiv2DEdge e;
	CvSubdiv2DEdge e0 = 0;
	CvSubdiv2DPoint* p = NULL;

	CvSubdiv2DPoint* org_pt;//源顶点  
	CvSubdiv2DPoint* dst_pt;//目地顶点  
	CvPoint2D32f org;
	CvPoint2D32f dst;
	//CvPoint iorg, idst;

	cvSubdiv2DLocate(subdiv, fp, &e0, &p);    //定位点的位置

	org_pt = cvSubdiv2DEdgeOrg(e0);//通过边获取顶点  
	dst_pt = cvSubdiv2DEdgeDst(e0);
	if (org_pt && dst_pt)//如果两个端点不为空  
	{
		org = org_pt->pt;
		dst = dst_pt->pt;
		//  iorg = cvPoint( cvRound( org.x ), cvRound( org.y ));  
		//  idst = cvPoint( cvRound( dst.x ), cvRound( dst.y ));  
	}
	if (e0)
	{
		e = e0;
		do
		{
			draw_edge(img, e, active_color);
			e = cvSubdiv2DGetEdge(e, CV_NEXT_AROUND_RIGHT);
			cvSaveImage("i.jpg", img);
		} while (e != e0);
	}
	cvSaveImage("i.jpg", img);
	//draw_point( img, fp, active_color );  
}


void locate_pointInVoronoi(CvSubdiv2D* subdiv, CvPoint2D32f fp, IplImage* img, CvScalar color)
{
	CvSubdiv2DPoint* pt = cvFindNearestPoint2D(subdiv, fp);
	CvSubdiv2DEdge e = 0;
	CvSubdiv2DEdge e0 = 0;
	CvSubdiv2DPoint* p = NULL;
	CvSubdiv2DPoint* org_pt, *dst_pt;
	CvPoint2D32f org;
	CvPoint iorg;

	cvSubdiv2DLocate(subdiv, fp, &e0, &p);    //定位点的位置
	draw_facet(img, cvSubdiv2DRotateEdge(e0, 1));
	//*
	org_pt = cvSubdiv2DEdgeOrg(e0);
	org = org_pt->pt;
	iorg = cvPoint(cvRound(org.x), cvRound(org.y));

	if (e0)
	{
		e = e0;
		do
		{
			//  draw_edge( img, e, active_color );  
			e = cvSubdiv2DGetEdge(e, CV_NEXT_AROUND_LEFT);
		} while (e != e0);
	}


	/**/
}


//画出三角剖分的顶点
inline void draw_point(IplImage* img, CvPoint2D32f fp, CvScalar color)
{
	cvCircle(img, cvPoint(cvRound(fp.x), cvRound(fp.y)), 3, color, CV_FILLED, 8, 0);
}