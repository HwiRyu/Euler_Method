#ifndef EULER_METHOD_EULER_METHOD_H
#define EULER_METHOD_EULER_METHOD_H

//Input Differential function. Find approximate solution.
double differential_function(double x, double y, int number) {
    double t;
    switch (number) {
        case 1:
            t = y*y*(y*y-4);
            break;
        case 2:
            t = y*(1-y);
            break;
        case 3:
            t = y*(2-y);
            break;
        case 4:
            t = y*(1-2*y);
            break;
        case 5:
            t = y*(0-y);
            break;
        case 6:
            t = y/(1+x*x);
            break;
        case 7:
            t = exp(sin(x));
            break;
        case 8:
            t = exp(-y*y);
            break;
    }
    return t;
}

void EulerMethod(sf::RenderWindow &window, sf::VertexArray &graph, double startX, double startY, double stepSize,
                 double size, double input_function(double, double, int), double start, double end, int number) {
    double y = startY;
    graph.clear();

    for (double x = startX; x <= end / size; x += stepSize) {
        if (x_scale(x, size) >= start)
            graph.append(sf::Vertex(sf::Vector2f(x_scale(x, size), y_scale(y, size)), sf::Color::Red));
        double dydx = input_function(x, y, number);
        y += dydx * stepSize;
    }
    window.draw(graph);
}

double second_ode(double x, double y, double diff_y) {
    double f_x_y = x;
    return f_x_y;
}


void second_EulerMethod(sf::RenderWindow &window, sf::VertexArray &graph, double startX, double startY, double start_diff_Y ,double stepSize,
                 double size, double input_function(double, double, double), double start, double end, int number) {
    double y = startY;
    double diff_y  = start_diff_Y;
    graph.clear();

    for (double x = startX; x <= end / size; x += stepSize) {
        if (x_scale(x, size) >= start)
            graph.append(sf::Vertex(sf::Vector2f(x_scale(x, size), y_scale(y, size)), sf::Color::Green));
        diff_y += stepSize * input_function(x, y, diff_y);
        y += stepSize*diff_y;
    }

    window.draw(graph);
}


int Calculate_error(double start, double end, double stepSize) {
    int domain_range = floor((end - start) / stepSize);
    return std::max(domain_range, 0);
}

double Error_size(double start, double end, double stepSize,
                  double differential_function(double, double, int),
                  int number) {
    double error = 0;
    double origin;

    for (double x = start; x <= end; x += stepSize) {
        double temporary_error = 0;
        for (double i = x; i <= x + stepSize; i += stepSize / 100) {
            double current_error = std::abs(differential_function(x, 0, number) - differential_function(i, 0, number));
            if (temporary_error < current_error) {
                temporary_error = current_error;
            }
        }
        error += temporary_error;
    }
    return error * stepSize;
}


#endif //EULER_METHOD_EULER_METHOD_H
