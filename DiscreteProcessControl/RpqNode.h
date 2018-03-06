#pragma once
class RpqNode
{
public:
	RpqNode();
	RpqNode(int r, int p, int q);
	~RpqNode();

	int getR() const { return _r; }
	void setR(const int r) { _r = r; }

	int getP() const { return _p; }
	void setP(const int p) { _p = p; }

	int getQ() const { return _q; }
	void setQ(const int q) { _q = q; }

private:
	int _r;
	int _p;
	int _q;
};

