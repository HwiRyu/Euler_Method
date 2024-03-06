#ifndef EULER_METHOD_EULER_METHOD_H
#define EULER_METHOD_EULER_METHOD_H

//Input Differential function. Find approximate solution.
double differential_function(double x, double y) {
    //differential_function is f(x,y(t)). i.e dy/dx = f(x, y(x)).
    //Ex) If origin function is tan(x), then dy/dx = f(x,y(x)) = 1+y^2.
    return 1 / x;
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


#endif //EULER_METHOD_EULER_METHOD_H
