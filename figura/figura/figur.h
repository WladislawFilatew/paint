#pragma once
#include <iostream>
#include <string>
#include <vector>
#define M_PI 3.14159265358979323846
using namespace std;
namespace mcf {
	using namespace System;
	using namespace System::Drawing;
	using namespace System::Drawing::Drawing2D;
	using namespace System::Collections::Generic;
	ref class figure
	{
	public:
		bool flag = false;
	protected:
		int x, y;
		//string name = "figure";
		Pen^ pen;
		Brush^ brush;
		Graphics^ g;
	public:
		figure(Graphics^ g) {
			this->g = g;
			pen = gcnew Pen(Color::Black);
			brush = gcnew SolidBrush(Color::Black);
		}
		void Set_color(Color color) { brush = gcnew SolidBrush(color); }
		virtual double S() = 0;
		virtual double P() = 0;
		int Get_x() { return x; }
		int Get_y() { return y; }
		virtual int Get_px() = 0;
		virtual int Get_ny() = 0;
		virtual void Show() = 0;
		virtual void Hide() = 0;
		virtual void go(int x, int y) {
			Hide();
			this->x += x;
			this->y += y;
			Show();
		}
		virtual bool clic(int x, int y) = 0;
		virtual void iz_razmer(int a, int b) = 0;
		virtual bool contur(int x, int y) = 0;
		bool rebro_izm(int x, int y) {
			if (Get_px() * 0.99 <= x && x <= Get_px() * 1.01)
				if (Get_ny() * 0.99 <= y && y <= Get_ny() * 1.01)
					return true;
			return false;
		}
		//void what() { cout << name << endl; }
	};
	ref class point: public figure {
	public:
		point(Graphics^ g, int x, int y):figure(g) {
			this->x = x;
			this->y = y;
			//name = "point";
		}
		double S() override { return 0; }
		double P() override { return 0; }
		int Get_px() override { return x; }
		int Get_ny() override { return y; }
		void Show() override {
			g->DrawRectangle(pen,x, y, 1 ,1);
		}
		void Hide() override {
			Pen^ redPen = gcnew Pen(Color::White);
			g->DrawRectangle(redPen, x, y,1,1);
		}
		bool clic(int x, int y) override {
			if (this->x == x && this->y == y) return true;
			return false;
		}
		bool contur(int x, int y) override {
			if (this->x == x && this->y == y) return true;
			return false;
		}
		void iz_razmer(int a, int b) override { ; }
	};
	ref class line : public figure {
	protected:
		int a;
		int b;
	public:
		line(Graphics^ g,int x, int y,int a):figure(g) {
			this->x = x;
			this->y = y;
			this->a = a;
			this->b = 0;
			//name = "point";
		}
		double S() override { return 0; }
		double P() override { return a; }
		int Get_px() override { return x + a; }
		int Get_ny() override { return y + b; }
		void Show() override {
			g->DrawLine(pen, x, y, x + a, y + b);
		}
		void Hide() override {
			Pen^ redPen = gcnew Pen(Color::White);
			g->DrawLine(redPen, x, y, x + a, y + b);
		}
		bool clic(int x, int y)override {
			if (this->y != y) return false;
			if (this->x <= x && Get_px() >= x) return true;
			return false;
		}
		void iz_razmer(int a, int b) override {
			Hide();
			this->a = a;
			this->b = b;
			Show();
		}
		bool contur(int x, int y) override {
			double k = (double)b / a;
			double smes = this->y - k * this->x;
			if (y * 0.99 <= k * x + smes && k * x + smes <= y * 1.01) return true;
			return false;
		}
	};
	ref class rectagle :public figure {
	protected:
		int a, b;
	public:
		rectagle(Graphics^ g, int x, int y, int a, int b):figure(g) {
			this->x = x;
			this->y = y;
			this->a = a;
			this->b = b;
			//name = "rectagle";
		}
		double S() override { return a * b; }
		double P() override { return (a + b) * 2; }
		int Get_px() override { return x + b; }
		int Get_ny() override { return y + a; }
		void Show() override {
			if (flag) g->FillRectangle(brush, x, y, b, a);
			g->DrawRectangle(pen, x, y, b, a);
		}
		void Hide() override {
			Pen^ redPen = gcnew Pen(Color::White);
			Brush^ br = gcnew SolidBrush(Color::White);
			if (flag) g->FillRectangle(br, x, y, b, a);
			g->DrawRectangle(redPen, x, y, b, a);
		}
		bool clic(int x, int y) override {
			if (x < this->x || x > Get_px()) return false;
			if (y < this->y || y > Get_ny()) return false;
			return true;
		}
		void iz_razmer(int a, int b) override {
			Hide();
			this->a = a;
			this->b = b;
			Show();
		}

		bool contur(int x, int y) override {
			if (this->x <= x && x <= Get_px()) {
				if (0.99 * this->y <= y && y <= this->y * 1.01) return true;
				if (0.99 * Get_ny() <= y && y <= Get_ny() * 1.01) return true;
			}
			if (this->y <= y && y <= Get_ny()) {
				if (0.99 * this->x <= x && x <= this->x * 1.01) return true;
				if (0.99 * Get_px() <= x && x <= Get_px() * 1.01) return true;
			}
			return false;
		}
	};
	ref class kvadrat :public rectagle {
	public:
		kvadrat(Graphics^ g, int x, int y, int a) :rectagle(g,x, y, a, a) { /*name = "kvadrat"; */}
	};
	ref class elips : public figure {
	protected:
		int a, b;
	public:
		elips(Graphics^ g,int x, int y, int a, int b):figure(g) {
			this->x = x;
			this->y = y;
			this->a = a;
			this->b = b;
			//name = "elips";
		}
		double S()override { return M_PI * a * b; }
		double P()override { return 2 * M_PI * sqrt((a * a + b * b) / 2); }
		int Get_px() override { return x + b; }
		int Get_ny() override { return y + a; }
		void Show() override {
			if (flag) g->FillEllipse(brush, x, y, b, a);
			g->DrawEllipse(pen, x, y, b, a);
		}
		void Hide() override {
			Pen^ redPen = gcnew Pen(Color::White);
			Brush^ br = gcnew SolidBrush(Color::White);
			if (flag) g->FillEllipse(br, x, y, b, a);
			g->DrawEllipse(redPen, x, y, b, a);
		}
		bool clic(int x, int y) override {
			double dt = pow((x - (this->x + (b / 2))), 2) / pow((b/2),2) + pow((y - (this->y + (a / 2))), 2) / pow((a /2),2);
			if (dt <= 1) return true;
			return false;
		}
		void iz_razmer(int a, int b) override {
			Hide();
			this->a = a;
			this->b = b;
			Show();
		}

		bool contur(int x, int y) override {
			double dt = pow((x - (this->x + (b / 2))), 2) / pow((b / 2), 2) + pow((y - (this->y + (a / 2))), 2) / pow((a / 2), 2);
			if (0.90 <= dt && dt <= 1.10) return true;
			return false;
		}
	};
	ref class crug :public elips {
	public:
		crug(Graphics^ g, int x, int y, int a) :elips(g, x, y, a, a) {/* name = "crug";*/ }
	};
	ref class treugl : public figure {
	protected:
		int sx;
		int a, b;
	public:
		treugl(Graphics^ g,int x, int y, int sx, int a, int b):figure(g) {
			this->x = x;
			this->y = y;
			this->sx = x + sx;
			this->a = a;
			this->b = b;
			//name = "treugl";
		}
		double S()override {
			double S = a * b;
			S -= (a * (sx - x)) / 2;
			S -= (a * (Get_px() - sx)) / 2;
			return S;
		}
		double P()override {
			double P = b;
			P += sqrt(a * a + (sx - x) * (sx - x));
			P += sqrt(a * a + (Get_px() - sx) * (Get_px() - sx));
			return P;
		}
		int Get_px() override { return x + b; }
		int Get_sx() { return sx; }
		int Get_ny() override { return y + a; }
		void Show() override {
			GraphicsPath^ gp = gcnew GraphicsPath();
			gp->AddLine(Point(x, Get_ny()), Point(sx, y));
			gp->AddLine(Point(sx, y), Point(Get_px(),Get_ny()));
			gp->AddLine(Point(x, Get_ny()), Point(Get_px(), Get_ny()));
			if (flag) g->FillPath(brush, gp);
			g->DrawPath(pen,gp);
		}
		void Hide() override {
			Pen^ redPen = gcnew Pen(Color::White);
			GraphicsPath^ gp = gcnew GraphicsPath();
			gp->AddLine(Point(x, Get_ny()), Point(sx, y));
			gp->AddLine(Point(sx, y), Point(Get_px(), Get_ny()));
			gp->AddLine(Point(x, Get_ny()), Point(Get_px(), Get_ny()));
			Brush^ br = gcnew SolidBrush(Color::White);
			if (flag) g->FillPath(br, gp);
			g->DrawPath(redPen, gp);
		}
		void go(int x, int y) override{
			Hide();
			this->x += x;
			this->y += y;
			this->sx += x;
			Show();
		}
		double S_T(vector<int> X, vector<int> Y) {
			double S = 0;
			for (int k = 1; k <= 3; k++) {
				S += (Y[k % 3] + Y[k - 1]) / 2 * (X[k % 3] - X[k - 1]);
			}
			return abs(S);
		}
		bool clic(int x, int y)override {
			vector<int> X, Y;
			int S = 0;
			X.push_back(x); X.push_back(Get_x()); X.push_back(Get_sx());
			Y.push_back(y); Y.push_back(Get_ny()); Y.push_back(Get_y());
			S += S_T(X, Y);
			X.pop_back(); X.push_back(Get_px());
			Y.pop_back(); Y.push_back(Get_ny());
			S += S_T(X, Y);
			X.erase(X.begin() + 1); X.push_back(Get_sx());
			Y.erase(Y.begin() + 1); Y.push_back(Get_y());
			S += S_T(X, Y);
			if (this->S() * 0.90 <= S && S <= this->S() * 1.10) return true;
			return false;
		}
		void iz_razmer(int a, int b) override{
			Hide();
			this->a = a;
			this->b = b;
			this->sx = (x + b / 2);
			Show();
		}

		bool contur(int x, int y) override {
			if (this->x <= x && x <= Get_px()) {
				if (0.99 * Get_ny() <= y && y <= Get_ny() * 1.01) return true;
			}
			return false;
		}
	};
	ref class RavnBedr :public treugl {
	public:
		RavnBedr(Graphics^ g, int x, int y, int a, int b) : treugl(g, x, y, x + (b / 2), a, b) { /*name = "RavnBedr";*/ }
	};
	ref class RavnStor : public RavnBedr {
	public:
		RavnStor(Graphics^ g, int x, int y, int a) : RavnBedr(g, x, y, a, a) { /*name = "RavnStor";*/ }
	};


