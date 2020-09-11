#include <functional>
#include <iostream>
#include <map>

double SIN(double x)
{
	return sin(x);
}

double COS(double x)
{
	return cos(x);
}

double SQUARE_X(double x)
{
	return x*x;
}

double X(double x)
{
	return x;
}

int Start()
{
	int ch;
	while (true)
	{
		std::cout << "Select function to integrate: \n";
		std::cout << "1) sin(x)\n2) cos(x)\n3) x^2\n4) x\n5) quit\n\t\t";
		std::cin >> ch;
		switch (ch)
		{
		case 5:
			return 0;
		case 1 :
		case 2:
		case 3:
		case 4:
			return ch;
//			break;
		default:
			std::cout << "Oops, something went wrong, try again\n";
			break;
		}
	}
}

std::pair<double, double> Span()
{
	std::pair<double, double> span;
	while (true)
	{
		std::cout << "Enter the start and end of the line\n";
		std::cout << "from: \t\t";
		std::cin >> span.first;
		std::cout << "to: \t\t";
		std::cin >> span.second;

		if (span.first >= span.second)
		{
			while (true)
			{
				int ch;
				std::cout << "Oops, something went wrong\nDo you want:\n1)Try again\n2)To the start\n3)Quit\n\t\t";
				std::cin >> ch;
				switch (ch)
				{
				case 1:
					break;
				case 2:
					return std::make_pair(0, 0);
				case 3:
					return std::make_pair(-1, -1);
				default:
					std::cout << "Oops, something went wrong, try again\n";
					break;
				}
				if (ch == 1) break;
			}
		}
		else
			return span;
	}
}

double Step()
{
	double step;
	while (true)
	{
		std::cout << "Enter integration step\n\t\t";
		std::cin >> step;
		if (step <= 0)
		{
			while (true)
			{
				int ch;
				std::cout << "Oops, something went wrong\nDo you want:\n1)Try again\n2)To the start\n3)Quit\n\t\t";
				std::cin >> ch;
				switch (ch)
				{
				case 1:
					break;
				case 2:
					return 0;
				case 3:
					return -1;
				default:
					std::cout << "Oops, something went wrong, try again\n";
					break;
				}
				if (ch == 1) break;
			}
		}
		else
		    return step;
	}
}

int Method()
{
	int m;
	while (true)
	{
		std::cout << "Choose the integration method\n1)Bars\n2)Trapeze\n\t\t";
		std::cin >> m;
		if (m <= 0 || m >= 3)
		{
			while (true)
			{
				int ch;
				std::cout << "Oops, something went wrong\nDo you want:\n1)Try again\n2)To the start\n3)Quit\n\t\t";
				std::cin >> ch;
				switch (ch)
				{
				case 1:
					break;
				case 2:
					return 0;
				case 3:
					return -1;
				default:
					std::cout << "Oops, something went wrong, try again\n";
					break;
				}
				if (ch == 1) break;
			}
		}
		else
			return m;
	}
}

double Bars_Integration(std::function<double(double) > f, double begin, double end, double step)
{
	double res = 0., span_end = begin + step;

	while (span_end <= end)
	{
		res += f(begin + step * 0.5) * step;
		begin = span_end;
		span_end += step;
	}
	if (span_end > end)
	{
		res += f(begin + (end - begin) * 0.5) * (end - begin);
	}

	std::cout << res << '\n';
	return res;
}

double Trapeze_Integration(std::function<double(double) > f, double begin, double end, double step)
{
	double res = 0., span_end = begin + step;

	while (span_end <= end)
	{
		res += (f(begin) + f(span_end)) * 0.5 * step;
		begin = span_end;
		span_end += step;
	}
	if (span_end > end)
	{
		res += (f(begin) + f(end)) * 0.5 * (end - begin);
	}

	std::cout << res << '\n';
	return res;
}


int main()
{
	double x;
	std::map<int, std::function<double(double)>> Functions;
	Functions[1] = SIN;
	Functions[2] = COS;
	Functions[3] = SQUARE_X;
	Functions[4] = X;

	int k = Start();
	std::pair<double, double> span = std::make_pair(0, 0);
	double step = 0;
	int M = -2;
	while (k > 0)
	{
		span = Span();
		
		if (span.first != span.second)
		{
			step = Step();
			if (step == -1) break;
			if (step > 0)
			{
				M = Method();
				if (M == -1) break;
				if (M == 1)
					Bars_Integration(Functions[k], span.first, span.second, step);
				if (M == 2)
					Trapeze_Integration(Functions[k], span.first, span.second, step);
			}

		}
		else
			if (span.first == -1) break;

		if (M == 1 || M == 2)
		{
			while (true)
			{
				std::cout << "Do you want continue?\n1)Yes\n2)No\n\t\t";
				std::cin >> k;
				if (k != 2 && k != 1)
					std::cout << "I didn't catch...\n";
				else
					break;
			}
		}
		if (k == 1 || M == 0 || step == 0 || (span.first == 0 && span.second == 0))
			k = Start();
		else
			break;
	}

	std::cout << "END\n";
	return 0;
}