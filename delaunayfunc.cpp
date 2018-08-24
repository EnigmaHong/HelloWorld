/* delaunayfunc.cpp */
#include "delaunayfunc.h"

//��ʼ����ʼ������
CvSubdiv2D* init_delaunay(CvMemStorage* storage, CvRect rect)
{
	CvSubdiv2D* subdiv;//�����ʷֵ����ݵ�Ԫ  

	subdiv = cvCreateSubdiv2D(CV_SEQ_KIND_SUBDIV2D, sizeof(*subdiv),
		sizeof(CvSubdiv2DPoint),
		sizeof(CvQuadEdge2D),
		storage);
	cvInitSubdivDelaunay2D(subdiv, rect);

	return subdiv;
}

//���������ʷֵ�ĳһ����
inline void draw_edge(IplImage* img, CvSubdiv2DEdge edge, CvScalar color)
{
	CvSubdiv2DPoint* org_pt;//Դ����  
	CvSubdiv2DPoint* dst_pt;//Ŀ�ض���  
	CvPoint2D32f org;
	CvPoint2D32f dst;
	CvPoint iorg, idst;

	org_pt = cvSubdiv2DEdgeOrg(edge);//ͨ���߻�ȡ����  
	dst_pt = cvSubdiv2DEdgeDst(edge);

	if (org_pt && dst_pt)//��������˵㲻Ϊ��  
	{
		org = org_pt->pt;
		dst = dst_pt->pt;

		iorg = cvPoint(cvRound(org.x), cvRound(org.y));
		idst = cvPoint(cvRound(dst.x), cvRound(dst.y));

		cvLine(img, iorg, idst, color, 1, CV_AA, 0);
	}
}

//����Deluanaryϸ��
void draw_delaunay(IplImage* img, CvSubdiv2D* subdiv, CvScalar delaunay_color)
{
	CvSeqReader  reader;
	int i, total = subdiv->edges->total;//�ߵ�����  
	int elem_size = subdiv->edges->elem_size;//�ߵĴ�С  

	cvStartReadSeq((CvSeq*)(subdiv->edges), &reader, 0);//ʹ��CvSeqReader����Delaunay����Voronoi��  

	for (i = 0; i < total; i++)
	{
		CvQuadEdge2D* edge = (CvQuadEdge2D*)(reader.ptr);
		//CvSubdiv2DEdge edge1 = (CvSubdiv2DEdge)(reader.ptr);  //������ֵҲ����,��ʵedge1��edgeָ�����ͬһƬ�ڴ棬��Ϊedge�����2λ��00������ʹ������ķ�ʽ��֤
		//size_t t = (size_t)edge;size_t t1 = (size_t)edge1;if (t == t1) printf("edge1 == edge\n");

		if (CV_IS_SET_ELEM(edge))
		{
			draw_edge(img, (CvSubdiv2DEdge)edge, delaunay_color);
		}

		CV_NEXT_SEQ_ELEM(elem_size, reader);
	}

}


//����voronoi��  
void draw_voronoi(CvSubdiv2D* subdiv, IplImage* img)
{
	CvSeqReader  reader;
	int i, total = subdiv->edges->total;//��Ե����  
	int elem_size = subdiv->edges->elem_size;//��Ե�Ĵ�С 

	cvStartReadSeq((CvSeq*)(subdiv->edges), &reader, 0);

	for (i = 0; i < total; i++)
	{
		CvQuadEdge2D* edge = (CvQuadEdge2D*)(reader.ptr);//��ȡ�ķ���Ե  

		if (CV_IS_SET_ELEM(edge))//�жϱ�Ե�Ƿ��ڱ�Ե����  
		{
			CvSubdiv2DEdge e = (CvSubdiv2DEdge)edge;//edge���ķ���Ե��ָ�룬��CvSubdiv2DEdge��λ��ʾ�ķ���Ե��ָ�롣  
													//cout<<(e&3)<<endl;//ͨ������e��2λ������ֵӦ������Ϊ0�ˣ��������Ե  
													// left  ��ʱ�����С����
			draw_facet(img, cvSubdiv2DRotateEdge(e, 1));//eΪDelaunay�ߣ����Delaunay�߶�Ӧ��voronoi�ߣ���e����ת��Ե  

														// right  ˳ʱ�����С����
														//draw_facet( img, cvSubdiv2DRotateEdge( e, 3 ));//�������ת��Ե  
		}

		CV_NEXT_SEQ_ELEM(elem_size, reader);//�ƶ�����һ��λ��  
	}
}


