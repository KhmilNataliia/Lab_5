using System;
using System.Collections.Generic;
using System.Collections;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using Emgu.CV;
using Emgu.CV.CvEnum;
using Emgu.CV.Structure;
using Emgu.CV.UI;
using Emgu.CV.Util;

namespace shtrih_code
{
    public partial class Form1 : Form
    {
        string filename = "";
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        public Mat redact_img(Mat source, bool by_x)
        {
            Size size=new System.Drawing.Size(source.Width, source.Height);
            Mat gray_img = new Mat();
            CvInvoke.CvtColor(source, gray_img, ColorConversion.Bgr2Gray);
            Mat grad_by_x = new Mat();
            Mat grad_by_y = new Mat();
            
            CvInvoke.Sobel(gray_img, grad_by_x, DepthType.Cv32F, 1, 0 ,3);
            CvInvoke.Sobel(gray_img, grad_by_y, DepthType.Cv32F, 0, 1, 3);
            CvInvoke.ConvertScaleAbs(grad_by_x, grad_by_x, 3, 3);
            CvInvoke.ConvertScaleAbs(grad_by_y, grad_by_y, 3, 3);
            Mat res_gradient = new Mat();
            if(by_x)
            CvInvoke.Subtract(grad_by_x,grad_by_y,res_gradient);
            else CvInvoke.Subtract(grad_by_y, grad_by_x, res_gradient);
            CvInvoke.ConvertScaleAbs(res_gradient, res_gradient,3,3);

            CvInvoke.GaussianBlur(res_gradient, res_gradient, new Size(7, 7), 0);

            CvInvoke.Threshold(res_gradient, res_gradient, 100, 255, ThresholdType.Binary);

            CvInvoke.Erode(res_gradient, res_gradient, null, new Point(-1, -1), 7, BorderType.Default, new MCvScalar(1));
            CvInvoke.Dilate(res_gradient, res_gradient, null, new Point(-1, -1), 10, BorderType.Default, new MCvScalar(1));

            return res_gradient;
        }

        public Rectangle find_rect(Mat img)
        {
            VectorOfVectorOfPoint contours=new VectorOfVectorOfPoint();
            Mat copy = new Mat(); img.CopyTo(copy);
            CvInvoke.FindContours(copy, contours, null, RetrType.List, ChainApproxMethod.ChainApproxSimple);
            ArrayList rects = new ArrayList();
            for(int i=0;i<contours.Size;i++)
            {
                RotatedRect temp = new RotatedRect();
                Rectangle t = new Rectangle();
                temp =  CvInvoke.MinAreaRect(contours[i]);
                t = temp.MinAreaRect();
                rects.Add(t);
                
            }
            Rectangle max =new Rectangle();
            if(rects.Count>0)   max=(Rectangle)rects[0];
            for(int i=1;i<rects.Count;i++)
            {
                Rectangle temp=new Rectangle(); temp=(Rectangle)rects[i];
                if (max.Height * max.Width < temp.Width * temp.Height)
                    max = temp;
            }
            return max;
        }

        public Rectangle find_bar_code(Mat img)
        {
            Rectangle r1 = new Rectangle();
            Rectangle r2 = new Rectangle();
            Mat filt = new Mat();
            filt = redact_img(img, true);
            r1 = find_rect(filt);
            filt = redact_img(img, false);
            r2 = find_rect(filt);
            if (r1.Height * r1.Width > r2.Width * r2.Height)
                return r1;
            else return r2;
        }

        private void imageBox1_Click(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            openFileDialog1.ShowDialog();
            filename = openFileDialog1.FileName;
            Mat image = new Mat(filename);
            Rectangle rect = new Rectangle();
            rect = find_bar_code(image);
            CvInvoke.Rectangle(image, rect, new MCvScalar(0, 255, 0), 3);
            imageBox1.Image = image.ToImage<Bgr,Byte>();
        }
    }
}
