#ifndef EULER_METHOD_EULER_METHOD_H
#define EULER_METHOD_EULER_METHOD_H

//Input Differential function. Find approximate solution.
double differential_function(double x, double y) {
    return exp(-x*x)+ y;
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

double Error_size(double start, double end, double stepSize,
                  double differential_function(double, double),
                  double size) {
    double error = 0;
    double origin;

    for (double x = start; x <= end; x += stepSize) {
        double temporary_error = 0;
        for (double i = x; i <= x + stepSize; i += stepSize / 100) {
            double current_error = std::abs(differential_function(x, 0) - differential_function(i, 0));
            if (temporary_error < current_error) {
                temporary_error = current_error;
            }
        }
        error += temporary_error;
    }
    return error * stepSize;
}


#endif //EULER_METHOD_EULER_METHOD_H