//����voronoi��ĳ��ռ�е�С���� 
void draw_facet(IplImage* img, CvSubdiv2DEdge edge)
{
	//cout<<edge<<endl;//edge����λ��ʾ��ʾ��������λ��ʾ�ķ���Եָ�롣  
	//cout<<(edge&3)<<endl;  
	CvSubdiv2DEdge t = edge;//�����ǰ�����ĵ�����ʽʱ��edgeΪeRot��  
	int i, count = 0;
	CvPoint* buf = 0;
	Point2d *buf1 = 0;

	// count number of edges in facet //���ڱߵļ���  
	do
	{
		count++;
		t = cvSubdiv2DGetEdge(t, CV_NEXT_AROUND_LEFT);
	} while (t != edge);//��������һ��voronoi��Ԫһ�ܣ�������vornonoi��Ե��ӵ�еı�Ե����  

	buf = (CvPoint*)malloc(count * sizeof(buf[0]));
	buf1 = (Point2d*)malloc(count * sizeof(buf1[0]));

	// gather points  
	t = edge;
	for (i = 0; i < count; i++)
	{
		CvSubdiv2DPoint* pt = cvSubdiv2DEdgeOrg(t);//��һ�λ�ȡeRot��Ե����ʼ��  
		if (!pt) break;//����ò�����Դ�㣬���˳�ѭ��  
		buf[i] = cvPoint(cvRound(pt->pt.x), cvRound(pt->pt.y));//���õ�ת��ΪcvPoint���͵㣬�洢��buf��  
		t = cvSubdiv2DGetEdge(t, CV_NEXT_AROUND_LEFT);//Ȼ������vornonoi��Ԫ������ת��  
	}

	if (i == count)//������еĵ㶼�洢�����ˡ�  
	{
		CvSubdiv2DPoint* pt = cvSubdiv2DEdgeDst(cvSubdiv2DRotateEdge(edge, 1));//����eRot����ת��ԵӦ����reversed e,��ôĿ�ĵ㣬����e��Դ�㡣  
		cvFillConvexPoly(img, buf, count, CV_RGB(rand() & 255, rand() & 255, rand() & 255), CV_AA, 0);//��ɫ������͹�����  
		for (i = 0; i<count; i++)
		{
			buf1[i].x = buf[i].x;
			buf1[i].y = buf[i].y;
		}
		Mat mat_img(img);

		cvPolyLine(img, &buf, &count, 1, 1, CV_RGB(0, 200, 0), 1, CV_AA, 0);//�����ߡ�   
		draw_point(img, pt->pt, CV_RGB(255, 0, 0));//�ú�ɫ���������ʷֶ��㡣  
	}
	free(buf);
}

//��λ����������Delaunary�����͵�����,�ؼ�����ȷ���������붨λ�ߵ�λ�ù�ϵ
void locate_pointInDelaunay(CvSubdiv2D* subdiv, CvPoint2D32f fp, IplImage* img,
	CvScalar active_color)
{
	CvSubdiv2DEdge e;
	CvSubdiv2DEdge e0 = 0;
	CvSubdiv2DPoint* p = NULL;

	CvSubdiv2DPoint* org_pt;//Դ����  
	CvSubdiv2DPoint* dst_pt;//Ŀ�ض���  
	CvPoint2D32f org;
	CvPoint2D32f dst;
	//CvPoint iorg, idst;

	cvSubdiv2DLocate(subdiv, fp, &e0, &p);    //��λ���λ��

	org_pt = cvSubdiv2DEdgeOrg(e0);//ͨ���߻�ȡ����  
	dst_pt = cvSubdiv2DEdgeDst(e0);
	if (org_pt && dst_pt)//��������˵㲻Ϊ��  
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

	cvSubdiv2DLocate(subdiv, fp, &e0, &p);    //��λ���λ��
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


//���������ʷֵĶ���
inline void draw_point(IplImage* img, CvPoint2D32f fp, CvScalar color)
{
	cvCircle(img, cvPoint(cvRound(fp.x), cvRound(fp.y)), 3, color, CV_FILLED, 8, 0);
}