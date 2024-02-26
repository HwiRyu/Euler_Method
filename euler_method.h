#ifndef EULER_METHOD_EULER_METHOD_H
#define EULER_METHOD_EULER_METHOD_H

struct Point {
    double x;
    double y;
};

//Input one variable functoin, like y = sin(x).
double one_variable_function(double x) {
    return pow(x, 2) - 2 * abs(x) - 8;
}

//Input Differential function. Find approximate solution.
double differential_function(double x, double y) {
    //differential_function is f(x,y(t)). i.e dy/dx = f(x, y(x)).
    //Ex) If origin function is tan(x), then dy/dx = f(x,y(x)) = 1+y^2.
    return sin(x) * (pow(y, 2) - 4 * pow(y, 1));
}

//Input parameter function, like x = f(t), y = g(t).
Point parameter_function(double t) {
    Point output;
    output.x = sin(4*t) * (std::exp(cos(1/2*t)) - 2 * cos(18*t) - pow(sin(1/12), 5));
    output.y = cos(5*t) * (std::exp(cos(1/3*t)) - 2 * cos(11*t) - pow(sin(1/12), 5));
    return output;
}

void origin_function_one(sf::RenderWindow& window, sf::VertexArray& graph, double size, double one_variable_input_function(double), double start, double end) {
    graph.clear();
    for (double x = start/size; x <= end/size; x += 0.001) {
        double y = one_variable_input_function(x);
        graph.append(sf::Vertex(sf::Vector2f(x_scale(x, size), y_scale(y, size)), sf::Color::Blue));
    }
    window.draw(graph);
}

double origin_function_parameter(sf::RenderWindow& window, sf::VertexArray& graph, double size, Point (*parameter_input_function)(double), double current_t_value, double point_x, double point_y) {
    graph.clear();
    Point p;
    double x, y;
    double t_start = 0;
    double t_end = 10;
    double output = -100000000;
    bool click = false;
    std::vector<double> click_t;

    sf::CircleShape circle(std::max(size/20.0, 3.0)); // Create a circle with radius 3 (adjust as needed)
    circle.setFillColor(sf::Color::Black);

    for (double t = t_start; t <= t_end; t += 0.001){
        p = parameter_input_function(t);
        x = p.x;
        y = p.y;

        if (abs(point_x - x) < 5/size && abs(point_y - y) < 5/size) {
            click_t.push_back(t);
            click = true;
        }

        if (abs(current_t_value - t) <= 0.001)
            circle.setPosition(sf::Vector2f(x_scale(x, size)-circle.getRadius(), y_scale(y, size)-circle.getRadius())); // Set position based on scaled coordinates
        else
            graph.append(sf::Vertex(sf::Vector2f(x_scale(x, size), y_scale(y, size)), sf::Color::Green));
    }
    window.draw(graph);
    window.draw(circle); // Draw the circle
    if (click) {
        auto minElementIterator = std::min_element(click_t.begin(), click_t.end());
        output = static_cast<double>(*minElementIterator);
    }
    return output;
}

void EulerMethod(sf::RenderWindow& window, sf::VertexArray& graph, double startX, double startY, double stepSize, double size, bool tracer, double input_function(double, double), double start, double end) {
    double y = startY;
    graph.clear();

    for (double x = startX; x <= end/size; x += stepSize) {
        if (x_scale(x, size) >= start)
            graph.append(sf::Vertex(sf::Vector2f(x_scale(x, size), y_scale(y, size)), sf::Color::Red));
        double dydx = input_function(x, y);
        y += dydx * stepSize;
    }
    window.draw(graph);
}
#endif //EULER_METHOD_EULER_METHOD_H
