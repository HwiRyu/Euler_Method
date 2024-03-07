#ifndef EULER_METHOD_EULER_METHOD_H
#define EULER_METHOD_EULER_METHOD_H

//Input Differential function. Find approximate solution.
double differential_function(double x, double y) {
    //differential_function is f(x,y(t)). i.e dy/dx = f(x, y(x)).
    //Ex) If origin function is tan(x), then dy/dx = f(x,y(x)) = 1+y^2.
    return x;
}

double twice_differential_function(double x, double y) {
    return y;
}

void EulerMethod(sf::RenderWindow &window, sf::VertexArray &graph, double startX, double startY, double stepSize,
                 double size, double input_function(double, double), double start, double end) {
    double y = startY;
    graph.clear();

    for (double x = startX; x <= end / size; x += stepSize) {
        if (x_scale(x, size) >= start)
            graph.append(sf::Vertex(sf::Vector2f(x_scale(x, size), y_scale(y, size)), sf::Color::Red));
        double dydx = input_function(x, y);
        y += dydx * stepSize;
    }
    window.draw(graph);
}

int Calculate_error(double start, double end, double stepSize) {
    int domain_range = floor((end - start) / stepSize);
    return std::max(domain_range, 0);
}

double reminder(double h, double x){
    double rem = 0;
    double fac;
    for (int i = 0; i < 100; i+=1) {
        fac = 1;
        for (int k = 1; k <= i+1; k+=1) {
            fac *= k;
        }
        rem += pow(h,i+1)*1 / fac;
    }
    return rem;
}

double Error_size(int large_n(double, double, double),
                  double start, double end, double stepSize,
                  double reminder(double, double)) {
    double L = 1; // 더 정확한 자연상수 e 사용
    int large_N = large_n(start, end, stepSize);
    double error = 0;

    for (int i = 0; i <= large_N - 1; i += 1) {
        error += reminder(stepSize, start + stepSize * i) * pow(1 + stepSize * L, i);
    }
    return error;
}


#endif //EULER_METHOD_EULER_METHOD_H
