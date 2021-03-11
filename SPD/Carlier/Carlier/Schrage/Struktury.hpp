#ifndef STRUKTURY_SCHRAGE_HPP
#define STRUKTURY_SCHRAGE_HPP

struct Element 
{
	int R;
	int P;
	int Q;
	int index;
};

class Output
{
	public:
		int dlugosc;
		vector<int> permutacja;
};

bool min_r(const Element& l, const Element& r) // Asceding order
{
	return l.R > r.R;
}

bool max_q(const Element& l, const Element& r) // Desceding order
{
	return l.Q < r.Q;
}

#endif