	ref class mno : public figure {
	protected:
		List<Point> arr;
	public:
		mno(Graphics^ g, int x, int y) :figure(g) {
			this->x = x;
			this->y = y;
			arr.Add(Point(x, y));
			//name = "mnoug";
		}
		void Add(int x, int y) {
			arr.Add(Point(x, y));
		}
		double S()override {
			double S = 0;
			for (int k = 1; k <= arr.Count; k++) {
				S += (arr[k % arr.Count].Y + arr[k - 1].Y) / 2 * (arr[k % arr.Count].X - arr[k - 1].X);
			}
			return abs(S);
		}
		double P()override {
			double P = 0;
			for (int k = 1; k <= arr.Count; k++) {
				P += sqrt(abs(pow((arr[k % arr.Count].Y - arr[k - 1].Y),2) + pow((arr[k % arr.Count].X - arr[k - 1].X),2)));
			}
			return abs(P);
		}
		int Min(int a, int b) {
			if (a < b) return a;
			return b;
		}
		int Max(int a, int b) {
			if (a > b) return a;
			return b;
		}
		int Get_px() override {
			int max_x = 0;
			for (int i = 0; i < arr.Count; i++) 
				max_x = Max(max_x, arr[i].X);
			return max_x; 
		}
		int Get_ny() override {
			int max_y = 0;
			for (int i = 0; i < arr.Count; i++)
				max_y = Max(max_y, arr[i].X);
			return max_y;
		}
		void Show() override {
			GraphicsPath^ gp = gcnew GraphicsPath();
			for (int i = 1; i <= arr.Count; i++)
				gp->AddLine(arr[i % arr.Count], arr[i - 1]);
			if (flag) g->FillPath(brush, gp);
			g->DrawPath(pen, gp);
		}
		void Hide() override {
			Pen^ redPen = gcnew Pen(Color::White);
			GraphicsPath^ gp = gcnew GraphicsPath();
			for (int i = 1; i <= arr.Count; i++)
				gp->AddLine(arr[i % arr.Count], arr[i - 1]);
			if (flag) g->FillPath(brush, gp);
			Brush^ br = gcnew SolidBrush(Color::White);
			if (flag) g->FillPath(br, gp);
			g->DrawPath(redPen, gp);
		}
		void go(int x, int y) override {
			Hide();
			for (int i = 0; i < arr.Count; i++) {
				arr[i] = Point(arr[i].X + x, arr[i].Y + y);
			}	
			Show();
		}
		double S_T(vector<int> X, vector<int> Y) {
			double S = 0;
			for (int k = 1; k <= 3; k++) {
				S += (Y[k % 3] + Y[k - 1]) / 2 * (X[k % 3] - X[k - 1]);
			}
			return abs(S);
		}
		bool clic(int x, int y)override {
			vector<int> X, Y;
			int S = 0;
			for (int i = 1; i <= arr.Count; i++) {
				X.push_back(x); Y.push_back(y);
				X.push_back(arr[i - 1].X); Y.push_back(arr[i - 1].Y);
				X.push_back(arr[i % arr.Count].X); Y.push_back(arr[i % arr.Count].Y);
				S += S_T(X, Y);
				X.clear(); Y.clear();
			}
			if (this->S() * 0.90 <= S && S <= this->S() * 1.10) return true;
			return false;
		}
		void iz_razmer(int a, int b) override { ; }

		bool contur(int x, int y) override {
			for (int i = 0;i < arr.Count;i++)
				if (arr[i].X * 0.99 <= x && x <= arr[i].X * 1.01) {
					if (arr[i].Y * 0.99 <= y && y <= arr[i].Y * 1.01) return true;
				}
			return false;
		}
	};
}